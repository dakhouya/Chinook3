/************************************************************/
/* main.c                                                   */
/* Main application for Notus sensor board                  */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  : 11/06/2013                                      */
/************************************************************/

/************************************************************/
/*			INCLUDES                            */
/************************************************************/
/*Global definitions*/
#include "can_chinook3.h"
#include "globaldef.h"
#include "hardware_profile.h"
#include "p33EP512MC806.h"
#include <string.h>

/*Peripherals*/
#include "Peripherals/uart.h"
#include "Peripherals/i2c.h"
#include "Peripherals/can.h"
#include "Peripherals/dma.h"
#include "Peripherals/M_TMR.h"
#include "Peripherals/can.h"

/*Devices*/
#include "Devices/MMA8452.h"
#include "Devices/ds1338.h"
#include "Devices/cat24c256.h"

/*Applications*/
#include "notus.h"
#include "skadi/skadi.h"
#include "chinookpack.h"


/************************************************************/

/************************************************************/
/*                       VARIABLES                          */
/************************************************************/
/*Global variable for sensor*/
extern volatile sSensorValues_t sSensorValues;
extern volatile sSensorRawFreq_t sSensorRawFreq;
extern volatile sSystemFlags_t  sSystemFlags;

/*Timer variables*/
extern volatile uint8_t print; //from isr.c
extern volatile float fTimeStamp; //from isr.c
extern volatile uint8_t ubEepromWrite;

/*CANbus variables*/
uint8_t ubEepromGearInit = 0;
float fEepromTurbineDirectionInit = 0.0f;
float fEepromPitchInit = 0.0f;

uint8_t ubEepromAnswerReceiveMem = 0;
uint8_t ubEepromAnswerReceive = 0;
uint8_t ubPitchEepromAnswerReceive = 0;
uint8_t ubGearCanReceive = 0;
float fTubineDirectionReceive = 0.0f;

float fLastCanPitchPercent = 0.0f;
float fCanPitchPercent = 0.0f;

