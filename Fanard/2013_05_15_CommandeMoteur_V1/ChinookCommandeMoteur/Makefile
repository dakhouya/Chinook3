# MPLAB IDE generated this makefile for use with GNU make.
# Project: Commande_moteur.mcp
# Date: Tue May 07 21:23:50 2013

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

Commande_moteur.hex : Commande_moteur.cof
	$(HX) "Commande_moteur.cof"

Commande_moteur.cof : ISR.o M_TMR.o setup_commande.o main.o M_UART.o M_OC.o ADC.o can.o dma.o
	$(CC) -mcpu=33EP512MC806 "ISR.o" "M_TMR.o" "setup_commande.o" "main.o" "M_UART.o" "M_OC.o" "ADC.o" "can.o" "dma.o" -o"Commande_moteur.cof" -Wl,-Tp33EP512MC806.gld,--defsym=__MPLAB_BUILD=1,-Map="Commande_moteur.map",--report-mem

ISR.o : Global.h p33EP512MC806.h Setup_commande.h p33EP512MC806.h ISR.c
	$(CC) -mcpu=33EP512MC806 -x c -c "ISR.c" -o"ISR.o" -g -Wall

M_TMR.o : Global.h p33EP512MC806.h Setup_commande.h p33EP512MC806.h M_TMR.c
	$(CC) -mcpu=33EP512MC806 -x c -c "M_TMR.c" -o"M_TMR.o" -g -Wall

setup_commande.o : Global.h p33EP512MC806.h Setup_commande.h setup_commande.c
	$(CC) -mcpu=33EP512MC806 -x c -c "setup_commande.c" -o"setup_commande.o" -g -Wall

main.o : ../../../../../../../../program\ files\ (x86)/microchip/mplab\ c30/include/stdarg.h ../../../../../../../../program\ files\ (x86)/microchip/mplab\ c30/include/stddef.h ../../../../../../../../program\ files\ (x86)/microchip/mplab\ c30/include/stdio.h dma.h can_chinook3.h can.h p33EP512MC806.h M_UART.h Global.h p33EP512MC806.h Setup_commande.h p33EP512MC806.h main.c
	$(CC) -mcpu=33EP512MC806 -x c -c "main.c" -o"main.o" -g -Wall

M_UART.o : M_OC.h Global.h p33EP512MC806.h M_UART.h M_UART.c
	$(CC) -mcpu=33EP512MC806 -x c -c "M_UART.c" -o"M_UART.o" -g -Wall

M_OC.o : Global.h p33EP512MC806.h M_OC.c
	$(CC) -mcpu=33EP512MC806 -x c -c "M_OC.c" -o"M_OC.o" -g -Wall

ADC.o : Global.h p33EP512MC806.h ADC.h ADC.c
	$(CC) -mcpu=33EP512MC806 -x c -c "ADC.c" -o"ADC.o" -g -Wall

can.o : dma.h Global.h p33EP512MC806.h Setup_commande.h ../../../../../../../../program\ files\ (x86)/microchip/mplab\ c30/include/stddef.h ../../../../../../../../program\ files\ (x86)/microchip/mplab\ c30/include/stdlib.h p33EP512MC806.h can_chinook3.h can.h can.c
	$(CC) -mcpu=33EP512MC806 -x c -c "can.c" -o"can.o" -g -Wall

dma.o : p33EP512MC806.h dma.h dma.c
	$(CC) -mcpu=33EP512MC806 -x c -c "dma.c" -o"dma.o" -g -Wall

clean : 
	$(RM) "ISR.o" "M_TMR.o" "setup_commande.o" "main.o" "M_UART.o" "M_OC.o" "ADC.o" "can.o" "dma.o" "Commande_moteur.cof" "Commande_moteur.hex"

