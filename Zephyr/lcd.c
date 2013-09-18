/************************************************************/
/* lcd.c                                                   	*/
/* Functions related to the LCD display			            */
/*															*/
/* MCU 		: dspic33EP512MC806								*/
/* Display 	: NHD-0420D3Z-NSW-BBW-V3                        */
/* Author 	: Mikael Ducharme                               */
/* Date	  	: June 2013                                    	*/
/************************************************************/

/**********************    INCLUDE    ***********************/
#include "lcd.h"
#include <math.h>
/************************************************************/

float calcul_PercentToDegree(float percent){
	float degree;
/*
y = 0.4528x - 11.27
x c'est le pourcentage
y c'est le pitch
*/

degree = 0.4528f*percent -11.27f; 

	return degree;
}

/*
Vent relatif	Angle	%		RPM cible
6				11.2	52.30	300-400
7				11.2	52.30	300-400
8				11.2	52.30	300-400
9				11.2	52.30	400
10				11.2	52.30	400-500
11				10.2	54.55	500
12				9.2		56.79	500-600
13				9.2		56.79	600
14				9.2		56.79	600-700
15				8.2		59.04	700
16				7.2		61.29	700-800
17				6.2		63.54	800
18				5.2		65.78	800-900
19				5.2		65.78	900
20				5.2		65.78	900-1000
*/
 
 
target_s calcTarget(float windSpeed){
	int s = 0;
	target_s t;
 
	s = (int) windSpeed;
	switch(s){
		case 6:
			t.pitch=52.30;t.rpm=350.0f;
			break;
		case 7:
			t.pitch=52.30;t.rpm=350.0f;
			break;
		case 8:
			t.pitch=52.30;t.rpm=350.0f;
			break;
		case 9:
			t.pitch=52.30;t.rpm=400.0f;
			break;
		case 10:
			t.pitch=52.30;t.rpm=450.0f;
			break;
		case 11:
			t.pitch=54.55;t.rpm=500.0f;
			break;	
		case 12:
			t.pitch=56.79;t.rpm=550.0f;
			break;
		case 13:
			t.pitch=56.79;t.rpm=600.0f;
			break;
		case 14:
			t.pitch=56.79;t.rpm=650.0f;
			break;
		case 15:
			t.pitch=59.04;t.rpm=700.0f;
			break;
		case 16:
			t.pitch=61.29;t.rpm=750.0f;
			break;
		case 17:
			t.pitch=63.54;t.rpm=800.0f;
			break;
		case 18:
			t.pitch=65.78;t.rpm=850.0f;
			break;
		case 19:
			t.pitch=65.78;t.rpm=900.0f;
			break;
		case 20:
			t.pitch=65.78;t.rpm=950.0f;
			break;
		default:
			t.pitch=0;
			t.rpm=0;
 
	}
	return t;
}

float calcul_TSR(float windspeed, float turbineRPM){
	float TSR;
	if(windspeed != 0){
		TSR = (turbineRPM * (3.1415926536f/30) * (1.79f/2))/windspeed;
	}
	else{
		TSR = 0;
	}
	return TSR;	
}

float calcul_vitesseEff(float wheelRPM, float windspeed){
	float vitesse;
	float vitesseEff;
 
	if(windspeed != 0){

	vitesse = wheelRPM*0.049207813f;
	vitesseEff = vitesse/windspeed;
	}

	else{
	vitesseEff = 0;
	}
	
	return vitesseEff*100;
}

float calcul_RPMratio(int gear, float wheelRPM, float turbineRPM){
	int staticRatio = 3;
	float rolhoffRatio;
	float turbineRPMtheoric;		
	float RPMratio;

	switch(gear){
		case 1:
			rolhoffRatio = 0.279;
			break;
		case 2:
			rolhoffRatio = 0.316;
			break;
		case 3:
			rolhoffRatio = 0.360;
			break;
		case 4:
			rolhoffRatio = 0.409;
			break;
		case 5:
			rolhoffRatio = 0.464;
			break;
		case 6:
			rolhoffRatio = 0.528;
			break;
		case 7:
			rolhoffRatio = 0.6;
			break;
		case 8:
			rolhoffRatio = 0.682;
			break;
		case 9:
			rolhoffRatio = 0.774;
			break;
		case 10:
			rolhoffRatio = 0.881;
			break;
		case 11:
			rolhoffRatio = 1.0;
			break;
		case 12:
			rolhoffRatio = 1.135;
			break;
		case 13:
			rolhoffRatio = 1.292;
			break;
		case 14:
			rolhoffRatio = 1.467;
			break;
		}
	turbineRPMtheoric = wheelRPM*staticRatio*(1/rolhoffRatio);
	
	if(turbineRPM != 0){
		RPMratio = turbineRPMtheoric/turbineRPM;
	}
	else{
		RPMratio = 0;
	}
	return RPMratio*100;
}


