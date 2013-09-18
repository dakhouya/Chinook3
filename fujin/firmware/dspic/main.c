#include "fujin.h"
#include "utils.h"
#include "lib/chinookpack.h"
#include <stdio.h>
#include <string.h>

// Device Configurations registers
_FOSCSEL(FNOSC_FRCPLL); // select fast internal rc with pll
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); // Watchdog timer software enabled

uint8_t print=0;
unsigned char CanTimeout = 0;

int datReceive_can_cmd;

void setup_can_rx(void);
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_shift(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_pitch_orientation(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_trust(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_wind_speed(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, int nbr_data);
void fct_can_turbine_rpm_motor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_turbine_rpm_sensor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_wheel_rpm(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_turbine_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);
void fct_can_gear(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data);

T_CAN_Tx_MSG can_msg_clock;
T_CAN_Tx_MSG can_msg_current;
T_CAN_Tx_MSG can_msg_voltage;
T_CAN_Tx_MSG can_msg_pitch;
T_CAN_Tx_MSG can_msg_gear;

char bTxCanBuffer[8];
chinookpack_fbuffer buf;
chinookpack_packer pk;
chinookpack_unpacked unpacker; //Will contain the unpacked data
unsigned int off = 0; //offset to read more than 1 msg in 1 packet

uint8_t can_msg_current_buf[5];
uint8_t can_msg_voltage_buf[5];
uint8_t can_msg_pitch_buf[5];


uint8_t uartline_rcv_new;
char uartline_rcv[256];

uint8_t xbeeline_rcv_new;
char xbeeline_rcv[256];

/*Data logging buffer*/
uint8_t ubDataLoggingBuffer[256] = {0};

void skadiChangePitch(Skadi* skadi, SkadiArgs args){
    if(args.length==1){
        // args.elements[0];
        LATBbits.LATB13 ^=1;
    }
}


SkadiCommand testCommandTable[] = {
  {"pitch", skadiChangePitch, 2, "changer le pitch"}
};

void xbeeReceiveLineEvt(const char* line,size_t s){
    xbeeline_rcv_new=1;
    memcpy(xbeeline_rcv,line,s-1);
    xbeeline_rcv[s-1]= '\0';
}

void uartReceiveLineEvt(const char* line,size_t s){
    uartline_rcv_new=1;
    memcpy(uartline_rcv,line,s-1);
    uartline_rcv[s-1]= '\0';
}

int main(void) {

    fujin_init_board();

    // CAN PREPARATION
    #if ENABLE_CAN == TRUE
    chinookpack_fbuffer_init(&buf,bTxCanBuffer,8);
    chinookpack_packer_init(&pk,&buf,chinookpack_fbuffer_write);
    chinookpack_unpacked_init(&unpacker);
    
    config_CAN_Tx_msg(&can_msg_current, CAN_MSG_CURRENT_MONITOR_SID , STANDARD_ID, 3);
    config_CAN_Tx_msg(&can_msg_voltage, CAN_MSG_VOLTAGE_MONITOR_SID , STANDARD_ID, 3);
    config_CAN_Tx_msg(&can_msg_clock,   CAN_MSG_TIME_SID , STANDARD_ID, 3);
    //config_CAN_Tx_msg(&can_msg_pitch,   CAN_MSG_PITCH_AUTO_SID , STANDARD_ID, 3);
    config_CAN_Tx_msg(&can_msg_gear,    CAN_MSG_GEAR_FUJIN_SID , STANDARD_ID, 3);

    setup_can_rx();
    #endif
    
    // Read Clock for timestamps
    #if ENABLE_RTC == TRUE
    // init the rtc
    #endif



    // TODO: Read Eeprom Parameters
    //       and and set settings
    // Skadi
      skadi_init(&fujin.skadi, testCommandTable,sizeof(testCommandTable)/sizeof(SkadiCommand));

    UartSetRXLineEvt(UART_1,uartReceiveLineEvt);
    UartSetRXLineEvt(UART_2,xbeeReceiveLineEvt);
    while(1){
        // 1. Read Current and SHUT DOWN RELAY if overloading
        #if ENABLE_VMON == TRUE && ENABLE_I2C == TRUE
        fujin.chinook.power.v = ltc4151_read_voltage(&(fujin.ltc4151_state));
        fujin.chinook.power.i = ltc4151_read_current(&(fujin.ltc4151_state));
        #endif

        
        // 2. Read Clock for timestamps
        #if ENABLE_RTC == TRUE
        // At some interval read rtc and send time on can
        #endif

                // 2. Read Clock for timestamps
        #if ENABLE_RTC == TRUE
        // At some interval read rtc and send time on can
        #endif


        
        // 4. UART Processing
        #if ENABLE_UART == TRUE
        // 4.1 XBEE Processing
        #if ENABLE_XBEE == TRUE
        if(xbeeline_rcv_new){
            skadi_process_command(&fujin.skadi,xbeeline_rcv);
            xbeeline_rcv_new=0;
        }
        
        #endif
        // 4.2 USB-Serial Processing
        #if ENABLE_USBSERIAL == TRUE
        if(uartline_rcv_new){
            skadi_process_command(&fujin.skadi,uartline_rcv);
            uartline_rcv_new=0;
        }
        #endif
        #endif
        if(print)
        {
            #if ENABLE_XBEE == TRUE && ENABLE_UART == TRUE
            sprintf(ubDataLoggingBuffer,"%u %.2f %.2f %.2f %.2f %.2f\n\r"
                                                                ,fujin.loggin.ubGear
                                                                ,fujin.loggin.fWindSpeed
                                                                ,fujin.loggin.fTurbineRPM
                                                                ,fujin.loggin.fWheelRPM
                                                                ,fujin.loggin.fTrust
                                                                ,fujin.loggin.fPitch);
            UartTxFrame(UART_1, ubDataLoggingBuffer, strlen(ubDataLoggingBuffer));
            
            #endif

            // 3. CAN Processing
            #if ENABLE_CAN == TRUE
            chinookpack_pack_float(&pk,fujin.chinook.power.i);
            Set_Timeout();
            send_CAN_msg(&can_msg_current, bTxCanBuffer, 5);
            while(!is_CAN_msg_send(&can_msg_current) && !CanTimeout);      // test si le message est envoyé
            Reset_Timeout();
            chinookpack_fbuffer_clear(&buf);

            chinookpack_pack_float(&pk,fujin.chinook.power.v);
            Set_Timeout();
            send_CAN_msg(&can_msg_voltage, bTxCanBuffer, 5);
            while(!is_CAN_msg_send(&can_msg_voltage) && !CanTimeout);      // test si le message est envoyé
            Reset_Timeout();
            chinookpack_fbuffer_clear(&buf);
            #endif

            print = 0;
        }

    }

    // Should never go there
    return 0;
}

void __attribute__((interrupt, auto_psv)) _T5Interrupt(void)
{
    /*Timer used for display at 10 Hz*/
    if(print==0) print = 1;
    _T5IF=0;
}
void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
    CanTimeout = 1;
    _T3IF=0;
}

void setup_can_rx(void)
{
        /*configuration du message pour les commandes */
	config_CAN_filter(0, CAN_MSG_BUTTON_CMD_SID , STANDARD_ID);
	receive_CAN_msg(0, 3, fct_can_cmd);
	//config_CAN_mask(0, 2.0f, STANDARD_ID);

	/*configuration du message pour l'orientation du pitch */
	config_CAN_filter(1, CAN_MSG_MANUAL_PITCH_SID , STANDARD_ID);
	receive_CAN_msg(1, 3, fct_can_pitch_orientation);
	//config_CAN_mask(1, 2.0f, STANDARD_ID);

	/*configuration du message pour la vitesse du vent */
	config_CAN_filter(2, CAN_MSG_WIND_SPEED_SID , STANDARD_ID);
	receive_CAN_msg(2, 3, fct_can_wind_speed);
	//config_CAN_mask(2, 2.0f, STANDARD_ID);

	/*configuration du message pour la direction du vent */
	config_CAN_filter(3, CAN_MSG_WIND_DIRECTION_SID , STANDARD_ID);
	receive_CAN_msg(3, 3, fct_can_wind_direction);
	//config_CAN_mask(3, 2.0f, STANDARD_ID);

	/*configuration du message pour le RPM Moteur */
	config_CAN_filter(4, CAN_MSG_TURBINE_RPM_MOTOR_SID , STANDARD_ID);
	receive_CAN_msg(4, 3, fct_can_turbine_rpm_motor);
	//config_CAN_mask(5, 2.0f, STANDARD_ID);

	/*configuration du message pour le RPM Roues */
	config_CAN_filter(5, CAN_MSG_WHEEL_RPM_SID , STANDARD_ID);
	receive_CAN_msg(5, 3, fct_can_wheel_rpm);
	//config_CAN_mask(6, 2.0f, STANDARD_ID);

	/*configuration du message pour la direction de l'eolienne */
	config_CAN_filter(6, CAN_MSG_TURBINE_DIRECTION_SID , STANDARD_ID);
	receive_CAN_msg(6, 3, fct_can_turbine_direction);
	//config_CAN_mask(7, 2.0f, STANDARD_ID);

	/*configuration du message pour le gear */
	config_CAN_filter(7, CAN_MSG_GEAR_SID , STANDARD_ID);
	receive_CAN_msg(7, 3, fct_can_gear);
	//config_CAN_mask(8, 2.0f, STANDARD_ID);

        /*configuration du message pour le RPM de l'eolienne */
	config_CAN_filter(8, CAN_MSG_TURBINE_RPM_SENSOR_SID , STANDARD_ID);
	receive_CAN_msg(8, 3, fct_can_turbine_rpm_sensor);
	//config_CAN_mask(8, 2.0f, STANDARD_ID)

        /*configuration du message pour le trust */
	config_CAN_filter(9, CAN_MSG_TRUST_SID , STANDARD_ID);
	receive_CAN_msg(9, 3, fct_can_trust);
	//config_CAN_mask(8, 2.0f, STANDARD_ID)
}
void fct_can_cmd(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);

	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;

	RESTORE_CPU_IPL(old_ipl);

        datReceive_can_cmd = (int)unpacker.data.via.i64;
}
void fct_can_pitch_orientation(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fujin.loggin.fPitch = unpacker.data.via.dec;
}
void fct_can_wind_speed(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fujin.loggin.fWindSpeed = unpacker.data.via.dec;
}
//volatile void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID,T_CAN_DATA recopie, int nbr_data)
void fct_can_wind_direction(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, int nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fujin.loggin.fWindDir = unpacker.data.via.dec;

}
void fct_can_turbine_rpm_motor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fujin.loggin.fTurbineRPM = unpacker.data.via.dec;
}
void fct_can_turbine_rpm_sensor(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
         const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fujin.loggin.fTurbineRPM = unpacker.data.via.dec;
}
void fct_can_wheel_rpm(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fujin.loggin.fWheelRPM = unpacker.data.via.dec;
}
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
        fujin.loggin.fTurbineDir = unpacker.data.via.dec;
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
        fujin.loggin.ubGear = (unsigned char)unpacker.data.via.u64;
}
void fct_can_trust(unsigned long ID, T_TYPE_ID type_ID, T_CAN_DATA* recopie, char nbr_data)
{
        const char ubReceiveData[5] = {(recopie->data3 & 0x00FF),(recopie->data3 & 0xFF00)>>8,(recopie->data4 & 0x00FF),(recopie->data4 & 0xFF00)>>8,(recopie->data5 & 0x00FF)};
	int old_ipl;

	// Block interruptions
	SET_AND_SAVE_CPU_IPL(old_ipl, 7);
	off = 0;
	chinookpack_unpack_next(&unpacker,ubReceiveData,5,&off);
	off = 0;
	RESTORE_CPU_IPL(old_ipl);
        fujin.loggin.fTrust = unpacker.data.via.dec;
}
/************************************************************/