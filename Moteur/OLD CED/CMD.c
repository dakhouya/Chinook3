//Contient la commande et l'asservissement des moteur
#include "CMD.h"
char NF;

extern int input;

const float gm1 = (40e6/256.0f)/(200.0f/15.0f);		//(60000000.0F/256.0F)/(200.0f/60.0f)/4;
const float gm2 = 1.0f/32768.0f;

float DUTY_1 = -0.9f;
float DUTY_2 = -0.9f;

long int stp_cnt =0;


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

#define DIR_UP 1
#define DIR_DOWN 8


void SpeedStep(float tmp)
{
    //tmp en vitesse  max 200RPM
            if(tmp<0.0f)
            {
                tmp = tmp*-1.0f;
                Stepper_1.dir= 1;
            }
            else
            {
                Stepper_1.dir= 8;
            }

        //Minimum speed 10 RPM
        if(tmp > 0.01f)
        {
            //S'assurer que le timer est d�marr�
        T8CON=0;
	T8CONbits.TCKPS =0b11;	//1:256
        TMR8=0;
            PR8=(unsigned int)(75.0f/tmp);
            //0.65 � -1.0  | tmp =(1 � 0)
            DUTY_1 = 1.5f*tmp-1.0f;
            DUTY_2 = 1.2f*tmp-1.0f;
        T8CONbits.TON=1;
       }
       else
       {
       	//réduit la commande des PWM (donc le courant)
       	//Arrête le timer pendant que la commande est très petite
       	   TMR8=0;
       	   DUTY_1 = -0.95f;
       	   DUTY_2 = -0.95f;
       	   T8CONbits.TON=0;
       }
}
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
void StartSTEP(unsigned int TMR_RPM)
{
	T8CON=0;
	T8CONbits.TCKPS =0b11;	//1:256
        TMR8=0;
	PR8=TMR_RPM;
	_T8IF=0;
	//_T8IE=1;
	//_T8IP=4;
	T8CONbits.TON=1;		//Start Timer
}

void StopSTEP(void)
{
    T8CONbits.TON=0;
    Motor_PWM_two_Level(&PWMC, -1.0f);
    Motor_PWM_two_Level(&PWME, -1.0f);
    Motor_PWM_two_Level(&PWMD, -1.0f);
    Motor_PWM_two_Level(&PWMF, -1.0f);
}

void RunStepper(float accel, float RPM, int state)
{
	_TRISE0 =0;
	_TRISE1 =0;
	_TRISE2 =0;
	_TRISE3 =0;
	
	_RE0=0;
	_RE1=0;
	_RE2=0;
	_RE3=0;
	
	Stepper_1.accel=	accel;
	
	Stepper_1.SS_SET=	RPM*GM1;
	Stepper_1.SS_CUR=	0;
	
	Stepper_1.NbStep=	200;
	
	if(RPM>0.0f)
	{
		Stepper_1.dir  =	1;
	}
	else
	{
		Stepper_1.dir  =	8;
	}	
	//Enable IO
	//

	Stepper_1.State=	state;
	
	//Changer timer pour 32bit -> meilleure pr�cision � bas r�gime
	//Pulses aux 305 minutes � pulses � 234khz (585 RPM) pour f_CPU=60MHz
	T8CON=0;
	T8CONbits.TCKPS =0b11;	//1:256
	PR8=1000;
	_T8IF=0;
	//_T8IE=1;
	//_T8IP=4;
	T8CONbits.TON=1;		//Start Timer
}

