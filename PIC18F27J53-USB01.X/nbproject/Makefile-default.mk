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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app_device_cdc_basic.c src/app_led_usb_status.c src/usb_descriptors.c src/pic18f47j53_pim/adc.c src/pic18f47j53_pim/buttons.c src/pic18f47j53_pim/leds.c src/pic18f47j53_pim/system.c src/pic18f47j53_pim/usart.c src/PIC18F27J53-USB01.c src/usb/usb_device.c src/usb/usb_device_cdc.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app_device_cdc_basic.p1 ${OBJECTDIR}/src/app_led_usb_status.p1 ${OBJECTDIR}/src/usb_descriptors.p1 ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1 ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1 ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1 ${OBJECTDIR}/src/pic18f47j53_pim/system.p1 ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1 ${OBJECTDIR}/src/PIC18F27J53-USB01.p1 ${OBJECTDIR}/src/usb/usb_device.p1 ${OBJECTDIR}/src/usb/usb_device_cdc.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app_device_cdc_basic.p1.d ${OBJECTDIR}/src/app_led_usb_status.p1.d ${OBJECTDIR}/src/usb_descriptors.p1.d ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1.d ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1.d ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1.d ${OBJECTDIR}/src/pic18f47j53_pim/system.p1.d ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1.d ${OBJECTDIR}/src/PIC18F27J53-USB01.p1.d ${OBJECTDIR}/src/usb/usb_device.p1.d ${OBJECTDIR}/src/usb/usb_device_cdc.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app_device_cdc_basic.p1 ${OBJECTDIR}/src/app_led_usb_status.p1 ${OBJECTDIR}/src/usb_descriptors.p1 ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1 ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1 ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1 ${OBJECTDIR}/src/pic18f47j53_pim/system.p1 ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1 ${OBJECTDIR}/src/PIC18F27J53-USB01.p1 ${OBJECTDIR}/src/usb/usb_device.p1 ${OBJECTDIR}/src/usb/usb_device_cdc.p1

# Source Files
SOURCEFILES=src/app_device_cdc_basic.c src/app_led_usb_status.c src/usb_descriptors.c src/pic18f47j53_pim/adc.c src/pic18f47j53_pim/buttons.c src/pic18f47j53_pim/leds.c src/pic18f47j53_pim/system.c src/pic18f47j53_pim/usart.c src/PIC18F27J53-USB01.c src/usb/usb_device.c src/usb/usb_device_cdc.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F27J53
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/app_device_cdc_basic.p1: src/app_device_cdc_basic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_device_cdc_basic.p1.d 
	@${RM} ${OBJECTDIR}/src/app_device_cdc_basic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_device_cdc_basic.p1  src/app_device_cdc_basic.c 
	@-${MV} ${OBJECTDIR}/src/app_device_cdc_basic.d ${OBJECTDIR}/src/app_device_cdc_basic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_device_cdc_basic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_led_usb_status.p1: src/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/src/app_led_usb_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_led_usb_status.p1  src/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/src/app_led_usb_status.d ${OBJECTDIR}/src/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb_descriptors.p1: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/usb_descriptors.p1  src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/src/usb_descriptors.d ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/adc.p1: src/pic18f47j53_pim/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/adc.p1  src/pic18f47j53_pim/adc.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/adc.d ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1: src/pic18f47j53_pim/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1  src/pic18f47j53_pim/buttons.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.d ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/leds.p1: src/pic18f47j53_pim/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/leds.p1  src/pic18f47j53_pim/leds.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/leds.d ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/system.p1: src/pic18f47j53_pim/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/system.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/system.p1  src/pic18f47j53_pim/system.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/system.d ${OBJECTDIR}/src/pic18f47j53_pim/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/usart.p1: src/pic18f47j53_pim/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/usart.p1  src/pic18f47j53_pim/usart.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/usart.d ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/PIC18F27J53-USB01.p1: src/PIC18F27J53-USB01.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PIC18F27J53-USB01.p1.d 
	@${RM} ${OBJECTDIR}/src/PIC18F27J53-USB01.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/PIC18F27J53-USB01.p1  src/PIC18F27J53-USB01.c 
	@-${MV} ${OBJECTDIR}/src/PIC18F27J53-USB01.d ${OBJECTDIR}/src/PIC18F27J53-USB01.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/PIC18F27J53-USB01.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb/usb_device.p1: src/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/usb" 
	@${RM} ${OBJECTDIR}/src/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/src/usb/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/usb/usb_device.p1  src/usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/src/usb/usb_device.d ${OBJECTDIR}/src/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb/usb_device_cdc.p1: src/usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/usb" 
	@${RM} ${OBJECTDIR}/src/usb/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/src/usb/usb_device_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/usb/usb_device_cdc.p1  src/usb/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/src/usb/usb_device_cdc.d ${OBJECTDIR}/src/usb/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/app_device_cdc_basic.p1: src/app_device_cdc_basic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_device_cdc_basic.p1.d 
	@${RM} ${OBJECTDIR}/src/app_device_cdc_basic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_device_cdc_basic.p1  src/app_device_cdc_basic.c 
	@-${MV} ${OBJECTDIR}/src/app_device_cdc_basic.d ${OBJECTDIR}/src/app_device_cdc_basic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_device_cdc_basic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_led_usb_status.p1: src/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/src/app_led_usb_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_led_usb_status.p1  src/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/src/app_led_usb_status.d ${OBJECTDIR}/src/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb_descriptors.p1: src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/src/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/usb_descriptors.p1  src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/src/usb_descriptors.d ${OBJECTDIR}/src/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/adc.p1: src/pic18f47j53_pim/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/adc.p1  src/pic18f47j53_pim/adc.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/adc.d ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1: src/pic18f47j53_pim/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1  src/pic18f47j53_pim/buttons.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.d ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/leds.p1: src/pic18f47j53_pim/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/leds.p1  src/pic18f47j53_pim/leds.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/leds.d ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/system.p1: src/pic18f47j53_pim/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/system.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/system.p1  src/pic18f47j53_pim/system.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/system.d ${OBJECTDIR}/src/pic18f47j53_pim/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic18f47j53_pim/usart.p1: src/pic18f47j53_pim/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic18f47j53_pim" 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1.d 
	@${RM} ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/pic18f47j53_pim/usart.p1  src/pic18f47j53_pim/usart.c 
	@-${MV} ${OBJECTDIR}/src/pic18f47j53_pim/usart.d ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic18f47j53_pim/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/PIC18F27J53-USB01.p1: src/PIC18F27J53-USB01.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PIC18F27J53-USB01.p1.d 
	@${RM} ${OBJECTDIR}/src/PIC18F27J53-USB01.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/PIC18F27J53-USB01.p1  src/PIC18F27J53-USB01.c 
	@-${MV} ${OBJECTDIR}/src/PIC18F27J53-USB01.d ${OBJECTDIR}/src/PIC18F27J53-USB01.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/PIC18F27J53-USB01.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb/usb_device.p1: src/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/usb" 
	@${RM} ${OBJECTDIR}/src/usb/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/src/usb/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/usb/usb_device.p1  src/usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/src/usb/usb_device.d ${OBJECTDIR}/src/usb/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/usb/usb_device_cdc.p1: src/usb/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/usb" 
	@${RM} ${OBJECTDIR}/src/usb/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/src/usb/usb_device_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/usb/usb_device_cdc.p1  src/usb/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/src/usb/usb_device_cdc.d ${OBJECTDIR}/src/usb/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/usb/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"       --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/pic18f47j53_pim" -I"../My_header" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/PIC18F27J53-USB01.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
