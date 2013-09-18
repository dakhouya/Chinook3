/*
Propriété du 
Club Chinook ETS
*/
/******************************************************************
					Main.c
******************************************************************/



// DSPIC33EP512MU810 Configuration Bit Settings

#include "p33EP512MU810.h"

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
 int FOSC __attribute__((space(prog), address(0xF80008))) = 0xFFDF ;
//_FOSC(
//    POSCMD_NONE &        // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
//    OSCIOFNC_OFF &       // OSC2 Pin Function bit (OSC2 is clock output)
//    IOL1WAY_OFF &        // Peripheral pin select configuration (Allow multiple reconfigurations)
//    FCKSM_CSDCMD         // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)
//);
 int FWDT __attribute__((space(prog), address(0xF8000A))) = 0xFF7F ;
//_FWDT(
//    WDTPOST_PS32768 &    // Watchdog Timer Postscaler Bits (1:32,768)
//    WDTPRE_PR128 &       // Watchdog Timer Prescaler bit (1:128)
//    PLLKEN_ON &          // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
//    WINDIS_OFF &         // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
//    FWDTEN_OFF           // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)
//);
 int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xFFF0 ;
//_FPOR(
//    FPWRT_PWR1 &         // Power-on Reset Timer Value Select bits (Disabled)
//    BOREN_OFF &          // Brown-out Reset (BOR) Detection Enable bit (BOR is disabled)
//    ALTI2C1_OFF &        // Alternate I2C pins for I2C1 (SDA1/SCK1 pins are selected as the I/O pins for I2C1)
//    ALTI2C2_OFF          // Alternate I2C pins for I2C2 (SDA2/SCK2 pins are selected as the I/O pins for I2C2)
//);
 int FICD __attribute__((space(prog), address(0xF8000E))) = 0xFFDF ;
//_FICD(
//    ICS_PGD1 &           // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
//    RSTPRI_PF &          // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
//    JTAGEN_OFF           // JTAG Enable bit (JTAG is disabled)
//);
 int FAS __attribute__((space(prog), address(0xF80010))) = 0xFFCF ;
//_FAS(
//    AWRP_OFF &           // Auxiliary Segment Write-protect bit (Auxiliary program memory is not write-protected)
//    APL_OFF &            // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
//    APLK_OFF             // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)
//);

/******************************************************************
			Modules Definition
*******************************************************************
TIMER1  //DC motor control
TIMER2	
TIMER3	//Stepper speed control
TIMER5	
TIMER6	
TIMER7	
TIMER8	
TIMER9	

QEI1    //Speed/position control
QEI2

PWM1    //DC motor control
PWM5    //Stepper step control
						
ADC1    //DC motor current sampling
ADC2
				
******************************************************************/

/******************************************************************
				Includes
******************************************************************/
#include "Global.h"
#include "can.h"
#include "dma.h"
#include "can_chinook3.h"
#include "CMD.h"
#include "M_UART.h"
#include "M_TMR.h"
#include "M_PWM.h"
#include "M_ADC.h"
#include "M_QEI.h"
#include <stdio.h>
#include "chinookpack.h"

/******************************************************************
                    Variable, Macro & Const
******************************************************************/

const float PI=3.141592653589793f;
chinookpack_unpacked unpacker;
unsigned int off=0;
#define mat_manuel
char cmd_mat = 0;
char last_cmd_mat = 15;
unsigned int delai_mat = 0;

/******************************************************************
                            CAN
******************************************************************/

/*Pointers to data received*/
int datReceive_can_cmd[4]={0,0,0,0};
char datReceive_can_shift;
float datReceive_can_wind_direction = 0.0f;
char datReceive_can_EEPROM_CONFIG_ANSWER_gear =0xFF;
float datReceive_can_EEPROM_CONFIG_ANSWER_mat = 190.0f;
int datReceive_can_conf;

/*Data transmitted*/
T_CAN_Tx_MSG can_msg_EEPROM_REQUEST;
T_CAN_Tx_MSG can_msg_EEPROM_ACK;
T_CAN_Tx_MSG can_msg_GEAR;
T_CAN_Tx_MSG can_msg_POSITION_MAT;
char canBuffer[8]; //Buffer that contain the encoded data
chinookpack_fbuffer buf;
chinookpack_packer pk;
volatile char CAN_cycle = 0;

