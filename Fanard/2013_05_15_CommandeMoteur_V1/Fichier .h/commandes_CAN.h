/*Propriété du Chinook ÉTS*/

/*Commandes_CAN.h*/

//#include

/********************************************************/
/*buttons_status()

Description:	Concaténer 4 statuts des boutons pour envoyer sur le CAN bus

Inputs:			Adresse du PORT contenant les 4 boutons

Outputs:		Message CAN contenant l'état des boutons de commande

Specs:			-SID: 11 bit identifier à définir

				-Seulement envoyer statuts des boutons si détection 
				d'un front descendant d'un des boutons (utiliser les change notice)
				
				-Exemple: buttons_status(&PORTA);

*/

int buttons_status(unsigned * PORTx);

/********************************************************/
/*mode_auto()

Description:	Envoyer l'information sur le mode de fonctionnement de l'automatisation

Inputs:			Adresse du PORT contenant le bouton manuel/automatique
				1: Mode automatique
				0: Mode manuel

Outputs:		Message CAN contenant l'état du bouton manuel/automatique

Specs:			-SID: 11 bit identifier (à définir)

				-Envoyer continuellement le mode de l'automatisation sur le CAN bus

				-Exemple: mode_auto(&PORTA);

*/

int mode_auto(unsigned char * PORTx);

/********************************************************/
/*pitchangle_man()

Description: 	Convertit la tension du potentiomètre en degrés

Inputs:			Tension du potentiomètre (volts)

Outputs:		Message CAN contenant l'angle du pitch de l'éolienne

Specs: 			-SID: 11 bit identifier (à définir)

				-Plage d'angles de pitch de l'éolienne : 0 deg à ? deg
				
				-Envoyer continuellement l'angle de pitch de l'éolienne
				si le mode est manuel (Fonction n'est pas utilisée en mode automatique)

				-L'ADC doit être activé et fonctionnel

*/

int pitchangle_man(float Vpot);
/********************************************************/