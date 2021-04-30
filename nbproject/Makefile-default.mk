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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Main.c Initial.c G5_Function.c Function.c G5_Interrupt_Fuction.c timer1.c I2C_LCD.c I2C_Interrupt.c Ele_load_Interrupt.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Main.o ${OBJECTDIR}/Initial.o ${OBJECTDIR}/G5_Function.o ${OBJECTDIR}/Function.o ${OBJECTDIR}/G5_Interrupt_Fuction.o ${OBJECTDIR}/timer1.o ${OBJECTDIR}/I2C_LCD.o ${OBJECTDIR}/I2C_Interrupt.o ${OBJECTDIR}/Ele_load_Interrupt.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Main.o.d ${OBJECTDIR}/Initial.o.d ${OBJECTDIR}/G5_Function.o.d ${OBJECTDIR}/Function.o.d ${OBJECTDIR}/G5_Interrupt_Fuction.o.d ${OBJECTDIR}/timer1.o.d ${OBJECTDIR}/I2C_LCD.o.d ${OBJECTDIR}/I2C_Interrupt.o.d ${OBJECTDIR}/Ele_load_Interrupt.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Main.o ${OBJECTDIR}/Initial.o ${OBJECTDIR}/G5_Function.o ${OBJECTDIR}/Function.o ${OBJECTDIR}/G5_Interrupt_Fuction.o ${OBJECTDIR}/timer1.o ${OBJECTDIR}/I2C_LCD.o ${OBJECTDIR}/I2C_Interrupt.o ${OBJECTDIR}/Ele_load_Interrupt.o

# Source Files
SOURCEFILES=Main.c Initial.c G5_Function.c Function.c G5_Interrupt_Fuction.c timer1.c I2C_LCD.c I2C_Interrupt.c Ele_load_Interrupt.c



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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GA106
MP_LINKER_FILE_OPTION=,-Tp24FJ128GA106.gld
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
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o.ok ${OBJECTDIR}/Main.o.err 
	@${RM} ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c    -legacy-libc
	
${OBJECTDIR}/Initial.o: Initial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Initial.o.d 
	@${RM} ${OBJECTDIR}/Initial.o.ok ${OBJECTDIR}/Initial.o.err 
	@${RM} ${OBJECTDIR}/Initial.o 
	@${FIXDEPS} "${OBJECTDIR}/Initial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Initial.o.d" -o ${OBJECTDIR}/Initial.o Initial.c    -legacy-libc
	
${OBJECTDIR}/G5_Function.o: G5_Function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/G5_Function.o.d 
	@${RM} ${OBJECTDIR}/G5_Function.o.ok ${OBJECTDIR}/G5_Function.o.err 
	@${RM} ${OBJECTDIR}/G5_Function.o 
	@${FIXDEPS} "${OBJECTDIR}/G5_Function.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/G5_Function.o.d" -o ${OBJECTDIR}/G5_Function.o G5_Function.c    -legacy-libc
	
${OBJECTDIR}/Function.o: Function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Function.o.d 
	@${RM} ${OBJECTDIR}/Function.o.ok ${OBJECTDIR}/Function.o.err 
	@${RM} ${OBJECTDIR}/Function.o 
	@${FIXDEPS} "${OBJECTDIR}/Function.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Function.o.d" -o ${OBJECTDIR}/Function.o Function.c    -legacy-libc
	
${OBJECTDIR}/G5_Interrupt_Fuction.o: G5_Interrupt_Fuction.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/G5_Interrupt_Fuction.o.d 
	@${RM} ${OBJECTDIR}/G5_Interrupt_Fuction.o.ok ${OBJECTDIR}/G5_Interrupt_Fuction.o.err 
	@${RM} ${OBJECTDIR}/G5_Interrupt_Fuction.o 
	@${FIXDEPS} "${OBJECTDIR}/G5_Interrupt_Fuction.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/G5_Interrupt_Fuction.o.d" -o ${OBJECTDIR}/G5_Interrupt_Fuction.o G5_Interrupt_Fuction.c    -legacy-libc
	
${OBJECTDIR}/timer1.o: timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer1.o.d 
	@${RM} ${OBJECTDIR}/timer1.o.ok ${OBJECTDIR}/timer1.o.err 
	@${RM} ${OBJECTDIR}/timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/timer1.o.d" -o ${OBJECTDIR}/timer1.o timer1.c    -legacy-libc
	
${OBJECTDIR}/I2C_LCD.o: I2C_LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.d 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.ok ${OBJECTDIR}/I2C_LCD.o.err 
	@${RM} ${OBJECTDIR}/I2C_LCD.o 
	@${FIXDEPS} "${OBJECTDIR}/I2C_LCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/I2C_LCD.o.d" -o ${OBJECTDIR}/I2C_LCD.o I2C_LCD.c    -legacy-libc
	
${OBJECTDIR}/I2C_Interrupt.o: I2C_Interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_Interrupt.o.d 
	@${RM} ${OBJECTDIR}/I2C_Interrupt.o.ok ${OBJECTDIR}/I2C_Interrupt.o.err 
	@${RM} ${OBJECTDIR}/I2C_Interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/I2C_Interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/I2C_Interrupt.o.d" -o ${OBJECTDIR}/I2C_Interrupt.o I2C_Interrupt.c    -legacy-libc
	
