#include "Setup_commande.h"
#include "chinookpack.h"

/******************************************************************
                    Prototypes des fonctions
******************************************************************/
void fct_can_manual_pitch(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_brake(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, const void * data_rx, char nbr_data);
void initialisation_message_Tx_CAN(void);
void initialisation_message_Rx_CAN(void);
void Delayus(unsigned int delay);
int variation_pitch(float val_pot, unsigned int *Levier_num_cran);


/******************************************************************
                    Variables globales pour le main.c
******************************************************************/
/*messages CAN en transmission Tx*/
T_CAN_Tx_MSG can_msg_manual_pitch;			// message sortant pour commander le pitch variable des pâles
T_CAN_Tx_MSG can_msg_brake;					// message sortant pour commander le frein
T_CAN_Tx_MSG can_msg_button_cmd;			// message sortant pour l'état des boutons du PCB commande

/*messages CAN encodeur*/
char dataArray[8];													//valeur à envoyer
chinookpack_fbuffer buf;											//création de la variable de buffer
chinookpack_packer pk;												//création du pack du message (type et data)

// Device Configurations registers
_FOSCSEL(FNOSC_FRCPLL); // select fast internal rc with pll
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); // Watchdog timer software enabled
volatile unsigned char can_time_out=0;

int main(){
	
	int memo_bit_0[4]={0, 0, 0, 0}, memo_bit_1[4]={0, 0, 0, 0};			//Utilisé pour détecter les fronts (up/down) des boutons
	unsigned int memo_cran_levier=0;									//Mémorise dans quel cran se trouve le levier 	

	/* Paramète d'affichage de l'ADC du pitch variable */
	float BUFF[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};											// initialise 16 BUFFER
	float OFFSET[16]={0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0,0.005f,0};	// ajout d'un offset pour un réglage précis
	int BUFF_val[16]={1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};											// 1 = affichage du buffer

	float Pot_Pitch_Volt=0;					//valeur en volt du potentiomètre pour les pitchs variables 
	unsigned int *Levier_num_cran=0;		//numéro du cran dans lequel se trouve le levier pour le pitch variable

	Setup(); //Initialisation PIC, UART,...

	/* initialisation de l'encodeur et can*/
	initialisation_CAN();
	initialisation_message_Tx_CAN();
	chinookpack_fbuffer_init(&buf, dataArray, 8);						//initialisation des buffer
	chinookpack_packer_init(&pk, &buf, chinookpack_fbuffer_write);		//initialisation du pack pour le message

    Init_Timer3(TIMER3_FREQ);											//CAN timeout timer

	while(1)
	{
		Analyse_ADC(BUFF, OFFSET, BUFF_val);							//Analyse les entrées analogiques 
	    Pot_Pitch_Volt = BUFF[0];										//recopie de la valeur du potentiomètre

		if(variation_pitch(Pot_Pitch_Volt, &Levier_num_cran)){			//Envoie du message commande des pitchs variables seulement s'il y a eu un changement de cran sur le levier

			chinookpack_pack_uint8(&pk, Levier_num_cran);

			Set_Timeout();
			send_CAN_msg(&can_msg_manual_pitch, dataArray, 2);							// envoie du message Can_manual_pitch
			while(is_CAN_msg_send(&can_msg_manual_pitch) != TRUE && !can_time_out);		// test si le message est envoyé
            Reset_Timeout();
			
		}
		chinookpack_fbuffer_clear(&buf);

		/*détecte si un bouton change et envoie des messages can seulement s'il y a changement sur un bouton*/
		if((!BP1 && !memo_bit_1[0]) || (!BP2 && !memo_bit_1[1]) || (!BP3 && !memo_bit_1[2]) ||(!BP4 && !memo_bit_1[3])){
			if(!BP1) {memo_bit_0[0]=0;memo_bit_1[0]=1;Led1=1;Nop();}					// mémorise le bouton 1 comme étant à l'état haut
			if(!BP2) {memo_bit_0[1]=0;memo_bit_1[1]=1;Led2=1;Nop();}					// mémorise le bouton 2 comme étant à l'état haut
			if(!BP3) {memo_bit_0[2]=0;memo_bit_1[2]=1;Led3=1;Nop();}					// mémorise le bouton 3 comme étant à l'état haut
			if(!BP4) {memo_bit_0[3]=0;memo_bit_1[3]=1;Led4=1;Nop();}					// mémorise le bouton 4 comme étant à l'état haut
		
			chinookpack_pack_uint8(&pk,(memo_bit_0[3]<<3)|(memo_bit_0[2]<<2)|(memo_bit_0[1]<<1)|(memo_bit_0[0])); 	//concatène les quatre boutons
			Set_Timeout();
			send_CAN_msg(&can_msg_button_cmd, dataArray, 2);							// Envoie du message CAN des boutons
			while(is_CAN_msg_send(&can_msg_button_cmd) != TRUE && !can_time_out);		// test si le message est envoyé
          	Reset_Timeout();
		    
		}
		else if((BP1 && !memo_bit_0[0]) || (BP2 && !memo_bit_0[1]) || (BP3 && !memo_bit_0[2]) ||(BP4 && !memo_bit_0[3])){
			if(BP1) {memo_bit_0[0]=1;memo_bit_1[0]=0;Led1=0;Nop();}						// mémorise le bouton 1 comme étant à l'état bas
			if(BP2) {memo_bit_0[1]=1;memo_bit_1[1]=0;Led2=0;Nop();}						// mémorise le bouton 2 comme étant à l'état bas
			if(BP3) {memo_bit_0[2]=1;memo_bit_1[2]=0;Led3=0;Nop();}						// mémorise le bouton 3 comme étant à l'état bas
			if(BP4) {memo_bit_0[3]=1;memo_bit_1[3]=0;Led4=0;Nop();}						// mémorise le bouton 4 comme étant à l'état bas
		
			chinookpack_pack_uint8(&pk,(memo_bit_0[3]<<3)|(memo_bit_0[2]<<2)|(memo_bit_0[1]<<1)|(memo_bit_0[0])); 	//concatène les quatre boutons	
			Set_Timeout();
			send_CAN_msg(&can_msg_button_cmd, dataArray, 2);							// Envoie du message CAN des boutons
			while(is_CAN_msg_send(&can_msg_button_cmd) != TRUE && !can_time_out);		// test si le message est envoyé
         	Reset_Timeout();			
		}
		chinookpack_fbuffer_clear(&buf);											// vide le buffer pour le pack de l'encodeur message can
	}//while	
}
/**********************************************************************************************/
	/*Initialise les messages can en transmission

	Entrée :
			- N/A
	Sortie :
			- N/A

	Message CAN :
			- CAN_MSG_MANUAL_PITCH : envoie la valeur du cran dans lequel se trouve le bras
				=> nb bytes : 2, (data 1 : type, data 0 : valeur)
				=> Range : nombre de cran sur le levier (0 à 14)
				=> Type : entier non signé 
			- CAN_MSG_BUTTON_CMD : envoie la valeur des quatre boutons
				=> nb bytes : 2, (data 1 : type, data 0 : sur 4 bits LSB)
				=> Range : bit3 = S4 bit2 = S3 bit1 = S2 bit0 = S1
				=> Type : entier non signé */