/*User application*/
char can_print[80];
float wind_direction = 0.0f;
unsigned char last_gear = 14;
float last_position_mat = 0.0f;

#define memory_init
extern volatile char NF;
extern float Position_mat;
extern volatile char can_time_out;
extern char gear;
char EEPROM_REQUEST = 0;

/****************************************************************
                            Prototype
******************************************************************/
void set_clk(void);
void InitIO(void);
void initialisation_CAN(void);
void setup_can_rx(void);
void setup_can_tx(void);
void envoi_CAN(int ID);
void envoi_CAN_periodique(void);

void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_shift(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_EEPROM_CONFIG_ANSWER(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_conf(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);

/******************************************************************
                                Main
******************************************************************/
int main(void)
{
        /*Disable watchdog*/
        RCONbits.SWDTEN = 0;
        
	set_clk();

	InitIO();

        //Initialize CAN communication
        initialisation_CAN();
        
	//Initialize PWM (Motor Control)
        Init_PWM();

	//Initialize ADC
	//Init_ADC();
	
	//Initialize QEI (Speed/Position DC motor)
	InitQEI();
        chinookpack_unpacked_init(&unpacker);

        #ifdef memory_init
        /*Retrieve Last gear and mât position*/
        do{
            EEPROM_REQUEST = 0x55;
            envoi_CAN_periodique_init();
            last_gear = datReceive_can_EEPROM_CONFIG_ANSWER_gear;
            last_position_mat = datReceive_can_EEPROM_CONFIG_ANSWER_mat;
        }while(datReceive_can_EEPROM_CONFIG_ANSWER_mat==190.0f);
        gear = last_gear;
        Position_mat = last_position_mat;
        char print[80];
        sprintf(print,"last gear: %d \t last position mat : %f \r",last_gear,last_position_mat);
        char u=0;
        do
        {
                U1TXREG=print[u];

                while(U1STAbits.TRMT!=1);
                u++;

        }while(print[u]!=0);
        int k=0;
        do{
            EEPROM_REQUEST = 0xAA;
            envoi_CAN_periodique_init();
            k++;
        }while(k<5);
        #endif
        
        /*Enable 24V supply switch*/
        ENALIM = 1;
                                                                                                                    //envoi_CAN_periodique();
        //envoi_CAN_periodique();
        //Transmission goes to first gear

        Stepper_Shift_Init(last_gear);
        //Mat goes to origin
        //Init_mat(last_position_mat);

	while(1)
	{

            //Transmission goes to first gear
            if(datReceive_can_conf)
                Stepper_Shift_Init(last_gear);

            Stepper_Shift();

            envoi_CAN_periodique();
            
            #ifdef mat_manuel
            if(!datReceive_can_cmd[0])
            {
                if(last_cmd_mat == 14 || last_cmd_mat == 15){
                    cmd_mat=datReceive_can_cmd[3]|datReceive_can_cmd[2]|datReceive_can_cmd[1]|datReceive_can_cmd[0];
                }
                if(last_cmd_mat == 11){
                    delai_mat++;
                    cmd_mat = 0;
                    if(delai_mat<60000)
                        tower_motor_ctrl(&PDC1,Position_mat);
                    else if(delai_mat>=60000)
                        delai_mat = 0;
                    
                }
            }
            else if(!datReceive_can_cmd[2])
            {
                if(last_cmd_mat == 11  || last_cmd_mat == 15){
                    cmd_mat=datReceive_can_cmd[3]|datReceive_can_cmd[2]|datReceive_can_cmd[1]|datReceive_can_cmd[0];
                }
                if(last_cmd_mat == 14){
                    cmd_mat = 0;
                    delai_mat++;
                    if(delai_mat<60000)
                        tower_motor_ctrl(&PDC1,Position_mat);
                    else if(delai_mat>=60000)
                        delai_mat = 0;

                }
            }
            else //if(datReceive_can_cmd == 15)
            {
                cmd_mat=15;
            }
            if(cmd_mat ==14)
            {
                last_cmd_mat = cmd_mat;
                LED0^=1;
                tower_motor_ctrl(&PDC1,-180.0f);
            }
            else if(cmd_mat == 11)
            {
                last_cmd_mat = cmd_mat;
                tower_motor_ctrl(&PDC1,180.0f);
            }
            else if(cmd_mat == 15)
            {
                last_cmd_mat = cmd_mat;
                tower_motor_ctrl(&PDC1,Position_mat);
            }
            #endif
            #ifdef mat_test
            tower_motor_ctrl(&PDC1,-90.0f);
            #endif
            #ifdef mat_auto
            tower_motor_ctrl(&PDC1,datReceive_can_wind_direction);
            #endif
            
            
	}
}
/******************************************************************
			Functions
******************************************************************/
void set_clk(void)
{					//datasheet section 7 p.21
_PLLPRE=0;
_PLLPOST=0;
_PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;
while(OSCCONbits.LOCK !=1);
}


void InitIO(void)
{
	//Init UART for debug
	//If USB is plugged
	//TTL232R-3V3-WE will pull _RF3 and _RF5 high
	if(_RF2==1 && _RF3==1);
	{
		//Connect RP99 to U1TX
		_RP98R =	0b000001;
		//Init Uart and connect RP104 to U1RX 	
		Init_UART((unsigned int)(FOSC/BAUDRATE/32.0f)-1,99);
	}

        /*Set ports to digital*/
	ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;

        /*Set inputs and outputs*/
	TRISE=0x0000;
        TRISC=0x0000;
	TRISF=0x0000;
	TRISD=0x0000;
	TRISG=0x0000;
        TRISA=0x0000;
        TRISDbits.TRISD1 = 0;   //Output for CAN
        TRISDbits.TRISD2 = 1;   //Input for CAN
	TRISB=0xFFFF;           //Analog inputs

        /*Reset leds*/
        LED0=0;
        LED1=0;

}

void initialisation_CAN(void){

	/*IO settings*/
   	//Inputs (RPINxxbits.registre)
  	_C1RXR = 66;    //RP66 Pin 34

   	//Outputs (RPORxxbits.registre)
  	_RP65R = 0b001110;  //RP65 Pin 33

	init_CAN(CAN_NORMAL,8,4,1,5);

        setup_can_rx();
        setup_can_tx();

        /*Timeout*/
        Init_Timer5(10.0f);
        /*Envoi périodique*/
        Init_Timer4(15.0f);
}

void setup_can_rx(void)
{

	/*configuration du message pour le boutton */
	config_CAN_filter(0, CAN_MSG_BUTTON_CMD_SID , STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_cmd);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le shift */
	config_CAN_filter(1, CAN_MSG_SHIFT_SID , STANDARD_ID);
	receive_CAN_msg(1, 3, fct_can_shift);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);


	/*configuration du message pour le wind direction */
	config_CAN_filter(2,CAN_MSG_WIND_DIRECTION_SID , STANDARD_ID);
	receive_CAN_msg(2, 3, fct_can_wind_direction);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

        /*configuration du message de la requête des dernières valeurs d'automatisation */
	config_CAN_filter(3, CAN_MSG_EEPROM_CONFIG_SEND_SID, STANDARD_ID);
	receive_CAN_msg(3, 3, fct_can_EEPROM_CONFIG_ANSWER);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

        /*configuration du message de la requête des dernières valeurs d'automatisation */
	config_CAN_filter(4, CAN_MSG_CONF_SID, STANDARD_ID);
	receive_CAN_msg(4, 3, fct_can_conf);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

}

void setup_can_tx(void)
{
    /*configuration du message sur la demande des dernières valeurs de gear et de position du mât */
    config_CAN_Tx_msg(&can_msg_EEPROM_ACK, CAN_MSG_EEPROM_CONFIG_ACK_SID , STANDARD_ID, 3);

    /*configuration du message pour la gear actuelle */
    config_CAN_Tx_msg(&can_msg_GEAR, CAN_MSG_GEAR_SID , STANDARD_ID, 3);

    /*configuration du message pour la position du mât */
    config_CAN_Tx_msg(&can_msg_POSITION_MAT, CAN_MSG_TURBINE_DIRECTION_SID , STANDARD_ID, 3);

    // Initialize everything
    chinookpack_fbuffer_init(&buf,canBuffer,8);
    chinookpack_packer_init(&pk,&buf,chinookpack_fbuffer_write);

}

void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[2] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8};
	int old_ipl, tempo=0;
	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,2,&off);
	off = 0;

	RESTORE_CPU_IPL(old_ipl);

        tempo = (int)unpacker.data.via.i64;
        datReceive_can_cmd[0] = tempo & 0b0001;
        datReceive_can_cmd[1] = (tempo & 0b0010)>>1;
        datReceive_can_cmd[2] = (tempo & 0b0100)>>2;
        datReceive_can_cmd[3] = (tempo & 0b1000)>>3;
}
void fct_can_shift(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[2] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,2,&off);
	off = 0;

	RESTORE_CPU_IPL(old_ipl);

        datReceive_can_shift = (char)unpacker.data.via.u64;
}