${OBJECTDIR}/Ele_load_Interrupt.o: Ele_load_Interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Ele_load_Interrupt.o.d 
	@${RM} ${OBJECTDIR}/Ele_load_Interrupt.o.ok ${OBJECTDIR}/Ele_load_Interrupt.o.err 
	@${RM} ${OBJECTDIR}/Ele_load_Interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/Ele_load_Interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Ele_load_Interrupt.o.d" -o ${OBJECTDIR}/Ele_load_Interrupt.o Ele_load_Interrupt.c    -legacy-libc
	
else
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o.ok ${OBJECTDIR}/Main.o.err 
	@${RM} ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Main.o.d" -o ${OBJECTDIR}/Main.o Main.c    -legacy-libc
	
${OBJECTDIR}/Initial.o: Initial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Initial.o.d 
	@${RM} ${OBJECTDIR}/Initial.o.ok ${OBJECTDIR}/Initial.o.err 
	@${RM} ${OBJECTDIR}/Initial.o 
	@${FIXDEPS} "${OBJECTDIR}/Initial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Initial.o.d" -o ${OBJECTDIR}/Initial.o Initial.c    -legacy-libc
	
${OBJECTDIR}/G5_Function.o: G5_Function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/G5_Function.o.d 
	@${RM} ${OBJECTDIR}/G5_Function.o.ok ${OBJECTDIR}/G5_Function.o.err 
	@${RM} ${OBJECTDIR}/G5_Function.o 
	@${FIXDEPS} "${OBJECTDIR}/G5_Function.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/G5_Function.o.d" -o ${OBJECTDIR}/G5_Function.o G5_Function.c    -legacy-libc
	
${OBJECTDIR}/Function.o: Function.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Function.o.d 
	@${RM} ${OBJECTDIR}/Function.o.ok ${OBJECTDIR}/Function.o.err 
	@${RM} ${OBJECTDIR}/Function.o 
	@${FIXDEPS} "${OBJECTDIR}/Function.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Function.o.d" -o ${OBJECTDIR}/Function.o Function.c    -legacy-libc
	
${OBJECTDIR}/G5_Interrupt_Fuction.o: G5_Interrupt_Fuction.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/G5_Interrupt_Fuction.o.d 
	@${RM} ${OBJECTDIR}/G5_Interrupt_Fuction.o.ok ${OBJECTDIR}/G5_Interrupt_Fuction.o.err 
	@${RM} ${OBJECTDIR}/G5_Interrupt_Fuction.o 
	@${FIXDEPS} "${OBJECTDIR}/G5_Interrupt_Fuction.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/G5_Interrupt_Fuction.o.d" -o ${OBJECTDIR}/G5_Interrupt_Fuction.o G5_Interrupt_Fuction.c    -legacy-libc
	
${OBJECTDIR}/timer1.o: timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer1.o.d 
	@${RM} ${OBJECTDIR}/timer1.o.ok ${OBJECTDIR}/timer1.o.err 
	@${RM} ${OBJECTDIR}/timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/timer1.o.d" -o ${OBJECTDIR}/timer1.o timer1.c    -legacy-libc
	
${OBJECTDIR}/I2C_LCD.o: I2C_LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.d 
	@${RM} ${OBJECTDIR}/I2C_LCD.o.ok ${OBJECTDIR}/I2C_LCD.o.err 
	@${RM} ${OBJECTDIR}/I2C_LCD.o 
	@${FIXDEPS} "${OBJECTDIR}/I2C_LCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/I2C_LCD.o.d" -o ${OBJECTDIR}/I2C_LCD.o I2C_LCD.c    -legacy-libc
	
${OBJECTDIR}/I2C_Interrupt.o: I2C_Interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_Interrupt.o.d 
	@${RM} ${OBJECTDIR}/I2C_Interrupt.o.ok ${OBJECTDIR}/I2C_Interrupt.o.err 
	@${RM} ${OBJECTDIR}/I2C_Interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/I2C_Interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/I2C_Interrupt.o.d" -o ${OBJECTDIR}/I2C_Interrupt.o I2C_Interrupt.c    -legacy-libc
	
${OBJECTDIR}/Ele_load_Interrupt.o: Ele_load_Interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Ele_load_Interrupt.o.d 
	@${RM} ${OBJECTDIR}/Ele_load_Interrupt.o.ok ${OBJECTDIR}/Ele_load_Interrupt.o.err 
	@${RM} ${OBJECTDIR}/Ele_load_Interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/Ele_load_Interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -MMD -MF "${OBJECTDIR}/Ele_load_Interrupt.o.d" -o ${OBJECTDIR}/Ele_load_Interrupt.o Ele_load_Interrupt.c    -legacy-libc
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -legacy-libc -Wl,--defsym=__MPLAB_BUILD=1,--stack=16,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}        -legacy-libc -Wl,--defsym=__MPLAB_BUILD=1,--stack=16,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/G5_Chaggerrrr.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
