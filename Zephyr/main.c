/************************************************************/
/* main.c                                                   */
/* Main application for Zephyr display board	            */
/*															*/
/* MCU : dspic33EP512MC806									*/
/*                                                          */
/* Author : Mikael Ducharme                                 */
/* Date	  : June 2013                                     	*/
/************************************************************/

/**********************    INCLUDE    ***********************/
#include "dma.h"
#include "can.h"
#include "can_chinook3.h"
#include "M_TMR.h"
#include "lcd.h"
#include "p33EP512MC806.h"
#include "global.h"
#include "spi.h"
#include "as1107.h"
#include "shift.h"
#include "chinookpack.h"
/************************************************************/

/******************   GLOBAL VARIABLES   ********************/
extern volatile unsigned char print;
unsigned char datReceive_can_cmd;
float datReceive_can_pitch_orientation = 0.0f;
float datReceive_can_wind_speed = 0.0f;
float datReceive_can_wind_direction = 0.0f;
float datReceive_can_turbine_rpm_motor = 0.0f;
float datReceive_can_wheel_rpm = 0.0f;
float datReceive_can_turbine_direction = 0.0f;
unsigned char datReceive_can_gear = 0;
float datReceive_can_voltage_monitor = 0.0f;

char bTxCanBuffer[8];
chinookpack_fbuffer buf;
chinookpack_packer pk;
chinookpack_unpacked unpacker; //Will contain the unpacked data
unsigned int off = 0; //offset to read more than 1 msg in 1 packet

extern unsigned char Can_shift[8]; //from shift.c
extern T_CAN_Tx_MSG can_msg_shift; //from shift.c
extern T_CAN_Tx_MSG can_msg_conf;  //from shift.c
extern int memo_bit_0[2], memo_bit_1[2];
/************************************************************/

