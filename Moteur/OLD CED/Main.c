    /*
 * File:   Main.c
 * Author: C�dric Somers
 *
 * Created on 26 avril 2013, 10:58
 */
// DSPIC33EP512MU810 Configuration Bit Settings

//#include <stdio.h>
//#include <stdlib.h>

#ifndef USE_512
    #include "p33EP512MU810.h"
#else
    #include "p33EP256MU810.h"
#endif

#include "Global.h"
#include <math.h>
#include "can_chinook3.h"
#include "chinookpack.h"
#include "can.h"

/* Variables Importante:
 * RPM   (Read)
 * POS   (write) 0 � 1
 */


// DSPIC33EP512MU810 Configuration Bit Settings

//#include <p33Exxxx.h>

 int FGS __attribute__((space(prog), address(0xF80004))) = 0xFFCF ;
//_FGS(
//    GWRP_OFF &           // General Segment Write-Protect bit (General Segment may be written)
//    GSS_OFF &            // General Segment Code-Protect bit (General Segment Code protect is disabled)
//    GSSK_OFF             // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)
//);
 int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0xFF79 ;
//_FOSCSEL(
//    FNOSC_FRCPLL &       // Initial Oscillator Source Selection Bits (Internal Fast RC with PLL (FRCPLL))
//    IESO_OFF             // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)
//);
 int FOSC __attribute__((space(prog), address(0xF80008))) = 0xFFDB ;
//_FOSC(
//    POSCMD_NONE &        // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
//    OSCIOFNC_ON &        // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
//    IOL1WAY_OFF &        // Peripheral pin select configuration (Allow multiple reconfigurations)
//    FCKSM_CSDCMD         // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
//);
 int FWDT __attribute__((space(prog), address(0xF8000A))) = 0xFFDF ;
//_FWDT(
//    WDTPOST_PS32768 &    // Watchdog Timer Postscaler Bits (1:32,768)
//    WDTPRE_PR128 &       // Watchdog Timer Prescaler bit (1:128)
//    PLLKEN_OFF &         // PLL Lock Wait Enable bit (Clock switch will not wait for the PLL lock signal.)
//    WINDIS_OFF &         // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
//    FWDTEN_ON            // Watchdog Timer Enable bit (Watchdog timer always enabled)
//);
 int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xFFF0 ;
//_FPOR(
//    FPWRT_PWR1 &         // Power-on Reset Timer Value Select bits (Disabled)
//    BOREN_OFF &          // Brown-out Reset (BOR) Detection Enable bit (BOR is disabled)
//    ALTI2C1_OFF &        // Alternate I2C pins for I2C1 (SDA1/SCK1 pins are selected as the I/O pins for I2C1)
//    ALTI2C2_OFF          // Alternate I2C pins for I2C2 (SDA2/SCK2 pins are selected as the I/O pins for I2C2)
//);
 int FICD __attribute__((space(prog), address(0xF8000E))) = 0xFFDE ;
//_FICD(
//    ICS_PGD2 &           // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
//    RSTPRI_PF &          // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
//    JTAGEN_OFF           // JTAG Enable bit (JTAG is disabled)
//);
 int FAS __attribute__((space(prog), address(0xF80010))) = 0xFFCF ;
//_FAS(
//    AWRP_OFF &           // Auxiliary Segment Write-protect bit (Auxiliary program memory is not write-protected)
//    APL_OFF &            // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
//    APLK_OFF             // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)
//);




/*
 *  RPM & Torque Meter
 */
void RPM_Init(float freq, unsigned int * ICx, unsigned int RPI);
struct TMeter{
/***** RPM Status *****/	
	//Tell if RollOver occur (bad reading)
	char RO;
	
	char DR;
	
	int Dir;
/***** RPM READING *****/
 //First Captured value (Start of count)
	unsigned int  T0_Low;
	unsigned int  T0_High;
   
 //Second Captured value (Stop of count)
	unsigned int  T1_Low;
	unsigned int  T1_High;
   
/***** Phase READING ****/

