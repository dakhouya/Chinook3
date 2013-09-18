/************************************************************/
/* as1107.c                                                 */
/* Functions related LED drivers and 7 segments displays    */
/*															*/
/* MCU : dspic33EP512MC806									*/
/*                                                          */
/* Author : Mikael Ducharme                                 */
/* Date	  : June 2013                                     	*/
/************************************************************/
/**********************    INCLUDE    ***********************/
#include "as1107.h"
/************************************************************/

extern int config;

void resetGrammant(void){
	if(config == 9){
	as1107_reset();
	config = 0;
	TMR7 = 0;
	}

}	



void as1107_decode_speed_count(void){
	int k;
	float test = 0.0002f;
	for(k=0; k<=9999; k++){
	float j;
	for(j=0;j<=12000; j++){
	Nop();
	}
	as1107_decode_speed(test);
	test = test + 0.1f;
	}	
}
void as1107_decode_speed(float speed){		
	if((speed >= 0.0f)&&(speed<=99.99f))
	{
		int temp;
		char a[4] = {0};
		speed = speed * 100;
		speed = speed + 0.5f;
		temp = (int)speed;
		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;
	
		as1107_write_u1(dig3,	a[3]);
		as1107_write_u1(dig2,	a[2]);
		as1107_write_u1(dig1,	0x80|a[1]);
		as1107_write_u1(dig0,	a[0]);

	}
	else;
}

void as1107_decode_gear(int gear){		
	if((gear > 0)&&(gear <= 14))
	{
		int temp = gear;
		int a[2] = {0};
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;
	
		as1107_write_u1(dig5,	a[1]);
		as1107_write_u1(dig4,	a[0]);

	}
	else;
}

void as1107_decode_rpm(float rpm){		
	if((rpm >= 0)&&(rpm<=4000))
	{
		int temp;
		int a[4] = {0};
		rpm += 0.5f;
		temp = (int)rpm;
		a[3] = temp % 10;
		temp = (temp - a[3]) / 10;
		a[2] = temp % 10;
		temp = (temp - a[2]) / 10;
		a[1] = temp % 10;
		temp = (temp - a[1]) / 10;
		a[0] = temp % 10;
	
		as1107_write_u2(dig3,	a[3]);
		as1107_write_u2(dig2,	a[2]);
		as1107_write_u2(dig1,	a[1]);
		as1107_write_u2(dig0,	a[0]);

	}
	else;
}



void as1107_write_u1(int reg,int data){
		
		int old_ipl;

		load=0;
		while(SPI2STATbits.SPITBF == 1);
		SET_AND_SAVE_CPU_IPL(old_ipl, 7);
		SPI2BUF = (reg<<8)|data;
		while(SPI2STATbits.SPITBF == 1);
		load=1;
		RESTORE_CPU_IPL(old_ipl);
		int i = 0;
		for (i = 0; i == 10; i++){}
		load=0;			
}

void as1107_init(void){
	
		as1107_write_u1(shutdown,	0x00);
		as1107_write_u1(feature, 	0x02);
		as1107_write_u1(feature, 	0x00);
		as1107_write_u1(disptest, 	0x00);
		as1107_write_u1(scanlimit, 	0x05);
		as1107_write_u1(intensity, 	0x0F);
		as1107_write_u1(decodemode, 0xFF);
		as1107_write_u1(shutdown,	0x81);
		delay300us();
		int e;
		for(e=1;e<=7;e++){
			as1107_write_u1(e,		0x00);
		}	

		as1107_write_u2(shutdown,	0x00);
		as1107_write_u2(feature, 	0x02);
		as1107_write_u2(feature, 	0x00);
		as1107_write_u2(disptest, 	0x00);
		as1107_write_u2(scanlimit, 	0x05);
		as1107_write_u2(intensity, 	0x0F);
		as1107_write_u2(decodemode, 0xFF);
		as1107_write_u2(shutdown,	0x81);
		delay300us();
		int f;
		for(f=1;f<=5;f++){
			as1107_write_u2(f,		0x00);
		}			
		
}

void as1107_reset(void){
	
		as1107_write_u1(shutdown,	0x00);
		as1107_write_u1(feature, 	0x02);
		as1107_write_u1(feature, 	0x00);
		as1107_write_u1(disptest, 	0x00);
		as1107_write_u1(scanlimit, 	0x05);
		as1107_write_u1(intensity, 	0x0F);
		as1107_write_u1(decodemode, 0xFF);
		as1107_write_u1(shutdown,	0x81);
		delay300us();	

		as1107_write_u2(shutdown,	0x00);
		as1107_write_u2(feature, 	0x02);
		as1107_write_u2(feature, 	0x00);
		as1107_write_u2(disptest, 	0x00);
		as1107_write_u2(scanlimit, 	0x05);
		as1107_write_u2(intensity, 	0x0F);
		as1107_write_u2(decodemode, 0xFF);
		as1107_write_u2(shutdown,	0x81);
		delay300us();
					
		
}

void as1107_write_u2(int reg,int data){
		
		int old_ipl;
	


		load3=0;
		while(SPI3STATbits.SPITBF == 1);
		SET_AND_SAVE_CPU_IPL(old_ipl, 7);
		SPI3BUF = (reg<<8)|data;
		while(SPI3STATbits.SPITBF == 1);
		load3=1;
		RESTORE_CPU_IPL(old_ipl);
		int i = 0;
		for (i = 0; i == 10; i++){}
		load3=0;			
}
