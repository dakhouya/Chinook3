#include "Setup_commande.h"

/******************************************************************
                    Variable, Macro & Const
******************************************************************/

void fct_can_pitch_orientation(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_brake(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_shift_up(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_shift_down(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
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

unsigned int compteur =0;

char* datReceive_can_brake ;				// les données brutes du message can pour les brakes
char* datReceive_can_manual_pitch ;			// les données brutes du message can pour le pitch variable
char* datReceive_can_cmd;					// les données brutes du message can pour les boutons du pcb commande

/**************************CONSTANTS******************************/
const float PI=3.141592653589793f;
/*****************************************************************/

// Device Configurations registers
_FOSCSEL(FNOSC_FRCPLL); // select fast internal rc with pll
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); // Watchdog timer software enabled

int main(){
	


	Setup(); //Initialisation PIC, UART, can,...

	initialisation_CAN();
	initialisation_message_Rx_CAN();	

	while(1)
	{
	
		
	}


}
void fct_can_pitch_orientation(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can pitch orientation : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[50]={0x00};
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive_can_manual_pitch = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can manual pitch : %c%c%c%c%c%c%c%c   ",compteur++,datReceive_can_manual_pitch[0],datReceive_can_manual_pitch[1],datReceive_can_manual_pitch[2],datReceive_can_manual_pitch[3],datReceive_can_manual_pitch[4],datReceive_can_manual_pitch[5],datReceive_can_manual_pitch[6],datReceive_can_manual_pitch[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_brake(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[50]={0x00};
	int old_ipl, ii, jj;
	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive_can_brake = (char *)data_rx;

	if(DEBUG_MSG_CAN_BRAKE){
		sprintf(UART_can_receive,"\n\r%d : Can brake : %c%c%c%c%c%c%c%c\n\r   ",compteur++,datReceive_can_brake[7],datReceive_can_brake[6],datReceive_can_brake[5],datReceive_can_brake[4],datReceive_can_brake[3],datReceive_can_brake[2],datReceive_can_brake[1],datReceive_can_brake[0]);
	
		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}

	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[50]={0x00};
	int old_ipl, ii, jj;
	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive_can_cmd = (char *)data_rx;
	Led1=datReceive_can_cmd[0];

	if(DEBUG_MSG_CAN_CMD){
		sprintf(UART_can_receive,"\n\r%d : Can commande : %c%c%c%c\n\r   ",compteur++,datReceive_can_cmd[3],datReceive_can_cmd[2],datReceive_can_cmd[1],datReceive_can_cmd[0]);
	
		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}

	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_shift_up(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can shift up : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_shift_down(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can shift down : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_wind_speed(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can wind speed : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can wind direction : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_turbine_rpm_sensor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can turbine rpm sensor : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_turbine_rpm_motor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can turbine rpm motor : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_wheel_rpm(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can wheel rpm : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_trust(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can trust : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_torque(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can torque : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_turbine_direction(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can turbine direction : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_gear(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can gear : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_acceleration(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can acceleration : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_clutch_temperature(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can clutch temperature : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_voltage_monitor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can voltage monitor : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_current_monitor(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can current monitor : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}
void fct_can_time(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data)
{
	char UART_can_receive[100]={0x00};
	char* datReceive;
	int old_ipl, ii, jj;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

 	datReceive = (char *)data_rx;

 	if(DEBUG_MSG_CAN_MANUAL_PITCH){
		sprintf(UART_can_receive,"\n\r%d : Can time : %c%c%c%c%c%c%c%c   ",compteur++,datReceive[0],datReceive[1],datReceive[2],datReceive[3],datReceive[4],datReceive[5],datReceive[6],datReceive[7]);

		/* Affichage des données du can */
		for(ii=0;ii<50;ii++){
				U1TXREG=UART_can_receive[ii];		//envoie de la valeur à afficher
				while(U1STAbits.TRMT == 0);	
				UART_can_receive[ii]=0x00;					//réinitialise le message à afficher
		}
	}
	RESTORE_CPU_IPL(old_ipl);
}


void initialisation_message_Rx_CAN(void){

	/*configuration du message pour le brake */
	config_CAN_filter(3, CAN_MSG_PITCH_ORIENTATION_SID , STANDARD_ID);
	receive_CAN_msg(3, 3, fct_can_cmd);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message sur le pitch variable */
	config_CAN_filter(0, CAN_MSG_MANUAL_PITCH_SID, STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_manual_pitch);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(1, CAN_MSG_BRAKE_SID , STANDARD_ID);
	receive_CAN_msg(1, 3, fct_can_brake);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(2, CAN_MSG_BUTTON_CMD_SID , STANDARD_ID);
	receive_CAN_msg(2, 3, fct_can_cmd);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(4, CAN_MSG_TURBINE_RPM_SENSOR_SID , STANDARD_ID);
	receive_CAN_msg(4, 3, fct_can_turbine_rpm_sensor);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(5, CAN_MSG_WHEEL_RPM_SID , STANDARD_ID);
	receive_CAN_msg(5, 3, fct_can_wheel_rpm);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(6, CAN_MSG_WIND_SPEED_SID , STANDARD_ID);
	receive_CAN_msg(6, 3, fct_can_wind_speed);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(7, CAN_MSG_WIND_DIRECTION_SID , STANDARD_ID);
	receive_CAN_msg(7, 3, fct_can_wind_direction);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(8, CAN_MSG_TRUST_SID , STANDARD_ID);
	receive_CAN_msg(8, 3, fct_can_trust);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(9, CAN_MSG_VOLTAGE_MONITOR_SID , STANDARD_ID);
	receive_CAN_msg(9, 3, fct_can_voltage_monitor);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour le brake */
	config_CAN_filter(10, CAN_MSG_CURRENT_MONITOR_SID , STANDARD_ID);
	receive_CAN_msg(10, 3, fct_can_current_monitor);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);


}//fonction initialisation_message_Rx_CAN