	unsigned int Ph_Low;
	unsigned int Ph_High;
} TMeter;
unsigned long Capture1, Capture2;
float RPM=0.0f;



/*
 *  STEPPER 
 */
float POS=0.0f;
float POS_CAN=0.0f;
extern long int stp_cnt;    //Stepper position
long int stp_pos_ref=0;     //Stepper position reference
extern float DUTY_1;
extern float DUTY_2;

/*
 *  PWM 
 */
void Init_PWM(unsigned int * PWMCONx, float freq, char start);
void Motor_PWM_two_Level(unsigned int * PWMx, float Duty);
void Motor_PWM_three_Level(unsigned int * PWMx, float Duty);
float DA =0.0f; //Duty cycle PWM A
float DB =0.0f; //Duty cycle PWM B
float DC =0.0f; //Duty cycle PWM C
float DD =0.0f; //Duty cycle PWM D
float DE =0.0f; //Duty cycle PWM E
float DF =0.0f; //Duty cycle PWM F



/*
 *  Timers and Oscillators
 */
void set_clk(float Fosc);
void map_osc_out(unsigned int rpi);
void Init_Timer3(float freq);
void Init_Timer2(float freq);
void Init_Timer4(float freq);

/*
 * CAN
 */

//float datReceive_can_manual_pitch = 0.0f;

char bTxCanBuffer[8];
chinookpack_fbuffer buf;
chinookpack_packer pk;
chinookpack_unpacked unpacker; //Will contain the unpacked data
unsigned int off = 0; //offset to read more than 1 msg in 1 packet

//fonction of reception CAN message
void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void initRx_CAN(void);
void initTx_CAN(void);

T_CAN_Tx_MSG can_msg_RPM;
/*
 *  MISC
 */
float t=0.0f;

float cmd=0.0f;
float Brake=0.0f;
//const unsigned int TMR8_MAX=100;

T_CAN_Tx_MSG can_msg_EEPROM_ACK;

/*
 * T1 CAN_Cycle (� impl�menter)
 * T2 CAN Timeout
 * T3 -> Control Loop Constant Sampling
 * T4 -> DC Motor Timer
 * T5 -> RPM Timeout
 * T6/T7, IC1/IC2 , INT3/INT4 -> RPM & Torque meter
 * T8 -> Stepper Motor Speed Timer
 * 
 * PWM1 -> STP MOTOR PHASE NotA
 * PWM2 -> STP MOTOR PHASE A
 * PWM3 -> STP MOTOR PHASE B
 * PWM4 -> DC MOTOR +
 * PWM5 -> STP MOTOR PHASE NotB
 * PWM6 -> DC MOTOR -
 * 
 */

