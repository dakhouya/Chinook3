#include"globaldef.h"
#include"hardware_profile.h"
#include"p33EP512MC806.h"
#include"uart.h"
#include"i2c.h"
#include "MMA8452.h"
#include "notus.h"
#include <stdio.h>
#include "M_TMR.h"

/*Global variable for sensor*/
extern volatile sSensorValues_t sSensorValues;
extern volatile sSensorRawFreq_t sSensorRawFreq;

/*UART Variables*/
uint8_t ubParam[5]={BRGH_HIGH_SPEED,0,UART_8BITS_NOPARITY,UART_1STOP_BIT,UART_115200BAUD};
uint8_t buf[80]={0};

/*Timer Variables*/
extern volatile uint8_t print; //from isr.c
extern volatile float fTimeStamp; //from isr.c

volatile sAxis_t sAccelerometerAxis = {0};
int main(void)
{
	set_clk();
        NotusInitIOs();
        DataStructInit(&sSensorValues);

	UartInit(UART_1,ubParam);
	UartTxEnable(UART_1, ENABLE);
	UartInitPortStruc(UART_1, NULL,NULL);
	UartInterruptTxEnable(UART_1, CHAR_N_BUFFER_EMPTY,2,ENABLE);
	//UartInterruptRxEnable(UART_1, CHAR_RECEIVE,3,ENABLE);
	UartTxFrame(UART_1, "Notus Started \n\r", 18);

	I2C_Init(I2C_1,100000.0f);
	Init_Timer5(TIMER5_FREQ);/*print*/
        RPMInit();
        ADCInit();
        
	while(TRUE)
	{
                GetTrust();
                GetWindDirection();
                GetWindSpeed();
                GetTurbineRPM();
		if(print)
		{
                    sprintf(buf, "%.2f    %.2f    %.2f    %.2f    %.2f",(double)fTimeStamp, (double)sSensorValues.fTrust, (double)sSensorValues.fWindDir, (double)sSensorValues.fWindSpeed, (double)sSensorValues.fTurbineRPM);
                    UartTxFrame(UART_1, buf, 80);
                    UartTxFrame(UART_1,"\n\r", 4);
                    print = 0;
		}

	}
	return 0;
}