void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
        //char* DataReceive;
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;

	RESTORE_CPU_IPL(old_ipl);        
        datReceive_can_wind_direction = unpacker.data.via.dec;
}

void fct_can_EEPROM_CONFIG_ANSWER(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
        const char ubReceiveData2[2] = {(recopie->data5 & 0xFF00)>>8,(recopie->data6 & 0x00FF)};
        int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

	off = 0;
        chinookpack_unpack_next(&unpacker,ubReceiveData2,2,&off);
        off=0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;

	RESTORE_CPU_IPL(old_ipl);

        datReceive_can_EEPROM_CONFIG_ANSWER_gear = (char)unpacker.data.via.u64;
        datReceive_can_EEPROM_CONFIG_ANSWER_mat = unpacker.data.via.dec;

}

void fct_can_conf(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[1] = {(recopie->data3 & 0x00FF)};
	int old_ipl;
	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,2,&off);
	off = 0;

	RESTORE_CPU_IPL(old_ipl);

        datReceive_can_conf = (int)unpacker.data.via.i64;
}

void envoi_CAN(int ID)
{
    switch(ID)
    {
        case CAN_MSG_EEPROM_CONFIG_ACK_SID:
            chinookpack_pack_uint8(&pk,EEPROM_REQUEST);
            Set_Timeout();
            send_CAN_msg(&can_msg_EEPROM_ACK,canBuffer, 2);
            while(!is_CAN_msg_send(&can_msg_EEPROM_ACK) && !can_time_out);
            Reset_Timeout();
            // If you need to clear the packer buffer
            chinookpack_fbuffer_clear(&buf);
        break;

        case CAN_MSG_GEAR_SID :
            chinookpack_pack_uint8(&pk,gear);
            Set_Timeout();
            send_CAN_msg(&can_msg_GEAR,canBuffer, 2);
            while(!is_CAN_msg_send(&can_msg_GEAR) && !can_time_out);
            Reset_Timeout();
            // If you need to clear the packer buffer
            chinookpack_fbuffer_clear(&buf);
        break;
        
        case CAN_MSG_TURBINE_DIRECTION_SID :
            chinookpack_pack_float(&pk,Position_mat);
            Set_Timeout();
            send_CAN_msg(&can_msg_POSITION_MAT,canBuffer, 5);
            while(!is_CAN_msg_send(&can_msg_POSITION_MAT) && !can_time_out);
            Reset_Timeout();
            // If you need to clear the paker buffer
            chinookpack_fbuffer_clear(&buf);
        break;
        default:

        break;      
    }

}

char CAN_delai = 0;

void envoi_CAN_periodique(void)
{
    if(CAN_cycle)
    {
        CAN_cycle=0;
        CAN_delai++;
        if(CAN_delai==5)
        {
            CAN_delai = 0;
            envoi_CAN(CAN_MSG_GEAR_SID);
            envoi_CAN(CAN_MSG_TURBINE_DIRECTION_SID);
            EEPROM_REQUEST = 0xAA;
            envoi_CAN(CAN_MSG_EEPROM_CONFIG_ACK_SID);
        }

    }

}

void envoi_CAN_periodique_init(void)
{
    if(CAN_cycle)
    {
        CAN_cycle=0;
        CAN_delai++;
        if(CAN_delai==5)
        {
            CAN_delai = 0;
            envoi_CAN(CAN_MSG_EEPROM_CONFIG_ACK_SID);
        }

    }

}
void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{
	can_time_out = 1;
	_T5IF = 0;
}
void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void)
{
        CAN_cycle = 1;
	_T4IF = 0;
}