int main(void)
{
unsigned int i,j;
long int err_L=1;
float err;

    set_clk(FOSCP);

    ANSELC = ANSELE = 0;
    TRISE = TRISC = 0;
    PORTE = PORTC = 0x0000; 

    ANSELB = 0xFFFF;


    
    //RPM_Init(0.1f, &IC1CON1, 104);	//Roll-over Frequency, Capture module

    	// Initialize can encoder & encoder
        init_CAN(CAN_NORMAL, 8, 1, 0, 7);
        Init_Timer2(10.0f); //CAN T
	chinookpack_fbuffer_init(&buf,bTxCanBuffer,8);
	chinookpack_packer_init(&pk,&buf,chinookpack_fbuffer_write);
	chinookpack_unpacked_init(&unpacker);

        //Init receive fct
        config_CAN_filter(0, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_manual_pitch);
        config_CAN_mask(CAN_MSG_MANUAL_PITCH_SID, 2.0f, STANDARD_ID);
	//initRx_CAN();
	//initTx_CAN();

    /*for(i=0;i<0x1000;i++)
    {
        for(j=0;j<0xF0;j++);
    }*/

    Init_PWM(&PWMA, 20E3,1);
    Init_PWM(&PWMB, 20E3,1);
    Init_PWM(&PWMC, 20E3,1);
    Init_PWM(&PWMD, 20E3,1);
    Init_PWM(&PWME, 20E3,1);
    Init_PWM(&PWMF, 20E3,1);

    PTCONbits.PTEN =1;
//#define TEST_PWM
#ifdef TEST_PWM
    Motor_PWM_two_Level(&PWMA, -0.90f);
    Motor_PWM_two_Level(&PWMB, -0.90f);
    Motor_PWM_two_Level(&PWMC, -0.90f);
    Motor_PWM_two_Level(&PWMD, -0.90f);
    Motor_PWM_two_Level(&PWME, -0.90f);
    Motor_PWM_two_Level(&PWMF, -0.90f);
    while(1);
#endif
    //Init timer
    StartSTEP(0XFFFF);
    StopSTEP();

    Init_Timer3(50.0f);
    //Init_Timer4(10.0f);
    //setup_can_tx();
    ActivateBrake(0.0);
    //while(1);
#define INIT_PITCH
#ifdef INIT_PITCH
    while(err_L != 0)
    {
        if(_T3IF)
        {
//Position error computation
            /*long int*/ err_L = -1000-stp_cnt;  //-avancer; +reculer

//Dceleration on 1 turn(200 step per turn) X 4 states per step
            err_L= (err_L > 100)?100:((err_L < -100)?-100:err_L);

            /*float*/ err = (float)(err_L);
//Proportionnal speed controller
            cmd = 0.7304f*cmd+0.2696f*err*0.0025f;
            cmd = (cmd > 0.99f)?0.99f:((cmd < -0.99f)?-0.99f:cmd);

 //Update timer 8 periode
            SpeedStep(cmd);
            _T3IF=0;
        }


        if(_T8IF)
        {
 //Change State machine that control the Stepper Motor
            UpdateStepper(0.0f);
            _T8IF = 0;
        }
    }
#endif
    //StopSTEP();
    //while(1);
    /********************************************************************/

    /********************************************************************/
    //InitADCReg2(12,12);
    stp_cnt =0;
    while(1)
    {
        if(_T3IF)
        {
//#define TEST_PITCH
#ifdef TEST_PITCH
            //Sinus test
            t+=0.01f;
            if(t>=6.283185)
            {
                t=0.0f;
            }

            POS = (0.5f)*sin(t)+0.5f;
#endif
            //int old_ipl;
//Position error computation
            //SET_AND_SAVE_CPU_IPL(old_ipl, 7);
            //POS = 0.25f;
            stp_pos_ref = (long int)(POS * (float)MAX_TRAVEL);
            /*long int*/ err_L = stp_pos_ref-stp_cnt;  //-avancer; +reculer

//Dceleration on 1 turn(200 step per turn) X 4 states per step
            err_L= (err_L > 200)?200:((err_L < -200)?-200:err_L);

            /*float*/ err = (float)(err_L);
//Proportionnal speed controller
            cmd = 0.7304f*cmd+0.2696f*err*0.0025f;
            cmd = (cmd > 0.99f)?0.99f:((cmd < -0.99f)?-0.99f:cmd);
            //envoi_CAN(CAN_MSG_EEPROM_CONFIG_ACK_SID);
 //Update timer 8 periode
            SpeedStep(cmd);
            //RESTORE_CPU_IPL(old_ipl);
//#endif
            _T3IF=0;
        }
        if(_T8IF)
        {
//Change State machine that control the Stepper Motor
            UpdateStepper(0.50f);
            _T8IF = 0;
        }

        if(TMeter.DR)
	{
            TMeter.DR=0;
            if(!TMeter.RO)
            {
                Capture1 = (unsigned long)(TMeter.T0_Low)+((unsigned long)(TMeter.T0_High)<<16); // Read and save off first capture entry
                Capture2 = (unsigned long)TMeter.T1_Low+((unsigned long)TMeter.T1_High<<16); // Read and save off second capture entry
                RPM += 0.05f*FOSCP/((float)Capture2-(float)Capture1);
			
            }		
	}

        ActivateBrake(POS);
    }
}
void setup_can_tx(void)
{
    /*configuration du message sur la demande des derni�res valeurs de gear et de position du m�t */
    config_CAN_Tx_msg(&can_msg_EEPROM_ACK, CAN_MSG_EEPROM_CONFIG_ACK_SID , STANDARD_ID, 3);

    // Initialize everything
    chinookpack_fbuffer_init(&buf,bTxCanBuffer,8);
    chinookpack_packer_init(&pk,&buf,chinookpack_fbuffer_write);

}
volatile char can_time_out;
void Reset_Timeout(void)
{
    T2CONbits.TON = 0;// Stop Timer2
    can_time_out = 0;
    TMR2 = 0; //Reset the CAN bus timeout counter
}
/*****************************************************************/
/*****************************************************************/
void Set_Timeout(void)
{
    T2CONbits.TON = 1;// Stop Timer2
}