void LCD_displayWindSpeed(float wsr){
	if((wsr >= 0.00f)&&(wsr <= 99.9f))
	{
		int temp;
		char a[3] = {0};
		float wsrTampered;

		wsrTampered = (wsr * 10) + 0.5f;
		temp = (int)wsrTampered;
		
		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = '.';
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

		a[3] += 48;
		a[1] += 48;
		a[0] += 48;
						
		LCD_setCursor(line3char14);
		delay600us();
		LCD_writeString(&a, 4);
	}
	else;
}

void LCD_displayTargetRPM(float spd){
	if((spd >= 0.00f)&&(spd <= 3000.00f))
	{
		int temp;
		char a[3] = {0};
		float spdTampered;

		spdTampered = spd + 0.5f;
		temp = (int)spdTampered;

		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

		a[3] += 48;
		a[2] += 48;
		a[1] += 48;
		a[0] += 48;



		LCD_setCursor(line1char5);
		delay600us();
		LCD_writeString(&a, 4);


	}
	else;
}



void LCD_displayTargetPitch(float pitch){
	if((pitch >= -20.0f)&&(pitch <= 40.0f))
	{
		int temp;
		char a[5] = {0};
		float pitchTampered;

		if(pitch < 0){
			a[0] = '-';
			pitchTampered = (pitch * 10) - 0.5f;
			temp = (int)pitchTampered;
			temp *= -1;
		}
		else{
			a[0] = '+';
			pitchTampered = (pitch * 10) + 0.5f;
			temp = (int)pitchTampered;
		}

		


		a[4] = temp % 10;
		temp = (temp - a[4]) / 10;
		a[3] = '.';
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;	

		a[4] += 48;
		a[2] += 48;
		a[1] += 48;
				
		LCD_setCursor(line3char4);
		delay600us();
		LCD_writeString(&a, 5);
		
		
	}
	else;



}

void LCD_displayWindSpeedRatio(float wsr){
	if((wsr >= 0.00f)&&(wsr <= 99.9f))
	{
		int temp;
		char a[3] = {0};
		float wsrTampered;

		wsrTampered = (wsr * 10) + 0.5f;
		temp = (int)wsrTampered;
		
		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = '.';
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

		a[3] += 48;
		a[1] += 48;
		a[0] += 48;
						
		LCD_setCursor(line4char5);
		delay600us();
		LCD_writeString(&a, 4);
	}
	else;
}

void LCD_displayRPMRatio(float rpm){
	if((rpm >= 000.0f)&&(rpm <= 400.0f))
	{
		int temp;
		char a[5] = {0};
		float rpmTampered;

		rpmTampered = (rpm * 10) + 0.5f;
		temp = (int)rpmTampered;
		
		a[4] = temp % 10;
		temp = (temp - a[4]) / 10;
		a[3] = '.';
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

		a[4] += 48;
		a[2] += 48;
		a[1] += 48;
		a[0] += 48;
						
		LCD_setCursor(line3char15);
		delay600us();
		LCD_writeString(&a, 5);
	}
	else;
}

void LCD_displayTipSpeedRatio(float tsr){
	if((tsr >= 0.00f)&&(tsr <= 25.00f))
	{
		int temp;
		char a[4] = {0};
		float tsrTampered;

		tsrTampered = (tsr * 100) + 0.5f;
		temp = (int)tsrTampered;
		
		a[4] = temp % 10;
		temp = (temp - a[4]) / 10;
		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = '.';
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

		a[4] += 48;
		a[3] += 48;
		a[1] += 48;
		a[0] += 48;
				
		
		
		LCD_setCursor(line2char16);
		delay600us();
		LCD_writeString(&a, 5);
		
		
	}
	else;
}

void LCD_displayGear(int spd){
	if((spd >= 1)&&(spd <= 14))
	{
		int temp;
		char a[1] = {0};

		temp = spd;

		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

        a[1] += 48;
		a[0] += 48;



		LCD_setCursor(line4char9);
		delay600us();
		LCD_writeString(&a, 2);


	}
	else;
}

void LCD_displaySpeedKMH(float spd){
	if((spd >= 0.00f)&&(spd <= 50.00f))
	{
		int temp;
		char a[4] = {0};
		float spdTampered;

		spdTampered = (spd * 100) + 0.5f;
		temp = (int)spdTampered;

		a[4] = temp % 10;
		temp = (temp - a[4]) / 10;
		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = '.';
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

		a[4] += 48;
		a[3] += 48;
		a[1] += 48;
		a[0] += 48;



		LCD_setCursor(line4char10);
		delay600us();
		LCD_writeString(&a, 5);


	}
	else;
}

