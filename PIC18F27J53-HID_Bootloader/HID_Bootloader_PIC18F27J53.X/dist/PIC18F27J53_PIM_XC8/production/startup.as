
	; Microchip MPLAB XC8 C Compiler V1.35
	; Copyright (C) 1984-2015 HI-TECH Software

	; Auto-generated runtime startup code for final link stage.

	;
	; Compiler options:
	;
	; --chip=18F27J53 -G \
	; -mdist/PIC18F27J53_PIM_XC8/production/HID_Bootloader_PIC18F27J53.X.production.map \
	; --double=32 --float=32 --emi=wordwrite --rom=default,-1000-1FFF7 \
	; --opt=default,+asm,-asmfile,-speed,+space,-debug --addrqual=require \
	; --mode=pro -P -N255 --warn=0 --asmlist \
	; --summary=default,-psect,-class,+mem,-hex,-file \
	; --output=default,-inhx032 \
	; --runtime=default,-clear,-init,+keep,-no_startup,-download,+config,+clib,+plib \
	; --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto \
	; --errformat=%f:%l: error: (%n) %s \
	; --warnformat=%f:%l: warning: (%n) %s \
	; --msgformat=%f:%l: advisory: (%n) %s --summary=+xml \
	; --summarydir=dist/PIC18F27J53_PIM_XC8/production/memoryfile.xml \
	; -odist/PIC18F27J53_PIM_XC8/production/HID_Bootloader_PIC18F27J53.X.production.elf \
	; build/PIC18F27J53_PIM_XC8/production/_ext/1360937237/main.p1 \
	; build/PIC18F27J53_PIM_XC8/production/_ext/1360937237/usb_descriptors.p1 \
	; build/PIC18F27J53_PIM_XC8/production/_ext/1360937237/usb_device.p1 \
	; build/PIC18F27J53_PIM_XC8/production/_ext/1360937237/usb_device_hid.p1 \
	; build/PIC18F27J53_PIM_XC8/production/_ext/1360937237/VectorRemap.obj \
	; build/PIC18F27J53_PIM_XC8/production/_ext/1360937237/boot_18fxxjxx.p1 \
	; --ccmode=cci
	;


	processor	18F27J53

	GLOBAL	_main,start
	FNROOT	_main

	pic18cxx	equ	1

	psect	jflash_buffer,class=CODE,space=0,noexec
	psect	config,class=CONFIG,delta=1,noexec
	psect	idloc,class=IDLOC,delta=1,noexec
	psect	const,class=CODE,delta=1,reloc=2,noexec
	psect	smallconst,class=SMALLCONST,delta=1,reloc=2,noexec
	psect	mediumconst,class=MEDIUMCONST,delta=1,reloc=2,noexec
	psect	rbss,class=COMRAM,space=1,noexec
	psect	bss,class=RAM,space=1,noexec
	psect	rdata,class=COMRAM,space=1,noexec
	psect	irdata,class=CODE,space=0,reloc=2,noexec
	psect	bss,class=RAM,space=1,noexec
	psect	data,class=RAM,space=1,noexec
	psect	idata,class=CODE,space=0,reloc=2,noexec
	psect	nvrram,class=COMRAM,space=1,noexec
	psect	nvbit,class=COMRAM,bit,space=1,noexec
	psect	temp,ovrld,class=COMRAM,space=1,noexec
	psect	struct,ovrld,class=COMRAM,space=1,noexec
	psect	rbit,class=COMRAM,bit,space=1,noexec
	psect	bigbss,class=BIGRAM,space=1,noexec
	psect	bigdata,class=BIGRAM,space=1,noexec
	psect	ibigdata,class=CODE,space=0,reloc=2,noexec
	psect	farbss,class=FARRAM,space=0,reloc=2,delta=1,noexec
	psect	nvFARRAM,class=FARRAM,space=0,reloc=2,delta=1,noexec
	psect	fardata,class=FARRAM,space=0,reloc=2,delta=1,noexec
	psect	ifardata,class=CODE,space=0,reloc=2,delta=1,noexec

	psect	reset_vec,class=CODE,delta=1,reloc=2
	psect	powerup,class=CODE,delta=1,reloc=2
	psect	intcode,class=CODE,delta=1,reloc=2
	psect	intcode_body,class=CODE,delta=1,reloc=2
	psect	intcodelo,class=CODE,delta=1,reloc=2
	psect	intret,class=CODE,delta=1,reloc=2
	psect	intentry,class=CODE,delta=1,reloc=2

	psect	intsave_regs,class=BIGRAM,space=1
	psect	init,class=CODE,delta=1,reloc=2
	psect	text,class=CODE,delta=1,reloc=2
GLOBAL	intlevel0,intlevel1,intlevel2
intlevel0:
intlevel1:
intlevel2:
GLOBAL	intlevel3
intlevel3:
	psect	end_init,class=CODE,delta=1,reloc=2
	psect	clrtext,class=CODE,delta=1,reloc=2

	psect	smallconst
	GLOBAL	__smallconst
__smallconst:
	psect	mediumconst
	GLOBAL	__mediumconst
__mediumconst:
wreg	EQU	0FE8h
fsr0l	EQU	0FE9h
fsr0h	EQU	0FEAh
fsr1l	EQU	0FE1h
fsr1h	EQU	0FE2h
fsr2l	EQU	0FD9h
fsr2h	EQU	0FDAh
postinc0	EQU	0FEEh
postdec0	EQU	0FEDh
postinc1	EQU	0FE6h
postdec1	EQU	0FE5h
postinc2	EQU	0FDEh
postdec2	EQU	0FDDh
tblptrl	EQU	0FF6h
tblptrh	EQU	0FF7h
tblptru	EQU	0FF8h
tablat		EQU	0FF5h

	PSECT	ramtop,class=RAM,noexec
	GLOBAL	__S1			; top of RAM usage
	GLOBAL	__ramtop
	GLOBAL	__LRAM,__HRAM