void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        POS = unpacker.data.via.dec * 0.01f;
}
/*
void fct_can_Brake(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, int nbr_data)
{
    const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
         = unpacker.data.via.dec;

}*/
void initRx_CAN(void){

	/*configuration can message of manual pitch */
	config_CAN_filter(0, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_manual_pitch);
        config_CAN_mask(CAN_MSG_MANUAL_PITCH_SID, 2.0f, STANDARD_ID);

        //config_CAN_filter(1, CAN_MSG_BRAKE_SID, STANDARD_ID);
	//receive_CAN_msg(1, 3, fct_can_Brake);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

}
void initTx_CAN(void){

	/*configuration du message sur le pitch variable */
	config_CAN_Tx_msg(&can_msg_RPM, CAN_MSG_TURBINE_RPM_MOTOR_SID , STANDARD_ID, 3);

}

void InitADCReg2(unsigned int CHA,unsigned int CHB)
{
	//Analog conerter used
	//AN8, AN9, AN10, AN11
	/* Initialize ADC module */
	AD2CON1 = 0x0000; // Enable auto-sample and auto-conversion

	AD2CON1bits.ASAM=1;   // ADC Sample Auto-Start bit
	AD2CON1bits.SSRC=0b010;	//Use timer3 as trigger source

	AD2CON2 = 0x0000; // Select 2-channel mode, enable both scanning and alternate sampling
	AD2CON2bits.CSCNA = 0;		//Don't Scan inputs
	AD2CON2bits.CHPS = 0b00;	//Convert Ch0
	AD2CON2bits.SMPI = 1;		//Interrupt after 2 Convert (after A & B)
	AD2CON2bits.ALTS = 1;		//Convert Channel  A & B
	float Tad = 8.3f; //1/(1 TAD) -> 1/(120 ns) = 8.3 MHz
	Tad= FOSCP/Tad;
	AD2CON3 = 0; // Sample for 15 * Tad before converting
	AD2CON3bits.ADCS = 3+(unsigned int)Tad;
	AD2CON4 = 0x0000;
	AD2CSSL = 0x0000;
	/* Assign MUXA inputs */
	AD2CHS0 =0;
	AD2CHS0bits.CH0SA = CHA; // CH0SA bits ignored for CH0 +ve input selection
	AD2CHS0bits.CH0NA = 0; // Select VREF- for CH0 -ve input

/*	AD1CON2bits.ALTS = 0;		//Convert only Channel A
	AD1CHS123bits.CH123SA = 0;	//AN0-AN2
	AD1CHS123bits.CH123NA = 0;
	AD1CHS123bits.CH123SB = 0;	//AN3-AN5
	AD1CHS123bits.CH123NB = 0;*/
	/* Assign MUXB inputs */

	AD2CHS0bits.CH0SB = CHB; // Select AN10 for CH0 +ve input
	AD2CHS0bits.CH0NB = 0; // Select VREF- for CH0 -ve input
	/* Enable ADC module and provide ADC stabilization delay */
	_AD2IF=0;
	_AD2IE=1;
	AD2CON1bits.ADON = 1;
}


#define LOW     -0.35f
#define MID     0.0f
#define HIGH    0.35f

