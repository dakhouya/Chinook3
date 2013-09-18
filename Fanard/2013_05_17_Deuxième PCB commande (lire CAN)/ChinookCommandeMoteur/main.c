#include "Setup_commande.h"

/******************************************************************
                    Variable, Macro & Const
******************************************************************/

void fct_can_pitch_orientation(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_brake(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_shift(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_wind_speed(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_turbine_rpm_sensor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_turbine_rpm_motor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_wheel_rpm(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_trust(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_torque(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_turbine_direction(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_gear(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_acceleration(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_clutch_temperature(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_voltage_monitor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_current_monitor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_time(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);

void initialisation_message_Rx_CAN(void);
float decodeur_can(T_CAN_RX message_rx);

unsigned int compteur =0;

T_CAN_RX datReceive_can_brake ;				// les données brutes du message can pour les brakes
T_CAN_RX datReceive_can_manual_pitch ;			// les données brutes du message can pour le pitch variable
T_CAN_RX datReceive_can_cmd;					// les données brutes du message can pour les boutons du pcb commande

/**************************CONSTANTS******************************/
const float PI=3.141592653589793f;
/*****************************************************************/


int main(){
	
	char UART_can_receive[100]="fuck!!!";
	int ii;
	T_CAN_RX essai;
	Setup(); //Initialisation PIC, UART, can,...

	initialisation_CAN();
	initialisation_message_Rx_CAN();	

//	initialisation_UART();

	while(1)
	{
	//	Led3=BP3;
	//	Nop();
		essai=datReceive_can_cmd;
		Nop();
		if(decodeur_can(essai)==1) Led1=1;
		else Led1=0;
		Nop();
		if(datReceive_can_cmd.nb_data==1) Led3=1;
		else Led3=0;

	}


}
void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[50]={0x00};
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive_can_manual_pitch.datReceive = (char *)data_rx;
 	datReceive_can_manual_pitch.nb_data = (int)nbr_data -48;


	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_brake(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[50]={0x00};
	int old_ipl, ii, jj;
	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive_can_brake.datReceive = (char *)data_rx;
 	datReceive_can_brake.nb_data = (char *)data_rx;

	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[50]={0x00};
	int old_ipl, ii, jj;
	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive_can_cmd.datReceive = (char *)data_rx;
 	datReceive_can_cmd.nb_data = (unsigned int)nbr_data;

	RESTORE_CPU_IPL(old_ipl);
}

void initialisation_message_Rx_CAN(void){

	if(DEBUG_MSG_PITCH_ORIENTATION){
		/*configuration du message pour le brake */
		config_CAN_filter(3, CAN_MSG_PITCH_ORIENTATION_SID , STANDARD_ID);
		receive_CAN_msg(3, 3, fct_can_pitch_orientation);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_MANUAL_PITCH){
		/*configuration du message sur le pitch variable */
		config_CAN_filter(0, CAN_MSG_MANUAL_PITCH_SID, STANDARD_ID);
		receive_CAN_msg(0, 3, fct_can_manual_pitch);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_BRAKE){
		/*configuration du message pour le brake */
		config_CAN_filter(1, CAN_MSG_BRAKE_SID , STANDARD_ID);
		receive_CAN_msg(1, 3, fct_can_brake);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_BUTTON_CMD){
		/*configuration du message pour le bouton commande */
		config_CAN_filter(2, CAN_MSG_BUTTON_CMD_SID , STANDARD_ID);
		receive_CAN_msg(2, 3, fct_can_cmd);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_TURBINE_RPM_SENSOR){
		config_CAN_filter(4, CAN_MSG_TURBINE_RPM_SENSOR_SID , STANDARD_ID);
		receive_CAN_msg(4, 3, fct_can_turbine_rpm_sensor);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_WHEEL_RPM){
		config_CAN_filter(5, CAN_MSG_WHEEL_RPM_SID , STANDARD_ID);
		receive_CAN_msg(5, 3, fct_can_wheel_rpm);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_WIND_SPEED){
		config_CAN_filter(6, CAN_MSG_WIND_SPEED_SID , STANDARD_ID);
		receive_CAN_msg(6, 3, fct_can_wind_speed);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_WIND_DIRECTION){
		config_CAN_filter(7, CAN_MSG_WIND_DIRECTION_SID , STANDARD_ID);
		receive_CAN_msg(7, 3, fct_can_wind_direction);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_TRUST){
		config_CAN_filter(8, CAN_MSG_TRUST_SID , STANDARD_ID);
		receive_CAN_msg(8, 3, fct_can_trust);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_VOLTAGE_MONITOR){
		config_CAN_filter(9, CAN_MSG_VOLTAGE_MONITOR_SID , STANDARD_ID);
		receive_CAN_msg(9, 3, fct_can_voltage_monitor);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}
	if(DEBUG_MSG_CURRENT_MONITOR){
		config_CAN_filter(10, CAN_MSG_CURRENT_MONITOR_SID , STANDARD_ID);
		receive_CAN_msg(10, 3, fct_can_current_monitor);
		//config_CAN_mask(0, 2.0f, STANDARD_ID);
	}

}//fonction initialisation_message_Rx_CAN
float decodeur_can(T_CAN_RX message_rx){
	int compteur_data=0, div_10=0;
	float convert_data=0, valeur=0;

	for(compteur_data=0;compteur_data<message_rx.nb_data;compteur_data++){
		if(message_rx.datReceive[message_rx.nb_data-compteur_data]=='.' && !compteur_data)
			valeur/=div_10;
		else
			convert_data=(float)(message_rx.datReceive[message_rx.nb_data-compteur_data]-48);
		valeur += convert_data;
		div_10+=10;
	}//for
	return convert_data;//convert_data;
}//fonction decodeur_can

