/* Fonction d'initialisation du dsPIC33EP512MC806 pour le PCB Commande moteur*/
#include "p33EP512MC806.h"
#include <stdio.h>
#include "Global.h"
#include "can.h"
#include "can_chinook3.h"
#include "M_UART.h"
#include "dma.h"

#ifndef MOTOR_SETUP
#define MOTOR_SETUP

/*Initialisation des boutons poussoirs */
#define BP1 PORTDbits.RD0
#define BP2 PORTCbits.RC14
#define BP3 PORTDbits.RD10
#define BP4 PORTDbits.RD8

/*Initialisation de la commande automatique/manuel*/
#define AUTO_MAN PORTGbits.RG2

/*Initialisation du claxon*/
#define BUZZER PORTBbits.RB1

/*Initialisation des LED */
#define Led1 _RF1
#define Led2 _RF0
#define Led3 _RE0
#define Led4 _RE2

/*Initialisation des potentiomètres */
//#define POTANA4 PORTBbits.ANA4

/***************************DEFINES*******************************/
/*Activate CAN initialisation and CAN msg Tx*/ 
#define USE_MY_CAN
/*****************************************************************/

/* Fonction setup qui initialise les entrées/sorties et caractéristiques du pic */
void Setup(void);
void initialisation_UART(void);
void initialisation_CAN(void);
void initialisation_CLK(void);

#endif
