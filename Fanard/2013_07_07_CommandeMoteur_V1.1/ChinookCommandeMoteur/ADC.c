#include "ADC.h"

void init_ADC()
{
	/* initialisation ADC 										     */	
	ANSELBbits.ANSB4 = 1;	// AN4/RB4 est une entrée analogique
	ANSELBbits.ANSB1 = 0;	// AN1/RB1 est une entrée analogique
	
	/* Initialisation des registres */
	AD1CON1 = 0x0000; 
	AD1CON2 = 0x0000; 
	AD1CON3 = 0x0000; 
	AD1CON4 = 0x0000; 
	AD2CON4 = 0x0000;
	AD1CHS123 = 0x0000; 
	
	AD1CSSH = 0x0000;
	AD1CSSL = 0x0000;
	
	/* Initialisation conversion */
	AD1CON1bits.FORM = 0b00;	// Conversion de 0 à 1024
	AD1CON2bits.VCFG = 0b000;	// VREFH = AVDD et VREFL = AVSS
	AD1CON1bits.AD12B = 0;		// mode 10 bits
	AD1CON1bits.SSRC = 0b111;	//conversion automatique
	AD1CON1bits.SSRCG = 0;


	/* assigne les MUX */
	AD1CON1bits.SIMSAM = 0; // Pour le simultané
	AD1CON1bits.SAMP = 0; // Pour le scan manuel
	AD1CON1bits.ASAM = 1; // Conversion automatique
	AD1CON2bits.ALTS = 1; // pour switcher entre le MUXA et le MUXB
	AD1CON4bits.ADDMAEN = 0; // désactive DMA pour le mode ADC
	AD1CON2bits.CSCNA = 0; // ne pas scanner les entrées du channel CH0 pendant l'échantillonnage du MUXA
	
	/* assigne le temps d'échantillonage (sample) */
	AD1CON3bits.SAMC = 0b00010; // 2 * TAD
	AD1CON3bits.ADCS = 0b1111111; // TSMP = SAMC * TAD
	AD1CON3bits.ADRC = 0; // choix de la clock Fcy=FOSC/2 (50Mhz)
	
	AD1CON2bits.CHPS = 0b00; // convertir seulement le channel 0
	

	AD1CSSL = 0x000F;	// sélectionne les entrées à scanner (ici les 16 entrées sont scannées)

	/* assigne les BUFF */
	AD1CON2bits.BUFM = 1; // utilise 16 buff
	AD1CON2bits.SMPI = 0b00111; // BUF0-7==>MUXA et  BUF8-F==>MUXB
	
	/* assigne MUXA pour CH0*/
	AD1CHS0bits.CH0SA = 4; // Choix de la pin MUXA
	AD1CHS0bits.CH0NA = 0; // référence pour le channel CHO est VREFL du MUXA
	
	/* assigne MUXB pour CH0*/
	AD1CHS0bits.CH0SB = 1; // Choix de la pin MUXB
	AD1CHS0bits.CH0NB = 0; // référence pour le channel CHO est VREFL du MUXB
	
	/* assigne CH1, CH2 et CH3 pour MUXA*/
	AD1CHS123bits.CH123SA = 0; // N/A car on utilise seulement le channel 0 CHO
	AD1CHS123bits.CH123NA = 0; // N/A car on utilise seulement le channel 0 CHO
	
	/* assigne CH1, CH2 et CH3 pour MUXB*/
	AD1CHS123bits.CH123SB = 0; // N/A car on utilise seulement le channel 0 CHO
	AD1CHS123bits.CH123NB = 0; // N/A car on utilise seulement le channel 0 CHO
	
	AD1CON1bits.ADON = 1;	//activ le mode ADC
}