/*Receive fct prototypes*/
void fct_can_turbine_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_gear(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_pitch(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_pitch_eeprom(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_eeprom_answer(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);

/*CAN msg to send*/
T_CAN_Tx_MSG sCanMsgTurbineRPM;
T_CAN_Tx_MSG sCanMsgWheelRPM;
T_CAN_Tx_MSG sCanMsgWindSpeed;
T_CAN_Tx_MSG sCanMsgWindDirection;
T_CAN_Tx_MSG sCanMsgTrust;
T_CAN_Tx_MSG sCanMsgAccelerometer;
T_CAN_Tx_MSG sCanMsgEepromConfigSend;
T_CAN_Tx_MSG sCanMsgEepromPitchSend;

/*Encoder*/
int8_t bTxCanBuffer[8];
chinookpack_fbuffer buf;
chinookpack_packer pk;
/*Decoder*/
chinookpack_unpacked unpacker;
size_t off = 0;

/*UART command decoder variables*/
Skadi skadi;
uint8_t uartline_rcv_new;
char uartline_rcv[256];
/*Commands initializations*/
void CmdNotusVersion(Skadi* skadi, SkadiArgs args){PrintNotusVersion();}
void CmdVoltageSensing(Skadi* skadi, SkadiArgs args){PrintVoltageSensing(&sSensorValues);}
void CmdTrust(Skadi* skadi, SkadiArgs args){PrintTrust(&sSensorValues);}
void CmdWindDirection(Skadi* skadi, SkadiArgs args){PrintWindDirection(&sSensorValues);}
void CmdWindSpeed(Skadi* skadi, SkadiArgs args){PrintWindSpeed(&sSensorValues);}
void CmdTurbineRPM(Skadi* skadi, SkadiArgs args){PrintTurbineRPM(&sSensorValues);}
void CmdWheelRPM(Skadi* skadi, SkadiArgs args){PrintWheelRPM(&sSensorValues);}
void CmdAccelerometer0(Skadi* skadi, SkadiArgs args){PrintAccelerometer0(&sSensorValues);}
void CmdWheelFreq(Skadi* skadi, SkadiArgs args){PrintWheelFreq(&sSensorRawFreq);}
void CmdTurbineFreq(Skadi* skadi, SkadiArgs args){PrintTurbineFreq(&sSensorRawFreq);}
void CmdWindFreq(Skadi* skadi, SkadiArgs args){PrintWindFreq(&sSensorRawFreq);}
void CmdEeprom(Skadi* skadi, SkadiArgs args){PrintEeprom();}

SkadiCommand skadiCommandTable[] = {
  {"Version", CmdNotusVersion, 0, "Get Notus firmware version"},
  {"GetVoltage", CmdVoltageSensing, 0, "Get 3V3 and 5V0 voltage sensing"},
  {"GetTrust", CmdTrust, 0, "Get 3V3 and 5V0 voltage sensing"},
  {"GetWindDirection", CmdWindDirection, 0, "Get the wind direction"},
  {"GetWindSpeed", CmdWindSpeed, 0, "Get the wind speed"},
  {"GetTurbineRPM", CmdTurbineRPM, 0, "Get the turbine RPM"},
  {"GetWheelRPM", CmdWheelRPM, 0, "Get the wheel RPM"},
  {"GetAccelerometer0", CmdAccelerometer0, 0, "Get X Y Z axis from the on board accelerometer"},
  {"GetWheelFreq", CmdWheelFreq, 0, "Get the wheel frequency"},
  {"GetTurbineFreq", CmdTurbineFreq, 0, "Get the turbine frequency"},
  {"GetWindFreq", CmdWindFreq, 0, "Get the wind frequency"},
  {"GetEEPROM", CmdEeprom, 0,"Get EEPROM data"}
};
void uartReceiveLineEvt(const char* line,size_t s){
    uartline_rcv_new=1;
    memcpy(uartline_rcv,line,s-1);
    uartline_rcv[s-1]= '\0';
}

/*Configuration bits*/
_FOSCSEL(FNOSC_FRCPLL); // select fast internal rc with pll
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); // Watchdog timer software enabled

/************************************************************/

/************************************************************/
/*			MAIN PROGRAM                        */
/************************************************************/
int main(void)
{
        /*Disable watchdog*/
        RCONbits.SWDTEN = 0;
	set_clk();
        DataStructInit(&sSensorValues);
        NotusInitIOs();
        NotusInitPeripherals();
        NotusInitDevices();

        /*CAN bus initialization*/
        /*Encoder & decoder*/
	chinookpack_fbuffer_init(&buf,bTxCanBuffer,8);
	chinookpack_packer_init(&pk,&buf,chinookpack_fbuffer_write);
	chinookpack_unpacked_init(&unpacker);

        /*Msg*/
        /*configuration du message pour la direction de l'eolienne */
	config_CAN_filter(0, CAN_MSG_TURBINE_DIRECTION_SID , STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_turbine_direction);

	/*configuration du message pour le gear */
	config_CAN_filter(1, CAN_MSG_GEAR_SID , STANDARD_ID);
	receive_CAN_msg(1, 3, fct_can_gear);

        /*configuration du message pour l'eeprom ack */
	config_CAN_filter(2, CAN_MSG_EEPROM_CONFIG_ACK_SID , STANDARD_ID);
        receive_CAN_msg(2, 3, fct_can_eeprom_answer);

        /*configuration du message pour l'eeprom ack */
	config_CAN_filter(3, CAN_MSG_PITCH_ACK_CONFIG , STANDARD_ID);
        receive_CAN_msg(3, 3, fct_can_pitch_eeprom);

        /*configuration du message pour le pitch */
	config_CAN_filter(4, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID);
        receive_CAN_msg(4, 3, fct_can_pitch);

	config_CAN_Tx_msg(&sCanMsgTurbineRPM,CAN_MSG_TURBINE_RPM_SENSOR_SID,STANDARD_ID,3);
	config_CAN_Tx_msg(&sCanMsgWheelRPM,CAN_MSG_WHEEL_RPM_SID,STANDARD_ID,3);
	config_CAN_Tx_msg(&sCanMsgWindSpeed,CAN_MSG_WIND_SPEED_SID,STANDARD_ID,3);
	config_CAN_Tx_msg(&sCanMsgWindDirection,CAN_MSG_WIND_DIRECTION_SID,STANDARD_ID,3);
 	config_CAN_Tx_msg(&sCanMsgTrust,CAN_MSG_TRUST_SID,STANDARD_ID,3);
        config_CAN_Tx_msg(&sCanMsgAccelerometer,CAN_MSG_ACCELERATION_SID,STANDARD_ID,3);
        config_CAN_Tx_msg(&sCanMsgEepromConfigSend,CAN_MSG_EEPROM_CONFIG_SEND_SID,STANDARD_ID,3);
        config_CAN_Tx_msg(&sCanMsgEepromPitchSend,CAN_MSG_PITCH_CONFIG_SEND,STANDARD_ID,3);

        /*UART command decoder initialization*/
        UartSetRXLineEvt(UART_1,uartReceiveLineEvt);
        skadi_init(&skadi, skadiCommandTable,sizeof(skadiCommandTable)/sizeof(SkadiCommand));

	while(TRUE)
	{
                /*Get sensors data*/
                GetTrust(&sSensorValues);
                GetWindDirection(&sSensorValues);
                GetWindSpeed(&sSensorValues);
                GetTurbineRPM(&sSensorValues);
                GetWheelRPM(&sSensorValues);
                Get3V3Sensing(&sSensorValues);
                Get5V0Sensing(&sSensorValues);
                //GetsAccelerometer0(&sSensorValues);

                /*Uart command processing*/
                if(uartline_rcv_new){
                    skadi_process_command(&skadi,uartline_rcv);
                    uartline_rcv_new=0;
                }

		if(print)
		{
                    LED_STAT2^=1;
                    /*Send CAN messages*/

                    /*Initial message to set turbine direction and gear*/
                    if(ubEepromAnswerReceive == 0x55)
                    {
                        ubEepromGearInit = ReadGearEeprom();
                        fEepromTurbineDirectionInit = ReadTurbineDirEeprom();
                        chinookpack_pack_uint8(&pk,ubEepromGearInit);
                        chinookpack_pack_float(&pk,fEepromTurbineDirectionInit);
                        Set_Timeout();
                        send_CAN_msg(&sCanMsgEepromConfigSend,bTxCanBuffer, 7);
                        while(!is_CAN_msg_send(&sCanMsgEepromConfigSend) && !sSystemFlags.CanTimeout);
                        Reset_Timeout();
                        chinookpack_fbuffer_clear(&buf);
                    }

                    /*Initial message to set pitch position*/
                    if(ubPitchEepromAnswerReceive == 0x55)
                    {
                        fEepromPitchInit = ReadPitchEeprom();
                        chinookpack_pack_float(&pk,fEepromPitchInit);
                        Set_Timeout();
                        send_CAN_msg(&sCanMsgEepromPitchSend,bTxCanBuffer, 5);
                        while(!is_CAN_msg_send(&sCanMsgEepromPitchSend) && !sSystemFlags.CanTimeout);
                        Reset_Timeout();
                        chinookpack_fbuffer_clear(&buf);
                    }

                    chinookpack_pack_float(&pk,sSensorValues.fTurbineRPM);
                    Set_Timeout();
                    send_CAN_msg(&sCanMsgTurbineRPM,bTxCanBuffer, 5);
                    while(!is_CAN_msg_send(&sCanMsgTurbineRPM) && !sSystemFlags.CanTimeout);
                    Reset_Timeout();
                    chinookpack_fbuffer_clear(&buf);

                    /*
                    chinookpack_pack_float(&pk,sSensorValues.sAccelerometer0.fGx);
                    Set_Timeout();
                    send_CAN_msg(&sCanMsgAccelerometer,bTxCanBuffer, 5);
                    while(!is_CAN_msg_send(&sCanMsgAccelerometer) && !sSystemFlags.CanTimeout);
                    Reset_Timeout();
                    chinookpack_fbuffer_clear(&buf);
                    */

                    /*EEPROM gear and turbine position*/
                    if(ubEepromAnswerReceiveMem != ubGearCanReceive)
                    {
                        ubEepromAnswerReceiveMem = ubGearCanReceive;
                        WriteGearEeprom(ubGearCanReceive);
                        WriteTurbineDirEeprom(fTubineDirectionReceive);
                    }
                    /*EEPROM pitch position*/
                    if(fLastCanPitchPercent != fCanPitchPercent)
                    {
                        fLastCanPitchPercent = fCanPitchPercent;
                        WritePitchEeprom(fLastCanPitchPercent);
                    }

                    chinookpack_pack_float(&pk,sSensorValues.fWheelRPM);
                    Set_Timeout();
                    send_CAN_msg(&sCanMsgWheelRPM,bTxCanBuffer, 5);
                    while(!is_CAN_msg_send(&sCanMsgWheelRPM) && !sSystemFlags.CanTimeout);
                    Reset_Timeout();
                    chinookpack_fbuffer_clear(&buf);

                    chinookpack_pack_float(&pk,sSensorValues.fWindSpeed);
                    Set_Timeout();
                    send_CAN_msg(&sCanMsgWindSpeed,bTxCanBuffer, 5);
                    while(!is_CAN_msg_send(&sCanMsgWindSpeed) && !sSystemFlags.CanTimeout);
                    Reset_Timeout();
                    chinookpack_fbuffer_clear(&buf);

                    chinookpack_pack_float(&pk,sSensorValues.fWindDir);
                    Set_Timeout();
                    send_CAN_msg(&sCanMsgWindDirection,bTxCanBuffer, 5);
                    while(!is_CAN_msg_send(&sCanMsgWindDirection) && !sSystemFlags.CanTimeout);
                    Reset_Timeout();
                    chinookpack_fbuffer_clear(&buf);

                    chinookpack_pack_float(&pk,sSensorValues.fTrust);
                    Set_Timeout();
                    send_CAN_msg(&sCanMsgTrust,bTxCanBuffer, 5);
                    while(!is_CAN_msg_send(&sCanMsgTrust) && !sSystemFlags.CanTimeout);
                    Reset_Timeout();
                    chinookpack_fbuffer_clear(&buf);

                    print = 0;
		}

                /*Error processing*/
                if(sSystemFlags.CanError)
                {
                    LED_STAT0 = 1;
                }
	}
	return 0;
}
/************************************************************/

void fct_can_turbine_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fTubineDirectionReceive = unpacker.data.via.dec;
}
void fct_can_pitch(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fCanPitchPercent = unpacker.data.via.dec;
}

void fct_can_gear(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[2] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        ubGearCanReceive = (unsigned char)unpacker.data.via.u64;
}
void fct_can_eeprom_answer(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        //LED_STAT1 = 1;
        const char ubReceiveData[2] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8};
        int old_ipl;

        // Block interruptions
        SET_AND_SAVE_CPU_IPL(old_ipl, 7);
        off = 0;
        chinookpack_unpack_next(&unpacker,ubReceiveData,2,&off);
        off = 0;
        RESTORE_CPU_IPL(old_ipl);
        ubEepromAnswerReceive = (unsigned char)unpacker.data.via.u64;
        if(ubEepromAnswerReceive == 0xAA)LED_STAT1 = 1;
}
void fct_can_pitch_eeprom(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        //LED_STAT1 = 1;
        const char ubReceiveData[2] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8};
        int old_ipl;

        // Block interruptions
        SET_AND_SAVE_CPU_IPL(old_ipl, 7);
        off = 0;
        chinookpack_unpack_next(&unpacker,ubReceiveData,2,&off);
        off = 0;
        RESTORE_CPU_IPL(old_ipl);
        ubPitchEepromAnswerReceive = (unsigned char)unpacker.data.via.u64;
}