void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{   
 /*   t +=0.1;
    if( t>1.0f)
    {
        t=0;
    }
 */


   _T3IF=0;
}


void set_clk(float Fosc)
{
    int i;
    int tmp=0b111;
    float FRC = 7.37f; //MHz
    float Fvco = 0.0f;
    _DOZE = 0;
    _PLLPRE = 2 ;       //0=/2; 1=/3; 2=/4 ... /33
    _PLLPOST = 0;       // =/2

    Fvco = (Fosc/FRC *(float)(_PLLPRE+2));
    PLLFBD = (unsigned int)(Fvco*((float)(2<<_PLLPOST)));

    //while(_LOCK ==0);

}


void Init_PWM(unsigned int * PWMCONx, float freq, char start)
{
    // PWM module is used as independant
	PTCON = 0;
	PTCON2bits.PCLKDIV = 0b000;  // 0b01=2.0f / 0b10=4.0f / 0b11 = 8.0f
	PTPER = (unsigned int)((FOSCP*1e6/1.0f)/freq);	//500khz period

        //MDC = (unsigned int)((float)PTPER*0.25f);
    //PDCx
        PWMCONx[3] = 0;

   /*PWMCONx    FLTSTAT CLSTAT TRGSTAT FLTIEN
    *           CLIEN   TRGIEN ITB     MDCS
    *           DTC<1:0>       DTCP    ?
    *           MTBS    CAM    XPRES   IUE*/
        PWMCONx[0] =0x0040;

   /*IOCONx PENH PENL POLH POLL
    *       PMOD<1:0> OVRENH OVRENL
    *       OVRDAT<1:0> FLTDAT<1:0>
    *       CLDAT<1:0> SWAP OSYNC*/
	//PWMCONx[1] =0x4000;

        if(start>0)
        {
            
            if(PWMCONx == &PWMCON2 || PWMCONx == &PWMCON4 || PWMCONx==&PWMCON6)
            {
                //Swap PIN for PWM on bottom layer
                PWMCONx[1] = 0xD082;
            }
            else
            {
                PWMCONx[1] = 0xE080;
            }
        }

   /*PHASEx*/
        //PWMCONx[4] = MDC>>2;
   /*DTRx*/

        PWMCONx[5] =  0x0058/*(unsigned int)((float)PTPER*0.25f)*/;
        PWMCONx[6]  = 0x0058/*(unsigned int)((float)PTPER*0.25f)*/;

        /*TRIG DIV*/
        //PWMCONx[10] = 7<<12;

}

void Motor_PWM_two_Level(unsigned int * PWMx, float Duty)
{
	/*
		Two Level motor drive. Duty from -1.0f to 1.0f
		Motor voltage waveform below
+VCC   _            _____      __        _____
     0 _	   |     |    |  |      |     |     |
-VCC   _	___|     |____|  |______|     |_____|

	Register Map
	PWMx[0] = PWMCONx
	PWMx[1] = IOCONx
	PWMx[2] = FCLCONx
	PWMx[3] = PDCx
	PWMx[4] = PHASEx
	PWMx[5] = SDCx
	etc...
	*/
	Duty = 0.5f*Duty+0.5f;

	PWMx[3] = (unsigned int)((float)PTPER*Duty);

}
/*
	Call exemple
	Motor_PWM_three_Level(& PWMCON1, -0.5f)
*/
void Motor_PWM_three_Level(unsigned int * PWMx, float Duty)
{
	/*
		Three Level motor drive. Duty from -1.0f to 1.0f
		Motor voltage waveform below
		|---Forward PWM----|
+VCC  _		_____      __
	0 _	___|     |____|  |___    _____       ____
-VCC  _	                     |__|     |_____|

	                        |-----Backward PWM---|
	Register Map
	PWMx[0] = PWMCONx
	PWMx[1] = IOCONx
	PWMx[2] = FCLCONx
	PWMx[3] = PDCx
	PWMx[4] = PHASEx
	etc...

	*/

	//PWM in redundant mode
	//OVRDAT<1:0>: = 0b00
	if(Duty < 0.0f)
	{
		//High output active
		//Overide Low output with low state
		Duty *= -1.0f;
		PWMx[1] &= ~0x0100;		//Clear bit 8 OVRENL: PWM generator provides data for PWMxL pin
		PWMx[1] |= 0x0200;		//Set bit 9 OVRENH: Override Enable for PWMxH Pin bit
		PWMx[3] = (unsigned int)((float)PTPER*Duty);
	}
	else
	{
		//High output active
		//Overide Low output with low state
		PWMx[1] &= ~0x0200;		//Clear bit 9 OVRENH: PWM generator provides data for PWMxH pin
		PWMx[1] |= 0x0100;		//Set bit 8 OVRENL: Override Enable for PWMxL Pin bit
		PWMx[3] = (unsigned int)((float)PTPER*Duty);
	}
}
//Remap reference clock to a RPx IO
void map_osc_out(unsigned int rpi)
{
    unsigned int *RPT = &RPOR0;

    REFOCON = 0;
    REFOCONbits.RODIV = 0;
    REFOCONbits.ROSEL = 0; // Sysclock as refclock
    REFOCONbits.ROON  = 1;
    RPT += rpi/2;
    *RPT = 0b100110<<(8*(rpi%2));
    //RPOR11 = 0b100110;
}


