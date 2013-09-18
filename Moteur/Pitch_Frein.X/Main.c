/*
Propriété du 
Club Chinook ETS
*/
/******************************************************************
					Main.c
******************************************************************/



// DSPIC33EP256MC502 Configuration Bit Settings

#include <p33EP256MC502.h>

 int FICD __attribute__((space(prog), address(0x2AFF0))) = 0xFFCF ;
//_FICD(
//    ICS_PGD1 &           // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
//    JTAGEN_OFF           // JTAG Enable bit (JTAG is disabled)
//);
 int FPOR __attribute__((space(prog), address(0x2AFF2))) = 0xFFFF ;
//_FPOR(
//    ALTI2C1_OFF &        // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
//    ALTI2C2_OFF &        // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
//    WDTWIN_WIN25         // Watchdog Window Select bits (WDT Window is 25% of WDT period)
//);
 int FWDT __attribute__((space(prog), address(0x2AFF4))) = 0xFF7F ;
//_FWDT(
//    WDTPOST_PS32768 &    // Watchdog Timer Postscaler bits (1:32,768)
//    WDTPRE_PR128 &       // Watchdog Timer Prescaler bit (1:128)
//    PLLKEN_ON &          // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
//    WINDIS_OFF &         // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
//    FWDTEN_OFF           // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)
//);
 int FOSC __attribute__((space(prog), address(0x2AFF6))) = 0xFFDF ;
//_FOSC(
//    POSCMD_NONE &        // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
//    OSCIOFNC_OFF &       // OSC2 Pin Function bit (OSC2 is clock output)
//    IOL1WAY_OFF &        // Peripheral pin select configuration (Allow multiple reconfigurations)
//    FCKSM_CSECMD         // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)
//);
 int FOSCSEL __attribute__((space(prog), address(0x2AFF8))) = 0xFF39 ;
//_FOSCSEL(
//    FNOSC_FRCPLL &       // Oscillator Source Selection (Fast RC Oscillator with divide-by-N with PLL module (FRCPLL))
//    PWMLOCK_ON &         // PWM Lock Enable bit (Certain PWM registers may only be written after key sequence)
//    IESO_ON              // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)
//);
 int FGS __attribute__((space(prog), address(0x2AFFA))) = 0xFFFF ;
//_FGS(
//    GWRP_OFF &           // General Segment Write-Protect bit (General Segment may be written)
//    GCP_OFF              // General Segment Code-Protect bit (General Segment Code protect is Disabled)
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
				
******************************************************************/
int COMMANDE = 0;
int delai = 0;
/******************************************************************
				Includes
******************************************************************/
#include "Global.h"
#include "CMD.h"
#include "can.h"
#include "dma.h"
#include "can_chinook3.h"
#include "M_UART.h"
#include "M_TMR.h"
#include "M_PWM.h"
#include <stdio.h>
#include "chinookpack.h"

/******************************************************************
                    Variable, Macro & Const
******************************************************************/
#define NB_TOURS_PITCH_MAX  13
#define STEP_COUNT_MAX  400*NB_TOURS_PITCH_MAX //200 Step * 2(Halfstep) = 400 Step par tour

extern volatile char can_time_out;
/*CAN variables*/
T_CAN_Tx_MSG CAN_MSG_PITCH_ACK;
/*Encoder*/
int8_t bTxCanBuffer[5]={0x55,5,3,8,9};
char canBuffer[8]; //Buffer that contain the encoded data
chinookpack_fbuffer buf;
chinookpack_packer pk;
chinookpack_unpacked unpacker;
unsigned int off = 0; //offset to read more than 1 msg in 1 packet
void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_manual_pitch_config(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);

float CanPitchPosition = 110.0f;
float CanPitchConfig = 110.0f;
volatile char NF=0;
volatile char CAN_delai = 0;
volatile char CAN_cycle = 0;
unsigned char InitialState = 0;
extern unsigned int stepcnt;
extern unsigned int stepref;
unsigned int Pitch_config =0;
int i=0;
int j=0;

/******************************************************************
                            CAN
******************************************************************/

/****************************************************************
                            Prototype
******************************************************************/
void set_clk(void);
void InitIO(void);
void initialisation_CAN(void);
void envoi_CAN(int ID);
void envoi_CAN_periodique(void);

