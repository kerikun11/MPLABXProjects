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
ifeq "$(wildcard nbproject/Makefile-local-LPCUSBDK_16F1459.mk)" "nbproject/Makefile-local-LPCUSBDK_16F1459.mk"
include nbproject/Makefile-local-LPCUSBDK_16F1459.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=LPCUSBDK_16F1459
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/low_pin_count_usb_development_kit/pic16f1459/system.c ../src/app_device_cdc_basic.c ../src/app_led_usb_status.c ../src/main.c ../src/usb_descriptors.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/adc.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/buttons.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/leds.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/usart.c ../../../../../../framework/usb/src/usb_device.c ../../../../../../framework/usb/src/usb_device_cdc.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/115382418/system.p1 ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1 ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 ${OBJECTDIR}/_ext/1333569941/adc.p1 ${OBJECTDIR}/_ext/1333569941/buttons.p1 ${OBJECTDIR}/_ext/1333569941/leds.p1 ${OBJECTDIR}/_ext/1333569941/usart.p1 ${OBJECTDIR}/_ext/838585624/usb_device.p1 ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/115382418/system.p1.d ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1.d ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d ${OBJECTDIR}/_ext/1360937237/main.p1.d ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d ${OBJECTDIR}/_ext/1333569941/adc.p1.d ${OBJECTDIR}/_ext/1333569941/buttons.p1.d ${OBJECTDIR}/_ext/1333569941/leds.p1.d ${OBJECTDIR}/_ext/1333569941/usart.p1.d ${OBJECTDIR}/_ext/838585624/usb_device.p1.d ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/115382418/system.p1 ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1 ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 ${OBJECTDIR}/_ext/1360937237/main.p1 ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 ${OBJECTDIR}/_ext/1333569941/adc.p1 ${OBJECTDIR}/_ext/1333569941/buttons.p1 ${OBJECTDIR}/_ext/1333569941/leds.p1 ${OBJECTDIR}/_ext/1333569941/usart.p1 ${OBJECTDIR}/_ext/838585624/usb_device.p1 ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1

# Source Files
SOURCEFILES=../src/system_config/low_pin_count_usb_development_kit/pic16f1459/system.c ../src/app_device_cdc_basic.c ../src/app_led_usb_status.c ../src/main.c ../src/usb_descriptors.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/adc.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/buttons.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/leds.c ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/usart.c ../../../../../../framework/usb/src/usb_device.c ../../../../../../framework/usb/src/usb_device_cdc.c


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
	${MAKE}  -f nbproject/Makefile-LPCUSBDK_16F1459.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F1459
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/115382418/system.p1: ../src/system_config/low_pin_count_usb_development_kit/pic16f1459/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/115382418" 
	@${RM} ${OBJECTDIR}/_ext/115382418/system.p1.d 
	@${RM} ${OBJECTDIR}/_ext/115382418/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/115382418/system.p1  ../src/system_config/low_pin_count_usb_development_kit/pic16f1459/system.c 
	@-${MV} ${OBJECTDIR}/_ext/115382418/system.d ${OBJECTDIR}/_ext/115382418/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/115382418/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1: ../src/app_device_cdc_basic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1  ../src/app_device_cdc_basic.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.d ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1: ../src/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1  ../src/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.d ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/main.p1  ../src/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/main.d ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1: ../src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1  ../src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.d ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/adc.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/adc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/adc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/adc.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/adc.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/adc.d ${OBJECTDIR}/_ext/1333569941/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/buttons.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/buttons.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/buttons.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/buttons.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/buttons.d ${OBJECTDIR}/_ext/1333569941/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/leds.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/leds.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/leds.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/leds.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/leds.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/leds.d ${OBJECTDIR}/_ext/1333569941/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/usart.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/usart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/usart.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/usart.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/usart.d ${OBJECTDIR}/_ext/1333569941/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device.p1: ../../../../../../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device.p1  ../../../../../../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device.d ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1: ../../../../../../framework/usb/src/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1  ../../../../../../framework/usb/src/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.d ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/115382418/system.p1: ../src/system_config/low_pin_count_usb_development_kit/pic16f1459/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/115382418" 
	@${RM} ${OBJECTDIR}/_ext/115382418/system.p1.d 
	@${RM} ${OBJECTDIR}/_ext/115382418/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/115382418/system.p1  ../src/system_config/low_pin_count_usb_development_kit/pic16f1459/system.c 
	@-${MV} ${OBJECTDIR}/_ext/115382418/system.d ${OBJECTDIR}/_ext/115382418/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/115382418/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1: ../src/app_device_cdc_basic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1  ../src/app_device_cdc_basic.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.d ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_device_cdc_basic.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1: ../src/app_led_usb_status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1  ../src/app_led_usb_status.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.d ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/app_led_usb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/main.p1: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/main.p1  ../src/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/main.d ${OBJECTDIR}/_ext/1360937237/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1: ../src/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1  ../src/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.d ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1360937237/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/adc.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/adc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/adc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/adc.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/adc.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/adc.d ${OBJECTDIR}/_ext/1333569941/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/buttons.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/buttons.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/buttons.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/buttons.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/buttons.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/buttons.d ${OBJECTDIR}/_ext/1333569941/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/leds.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/leds.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/leds.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/leds.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/leds.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/leds.d ${OBJECTDIR}/_ext/1333569941/leds.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/leds.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1333569941/usart.p1: ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1333569941" 
	@${RM} ${OBJECTDIR}/_ext/1333569941/usart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1333569941/usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1333569941/usart.p1  ../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459/usart.c 
	@-${MV} ${OBJECTDIR}/_ext/1333569941/usart.d ${OBJECTDIR}/_ext/1333569941/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1333569941/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device.p1: ../../../../../../framework/usb/src/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device.p1  ../../../../../../framework/usb/src/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device.d ${OBJECTDIR}/_ext/838585624/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1: ../../../../../../framework/usb/src/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/838585624" 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1  ../../../../../../framework/usb/src/usb_device_cdc.c 
	@-${MV} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.d ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/838585624/usb_device_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"       --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.map  --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug --addrqual=require --mode=pro -P -N100 -I"../src" -I"../../../../../../framework" -I"../../../../../../bsp/low_pin_count_usb_development_kit/pic16f1459" -I"../src/system_config/low_pin_count_usb_development_kit/pic16f1459" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/LPCUSBDK_16F1459
	${RM} -r dist/LPCUSBDK_16F1459

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