__ramtop:

	psect	reset_vec
reset_vec:
	; No powerup routine
	; No interrupt routine
	GLOBAL __accesstop
__accesstop EQU 96


	psect	init
start:

;Initialize the stack pointer (FSR1)
	global stacklo, stackhi
	stacklo	equ	04E2h
	stackhi	equ	0CFFh


	psect	stack,class=STACK,space=2,noexec
	global ___sp,___inthi_sp,___intlo_sp
___sp:
___inthi_sp:
___intlo_sp:

	psect	end_init
	global start_initialization
	goto start_initialization	;jump to C runtime clear & initialization

; Config register CONFIG1L @ 0x1FFF8
;	PLL Prescaler Selection
;	PLLDIV = 2, Divide by 2 (8 MHz oscillator input)
;	Stack Overflow/Underflow Reset
;	STVREN = OFF, Disabled
;	Watchdog Timer
;	WDTEN = OFF, Disabled - Controlled by SWDTEN bit
;	Extended Instruction Set
;	XINST = OFF, Disabled
;	PLL Enable Configuration Bit
;	CFGPLLEN = ON, PLL Enabled

	psect	config,class=CONFIG,delta=1,noexec
		org 0x0
		db 0x8C

; Config register CONFIG1H @ 0x1FFF9
;	Code Protect
;	CP0 = OFF, Program memory is not code-protected
;	CPU System Clock Postscaler
;	CPUDIV = OSC1, No CPU system clock divide

	psect	config,class=CONFIG,delta=1,noexec
		org 0x1
		db 0xF7

; Config register CONFIG2L @ 0x1FFFA
;	T1OSC/SOSC Power Selection Bits
;	SOSCSEL = LOW, Low Power T1OSC/SOSC circuit selected
;	Oscillator
;	OSC = INTOSCPLL, INTOSCPLL
;	Fail-Safe Clock Monitor
;	FCMEN = OFF, Disabled
;	Internal External Oscillator Switch Over Mode
;	IESO = OFF, Disabled
;	EC Clock Out Enable Bit
;	CLKOEC = OFF, CLKO output disabled on the RA6 pin

	psect	config,class=CONFIG,delta=1,noexec
		org 0x2
		db 0xA

; Config register CONFIG2H @ 0x1FFFB
;	Watchdog Postscaler
;	WDTPS = 1024, 1:1024

	psect	config,class=CONFIG,delta=1,noexec
		org 0x3
		db 0xFA

; Config register CONFIG3L @ 0x1FFFC
;	Deep Sleep BOR
;	DSBOREN = OFF, Disabled
;	Deep Sleep Watchdog Postscaler
;	DSWDTPS = G2, 1:2,147,483,648 (25.7 days)
;	DSWDT Clock Select
;	DSWDTOSC = T1OSCREF, DSWDT uses T1OSC/T1CKI
;	Deep Sleep Watchdog Timer
;	DSWDTEN = OFF, Disabled
;	RTCC Clock Select
;	RTCOSC = T1OSCREF, RTCC uses T1OSC/T1CKI

	psect	config,class=CONFIG,delta=1,noexec
		org 0x4
		db 0xF2

; Config register CONFIG3H @ 0x1FFFD
;	IOLOCK One-Way Set Enable bit
;	IOL1WAY = OFF, The IOLOCK bit (PPSCON<0>) can be set and cleared as needed
;	ADC 10 or 12 Bit Select
;	ADCSEL = BIT12, 12 - Bit ADC Enabled
;	MSSP address masking
;	MSSP7B_EN = MSK7, 7 Bit address masking mode

	psect	config,class=CONFIG,delta=1,noexec
		org 0x5
		db 0xF8

; Config register CONFIG4L @ 0x1FFFE
;	Write/Erase Protect Page Start/End Location
;	WPFP = PAGE_127, Write Protect Program Flash Page 127
;	Write/Erase Protect Configuration Region
;	WPCFG = OFF, Configuration Words page not erase/write-protected

	psect	config,class=CONFIG,delta=1,noexec
		org 0x6
		db 0xFF

; Config register CONFIG4H @ 0x1FFFF
;	Low Speed USB mode with 48 MHz system clock bit
;	LS48MHZ = SYS48X8, System clock at 48 MHz USB CLKEN divide-by is set to 8
;	Write/Erase Protect Region Select bit (valid when WPDIS = 0)
;	WPEND = PAGE_WPFP, Pages WPFP<6:0> through Configuration Words erase/write protected
;	Write Protect Disable bit
;	WPDIS = OFF, WPFP<6:0>/WPEND region ignored

	psect	config,class=CONFIG,delta=1,noexec
		org 0x7
		db 0xFB


psect comram,class=COMRAM,space=1
psect abs1,class=ABS1,space=1
psect bigram,class=BIGRAM,space=1
psect ram,class=RAM,space=1
psect bank0,class=BANK0,space=1
psect bank1,class=BANK1,space=1
psect bank2,class=BANK2,space=1
psect bank3,class=BANK3,space=1
psect bank4,class=BANK4,space=1
psect bank5,class=BANK5,space=1
psect bank6,class=BANK6,space=1
psect bank7,class=BANK7,space=1
psect bank8,class=BANK8,space=1
psect bank9,class=BANK9,space=1
psect bank10,class=BANK10,space=1
psect bank11,class=BANK11,space=1
psect bank12,class=BANK12,space=1
psect bank13,class=BANK13,space=1
psect bank14,class=BANK14,space=1
psect sfr,class=SFR,space=1


	end	start