void Init_Timer2(float freq)
{
	float div=2.0f;
	//Init Timer 3
	TMR2 = 0x0000;

	//Calibrate prescaller with given freq
	if(FOSCP*1e6/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;
		T2CONbits.TCKPS	= 0b11;
	}
	else if(FOSCP*1e6/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T2CONbits.TCKPS	= 0b10;
	}
	else if(FOSCP*1e6/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T2CONbits.TCKPS	= 0b01;
	}
	else
	{
		T2CONbits.TCKPS	= 0b00;
	}

	PR2 = (unsigned int)(FOSCP*1e6/(div*freq));
	div=1.0f/div;
	_T2IF = 0;// Clear Timer2 interrupt
	_T2IP = 6;
	_T2IE = 1;// Disable Timer2 interrupt
	T2CONbits.TON = 1;// Start Timer2
}


void Init_Timer3(float freq)
{
	float div=2.0f;
	//Init Timer 3
	TMR3 = 0x0000;

	//Calibrate prescaller with given freq
	if(FOSCP*1e6/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;
		T3CONbits.TCKPS	= 0b11;
	}
	else if(FOSCP*1e6/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T3CONbits.TCKPS	= 0b10;
	}
	else if(FOSCP*1e6/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T3CONbits.TCKPS	= 0b01;
	}
	else
	{
		T3CONbits.TCKPS	= 0b00;
	}

	PR3 = (unsigned int)(FOSCP*1e6/(div*freq));
	div=1.0f/div;
	_T3IF = 0;// Clear Timer3 interrupt
	_T3IP = 6;
	_T3IE = 0;// Disable Timer3 interrupt
	T3CONbits.TON = 1;// Start Timer3
}
void Init_Timer4(float freq)
{
	float div=2.0f;
	//Init Timer 3
	TMR4 = 0x0000;

	//Calibrate prescaller with given freq
	if(FOSCP*1e6/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;
		T4CONbits.TCKPS	= 0b11;
	}
	else if(FOSCP*1e6/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T4CONbits.TCKPS	= 0b10;
	}
	else if(FOSCP*1e6/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T4CONbits.TCKPS	= 0b01;
	}
	else
	{
		T4CONbits.TCKPS	= 0b00;
	}

	PR4 = (unsigned int)(FOSCP*1e6/(div*freq));
	div=1.0f/div;
	_T4IF = 0;// Clear Timer2 interrupt
	_T4IP = 6;
	_T4IE = 0;// Disable Timer2 interrupt
	T4CONbits.TON = 1;// Start Timer2
}


const float G_norm = 1.0f/1024.0f;
float ref= 0.5f;