/******************************************************************
                                Main
******************************************************************/
int main(void)
{
        /*Disable watchdog*/
        RCONbits.SWDTEN = 0;
        
	set_clk();

	InitIO();

        _TRISB6 = 0;   //Output for CAN
        _TRISB7 = 1;   //Input for CAN

        /*IO settings*/
        //Inputs (RPINxxbits.registre)
        _C1RXR = 39;    //RP39 Pin 16

        //Outputs (RPORxxbits.registre)
        _RP38R = 0b001110;  //RP38 Pin 15

        //Initialize CAN communication
        init_CAN(CAN_NORMAL, 8, 1, 0, 5);
	chinookpack_unpacked_init(&unpacker);
        config_CAN_Tx_msg(&CAN_MSG_PITCH_ACK,CAN_MSG_PITCH_ACK_CONFIG,STANDARD_ID,3);
        chinookpack_fbuffer_init(&buf,canBuffer,8);
        chinookpack_packer_init(&pk,&buf,chinookpack_fbuffer_write);
        /*CAN receive fct config*/
        config_CAN_filter(0, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_manual_pitch);
        config_CAN_filter(1, CAN_MSG_PITCH_CONFIG_SEND , STANDARD_ID);
	receive_CAN_msg(1, 3, fct_can_manual_pitch_config);

	/*Frein*/
        Init_Timer1(10.0f);
        Init_Timer5(10.0f);
        
        do{
            if(CAN_cycle){
                CAN_cycle=0;
                i++;
            }
        }while(i<30);

        do{
            Pitch_config = 0x55;
            envoi_CAN_periodique();
        }while(CanPitchConfig > 100.0f);
        stepcnt = (unsigned int)(5650.0f*((100.0f-CanPitchConfig)*0.01f));
        stepref=stepcnt;
        do{
            Pitch_config = 0x34;
            envoi_CAN_periodique();
        }while(j<15);
        Init_PWM();
        RunStepper();
	while(1)
	{
            /*Pitch de l'éolienne*/
            if(NF){
                
                if(CanPitchPosition >= 0.0f && CanPitchPosition <= 100.0f){
                    stepref = (unsigned int)(5650.0f*((100.0f-CanPitchPosition)*0.01f));
                }
                if(stepref!=stepcnt)
                {
                    if(stepref >= stepcnt)
                    {
                            UpdateStepper(PITCH_NEG);
                    }
                    else
                    {
                            UpdateStepper(PITCH_POS);
                    }
                }
                else if(stepref==stepcnt){
                    DisableStepper();
                }
                NF=0;
            }


	}
}
/******************************************************************
			Functions
******************************************************************/
void set_clk(void)
{					//datasheet section 7 p.21
_PLLPRE=0;
_PLLPOST=0;
_PLLDIV=(unsigned int) (4.0f*100.0f/(7.37f))-1;
//_PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;

while(OSCCONbits.LOCK !=1);
}


void InitIO(void)
{
    ANSELB = 0x0000;
    TRISB = 0x0000;

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
        CanPitchPosition = (unpacker.data.via.dec);
}
void fct_can_manual_pitch_config(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        CanPitchConfig = unpacker.data.via.dec;
}


void envoi_CAN(int ID)
{
    switch(ID)
    {
        case CAN_MSG_PITCH_ACK_CONFIG:
            chinookpack_pack_uint8(&pk,Pitch_config);
            Set_Timeout();
            send_CAN_msg(&CAN_MSG_PITCH_ACK,canBuffer, 2);
            while(!is_CAN_msg_send(&CAN_MSG_PITCH_ACK) && !can_time_out);
            Reset_Timeout();
            // If you need to clear the packer buffer
            chinookpack_fbuffer_clear(&buf);
        break;
        default:

        break;
    }

}
void envoi_CAN_periodique(void)
{
    if(CAN_cycle)
    {
        CAN_cycle=0;
        CAN_delai++;
        j++;
        if(CAN_delai==5)
        {
            CAN_delai = 0;
            envoi_CAN(CAN_MSG_PITCH_ACK_CONFIG);
        }

    }

}
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
        CAN_cycle = 1;
	_T1IF = 0;
}
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
        NF = 1;
	_T3IF = 0;
}