void LCD_displayRPM(float spd){
	if((spd >= 0.00f)&&(spd <= 3000.00f))
	{
		int temp;
		char a[3] = {0};
		float spdTampered;

		spdTampered = spd + 0.5f;
		temp = (int)spdTampered;

		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;

		a[3] += 48;
		a[2] += 48;
		a[1] += 48;
		a[0] += 48;



		LCD_setCursor(line4char17);
		delay600us();
		LCD_writeString(&a, 4);


	}
	else;
}


void LCD_displayRelWindDir(float rlwd){
	if((rlwd >= -180.0f)&&(rlwd <= 180.0f))
	{
		int temp;
		char a[6] = {0};
		float rlwdTampered;

		if(rlwd < 0){
			a[0] = '-';
			rlwdTampered = (rlwd * 10) - 0.5f;
			temp = (int)rlwdTampered;
			temp *= -1;
		}
		else{
			a[0] = '+';
			rlwdTampered = (rlwd * 10) + 0.5f;
			temp = (int)rlwdTampered;
		}

		


		a[5] = temp % 10;
		temp = (temp - a[5]) / 10;
		a[4] = '.';
		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;	

		a[5] += 48;
		a[3] += 48;
		a[2] += 48;
		a[1] += 48;
				
		
		
		LCD_setCursor(line1char14);
		delay600us();
		LCD_writeString(&a, 6);
		
		
	}
	else;


}


void LCD_displayPitch(float pitch){
	if((pitch >= -20.0f)&&(pitch <= 40.0f))
	{
		int temp;
		char a[5] = {0};
		float pitchTampered;

		if(pitch < 0){
			a[0] = '-';
			pitchTampered = (pitch * 10) - 0.5f;
			temp = (int)pitchTampered;
			temp *= -1;
		}
		else{
			a[0] = '+';
			pitchTampered = (pitch * 10) + 0.5f;
			temp = (int)pitchTampered;
		}

		


		a[4] = temp % 10;
		temp = (temp - a[4]) / 10;
		a[3] = '.';
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;	

		a[4] += 48;
		a[2] += 48;
		a[1] += 48;
				
		LCD_setCursor(line2char4);
		delay600us();
		LCD_writeString(&a, 5);
		
		
	}
	else;



}

void LCD_displaySetup(void){
	LCD_setCursor(line1char1);
	LCD_writeString("TGR:0000 RWD:+000.0", 19);
	LCD_write(0xDF);
	delay300us();
	
	LCD_setCursor(line2char1);
	LCD_writeString("PCH+00.0 TIPSP:00.00", 20);

	LCD_setCursor(line3char1);
	LCD_writeString("TGP+00.0 WND:00.0m/s", 20);
	delay300us();

	LCD_setCursor(line4char1);
	LCD_writeString("WSR:00.0 00.00  0000", 20);
	
}


void LCD_init(int backlight, int contrast){
	
	LCD_displayON();
	
	LCD_setBacklight(backlight);
	LCD_setContrast(contrast);

	LCD_cursorHome();
	LCD_clearScreen();
	
}

void LCD_writeString(char string[], int stringLength){
	int i = 0;
	for(i=0; i < stringLength; i++){
		LCD_write(string[i]);
	}
}


void LCD_write(int data1){
	int old_ipl;
		
	CS=0;
	while(SPI1STATbits.SRMPT == 0);
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	SPI1BUF = data1;
	while(SPI1STATbits.SRMPT == 0);
	CS=1;
	RESTORE_CPU_IPL(old_ipl);
	delay300us();		
}

void LCD_displayON(void){
	LCD_write(0xFE);
	LCD_write(0x41);
	delay300us();
}

void LCD_displayOFF(void){
	LCD_write(0xFE);
	LCD_write(0x42);
	delay300us();
}

void LCD_setCursor(int position){
	LCD_write(0xFE);
	LCD_write(0x45);
	LCD_write(position);
	delay300us();	
}

void LCD_cursorHome(void){
	LCD_write(0xFE);
	LCD_write(0x46);
	delay600us();
	delay600us();
	delay600us();
}

void LCD_cursorLeft(void){
	LCD_write(0xFE);
	LCD_write(0x49);
	delay300us();
}

void LCD_cursorRight(void){
	LCD_write(0xFE);
	LCD_write(0x4A);
	delay300us();
}

void LCD_backspace(void){
	LCD_write(0xFE);
	LCD_write(0x4E);
	delay300us();
}

void LCD_clearScreen(void){
	LCD_write(0xFE);
	LCD_write(0x51);
	delay600us();
	delay600us();
	delay600us();
}

void LCD_setContrast(int contrast){
	LCD_write(0xFE);
	LCD_write(0x52);
	LCD_write(contrast);
	delay300us();
	delay300us();	
}

void LCD_setBacklight(int backlight){
	LCD_write(0xFE);
	LCD_write(0x53);
	LCD_write(backlight);
	delay300us();	
}