void __attribute__((interrupt, auto_psv)) _AD2Interrupt(void)
{
    //stp_pos_ref = ADC2BUF0;

    //cmd=((float)(ADC2BUF0)*G_norm)-1.0f;
   /*
    float speed = z0-z1;
    
    float ErrSpeed = ((ref-z0)*10.0f)-speed;
    
    cmd = 5.0f*(ref-z0);


    cmd = (cmd > 0.99f)?0.99f:((cmd < -0.99f)?-0.99f:cmd);
   */
    //Motor_PWM_two_Level(&PWME, -1.0f*cmd);
    //Motor_PWM_two_Level(&PWMF, cmd);
/*    
        float err = 0.25f-((float)(ADC2BUF0+ADC2BUF1))*G_norm;

        cmd = 10.0f*err;


*/
//First order LPF	fixpoint
	//val:	 ADC *   1/(10*pi) + Mpwm  *  0.9691
	//type:  (1:10)  (1:14)      (1:10)  (1:14)
	//tmp = ((long)ADC2BUF0*0x020a) + ((long)Mpwm* 0x3E06);
	//tmp = ((long)ADC2BUF0*0x021) + ((long)Mpwm* 0x3E0);
	//Mpwm = (int)(tmp>>10);

/*
//second order LPF floating
	tmpOUT_2=fpwm;
	fpwm = sample_1*(e1-e2) + fpwm*e11 - OUT_2*e2;
	fpwm *= 10.0f*e3;
	sample_1= (float)ADC2BUF0*G_ADC;
	OUT_2 = tmpOUT_2;
*/
	_AD2IF=0;
}


void RPM_Init(float freq, unsigned int * ICx, unsigned int RPI)
 {
 	//Start 32 Bits Timer (8 & 9)
 	unsigned long tmp;
 	T7CONbits.TON = 0; // Stop any 16-bit Timer3 operation
	T6CONbits.TON = 0; // Stop any 16/32-bit Timer3 operation
	T6CONbits.T32 = 1; // Enable 32-bit Timer mode
	T6CONbits.TCS = 0; // Select internal instruction cycle clock
	T6CONbits.TGATE = 0; // Disable Gated Timer mode
	
	T6CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
	tmp=(unsigned long)(FOSCP/(2.0f*freq));
	TMR7 = 0x00; // Clear 32-bit Timer (msw)
	TMR6 = 0x00; // Clear 32-bit Timer (lsw)
	PR7 = (unsigned int)((tmp>>16) & 0xFFFF); // Load 32-bit period value (msw)
	PR6 = (unsigned int)(tmp & 0xFFFF); // Load 32-bit period value (lsw)
	//_T9IP = 0x05; // Set Timer3 Interrupt Priority Level
	//_T9IF = 0; // Clear Timer3 Interrupt Flag
	//_T9IE = 1; // Enable Timer3 interrupt
	T6CONbits.TON = 1; // Start 32-bit Timer
 	
 	//Start 32 Bits Input Capture
	
	IC2CON1bits.ICM = 0b000; // Disable Input Capture 1 module
	IC2CON1bits.ICTSEL = 7; // Select system clock as the IC1 Time base
	IC2CON1bits.ICI = 0b01; // Interrupt on every 2 capture event
	IC2CON2 = 0; // No sync or trigger source for IC1
	IC2CON2bits.IC32=1;
	IC2CON1bits.ICM = 0b010; // Generate capture event on every falling edge
	
	//Initialize Input Capture Module:
	IC1CON1bits.ICM = 0b000; // Disable Input Capture 1 module
	IC1CON1bits.ICTSEL = 7; // Select system clock as the IC1 Time base
	IC1CON1bits.ICI = 0b01; // Interrupt on every 2 capture event
	IC1CON2 = 0; // No sync or trigger source for IC1
	IC1CON2bits.IC32=1;
	IC1CON1bits.ICM = 0b010; // Generate capture event on every falling edge
	
	
	_IC1R = RPI;
 	_IC2R = RPI;
	_IC1IF=0;
 	_IC1IE=1; 
 
 	_INT3R = RPI;	
 	_INT4R = 65;
	//Setup Phase detection 
	INTCON2bits.INT3EP = 1; // 0: Interrupt on positive edge   1: negative
	INTCON2bits.INT4EP = 1; // 0: Interrupt on positive edge   1: negative
	
	_INT3IF=0;
	_INT4IF=0;
	
	_INT3IE=1;
	_INT4IE=1;
	
	T5CON=0;
	TMR5=0;
	PR5=0xFFFF;
 }
