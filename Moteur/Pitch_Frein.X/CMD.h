//Contient les macro de la commande et l'asservissement des moteur
#include <p33EP256MC502.h>
#include "Global.h"

#ifndef MOTOR_CMD
#define MOTOR_CMD

#define U_PWM		//Use PWM I/O

#ifdef	U_PWM
	#define PHASE_A		IOCON1bits.PENL	
	#define PHASE_NA	IOCON1bits.PENH	
	#define PHASE_B		IOCON2bits.PENL		
	#define PHASE_NB	IOCON2bits.PENH		
#else
	#define PHASE_A		LATEbits.LATE0
	#define PHASE_NA	LATEbits.LATE1
	#define PHASE_B		LATEbits.LATE2
	#define PHASE_NB	LATEbits.LATE3
#endif

#define NBSTEP	400	
#define min_degres_pitch    35.11f
#define max_degres_pitch    -10.17f
#define GM1		60.0f*(float)NBSTEP 
void ChangeDir(int dir);
//char NF=0;

void SHIFT_UP(void);
void SHIFT_DOWN(void);
void DisableStepper(void);
/*****************************************************************/
/*
tower_motor_ctrl

	Met à jour la boucle de control pour le moteur du mat

	INPUT 		: 
				- duty_reg, registre dans lequel mettre le nouveau duty-cycle 				
	REQUIS		:
				-	La fonction doit être appelé à un intervalle précis (e.g. 10Hz)
				-   Un module PWM doit être démarré
	OUTPUT 		:
				- Aucun
    
    EFFECT		:
    			-	Augmente ou réduit le duty-cycle  du moteur pour changer
    				la vitesse de ce dernier
    			
	SPEC		: 	
				-	
	
	//Call example:
	//tower_motor_ctrl(& MDC)
*/
void tower_motor_ctrl(unsigned int * duty_reg, float Speed_CMD);

/*****************************************************************/
/*
RunStepper

	Initialise un moteur Stepper

	INPUT 		: 
				- accel, 	float, valeur de l'accélération maximale 
							que le système doit admettre
				- RPM, 		float, valeur de la consigne de vitesse
				- state, 	int, valeur de l'état ou du pas actuel du moteur				
	REQUIS		:
				-	Une variable de type Struct Stepper de nom Stepper_1 doit
							être déclaré.
				-	Timer8 doit être libre. Ce dernier sert à synchroniser les pas.
	OUTPUT 		:
				- Aucun
    
    EFFECT		:
    			-	Initialise la variable Stepper_1 et démarre le Timer8.
    			
	SPEC		: 	
				-	Le moteur peut être initialiser dans n'importe quel état (state)
							mais devrait être mis à off(state= -1) et une boucle
							de régulation se chargera de l'état du moteur
*/
void RunStepper(void);
/*****************************************************************/

/*****************************************************************/
/*
UpdateStepper

	

	INPUT 		: 
				- Aucun				
	REQUIS		:
				-	La fonction RunStepper doit être appelé avant.
				-	Les sorties physiques (Phases) doivent être définie dans CMD.h
	OUTPUT 		:
				- Aucun
    
    EFFECT		:
    			-	Incrémente Stepper_1.State et permet l'affichage des états via UART.
    			
	SPEC		: 	
				-	Si 
*/
void UpdateStepper(int dir);
/*****************************************************************/


unsigned int DutyCycle(float duty);

#endif