/********************    PROTOTYPES    **********************/
void initRX(void);
void initialisation_message_Tx_CAN(void);
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_pitch_orientation(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_wind_speed(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, int nbr_data);
void fct_can_turbine_rpm_motor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_wheel_rpm(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_turbine_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_gear(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_voltage_monitor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
/************************************************************/

/*Configuration bits*/
_FOSCSEL(FNOSC_FRCPLL); // select fast internal rc with pll
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); // Watchdog timer software enabled

void main(){			//Start of main()
	
	set_clk();

	/*Disable watchdog*/
	RCONbits.SWDTEN = 0;

	_TRISD11 = 0;
	_LATD11 = 1;

	_TRISD10 = 0;
	_LATD10 = 0;	

	_TRISD9 = 0;
	_LATD9 = 0;	

	spi_init_as1107_u1();
	spi_init_as1107_u2();
	spi_init_lcd();
	as1107_init();
	LCD_init(8,40);
	LCD_displaySetup();
	Init_Timer3(10.0f);			//TIMEOUT
	Init_Timer5(10.0f);			//RECEPTION PERIODIQUE
	Init_Timer7(1.0f);			//MODE CONFIG

	ANSELE=0x0000;
	
	// Initialize can encoder & encoder
	chinookpack_fbuffer_init(&buf,bTxCanBuffer,8);
	chinookpack_packer_init(&pk,&buf,chinookpack_fbuffer_write);
	chinookpack_unpacked_init(&unpacker);
        
	init_CAN(CAN_NORMAL, 8, 0, 1, 7);
	initRX();
	initialisation_message_Tx_CAN();
	init_shiftButtons();
	
	float RPMratio;
	float vitesseEff;
	float TSR;
	target_s target;
        
	ANSELE=0x0000;
	
	while(1){			//START of while(1)
		if(print){
			//modeConfig();
			//as1107_decode_speed_count();

			
			if((_RE7==0) || (_RE6==0)){
				as1107_reset();
			}

			resetGrammant();
			
			if(datReceive_can_wind_speed < 6){
				LCD_setCursor(line1char5);
				delay600us();
				LCD_writeString("----", 4);

				LCD_setCursor(line3char4);
				delay600us();
				LCD_writeString(":--.-", 5);
			}
			else{
				target = calcTarget(datReceive_can_wind_speed);
				LCD_displayTargetRPM(target.rpm);
				float targetPitch = calcul_PercentToDegree(target.pitch);
				LCD_displayTargetPitch(targetPitch);
			}
		
			as1107_decode_speed(datReceive_can_wheel_rpm*0.049207813f*3.6f);
			LCD_displaySpeedKMH(datReceive_can_wheel_rpm*0.049207813f*3.6f);

			as1107_decode_rpm(datReceive_can_turbine_rpm_motor);
			LCD_displayRPM(datReceive_can_turbine_rpm_motor);
		
			as1107_decode_gear(datReceive_can_gear);
			//LCD_displayGear(datReceive_can_gear);
		
			float pitchDegree = calcul_PercentToDegree(datReceive_can_pitch_orientation);
			LCD_displayPitch(pitchDegree);
		
			LCD_displayRelWindDir(datReceive_can_wind_direction-datReceive_can_turbine_direction);
		
			TSR = calcul_TSR(datReceive_can_wind_speed, datReceive_can_turbine_rpm_motor);
			LCD_displayTipSpeedRatio(TSR);
		
			//RPMratio = calcul_RPMratio(datReceive_can_gear,datReceive_can_wheel_rpm,datReceive_can_turbine_rpm_motor);
			//LCD_displayRPMRatio(RPMratio);
			LCD_displayWindSpeed(datReceive_can_wind_speed);
			
			vitesseEff = calcul_vitesseEff(datReceive_can_wheel_rpm, datReceive_can_wind_speed);
			LCD_displayWindSpeedRatio(vitesseEff);
		
			print = 0;
		}
		
		memButtons();
	}					//END of while(1)
}						//END of main()



/*********************    INIT RX    ************************/
void initRX(void){

	/*configuration du message pour les commandes */
	config_CAN_filter(0, CAN_MSG_BUTTON_CMD_SID , STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_cmd);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour l'orientation du pitch */
	config_CAN_filter(1, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID);
	receive_CAN_msg(1, 3, fct_can_pitch_orientation);
	//config_CAN_mask(1, 2.0f, STANDARD_ID);

	/*configuration du message pour la vitesse du vent */
	config_CAN_filter(2, CAN_MSG_WIND_SPEED_SID , STANDARD_ID);
	receive_CAN_msg(2, 3, fct_can_wind_speed);
	//config_CAN_mask(2, 2.0f, STANDARD_ID);

	/*configuration du message pour la direction du vent */
	config_CAN_filter(3, CAN_MSG_WIND_DIRECTION_SID , STANDARD_ID);
	receive_CAN_msg(3, 3, fct_can_wind_direction);
	//config_CAN_mask(3, 2.0f, STANDARD_ID);

	/*configuration du message pour le RPM Moteur */
	config_CAN_filter(5, CAN_MSG_TURBINE_RPM_SENSOR_SID , STANDARD_ID);
	receive_CAN_msg(5, 3, fct_can_turbine_rpm_motor);
	//config_CAN_mask(5, 2.0f, STANDARD_ID);

	/*configuration du message pour le RPM Roues */
	config_CAN_filter(6, CAN_MSG_WHEEL_RPM_SID , STANDARD_ID);
	receive_CAN_msg(6, 3, fct_can_wheel_rpm);
	//config_CAN_mask(6, 2.0f, STANDARD_ID);

	/*configuration du message pour la direction de l'eolienne */
	config_CAN_filter(7, CAN_MSG_TURBINE_DIRECTION_SID , STANDARD_ID);
	receive_CAN_msg(7, 3, fct_can_turbine_direction);
	//config_CAN_mask(7, 2.0f, STANDARD_ID);

	/*configuration du message pour le gear */
	config_CAN_filter(8, CAN_MSG_GEAR_SID , STANDARD_ID);
	receive_CAN_msg(8, 3, fct_can_gear);
	//config_CAN_mask(8, 2.0f, STANDARD_ID);

	/*configuration du message pour le voltage */
	config_CAN_filter(9, CAN_MSG_VOLTAGE_MONITOR_SID , STANDARD_ID);
	receive_CAN_msg(9, 3, fct_can_voltage_monitor);
	//config_CAN_mask(9, 2.0f, STANDARD_ID);
}
/************************************************************/

/*********************    TX FUNC    ************************/
void initialisation_message_Tx_CAN(void){

	/*configuration du message sur le pitch variable */
	config_CAN_Tx_msg(&can_msg_shift, CAN_MSG_SHIFT_SID , STANDARD_ID, 3);

	/*configuration du message sur le mode config */
	config_CAN_Tx_msg(&can_msg_conf, CAN_MSG_CONF_SID , STANDARD_ID, 3);

}//fonction initialisation_message_Tx_CAN
/************************************************************/

/*********************    RX FUNC    ************************/
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_pitch_orientation(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_pitch_orientation = unpacker.data.via.dec;
}
void fct_can_wind_speed(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_wind_speed = unpacker.data.via.dec;
}
//volatile void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID,T_CAN_DATA recopie, int nbr_data)
void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, int nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_wind_direction = unpacker.data.via.dec;

}
void fct_can_turbine_rpm_motor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_turbine_rpm_motor = unpacker.data.via.dec;
}
void fct_can_wheel_rpm(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_wheel_rpm = unpacker.data.via.dec;
}
void fct_can_turbine_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_turbine_direction = unpacker.data.via.dec;
}
void fct_can_gear(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[2] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,2,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_gear = (unsigned char)unpacker.data.via.u64;
}
void fct_can_voltage_monitor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        datReceive_can_voltage_monitor =(float)unpacker.data.via.dec;

}
/************************************************************/