/**********************************************************************************************/
void initialisation_message_Tx_CAN(void){

	/*configuration du message sur le pitch variable */
	config_CAN_Tx_msg(&can_msg_manual_pitch, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID, 3);

	/*configuration du message pour le brake */
	config_CAN_Tx_msg(&can_msg_brake, CAN_MSG_BRAKE_SID , STANDARD_ID, 3);

	/*configuration du message pour les boutons */
	config_CAN_Tx_msg(&can_msg_button_cmd, CAN_MSG_BUTTON_CMD_SID , STANDARD_ID, 3);

}//fonction initialisation_message_Tx_CAN

/**********************************************************************************************/
	/*Donne le numéro du cran où se trouve le levier et indique si le cran a changé

	Entrée :
			- val_pot => vaeur du potentiomètre en V.
			- Levier_num_cran => donne la valeur du cran actuel
	Sortie :
			- Retourne 1 si le cran à changé, 0 s'il n'a pas changé
			- Levier_num_cran => retourne par pointeur la valeur du cran*/
/**********************************************************************************************/
int variation_pitch(float val_pot, unsigned int *Levier_num_cran){
	
	unsigned int memo_num_levier=*Levier_num_cran;									//enregistre le numéro du cran dans lequel se trouve le levier
	float ref_pot=(POT_PITCH_MAX-POT_PITCH_MIN)/LEVIER_PITCH_NB_CRAN;				//variation de tension en fonction du nombre de cran 
	float pot_min, pot_max;
	int count_cran;							

	for(count_cran=0;count_cran<LEVIER_PITCH_NB_CRAN;count_cran++){
		pot_min=POT_PITCH_MIN+(ref_pot*count_cran);									//calcul de la valeur min de la plage actuelle
		pot_max=POT_PITCH_MIN+(ref_pot*(count_cran+1));								//calcul de la valeur max de la plage actuelle
		if((val_pot>=pot_min) && (val_pot<pot_max))  *Levier_num_cran=count_cran;	//permet de savoir dans quel cran est le levier
	}//for count_cran

	if(memo_num_levier==*Levier_num_cran) return 0;		//si le levier n'a pas changé de cran, ne rien envoyer
	else return 1;										//envoyer un message si le levier a changé de cran
}//fonction variation_pitch
