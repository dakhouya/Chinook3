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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=CMD.c M_ADC.c M_ISR.c M_PWM.c M_QEI.c M_TMR.c M_UART.c Main.c can.c dma.c chinookpack_unpack.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/CMD.o ${OBJECTDIR}/M_ADC.o ${OBJECTDIR}/M_ISR.o ${OBJECTDIR}/M_PWM.o ${OBJECTDIR}/M_QEI.o ${OBJECTDIR}/M_TMR.o ${OBJECTDIR}/M_UART.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/can.o ${OBJECTDIR}/dma.o ${OBJECTDIR}/chinookpack_unpack.o
POSSIBLE_DEPFILES=${OBJECTDIR}/CMD.o.d ${OBJECTDIR}/M_ADC.o.d ${OBJECTDIR}/M_ISR.o.d ${OBJECTDIR}/M_PWM.o.d ${OBJECTDIR}/M_QEI.o.d ${OBJECTDIR}/M_TMR.o.d ${OBJECTDIR}/M_UART.o.d ${OBJECTDIR}/Main.o.d ${OBJECTDIR}/can.o.d ${OBJECTDIR}/dma.o.d ${OBJECTDIR}/chinookpack_unpack.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/CMD.o ${OBJECTDIR}/M_ADC.o ${OBJECTDIR}/M_ISR.o ${OBJECTDIR}/M_PWM.o ${OBJECTDIR}/M_QEI.o ${OBJECTDIR}/M_TMR.o ${OBJECTDIR}/M_UART.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/can.o ${OBJECTDIR}/dma.o ${OBJECTDIR}/chinookpack_unpack.o

# Source Files
SOURCEFILES=CMD.c M_ADC.c M_ISR.c M_PWM.c M_QEI.c M_TMR.c M_UART.c Main.c can.c dma.c chinookpack_unpack.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MU810
MP_LINKER_FILE_OPTION=,-Tp33EP512MU810.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/CMD.o: CMD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CMD.o.d 
	@${RM} ${OBJECTDIR}/CMD.o.ok ${OBJECTDIR}/CMD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/CMD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CMD.o.d" -o ${OBJECTDIR}/CMD.o CMD.c     --std=gnu99
	
${OBJECTDIR}/M_ADC.o: M_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_ADC.o.d 
	@${RM} ${OBJECTDIR}/M_ADC.o.ok ${OBJECTDIR}/M_ADC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_ADC.o.d" -o ${OBJECTDIR}/M_ADC.o M_ADC.c     --std=gnu99
	
${OBJECTDIR}/M_ISR.o: M_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_ISR.o.d 
	@${RM} ${OBJECTDIR}/M_ISR.o.ok ${OBJECTDIR}/M_ISR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_ISR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_ISR.o.d" -o ${OBJECTDIR}/M_ISR.o M_ISR.c     --std=gnu99
	
${OBJECTDIR}/M_PWM.o: M_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_PWM.o.d 
	@${RM} ${OBJECTDIR}/M_PWM.o.ok ${OBJECTDIR}/M_PWM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_PWM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_PWM.o.d" -o ${OBJECTDIR}/M_PWM.o M_PWM.c     --std=gnu99
	
${OBJECTDIR}/M_QEI.o: M_QEI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_QEI.o.d 
	@${RM} ${OBJECTDIR}/M_QEI.o.ok ${OBJECTDIR}/M_QEI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_QEI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_QEI.o.d" -o ${OBJECTDIR}/M_QEI.o M_QEI.c     --std=gnu99
	
${OBJECTDIR}/M_TMR.o: M_TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_TMR.o.d 
	@${RM} ${OBJECTDIR}/M_TMR.o.ok ${OBJECTDIR}/M_TMR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_TMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_TMR.o.d" -o ${OBJECTDIR}/M_TMR.o M_TMR.c     --std=gnu99
	
${OBJECTDIR}/M_UART.o: M_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_UART.o.d 
	@${RM} ${OBJECTDIR}/M_UART.o.ok ${OBJECTDIR}/M_UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_UART.o.d" -o ${OBJECTDIR}/M_UART.o M_UART.c     --std=gnu99
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o.ok ${OBJECTDIR}/Main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c     --std=gnu99
	
${OBJECTDIR}/can.o: can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/can.o.d 
	@${RM} ${OBJECTDIR}/can.o.ok ${OBJECTDIR}/can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/can.o.d" -o ${OBJECTDIR}/can.o can.c     --std=gnu99
	
