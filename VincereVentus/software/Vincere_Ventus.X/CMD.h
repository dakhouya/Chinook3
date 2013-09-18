//Contient les macros de la commande et l'asservissement des moteurs
#include "p33EP512MU810.h"
#include "Global.h"

#ifndef MOTOR_CMD
#define MOTOR_CMD

/******************************************************************
                            Transmission
******************************************************************/

void Stepper_Shift_Init(char lastgear);
void Stepper_Shift(void);
void UpdateStepper(int direction);
void SHIFT_UP(void);
void SHIFT_DOWN(void);
void DisableStepper(void);
unsigned int DutyCycle(float duty);

/******************************************************************
                             Mât
******************************************************************/

void Init_mat(float last_position_tourelle);

/*Contrôle de la position du mât*/
void Update_mat_init(float Position_CMD);
void Update_mat(float Position_CMD);

/*Contrôleur de vitesse et de courant*/
void tower_motor_ctrl(unsigned int * duty_reg,float POS_CMD);


#endif

