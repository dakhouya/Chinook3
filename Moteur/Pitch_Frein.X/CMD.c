//Contient la commande et l'asservissement des moteur
#include "CMD.h"
#include "M_TMR.h"
#include <p33EP256MC502.h>


extern int input;

const float gm1 = 70312.5f;		//(60000000.0F/256.0F)/(200.0f/60.0f);
const float gm2 = 1.0f/32768.0f;


struct Stepper{
	float accel;		//Step / Seconde^2
	float SS_SET;		//Consigne	Step / seconde	
	float SS_CUR;		//Step / seconde
	float Iset;			//Consigne Courant de phases
	float IReadA;		//Lecture du Courant de phaseA
	float IReadB;		//Lecture du Courant de phaseB
	char dir;			//1:Forward 8:Backward
	char NbStep;		//200 Step / rev
	volatile int State;
}Stepper_1;	


/*
void ChangeDir(int dir)
{
	if(dir ==1)
	{
		Stepper_1.dir=8;
	}
	if(dir ==0)
	{
		Stepper_1.dir=1;
	}
}
*/

void RunStepper(void)
{
        Init_Timer3(800.0f);
        Stepper_1.State = 1;
        Stepper_1.dir = 1;
}
//stepcnt à 5200 pour pitch négatif maximum
#define pitch_init
#ifdef pitch_init
unsigned int stepcnt;
unsigned int stepref;
#endif

//#define pitch_raz
#ifdef pitch_raz
unsigned int stepcnt = 0;
unsigned int stepref = 5750;
#endif

//#define pitch_dans_ltape
#ifdef pitch_dans_ltape
unsigned int stepcnt = 5750;
unsigned int stepref = 0;
#endif

void DisableStepper(void)
{
	//disable motor
	Motor_PWM_three_Level(&PWMCON1, 0.0f);
	Motor_PWM_three_Level(&PWMCON2, 0.0f);

}
void UpdateStepper(int dir)
{
	#define DUTY_1  0.50f
	#define DUTY_2	0.25f
	
	if(dir ==1 || dir ==8)
	{
		Stepper_1.dir = dir;
	}
	if(Stepper_1.State >8 || Stepper_1.State <=0)
	{
		Stepper_1.State=Stepper_1.dir;
	}
	//Les phases peuvent contenir la valeur de Duty-Cycle
	switch(Stepper_1.State){
		case -1:		//All OFF
			Motor_PWM_three_Level(&PWMCON1, 0.0f);
			Motor_PWM_three_Level(&PWMCON2, 0.0f);
			/*
			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =0;*/
 	 		break;
		case 1:			//STEP1
			Motor_PWM_three_Level(&PWMCON1, DUTY_1);
			Motor_PWM_three_Level(&PWMCON2, 0.0f);
			/*
			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =0;	
			*/
  			break;
  		case 2:
  			Motor_PWM_three_Level(&PWMCON1, DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, DUTY_2);
			/*
			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B  =1;
			PHASE_NB =0;	*/
  			break;
  		case 3:			//STEP 2
  			Motor_PWM_three_Level(&PWMCON1, 0.0f);
			Motor_PWM_three_Level(&PWMCON2, DUTY_1);
			/*
  			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =1;
			PHASE_NB =0;	*/
  			break;
  		case 4:
  			Motor_PWM_three_Level(&PWMCON1, -DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, DUTY_2);
  			/*
  			PHASE_A	 =0;
  			PHASE_NA =1;
  			PHASE_B	 =1;
			PHASE_NB =0;*/
			break;
		case 5:			//STEP 3
			Motor_PWM_three_Level(&PWMCON1, -DUTY_1);
			Motor_PWM_three_Level(&PWMCON2, 0.0f);
			/*
			PHASE_A	 =0;
			PHASE_NA =1;
			PHASE_B  =0;
			PHASE_NB =0;*/	
  			break;
  		case 6:
  			Motor_PWM_three_Level(&PWMCON1, -DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, -DUTY_2);
			/*
			PHASE_A	 =0;
			PHASE_NA =1;
			PHASE_B  =0;
			PHASE_NB =1;
			*/	
  			break;
  		case 7:			//STEP4
  			Motor_PWM_three_Level(&PWMCON1, 0.0f);
			Motor_PWM_three_Level(&PWMCON2, -DUTY_1);
  			/*
  			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =1;	
			*/
  			break;
  		case 8:
  			Motor_PWM_three_Level(&PWMCON1, DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, -DUTY_2);
  			/*
  			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B	 =0;
			PHASE_NB =1;	
			*/
  		break;
	//default:
  	//break;
	}
	//MDC	= (Stepper_1.State%2)?PTPER>>1:PTPER>>2;	//Duty-Cycle
//#define DEBUG
#ifdef DEBUG
	U1TXREG = Stepper_1.State+'0';
	
	if(PHASE_A	 ==1)
	{
		U1TXREG = 'A';
	}
	if(PHASE_NA	 ==1)
	{
		U1TXREG = 'C';
	}
	if(PHASE_B	 ==1)
	{
		U1TXREG = 'B';
	}
	if(PHASE_NB	 ==1)
	{
		U1TXREG = 'D';
	}
	U1TXREG = 13;
#endif
	if(Stepper_1.dir == 1)
	{
                stepcnt++;
		Stepper_1.State++;	
	}
	else if(Stepper_1.dir == 8)
	{
                stepcnt--;
		Stepper_1.State--;
	}
}

