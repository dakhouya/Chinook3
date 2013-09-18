/**********************    INCLUDE    ***********************/
#include "shift.h"
#include "chinookpack.h"
/************************************************************/

extern char bTxCanBuffer[8];
extern chinookpack_fbuffer buf;
extern chinookpack_packer pk;
//volatile extern config;

unsigned char Can_shift[8] = {0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57}; //données envoyées pour la variation des pâles
T_CAN_Tx_MSG can_msg_shift;
T_CAN_Tx_MSG can_msg_conf;

int memo_bit_0[2]={0, 0}, memo_bit_1[2]={0, 0};

void init_shiftButtons(void){
	_TRISE7 = 1; 	//BUT_L is input (SHIFTUP)
        Nop();
	_TRISE6 = 1;	//BUT_R is input (SHIFTDWN)
}

/*void modeConfig(void){
	while(!SHIFTUP && !SHIFTDWN){
		if(!T7CONbits.TON){
			T7CONbits.TON = 1;
		}
		if(config == 3){
			//ENVOIE DU MESSAGE CAN
			chinookpack_pack_uint8(&pk,1);
			Set_Timeout();
			send_CAN_msg(&can_msg_conf, bTxCanBuffer, 2);		//envoie des 4 bits, un pour chaque bouton
			while(is_CAN_msg_send(&can_msg_conf) != TRUE);		// test si le message est envoyé
			Reset_Timeout();
			chinookpack_fbuffer_clear(&buf);
		}	
	}
	if(config >= 3){
			chinookpack_pack_uint8(&pk,0);
			Set_Timeout();
			send_CAN_msg(&can_msg_conf, bTxCanBuffer, 2);		//envoie des 4 bits, un pour chaque bouton
			while(is_CAN_msg_send(&can_msg_conf) != TRUE);		// test si le message est envoyé
			Reset_Timeout();
			chinookpack_fbuffer_clear(&buf);
	}
	T7CONbits.TON = 0;
	config = 0;
	TMR7 = 0;

}
*/

//memorisation du bouton :****************************************************************************************************
void memButtons(void){

	if((!SHIFTUP && !memo_bit_1[0]) || (!SHIFTDWN && !memo_bit_1[1])){
		if(!SHIFTUP) {memo_bit_0[0]=0;memo_bit_1[0]=1;_LATD10=1;}					//mémorise le bouton 1 comme étant à l'état haut
		if(!SHIFTDWN) {memo_bit_0[1]=0;memo_bit_1[1]=1;_LATD9=1;}					//mémorise le bouton 2 comme étant à l'état haut
	
			chinookpack_pack_uint8(&pk,memo_bit_1[0]|memo_bit_1[1]<<1);
			Set_Timeout();
			send_CAN_msg(&can_msg_shift, bTxCanBuffer, 2);		//envoie des 4 bits, un pour chaque bouton
			while(is_CAN_msg_send(&can_msg_shift) != TRUE);		// test si le message est envoyé
			Reset_Timeout();
			chinookpack_fbuffer_clear(&buf);
	}
	else if((SHIFTUP && !memo_bit_0[0]) || (SHIFTDWN && !memo_bit_0[1])){
		if(SHIFTUP) {memo_bit_0[0]=1;memo_bit_1[0]=0;_LATD10=0;}					//mémorise le bouton 1 comme étant à l'état bas
		if(SHIFTDWN) {memo_bit_0[1]=1;memo_bit_1[1]=0;_LATD9=0;}					//mémorise le bouton 2 comme étant à l'état bas
		
			chinookpack_pack_uint8(&pk,memo_bit_1[0]|memo_bit_1[1]<<1);
			Set_Timeout();
			send_CAN_msg(&can_msg_shift, bTxCanBuffer, 2);		//envoie des 4 bits, un pour chaque bouton
			while(is_CAN_msg_send(&can_msg_shift) != TRUE);		// test si le message est envoyé
			Reset_Timeout();
			chinookpack_fbuffer_clear(&buf);
		
	}
}