${OBJECTDIR}/dma.o: dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/dma.o.d 
	@${RM} ${OBJECTDIR}/dma.o.ok ${OBJECTDIR}/dma.o.err 
	@${FIXDEPS} "${OBJECTDIR}/dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dma.o.d" -o ${OBJECTDIR}/dma.o dma.c     --std=gnu99
	
${OBJECTDIR}/chinookpack_unpack.o: chinookpack_unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/chinookpack_unpack.o.d 
	@${RM} ${OBJECTDIR}/chinookpack_unpack.o.ok ${OBJECTDIR}/chinookpack_unpack.o.err 
	@${FIXDEPS} "${OBJECTDIR}/chinookpack_unpack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/chinookpack_unpack.o.d" -o ${OBJECTDIR}/chinookpack_unpack.o chinookpack_unpack.c     --std=gnu99
	
else
${OBJECTDIR}/CMD.o: CMD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/CMD.o.d 
	@${RM} ${OBJECTDIR}/CMD.o.ok ${OBJECTDIR}/CMD.o.err 
	@${FIXDEPS} "${OBJECTDIR}/CMD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/CMD.o.d" -o ${OBJECTDIR}/CMD.o CMD.c     --std=gnu99
	
${OBJECTDIR}/M_ADC.o: M_ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_ADC.o.d 
	@${RM} ${OBJECTDIR}/M_ADC.o.ok ${OBJECTDIR}/M_ADC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_ADC.o.d" -o ${OBJECTDIR}/M_ADC.o M_ADC.c     --std=gnu99
	
${OBJECTDIR}/M_ISR.o: M_ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_ISR.o.d 
	@${RM} ${OBJECTDIR}/M_ISR.o.ok ${OBJECTDIR}/M_ISR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_ISR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_ISR.o.d" -o ${OBJECTDIR}/M_ISR.o M_ISR.c     --std=gnu99
	
${OBJECTDIR}/M_PWM.o: M_PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_PWM.o.d 
	@${RM} ${OBJECTDIR}/M_PWM.o.ok ${OBJECTDIR}/M_PWM.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_PWM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_PWM.o.d" -o ${OBJECTDIR}/M_PWM.o M_PWM.c     --std=gnu99
	
${OBJECTDIR}/M_QEI.o: M_QEI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_QEI.o.d 
	@${RM} ${OBJECTDIR}/M_QEI.o.ok ${OBJECTDIR}/M_QEI.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_QEI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_QEI.o.d" -o ${OBJECTDIR}/M_QEI.o M_QEI.c     --std=gnu99
	
${OBJECTDIR}/M_TMR.o: M_TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_TMR.o.d 
	@${RM} ${OBJECTDIR}/M_TMR.o.ok ${OBJECTDIR}/M_TMR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_TMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_TMR.o.d" -o ${OBJECTDIR}/M_TMR.o M_TMR.c     --std=gnu99
	
${OBJECTDIR}/M_UART.o: M_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/M_UART.o.d 
	@${RM} ${OBJECTDIR}/M_UART.o.ok ${OBJECTDIR}/M_UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/M_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/M_UART.o.d" -o ${OBJECTDIR}/M_UART.o M_UART.c     --std=gnu99
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o.ok ${OBJECTDIR}/Main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c     --std=gnu99
	
${OBJECTDIR}/can.o: can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/can.o.d 
	@${RM} ${OBJECTDIR}/can.o.ok ${OBJECTDIR}/can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/can.o.d" -o ${OBJECTDIR}/can.o can.c     --std=gnu99
	
${OBJECTDIR}/dma.o: dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/dma.o.d 
	@${RM} ${OBJECTDIR}/dma.o.ok ${OBJECTDIR}/dma.o.err 
	@${FIXDEPS} "${OBJECTDIR}/dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dma.o.d" -o ${OBJECTDIR}/dma.o dma.c     --std=gnu99
	
${OBJECTDIR}/chinookpack_unpack.o: chinookpack_unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/chinookpack_unpack.o.d 
	@${RM} ${OBJECTDIR}/chinookpack_unpack.o.ok ${OBJECTDIR}/chinookpack_unpack.o.err 
	@${FIXDEPS} "${OBJECTDIR}/chinookpack_unpack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/chinookpack_unpack.o.d" -o ${OBJECTDIR}/chinookpack_unpack.o chinookpack_unpack.c     --std=gnu99
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Vincere_Ventus.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