void Analyse_ADC(float *BUFF,float OFFSET[16],int BUFF_val[16])
{
	char print_BUFF_tab[16][80]={"0B","1B","2D","3F","4H","5J","6L","7N","8P","9R","AT","BV","CX","DZ","EB","FD"};
	float temporaire[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int count, count_car; 

/* Addition de NB_ANALYSE par BUFFER */
	for(count=0;count<NB_ANALYSE;count++){

		if(BUFF_val[0]) BUFF[0]=(float)ADC1BUF0+BUFF[0];			//ANA1
		if(BUFF_val[1]) BUFF[1]=(float)ADC1BUF1+BUFF[1];			//ANA4
		if(BUFF_val[2]) BUFF[2]=(float)ADC1BUF2+BUFF[2];			//ANA1
		if(BUFF_val[3]) BUFF[3]=(float)ADC1BUF3+BUFF[3];			//ANA4
		if(BUFF_val[4]) BUFF[4]=(float)ADC1BUF4+BUFF[4];			//ANA1
		if(BUFF_val[5]) BUFF[5]=(float)ADC1BUF5+BUFF[5];			//ANA4
		if(BUFF_val[6]) BUFF[6]=(float)ADC1BUF6+BUFF[6];			//ANA1
		if(BUFF_val[7]) BUFF[7]=(float)ADC1BUF7+BUFF[7];			//ANA4
		if(BUFF_val[8]) BUFF[8]=(float)ADC1BUF8+BUFF[8];			//ANA1
		if(BUFF_val[9]) BUFF[9]=(float)ADC1BUF9+BUFF[9];			//ANA4
		if(BUFF_val[10]) BUFF[10]=(float)ADC1BUFA+BUFF[10];			//ANA1
		if(BUFF_val[11]) BUFF[11]=(float)ADC1BUFB+BUFF[11];			//ANA4
		if(BUFF_val[12]) BUFF[12]=(float)ADC1BUFC+BUFF[12];			//ANA1
		if(BUFF_val[13]) BUFF[13]=(float)ADC1BUFD+BUFF[13];			//ANA4
		if(BUFF_val[14]) BUFF[14]=(float)ADC1BUFE+BUFF[14];			//ANA1
		if(BUFF_val[15]) BUFF[15]=(float)ADC1BUFF+BUFF[15];			//ANA4
	}//for

/*  échelle de conversion : 0 à 1024 ==> 0v à 3.3v  */
	for(count=0;count<NB_BUFF;count++)
		if(BUFF_val[count]) BUFF[count]=(ADC_VOLTAGE*(BUFF[count]/NB_ANALYSE)/G_ADC)+OFFSET[count];

/**************************************DEBBUGAGE******************************************************/
/* Afficher les valeurs avec l'UART */
	if(DEBUG_ADC){
	/* Retour à la ligne  */
			U1TXREG = '\n';
			while(U1STAbits.TRMT == 0);
			U1TXREG = '\r';
			while(U1STAbits.TRMT == 0);
			U1TXREG = '\n';
			while(U1STAbits.TRMT == 0);
			U1TXREG = '\r';
			while(U1STAbits.TRMT == 0);
	
	/* Convertion de la valeur d'un buffer en char  */
		for(count=0;count<NB_BUFF;count++)
			if(BUFF_val[count]) sprintf(print_BUFF_tab[count],"BUFF%c : %f   ",print_BUFF_tab[count][0],BUFF[count]);
	
	/* Affichage des valeurs de buffer  */
		for(count=0;count<NB_BUFF;count++){
			for(count_car=0;count_car<NB_CAR_AFF;count_car++){
				/* BUFF_val permet la sélection des buffer à afficher, cf initialisation de cette variable */
				if(BUFF_val[count]){
					U1TXREG=print_BUFF_tab[count][count_car];		//envoie de la valeur à afficher
					while(U1STAbits.TRMT == 0);					//attente, valeur est bien envoyée
				}
			}//for
			if(count==NB_BUFF/2){
				U1TXREG = '\n';
				while(U1STAbits.TRMT == 0);
				U1TXREG = '\r';
				while(U1STAbits.TRMT == 0);
			}//if
	
		}//for
	}
/*******************************************************************************************************/
}