void __attribute__ ((__interrupt__, no_auto_psv)) _IC1Interrupt(void)
{
	unsigned int tmp;
	//float fin;
_IC1IF = 0; // Reset respective interrupt flag

TMeter.T0_Low=IC1BUF;
TMeter.T1_Low=IC1BUF;

TMeter.T0_High=IC2BUF;
TMeter.T1_High=IC2BUF;

//_RA2 = ~_RA2;

if(IC1CON1bits.ICOV || IC2CON1bits.ICOV || IC1CON1bits.ICOV || IC2CON1bits.ICOV)	//Buffer overflow
{
	while(IC1CON1bits.ICBNE)
	{
		tmp = IC1BUF;
	}
	
	while(IC2CON1bits.ICBNE)
	{
		tmp = IC2BUF;
	}
	IC1CON1bits.ICOV = 0;
	IC2CON1bits.ICOV = 0;
}

//Rolover detection
	if(_T7IF)
	{
		_T7IF=0;
		TMeter.RO = 1;
			//fin = 0.0f;
	}
	else
	{
		TMeter.RO = 0;
			//fin = 0.5f*FOSCP/((float)Capture1);
	}
	
	TMR7 = TMR6=0;
}
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)
{
    can_time_out =1;
	_T2IF=0;
}
void __attribute__((interrupt, auto_psv)) _T5Interrupt(void)
{
	
	_T5IF=0;
}
void __attribute__((interrupt, auto_psv)) _T7Interrupt(void)
{
	
	_T7IF=0;
}
void __attribute__((interrupt, auto_psv)) _INT3Interrupt(void)
{
	//timer is started
	if(T5CON)
	{
		//Stop Timer
		T5CON= 0x0000;
		//_RA4 = 1;
		//Save Phase value
		TMeter.Ph_Low = TMR5;
		//tmp = TMR7;
		//Clear counter
		TMR5=0;
	
		TMeter.DR = 1;
		
		//Is going forward
		TMeter.Dir = 1;
	}
	else
	{
		//Start Timer
		T5CON= 0x8000;
		//_RA4 = 0;
	}
	_INT3IF=0;
}	
	void __attribute__((interrupt, auto_psv)) _INT4Interrupt(void)
{
	//timer is started
	if(T5CON)
	{
		//Stop Timer
		T5CON= 0x0000;
		//_RA4 = 1;
		//Save Phase value
		TMeter.Ph_Low = TMR5;
		//tmp = TMR7;
		//Clear counter
		TMR5=0;
	
		TMeter.DR = 1;
		//Is going backward
		TMeter.Dir = -1;
	}
	else
	{
		//Start Timer
		T5CON= 0x8000;
		//_RA4 = 0;
	}
	_INT4IF=0;
}	

void envoi_CAN(int ID)
{
    switch(ID)
    {
        case CAN_MSG_EEPROM_CONFIG_ACK_SID:
            chinookpack_pack_uint8(&pk,1);
            Set_Timeout();
            send_CAN_msg(&can_msg_EEPROM_ACK,bTxCanBuffer, 2);
            while(!is_CAN_msg_send(&can_msg_EEPROM_ACK) && !can_time_out);
            Reset_Timeout();
            // If you need to clear the packer buffer
            chinookpack_fbuffer_clear(&buf);
        break;

        default:

        break;
    }

}

char CAN_delai = 0;

void envoi_CAN_periodique(void)
{
    /*if(CAN_cycle)
    {

        CAN_delai++;
        if(CAN_delai==5)
        {
            CAN_delai = 0;
            envoi_CAN(CAN_MSG_EEPROM_CONFIG_ACK_SID);
        }

    }*/

}
