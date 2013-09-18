/*
Propriété du 
Club Chinook ETS
*/
/******************************************************************
                        	CMD.c
******************************************************************/

//Contient la commande et l'asservissement des moteurs

#include "CMD.h"
#include "M_TMR.h"
#include "M_PWM.h"
#include "M_ADC.h"
#include "chinookpack.h"
#include "can.h"


/******************************************************************
                            Transmission
******************************************************************/

volatile char NF;	//Flag from timer3 to update stepper
char gear=1;
static int i = 0;
static int k = 0;
unsigned char step_print[80];
unsigned int stepref = 0;
unsigned int stepcnt = 30;
extern int datReceive_can_cmd;
extern char datReceive_can_shift;
extern chinookpack_fbuffer buf; //from main.c
extern chinookpack_packer pk; //from main.c
extern unsigned char last_gear;
int delai=0;
#define STEP_COUNT_MAX 91
#define STEP_INCREMENT 7
#define print_step
//#define print_gear_CMD

void Stepper_Shift(void)
{

    if(NF)
    {
        NF=0;

        if(stepref!=stepcnt)
        {
            if(stepref >=stepcnt)
            {
                    UpdateStepper(UP);
                    stepcnt++;
            }
            else
            {
                    UpdateStepper(DOWN);
                    stepcnt--;
            }
            #ifdef print_step
            sprintf(step_print,"STEPCNT : %d \t STEPREF : %d \t \r",stepcnt,stepref);

            k=0;
            do
            {
                    U1TXREG=step_print[k];

                    while(U1STAbits.TRMT!=1);
                    k++;

            }while(step_print[k]!=0);
            #endif

        }
    }
    else if(stepref == stepcnt)
    {
        DisableStepper();

        #ifdef print_gear_CMD
        sprintf(step_print,"gear : %d \t\r",datReceive_can_shift);

        k=0;
        do
        {
                U1TXREG=step_print[k];

                while(U1STAbits.TRMT!=1);
                k++;

        }while(step_print[k]!=0);
        #endif

        delai++;
        if(delai>3)
        {
            delai = 0;
            if(datReceive_can_shift==1)
            {
                SHIFT_UP();
            }
            else if(datReceive_can_shift==2)
            {
                SHIFT_DOWN();
            }
        }
    }
}


 void Stepper_Shift_Init(char lastgear)
{
        /*Delay so that the stepper is not activated while programming*/
        while(stepcnt)
	{
		if(NF)
		{
			stepcnt--;
			NF=0;
		}
	}
        lastgear--;
        stepref = lastgear*(STEP_INCREMENT);
        stepcnt = lastgear*(STEP_INCREMENT);
	STPER /=1.5f;

        /*Enable Stepper*/
        EN_STEP = 0;

	/*while(stepcnt)
	{
            Stepper_Shift();
	}*/
        DisableStepper();
        //gear = 1;
}

void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
	NF = 1;
	_T3IF=0;
}

void UpdateStepper(int direction)
{
            DIR=direction;
            EN_STEP=0;
            IOCON5bits.PENL = 1;
}

void SHIFT_UP(void)
{
	stepref+=(stepcnt < STEP_COUNT_MAX)?STEP_INCREMENT:0;
        gear+=(gear==14)?0:1;
}

void SHIFT_DOWN(void)
{
	stepref+=(stepcnt > 0)?-STEP_INCREMENT:0;
        gear-=(gear==1)?0:1;
}

void DisableStepper(void)
{
	//disable  stepper motor
        EN_STEP=1;
        IOCON5bits.PENL = 0;
}


unsigned int DutyCycle(float duty)
{
	duty=(duty<0.00001f)?0.0f:((duty>0.9999f)?1.0f:duty);
	return (unsigned int)(PTPER*duty);
}

/******************************************************************
                             Mât
******************************************************************/

/*PWM command to DC motor*/
static float CMD=0.0f;

/*Current*/
static float Current_Error=0.0f;
float Current_DC = 0.0f;
float Current_CMD = 0.0f;
volatile int ADC_FLAG = 0;
const float Current_noload = 0.18f;

/*UART*/
volatile unsigned char print_speed = 0;
volatile unsigned char print_pos = 0;
unsigned char speed_print [80];
unsigned char pos_print [80];
unsigned char current_print [80];
unsigned int j = 0;
unsigned int print_decoupl = 0;

/*Flag to update tower position*/
volatile int flag_DC_motor = 0;

