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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../ISR.c ../M_TMR.c ../setup_commande.c ../main.c ../M_UART.c ../M_OC.c ../ADC.c ../can.c ../dma.c ../chinookpack_unpack.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/ISR.o ${OBJECTDIR}/_ext/1472/M_TMR.o ${OBJECTDIR}/_ext/1472/setup_commande.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/M_UART.o ${OBJECTDIR}/_ext/1472/M_OC.o ${OBJECTDIR}/_ext/1472/ADC.o ${OBJECTDIR}/_ext/1472/can.o ${OBJECTDIR}/_ext/1472/dma.o ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/ISR.o.d ${OBJECTDIR}/_ext/1472/M_TMR.o.d ${OBJECTDIR}/_ext/1472/setup_commande.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/M_UART.o.d ${OBJECTDIR}/_ext/1472/M_OC.o.d ${OBJECTDIR}/_ext/1472/ADC.o.d ${OBJECTDIR}/_ext/1472/can.o.d ${OBJECTDIR}/_ext/1472/dma.o.d ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/ISR.o ${OBJECTDIR}/_ext/1472/M_TMR.o ${OBJECTDIR}/_ext/1472/setup_commande.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/M_UART.o ${OBJECTDIR}/_ext/1472/M_OC.o ${OBJECTDIR}/_ext/1472/ADC.o ${OBJECTDIR}/_ext/1472/can.o ${OBJECTDIR}/_ext/1472/dma.o ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o

# Source Files
SOURCEFILES=../ISR.c ../M_TMR.c ../setup_commande.c ../main.c ../M_UART.c ../M_OC.c ../ADC.c ../can.c ../dma.c ../chinookpack_unpack.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MC806
MP_LINKER_FILE_OPTION=,-Tp33EP512MC806.gld
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
${OBJECTDIR}/_ext/1472/ISR.o: ../ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ISR.o.ok ${OBJECTDIR}/_ext/1472/ISR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ISR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/ISR.o.d" -o ${OBJECTDIR}/_ext/1472/ISR.o ../ISR.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/M_TMR.o: ../M_TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/M_TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/M_TMR.o.ok ${OBJECTDIR}/_ext/1472/M_TMR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/M_TMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/M_TMR.o.d" -o ${OBJECTDIR}/_ext/1472/M_TMR.o ../M_TMR.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/setup_commande.o: ../setup_commande.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/setup_commande.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/setup_commande.o.ok ${OBJECTDIR}/_ext/1472/setup_commande.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/setup_commande.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/setup_commande.o.d" -o ${OBJECTDIR}/_ext/1472/setup_commande.o ../setup_commande.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.ok ${OBJECTDIR}/_ext/1472/main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/M_UART.o: ../M_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/M_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/M_UART.o.ok ${OBJECTDIR}/_ext/1472/M_UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/M_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/M_UART.o.d" -o ${OBJECTDIR}/_ext/1472/M_UART.o ../M_UART.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/M_OC.o: ../M_OC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/M_OC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/M_OC.o.ok ${OBJECTDIR}/_ext/1472/M_OC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/M_OC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/M_OC.o.d" -o ${OBJECTDIR}/_ext/1472/M_OC.o ../M_OC.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/ADC.o: ../ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o.ok ${OBJECTDIR}/_ext/1472/ADC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/ADC.o.d" -o ${OBJECTDIR}/_ext/1472/ADC.o ../ADC.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/can.o: ../can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o.ok ${OBJECTDIR}/_ext/1472/can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/can.o.d" -o ${OBJECTDIR}/_ext/1472/can.o ../can.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/dma.o: ../dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/dma.o.ok ${OBJECTDIR}/_ext/1472/dma.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/dma.o.d" -o ${OBJECTDIR}/_ext/1472/dma.o ../dma.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/chinookpack_unpack.o: ../chinookpack_unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.ok ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.d" -o ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o ../chinookpack_unpack.c     --std=gnu99
	
else
${OBJECTDIR}/_ext/1472/ISR.o: ../ISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/ISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ISR.o.ok ${OBJECTDIR}/_ext/1472/ISR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ISR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/ISR.o.d" -o ${OBJECTDIR}/_ext/1472/ISR.o ../ISR.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/M_TMR.o: ../M_TMR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/M_TMR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/M_TMR.o.ok ${OBJECTDIR}/_ext/1472/M_TMR.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/M_TMR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/M_TMR.o.d" -o ${OBJECTDIR}/_ext/1472/M_TMR.o ../M_TMR.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/setup_commande.o: ../setup_commande.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/setup_commande.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/setup_commande.o.ok ${OBJECTDIR}/_ext/1472/setup_commande.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/setup_commande.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/setup_commande.o.d" -o ${OBJECTDIR}/_ext/1472/setup_commande.o ../setup_commande.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.ok ${OBJECTDIR}/_ext/1472/main.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/M_UART.o: ../M_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/M_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/M_UART.o.ok ${OBJECTDIR}/_ext/1472/M_UART.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/M_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/M_UART.o.d" -o ${OBJECTDIR}/_ext/1472/M_UART.o ../M_UART.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/M_OC.o: ../M_OC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/M_OC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/M_OC.o.ok ${OBJECTDIR}/_ext/1472/M_OC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/M_OC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/M_OC.o.d" -o ${OBJECTDIR}/_ext/1472/M_OC.o ../M_OC.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/ADC.o: ../ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/ADC.o.ok ${OBJECTDIR}/_ext/1472/ADC.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/ADC.o.d" -o ${OBJECTDIR}/_ext/1472/ADC.o ../ADC.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/can.o: ../can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o.ok ${OBJECTDIR}/_ext/1472/can.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/can.o.d" -o ${OBJECTDIR}/_ext/1472/can.o ../can.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/dma.o: ../dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/dma.o.ok ${OBJECTDIR}/_ext/1472/dma.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/dma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/dma.o.d" -o ${OBJECTDIR}/_ext/1472/dma.o ../dma.c     --std=gnu99
	
${OBJECTDIR}/_ext/1472/chinookpack_unpack.o: ../chinookpack_unpack.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.ok ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/chinookpack_unpack.o.d" -o ${OBJECTDIR}/_ext/1472/chinookpack_unpack.o ../chinookpack_unpack.c     --std=gnu99
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"..",-Map="${DISTDIR}/Commande_moteur.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,-L"..",-Map="${DISTDIR}/Commande_moteur.X.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Commande_moteur.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