void UpdateStepper(float torque)
{
#define STEP_A      PWMC
#define STEP_NA     PWME
#define STEP_B      PWMD
#define STEP_NB     PWMF
	if(Stepper_1.State >8 || Stepper_1.State <=0)
	{
		Stepper_1.State=Stepper_1.dir;
	}
	//Les phases peuvent contenir la valeur de Duty-Cycle
	switch(Stepper_1.State){
		case -1:		//All OFF
			//Motor_PWM_three_Level(&PWMCON1, 0.0f);
			//Motor_PWM_three_Level(&PWMCON2, 0.0f);
                            Motor_PWM_two_Level(&STEP_A, -1.0f);
                            Motor_PWM_two_Level(&STEP_NA, -1.0f);
                            Motor_PWM_two_Level(&STEP_B, -1.0f);
                            Motor_PWM_two_Level(&STEP_NB, -1.0f);
                            return;
			/*
			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =0;*/
 	 		break;
		case 1:			//STEP1
			//Motor_PWM_three_Level(&PWMCON1, DUTY_1);
			//Motor_PWM_three_Level(&PWMCON2, 0.0f);
                            Motor_PWM_two_Level(&STEP_A, DUTY_1+torque);
                            Motor_PWM_two_Level(&STEP_NA, -1.0f);
                            Motor_PWM_two_Level(&STEP_B, -1.0f);
                            Motor_PWM_two_Level(&STEP_NB, -1.0f);
			/*
			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =0;	
			*/
  			break;
  		case 2:
  			//Motor_PWM_three_Level(&PWMCON1, DUTY_2);
			//Motor_PWM_three_Level(&PWMCON2, DUTY_2);
                            Motor_PWM_two_Level(&STEP_A, DUTY_2+torque);
                            Motor_PWM_two_Level(&STEP_NA, -1.0f);
                            Motor_PWM_two_Level(&STEP_B, DUTY_2+torque);
                            Motor_PWM_two_Level(&STEP_NB, -1.0f);
			/*
			PHASE_A	 =1;
			PHASE_NA =0;
			PHASE_B  =1;
			PHASE_NB =0;	*/
  			break;
  		case 3:			//STEP 2
  			//Motor_PWM_three_Level(&PWMCON1, 0.0f);
			//Motor_PWM_three_Level(&PWMCON2, DUTY_1);
                            Motor_PWM_two_Level(&STEP_A, -1.0f);
                            Motor_PWM_two_Level(&STEP_NA, -1.0f);
                            Motor_PWM_two_Level(&STEP_B, DUTY_1+torque);
                            Motor_PWM_two_Level(&STEP_NB, -1.0f);
			/*
  			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =1;
			PHASE_NB =0;	*/
  			break;
  		case 4:
  			//Motor_PWM_three_Level(&PWMCON1, -DUTY_2);
			//Motor_PWM_three_Level(&PWMCON2, DUTY_2);
                            Motor_PWM_two_Level(&STEP_A, -1.0f);
                            Motor_PWM_two_Level(&STEP_NA, DUTY_2+torque);
                            Motor_PWM_two_Level(&STEP_B, DUTY_2+torque);
                            Motor_PWM_two_Level(&STEP_NB, -1.0f);
  			/*
  			PHASE_A	 =0;
  			PHASE_NA =1;
  			PHASE_B	 =1;
			PHASE_NB =0;*/
			break;
		case 5:			//STEP 3
			//Motor_PWM_three_Level(&PWMCON1, -DUTY_1);
			//Motor_PWM_three_Level(&PWMCON2, 0.0f);
                            Motor_PWM_two_Level(&STEP_A, -1.0f);
                            Motor_PWM_two_Level(&STEP_NA, DUTY_1+torque);
                            Motor_PWM_two_Level(&STEP_B, -1.0f);
                            Motor_PWM_two_Level(&STEP_NB, -1.0f);
			/*
			PHASE_A	 =0;
			PHASE_NA =1;
			PHASE_B  =0;
			PHASE_NB =0;*/	
  			break;
  		case 6:
  			//Motor_PWM_three_Level(&PWMCON1, -DUTY_2);
			//Motor_PWM_three_Level(&PWMCON2, -DUTY_2);
                            Motor_PWM_two_Level(&STEP_A, -1.0f);
                            Motor_PWM_two_Level(&STEP_NA, DUTY_2+torque);
                            Motor_PWM_two_Level(&STEP_B, -1.0f);
                            Motor_PWM_two_Level(&STEP_NB, DUTY_2+torque);
			/*
			PHASE_A	 =0;
			PHASE_NA =1;
			PHASE_B  =0;
			PHASE_NB =1;
			*/	
  			break;
  		case 7:			//STEP4
  			//Motor_PWM_three_Level(&PWMCON1, 0.0f);
			//Motor_PWM_three_Level(&PWMCON2, -DUTY_1);
                            Motor_PWM_two_Level(&STEP_A, -1.0f);
                            Motor_PWM_two_Level(&STEP_NA, -1.0f);
                            Motor_PWM_two_Level(&STEP_B, -1.0f);
                            Motor_PWM_two_Level(&STEP_NB, DUTY_1+torque);
  			/*
  			PHASE_A	 =0;
			PHASE_NA =0;
			PHASE_B  =0;
			PHASE_NB =1;	
			*/
  			break;
  		case 8:
  			//Motor_PWM_three_Level(&PWMCON1, DUTY_2);
			//Motor_PWM_three_Level(&PWMCON2, -DUTY_2);
                            Motor_PWM_two_Level(&STEP_A, DUTY_2+torque);
                            Motor_PWM_two_Level(&STEP_NA, -1.0f);
                            Motor_PWM_two_Level(&STEP_B, -1.0f);
                            Motor_PWM_two_Level(&STEP_NB, DUTY_2+torque);
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

	if(Stepper_1.dir == 1)
	{
                stp_cnt--;
		Stepper_1.State++;
	}
	else if(Stepper_1.dir == 8)
	{
                stp_cnt++;
		Stepper_1.State--;
	}
}

void RPMToCount(int	cmd)
{
	if(cmd==0 || cmd > 150)
	{
		Stepper_1.dir= 0;	
		Stepper_1.State=-1;
		NF=1;
	}
	else
	{
		//Stepper_1.dir= (cmd>0)?1:8;
		cmd=(cmd>0)?cmd:-1*cmd;
		PR8=(unsigned int)(1.0f/((float)cmd)*gm1);
	}
}

void ActivateBrake(float BR)
{
    //When Pitch position is lower than 0.1f activate brake
    if(BR > 0.1f)
    {   
        //release brake
        Motor_PWM_two_Level(&PWMA, -0.80f);
        Motor_PWM_two_Level(&PWMB, -1.0f);
    }
    else
    {
        //brake
        Motor_PWM_two_Level(&PWMA, -1.0f);
        Motor_PWM_two_Level(&PWMB, -0.8f);
    }
    
}

void ReleaseBrake(void)
{
    Motor_PWM_two_Level(&PWMA, -0.85f);
    Motor_PWM_two_Level(&PWMB, -1.0f);
}