void UpdateStepperLowTorque(int dir)
{
	#define DUTY_1L  0.40f
	#define DUTY_2L	 0.20f
	
	if(dir ==1 || dir ==8)
	{
		Stepper_1.dir = dir;
	}
	if(Stepper_1.State >8 || Stepper_1.State <=0)
	{
		Stepper_1.State=Stepper_1.dir;
	}
	//Les phases peuvent contenir la valeur de Duty-Cycle
	switch(Stepper_1.State){
		case -1:		//All OFF
			Motor_PWM_three_Level(&PWMCON1, 0.0f);
			Motor_PWM_three_Level(&PWMCON2, 0.0f);
			/*
			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =0;*/
 	 		break;
		case 1:			//STEP1
			Motor_PWM_three_Level(&PWMCON1, DUTY_1);
			Motor_PWM_three_Level(&PWMCON2, 0.0f);
			/*
			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =0;	
			*/
  			break;
  		case 2:
  			Motor_PWM_three_Level(&PWMCON1, DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, DUTY_2);
			/*
			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B  =1;
			PHASE_NB =0;	*/
  			break;
  		case 3:			//STEP 2
  			Motor_PWM_three_Level(&PWMCON1, 0.0f);
			Motor_PWM_three_Level(&PWMCON2, DUTY_1);
			/*
  			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =1;
			PHASE_NB =0;	*/
  			break;
  		case 4:
  			Motor_PWM_three_Level(&PWMCON1, -DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, DUTY_2);
  			/*
  			PHASE_A	 =0;
  			PHASE_NA =1;
  			PHASE_B	 =1;
			PHASE_NB =0;*/
			break;
		case 5:			//STEP 3
			Motor_PWM_three_Level(&PWMCON1, -DUTY_1);
			Motor_PWM_three_Level(&PWMCON2, 0.0f);
			/*
			PHASE_A	 =0;
			PHASE_NA =1;
			PHASE_B  =0;
			PHASE_NB =0;*/	
  			break;
  		case 6:
  			Motor_PWM_three_Level(&PWMCON1, -DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, -DUTY_2);
			/*
			PHASE_A	 =0;
			PHASE_NA =1;
			PHASE_B  =0;
			PHASE_NB =1;
			*/	
  			break;
  		case 7:			//STEP4
  			Motor_PWM_three_Level(&PWMCON1, 0.0f);
			Motor_PWM_three_Level(&PWMCON2, -DUTY_1);
  			/*
  			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =1;	
			*/
  			break;
  		case 8:
  			Motor_PWM_three_Level(&PWMCON1, DUTY_2);
			Motor_PWM_three_Level(&PWMCON2, -DUTY_2);
  			/*
  			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B	 =0;
			PHASE_NB =1;	
			*/
  		break;
	//default:
  	//break;
	}
	//MDC	= (Stepper_1.State%2)?PTPER>>1:PTPER>>2;	//Duty-Cycle
//#define DEBUG
#ifdef DEBUG
	U1TXREG = Stepper_1.State+'0';
	
	if(PHASE_A	 ==1)
	{
		U1TXREG = 'A';
	}
	if(PHASE_NA	 ==1)
	{
		U1TXREG = 'C';
	}
	if(PHASE_B	 ==1)
	{
		U1TXREG = 'B';
	}
	if(PHASE_NB	 ==1)
	{
		U1TXREG = 'D';
	}
	U1TXREG = 13;
#endif
	if(Stepper_1.dir == 1)
	{
		Stepper_1.State++;	
	}
	else if(Stepper_1.dir == 8)
	{
		Stepper_1.State--;
	}
}
/*void RPMToCount(int	cmd)
{
	if(cmd==0)
	{
		Stepper_1.dir= 0;	
		Stepper_1.State=-1;
		NF=1;
	}
	else
	{
		Stepper_1.dir= (cmd>0)?1:8;			
		cmd=(cmd>0)?cmd:-1*cmd;
		PR8=(unsigned int)(1.0f/((float)cmd)*gm1);
	}
}*/

unsigned int DutyCycle(float duty)
{
	duty=(duty<0.00001f)?0.0f:((duty>0.9999f)?1.0f:duty);
	return (unsigned int)(PTPER*duty);
}

