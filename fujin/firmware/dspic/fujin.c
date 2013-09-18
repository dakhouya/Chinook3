#include "fujin.h"
#include "lib/dspic/dspic.h"

Fujin_s fujin;

void fujin_init_board(){
    fujin_set_clk();
    fujin_init_io();
    LED_PWR = 1;
    //PORTB = 0x7800;

    fujin_init_i2c();
    fujin_init_uart();
    fujin_init_can();

    fujin_init_vmon();
    //fujin_init_eeprom();
    //fujin_init_rtc();

    Init_Timer5(4.0f);/*Display timer and reset values*/
    Init_Timer3(10.0f);/*CAN timeout timer*/
    
    fujin.chinook.power.v = -1;
    fujin.chinook.power.i = -1;

    
}

void fujin_set_clk()
{
    _PLLPRE=0;
    _PLLPOST=0;
    _PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;
    while(OSCCONbits.LOCK !=1);
}

void fujin_init_io(){

    /*Disable analog inputs*/
    ANSELB = 0x0000;
    ANSELC = 0x0000;
    ANSELD = 0x0000;
    ANSELE = 0x0000;
    // LEDS
    TRISB = 0x0000;
    // UART 1 Pins // XBEE
    // _RP69R = 1; // RD5
    CONF_U1TX_PIN = OUTPUT;
    CONF_U1RX_PIN = INPUT;
    _RP97R = 0b000001;  // TX
    _U1RXR = 96; // RX

    // UART 2 Pins // USB-Serial
    CONF_U2TX_PIN = OUTPUT;
    CONF_U2RX_PIN = INPUT;
    _RP101R = 0b000011; //TX
    _U2RXR = 100;//RX
//    _RP101R = 0b000001; //TX
//    _U1RXR = 100; // RX

    // CAN 1 Pins
    CONF_CANTX_PIN = OUTPUT;
    CONF_CANRX_PIN = INPUT;
    _RP99R = 0b001110;    // CAN1TX
    _C1RXR = 98;

    // MISC Pins
    CONF_EEPROM_WP_PIN = OUTPUT;
    CONF_SD_CARD_CS_PIN = OUTPUT;

    // SPI Pins
    // SPI2 is an autonomus guy he configures himself alone
    //CONF_SDO_PIN = OUTPUT;
    //CONF_SCK_PIN = OUTPUT;
    //CONF_SDI_PIN = INPUT;
    //_RP120R = 0b001000; // SDO2
    //_RP118R = 0b001001; // SCK2
    
    // I2C Pins
    CONF_SCL_PIN = OUTPUT;
    // You dont need to configure i2c pins since the i2c module configures
    // them like a big boy

    // OSC Pins
    // OSC Pins too are big boys!
}


uint8_t uart_buf[80];
        sUartParam usbSerialParams={BRGH_HIGH_SPEED,0,UART_8BITS_NOPARITY,UART_1STOP_BIT,UART_9600BAUD};
        sUartParam xbeeParams     ={BRGH_HIGH_SPEED,0,UART_8BITS_NOPARITY,UART_1STOP_BIT,UART_9600BAUD};
void fujin_init_uart(){
#if ENABLE_UART == TRUE

    #if ENABLE_USBSERIAL == TRUE
        UartInit(UART_2,&usbSerialParams);
	UartTxEnable(UART_2, ENABLE);
	UartInitPortStruc(UART_2, NULL,NULL);
	UartInterruptTxEnable(UART_2, CHAR_N_BUFFER_EMPTY,2,ENABLE);
	UartInterruptRxEnable(UART_2, CHAR_RECEIVE,3,ENABLE);
        fujin.has_usbserial=true;
    #else
        fujin.has_usbserial=false;
    #endif
    #if ENABLE_XBEE == TRUE
        UartInit(UART_1,&xbeeParams);
	UartTxEnable(UART_1, ENABLE);
	UartInitPortStruc(UART_1, NULL,NULL);
	UartInterruptTxEnable(UART_1, CHAR_N_BUFFER_EMPTY,2,ENABLE);
	UartInterruptRxEnable(UART_1, CHAR_RECEIVE,3,ENABLE);
        fujin.has_xbee=true;
    #else
        fujin.has_xbee=false;
    #endif

    fujin.has_uart=true;
#else
    fujin.has_uart=false;
#endif
}

void fujin_init_i2c(){
#if ENABLE_I2C == TRUE
    I2C_InterruptEnable(I2C_1,5,DISABLE);
    I2C_Init(I2C_1,100000.0f);
    fujin.has_i2c=true;
#else
    fujin.has_i2c=false;
#endif
}

void fujin_init_rtc(){
#if ENABLE_RTC == TRUE && ENABLE_I2C == TRUE
    fujin.has_rtc=true;
    #error "fujin_init_rtc() not implemented"
#else
    fujin.has_rtc=false;
#endif
}

void fujin_init_vmon(){
#if ENABLE_VMON == TRUE && ENABLE_I2C == TRUE
    ltc4151_init(&(fujin.ltc4151_state),I2C_1);    
    fujin.has_vmon=true;
#else
    fujin.has_vmon=false;
#endif
}
void fujin_init_eeprom(){
#if ENABLE_EEPROM == TRUE && ENABLE_I2C == TRUE
    fujin.has_eeprom=true;
    #error "fujin_init_eeprom() not implemented"
#else
    fujin.has_eeprom=false;
#endif

}

void fujin_init_can(){
#if ENABLE_CAN == TRUE
    fujin.has_can=true;
    init_CAN(CAN_NORMAL, 8, 0, 1, 7);
#else
    fujin.has_can=false;
#endif
}

void fujin_init_spi(){
#if ENABLE_SPI == TRUE
    fujin.has_spi=true;

#else
    fujin.has_can=false;
#endif
}