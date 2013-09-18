#include "Setup_commande.h"

/******************************************************************
                    Variable, Macro & Const
******************************************************************/

void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_brake(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void initialisation_message_Tx_CAN(void);
void initialisation_message_Rx_CAN(void);
void Delayus(unsigned int delay);
int variation_pitch(float val_pot, unsigned int *Levier_num_cran);

unsigned int compteur =0, bp=0;
int count=0;

unsigned char Can_manual_pitch[8] = {0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57};	//données envoyées pour la variation des pâles
unsigned char Can_brake[8] = {0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47};			//données envoyées pour le brake
unsigned char Can_button_cmd[4] = {0x40,0x41,0x42,0x43};			//données envoyées pour le brake

/*CAN msg*/
T_CAN_Tx_MSG can_msg_manual_pitch;			// message sortant pour commander le pitch variable des pâles
T_CAN_Tx_MSG can_msg_brake;					// message sortant pour commander le frein
T_CAN_Tx_MSG can_msg_button_cmd;			// message sortant pour l'état des boutons du PCB commande


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
	
	int nb_ms, Board_envoie=0, memo_bit_0[4]={0, 0, 0, 0}, memo_bit_1[4]={0, 0, 0, 0};
	unsigned int memo_cran_levier=0;
	float BUFF[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};											// initialise 16 BUFFER
	float OFFSET[16]={0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0};	// ajout d'un offset pour un réglage précis
	int BUFF_val[16]={1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};											// 1 = affichage du buffer

	float Pot_Pitch_Volt=0;				//valeur en volt du potentiomètre pour les pitchs variables 
	unsigned int *Levier_num_cran=5;		//numéro du cran dans lequel se trouve le levier pour le pitch variable

	Setup(); //Initialisation PIC, UART, can,...

	initialisation_CAN();
	initialisation_message_Tx_CAN();
//	initialisation_message_Rx_CAN();	

	while(1)
	{
		Analyse_ADC(BUFF, OFFSET, BUFF_val);							//Analyse les entrées analogiques 
	    Pot_Pitch_Volt = BUFF[0];										//recopie de la valeur du potentiomètre

		if(variation_pitch(Pot_Pitch_Volt, &Levier_num_cran)){			//Envoie du message commande des pitchs variables seulement s'il y a eu un changement de cran sur le levier
			while((count<=TEMPS_MS));									//Délays entre deux messages

			sprintf(Can_manual_pitch, "%f", BUFF[0]);					//Valeur du pot1 à envoyer sur le can	

			send_CAN_msg(&can_msg_manual_pitch, Can_manual_pitch, 8);	// envoie du message Can_manual_pitch
			while(is_CAN_msg_send(&can_msg_manual_pitch) != TRUE);		// test si le message est envoyé

			count=0;													//réinitialise le compteur
		}

		/*détecte si un bouton change et envoie des messages can seulement s'il y a changement sur un bouton*/
		if((!BP1 && !memo_bit_1[0]) || (!BP2 && !memo_bit_1[1]) || (!BP3 && !memo_bit_1[2]) ||(!BP4 && !memo_bit_1[3])){
			if(!BP1) {memo_bit_0[0]=0;memo_bit_1[0]=1;Led1=1;}					//mémorise le bouton 1 comme étant à l'état haut
			if(!BP2) {memo_bit_0[1]=0;memo_bit_1[1]=1;Led2=1;}					//mémorise le bouton 2 comme étant à l'état haut
			if(!BP3) {memo_bit_0[2]=0;memo_bit_1[2]=1;Led3=1;}					//mémorise le bouton 3 comme étant à l'état haut
			if(!BP4) {memo_bit_0[3]=0;memo_bit_1[3]=1;Led4=1;}					//mémorise le bouton 4 comme étant à l'état haut
		
		 	 while((count<=TEMPS_MS));									//Délays entre deux messages
		
			sprintf(Can_button_cmd, "%d%d%d%d",memo_bit_0[3],memo_bit_0[2],memo_bit_0[1],memo_bit_0[0]);		//envoie des données sous forme de quatre bits
			
		
			send_CAN_msg(&can_msg_button_cmd, Can_button_cmd, 4);		//envoie des 4 bits, un pour chaque bouton
			while(is_CAN_msg_send(&can_msg_button_cmd) != TRUE);		// test si le message est envoyé

		    count=0;													//réinitialise le compteur
		
		}
		else if((BP1 && !memo_bit_0[0]) || (BP2 && !memo_bit_0[1]) || (BP3 && !memo_bit_0[2]) ||(BP4 && !memo_bit_0[3])){
			if(BP1) {memo_bit_0[0]=1;memo_bit_1[0]=0;Led1=0;}					//mémorise le bouton 1 comme étant à l'état bas
			if(BP2) {memo_bit_0[1]=1;memo_bit_1[1]=0;Led2=0;}					//mémorise le bouton 2 comme étant à l'état bas
			if(BP3) {memo_bit_0[2]=1;memo_bit_1[2]=0;Led3=0;}					//mémorise le bouton 3 comme étant à l'état bas
			if(BP4) {memo_bit_0[3]=1;memo_bit_1[3]=0;Led4=0;}					//mémorise le bouton 4 comme étant à l'état bas
		
			while((count<=TEMPS_MS));									//Délays entre deux messages
		
			sprintf(Can_button_cmd, "%d%d%d%d",memo_bit_0[3],memo_bit_0[2],memo_bit_0[1],memo_bit_0[0]);		//envoie des données sous forme de quatre bits
		
			send_CAN_msg(&can_msg_button_cmd, Can_button_cmd, 4);		//envoie des 4 bits, un pour chaque bouton
			while(is_CAN_msg_send(&can_msg_button_cmd) != TRUE);		// test si le message est envoyé
			count=0;													//réinitialise le compteur
		
		}


	//Led3=bp;
	
	}//while
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

	bp=(unsigned int)datReceive_can_brake[0];

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
void initialisation_message_Tx_CAN(void){

	/*configuration du message sur le pitch variable */
	config_CAN_Tx_msg(&can_msg_manual_pitch, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID, 3);

	/*configuration du message pour le brake */
	config_CAN_Tx_msg(&can_msg_brake, CAN_MSG_BRAKE_SID , STANDARD_ID, 3);

	/*configuration du message pour les boutons */
	config_CAN_Tx_msg(&can_msg_button_cmd, CAN_MSG_BUTTON_CMD_SID , STANDARD_ID, 3);

}//fonction initialisation_message_Tx_CAN
void initialisation_message_Rx_CAN(void){

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

}//fonction initialisation_message_Rx_CAN
int variation_pitch(float val_pot, unsigned int *Levier_num_cran){
	
	unsigned int memo_num_levier=*Levier_num_cran;									//enregistre le numéro du cran dans lequel se trouve le levier
	float ref_pot=(POT_PITCH_MAX-POT_PITCH_MIN)/LEVIER_PITCH_NB_CRAN;				//variation de tension en fonction du nombre de cran 
	float pot_min, pot_max;
	int count_cran, ii;
	char UART_debug_levier[100]={0x00};								

	for(count_cran=0;count_cran<LEVIER_PITCH_NB_CRAN;count_cran++){
		pot_min=POT_PITCH_MIN+(ref_pot*count_cran);									//calcul de la valeur min de la plage actuelle
		pot_max=POT_PITCH_MIN+(ref_pot*(count_cran+1));								//calcul de la valeur max de la plage actuelle
		if((val_pot>=pot_min) && (val_pot<pot_max))  *Levier_num_cran=count_cran;	//permet de savoir dans quel cran est le levier

	 	if(DEBUG_LEVIER){			//affiche différentes données de débugage
			sprintf(UART_debug_levier,"\n\rVal_pot : %f , Pot_min : %f , Pot_max : %f , cran : %d   \n\r",val_pot,pot_min,pot_max,*Levier_num_cran);
	
			/* Affichage des données du levier */
			for(ii=0;ii<100;ii++){
					U1TXREG=UART_debug_levier[ii];		//envoie de la valeur à afficher
					while(U1STAbits.TRMT == 0);	
					UART_debug_levier[ii]=0x00;					//réinitialise le message à afficher
			}//for ii
		}//if
	}//for count_cran

	if(memo_num_levier==*Levier_num_cran) return 0;		//si le levier n'a pas changé de cran, ne rien envoyer
	else return 1;										//envoyer un message si le levier a changé de cran
}//fonction variation_pitch
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
	if(count<=TEMPS_MS) count++;			//compteur pour laisser un delay entre chaque message
	//Led4^=1;
	IFS0bits.T3IF = 0; 						//Clear Timer3 interrupt flag
}