/*Speed/Position*/
const float PPT = 60.0f*FREQ_QEI/(980.0f*50.0f);
const float Position_const = (360.0f)/(980.0f*50.0f);
float Speed_error = 0.0f;
float Shaft_Speed = 0.0f;
float Position_mat = 0.0f;
float Speed_CMD = 0.0f;
static float Position_error = 1.0f;
static float Position_error_init = 0.0f;
volatile int NV = 0; /*Speed of dc motor*/
volatile int NP =0; /*Position of dc motor*/
#define mat_position_initiale 0.0f
float wind_direction_filt;

//#define print_current
//#define print_speed
//#define print_position
//#define print_wind_direction

char can_print_WD [80];
char n = 0;

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
         NV = (volatile int)VEL1CNT;
         NP = (volatile int)POS1CNTL;
         flag_DC_motor = 1;
	_T1IF = 0;
}

void Init_mat(float last_position_tourelle)
{
    Position_mat = last_position_tourelle;

    do{
        tower_motor_ctrl(&PDC1,0.0f);
    }while(Position_mat < -1.0f || Position_mat > 1.0f);
}

void tower_motor_ctrl(unsigned int * duty_reg,float POS_CMD)
{

        /*if(ADC_FLAG)
        {
            Current_DC = ((((float)(ADC1BUF0+ADC1BUF1+ADC1BUF2+ADC1BUF3+ADC1BUF4+ADC1BUF5+ADC1BUF6+ADC1BUF7)*G_ADC)/8.0f)-(1.69f));
            ADC_FLAG = 0;
        }*/

        if(flag_DC_motor)
        {   
            wind_direction_filt = POS_CMD;
            #ifdef print_wind_direction
            sprintf(can_print_WD,"Wind Direction : %.2f degrees \t \r",POS_CMD);
            n=0;
            do
            {
                    U1TXREG=can_print_WD[n];

                    while(U1STAbits.TRMT!=1);
                    n++;
            }while(can_print_WD[n]!=0);
            #endif

            //Shaft speed = Velocity counter / (49*20)*1/10Hz * 60
            Shaft_Speed = ((float)NV)*PPT;
            Position_mat=((float)NP)*Position_const;
            //POS_CMD = (POS_CMD>90.0f)?90.0f:((POS_CMD<-90.0f)?-90.0f:POS_CMD);

            /*Error = Ref - Reading*/
            Position_error = POS_CMD-Position_mat;
            Speed_CMD = Position_error*0.28f;

            Speed_error = Speed_CMD-Shaft_Speed;

            //Speed PI controller
            CMD = 0.04f*Speed_error+0.80f*CMD;

            //Saturation of the output
            CMD = (CMD>0.5f)?0.4f:((CMD<-0.5f)?-0.4f:CMD);

            if(CMD<0.035f && CMD >-0.035f)
                CMD = 0.0f;

            *duty_reg= (unsigned int)((CMD*(float)PTPER)+PTPER/2);
                
            print_decoupl++;
            if(print_decoupl>=5)
            {
                #ifdef print_position
                sprintf(pos_print,"Position DC motor : %5.2f \tPosition CMD : %5.2f \tPosition Error : %5.2f \tWind Dir : %5.2f \t CMD : %5.2f \r",(float)Position_mat,(float)POS_CMD,(float)Position_error,(float)Speed_error,(float)CMD);
                j=0;
                do
                {
                        U1TXREG=pos_print[j];

                        while(U1STAbits.TRMT!=1);
                        j++;
                }while(pos_print[j]!=0);
                #endif

                #ifdef print_speed
                sprintf(speed_print,"Speed : %4.2f \t Speed error : %4.2f\t CMD : %4.2f\t \r",Shaft_Speed,Speed_error,CMD);
                j=0;
                do
                {

                        U1TXREG=speed_print[j];

                        while(U1STAbits.TRMT!=1);
                        j++;

                }while(speed_print[j]!=0);
                #endif

                #ifdef print_current
                sprintf(current_print,"CURRENT : %2.2fA \t CURRENT CMD : %2.2fA \t CURRENT ERROR : %2.2fA \t CMD (%PWM): %2.2f \t\r",Current_DC,Current_CMD,Current_Error,CMD);

                j=0;
                do
                {

                        U1TXREG=current_print[j];

                        while(U1STAbits.TRMT!=1);
                        j++;

                }while(current_print[j]!=0);
                #endif

            print_decoupl=0;
            }

        flag_DC_motor = 0;
        }

}

void __attribute__((interrupt, auto_psv)) _AD1Interrupt(void)
{
        ADC_FLAG=1;
	_AD1IF = 0;
}
