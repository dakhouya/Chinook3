#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/lib/currentmonitor/ltc4151.o ${OBJECTDIR}/lib/dspic/can/can.o ${OBJECTDIR}/lib/dspic/dma/dma.o ${OBJECTDIR}/lib/dspic/i2c/i2c.o ${OBJECTDIR}/lib/dspic/timer/timer.o ${OBJECTDIR}/lib/dspic/uart/uart.o ${OBJECTDIR}/lib/eeprom/cat24c256w.o ${OBJECTDIR}/lib/rtc/ds1338.o ${OBJECTDIR}/lib/skadi/skadi.o ${OBJECTDIR}/lib/chinookpack_unpack.o ${OBJECTDIR}/fujin.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/lib/currentmonitor/ltc4151.o.d ${OBJECTDIR}/lib/dspic/can/can.o.d ${OBJECTDIR}/lib/dspic/dma/dma.o.d ${OBJECTDIR}/lib/dspic/i2c/i2c.o.d ${OBJECTDIR}/lib/dspic/timer/timer.o.d ${OBJECTDIR}/lib/dspic/uart/uart.o.d ${OBJECTDIR}/lib/eeprom/cat24c256w.o.d ${OBJECTDIR}/lib/rtc/ds1338.o.d ${OBJECTDIR}/lib/skadi/skadi.o.d ${OBJECTDIR}/lib/chinookpack_unpack.o.d ${OBJECTDIR}/fujin.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/lib/currentmonitor/ltc4151.o ${OBJECTDIR}/lib/dspic/can/can.o ${OBJECTDIR}/lib/dspic/dma/dma.o ${OBJECTDIR}/lib/dspic/i2c/i2c.o ${OBJECTDIR}/lib/dspic/timer/timer.o ${OBJECTDIR}/lib/dspic/uart/uart.o ${OBJECTDIR}/lib/eeprom/cat24c256w.o ${OBJECTDIR}/lib/rtc/ds1338.o ${OBJECTDIR}/lib/skadi/skadi.o ${OBJECTDIR}/lib/chinookpack_unpack.o ${OBJECTDIR}/fujin.o ${OBJECTDIR}/main.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MC806
MP_LINKER_FILE_OPTION=,--script=p33EP512MC806.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/lib/currentmonitor/ltc4151.o: lib/currentmonitor/ltc4151.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/currentmonitor 
	@${RM} ${OBJECTDIR}/lib/currentmonitor/ltc4151.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/currentmonitor/ltc4151.c  -o ${OBJECTDIR}/lib/currentmonitor/ltc4151.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/currentmonitor/ltc4151.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/currentmonitor/ltc4151.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/can/can.o: lib/dspic/can/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/can 
	@${RM} ${OBJECTDIR}/lib/dspic/can/can.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/can/can.c  -o ${OBJECTDIR}/lib/dspic/can/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/can/can.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/can/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/dma/dma.o: lib/dspic/dma/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/dma 
	@${RM} ${OBJECTDIR}/lib/dspic/dma/dma.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/dma/dma.c  -o ${OBJECTDIR}/lib/dspic/dma/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/dma/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/dma/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/i2c/i2c.o: lib/dspic/i2c/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/i2c 
	@${RM} ${OBJECTDIR}/lib/dspic/i2c/i2c.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/i2c/i2c.c  -o ${OBJECTDIR}/lib/dspic/i2c/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/i2c/i2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/i2c/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/timer/timer.o: lib/dspic/timer/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/timer 
	@${RM} ${OBJECTDIR}/lib/dspic/timer/timer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/timer/timer.c  -o ${OBJECTDIR}/lib/dspic/timer/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/timer/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/timer/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/uart/uart.o: lib/dspic/uart/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/uart 
	@${RM} ${OBJECTDIR}/lib/dspic/uart/uart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/uart/uart.c  -o ${OBJECTDIR}/lib/dspic/uart/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/uart/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/uart/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/eeprom/cat24c256w.o: lib/eeprom/cat24c256w.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/eeprom 
	@${RM} ${OBJECTDIR}/lib/eeprom/cat24c256w.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/eeprom/cat24c256w.c  -o ${OBJECTDIR}/lib/eeprom/cat24c256w.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/eeprom/cat24c256w.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/eeprom/cat24c256w.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/rtc/ds1338.o: lib/rtc/ds1338.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/rtc 
	@${RM} ${OBJECTDIR}/lib/rtc/ds1338.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/rtc/ds1338.c  -o ${OBJECTDIR}/lib/rtc/ds1338.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/rtc/ds1338.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/rtc/ds1338.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/skadi/skadi.o: lib/skadi/skadi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/skadi 
	@${RM} ${OBJECTDIR}/lib/skadi/skadi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/skadi/skadi.c  -o ${OBJECTDIR}/lib/skadi/skadi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/skadi/skadi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/skadi/skadi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/chinookpack_unpack.o: lib/chinookpack_unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib 
	@${RM} ${OBJECTDIR}/lib/chinookpack_unpack.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/chinookpack_unpack.c  -o ${OBJECTDIR}/lib/chinookpack_unpack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/chinookpack_unpack.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/chinookpack_unpack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/fujin.o: fujin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/fujin.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  fujin.c  -o ${OBJECTDIR}/fujin.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/fujin.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/fujin.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/lib/currentmonitor/ltc4151.o: lib/currentmonitor/ltc4151.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/currentmonitor 
	@${RM} ${OBJECTDIR}/lib/currentmonitor/ltc4151.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/currentmonitor/ltc4151.c  -o ${OBJECTDIR}/lib/currentmonitor/ltc4151.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/currentmonitor/ltc4151.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/currentmonitor/ltc4151.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/can/can.o: lib/dspic/can/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/can 
	@${RM} ${OBJECTDIR}/lib/dspic/can/can.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/can/can.c  -o ${OBJECTDIR}/lib/dspic/can/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/can/can.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/can/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/dma/dma.o: lib/dspic/dma/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/dma 
	@${RM} ${OBJECTDIR}/lib/dspic/dma/dma.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/dma/dma.c  -o ${OBJECTDIR}/lib/dspic/dma/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/dma/dma.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/dma/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/i2c/i2c.o: lib/dspic/i2c/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/i2c 
	@${RM} ${OBJECTDIR}/lib/dspic/i2c/i2c.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/i2c/i2c.c  -o ${OBJECTDIR}/lib/dspic/i2c/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/i2c/i2c.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/i2c/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/timer/timer.o: lib/dspic/timer/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/timer 
	@${RM} ${OBJECTDIR}/lib/dspic/timer/timer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/timer/timer.c  -o ${OBJECTDIR}/lib/dspic/timer/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/timer/timer.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/timer/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/dspic/uart/uart.o: lib/dspic/uart/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/dspic/uart 
	@${RM} ${OBJECTDIR}/lib/dspic/uart/uart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/dspic/uart/uart.c  -o ${OBJECTDIR}/lib/dspic/uart/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/dspic/uart/uart.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/dspic/uart/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/eeprom/cat24c256w.o: lib/eeprom/cat24c256w.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/eeprom 
	@${RM} ${OBJECTDIR}/lib/eeprom/cat24c256w.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/eeprom/cat24c256w.c  -o ${OBJECTDIR}/lib/eeprom/cat24c256w.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/eeprom/cat24c256w.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/eeprom/cat24c256w.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/rtc/ds1338.o: lib/rtc/ds1338.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/rtc 
	@${RM} ${OBJECTDIR}/lib/rtc/ds1338.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/rtc/ds1338.c  -o ${OBJECTDIR}/lib/rtc/ds1338.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/rtc/ds1338.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/rtc/ds1338.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/skadi/skadi.o: lib/skadi/skadi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib/skadi 
	@${RM} ${OBJECTDIR}/lib/skadi/skadi.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/skadi/skadi.c  -o ${OBJECTDIR}/lib/skadi/skadi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/skadi/skadi.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/skadi/skadi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/lib/chinookpack_unpack.o: lib/chinookpack_unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/lib 
	@${RM} ${OBJECTDIR}/lib/chinookpack_unpack.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib/chinookpack_unpack.c  -o ${OBJECTDIR}/lib/chinookpack_unpack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/lib/chinookpack_unpack.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/lib/chinookpack_unpack.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/fujin.o: fujin.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/fujin.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  fujin.c  -o ${OBJECTDIR}/fujin.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/fujin.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/fujin.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dspic.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
