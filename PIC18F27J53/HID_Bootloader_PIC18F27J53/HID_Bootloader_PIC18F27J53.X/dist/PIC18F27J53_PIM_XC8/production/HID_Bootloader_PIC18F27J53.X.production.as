opt subtitle "Microchip Technology Omniscient Code Generator v1.35 (PRO mode) build 201507080246"

opt pagewidth 120

	opt pm

	processor	18F27J53
porta	equ	0F80h
portb	equ	0F81h
portc	equ	0F82h
portd	equ	0F83h
porte	equ	0F84h
lata	equ	0F89h
latb	equ	0F8Ah
latc	equ	0F8Bh
latd	equ	0F8Ch
late	equ	0F8Dh
trisa	equ	0F92h
trisb	equ	0F93h
trisc	equ	0F94h
trisd	equ	0F95h
trise	equ	0F96h
pie1	equ	0F9Dh
pir1	equ	0F9Eh
ipr1	equ	0F9Fh
pie2	equ	0FA0h
pir2	equ	0FA1h
ipr2	equ	0FA2h
t3con	equ	0FB1h
tmr3l	equ	0FB2h
tmr3h	equ	0FB3h
ccp1con	equ	0FBDh
ccpr1l	equ	0FBEh
ccpr1h	equ	0FBFh
adcon1	equ	0FC1h
adcon0	equ	0FC2h
adresl	equ	0FC3h
adresh	equ	0FC4h
sspcon2	equ	0FC5h
sspcon1	equ	0FC6h
sspstat	equ	0FC7h
sspadd	equ	0FC8h
sspbuf	equ	0FC9h
t2con	equ	0FCAh
pr2	equ	0FCBh
tmr2	equ	0FCCh
t1con	equ	0FCDh
tmr1l	equ	0FCEh
tmr1h	equ	0FCFh
rcon	equ	0FD0h
wdtcon	equ	0FD1h
lvdcon	equ	0FD2h
osccon	equ	0FD3h
t0con	equ	0FD5h
tmr0l	equ	0FD6h
tmr0h	equ	0FD7h
status	equ	0FD8h
fsr2	equ	0FD9h
fsr2l	equ	0FD9h
fsr2h	equ	0FDAh
plusw2	equ	0FDBh
preinc2	equ	0FDCh
postdec2	equ	0FDDh
postinc2	equ	0FDEh
indf2	equ	0FDFh
bsr	equ	0FE0h
fsr1	equ	0FE1h
fsr1l	equ	0FE1h
fsr1h	equ	0FE2h
plusw1	equ	0FE3h
preinc1	equ	0FE4h
postdec1	equ	0FE5h
postinc1	equ	0FE6h
indf1	equ	0FE7h
wreg	equ	0FE8h
fsr0	equ	0FE9h
fsr0l	equ	0FE9h
fsr0h	equ	0FEAh
plusw0	equ	0FEBh
preinc0	equ	0FECh
postdec0	equ	0FEDh
postinc0	equ	0FEEh
indf0	equ	0FEFh
intcon3	equ	0FF0h
intcon2	equ	0FF1h
intcon	equ	0FF2h
prod	equ	0FF3h
prodl	equ	0FF3h
prodh	equ	0FF4h
tablat	equ	0FF5h
tblptr	equ	0FF6h
tblptrl	equ	0FF6h
tblptrh	equ	0FF7h
tblptru	equ	0FF8h
pcl	equ	0FF9h
pclat	equ	0FFAh
pclath	equ	0FFAh
pclatu	equ	0FFBh
stkptr	equ	0FFCh
tosl	equ	0FFDh
tosh	equ	0FFEh
tosu	equ	0FFFh
clrc   macro
	bcf	status,0
endm
setc   macro
	bsf	status,0
endm
clrz   macro
	bcf	status,2
endm
setz   macro
	bsf	status,2
endm
skipnz macro
	btfsc	status,2
endm
skipz  macro
	btfss	status,2
endm
skipnc macro
	btfsc	status,0
endm
skipc  macro
	btfss	status,0
endm
pushw macro
	movwf postinc1
endm
pushf macro arg1
	movff arg1, postinc1
endm
popw macro
	movf postdec1,f
	movf indf1,w
endm
popf macro arg1
	movf postdec1,f
	movff indf1,arg1
endm
popfc macro arg1
	movff plusw1,arg1
	decfsz fsr1,f
endm
	global	__ramtop
	global	__accesstop
# 51 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCTRIG equ 0EB8h ;# 
# 106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS0 equ 0EB9h ;# 
# 111 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD0 equ 0EB9h ;# 
# 411 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS1 equ 0EBAh ;# 
# 416 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD1 equ 0EBAh ;# 
# 624 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS2 equ 0EBBh ;# 
# 629 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD2 equ 0EBBh ;# 
# 833 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS3 equ 0EBCh ;# 
# 838 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD3 equ 0EBCh ;# 
# 1070 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PPSCON equ 0EBFh ;# 
# 1089 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR0 equ 0EC0h ;# 
# 1095 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR1 equ 0EC1h ;# 
# 1101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR2 equ 0EC2h ;# 
# 1107 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR3 equ 0EC3h ;# 
# 1113 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR4 equ 0EC4h ;# 
# 1119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR5 equ 0EC5h ;# 
# 1125 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR6 equ 0EC6h ;# 
# 1131 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR7 equ 0EC7h ;# 
# 1137 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR8 equ 0EC8h ;# 
# 1143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR9 equ 0EC9h ;# 
# 1149 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR10 equ 0ECAh ;# 
# 1155 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR11 equ 0ECBh ;# 
# 1161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR12 equ 0ECCh ;# 
# 1167 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR13 equ 0ECDh ;# 
# 1173 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR17 equ 0ED1h ;# 
# 1179 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR18 equ 0ED2h ;# 
# 1185 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR1 equ 0EE1h ;# 
# 1191 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR2 equ 0EE2h ;# 
# 1197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR3 equ 0EE3h ;# 
# 1203 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR4 equ 0EE4h ;# 
# 1209 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR6 equ 0EE6h ;# 
# 1215 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR15 equ 0EE7h ;# 
# 1221 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR7 equ 0EE8h ;# 
# 1227 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR8 equ 0EE9h ;# 
# 1233 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR9 equ 0EEAh ;# 
# 1239 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR12 equ 0EF2h ;# 
# 1245 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR13 equ 0EF3h ;# 
# 1251 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR14 equ 0EF4h ;# 
# 1257 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR16 equ 0EF7h ;# 
# 1263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR17 equ 0EF8h ;# 
# 1269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR21 equ 0EFCh ;# 
# 1275 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR22 equ 0EFDh ;# 
# 1281 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR23 equ 0EFEh ;# 
# 1287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR24 equ 0EFFh ;# 
# 1293 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP10CON equ 0F00h ;# 
# 1356 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10L equ 0F01h ;# 
# 1375 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10H equ 0F02h ;# 
# 1394 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP9CON equ 0F03h ;# 
# 1457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9L equ 0F04h ;# 
# 1476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9H equ 0F05h ;# 
# 1495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP8CON equ 0F06h ;# 
# 1558 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8L equ 0F07h ;# 
# 1577 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8H equ 0F08h ;# 
# 1596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP7CON equ 0F09h ;# 
# 1659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7L equ 0F0Ah ;# 
# 1678 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7H equ 0F0Bh ;# 
# 1697 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP6CON equ 0F0Ch ;# 
# 1760 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6L equ 0F0Dh ;# 
# 1779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6H equ 0F0Eh ;# 
# 1798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP5CON equ 0F0Fh ;# 
# 1861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5L equ 0F10h ;# 
# 1880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5H equ 0F11h ;# 
# 1899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP4CON equ 0F12h ;# 
# 1962 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4L equ 0F13h ;# 
# 1981 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4H equ 0F14h ;# 
# 2000 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP3CON equ 0F15h ;# 
# 2081 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3L equ 0F16h ;# 
# 2100 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3H equ 0F17h ;# 
# 2119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3DEL equ 0F18h ;# 
# 2188 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3AS equ 0F19h ;# 
# 2269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR3CON equ 0F1Ah ;# 
# 2396 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T8CON equ 0F1Bh ;# 
# 2466 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR8 equ 0F1Ch ;# 
# 2485 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR8 equ 0F1Dh ;# 
# 2504 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T6CON equ 0F1Eh ;# 
# 2574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR6 equ 0F1Fh ;# 
# 2593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR6 equ 0F20h ;# 
# 2612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5GCON equ 0F21h ;# 
# 2724 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5CON equ 0F22h ;# 
# 2827 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5L equ 0F23h ;# 
# 2846 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5H equ 0F24h ;# 
# 2865 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM3CON equ 0F25h ;# 
# 3012 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP0 equ 0F26h ;# 
# 3143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP1 equ 0F27h ;# 
# 3274 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP2 equ 0F28h ;# 
# 3405 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP3 equ 0F29h ;# 
# 3536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP4 equ 0F2Ah ;# 
# 3667 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP5 equ 0F2Bh ;# 
# 3798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP6 equ 0F2Ch ;# 
# 3929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP7 equ 0F2Dh ;# 
# 4060 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP8 equ 0F2Eh ;# 
# 4147 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP9 equ 0F2Fh ;# 
# 4234 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP10 equ 0F30h ;# 
# 4321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP11 equ 0F31h ;# 
# 4408 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP12 equ 0F32h ;# 
# 4495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP13 equ 0F33h ;# 
# 4582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP14 equ 0F34h ;# 
# 4669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP15 equ 0F35h ;# 
# 4756 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIE equ 0F36h ;# 
# 4811 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIE equ 0F37h ;# 
# 4861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UADDR equ 0F38h ;# 
# 4924 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCFG equ 0F39h ;# 
# 4997 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALL equ 0F3Ah ;# 
# 5016 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALH equ 0F3Bh ;# 
# 5106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PADCFG1 equ 0F3Ch ;# 
# 5132 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
REFOCON equ 0F3Dh ;# 
# 5196 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCAL equ 0F3Eh ;# 
# 5265 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCFG equ 0F3Fh ;# 
# 5321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON3 equ 0F40h ;# 
# 5346 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON2 equ 0F41h ;# 
# 5383 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON1 equ 0F42h ;# 
# 5444 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALL equ 0F44h ;# 
# 5463 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALH equ 0F45h ;# 
# 5482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMRPT equ 0F46h ;# 
# 5551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMCFG equ 0F47h ;# 
# 5626 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON0 equ 0F48h ;# 
# 5669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON1 equ 0F49h ;# 
# 5728 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEL equ 0F4Ah ;# 
# 5779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEH equ 0F4Bh ;# 
# 5798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONL equ 0F4Ch ;# 
# 5829 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONH equ 0F4Dh ;# 
# 5861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR0 equ 0F4Eh ;# 
# 5880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR1 equ 0F4Fh ;# 
# 5899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS2 equ 0F50h ;# 
# 5945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS1 equ 0F51h ;# 
# 6011 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS0 equ 0F52h ;# 
# 6092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CVRCON equ 0F53h ;# 
# 6170 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRM equ 0F60h ;# 
# 6176 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRML equ 0F60h ;# 
# 6253 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRMH equ 0F61h ;# 
# 6292 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIR equ 0F62h ;# 
# 6347 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIR equ 0F63h ;# 
# 6397 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
USTAT equ 0F64h ;# 
# 6456 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCON equ 0F65h ;# 
# 6506 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCH equ 0F66h ;# 
# 6525 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCL equ 0F67h ;# 
# 6544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRH equ 0F68h ;# 
# 6563 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRL equ 0F69h ;# 
# 6582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRH equ 0F6Ah ;# 
# 6601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRL equ 0F6Bh ;# 
# 6620 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTAT equ 0F70h ;# 
# 6625 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTATUS equ 0F70h ;# 
# 6681 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON2 equ 0F71h ;# 
# 6891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON1 equ 0F72h ;# 
# 7031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2STAT equ 0F73h ;# 
# 7325 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2ADD equ 0F74h ;# 
# 7415 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2MSK equ 0F74h ;# 
# 7476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2BUF equ 0F75h ;# 
# 7495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T4CON equ 0F76h ;# 
# 7565 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR4 equ 0F77h ;# 
# 7584 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR4 equ 0F78h ;# 
# 7603 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3CON equ 0F79h ;# 
# 7715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3 equ 0F7Ah ;# 
# 7721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3L equ 0F7Ah ;# 
# 7740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3H equ 0F7Bh ;# 
# 7759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON2 equ 0F7Ch ;# 
# 7904 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH2 equ 0F7Dh ;# 
# 7923 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON1 equ 0F7Eh ;# 
# 7928 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON equ 0F7Eh ;# 
# 7932 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCTL equ 0F7Eh ;# 
# 8516 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH1 equ 0F7Fh ;# 
# 8521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH equ 0F7Fh ;# 
# 8553 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTA equ 0F80h ;# 
# 8835 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTB equ 0F81h ;# 
# 9148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTC equ 0F82h ;# 
# 9413 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
HLVDCON equ 0F85h ;# 
# 9482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON2 equ 0F86h ;# 
# 9557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON2 equ 0F87h ;# 
# 9596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON1 equ 0F88h ;# 
# 9657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATA equ 0F89h ;# 
# 9784 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATB equ 0F8Ah ;# 
# 9916 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATC equ 0F8Bh ;# 
# 10031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE4 equ 0F8Eh ;# 
# 10092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR4 equ 0F8Fh ;# 
# 10153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR4 equ 0F90h ;# 
# 10222 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE5 equ 0F91h ;# 
# 10271 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISA equ 0F92h ;# 
# 10327 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISB equ 0F93h ;# 
# 10388 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISC equ 0F94h ;# 
# 10441 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3GCON equ 0F97h ;# 
# 10529 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR5 equ 0F98h ;# 
# 10578 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR5 equ 0F99h ;# 
# 10662 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1GCON equ 0F9Ah ;# 
# 10768 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCTUNE equ 0F9Bh ;# 
# 10837 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA2 equ 0F9Ch ;# 
# 10974 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE1 equ 0F9Dh ;# 
# 11050 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR1 equ 0F9Eh ;# 
# 11126 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR1 equ 0F9Fh ;# 
# 11202 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE2 equ 0FA0h ;# 
# 11287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR2 equ 0FA1h ;# 
# 11372 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR2 equ 0FA2h ;# 
# 11457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE3 equ 0FA3h ;# 
# 11580 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR3 equ 0FA4h ;# 
# 11659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR3 equ 0FA5h ;# 
# 11738 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON1 equ 0FA6h ;# 
# 11782 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON2 equ 0FA7h ;# 
# 11801 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA2 equ 0FA8h ;# 
# 11929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG2 equ 0FA9h ;# 
# 11948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG2 equ 0FAAh ;# 
# 11967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG2 equ 0FABh ;# 
# 11986 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA1 equ 0FACh ;# 
# 11991 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA equ 0FACh ;# 
# 12323 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA1 equ 0FADh ;# 
# 12328 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA equ 0FADh ;# 
# 12610 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG1 equ 0FAEh ;# 
# 12615 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG equ 0FAEh ;# 
# 12647 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG1 equ 0FAFh ;# 
# 12652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG equ 0FAFh ;# 
# 12684 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG1 equ 0FB0h ;# 
# 12689 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG equ 0FB0h ;# 
# 12721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUICON equ 0FB1h ;# 
# 12796 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONL equ 0FB2h ;# 
# 12857 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONH equ 0FB3h ;# 
# 12913 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP2CON equ 0FB4h ;# 
# 12918 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2CON equ 0FB4h ;# 
# 13104 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2 equ 0FB5h ;# 
# 13110 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2L equ 0FB5h ;# 
# 13129 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2H equ 0FB6h ;# 
# 13148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2DEL equ 0FB7h ;# 
# 13153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM2CON equ 0FB7h ;# 
# 13285 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2AS equ 0FB8h ;# 
# 13366 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR2CON equ 0FB9h ;# 
# 13652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP1CON equ 0FBAh ;# 
# 13657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1CON equ 0FBAh ;# 
# 13843 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1 equ 0FBBh ;# 
# 13849 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1L equ 0FBBh ;# 
# 13868 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1H equ 0FBCh ;# 
# 13887 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1DEL equ 0FBDh ;# 
# 13892 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM1CON equ 0FBDh ;# 
# 14024 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1AS equ 0FBEh ;# 
# 14105 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR1CON equ 0FBFh ;# 
# 14161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WDTCON equ 0FC0h ;# 
# 14230 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON1 equ 0FC1h ;# 
# 14332 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON0 equ 0FC2h ;# 
# 14477 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRES equ 0FC3h ;# 
# 14483 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESL equ 0FC3h ;# 
# 14502 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESH equ 0FC4h ;# 
# 14521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON2 equ 0FC5h ;# 
# 14526 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON2 equ 0FC5h ;# 
# 14940 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON1 equ 0FC6h ;# 
# 14945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON1 equ 0FC6h ;# 
# 15219 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1STAT equ 0FC7h ;# 
# 15224 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPSTAT equ 0FC7h ;# 
# 15876 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1ADD equ 0FC8h ;# 
# 15881 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPADD equ 0FC8h ;# 
# 16197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1MSK equ 0FC8h ;# 
# 16258 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1BUF equ 0FC9h ;# 
# 16263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPBUF equ 0FC9h ;# 
# 16295 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T2CON equ 0FCAh ;# 
# 16365 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR2 equ 0FCBh ;# 
# 16370 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
MEMCON equ 0FCBh ;# 
# 16490 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR2 equ 0FCCh ;# 
# 16509 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1CON equ 0FCDh ;# 
# 16612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1 equ 0FCEh ;# 
# 16618 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1L equ 0FCEh ;# 
# 16637 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1H equ 0FCFh ;# 
# 16656 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCON equ 0FD0h ;# 
# 16803 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON equ 0FD1h ;# 
# 16808 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON1 equ 0FD1h ;# 
# 17096 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON equ 0FD2h ;# 
# 17101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON1 equ 0FD2h ;# 
# 17423 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON equ 0FD3h ;# 
# 17499 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T0CON equ 0FD5h ;# 
# 17568 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0 equ 0FD6h ;# 
# 17574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0L equ 0FD6h ;# 
# 17593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0H equ 0FD7h ;# 
# 17612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STATUS equ 0FD8h ;# 
# 17690 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2 equ 0FD9h ;# 
# 17696 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2L equ 0FD9h ;# 
# 17715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2H equ 0FDAh ;# 
# 17721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW2 equ 0FDBh ;# 
# 17740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC2 equ 0FDCh ;# 
# 17759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC2 equ 0FDDh ;# 
# 17778 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC2 equ 0FDEh ;# 
# 17797 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF2 equ 0FDFh ;# 
# 17816 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BSR equ 0FE0h ;# 
# 17822 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1 equ 0FE1h ;# 
# 17828 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1L equ 0FE1h ;# 
# 17847 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1H equ 0FE2h ;# 
# 17853 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW1 equ 0FE3h ;# 
# 17872 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC1 equ 0FE4h ;# 
# 17891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC1 equ 0FE5h ;# 
# 17910 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC1 equ 0FE6h ;# 
# 17929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF1 equ 0FE7h ;# 
# 17948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WREG equ 0FE8h ;# 
# 17967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0 equ 0FE9h ;# 
# 17973 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0L equ 0FE9h ;# 
# 17992 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0H equ 0FEAh ;# 
# 17998 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW0 equ 0FEBh ;# 
# 18017 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC0 equ 0FECh ;# 
# 18036 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC0 equ 0FEDh ;# 
# 18055 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC0 equ 0FEEh ;# 
# 18074 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF0 equ 0FEFh ;# 
# 18093 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON3 equ 0FF0h ;# 
# 18204 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON2 equ 0FF1h ;# 
# 18296 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON equ 0FF2h ;# 
# 18427 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PROD equ 0FF3h ;# 
# 18433 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODL equ 0FF3h ;# 
# 18452 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODH equ 0FF4h ;# 
# 18471 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TABLAT equ 0FF5h ;# 
# 18492 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTR equ 0FF6h ;# 
# 18498 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRL equ 0FF6h ;# 
# 18517 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRH equ 0FF7h ;# 
# 18536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRU equ 0FF8h ;# 
# 18544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLAT equ 0FF9h ;# 
# 18551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PC equ 0FF9h ;# 
# 18557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCL equ 0FF9h ;# 
# 18576 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATH equ 0FFAh ;# 
# 18595 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATU equ 0FFBh ;# 
# 18601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STKPTR equ 0FFCh ;# 
# 18674 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOS equ 0FFDh ;# 
# 18680 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSL equ 0FFDh ;# 
# 18699 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSH equ 0FFEh ;# 
# 18718 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSU equ 0FFFh ;# 
# 51 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCTRIG equ 0EB8h ;# 
# 106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS0 equ 0EB9h ;# 
# 111 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD0 equ 0EB9h ;# 
# 411 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS1 equ 0EBAh ;# 
# 416 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD1 equ 0EBAh ;# 
# 624 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS2 equ 0EBBh ;# 
# 629 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD2 equ 0EBBh ;# 
# 833 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS3 equ 0EBCh ;# 
# 838 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD3 equ 0EBCh ;# 
# 1070 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PPSCON equ 0EBFh ;# 
# 1089 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR0 equ 0EC0h ;# 
# 1095 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR1 equ 0EC1h ;# 
# 1101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR2 equ 0EC2h ;# 
# 1107 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR3 equ 0EC3h ;# 
# 1113 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR4 equ 0EC4h ;# 
# 1119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR5 equ 0EC5h ;# 
# 1125 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR6 equ 0EC6h ;# 
# 1131 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR7 equ 0EC7h ;# 
# 1137 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR8 equ 0EC8h ;# 
# 1143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR9 equ 0EC9h ;# 
# 1149 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR10 equ 0ECAh ;# 
# 1155 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR11 equ 0ECBh ;# 
# 1161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR12 equ 0ECCh ;# 
# 1167 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR13 equ 0ECDh ;# 
# 1173 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR17 equ 0ED1h ;# 
# 1179 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR18 equ 0ED2h ;# 
# 1185 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR1 equ 0EE1h ;# 
# 1191 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR2 equ 0EE2h ;# 
# 1197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR3 equ 0EE3h ;# 
# 1203 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR4 equ 0EE4h ;# 
# 1209 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR6 equ 0EE6h ;# 
# 1215 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR15 equ 0EE7h ;# 
# 1221 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR7 equ 0EE8h ;# 
# 1227 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR8 equ 0EE9h ;# 
# 1233 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR9 equ 0EEAh ;# 
# 1239 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR12 equ 0EF2h ;# 
# 1245 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR13 equ 0EF3h ;# 
# 1251 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR14 equ 0EF4h ;# 
# 1257 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR16 equ 0EF7h ;# 
# 1263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR17 equ 0EF8h ;# 
# 1269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR21 equ 0EFCh ;# 
# 1275 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR22 equ 0EFDh ;# 
# 1281 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR23 equ 0EFEh ;# 
# 1287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR24 equ 0EFFh ;# 
# 1293 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP10CON equ 0F00h ;# 
# 1356 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10L equ 0F01h ;# 
# 1375 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10H equ 0F02h ;# 
# 1394 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP9CON equ 0F03h ;# 
# 1457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9L equ 0F04h ;# 
# 1476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9H equ 0F05h ;# 
# 1495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP8CON equ 0F06h ;# 
# 1558 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8L equ 0F07h ;# 
# 1577 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8H equ 0F08h ;# 
# 1596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP7CON equ 0F09h ;# 
# 1659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7L equ 0F0Ah ;# 
# 1678 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7H equ 0F0Bh ;# 
# 1697 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP6CON equ 0F0Ch ;# 
# 1760 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6L equ 0F0Dh ;# 
# 1779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6H equ 0F0Eh ;# 
# 1798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP5CON equ 0F0Fh ;# 
# 1861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5L equ 0F10h ;# 
# 1880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5H equ 0F11h ;# 
# 1899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP4CON equ 0F12h ;# 
# 1962 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4L equ 0F13h ;# 
# 1981 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4H equ 0F14h ;# 
# 2000 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP3CON equ 0F15h ;# 
# 2081 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3L equ 0F16h ;# 
# 2100 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3H equ 0F17h ;# 
# 2119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3DEL equ 0F18h ;# 
# 2188 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3AS equ 0F19h ;# 
# 2269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR3CON equ 0F1Ah ;# 
# 2396 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T8CON equ 0F1Bh ;# 
# 2466 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR8 equ 0F1Ch ;# 
# 2485 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR8 equ 0F1Dh ;# 
# 2504 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T6CON equ 0F1Eh ;# 
# 2574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR6 equ 0F1Fh ;# 
# 2593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR6 equ 0F20h ;# 
# 2612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5GCON equ 0F21h ;# 
# 2724 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5CON equ 0F22h ;# 
# 2827 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5L equ 0F23h ;# 
# 2846 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5H equ 0F24h ;# 
# 2865 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM3CON equ 0F25h ;# 
# 3012 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP0 equ 0F26h ;# 
# 3143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP1 equ 0F27h ;# 
# 3274 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP2 equ 0F28h ;# 
# 3405 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP3 equ 0F29h ;# 
# 3536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP4 equ 0F2Ah ;# 
# 3667 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP5 equ 0F2Bh ;# 
# 3798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP6 equ 0F2Ch ;# 
# 3929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP7 equ 0F2Dh ;# 
# 4060 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP8 equ 0F2Eh ;# 
# 4147 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP9 equ 0F2Fh ;# 
# 4234 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP10 equ 0F30h ;# 
# 4321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP11 equ 0F31h ;# 
# 4408 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP12 equ 0F32h ;# 
# 4495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP13 equ 0F33h ;# 
# 4582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP14 equ 0F34h ;# 
# 4669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP15 equ 0F35h ;# 
# 4756 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIE equ 0F36h ;# 
# 4811 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIE equ 0F37h ;# 
# 4861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UADDR equ 0F38h ;# 
# 4924 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCFG equ 0F39h ;# 
# 4997 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALL equ 0F3Ah ;# 
# 5016 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALH equ 0F3Bh ;# 
# 5106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PADCFG1 equ 0F3Ch ;# 
# 5132 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
REFOCON equ 0F3Dh ;# 
# 5196 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCAL equ 0F3Eh ;# 
# 5265 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCFG equ 0F3Fh ;# 
# 5321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON3 equ 0F40h ;# 
# 5346 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON2 equ 0F41h ;# 
# 5383 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON1 equ 0F42h ;# 
# 5444 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALL equ 0F44h ;# 
# 5463 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALH equ 0F45h ;# 
# 5482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMRPT equ 0F46h ;# 
# 5551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMCFG equ 0F47h ;# 
# 5626 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON0 equ 0F48h ;# 
# 5669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON1 equ 0F49h ;# 
# 5728 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEL equ 0F4Ah ;# 
# 5779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEH equ 0F4Bh ;# 
# 5798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONL equ 0F4Ch ;# 
# 5829 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONH equ 0F4Dh ;# 
# 5861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR0 equ 0F4Eh ;# 
# 5880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR1 equ 0F4Fh ;# 
# 5899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS2 equ 0F50h ;# 
# 5945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS1 equ 0F51h ;# 
# 6011 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS0 equ 0F52h ;# 
# 6092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CVRCON equ 0F53h ;# 
# 6170 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRM equ 0F60h ;# 
# 6176 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRML equ 0F60h ;# 
# 6253 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRMH equ 0F61h ;# 
# 6292 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIR equ 0F62h ;# 
# 6347 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIR equ 0F63h ;# 
# 6397 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
USTAT equ 0F64h ;# 
# 6456 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCON equ 0F65h ;# 
# 6506 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCH equ 0F66h ;# 
# 6525 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCL equ 0F67h ;# 
# 6544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRH equ 0F68h ;# 
# 6563 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRL equ 0F69h ;# 
# 6582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRH equ 0F6Ah ;# 
# 6601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRL equ 0F6Bh ;# 
# 6620 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTAT equ 0F70h ;# 
# 6625 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTATUS equ 0F70h ;# 
# 6681 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON2 equ 0F71h ;# 
# 6891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON1 equ 0F72h ;# 
# 7031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2STAT equ 0F73h ;# 
# 7325 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2ADD equ 0F74h ;# 
# 7415 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2MSK equ 0F74h ;# 
# 7476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2BUF equ 0F75h ;# 
# 7495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T4CON equ 0F76h ;# 
# 7565 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR4 equ 0F77h ;# 
# 7584 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR4 equ 0F78h ;# 
# 7603 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3CON equ 0F79h ;# 
# 7715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3 equ 0F7Ah ;# 
# 7721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3L equ 0F7Ah ;# 
# 7740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3H equ 0F7Bh ;# 
# 7759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON2 equ 0F7Ch ;# 
# 7904 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH2 equ 0F7Dh ;# 
# 7923 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON1 equ 0F7Eh ;# 
# 7928 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON equ 0F7Eh ;# 
# 7932 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCTL equ 0F7Eh ;# 
# 8516 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH1 equ 0F7Fh ;# 
# 8521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH equ 0F7Fh ;# 
# 8553 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTA equ 0F80h ;# 
# 8835 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTB equ 0F81h ;# 
# 9148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTC equ 0F82h ;# 
# 9413 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
HLVDCON equ 0F85h ;# 
# 9482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON2 equ 0F86h ;# 
# 9557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON2 equ 0F87h ;# 
# 9596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON1 equ 0F88h ;# 
# 9657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATA equ 0F89h ;# 
# 9784 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATB equ 0F8Ah ;# 
# 9916 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATC equ 0F8Bh ;# 
# 10031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE4 equ 0F8Eh ;# 
# 10092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR4 equ 0F8Fh ;# 
# 10153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR4 equ 0F90h ;# 
# 10222 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE5 equ 0F91h ;# 
# 10271 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISA equ 0F92h ;# 
# 10327 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISB equ 0F93h ;# 
# 10388 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISC equ 0F94h ;# 
# 10441 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3GCON equ 0F97h ;# 
# 10529 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR5 equ 0F98h ;# 
# 10578 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR5 equ 0F99h ;# 
# 10662 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1GCON equ 0F9Ah ;# 
# 10768 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCTUNE equ 0F9Bh ;# 
# 10837 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA2 equ 0F9Ch ;# 
# 10974 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE1 equ 0F9Dh ;# 
# 11050 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR1 equ 0F9Eh ;# 
# 11126 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR1 equ 0F9Fh ;# 
# 11202 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE2 equ 0FA0h ;# 
# 11287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR2 equ 0FA1h ;# 
# 11372 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR2 equ 0FA2h ;# 
# 11457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE3 equ 0FA3h ;# 
# 11580 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR3 equ 0FA4h ;# 
# 11659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR3 equ 0FA5h ;# 
# 11738 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON1 equ 0FA6h ;# 
# 11782 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON2 equ 0FA7h ;# 
# 11801 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA2 equ 0FA8h ;# 
# 11929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG2 equ 0FA9h ;# 
# 11948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG2 equ 0FAAh ;# 
# 11967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG2 equ 0FABh ;# 
# 11986 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA1 equ 0FACh ;# 
# 11991 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA equ 0FACh ;# 
# 12323 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA1 equ 0FADh ;# 
# 12328 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA equ 0FADh ;# 
# 12610 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG1 equ 0FAEh ;# 
# 12615 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG equ 0FAEh ;# 
# 12647 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG1 equ 0FAFh ;# 
# 12652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG equ 0FAFh ;# 
# 12684 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG1 equ 0FB0h ;# 
# 12689 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG equ 0FB0h ;# 
# 12721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUICON equ 0FB1h ;# 
# 12796 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONL equ 0FB2h ;# 
# 12857 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONH equ 0FB3h ;# 
# 12913 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP2CON equ 0FB4h ;# 
# 12918 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2CON equ 0FB4h ;# 
# 13104 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2 equ 0FB5h ;# 
# 13110 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2L equ 0FB5h ;# 
# 13129 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2H equ 0FB6h ;# 
# 13148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2DEL equ 0FB7h ;# 
# 13153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM2CON equ 0FB7h ;# 
# 13285 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2AS equ 0FB8h ;# 
# 13366 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR2CON equ 0FB9h ;# 
# 13652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP1CON equ 0FBAh ;# 
# 13657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1CON equ 0FBAh ;# 
# 13843 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1 equ 0FBBh ;# 
# 13849 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1L equ 0FBBh ;# 
# 13868 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1H equ 0FBCh ;# 
# 13887 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1DEL equ 0FBDh ;# 
# 13892 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM1CON equ 0FBDh ;# 
# 14024 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1AS equ 0FBEh ;# 
# 14105 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR1CON equ 0FBFh ;# 
# 14161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WDTCON equ 0FC0h ;# 
# 14230 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON1 equ 0FC1h ;# 
# 14332 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON0 equ 0FC2h ;# 
# 14477 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRES equ 0FC3h ;# 
# 14483 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESL equ 0FC3h ;# 
# 14502 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESH equ 0FC4h ;# 
# 14521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON2 equ 0FC5h ;# 
# 14526 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON2 equ 0FC5h ;# 
# 14940 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON1 equ 0FC6h ;# 
# 14945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON1 equ 0FC6h ;# 
# 15219 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1STAT equ 0FC7h ;# 
# 15224 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPSTAT equ 0FC7h ;# 
# 15876 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1ADD equ 0FC8h ;# 
# 15881 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPADD equ 0FC8h ;# 
# 16197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1MSK equ 0FC8h ;# 
# 16258 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1BUF equ 0FC9h ;# 
# 16263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPBUF equ 0FC9h ;# 
# 16295 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T2CON equ 0FCAh ;# 
# 16365 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR2 equ 0FCBh ;# 
# 16370 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
MEMCON equ 0FCBh ;# 
# 16490 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR2 equ 0FCCh ;# 
# 16509 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1CON equ 0FCDh ;# 
# 16612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1 equ 0FCEh ;# 
# 16618 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1L equ 0FCEh ;# 
# 16637 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1H equ 0FCFh ;# 
# 16656 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCON equ 0FD0h ;# 
# 16803 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON equ 0FD1h ;# 
# 16808 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON1 equ 0FD1h ;# 
# 17096 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON equ 0FD2h ;# 
# 17101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON1 equ 0FD2h ;# 
# 17423 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON equ 0FD3h ;# 
# 17499 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T0CON equ 0FD5h ;# 
# 17568 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0 equ 0FD6h ;# 
# 17574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0L equ 0FD6h ;# 
# 17593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0H equ 0FD7h ;# 
# 17612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STATUS equ 0FD8h ;# 
# 17690 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2 equ 0FD9h ;# 
# 17696 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2L equ 0FD9h ;# 
# 17715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2H equ 0FDAh ;# 
# 17721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW2 equ 0FDBh ;# 
# 17740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC2 equ 0FDCh ;# 
# 17759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC2 equ 0FDDh ;# 
# 17778 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC2 equ 0FDEh ;# 
# 17797 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF2 equ 0FDFh ;# 
# 17816 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BSR equ 0FE0h ;# 
# 17822 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1 equ 0FE1h ;# 
# 17828 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1L equ 0FE1h ;# 
# 17847 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1H equ 0FE2h ;# 
# 17853 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW1 equ 0FE3h ;# 
# 17872 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC1 equ 0FE4h ;# 
# 17891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC1 equ 0FE5h ;# 
# 17910 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC1 equ 0FE6h ;# 
# 17929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF1 equ 0FE7h ;# 
# 17948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WREG equ 0FE8h ;# 
# 17967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0 equ 0FE9h ;# 
# 17973 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0L equ 0FE9h ;# 
# 17992 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0H equ 0FEAh ;# 
# 17998 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW0 equ 0FEBh ;# 
# 18017 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC0 equ 0FECh ;# 
# 18036 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC0 equ 0FEDh ;# 
# 18055 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC0 equ 0FEEh ;# 
# 18074 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF0 equ 0FEFh ;# 
# 18093 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON3 equ 0FF0h ;# 
# 18204 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON2 equ 0FF1h ;# 
# 18296 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON equ 0FF2h ;# 
# 18427 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PROD equ 0FF3h ;# 
# 18433 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODL equ 0FF3h ;# 
# 18452 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODH equ 0FF4h ;# 
# 18471 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TABLAT equ 0FF5h ;# 
# 18492 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTR equ 0FF6h ;# 
# 18498 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRL equ 0FF6h ;# 
# 18517 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRH equ 0FF7h ;# 
# 18536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRU equ 0FF8h ;# 
# 18544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLAT equ 0FF9h ;# 
# 18551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PC equ 0FF9h ;# 
# 18557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCL equ 0FF9h ;# 
# 18576 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATH equ 0FFAh ;# 
# 18595 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATU equ 0FFBh ;# 
# 18601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STKPTR equ 0FFCh ;# 
# 18674 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOS equ 0FFDh ;# 
# 18680 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSL equ 0FFDh ;# 
# 18699 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSH equ 0FFEh ;# 
# 18718 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSU equ 0FFFh ;# 
# 51 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCTRIG equ 0EB8h ;# 
# 106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS0 equ 0EB9h ;# 
# 111 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD0 equ 0EB9h ;# 
# 411 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS1 equ 0EBAh ;# 
# 416 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD1 equ 0EBAh ;# 
# 624 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS2 equ 0EBBh ;# 
# 629 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD2 equ 0EBBh ;# 
# 833 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS3 equ 0EBCh ;# 
# 838 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD3 equ 0EBCh ;# 
# 1070 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PPSCON equ 0EBFh ;# 
# 1089 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR0 equ 0EC0h ;# 
# 1095 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR1 equ 0EC1h ;# 
# 1101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR2 equ 0EC2h ;# 
# 1107 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR3 equ 0EC3h ;# 
# 1113 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR4 equ 0EC4h ;# 
# 1119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR5 equ 0EC5h ;# 
# 1125 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR6 equ 0EC6h ;# 
# 1131 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR7 equ 0EC7h ;# 
# 1137 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR8 equ 0EC8h ;# 
# 1143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR9 equ 0EC9h ;# 
# 1149 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR10 equ 0ECAh ;# 
# 1155 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR11 equ 0ECBh ;# 
# 1161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR12 equ 0ECCh ;# 
# 1167 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR13 equ 0ECDh ;# 
# 1173 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR17 equ 0ED1h ;# 
# 1179 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR18 equ 0ED2h ;# 
# 1185 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR1 equ 0EE1h ;# 
# 1191 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR2 equ 0EE2h ;# 
# 1197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR3 equ 0EE3h ;# 
# 1203 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR4 equ 0EE4h ;# 
# 1209 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR6 equ 0EE6h ;# 
# 1215 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR15 equ 0EE7h ;# 
# 1221 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR7 equ 0EE8h ;# 
# 1227 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR8 equ 0EE9h ;# 
# 1233 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR9 equ 0EEAh ;# 
# 1239 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR12 equ 0EF2h ;# 
# 1245 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR13 equ 0EF3h ;# 
# 1251 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR14 equ 0EF4h ;# 
# 1257 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR16 equ 0EF7h ;# 
# 1263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR17 equ 0EF8h ;# 
# 1269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR21 equ 0EFCh ;# 
# 1275 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR22 equ 0EFDh ;# 
# 1281 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR23 equ 0EFEh ;# 
# 1287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR24 equ 0EFFh ;# 
# 1293 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP10CON equ 0F00h ;# 
# 1356 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10L equ 0F01h ;# 
# 1375 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10H equ 0F02h ;# 
# 1394 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP9CON equ 0F03h ;# 
# 1457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9L equ 0F04h ;# 
# 1476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9H equ 0F05h ;# 
# 1495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP8CON equ 0F06h ;# 
# 1558 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8L equ 0F07h ;# 
# 1577 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8H equ 0F08h ;# 
# 1596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP7CON equ 0F09h ;# 
# 1659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7L equ 0F0Ah ;# 
# 1678 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7H equ 0F0Bh ;# 
# 1697 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP6CON equ 0F0Ch ;# 
# 1760 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6L equ 0F0Dh ;# 
# 1779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6H equ 0F0Eh ;# 
# 1798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP5CON equ 0F0Fh ;# 
# 1861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5L equ 0F10h ;# 
# 1880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5H equ 0F11h ;# 
# 1899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP4CON equ 0F12h ;# 
# 1962 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4L equ 0F13h ;# 
# 1981 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4H equ 0F14h ;# 
# 2000 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP3CON equ 0F15h ;# 
# 2081 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3L equ 0F16h ;# 
# 2100 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3H equ 0F17h ;# 
# 2119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3DEL equ 0F18h ;# 
# 2188 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3AS equ 0F19h ;# 
# 2269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR3CON equ 0F1Ah ;# 
# 2396 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T8CON equ 0F1Bh ;# 
# 2466 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR8 equ 0F1Ch ;# 
# 2485 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR8 equ 0F1Dh ;# 
# 2504 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T6CON equ 0F1Eh ;# 
# 2574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR6 equ 0F1Fh ;# 
# 2593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR6 equ 0F20h ;# 
# 2612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5GCON equ 0F21h ;# 
# 2724 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5CON equ 0F22h ;# 
# 2827 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5L equ 0F23h ;# 
# 2846 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5H equ 0F24h ;# 
# 2865 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM3CON equ 0F25h ;# 
# 3012 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP0 equ 0F26h ;# 
# 3143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP1 equ 0F27h ;# 
# 3274 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP2 equ 0F28h ;# 
# 3405 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP3 equ 0F29h ;# 
# 3536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP4 equ 0F2Ah ;# 
# 3667 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP5 equ 0F2Bh ;# 
# 3798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP6 equ 0F2Ch ;# 
# 3929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP7 equ 0F2Dh ;# 
# 4060 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP8 equ 0F2Eh ;# 
# 4147 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP9 equ 0F2Fh ;# 
# 4234 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP10 equ 0F30h ;# 
# 4321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP11 equ 0F31h ;# 
# 4408 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP12 equ 0F32h ;# 
# 4495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP13 equ 0F33h ;# 
# 4582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP14 equ 0F34h ;# 
# 4669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP15 equ 0F35h ;# 
# 4756 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIE equ 0F36h ;# 
# 4811 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIE equ 0F37h ;# 
# 4861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UADDR equ 0F38h ;# 
# 4924 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCFG equ 0F39h ;# 
# 4997 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALL equ 0F3Ah ;# 
# 5016 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALH equ 0F3Bh ;# 
# 5106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PADCFG1 equ 0F3Ch ;# 
# 5132 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
REFOCON equ 0F3Dh ;# 
# 5196 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCAL equ 0F3Eh ;# 
# 5265 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCFG equ 0F3Fh ;# 
# 5321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON3 equ 0F40h ;# 
# 5346 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON2 equ 0F41h ;# 
# 5383 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON1 equ 0F42h ;# 
# 5444 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALL equ 0F44h ;# 
# 5463 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALH equ 0F45h ;# 
# 5482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMRPT equ 0F46h ;# 
# 5551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMCFG equ 0F47h ;# 
# 5626 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON0 equ 0F48h ;# 
# 5669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON1 equ 0F49h ;# 
# 5728 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEL equ 0F4Ah ;# 
# 5779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEH equ 0F4Bh ;# 
# 5798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONL equ 0F4Ch ;# 
# 5829 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONH equ 0F4Dh ;# 
# 5861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR0 equ 0F4Eh ;# 
# 5880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR1 equ 0F4Fh ;# 
# 5899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS2 equ 0F50h ;# 
# 5945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS1 equ 0F51h ;# 
# 6011 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS0 equ 0F52h ;# 
# 6092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CVRCON equ 0F53h ;# 
# 6170 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRM equ 0F60h ;# 
# 6176 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRML equ 0F60h ;# 
# 6253 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRMH equ 0F61h ;# 
# 6292 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIR equ 0F62h ;# 
# 6347 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIR equ 0F63h ;# 
# 6397 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
USTAT equ 0F64h ;# 
# 6456 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCON equ 0F65h ;# 
# 6506 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCH equ 0F66h ;# 
# 6525 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCL equ 0F67h ;# 
# 6544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRH equ 0F68h ;# 
# 6563 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRL equ 0F69h ;# 
# 6582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRH equ 0F6Ah ;# 
# 6601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRL equ 0F6Bh ;# 
# 6620 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTAT equ 0F70h ;# 
# 6625 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTATUS equ 0F70h ;# 
# 6681 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON2 equ 0F71h ;# 
# 6891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON1 equ 0F72h ;# 
# 7031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2STAT equ 0F73h ;# 
# 7325 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2ADD equ 0F74h ;# 
# 7415 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2MSK equ 0F74h ;# 
# 7476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2BUF equ 0F75h ;# 
# 7495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T4CON equ 0F76h ;# 
# 7565 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR4 equ 0F77h ;# 
# 7584 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR4 equ 0F78h ;# 
# 7603 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3CON equ 0F79h ;# 
# 7715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3 equ 0F7Ah ;# 
# 7721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3L equ 0F7Ah ;# 
# 7740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3H equ 0F7Bh ;# 
# 7759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON2 equ 0F7Ch ;# 
# 7904 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH2 equ 0F7Dh ;# 
# 7923 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON1 equ 0F7Eh ;# 
# 7928 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON equ 0F7Eh ;# 
# 7932 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCTL equ 0F7Eh ;# 
# 8516 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH1 equ 0F7Fh ;# 
# 8521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH equ 0F7Fh ;# 
# 8553 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTA equ 0F80h ;# 
# 8835 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTB equ 0F81h ;# 
# 9148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTC equ 0F82h ;# 
# 9413 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
HLVDCON equ 0F85h ;# 
# 9482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON2 equ 0F86h ;# 
# 9557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON2 equ 0F87h ;# 
# 9596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON1 equ 0F88h ;# 
# 9657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATA equ 0F89h ;# 
# 9784 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATB equ 0F8Ah ;# 
# 9916 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATC equ 0F8Bh ;# 
# 10031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE4 equ 0F8Eh ;# 
# 10092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR4 equ 0F8Fh ;# 
# 10153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR4 equ 0F90h ;# 
# 10222 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE5 equ 0F91h ;# 
# 10271 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISA equ 0F92h ;# 
# 10327 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISB equ 0F93h ;# 
# 10388 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISC equ 0F94h ;# 
# 10441 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3GCON equ 0F97h ;# 
# 10529 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR5 equ 0F98h ;# 
# 10578 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR5 equ 0F99h ;# 
# 10662 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1GCON equ 0F9Ah ;# 
# 10768 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCTUNE equ 0F9Bh ;# 
# 10837 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA2 equ 0F9Ch ;# 
# 10974 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE1 equ 0F9Dh ;# 
# 11050 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR1 equ 0F9Eh ;# 
# 11126 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR1 equ 0F9Fh ;# 
# 11202 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE2 equ 0FA0h ;# 
# 11287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR2 equ 0FA1h ;# 
# 11372 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR2 equ 0FA2h ;# 
# 11457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE3 equ 0FA3h ;# 
# 11580 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR3 equ 0FA4h ;# 
# 11659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR3 equ 0FA5h ;# 
# 11738 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON1 equ 0FA6h ;# 
# 11782 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON2 equ 0FA7h ;# 
# 11801 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA2 equ 0FA8h ;# 
# 11929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG2 equ 0FA9h ;# 
# 11948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG2 equ 0FAAh ;# 
# 11967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG2 equ 0FABh ;# 
# 11986 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA1 equ 0FACh ;# 
# 11991 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA equ 0FACh ;# 
# 12323 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA1 equ 0FADh ;# 
# 12328 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA equ 0FADh ;# 
# 12610 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG1 equ 0FAEh ;# 
# 12615 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG equ 0FAEh ;# 
# 12647 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG1 equ 0FAFh ;# 
# 12652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG equ 0FAFh ;# 
# 12684 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG1 equ 0FB0h ;# 
# 12689 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG equ 0FB0h ;# 
# 12721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUICON equ 0FB1h ;# 
# 12796 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONL equ 0FB2h ;# 
# 12857 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONH equ 0FB3h ;# 
# 12913 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP2CON equ 0FB4h ;# 
# 12918 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2CON equ 0FB4h ;# 
# 13104 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2 equ 0FB5h ;# 
# 13110 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2L equ 0FB5h ;# 
# 13129 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2H equ 0FB6h ;# 
# 13148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2DEL equ 0FB7h ;# 
# 13153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM2CON equ 0FB7h ;# 
# 13285 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2AS equ 0FB8h ;# 
# 13366 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR2CON equ 0FB9h ;# 
# 13652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP1CON equ 0FBAh ;# 
# 13657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1CON equ 0FBAh ;# 
# 13843 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1 equ 0FBBh ;# 
# 13849 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1L equ 0FBBh ;# 
# 13868 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1H equ 0FBCh ;# 
# 13887 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1DEL equ 0FBDh ;# 
# 13892 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM1CON equ 0FBDh ;# 
# 14024 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1AS equ 0FBEh ;# 
# 14105 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR1CON equ 0FBFh ;# 
# 14161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WDTCON equ 0FC0h ;# 
# 14230 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON1 equ 0FC1h ;# 
# 14332 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON0 equ 0FC2h ;# 
# 14477 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRES equ 0FC3h ;# 
# 14483 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESL equ 0FC3h ;# 
# 14502 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESH equ 0FC4h ;# 
# 14521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON2 equ 0FC5h ;# 
# 14526 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON2 equ 0FC5h ;# 
# 14940 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON1 equ 0FC6h ;# 
# 14945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON1 equ 0FC6h ;# 
# 15219 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1STAT equ 0FC7h ;# 
# 15224 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPSTAT equ 0FC7h ;# 
# 15876 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1ADD equ 0FC8h ;# 
# 15881 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPADD equ 0FC8h ;# 
# 16197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1MSK equ 0FC8h ;# 
# 16258 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1BUF equ 0FC9h ;# 
# 16263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPBUF equ 0FC9h ;# 
# 16295 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T2CON equ 0FCAh ;# 
# 16365 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR2 equ 0FCBh ;# 
# 16370 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
MEMCON equ 0FCBh ;# 
# 16490 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR2 equ 0FCCh ;# 
# 16509 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1CON equ 0FCDh ;# 
# 16612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1 equ 0FCEh ;# 
# 16618 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1L equ 0FCEh ;# 
# 16637 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1H equ 0FCFh ;# 
# 16656 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCON equ 0FD0h ;# 
# 16803 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON equ 0FD1h ;# 
# 16808 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON1 equ 0FD1h ;# 
# 17096 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON equ 0FD2h ;# 
# 17101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON1 equ 0FD2h ;# 
# 17423 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON equ 0FD3h ;# 
# 17499 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T0CON equ 0FD5h ;# 
# 17568 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0 equ 0FD6h ;# 
# 17574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0L equ 0FD6h ;# 
# 17593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0H equ 0FD7h ;# 
# 17612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STATUS equ 0FD8h ;# 
# 17690 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2 equ 0FD9h ;# 
# 17696 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2L equ 0FD9h ;# 
# 17715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2H equ 0FDAh ;# 
# 17721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW2 equ 0FDBh ;# 
# 17740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC2 equ 0FDCh ;# 
# 17759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC2 equ 0FDDh ;# 
# 17778 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC2 equ 0FDEh ;# 
# 17797 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF2 equ 0FDFh ;# 
# 17816 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BSR equ 0FE0h ;# 
# 17822 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1 equ 0FE1h ;# 
# 17828 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1L equ 0FE1h ;# 
# 17847 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1H equ 0FE2h ;# 
# 17853 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW1 equ 0FE3h ;# 
# 17872 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC1 equ 0FE4h ;# 
# 17891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC1 equ 0FE5h ;# 
# 17910 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC1 equ 0FE6h ;# 
# 17929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF1 equ 0FE7h ;# 
# 17948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WREG equ 0FE8h ;# 
# 17967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0 equ 0FE9h ;# 
# 17973 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0L equ 0FE9h ;# 
# 17992 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0H equ 0FEAh ;# 
# 17998 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW0 equ 0FEBh ;# 
# 18017 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC0 equ 0FECh ;# 
# 18036 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC0 equ 0FEDh ;# 
# 18055 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC0 equ 0FEEh ;# 
# 18074 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF0 equ 0FEFh ;# 
# 18093 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON3 equ 0FF0h ;# 
# 18204 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON2 equ 0FF1h ;# 
# 18296 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON equ 0FF2h ;# 
# 18427 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PROD equ 0FF3h ;# 
# 18433 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODL equ 0FF3h ;# 
# 18452 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODH equ 0FF4h ;# 
# 18471 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TABLAT equ 0FF5h ;# 
# 18492 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTR equ 0FF6h ;# 
# 18498 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRL equ 0FF6h ;# 
# 18517 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRH equ 0FF7h ;# 
# 18536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRU equ 0FF8h ;# 
# 18544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLAT equ 0FF9h ;# 
# 18551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PC equ 0FF9h ;# 
# 18557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCL equ 0FF9h ;# 
# 18576 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATH equ 0FFAh ;# 
# 18595 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATU equ 0FFBh ;# 
# 18601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STKPTR equ 0FFCh ;# 
# 18674 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOS equ 0FFDh ;# 
# 18680 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSL equ 0FFDh ;# 
# 18699 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSH equ 0FFEh ;# 
# 18718 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSU equ 0FFFh ;# 
# 51 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCTRIG equ 0EB8h ;# 
# 106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS0 equ 0EB9h ;# 
# 111 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD0 equ 0EB9h ;# 
# 411 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS1 equ 0EBAh ;# 
# 416 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD1 equ 0EBAh ;# 
# 624 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS2 equ 0EBBh ;# 
# 629 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD2 equ 0EBBh ;# 
# 833 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS3 equ 0EBCh ;# 
# 838 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD3 equ 0EBCh ;# 
# 1070 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PPSCON equ 0EBFh ;# 
# 1089 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR0 equ 0EC0h ;# 
# 1095 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR1 equ 0EC1h ;# 
# 1101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR2 equ 0EC2h ;# 
# 1107 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR3 equ 0EC3h ;# 
# 1113 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR4 equ 0EC4h ;# 
# 1119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR5 equ 0EC5h ;# 
# 1125 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR6 equ 0EC6h ;# 
# 1131 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR7 equ 0EC7h ;# 
# 1137 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR8 equ 0EC8h ;# 
# 1143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR9 equ 0EC9h ;# 
# 1149 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR10 equ 0ECAh ;# 
# 1155 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR11 equ 0ECBh ;# 
# 1161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR12 equ 0ECCh ;# 
# 1167 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR13 equ 0ECDh ;# 
# 1173 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR17 equ 0ED1h ;# 
# 1179 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR18 equ 0ED2h ;# 
# 1185 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR1 equ 0EE1h ;# 
# 1191 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR2 equ 0EE2h ;# 
# 1197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR3 equ 0EE3h ;# 
# 1203 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR4 equ 0EE4h ;# 
# 1209 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR6 equ 0EE6h ;# 
# 1215 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR15 equ 0EE7h ;# 
# 1221 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR7 equ 0EE8h ;# 
# 1227 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR8 equ 0EE9h ;# 
# 1233 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR9 equ 0EEAh ;# 
# 1239 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR12 equ 0EF2h ;# 
# 1245 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR13 equ 0EF3h ;# 
# 1251 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR14 equ 0EF4h ;# 
# 1257 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR16 equ 0EF7h ;# 
# 1263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR17 equ 0EF8h ;# 
# 1269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR21 equ 0EFCh ;# 
# 1275 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR22 equ 0EFDh ;# 
# 1281 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR23 equ 0EFEh ;# 
# 1287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR24 equ 0EFFh ;# 
# 1293 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP10CON equ 0F00h ;# 
# 1356 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10L equ 0F01h ;# 
# 1375 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10H equ 0F02h ;# 
# 1394 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP9CON equ 0F03h ;# 
# 1457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9L equ 0F04h ;# 
# 1476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9H equ 0F05h ;# 
# 1495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP8CON equ 0F06h ;# 
# 1558 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8L equ 0F07h ;# 
# 1577 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8H equ 0F08h ;# 
# 1596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP7CON equ 0F09h ;# 
# 1659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7L equ 0F0Ah ;# 
# 1678 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7H equ 0F0Bh ;# 
# 1697 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP6CON equ 0F0Ch ;# 
# 1760 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6L equ 0F0Dh ;# 
# 1779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6H equ 0F0Eh ;# 
# 1798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP5CON equ 0F0Fh ;# 
# 1861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5L equ 0F10h ;# 
# 1880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5H equ 0F11h ;# 
# 1899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP4CON equ 0F12h ;# 
# 1962 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4L equ 0F13h ;# 
# 1981 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4H equ 0F14h ;# 
# 2000 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP3CON equ 0F15h ;# 
# 2081 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3L equ 0F16h ;# 
# 2100 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3H equ 0F17h ;# 
# 2119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3DEL equ 0F18h ;# 
# 2188 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3AS equ 0F19h ;# 
# 2269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR3CON equ 0F1Ah ;# 
# 2396 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T8CON equ 0F1Bh ;# 
# 2466 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR8 equ 0F1Ch ;# 
# 2485 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR8 equ 0F1Dh ;# 
# 2504 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T6CON equ 0F1Eh ;# 
# 2574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR6 equ 0F1Fh ;# 
# 2593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR6 equ 0F20h ;# 
# 2612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5GCON equ 0F21h ;# 
# 2724 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5CON equ 0F22h ;# 
# 2827 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5L equ 0F23h ;# 
# 2846 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5H equ 0F24h ;# 
# 2865 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM3CON equ 0F25h ;# 
# 3012 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP0 equ 0F26h ;# 
# 3143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP1 equ 0F27h ;# 
# 3274 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP2 equ 0F28h ;# 
# 3405 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP3 equ 0F29h ;# 
# 3536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP4 equ 0F2Ah ;# 
# 3667 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP5 equ 0F2Bh ;# 
# 3798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP6 equ 0F2Ch ;# 
# 3929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP7 equ 0F2Dh ;# 
# 4060 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP8 equ 0F2Eh ;# 
# 4147 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP9 equ 0F2Fh ;# 
# 4234 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP10 equ 0F30h ;# 
# 4321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP11 equ 0F31h ;# 
# 4408 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP12 equ 0F32h ;# 
# 4495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP13 equ 0F33h ;# 
# 4582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP14 equ 0F34h ;# 
# 4669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP15 equ 0F35h ;# 
# 4756 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIE equ 0F36h ;# 
# 4811 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIE equ 0F37h ;# 
# 4861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UADDR equ 0F38h ;# 
# 4924 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCFG equ 0F39h ;# 
# 4997 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALL equ 0F3Ah ;# 
# 5016 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALH equ 0F3Bh ;# 
# 5106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PADCFG1 equ 0F3Ch ;# 
# 5132 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
REFOCON equ 0F3Dh ;# 
# 5196 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCAL equ 0F3Eh ;# 
# 5265 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCFG equ 0F3Fh ;# 
# 5321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON3 equ 0F40h ;# 
# 5346 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON2 equ 0F41h ;# 
# 5383 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON1 equ 0F42h ;# 
# 5444 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALL equ 0F44h ;# 
# 5463 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALH equ 0F45h ;# 
# 5482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMRPT equ 0F46h ;# 
# 5551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMCFG equ 0F47h ;# 
# 5626 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON0 equ 0F48h ;# 
# 5669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON1 equ 0F49h ;# 
# 5728 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEL equ 0F4Ah ;# 
# 5779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEH equ 0F4Bh ;# 
# 5798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONL equ 0F4Ch ;# 
# 5829 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONH equ 0F4Dh ;# 
# 5861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR0 equ 0F4Eh ;# 
# 5880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR1 equ 0F4Fh ;# 
# 5899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS2 equ 0F50h ;# 
# 5945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS1 equ 0F51h ;# 
# 6011 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS0 equ 0F52h ;# 
# 6092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CVRCON equ 0F53h ;# 
# 6170 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRM equ 0F60h ;# 
# 6176 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRML equ 0F60h ;# 
# 6253 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRMH equ 0F61h ;# 
# 6292 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIR equ 0F62h ;# 
# 6347 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIR equ 0F63h ;# 
# 6397 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
USTAT equ 0F64h ;# 
# 6456 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCON equ 0F65h ;# 
# 6506 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCH equ 0F66h ;# 
# 6525 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCL equ 0F67h ;# 
# 6544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRH equ 0F68h ;# 
# 6563 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRL equ 0F69h ;# 
# 6582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRH equ 0F6Ah ;# 
# 6601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRL equ 0F6Bh ;# 
# 6620 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTAT equ 0F70h ;# 
# 6625 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTATUS equ 0F70h ;# 
# 6681 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON2 equ 0F71h ;# 
# 6891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON1 equ 0F72h ;# 
# 7031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2STAT equ 0F73h ;# 
# 7325 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2ADD equ 0F74h ;# 
# 7415 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2MSK equ 0F74h ;# 
# 7476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2BUF equ 0F75h ;# 
# 7495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T4CON equ 0F76h ;# 
# 7565 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR4 equ 0F77h ;# 
# 7584 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR4 equ 0F78h ;# 
# 7603 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3CON equ 0F79h ;# 
# 7715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3 equ 0F7Ah ;# 
# 7721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3L equ 0F7Ah ;# 
# 7740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3H equ 0F7Bh ;# 
# 7759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON2 equ 0F7Ch ;# 
# 7904 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH2 equ 0F7Dh ;# 
# 7923 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON1 equ 0F7Eh ;# 
# 7928 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON equ 0F7Eh ;# 
# 7932 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCTL equ 0F7Eh ;# 
# 8516 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH1 equ 0F7Fh ;# 
# 8521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH equ 0F7Fh ;# 
# 8553 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTA equ 0F80h ;# 
# 8835 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTB equ 0F81h ;# 
# 9148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTC equ 0F82h ;# 
# 9413 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
HLVDCON equ 0F85h ;# 
# 9482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON2 equ 0F86h ;# 
# 9557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON2 equ 0F87h ;# 
# 9596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON1 equ 0F88h ;# 
# 9657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATA equ 0F89h ;# 
# 9784 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATB equ 0F8Ah ;# 
# 9916 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATC equ 0F8Bh ;# 
# 10031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE4 equ 0F8Eh ;# 
# 10092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR4 equ 0F8Fh ;# 
# 10153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR4 equ 0F90h ;# 
# 10222 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE5 equ 0F91h ;# 
# 10271 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISA equ 0F92h ;# 
# 10327 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISB equ 0F93h ;# 
# 10388 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISC equ 0F94h ;# 
# 10441 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3GCON equ 0F97h ;# 
# 10529 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR5 equ 0F98h ;# 
# 10578 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR5 equ 0F99h ;# 
# 10662 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1GCON equ 0F9Ah ;# 
# 10768 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCTUNE equ 0F9Bh ;# 
# 10837 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA2 equ 0F9Ch ;# 
# 10974 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE1 equ 0F9Dh ;# 
# 11050 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR1 equ 0F9Eh ;# 
# 11126 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR1 equ 0F9Fh ;# 
# 11202 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE2 equ 0FA0h ;# 
# 11287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR2 equ 0FA1h ;# 
# 11372 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR2 equ 0FA2h ;# 
# 11457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE3 equ 0FA3h ;# 
# 11580 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR3 equ 0FA4h ;# 
# 11659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR3 equ 0FA5h ;# 
# 11738 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON1 equ 0FA6h ;# 
# 11782 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON2 equ 0FA7h ;# 
# 11801 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA2 equ 0FA8h ;# 
# 11929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG2 equ 0FA9h ;# 
# 11948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG2 equ 0FAAh ;# 
# 11967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG2 equ 0FABh ;# 
# 11986 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA1 equ 0FACh ;# 
# 11991 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA equ 0FACh ;# 
# 12323 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA1 equ 0FADh ;# 
# 12328 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA equ 0FADh ;# 
# 12610 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG1 equ 0FAEh ;# 
# 12615 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG equ 0FAEh ;# 
# 12647 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG1 equ 0FAFh ;# 
# 12652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG equ 0FAFh ;# 
# 12684 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG1 equ 0FB0h ;# 
# 12689 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG equ 0FB0h ;# 
# 12721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUICON equ 0FB1h ;# 
# 12796 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONL equ 0FB2h ;# 
# 12857 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONH equ 0FB3h ;# 
# 12913 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP2CON equ 0FB4h ;# 
# 12918 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2CON equ 0FB4h ;# 
# 13104 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2 equ 0FB5h ;# 
# 13110 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2L equ 0FB5h ;# 
# 13129 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2H equ 0FB6h ;# 
# 13148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2DEL equ 0FB7h ;# 
# 13153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM2CON equ 0FB7h ;# 
# 13285 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2AS equ 0FB8h ;# 
# 13366 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR2CON equ 0FB9h ;# 
# 13652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP1CON equ 0FBAh ;# 
# 13657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1CON equ 0FBAh ;# 
# 13843 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1 equ 0FBBh ;# 
# 13849 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1L equ 0FBBh ;# 
# 13868 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1H equ 0FBCh ;# 
# 13887 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1DEL equ 0FBDh ;# 
# 13892 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM1CON equ 0FBDh ;# 
# 14024 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1AS equ 0FBEh ;# 
# 14105 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR1CON equ 0FBFh ;# 
# 14161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WDTCON equ 0FC0h ;# 
# 14230 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON1 equ 0FC1h ;# 
# 14332 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON0 equ 0FC2h ;# 
# 14477 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRES equ 0FC3h ;# 
# 14483 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESL equ 0FC3h ;# 
# 14502 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESH equ 0FC4h ;# 
# 14521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON2 equ 0FC5h ;# 
# 14526 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON2 equ 0FC5h ;# 
# 14940 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON1 equ 0FC6h ;# 
# 14945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON1 equ 0FC6h ;# 
# 15219 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1STAT equ 0FC7h ;# 
# 15224 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPSTAT equ 0FC7h ;# 
# 15876 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1ADD equ 0FC8h ;# 
# 15881 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPADD equ 0FC8h ;# 
# 16197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1MSK equ 0FC8h ;# 
# 16258 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1BUF equ 0FC9h ;# 
# 16263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPBUF equ 0FC9h ;# 
# 16295 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T2CON equ 0FCAh ;# 
# 16365 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR2 equ 0FCBh ;# 
# 16370 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
MEMCON equ 0FCBh ;# 
# 16490 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR2 equ 0FCCh ;# 
# 16509 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1CON equ 0FCDh ;# 
# 16612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1 equ 0FCEh ;# 
# 16618 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1L equ 0FCEh ;# 
# 16637 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1H equ 0FCFh ;# 
# 16656 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCON equ 0FD0h ;# 
# 16803 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON equ 0FD1h ;# 
# 16808 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON1 equ 0FD1h ;# 
# 17096 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON equ 0FD2h ;# 
# 17101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON1 equ 0FD2h ;# 
# 17423 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON equ 0FD3h ;# 
# 17499 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T0CON equ 0FD5h ;# 
# 17568 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0 equ 0FD6h ;# 
# 17574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0L equ 0FD6h ;# 
# 17593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0H equ 0FD7h ;# 
# 17612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STATUS equ 0FD8h ;# 
# 17690 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2 equ 0FD9h ;# 
# 17696 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2L equ 0FD9h ;# 
# 17715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2H equ 0FDAh ;# 
# 17721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW2 equ 0FDBh ;# 
# 17740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC2 equ 0FDCh ;# 
# 17759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC2 equ 0FDDh ;# 
# 17778 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC2 equ 0FDEh ;# 
# 17797 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF2 equ 0FDFh ;# 
# 17816 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BSR equ 0FE0h ;# 
# 17822 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1 equ 0FE1h ;# 
# 17828 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1L equ 0FE1h ;# 
# 17847 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1H equ 0FE2h ;# 
# 17853 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW1 equ 0FE3h ;# 
# 17872 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC1 equ 0FE4h ;# 
# 17891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC1 equ 0FE5h ;# 
# 17910 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC1 equ 0FE6h ;# 
# 17929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF1 equ 0FE7h ;# 
# 17948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WREG equ 0FE8h ;# 
# 17967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0 equ 0FE9h ;# 
# 17973 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0L equ 0FE9h ;# 
# 17992 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0H equ 0FEAh ;# 
# 17998 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW0 equ 0FEBh ;# 
# 18017 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC0 equ 0FECh ;# 
# 18036 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC0 equ 0FEDh ;# 
# 18055 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC0 equ 0FEEh ;# 
# 18074 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF0 equ 0FEFh ;# 
# 18093 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON3 equ 0FF0h ;# 
# 18204 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON2 equ 0FF1h ;# 
# 18296 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON equ 0FF2h ;# 
# 18427 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PROD equ 0FF3h ;# 
# 18433 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODL equ 0FF3h ;# 
# 18452 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODH equ 0FF4h ;# 
# 18471 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TABLAT equ 0FF5h ;# 
# 18492 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTR equ 0FF6h ;# 
# 18498 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRL equ 0FF6h ;# 
# 18517 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRH equ 0FF7h ;# 
# 18536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRU equ 0FF8h ;# 
# 18544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLAT equ 0FF9h ;# 
# 18551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PC equ 0FF9h ;# 
# 18557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCL equ 0FF9h ;# 
# 18576 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATH equ 0FFAh ;# 
# 18595 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATU equ 0FFBh ;# 
# 18601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STKPTR equ 0FFCh ;# 
# 18674 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOS equ 0FFDh ;# 
# 18680 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSL equ 0FFDh ;# 
# 18699 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSH equ 0FFEh ;# 
# 18718 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSU equ 0FFFh ;# 
# 51 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCTRIG equ 0EB8h ;# 
# 106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS0 equ 0EB9h ;# 
# 111 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD0 equ 0EB9h ;# 
# 411 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS1 equ 0EBAh ;# 
# 416 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD1 equ 0EBAh ;# 
# 624 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS2 equ 0EBBh ;# 
# 629 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD2 equ 0EBBh ;# 
# 833 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PMDIS3 equ 0EBCh ;# 
# 838 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PD3 equ 0EBCh ;# 
# 1070 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PPSCON equ 0EBFh ;# 
# 1089 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR0 equ 0EC0h ;# 
# 1095 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR1 equ 0EC1h ;# 
# 1101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR2 equ 0EC2h ;# 
# 1107 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR3 equ 0EC3h ;# 
# 1113 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR4 equ 0EC4h ;# 
# 1119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR5 equ 0EC5h ;# 
# 1125 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR6 equ 0EC6h ;# 
# 1131 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR7 equ 0EC7h ;# 
# 1137 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR8 equ 0EC8h ;# 
# 1143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR9 equ 0EC9h ;# 
# 1149 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR10 equ 0ECAh ;# 
# 1155 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR11 equ 0ECBh ;# 
# 1161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR12 equ 0ECCh ;# 
# 1167 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR13 equ 0ECDh ;# 
# 1173 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR17 equ 0ED1h ;# 
# 1179 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPOR18 equ 0ED2h ;# 
# 1185 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR1 equ 0EE1h ;# 
# 1191 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR2 equ 0EE2h ;# 
# 1197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR3 equ 0EE3h ;# 
# 1203 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR4 equ 0EE4h ;# 
# 1209 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR6 equ 0EE6h ;# 
# 1215 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR15 equ 0EE7h ;# 
# 1221 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR7 equ 0EE8h ;# 
# 1227 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR8 equ 0EE9h ;# 
# 1233 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR9 equ 0EEAh ;# 
# 1239 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR12 equ 0EF2h ;# 
# 1245 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR13 equ 0EF3h ;# 
# 1251 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR14 equ 0EF4h ;# 
# 1257 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR16 equ 0EF7h ;# 
# 1263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR17 equ 0EF8h ;# 
# 1269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR21 equ 0EFCh ;# 
# 1275 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR22 equ 0EFDh ;# 
# 1281 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR23 equ 0EFEh ;# 
# 1287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RPINR24 equ 0EFFh ;# 
# 1293 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP10CON equ 0F00h ;# 
# 1356 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10L equ 0F01h ;# 
# 1375 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR10H equ 0F02h ;# 
# 1394 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP9CON equ 0F03h ;# 
# 1457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9L equ 0F04h ;# 
# 1476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR9H equ 0F05h ;# 
# 1495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP8CON equ 0F06h ;# 
# 1558 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8L equ 0F07h ;# 
# 1577 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR8H equ 0F08h ;# 
# 1596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP7CON equ 0F09h ;# 
# 1659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7L equ 0F0Ah ;# 
# 1678 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR7H equ 0F0Bh ;# 
# 1697 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP6CON equ 0F0Ch ;# 
# 1760 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6L equ 0F0Dh ;# 
# 1779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR6H equ 0F0Eh ;# 
# 1798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP5CON equ 0F0Fh ;# 
# 1861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5L equ 0F10h ;# 
# 1880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR5H equ 0F11h ;# 
# 1899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP4CON equ 0F12h ;# 
# 1962 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4L equ 0F13h ;# 
# 1981 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR4H equ 0F14h ;# 
# 2000 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP3CON equ 0F15h ;# 
# 2081 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3L equ 0F16h ;# 
# 2100 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR3H equ 0F17h ;# 
# 2119 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3DEL equ 0F18h ;# 
# 2188 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP3AS equ 0F19h ;# 
# 2269 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR3CON equ 0F1Ah ;# 
# 2396 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T8CON equ 0F1Bh ;# 
# 2466 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR8 equ 0F1Ch ;# 
# 2485 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR8 equ 0F1Dh ;# 
# 2504 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T6CON equ 0F1Eh ;# 
# 2574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR6 equ 0F1Fh ;# 
# 2593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR6 equ 0F20h ;# 
# 2612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5GCON equ 0F21h ;# 
# 2724 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T5CON equ 0F22h ;# 
# 2827 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5L equ 0F23h ;# 
# 2846 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR5H equ 0F24h ;# 
# 2865 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM3CON equ 0F25h ;# 
# 3012 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP0 equ 0F26h ;# 
# 3143 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP1 equ 0F27h ;# 
# 3274 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP2 equ 0F28h ;# 
# 3405 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP3 equ 0F29h ;# 
# 3536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP4 equ 0F2Ah ;# 
# 3667 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP5 equ 0F2Bh ;# 
# 3798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP6 equ 0F2Ch ;# 
# 3929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP7 equ 0F2Dh ;# 
# 4060 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP8 equ 0F2Eh ;# 
# 4147 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP9 equ 0F2Fh ;# 
# 4234 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP10 equ 0F30h ;# 
# 4321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP11 equ 0F31h ;# 
# 4408 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP12 equ 0F32h ;# 
# 4495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP13 equ 0F33h ;# 
# 4582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP14 equ 0F34h ;# 
# 4669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEP15 equ 0F35h ;# 
# 4756 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIE equ 0F36h ;# 
# 4811 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIE equ 0F37h ;# 
# 4861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UADDR equ 0F38h ;# 
# 4924 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCFG equ 0F39h ;# 
# 4997 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALL equ 0F3Ah ;# 
# 5016 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCVALH equ 0F3Bh ;# 
# 5106 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PADCFG1 equ 0F3Ch ;# 
# 5132 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
REFOCON equ 0F3Dh ;# 
# 5196 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCAL equ 0F3Eh ;# 
# 5265 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RTCCFG equ 0F3Fh ;# 
# 5321 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON3 equ 0F40h ;# 
# 5346 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON2 equ 0F41h ;# 
# 5383 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ODCON1 equ 0F42h ;# 
# 5444 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALL equ 0F44h ;# 
# 5463 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMVALH equ 0F45h ;# 
# 5482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMRPT equ 0F46h ;# 
# 5551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ALRMCFG equ 0F47h ;# 
# 5626 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON0 equ 0F48h ;# 
# 5669 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ANCON1 equ 0F49h ;# 
# 5728 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEL equ 0F4Ah ;# 
# 5779 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSWAKEH equ 0F4Bh ;# 
# 5798 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONL equ 0F4Ch ;# 
# 5829 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSCONH equ 0F4Dh ;# 
# 5861 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR0 equ 0F4Eh ;# 
# 5880 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DSGPR1 equ 0F4Fh ;# 
# 5899 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS2 equ 0F50h ;# 
# 5945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS1 equ 0F51h ;# 
# 6011 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPTMRS0 equ 0F52h ;# 
# 6092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CVRCON equ 0F53h ;# 
# 6170 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRM equ 0F60h ;# 
# 6176 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRML equ 0F60h ;# 
# 6253 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UFRMH equ 0F61h ;# 
# 6292 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UIR equ 0F62h ;# 
# 6347 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UEIR equ 0F63h ;# 
# 6397 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
USTAT equ 0F64h ;# 
# 6456 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
UCON equ 0F65h ;# 
# 6506 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCH equ 0F66h ;# 
# 6525 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMABCL equ 0F67h ;# 
# 6544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRH equ 0F68h ;# 
# 6563 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RXADDRL equ 0F69h ;# 
# 6582 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRH equ 0F6Ah ;# 
# 6601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXADDRL equ 0F6Bh ;# 
# 6620 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTAT equ 0F70h ;# 
# 6625 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CMSTATUS equ 0F70h ;# 
# 6681 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON2 equ 0F71h ;# 
# 6891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2CON1 equ 0F72h ;# 
# 7031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2STAT equ 0F73h ;# 
# 7325 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2ADD equ 0F74h ;# 
# 7415 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2MSK equ 0F74h ;# 
# 7476 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP2BUF equ 0F75h ;# 
# 7495 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T4CON equ 0F76h ;# 
# 7565 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR4 equ 0F77h ;# 
# 7584 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR4 equ 0F78h ;# 
# 7603 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3CON equ 0F79h ;# 
# 7715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3 equ 0F7Ah ;# 
# 7721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3L equ 0F7Ah ;# 
# 7740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR3H equ 0F7Bh ;# 
# 7759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON2 equ 0F7Ch ;# 
# 7904 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH2 equ 0F7Dh ;# 
# 7923 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON1 equ 0F7Eh ;# 
# 7928 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCON equ 0F7Eh ;# 
# 7932 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BAUDCTL equ 0F7Eh ;# 
# 8516 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH1 equ 0F7Fh ;# 
# 8521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRGH equ 0F7Fh ;# 
# 8553 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTA equ 0F80h ;# 
# 8835 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTB equ 0F81h ;# 
# 9148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PORTC equ 0F82h ;# 
# 9413 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
HLVDCON equ 0F85h ;# 
# 9482 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON2 equ 0F86h ;# 
# 9557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON2 equ 0F87h ;# 
# 9596 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
DMACON1 equ 0F88h ;# 
# 9657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATA equ 0F89h ;# 
# 9784 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATB equ 0F8Ah ;# 
# 9916 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
LATC equ 0F8Bh ;# 
# 10031 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE4 equ 0F8Eh ;# 
# 10092 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR4 equ 0F8Fh ;# 
# 10153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR4 equ 0F90h ;# 
# 10222 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE5 equ 0F91h ;# 
# 10271 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISA equ 0F92h ;# 
# 10327 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISB equ 0F93h ;# 
# 10388 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TRISC equ 0F94h ;# 
# 10441 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T3GCON equ 0F97h ;# 
# 10529 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR5 equ 0F98h ;# 
# 10578 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR5 equ 0F99h ;# 
# 10662 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1GCON equ 0F9Ah ;# 
# 10768 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCTUNE equ 0F9Bh ;# 
# 10837 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA2 equ 0F9Ch ;# 
# 10974 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE1 equ 0F9Dh ;# 
# 11050 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR1 equ 0F9Eh ;# 
# 11126 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR1 equ 0F9Fh ;# 
# 11202 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE2 equ 0FA0h ;# 
# 11287 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR2 equ 0FA1h ;# 
# 11372 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR2 equ 0FA2h ;# 
# 11457 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIE3 equ 0FA3h ;# 
# 11580 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PIR3 equ 0FA4h ;# 
# 11659 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
IPR3 equ 0FA5h ;# 
# 11738 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON1 equ 0FA6h ;# 
# 11782 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
EECON2 equ 0FA7h ;# 
# 11801 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA2 equ 0FA8h ;# 
# 11929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG2 equ 0FA9h ;# 
# 11948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG2 equ 0FAAh ;# 
# 11967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG2 equ 0FABh ;# 
# 11986 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA1 equ 0FACh ;# 
# 11991 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCSTA equ 0FACh ;# 
# 12323 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA1 equ 0FADh ;# 
# 12328 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXSTA equ 0FADh ;# 
# 12610 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG1 equ 0FAEh ;# 
# 12615 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TXREG equ 0FAEh ;# 
# 12647 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG1 equ 0FAFh ;# 
# 12652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCREG equ 0FAFh ;# 
# 12684 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG1 equ 0FB0h ;# 
# 12689 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SPBRG equ 0FB0h ;# 
# 12721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUICON equ 0FB1h ;# 
# 12796 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONL equ 0FB2h ;# 
# 12857 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CTMUCONH equ 0FB3h ;# 
# 12913 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP2CON equ 0FB4h ;# 
# 12918 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2CON equ 0FB4h ;# 
# 13104 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2 equ 0FB5h ;# 
# 13110 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2L equ 0FB5h ;# 
# 13129 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR2H equ 0FB6h ;# 
# 13148 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2DEL equ 0FB7h ;# 
# 13153 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM2CON equ 0FB7h ;# 
# 13285 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP2AS equ 0FB8h ;# 
# 13366 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR2CON equ 0FB9h ;# 
# 13652 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCP1CON equ 0FBAh ;# 
# 13657 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1CON equ 0FBAh ;# 
# 13843 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1 equ 0FBBh ;# 
# 13849 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1L equ 0FBBh ;# 
# 13868 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CCPR1H equ 0FBCh ;# 
# 13887 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1DEL equ 0FBDh ;# 
# 13892 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PWM1CON equ 0FBDh ;# 
# 14024 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ECCP1AS equ 0FBEh ;# 
# 14105 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PSTR1CON equ 0FBFh ;# 
# 14161 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WDTCON equ 0FC0h ;# 
# 14230 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON1 equ 0FC1h ;# 
# 14332 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADCON0 equ 0FC2h ;# 
# 14477 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRES equ 0FC3h ;# 
# 14483 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESL equ 0FC3h ;# 
# 14502 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
ADRESH equ 0FC4h ;# 
# 14521 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON2 equ 0FC5h ;# 
# 14526 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON2 equ 0FC5h ;# 
# 14940 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1CON1 equ 0FC6h ;# 
# 14945 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPCON1 equ 0FC6h ;# 
# 15219 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1STAT equ 0FC7h ;# 
# 15224 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPSTAT equ 0FC7h ;# 
# 15876 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1ADD equ 0FC8h ;# 
# 15881 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPADD equ 0FC8h ;# 
# 16197 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1MSK equ 0FC8h ;# 
# 16258 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSP1BUF equ 0FC9h ;# 
# 16263 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
SSPBUF equ 0FC9h ;# 
# 16295 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T2CON equ 0FCAh ;# 
# 16365 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PR2 equ 0FCBh ;# 
# 16370 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
MEMCON equ 0FCBh ;# 
# 16490 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR2 equ 0FCCh ;# 
# 16509 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T1CON equ 0FCDh ;# 
# 16612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1 equ 0FCEh ;# 
# 16618 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1L equ 0FCEh ;# 
# 16637 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR1H equ 0FCFh ;# 
# 16656 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
RCON equ 0FD0h ;# 
# 16803 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON equ 0FD1h ;# 
# 16808 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM2CON1 equ 0FD1h ;# 
# 17096 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON equ 0FD2h ;# 
# 17101 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
CM1CON1 equ 0FD2h ;# 
# 17423 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
OSCCON equ 0FD3h ;# 
# 17499 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
T0CON equ 0FD5h ;# 
# 17568 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0 equ 0FD6h ;# 
# 17574 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0L equ 0FD6h ;# 
# 17593 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TMR0H equ 0FD7h ;# 
# 17612 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STATUS equ 0FD8h ;# 
# 17690 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2 equ 0FD9h ;# 
# 17696 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2L equ 0FD9h ;# 
# 17715 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR2H equ 0FDAh ;# 
# 17721 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW2 equ 0FDBh ;# 
# 17740 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC2 equ 0FDCh ;# 
# 17759 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC2 equ 0FDDh ;# 
# 17778 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC2 equ 0FDEh ;# 
# 17797 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF2 equ 0FDFh ;# 
# 17816 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
BSR equ 0FE0h ;# 
# 17822 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1 equ 0FE1h ;# 
# 17828 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1L equ 0FE1h ;# 
# 17847 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR1H equ 0FE2h ;# 
# 17853 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW1 equ 0FE3h ;# 
# 17872 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC1 equ 0FE4h ;# 
# 17891 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC1 equ 0FE5h ;# 
# 17910 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC1 equ 0FE6h ;# 
# 17929 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF1 equ 0FE7h ;# 
# 17948 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
WREG equ 0FE8h ;# 
# 17967 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0 equ 0FE9h ;# 
# 17973 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0L equ 0FE9h ;# 
# 17992 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
FSR0H equ 0FEAh ;# 
# 17998 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PLUSW0 equ 0FEBh ;# 
# 18017 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PREINC0 equ 0FECh ;# 
# 18036 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTDEC0 equ 0FEDh ;# 
# 18055 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
POSTINC0 equ 0FEEh ;# 
# 18074 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INDF0 equ 0FEFh ;# 
# 18093 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON3 equ 0FF0h ;# 
# 18204 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON2 equ 0FF1h ;# 
# 18296 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
INTCON equ 0FF2h ;# 
# 18427 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PROD equ 0FF3h ;# 
# 18433 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODL equ 0FF3h ;# 
# 18452 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PRODH equ 0FF4h ;# 
# 18471 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TABLAT equ 0FF5h ;# 
# 18492 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTR equ 0FF6h ;# 
# 18498 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRL equ 0FF6h ;# 
# 18517 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRH equ 0FF7h ;# 
# 18536 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TBLPTRU equ 0FF8h ;# 
# 18544 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLAT equ 0FF9h ;# 
# 18551 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PC equ 0FF9h ;# 
# 18557 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCL equ 0FF9h ;# 
# 18576 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATH equ 0FFAh ;# 
# 18595 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
PCLATU equ 0FFBh ;# 
# 18601 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
STKPTR equ 0FFCh ;# 
# 18674 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOS equ 0FFDh ;# 
# 18680 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSL equ 0FFDh ;# 
# 18699 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSH equ 0FFEh ;# 
# 18718 "C:\Program Files (x86)\Microchip\xc8\v1.35\include\pic18f27j53.h"
TOSU equ 0FFFh ;# 
	FNCALL	_main,_BootMain
	FNCALL	_BootMain,_BlinkUSBStatus
	FNCALL	_BootMain,_InitializeSystem
	FNCALL	_BootMain,_LowVoltageCheck
	FNCALL	_BootMain,_ProcessIO
	FNCALL	_BootMain,_USBDeviceTasks
	FNCALL	_ProcessIO,_ClearWatchdog
	FNCALL	_ProcessIO,_EraseFlashPage
	FNCALL	_ProcessIO,_HIDRxReport
	FNCALL	_ProcessIO,_HIDTxReport
	FNCALL	_ProcessIO,_ResetDeviceCleanly
	FNCALL	_ProcessIO,_SignFlash
	FNCALL	_ProcessIO,_USBDeviceTasks
	FNCALL	_ProcessIO,_WriteFlashSubBlock
	FNCALL	_WriteFlashSubBlock,_UnlockAndActivate
	FNCALL	_USBDeviceTasks,_USBCheckBusStatus
	FNCALL	_USBDeviceTasks,_USBCtrlTrfInHandler
	FNCALL	_USBDeviceTasks,_USBCtrlTrfSetupHandler
	FNCALL	_USBDeviceTasks,_USBProtocolResetHandler
	FNCALL	_USBDeviceTasks,_USBSuspend
	FNCALL	_USBDeviceTasks,_USBWakeFromSuspend
	FNCALL	_USBWakeFromSuspend,_USBCBWakeFromSuspend
	FNCALL	_USBCBWakeFromSuspend,_DelayRoutine
	FNCALL	_USBSuspend,_USBCBSuspend
	FNCALL	_USBCtrlTrfSetupHandler,_USBCBCheckOtherReq
	FNCALL	_USBCtrlTrfSetupHandler,_USBCheckStdRequest
	FNCALL	_USBCtrlTrfSetupHandler,_USBCtrlEPServiceComplete
	FNCALL	_USBCtrlEPServiceComplete,_LoadBDTandSetUOWN
	FNCALL	_USBCtrlEPServiceComplete,_USBCtrlTrfTxService
	FNCALL	_USBCheckStdRequest,_USBStdFeatureReqHandler
	FNCALL	_USBCheckStdRequest,_USBStdGetDscHandler
	FNCALL	_USBCheckStdRequest,_USBStdGetStatusHandler
	FNCALL	_USBCheckStdRequest,_USBStdSetCfgHandler
	FNCALL	_USBStdSetCfgHandler,_USBCBInitEP
	FNCALL	_USBCBCheckOtherReq,_USBCheckHIDRequest
	FNCALL	_USBCheckHIDRequest,_HIDGetReportHandler
	FNCALL	_USBCheckHIDRequest,_HIDSetReportHandler
	FNCALL	_USBCtrlTrfInHandler,_USBCtrlTrfTxService
	FNCALL	_SignFlash,_ClearWatchdog
	FNCALL	_SignFlash,_EraseFlashPage
	FNCALL	_SignFlash,_UnlockAndActivate
	FNCALL	_EraseFlashPage,_UnlockAndActivate
	FNCALL	_UnlockAndActivate,_LowVoltageCheck
	FNCALL	_ResetDeviceCleanly,_USBDisableWithLongDelay
	FNCALL	_InitializeSystem,_DelayRoutine
	FNCALL	_InitializeSystem,_USBDeviceInit
	FNCALL	_InitializeSystem,_UserInit
	FNCALL	_USBDeviceInit,_USBCheckBusStatus
	FNCALL	_USBDeviceInit,_USBDisableWithLongDelay
	FNCALL	_USBCheckBusStatus,_USBSoftAttach
	FNCALL	_USBSoftAttach,_USBDisableWithLongDelay
	FNCALL	_USBSoftAttach,_USBProtocolResetHandler
	FNCALL	_USBProtocolResetHandler,_ClearWatchdog
	FNCALL	_USBProtocolResetHandler,_LoadBDTandSetUOWN
	FNCALL	_USBProtocolResetHandler,_USBCBInitEP
	FNCALL	_USBCBInitEP,_HIDInitEP
	FNCALL	_USBCBInitEP,_UserInit
	FNCALL	_USBDisableWithLongDelay,_DelayRoutine
	FNCALL	_DelayRoutine,_ClearWatchdog
	FNROOT	_main
	global	_USB_SD_Ptr
psect	smallconst,class=SMALLCONST,space=0,reloc=2,noexec
global __psmallconst
__psmallconst:
	db	0
	file	"../src/usb_descriptors.c"
	line	280
_USB_SD_Ptr:
		db	low(_sd000)

		db	low(_sd001)

		db	low(_sd002)

	global __end_of_USB_SD_Ptr
__end_of_USB_SD_Ptr:
	global	_FlashSignatureWord
	global	_FlashSignatureWord_absconstaddr
_FlashSignatureWord_absconstaddr	set	0x1006
	global	_sd001
psect	smallconst
	file	"../src/usb_descriptors.c"
	line	247
_sd001:
	db	low(034h)
	db	low(03h)
	dw	(04Dh)&0ffffh
	dw	(069h)&0ffffh
	dw	(063h)&0ffffh
	dw	(072h)&0ffffh
	dw	(06Fh)&0ffffh
	dw	(063h)&0ffffh
	dw	(068h)&0ffffh
	dw	(069h)&0ffffh
	dw	(070h)&0ffffh
	dw	(020h)&0ffffh
	dw	(054h)&0ffffh
	dw	(065h)&0ffffh
	dw	(063h)&0ffffh
	dw	(068h)&0ffffh
	dw	(06Eh)&0ffffh
	dw	(06Fh)&0ffffh
	dw	(06Ch)&0ffffh
	dw	(06Fh)&0ffffh
	dw	(067h)&0ffffh
	dw	(079h)&0ffffh
	dw	(020h)&0ffffh
	dw	(049h)&0ffffh
	dw	(06Eh)&0ffffh
	dw	(063h)&0ffffh
	dw	(02Eh)&0ffffh
	global __end_of_sd001
__end_of_sd001:
	global	_CFG01
psect	smallconst
	file	"../src/usb_descriptors.c"
	line	191
_CFG01:
	db	low(09h)
	db	low(02h)
	db	low(029h)
	db	low(0)
	db	low(01h)
	db	low(01h)
	db	low(0)
	db	low(080h)
	db	low(032h)
	db	low(09h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(02h)
	db	low(03h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(09h)
	db	low(021h)
	db	low(011h)
	db	low(01h)
	db	low(0)
	db	low(01h)
	db	low(022h)
	db	low(01Dh)
	db	low(0)
	db	low(07h)
	db	low(05h)
	db	low(081h)
	db	low(03h)
	db	low(040h)
	db	low(0)
	db	low(01h)
	db	low(07h)
	db	low(05h)
	db	low(01h)
	db	low(03h)
	db	low(040h)
	db	low(0)
	db	low(01h)
	global __end_of_CFG01
__end_of_CFG01:
	global	_sd002
psect	smallconst
	file	"../src/usb_descriptors.c"
	line	252
_sd002:
	db	low(026h)
	db	low(03h)
	dw	(048h)&0ffffh
	dw	(049h)&0ffffh
	dw	(044h)&0ffffh
	dw	(020h)&0ffffh
	dw	(055h)&0ffffh
	dw	(053h)&0ffffh
	dw	(042h)&0ffffh
	dw	(020h)&0ffffh
	dw	(042h)&0ffffh
	dw	(06Fh)&0ffffh
	dw	(06Fh)&0ffffh
	dw	(074h)&0ffffh
	dw	(06Ch)&0ffffh
	dw	(06Fh)&0ffffh
	dw	(061h)&0ffffh
	dw	(064h)&0ffffh
	dw	(065h)&0ffffh
	dw	(072h)&0ffffh
	global __end_of_sd002
__end_of_sd002:
	global	_hid_rpt01
psect	smallconst
	file	"../src/usb_descriptors.c"
	line	257
_hid_rpt01:
	db	low(06h)
	db	low(0)
	db	low(0FFh)
	db	low(09h)
	db	low(01h)
	db	low(0A1h)
	db	low(01h)
	db	low(019h)
	db	low(01h)
	db	low(029h)
	db	low(040h)
	db	low(015h)
	db	low(0)
	db	low(026h)
	db	low(0FFh)
	db	low(0)
	db	low(075h)
	db	low(08h)
	db	low(095h)
	db	low(040h)
	db	low(081h)
	db	low(0)
	db	low(019h)
	db	low(01h)
	db	low(029h)
	db	low(040h)
	db	low(091h)
	db	low(0)
	db	low(0C0h)
	global __end_of_hid_rpt01
__end_of_hid_rpt01:
	global	_device_dsc
psect	smallconst
	file	"../src/usb_descriptors.c"
	line	172
_device_dsc:
	db	low(012h)
	db	low(01h)
	dw	(0200h)&0ffffh
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(08h)
	dw	(04D8h)&0ffffh
	dw	(03Ch)&0ffffh
	dw	(0101h)&0ffffh
	db	low(01h)
	db	low(02h)
	db	low(0)
	db	low(01h)
	global __end_of_device_dsc
__end_of_device_dsc:
	global	_sd000
psect	smallconst
	file	"../src/usb_descriptors.c"
	line	244
_sd000:
	db	low(04h)
	db	low(03h)
	dw	(0409h)&0ffffh
	global __end_of_sd000
__end_of_sd000:
	global	_USB_SD_Ptr
	global	_FlashSignatureWord
	global	_FlashSignatureWord_absconstaddr
_FlashSignatureWord_absconstaddr	set	0x1006
psect	_FlashSignatureWord_const,class=CODE,space=0,ovrld,reloc=2,noexec
global __p_FlashSignatureWord_const
__p_FlashSignatureWord_const:
	global	_FlashSignatureWord
_FlashSignatureWord:
	dw	(0600Dh)&0ffffh
	global __end_of_FlashSignatureWord
__end_of_FlashSignatureWord:
	global	_sd001
	global	_CFG01
	global	_sd002
	global	_hid_rpt01
	global	_device_dsc
	global	_sd000
	global	_SetupPkt
	global	EraseFlashPage@TablePointerValue
	global	WriteFlashSubBlock@Address
	global	_ProgramMemStopAddress
	global	_ProgrammedPointer
	global	_TempBDT
	global	_pDst
	global	_pSrc
	global	BlinkUSBStatus@led_count
	global	LoadBDTandSetUOWN@pBDTEntry
	global	ProcessIO@i
	global	SignFlash@i
	global	USBDeviceTasks@pBDTEntry
	global	_uint_delay_counter
	global	_wCount
	global	USBCBSuspend@OSCCONSave
	global	USBCtrlTrfTxService@bytes_to_send
	global	USBDeviceTasks@i
	global	USBStdSetCfgHandler@i
	global	USBSuspend@UIESave
	global	WriteFlashSubBlock@i
	global	_BootState
	global	_BufferedDataIndex
	global	_DeviceIsSoftDetached
	global	_EP0OutOddNeedsArmingNext
	global	_MaxPageToErase
	global	_bTRNIFCount
	global	_ctrl_trf_session_owner
	global	_ctrl_trf_state
	global	_hid_rpt_rx_len
	global	_short_pkt_status
	global	_usb_device_state
	global	_usb_stat
	global	_active_protocol
	global	_idle_rate
	global	_usb_active_cfg
	global	_usb_alt_intf
	global	_ProgrammingBuffer
	global	_PacketFromPC
	global	_PacketToPC
	global	_ep0Bi

	DABS	1,3336,4,_ep0Bi
	global	_ep1Bi

	DABS	1,3344,4,_ep1Bi
	global	_ep1Bo

	DABS	1,3340,4,_ep1Bo
	global	_EP0OutEvenBuf

	DABS	1,3348,8,_EP0OutEvenBuf
	global	_ep0BoOdd

	DABS	1,3332,4,_ep0BoOdd
	global	_ep0BoEven

	DABS	1,3328,4,_ep0BoEven
	global	_ANCON0
_ANCON0	set	0xF48
	global	_ANCON1
_ANCON1	set	0xF49
	global	_ANCON1bits
_ANCON1bits	set	0xF49
	global	_UADDR
_UADDR	set	0xF38
	global	_UCFG
_UCFG	set	0xF39
	global	_UEIE
_UEIE	set	0xF37
	global	_UEP0
_UEP0	set	0xF26
	global	_UEP1
_UEP1	set	0xF27
	global	_UEP2
_UEP2	set	0xF28
	global	_UEP3
_UEP3	set	0xF29
	global	_UEP4
_UEP4	set	0xF2A
	global	_UEP5
_UEP5	set	0xF2B
	global	_UEP6
_UEP6	set	0xF2C
	global	_UEP7
_UEP7	set	0xF2D
	global	_UIE
_UIE	set	0xF36
	global	_UIEbits
_UIEbits	set	0xF36
	global	_EECON1
_EECON1	set	0xFA6
	global	_EECON1bits
_EECON1bits	set	0xFA6
	global	_EECON2
_EECON2	set	0xFA7
	global	_INTCON
_INTCON	set	0xFF2
	global	_INTCONbits
_INTCONbits	set	0xFF2
	global	_LATCbits
_LATCbits	set	0xF8B
	global	_OSCCON
_OSCCON	set	0xFD3
	global	_OSCTUNEbits
_OSCTUNEbits	set	0xF9B
	global	_PIE2bits
_PIE2bits	set	0xFA0
	global	_PIR2bits
_PIR2bits	set	0xFA1
	global	_PORTBbits
_PORTBbits	set	0xF81
	global	_RCONbits
_RCONbits	set	0xFD0
	global	_STKPTR
_STKPTR	set	0xFFC
	global	_TABLAT
_TABLAT	set	0xFF5
	global	_TBLPTRH
_TBLPTRH	set	0xFF7
	global	_TBLPTRL
_TBLPTRL	set	0xFF6
	global	_TBLPTRU
_TBLPTRU	set	0xFF8
	global	_TRISCbits
_TRISCbits	set	0xF94
	global	_UCON
_UCON	set	0xF65
	global	_UCONbits
_UCONbits	set	0xF65
	global	_UIR
_UIR	set	0xF62
	global	_UIRbits
_UIRbits	set	0xF62
	global	_USTAT
_USTAT	set	0xF64
	global	_USTATbits
_USTATbits	set	0xF64
	global	_WDTCONbits
_WDTCONbits	set	0xFC0
	global	_hid_report_in

	DABS	1,3436,64,_hid_report_in
	global	_hid_report_out

	DABS	1,3372,64,_hid_report_out
	global	_CtrlTrfData

	DABS	1,3364,8,_CtrlTrfData
	global	_EP0OutOddBuf

	DABS	1,3356,8,_EP0OutOddBuf
; #config settings
global __CFG_PLLDIV$2
__CFG_PLLDIV$2 equ 0x0
global __CFG_STVREN$OFF
__CFG_STVREN$OFF equ 0x0
global __CFG_WDTEN$OFF
__CFG_WDTEN$OFF equ 0x0
global __CFG_XINST$OFF
__CFG_XINST$OFF equ 0x0
global __CFG_CFGPLLEN$ON
__CFG_CFGPLLEN$ON equ 0x0
global __CFG_CP0$OFF
__CFG_CP0$OFF equ 0x0
global __CFG_CPUDIV$OSC1
__CFG_CPUDIV$OSC1 equ 0x0
global __CFG_SOSCSEL$LOW
__CFG_SOSCSEL$LOW equ 0x0
global __CFG_OSC$INTOSCPLL
__CFG_OSC$INTOSCPLL equ 0x0
global __CFG_FCMEN$OFF
__CFG_FCMEN$OFF equ 0x0
global __CFG_IESO$OFF
__CFG_IESO$OFF equ 0x0
global __CFG_CLKOEC$OFF
__CFG_CLKOEC$OFF equ 0x0
global __CFG_WDTPS$1024
__CFG_WDTPS$1024 equ 0x0
global __CFG_DSBOREN$OFF
__CFG_DSBOREN$OFF equ 0x0
global __CFG_DSWDTPS$G2
__CFG_DSWDTPS$G2 equ 0x0
global __CFG_DSWDTOSC$T1OSCREF
__CFG_DSWDTOSC$T1OSCREF equ 0x0
global __CFG_DSWDTEN$OFF
__CFG_DSWDTEN$OFF equ 0x0
global __CFG_RTCOSC$T1OSCREF
__CFG_RTCOSC$T1OSCREF equ 0x0
global __CFG_IOL1WAY$OFF
__CFG_IOL1WAY$OFF equ 0x0
global __CFG_ADCSEL$BIT12
__CFG_ADCSEL$BIT12 equ 0x0
global __CFG_MSSP7B_EN$MSK7
__CFG_MSSP7B_EN$MSK7 equ 0x0
global __CFG_WPFP$PAGE_127
__CFG_WPFP$PAGE_127 equ 0x0
global __CFG_WPCFG$OFF
__CFG_WPCFG$OFF equ 0x0
global __CFG_LS48MHZ$SYS48X8
__CFG_LS48MHZ$SYS48X8 equ 0x0
global __CFG_WPEND$PAGE_WPFP
__CFG_WPEND$PAGE_WPFP equ 0x0
global __CFG_WPDIS$OFF
__CFG_WPDIS$OFF equ 0x0
	file	"dist/PIC18F27J53_PIM_XC8/production\HID_Bootloader_PIC18F27J53.X.production.as"
	line	#
psect	cinit,class=CODE,delta=1,reloc=2
global __pcinit
__pcinit:
global start_initialization
start_initialization:

global __initialization
__initialization:
psect	bssCOMRAM,class=COMRAM,space=1,noexec
global __pbssCOMRAM
__pbssCOMRAM:
	global	_SetupPkt
_SetupPkt:
       ds      8
EraseFlashPage@TablePointerValue:
       ds      4
WriteFlashSubBlock@Address:
       ds      4
	global	_ProgramMemStopAddress
_ProgramMemStopAddress:
       ds      4
	global	_ProgrammedPointer
_ProgrammedPointer:
       ds      4
	global	_TempBDT
_TempBDT:
       ds      4
	global	_pDst
_pDst:
       ds      3
	global	_pSrc
_pSrc:
       ds      3
BlinkUSBStatus@led_count:
       ds      2
LoadBDTandSetUOWN@pBDTEntry:
       ds      2
ProcessIO@i:
       ds      2
SignFlash@i:
       ds      2
USBDeviceTasks@pBDTEntry:
       ds      2
	global	_uint_delay_counter
_uint_delay_counter:
       ds      2
	global	_wCount
_wCount:
       ds      2
USBCBSuspend@OSCCONSave:
       ds      1
USBCtrlTrfTxService@bytes_to_send:
       ds      1
USBDeviceTasks@i:
       ds      1
USBStdSetCfgHandler@i:
       ds      1
USBSuspend@UIESave:
       ds      1
WriteFlashSubBlock@i:
       ds      1
	global	_BootState
_BootState:
       ds      1
	global	_BufferedDataIndex
_BufferedDataIndex:
       ds      1
	global	_DeviceIsSoftDetached
_DeviceIsSoftDetached:
       ds      1
	global	_EP0OutOddNeedsArmingNext
_EP0OutOddNeedsArmingNext:
       ds      1
	global	_MaxPageToErase
_MaxPageToErase:
       ds      1
	global	_bTRNIFCount
_bTRNIFCount:
       ds      1
	global	_ctrl_trf_session_owner
_ctrl_trf_session_owner:
       ds      1
	global	_ctrl_trf_state
_ctrl_trf_state:
       ds      1
	global	_hid_rpt_rx_len
_hid_rpt_rx_len:
       ds      1
	global	_short_pkt_status
_short_pkt_status:
       ds      1
	global	_usb_device_state
_usb_device_state:
       ds      1
	global	_usb_stat
_usb_stat:
       ds      1
	global	_active_protocol
_active_protocol:
       ds      1
	global	_idle_rate
_idle_rate:
       ds      1
	global	_usb_active_cfg
_usb_active_cfg:
       ds      1
	global	_usb_alt_intf
_usb_alt_intf:
       ds      1
psect	bssBANK0,class=BANK0,space=1,noexec
global __pbssBANK0
__pbssBANK0:
	global	_PacketFromPC
_PacketFromPC:
       ds      65
	global	_PacketToPC
_PacketToPC:
       ds      65
psect	bssBIGRAMl,class=BIGRAM,space=1,noexec
global __pbssBIGRAMl
__pbssBIGRAMl:
	global	_ProgrammingBuffer
_ProgrammingBuffer:
       ds      1024
psect cinit,class=CODE,delta=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
movlb 0
goto _main	;jump to C main() function
psect	cstackCOMRAM,class=COMRAM,space=1,noexec
global __pcstackCOMRAM
__pcstackCOMRAM:
?_BootMain:	; 0 bytes @ 0x0
?_InitializeSystem:	; 0 bytes @ 0x0
?_USBDeviceTasks:	; 0 bytes @ 0x0
?_BlinkUSBStatus:	; 0 bytes @ 0x0
??_BlinkUSBStatus:	; 0 bytes @ 0x0
?_LowVoltageCheck:	; 0 bytes @ 0x0
??_LowVoltageCheck:	; 0 bytes @ 0x0
?_ProcessIO:	; 0 bytes @ 0x0
?_DelayRoutine:	; 0 bytes @ 0x0
?_UserInit:	; 0 bytes @ 0x0
??_UserInit:	; 0 bytes @ 0x0
?_USBDeviceInit:	; 0 bytes @ 0x0
?_HIDInitEP:	; 0 bytes @ 0x0
??_HIDInitEP:	; 0 bytes @ 0x0
?_USBCheckHIDRequest:	; 0 bytes @ 0x0
??_USBCheckHIDRequest:	; 0 bytes @ 0x0
?_USBDisableWithLongDelay:	; 0 bytes @ 0x0
?_USBCheckBusStatus:	; 0 bytes @ 0x0
?_USBProtocolResetHandler:	; 0 bytes @ 0x0
?_USBWakeFromSuspend:	; 0 bytes @ 0x0
?_USBSuspend:	; 0 bytes @ 0x0
??_USBSuspend:	; 0 bytes @ 0x0
?_USBCtrlTrfSetupHandler:	; 0 bytes @ 0x0
?_USBCtrlTrfInHandler:	; 0 bytes @ 0x0
??_USBCtrlTrfInHandler:	; 0 bytes @ 0x0
?_ClearWatchdog:	; 0 bytes @ 0x0
??_ClearWatchdog:	; 0 bytes @ 0x0
?_LoadBDTandSetUOWN:	; 0 bytes @ 0x0
??_LoadBDTandSetUOWN:	; 0 bytes @ 0x0
?_USBCheckStdRequest:	; 0 bytes @ 0x0
?_USBCtrlEPServiceComplete:	; 0 bytes @ 0x0
?_USBCtrlTrfTxService:	; 0 bytes @ 0x0
??_USBCtrlTrfTxService:	; 0 bytes @ 0x0
?_USBStdGetDscHandler:	; 0 bytes @ 0x0
??_USBStdGetDscHandler:	; 0 bytes @ 0x0
?_USBStdSetCfgHandler:	; 0 bytes @ 0x0
?_USBStdGetStatusHandler:	; 0 bytes @ 0x0
??_USBStdGetStatusHandler:	; 0 bytes @ 0x0
?_USBStdFeatureReqHandler:	; 0 bytes @ 0x0
??_USBStdFeatureReqHandler:	; 0 bytes @ 0x0
?_HIDGetReportHandler:	; 0 bytes @ 0x0
??_HIDGetReportHandler:	; 0 bytes @ 0x0
?_HIDSetReportHandler:	; 0 bytes @ 0x0
??_HIDSetReportHandler:	; 0 bytes @ 0x0
?_WriteFlashSubBlock:	; 0 bytes @ 0x0
?_SignFlash:	; 0 bytes @ 0x0
?_ResetDeviceCleanly:	; 0 bytes @ 0x0
?_UnlockAndActivate:	; 0 bytes @ 0x0
??_UnlockAndActivate:	; 0 bytes @ 0x0
?_main:	; 0 bytes @ 0x0
?_USBCBWakeFromSuspend:	; 0 bytes @ 0x0
?_USBCBSuspend:	; 0 bytes @ 0x0
??_USBCBSuspend:	; 0 bytes @ 0x0
?_USBCBInitEP:	; 0 bytes @ 0x0
??_USBCBInitEP:	; 0 bytes @ 0x0
?_USBCBCheckOtherReq:	; 0 bytes @ 0x0
??_USBCBCheckOtherReq:	; 0 bytes @ 0x0
?_USBSoftAttach:	; 0 bytes @ 0x0
?_HIDTxReport:	; 0 bytes @ 0x0
?_HIDRxReport:	; 1 bytes @ 0x0
	global	USBCBInitEP@ConfigurationIndex
USBCBInitEP@ConfigurationIndex:	; 1 bytes @ 0x0
	global	LoadBDTandSetUOWN@BDTIndexToLoad
LoadBDTandSetUOWN@BDTIndexToLoad:	; 1 bytes @ 0x0
	global	HIDTxReport@len
HIDTxReport@len:	; 1 bytes @ 0x0
	global	HIDRxReport@len
HIDRxReport@len:	; 1 bytes @ 0x0
	global	UnlockAndActivate@UnlockKey
UnlockAndActivate@UnlockKey:	; 1 bytes @ 0x0
	global	DelayRoutine@DelayAmount
DelayRoutine@DelayAmount:	; 2 bytes @ 0x0
	ds   1
??_USBProtocolResetHandler:	; 0 bytes @ 0x1
??_USBCtrlEPServiceComplete:	; 0 bytes @ 0x1
??_USBStdSetCfgHandler:	; 0 bytes @ 0x1
?_EraseFlashPage:	; 0 bytes @ 0x1
??_WriteFlashSubBlock:	; 0 bytes @ 0x1
??_HIDTxReport:	; 0 bytes @ 0x1
??_HIDRxReport:	; 0 bytes @ 0x1
	global	EraseFlashPage@PageNumToErase
EraseFlashPage@PageNumToErase:	; 2 bytes @ 0x1
	ds   1
??_InitializeSystem:	; 0 bytes @ 0x2
??_DelayRoutine:	; 0 bytes @ 0x2
??_USBDeviceInit:	; 0 bytes @ 0x2
??_USBDisableWithLongDelay:	; 0 bytes @ 0x2
??_USBCheckBusStatus:	; 0 bytes @ 0x2
??_USBWakeFromSuspend:	; 0 bytes @ 0x2
??_USBCheckStdRequest:	; 0 bytes @ 0x2
??_ResetDeviceCleanly:	; 0 bytes @ 0x2
??_USBCBWakeFromSuspend:	; 0 bytes @ 0x2
??_USBSoftAttach:	; 0 bytes @ 0x2
	global	HIDTxReport@buffer
HIDTxReport@buffer:	; 1 bytes @ 0x2
	global	HIDRxReport@buffer
HIDRxReport@buffer:	; 1 bytes @ 0x2
	ds   1
??_USBDeviceTasks:	; 0 bytes @ 0x3
??_USBCtrlTrfSetupHandler:	; 0 bytes @ 0x3
??_EraseFlashPage:	; 0 bytes @ 0x3
	global	HIDTxReport@i
HIDTxReport@i:	; 1 bytes @ 0x3
	ds   4
??_SignFlash:	; 0 bytes @ 0x7
	ds   1
	global	SignFlash@pROM
SignFlash@pROM:	; 3 bytes @ 0x8
	ds   3
??_ProcessIO:	; 0 bytes @ 0xB
	ds   2
??_BootMain:	; 0 bytes @ 0xD
??_main:	; 0 bytes @ 0xD
;!
;!Data Sizes:
;!    Strings     0
;!    Constant    185
;!    Data        0
;!    BSS         1224
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM           95     13      83
;!    BANK0           160      0     130
;!    BANK1           256      0       0
;!    BANK2           256      0       0
;!    BANK3           256      0       0
;!    BANK4           256      0       0
;!    BANK5           256      0       0
;!    BANK6           256      0       0
;!    BANK7           256      0       0
;!    BANK8           256      0       0
;!    BANK9           256      0       0
;!    BANK10          256      0       0
;!    BANK11          256      0       0
;!    BANK12          256      0       0
;!    BANK13           84      0       0
;!    BANK14          176      0       0

;!
;!Pointer List with Targets:
;!
;!    ep0BoEven.ADR	PTR unsigned char  size(2) Largest target is 0
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    ep0BoOdd.ADR	PTR unsigned char  size(2) Largest target is 0
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    SignFlash@pROM	PTR  unsigned char  size(3) Largest target is 131063
;!		 -> ROM(CODE[131063]), 
;!
;!    HIDRxReport@buffer	PTR unsigned char  size(1) Largest target is 65
;!		 -> PacketFromPC(BANK0[65]), 
;!
;!    HIDTxReport@buffer	PTR unsigned char  size(1) Largest target is 65
;!		 -> PacketToPC(BANK0[65]), 
;!
;!    ep1Bi.ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    ep1Bo.ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    LoadBDTandSetUOWN@pBDTEntry	PTR volatile struct _BDT size(2) Largest target is 3759
;!		 -> NULL(NULL[0]), RAM(DATA[3759]), 
;!
;!    TempBDT.ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    ep0Bi.ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    USBDeviceTasks@pBDTEntry.ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    USBDeviceTasks@pBDTEntry	PTR volatile struct _BDT size(2) Largest target is 5
;!		 -> NULL(NULL[0]), ep0BoOdd(ABS[4]), ep0BoEven(BIGRAMl[4]), 
;!
;!    ep1Bi...ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    ep1Bo...ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    ep0Bi...ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    ep0BoOdd...ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    ep0BoEven...ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    S841$ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    TempBDT...ADR	PTR unsigned char  size(2) Largest target is 64
;!		 -> hid_report_in(BIGRAMh[64]), hid_report_out(BIGRAMh[64]), EP0OutEvenBuf(ABS[8]), EP0OutOddBuf(BIGRAMh[8]), 
;!		 -> CtrlTrfData(BIGRAMh[8]), 
;!
;!    pDst.wRom	PTR const unsigned short  size(2) Largest target is 0
;!
;!    pDst.bRom	PTR const unsigned char  size(2) Largest target is 0
;!
;!    pDst.wRam	PTR unsigned int  size(2) Largest target is 0
;!
;!    pDst.bRam	PTR unsigned char  size(2) Largest target is 0
;!
;!    S688_POINTER$wRom	PTR const unsigned short  size(2) Largest target is 0
;!
;!    pSrc.wRom	PTR const unsigned short  size(2) Largest target is 0
;!
;!    S688_POINTER$bRom	PTR const unsigned char  size(2) Largest target is 0
;!
;!    pSrc.bRom	PTR const unsigned char  size(2) Largest target is 0
;!
;!    S688_POINTER$wRam	PTR unsigned int  size(2) Largest target is 0
;!
;!    pSrc.wRam	PTR unsigned int  size(2) Largest target is 0
;!
;!    S688_POINTER$bRam	PTR unsigned char  size(2) Largest target is 0
;!
;!    pSrc.bRam	PTR unsigned char  size(2) Largest target is 0
;!
;!    USB_SD_Ptr	const PTR const unsigned char [3] size(1) Largest target is 52
;!		 -> sd002(CODE[38]), sd001(CODE[52]), sd000(CODE[4]), 
;!


;!
;!Critical Paths under _main in COMRAM
;!
;!    _BootMain->_ProcessIO
;!    _ProcessIO->_SignFlash
;!    _WriteFlashSubBlock->_UnlockAndActivate
;!    _USBCBWakeFromSuspend->_DelayRoutine
;!    _USBCtrlTrfSetupHandler->_USBCheckStdRequest
;!    _USBCtrlEPServiceComplete->_LoadBDTandSetUOWN
;!    _USBCheckStdRequest->_USBStdFeatureReqHandler
;!    _USBCheckStdRequest->_USBStdGetStatusHandler
;!    _USBStdSetCfgHandler->_USBCBInitEP
;!    _SignFlash->_EraseFlashPage
;!    _EraseFlashPage->_UnlockAndActivate
;!    _InitializeSystem->_DelayRoutine
;!    _USBProtocolResetHandler->_LoadBDTandSetUOWN
;!    _USBProtocolResetHandler->_USBCBInitEP
;!    _USBDisableWithLongDelay->_DelayRoutine
;!
;!Critical Paths under _main in BANK0
;!
;!    None.
;!
;!Critical Paths under _main in BANK1
;!
;!    None.
;!
;!Critical Paths under _main in BANK2
;!
;!    None.
;!
;!Critical Paths under _main in BANK3
;!
;!    None.
;!
;!Critical Paths under _main in BANK4
;!
;!    None.
;!
;!Critical Paths under _main in BANK5
;!
;!    None.
;!
;!Critical Paths under _main in BANK6
;!
;!    None.
;!
;!Critical Paths under _main in BANK7
;!
;!    None.
;!
;!Critical Paths under _main in BANK8
;!
;!    None.
;!
;!Critical Paths under _main in BANK9
;!
;!    None.
;!
;!Critical Paths under _main in BANK10
;!
;!    None.
;!
;!Critical Paths under _main in BANK11
;!
;!    None.
;!
;!Critical Paths under _main in BANK12
;!
;!    None.
;!
;!Critical Paths under _main in BANK13
;!
;!    None.
;!
;!Critical Paths under _main in BANK14
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 0     0      0    3980
;!                           _BootMain
;! ---------------------------------------------------------------------------------
;! (1) _BootMain                                             0     0      0    3980
;!                     _BlinkUSBStatus
;!                   _InitializeSystem
;!                    _LowVoltageCheck
;!                          _ProcessIO
;!                     _USBDeviceTasks
;! ---------------------------------------------------------------------------------
;! (2) _ProcessIO                                            2     2      0    2354
;!                                             11 COMRAM     2     2      0
;!                      _ClearWatchdog
;!                     _EraseFlashPage
;!                        _HIDRxReport
;!                        _HIDTxReport
;!                 _ResetDeviceCleanly
;!                          _SignFlash
;!                     _USBDeviceTasks
;!                 _WriteFlashSubBlock
;! ---------------------------------------------------------------------------------
;! (3) _WriteFlashSubBlock                                   6     6      0      22
;!                                              1 COMRAM     4     4      0
;!                  _UnlockAndActivate
;! ---------------------------------------------------------------------------------
;! (2) _USBDeviceTasks                                       2     2      0     712
;!                                              3 COMRAM     2     2      0
;!                  _USBCheckBusStatus
;!                _USBCtrlTrfInHandler
;!             _USBCtrlTrfSetupHandler
;!            _USBProtocolResetHandler
;!                         _USBSuspend
;!                 _USBWakeFromSuspend
;! ---------------------------------------------------------------------------------
;! (3) _USBWakeFromSuspend                                   0     0      0     290
;!               _USBCBWakeFromSuspend
;! ---------------------------------------------------------------------------------
;! (4) _USBCBWakeFromSuspend                                 0     0      0     290
;!                       _DelayRoutine
;! ---------------------------------------------------------------------------------
;! (3) _USBSuspend                                           0     0      0       0
;!                       _USBCBSuspend
;! ---------------------------------------------------------------------------------
;! (4) _USBCBSuspend                                         0     0      0       0
;! ---------------------------------------------------------------------------------
;! (3) _USBCtrlTrfSetupHandler                               0     0      0      44
;!                 _USBCBCheckOtherReq
;!                 _USBCheckStdRequest
;!           _USBCtrlEPServiceComplete
;! ---------------------------------------------------------------------------------
;! (4) _USBCtrlEPServiceComplete                             0     0      0      22
;!                  _LoadBDTandSetUOWN
;!                _USBCtrlTrfTxService
;! ---------------------------------------------------------------------------------
;! (4) _USBCheckStdRequest                                   1     1      0      22
;!                                              2 COMRAM     1     1      0
;!            _USBStdFeatureReqHandler
;!                _USBStdGetDscHandler
;!             _USBStdGetStatusHandler
;!                _USBStdSetCfgHandler
;! ---------------------------------------------------------------------------------
;! (5) _USBStdSetCfgHandler                                  0     0      0      22
;!                        _USBCBInitEP
;! ---------------------------------------------------------------------------------
;! (5) _USBStdGetStatusHandler                               2     2      0       0
;!                                              0 COMRAM     2     2      0
;! ---------------------------------------------------------------------------------
;! (5) _USBStdGetDscHandler                                  1     1      0       0
;!                                              0 COMRAM     1     1      0
;! ---------------------------------------------------------------------------------
;! (5) _USBStdFeatureReqHandler                              2     2      0       0
;!                                              0 COMRAM     2     2      0
;! ---------------------------------------------------------------------------------
;! (4) _USBCBCheckOtherReq                                   0     0      0       0
;!                 _USBCheckHIDRequest
;! ---------------------------------------------------------------------------------
;! (5) _USBCheckHIDRequest                                   0     0      0       0
;!                _HIDGetReportHandler
;!                _HIDSetReportHandler
;! ---------------------------------------------------------------------------------
;! (6) _HIDSetReportHandler                                  0     0      0       0
;! ---------------------------------------------------------------------------------
;! (6) _HIDGetReportHandler                                  0     0      0       0
;! ---------------------------------------------------------------------------------
;! (3) _USBCtrlTrfInHandler                                  0     0      0       0
;!                _USBCtrlTrfTxService
;! ---------------------------------------------------------------------------------
;! (5) _USBCtrlTrfTxService                                  0     0      0       0
;! ---------------------------------------------------------------------------------
;! (3) _SignFlash                                            4     4      0     361
;!                                              7 COMRAM     4     4      0
;!                      _ClearWatchdog
;!                     _EraseFlashPage
;!                  _UnlockAndActivate
;! ---------------------------------------------------------------------------------
;! (4) _EraseFlashPage                                       6     4      2     245
;!                                              1 COMRAM     6     4      2
;!                  _UnlockAndActivate
;! ---------------------------------------------------------------------------------
;! (4) _UnlockAndActivate                                    1     1      0      22
;!                                              0 COMRAM     1     1      0
;!                    _LowVoltageCheck
;! ---------------------------------------------------------------------------------
;! (5) _LowVoltageCheck                                      0     0      0       0
;! ---------------------------------------------------------------------------------
;! (3) _ResetDeviceCleanly                                   0     0      0     290
;!            _USBDisableWithLongDelay
;! ---------------------------------------------------------------------------------
;! (3) _HIDTxReport                                          4     3      1     532
;!                                              0 COMRAM     4     3      1
;! ---------------------------------------------------------------------------------
;! (3) _HIDRxReport                                          3     2      1     192
;!                                              0 COMRAM     3     2      1
;! ---------------------------------------------------------------------------------
;! (2) _InitializeSystem                                     0     0      0     914
;!                       _DelayRoutine
;!                      _USBDeviceInit
;!                           _UserInit
;! ---------------------------------------------------------------------------------
;! (3) _USBDeviceInit                                        0     0      0     624
;!                  _USBCheckBusStatus
;!            _USBDisableWithLongDelay
;! ---------------------------------------------------------------------------------
;! (3) _USBCheckBusStatus                                    0     0      0     334
;!                      _USBSoftAttach
;! ---------------------------------------------------------------------------------
;! (4) _USBSoftAttach                                        0     0      0     334
;!            _USBDisableWithLongDelay
;!            _USBProtocolResetHandler
;! ---------------------------------------------------------------------------------
;! (3) _USBProtocolResetHandler                              0     0      0      44
;!                      _ClearWatchdog
;!                  _LoadBDTandSetUOWN
;!                        _USBCBInitEP
;! ---------------------------------------------------------------------------------
;! (4) _USBCBInitEP                                          1     1      0      22
;!                                              0 COMRAM     1     1      0
;!                          _HIDInitEP
;!                           _UserInit
;! ---------------------------------------------------------------------------------
;! (5) _UserInit                                             0     0      0       0
;! ---------------------------------------------------------------------------------
;! (5) _HIDInitEP                                            0     0      0       0
;! ---------------------------------------------------------------------------------
;! (4) _LoadBDTandSetUOWN                                    1     1      0      22
;!                                              0 COMRAM     1     1      0
;! ---------------------------------------------------------------------------------
;! (5) _USBDisableWithLongDelay                              0     0      0     290
;!                       _DelayRoutine
;! ---------------------------------------------------------------------------------
;! (5) _DelayRoutine                                         2     0      2     290
;!                                              0 COMRAM     2     0      2
;!                      _ClearWatchdog
;! ---------------------------------------------------------------------------------
;! (6) _ClearWatchdog                                        0     0      0       0
;! ---------------------------------------------------------------------------------
;! (2) _BlinkUSBStatus                                       1     1      0       0
;!                                              0 COMRAM     1     1      0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 6
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _BootMain
;!     _BlinkUSBStatus
;!     _InitializeSystem
;!       _DelayRoutine
;!         _ClearWatchdog
;!       _USBDeviceInit
;!         _USBCheckBusStatus
;!           _USBSoftAttach
;!             _USBDisableWithLongDelay
;!               _DelayRoutine
;!                 _ClearWatchdog
;!             _USBProtocolResetHandler
;!               _ClearWatchdog
;!               _LoadBDTandSetUOWN
;!               _USBCBInitEP
;!                 _HIDInitEP
;!                 _UserInit
;!         _USBDisableWithLongDelay
;!           _DelayRoutine
;!             _ClearWatchdog
;!       _UserInit
;!     _LowVoltageCheck
;!     _ProcessIO
;!       _ClearWatchdog
;!       _EraseFlashPage
;!         _UnlockAndActivate
;!           _LowVoltageCheck
;!       _HIDRxReport
;!       _HIDTxReport
;!       _ResetDeviceCleanly
;!         _USBDisableWithLongDelay
;!           _DelayRoutine
;!             _ClearWatchdog
;!       _SignFlash
;!         _ClearWatchdog
;!         _EraseFlashPage
;!           _UnlockAndActivate
;!             _LowVoltageCheck
;!         _UnlockAndActivate
;!           _LowVoltageCheck
;!       _USBDeviceTasks
;!         _USBCheckBusStatus
;!           _USBSoftAttach
;!             _USBDisableWithLongDelay
;!               _DelayRoutine
;!                 _ClearWatchdog
;!             _USBProtocolResetHandler
;!               _ClearWatchdog
;!               _LoadBDTandSetUOWN
;!               _USBCBInitEP
;!                 _HIDInitEP
;!                 _UserInit
;!         _USBCtrlTrfInHandler
;!           _USBCtrlTrfTxService
;!         _USBCtrlTrfSetupHandler
;!           _USBCBCheckOtherReq
;!             _USBCheckHIDRequest
;!               _HIDGetReportHandler
;!               _HIDSetReportHandler
;!           _USBCheckStdRequest
;!             _USBStdFeatureReqHandler
;!             _USBStdGetDscHandler
;!             _USBStdGetStatusHandler
;!             _USBStdSetCfgHandler
;!               _USBCBInitEP
;!                 _HIDInitEP
;!                 _UserInit
;!           _USBCtrlEPServiceComplete
;!             _LoadBDTandSetUOWN
;!             _USBCtrlTrfTxService
;!         _USBProtocolResetHandler
;!           _ClearWatchdog
;!           _LoadBDTandSetUOWN
;!           _USBCBInitEP
;!             _HIDInitEP
;!             _UserInit
;!         _USBSuspend
;!           _USBCBSuspend
;!         _USBWakeFromSuspend
;!           _USBCBWakeFromSuspend
;!             _DelayRoutine
;!               _ClearWatchdog
;!       _WriteFlashSubBlock
;!         _UnlockAndActivate
;!           _LowVoltageCheck
;!     _USBDeviceTasks
;!       _USBCheckBusStatus
;!         _USBSoftAttach
;!           _USBDisableWithLongDelay
;!             _DelayRoutine
;!               _ClearWatchdog
;!           _USBProtocolResetHandler
;!             _ClearWatchdog
;!             _LoadBDTandSetUOWN
;!             _USBCBInitEP
;!               _HIDInitEP
;!               _UserInit
;!       _USBCtrlTrfInHandler
;!         _USBCtrlTrfTxService
;!       _USBCtrlTrfSetupHandler
;!         _USBCBCheckOtherReq
;!           _USBCheckHIDRequest
;!             _HIDGetReportHandler
;!             _HIDSetReportHandler
;!         _USBCheckStdRequest
;!           _USBStdFeatureReqHandler
;!           _USBStdGetDscHandler
;!           _USBStdGetStatusHandler
;!           _USBStdSetCfgHandler
;!             _USBCBInitEP
;!               _HIDInitEP
;!               _UserInit
;!         _USBCtrlEPServiceComplete
;!           _LoadBDTandSetUOWN
;!           _USBCtrlTrfTxService
;!       _USBProtocolResetHandler
;!         _ClearWatchdog
;!         _LoadBDTandSetUOWN
;!         _USBCBInitEP
;!           _HIDInitEP
;!           _UserInit
;!       _USBSuspend
;!         _USBCBSuspend
;!       _USBWakeFromSuspend
;!         _USBCBWakeFromSuspend
;!           _DelayRoutine
;!             _ClearWatchdog
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BITCOMRAM           5F      0       0       0        0.0%
;!NULL                 0      0       0       0        0.0%
;!CODE                 0      0       0       0        0.0%
;!COMRAM              5F      D      53       1       87.4%
;!STACK                0      0       0       2        0.0%
;!DATA                 0      0     4D5       3        0.0%
;!BITBANK0            A0      0       0       4        0.0%
;!BANK0               A0      0      82       5       81.3%
;!BITBANK1           100      0       0       6        0.0%
;!BANK1              100      0       0       7        0.0%
;!ABS                  0      0      D5       8        0.0%
;!BITBANK2           100      0       0       9        0.0%
;!BANK2              100      0       0      10        0.0%
;!BITBANK3           100      0       0      11        0.0%
;!BANK3              100      0       0      12        0.0%
;!BITBANK4           100      0       0      13        0.0%
;!BANK4              100      0       0      14        0.0%
;!BITBANK5           100      0       0      15        0.0%
;!BANK5              100      0       0      16        0.0%
;!BITBANK6           100      0       0      17        0.0%
;!BANK6              100      0       0      18        0.0%
;!BITBANK7           100      0       0      19        0.0%
;!BANK7              100      0       0      20        0.0%
;!BITBANK8           100      0       0      21        0.0%
;!BANK8              100      0       0      22        0.0%
;!BITBANK9           100      0       0      23        0.0%
;!BANK9              100      0       0      24        0.0%
;!BITBANK10          100      0       0      25        0.0%
;!BANK10             100      0       0      26        0.0%
;!BITBANK11          100      0       0      27        0.0%
;!BANK11             100      0       0      28        0.0%
;!BITBANK12          100      0       0      29        0.0%
;!BANK12             100      0       0      30        0.0%
;!BITBANK13           54      0       0      31        0.0%
;!BANK13              54      0       0      32        0.0%
;!BITBANK14           B0      0       0      33        0.0%
;!BANK14              B0      0       0      34        0.0%
;!BIGRAMh            104      0       0      35        0.0%
;!BIGRAMl            CFF      0     400      36       30.8%
;!BITSFR_2             0      0       0      40        0.0%
;!SFR_2                0      0       0      40        0.0%
;!BITSFR_1             0      0       0      40        0.0%
;!SFR_1                0      0       0      40        0.0%
;!BITSFR               0      0       0      40        0.0%
;!SFR                  0      0       0      40        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 322 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    8
;; This function calls:
;;		_BootMain
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	322
global __ptext0
__ptext0:
psect	text0
	file	"../src/main.c"
	line	322
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:
;incstack = 0
	opt	stack 23
	line	330
	
l3299:
;main.c: 330: {ANCON1bits.PCFG12 = 1;};
	movlb	15	; () banked
	bsf	((3913))&0ffh,4	;volatile
	line	334
;main.c: 334: if(PORTBbits.RB0 == 1)
	btfss	((c:3969)),c,0	;volatile
	goto	u2201
	goto	u2200
u2201:
	goto	l3305
u2200:
	line	339
	
l3301:; BSR set to: 15

;main.c: 335: {
;main.c: 339: {ANCON1bits.PCFG12 = 0;};
	bcf	((3913))&0ffh,4	;volatile
	line	343
;main.c: 343: goto DoFlashSignatureCheck;
	goto	l3307
	line	348
	
l3305:; BSR set to: 15

;main.c: 345: else
;main.c: 346: {
;main.c: 348: BootMain();
	call	_BootMain	;wreg free
	line	354
	
l3307:
;main.c: 354: if(*(const unsigned int*)0x1006 == 0x600D)
	movlw	low((4102))
	movwf	tblptrl
	if	1	;There is more than 1 active tblptr byte
	movlw	high((4102))
	movwf	tblptrh
	endif
	if	1	;There are 3 active tblptr bytes
	movlw	low highword((4102))
	movwf	tblptru
	endif
	tblrd	*+
	movlw	13
	xorwf	tablat,w
	bnz	u2211
tblrd	*+
	movlw	96
	xorwf	tablat,w
	btfss	status,2
	goto	u2211
	goto	u2210

u2211:
	goto	l3313
u2210:
	line	361
	
l3309:
;main.c: 355: {
;main.c: 361: if(*(const unsigned int*)0x1000 != 0xFFFF)
	movlw	low((4096))
	movwf	tblptrl
	if	1	;There is more than 1 active tblptr byte
	movlw	high((4096))
	movwf	tblptrh
	endif
	if	1	;There are 3 active tblptr bytes
	movlw	low highword((4096))
	movwf	tblptru
	endif
	tblrd	*+
	incf	tablat,w
	bnz	u2220
tblrd	*+
	incf	tablat,w
	btfsc	status,2
	goto	u2221
	goto	u2220

u2221:
	goto	l3313
u2220:
	line	366
	
l3311:
# 366 "../src/main.c"
goto 0x1000 ;# 
psect	text0
	line	378
	
l3313:
;main.c: 371: }
;main.c: 372: }
;main.c: 378: BootMain();
	call	_BootMain	;wreg free
	line	380
	
l64:
	global	start
	goto	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,88
	global	_BootMain

;; *************** function _BootMain *****************
;; Defined at:
;;		line 407 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_BlinkUSBStatus
;;		_InitializeSystem
;;		_LowVoltageCheck
;;		_ProcessIO
;;		_USBDeviceTasks
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	_BootMain_text,class=CODE,space=0,ovrld,reloc=2
	line	407
global __p_BootMain_text
__p_BootMain_text:
psect	_BootMain_text
	file	"../src/main.c"
	line	407
	global	__size_of_BootMain
	__size_of_BootMain	equ	__end_of_BootMain-_BootMain
	
_BootMain:
;incstack = 0
	global _BootMain_absaddr
	_BootMain_absaddr equ 0x30
	opt	stack 23
	line	424
	
l3287:
;main.c: 424: INTCON = 0x00;
	clrf	((c:4082)),c	;volatile
	line	438
;main.c: 438: STKPTR = 0x00;
	clrf	((c:4092)),c	;volatile
	line	447
	
l3289:
;main.c: 447: InitializeSystem();
	call	_InitializeSystem	;wreg free
	line	450
;main.c: 450: while(1)
	
l67:
	line	452
# 452 "../src/main.c"
clrwdt ;# 
psect	_BootMain_text
	line	457
	
l3291:
;main.c: 457: USBDeviceTasks();
	call	_USBDeviceTasks	;wreg free
	line	459
	
l3293:
;main.c: 459: BlinkUSBStatus();
	call	_BlinkUSBStatus	;wreg free
	line	461
	
l3295:
;main.c: 461: LowVoltageCheck();
	call	_LowVoltageCheck	;wreg free
	line	465
	
l3297:
;main.c: 465: ProcessIO();
	call	_ProcessIO	;wreg free
	goto	l67
	return	;funcret
	opt stack 0
	line	468
GLOBAL	__end_of_BootMain
	__end_of_BootMain:
	signat	_BootMain,88
	global	_ProcessIO

;; *************** function _ProcessIO *****************
;; Defined at:
;;		line 265 in file "../src/boot_18fxxjxx.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_ClearWatchdog
;;		_EraseFlashPage
;;		_HIDRxReport
;;		_HIDTxReport
;;		_ResetDeviceCleanly
;;		_SignFlash
;;		_USBDeviceTasks
;;		_WriteFlashSubBlock
;; This function is called by:
;;		_BootMain
;; This function uses a non-reentrant model
;;
psect	text2,class=CODE,space=0,reloc=2
	file	"../src/boot_18fxxjxx.c"
	line	265
global __ptext2
__ptext2:
psect	text2
	file	"../src/boot_18fxxjxx.c"
	line	265
	global	__size_of_ProcessIO
	__size_of_ProcessIO	equ	__end_of_ProcessIO-_ProcessIO
	
_ProcessIO:
;incstack = 0
	opt	stack 23
	line	275
	
l3113:
;boot_18fxxjxx.c: 267: static unsigned int i;
;boot_18fxxjxx.c: 275: if((usb_device_state != 6) || (UCONbits.SUSPND == 1))
		movlw	6
	xorwf	((c:_usb_device_state)),c,w
	btfss	status,2
	goto	u2051
	goto	u2050

u2051:
	goto	l614
u2050:
	
l3115:
	btfss	((c:3941)),c,1	;volatile
	goto	u2061
	goto	u2060
u2061:
	goto	l3117
u2060:
	goto	l614
	line	285
	
l3117:
;boot_18fxxjxx.c: 280: }
;boot_18fxxjxx.c: 285: if(BootState == 0x00)
	movf	((c:_BootState)),c,w
	btfss	status,2
	goto	u2071
	goto	u2070
u2071:
	goto	l3285
u2070:
	line	289
	
l3119:
;boot_18fxxjxx.c: 286: {
;boot_18fxxjxx.c: 289: if(!ep1Bo.Stat.UOWN)
	movlb	13	; () banked
	btfsc	((3340))&0ffh,7	;volatile
	goto	u2081
	goto	u2080
u2081:
	goto	l614
u2080:
	line	293
	
l3121:; BSR set to: 13

;boot_18fxxjxx.c: 290: {
;boot_18fxxjxx.c: 293: HIDRxReport((char *)&PacketFromPC, 0x40);
	movlw	low(040h)
	movwf	((c:HIDRxReport@len)),c
	movlw	(_PacketFromPC)&0ffh
	
	call	_HIDRxReport
	line	294
	
l3123:; BSR set to: 13

;boot_18fxxjxx.c: 294: BootState = 0x01;
	movlw	low(01h)
	movwf	((c:_BootState)),c
	line	297
	
l3125:; BSR set to: 13

;boot_18fxxjxx.c: 297: for(i = 0; i < 0x40; i++)
	clrf	((c:ProcessIO@i)),c
	clrf	((c:ProcessIO@i+1)),c
	line	298
	
l3131:
;boot_18fxxjxx.c: 298: PacketToPC.Contents[i] = 0;
	movf	((c:ProcessIO@i)),c,w
	addlw	low(_PacketToPC)
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(0)
	movwf	indf2
	line	297
	
l3133:
	infsnz	((c:ProcessIO@i)),c
	incf	((c:ProcessIO@i+1)),c
	
l3135:
		movf	((c:ProcessIO@i+1)),c,w
	bnz	u2090
	movlw	64
	subwf	 ((c:ProcessIO@i)),c,w
	btfss	status,0
	goto	u2091
	goto	u2090

u2091:
	goto	l3131
u2090:
	goto	l614
	line	309
	
l3137:; BSR set to: 0

;boot_18fxxjxx.c: 309: PacketToPC.Command = 0x02;
	movlw	low(02h)
	movwf	((_PacketToPC))&0ffh
	line	310
;boot_18fxxjxx.c: 310: PacketToPC.PacketDataFieldSize = 0x3A;
	movlw	low(03Ah)
	movwf	(0+(_PacketToPC+01h))&0ffh
	line	311
;boot_18fxxjxx.c: 311: PacketToPC.BytesPerAddress = 0x01;
	movlw	low(01h)
	movwf	(0+(_PacketToPC+02h))&0ffh
	line	312
;boot_18fxxjxx.c: 312: PacketToPC.Type1 = 0x01;
	movlw	low(01h)
	movwf	(0+(_PacketToPC+03h))&0ffh
	line	313
;boot_18fxxjxx.c: 313: PacketToPC.Address1 = (unsigned long)(uint32_t)0x1000;
	movlw	low(01000h)
	movwf	(0+(_PacketToPC+04h))&0ffh
	movlw	high(01000h)
	movwf	(1+(_PacketToPC+04h))&0ffh
	movlw	low highword(01000h)
	movwf	(2+(_PacketToPC+04h))&0ffh
	movlw	high highword(01000h)
	movwf	(3+(_PacketToPC+04h))&0ffh
	line	314
	
l3139:; BSR set to: 0

;boot_18fxxjxx.c: 314: PacketToPC.Length1 = (unsigned long)(ProgramMemStopAddress - (uint32_t)0x1000);
	movlw	0
	addwf	((c:_ProgramMemStopAddress)),c,w
	movwf	(0+(_PacketToPC+08h))&0ffh
	movlw	0F0h
	addwfc	((c:_ProgramMemStopAddress+1)),c,w
	movwf	1+(0+(_PacketToPC+08h))&0ffh
	
	movlw	0FFh
	addwfc	((c:_ProgramMemStopAddress+2)),c,w
	movwf	2+(0+(_PacketToPC+08h))&0ffh
	
	movlw	0FFh
	addwfc	((c:_ProgramMemStopAddress+3)),c,w
	movwf	3+(0+(_PacketToPC+08h))&0ffh
	line	315
	
l3141:; BSR set to: 0

;boot_18fxxjxx.c: 315: PacketToPC.Type2 = 0x03;
	movlw	low(03h)
	movwf	(0+(_PacketToPC+0Ch))&0ffh
	line	316
	
l3143:; BSR set to: 0

;boot_18fxxjxx.c: 316: PacketToPC.Address2 = (unsigned long)(uint32_t)0x01FFF8;
	movlw	low(01FFF8h)
	movwf	(0+(_PacketToPC+0Dh))&0ffh
	movlw	high(01FFF8h)
	movwf	(1+(_PacketToPC+0Dh))&0ffh
	movlw	low highword(01FFF8h)
	movwf	(2+(_PacketToPC+0Dh))&0ffh
	movlw	high highword(01FFF8h)
	movwf	(3+(_PacketToPC+0Dh))&0ffh
	line	317
	
l3145:; BSR set to: 0

;boot_18fxxjxx.c: 317: PacketToPC.Length2 = (unsigned long)8;
	movlw	low(08h)
	movwf	(0+(_PacketToPC+011h))&0ffh
	movlw	high(08h)
	movwf	(1+(_PacketToPC+011h))&0ffh
	movlw	low highword(08h)
	movwf	(2+(_PacketToPC+011h))&0ffh
	movlw	high highword(08h)
	movwf	(3+(_PacketToPC+011h))&0ffh
	line	318
	
l3147:; BSR set to: 0

;boot_18fxxjxx.c: 318: PacketToPC.Type3 = 0xFF;
	setf	(0+(_PacketToPC+015h))&0ffh
	line	319
	
l3149:; BSR set to: 0

;boot_18fxxjxx.c: 319: PacketToPC.VersionFlag = 0xA5;
	movlw	low(0A5h)
	movwf	(0+(_PacketToPC+039h))&0ffh
	line	323
	
l3151:; BSR set to: 0

;boot_18fxxjxx.c: 323: if(!ep1Bi.Stat.UOWN)
	movlb	13	; () banked
	btfsc	((3344))&0ffh,7	;volatile
	goto	u2101
	goto	u2100
u2101:
	goto	l614
u2100:
	line	325
	
l3153:; BSR set to: 13

;boot_18fxxjxx.c: 324: {
;boot_18fxxjxx.c: 325: HIDTxReport((char *)&PacketToPC, 0x40);
	movlw	low(040h)
	movwf	((c:HIDTxReport@len)),c
	movlw	(_PacketToPC)&0ffh
	
	call	_HIDTxReport
	line	326
	
l3155:
;boot_18fxxjxx.c: 326: BootState = 0x00;
	clrf	((c:_BootState)),c
	goto	l614
	line	330
	
l3157:; BSR set to: 0

;boot_18fxxjxx.c: 330: if(PacketFromPC.LockValue == 0x00)
	movf	(0+(_PacketFromPC+01h))&0ffh,w
	btfss	status,2
	goto	u2111
	goto	u2110
u2111:
	goto	l3161
u2110:
	line	332
	
l3159:; BSR set to: 0

;boot_18fxxjxx.c: 331: {
;boot_18fxxjxx.c: 332: MaxPageToErase = (((uint32_t)0x01FFF8)/1024);
	movlw	low(07Fh)
	movwf	((c:_MaxPageToErase)),c
	line	333
;boot_18fxxjxx.c: 333: ProgramMemStopAddress = ((uint32_t)0x01FFF8);
	movlw	low(01FFF8h)
	movwf	((c:_ProgramMemStopAddress)),c
	movlw	high(01FFF8h)
	movwf	((c:_ProgramMemStopAddress+1)),c
	movlw	low highword(01FFF8h)
	movwf	((c:_ProgramMemStopAddress+2)),c
	movlw	high highword(01FFF8h)
	movwf	((c:_ProgramMemStopAddress+3)),c
	line	334
;boot_18fxxjxx.c: 334: }
	goto	l3155
	line	337
	
l3161:; BSR set to: 0

;boot_18fxxjxx.c: 335: else
;boot_18fxxjxx.c: 336: {
;boot_18fxxjxx.c: 337: MaxPageToErase = ((((uint32_t)0x01FFF8)/1024) - 1);
	movlw	low(07Eh)
	movwf	((c:_MaxPageToErase)),c
	line	338
;boot_18fxxjxx.c: 338: ProgramMemStopAddress = ((((((uint32_t)0x01FFF8)/1024) - 1) + 1) * 1024);
	movlw	low(01FC00h)
	movwf	((c:_ProgramMemStopAddress)),c
	movlw	high(01FC00h)
	movwf	((c:_ProgramMemStopAddress+1)),c
	movlw	low highword(01FC00h)
	movwf	((c:_ProgramMemStopAddress+2)),c
	movlw	high highword(01FC00h)
	movwf	((c:_ProgramMemStopAddress+3)),c
	goto	l3155
	line	347
	
l3165:; BSR set to: 0

;boot_18fxxjxx.c: 347: for(i = ((uint32_t)0x1000/1024); i < (MaxPageToErase + 1); i++)
	movlw	high(04h)
	movwf	((c:ProcessIO@i+1)),c
	movlw	low(04h)
	movwf	((c:ProcessIO@i)),c
	goto	l3175
	line	349
	
l3167:
;boot_18fxxjxx.c: 348: {
;boot_18fxxjxx.c: 349: ClearWatchdog();
	call	_ClearWatchdog	;wreg free
	line	350
	
l3169:
;boot_18fxxjxx.c: 350: EraseFlashPage(i);
	movff	(c:ProcessIO@i),(c:EraseFlashPage@PageNumToErase)
	movff	(c:ProcessIO@i+1),(c:EraseFlashPage@PageNumToErase+1)
	call	_EraseFlashPage	;wreg free
	line	351
	
l3171:
;boot_18fxxjxx.c: 351: USBDeviceTasks();
	call	_USBDeviceTasks	;wreg free
	line	347
	
l3173:
	infsnz	((c:ProcessIO@i)),c
	incf	((c:ProcessIO@i+1)),c
	
l3175:
	movf	((c:_MaxPageToErase)),c,w
	movwf	(??_ProcessIO+0+0)&0ffh,c
	clrf	(??_ProcessIO+0+0+1)&0ffh,c

	movlw	01h
	addwf	(??_ProcessIO+0+0),c
	movlw	0
	addwfc	(??_ProcessIO+0+1),c
		movf	(??_ProcessIO+0+0),c,w
	subwf	((c:ProcessIO@i)),c,w
	movf	(??_ProcessIO+0+1),c,w
	subwfb	((c:ProcessIO@i+1)),c,w
	btfss	status,0
	goto	u2121
	goto	u2120

u2121:
	goto	l3167
u2120:
	goto	l3155
	line	356
	
l3177:; BSR set to: 0

;boot_18fxxjxx.c: 356: if(ProgrammedPointer == (uint32_t)0xFFFFFFFF)
		incf	((c:_ProgrammedPointer)),c,w
	bnz	u2131
	incf	((c:_ProgrammedPointer+1)),c,w
	bnz	u2131
	incf	((c:_ProgrammedPointer+2)),c,w
	bnz	u2131
	incf	((c:_ProgrammedPointer+3)),c,w
	btfss	status,2
	goto	u2131
	goto	u2130

u2131:
	goto	l3181
u2130:
	line	357
	
l3179:; BSR set to: 0

;boot_18fxxjxx.c: 357: ProgrammedPointer = PacketFromPC.Address;
	movff	0+(_PacketFromPC+01h),(c:_ProgrammedPointer)
	movff	1+(_PacketFromPC+01h),(c:_ProgrammedPointer+1)
	movff	2+(_PacketFromPC+01h),(c:_ProgrammedPointer+2)
	movff	3+(_PacketFromPC+01h),(c:_ProgrammedPointer+3)
	line	359
	
l3181:; BSR set to: 0

;boot_18fxxjxx.c: 359: if(ProgrammedPointer == (uint32_t)PacketFromPC.Address)
	movf	((c:_ProgrammedPointer)),c,w
xorwf	(0+(_PacketFromPC+01h))&0ffh,w
	bnz	u2141
movf	((c:_ProgrammedPointer+1)),c,w
xorwf	(1+(_PacketFromPC+01h))&0ffh,w
	bnz	u2141
movf	((c:_ProgrammedPointer+2)),c,w
xorwf	(2+(_PacketFromPC+01h))&0ffh,w
	bnz	u2141
movf	((c:_ProgrammedPointer+3)),c,w
xorwf	(3+(_PacketFromPC+01h))&0ffh,w
	btfss	status,2
	goto	u2141
	goto	u2140

u2141:
	goto	l3155
u2140:
	line	361
	
l3183:; BSR set to: 0

;boot_18fxxjxx.c: 360: {
;boot_18fxxjxx.c: 361: for(i = 0; i < PacketFromPC.Size; i++)
	clrf	((c:ProcessIO@i)),c
	clrf	((c:ProcessIO@i+1)),c
	goto	l3197
	line	363
	
l3185:; BSR set to: 0

;boot_18fxxjxx.c: 362: {
;boot_18fxxjxx.c: 363: ProgrammingBuffer[BufferedDataIndex] = PacketFromPC.Data[i+(0x3A-PacketFromPC.Size)];
	movf	(0+(_PacketFromPC+05h))&0ffh,w
	sublw	low(_PacketFromPC+040h)
	addwf	((c:ProcessIO@i)),c,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(_ProgrammingBuffer)
	addwf	((c:_BufferedDataIndex)),c,w
	movwf	c:fsr1l
	clrf	1+c:fsr1l
	movlw	high(_ProgrammingBuffer)
	addwfc	1+c:fsr1l
	movff	indf2,indf1
	line	364
	
l3187:; BSR set to: 0

;boot_18fxxjxx.c: 364: BufferedDataIndex++;
	incf	((c:_BufferedDataIndex)),c
	line	365
	
l3189:; BSR set to: 0

;boot_18fxxjxx.c: 365: ProgrammedPointer++;
	movlw	low(01h)
	addwf	((c:_ProgrammedPointer)),c
	movlw	0
	addwfc	((c:_ProgrammedPointer+1)),c
	addwfc	((c:_ProgrammedPointer+2)),c
	addwfc	((c:_ProgrammedPointer+3)),c
	line	366
	
l3191:; BSR set to: 0

;boot_18fxxjxx.c: 366: if(BufferedDataIndex == 0x3A)
		movlw	58
	xorwf	((c:_BufferedDataIndex)),c,w
	btfss	status,2
	goto	u2151
	goto	u2150

u2151:
	goto	l3195
u2150:
	line	368
	
l3193:; BSR set to: 0

;boot_18fxxjxx.c: 367: {
;boot_18fxxjxx.c: 368: WriteFlashSubBlock();
	call	_WriteFlashSubBlock	;wreg free
	line	361
	
l3195:
	infsnz	((c:ProcessIO@i)),c
	incf	((c:ProcessIO@i+1)),c
	
l3197:
	movlb	0	; () banked
	movf	(0+(_PacketFromPC+05h))&0ffh,w
	movwf	(??_ProcessIO+0+0)&0ffh,c
	clrf	(??_ProcessIO+0+0+1)&0ffh,c

		movf	(??_ProcessIO+0+0),c,w
	subwf	((c:ProcessIO@i)),c,w
	movf	(??_ProcessIO+0+1),c,w
	subwfb	((c:ProcessIO@i+1)),c,w
	btfss	status,0
	goto	u2161
	goto	u2160

u2161:
	goto	l3185
u2160:
	goto	l3155
	line	378
	
l3199:; BSR set to: 0

;boot_18fxxjxx.c: 378: WriteFlashSubBlock();
	call	_WriteFlashSubBlock	;wreg free
	line	379
	
l3201:
;boot_18fxxjxx.c: 379: ProgrammedPointer = 0xFFFFFFFF;
	setf	((c:_ProgrammedPointer)),c
	setf	((c:_ProgrammedPointer+1)),c
	setf	((c:_ProgrammedPointer+2)),c
	setf	((c:_ProgrammedPointer+3)),c
	goto	l3155
	line	384
	
l3205:; BSR set to: 0

;boot_18fxxjxx.c: 384: PacketToPC.Command = 0x07;
	movlw	low(07h)
	movwf	((_PacketToPC))&0ffh
	line	385
	
l3207:; BSR set to: 0

;boot_18fxxjxx.c: 385: PacketToPC.Address = PacketFromPC.Address;
	movff	0+(_PacketFromPC+01h),0+(_PacketToPC+01h)
	movff	1+(_PacketFromPC+01h),1+(_PacketToPC+01h)
	movff	2+(_PacketFromPC+01h),2+(_PacketToPC+01h)
	movff	3+(_PacketFromPC+01h),3+(_PacketToPC+01h)
	line	386
	
l3209:; BSR set to: 0

;boot_18fxxjxx.c: 386: PacketToPC.Size = PacketFromPC.Size;
	movff	0+(_PacketFromPC+05h),0+(_PacketToPC+05h)
	line	389
	
l3211:; BSR set to: 0

;boot_18fxxjxx.c: 389: TBLPTRU = PacketFromPC.Address >> 16;
	movff	0+2+0+(_PacketFromPC+01h),(c:4088)	;volatile
	line	390
	
l3213:; BSR set to: 0

;boot_18fxxjxx.c: 390: TBLPTRH = PacketFromPC.Address >> 8;
	movff	0+1+0+(_PacketFromPC+01h),(c:4087)	;volatile
	line	391
	
l3215:; BSR set to: 0

;boot_18fxxjxx.c: 391: TBLPTRL = PacketFromPC.Address;
	movff	0+(_PacketFromPC+01h),(c:4086)	;volatile
	line	392
	
l3217:; BSR set to: 0

;boot_18fxxjxx.c: 392: for(i = 0; i < PacketFromPC.Size; i++)
	clrf	((c:ProcessIO@i)),c
	clrf	((c:ProcessIO@i+1)),c
	goto	l3223
	line	393
	
l641:; BSR set to: 0

	line	395
# 395 "../src/boot_18fxxjxx.c"
tblrdpostinc ;# 
psect	text2
	line	397
	
l3219:
;boot_18fxxjxx.c: 397: PacketToPC.Data[i+((0x40 - 6) - PacketFromPC.Size)] = TABLAT;
	movlb	0	; () banked
	movf	(0+(_PacketFromPC+05h))&0ffh,w
	sublw	low(_PacketToPC+040h)
	addwf	((c:ProcessIO@i)),c,w
	movwf	fsr2l
	clrf	fsr2h
	movff	(c:4085),indf2	;volatile

	line	392
	
l3221:; BSR set to: 0

	infsnz	((c:ProcessIO@i)),c
	incf	((c:ProcessIO@i+1)),c
	
l3223:; BSR set to: 0

	movf	(0+(_PacketFromPC+05h))&0ffh,w
	movwf	(??_ProcessIO+0+0)&0ffh,c
	clrf	(??_ProcessIO+0+0+1)&0ffh,c

		movf	(??_ProcessIO+0+0),c,w
	subwf	((c:ProcessIO@i)),c,w
	movf	(??_ProcessIO+0+1),c,w
	subwfb	((c:ProcessIO@i+1)),c,w
	btfss	status,0
	goto	u2171
	goto	u2170

u2171:
	goto	l641
u2170:
	
l642:; BSR set to: 0

	line	409
;boot_18fxxjxx.c: 398: }
;boot_18fxxjxx.c: 409: if(!ep1Bi.Stat.UOWN)
	movlb	13	; () banked
	btfsc	((3344))&0ffh,7	;volatile
	goto	u2181
	goto	u2180
u2181:
	goto	l614
u2180:
	line	411
	
l3225:; BSR set to: 13

;boot_18fxxjxx.c: 410: {
;boot_18fxxjxx.c: 411: HIDTxReport((char *)&PacketToPC, 0x40);
	movlw	low(040h)
	movwf	((c:HIDTxReport@len)),c
	movlw	(_PacketToPC)&0ffh
	
	call	_HIDTxReport
	goto	l3155
	line	416
	
l3229:; BSR set to: 0

;boot_18fxxjxx.c: 416: SignFlash();
	call	_SignFlash	;wreg free
	goto	l3155
	line	425
	
l3233:; BSR set to: 0

;boot_18fxxjxx.c: 425: PacketToPC.Command = 0x0C;
	movlw	low(0Ch)
	movwf	((_PacketToPC))&0ffh
	line	426
;boot_18fxxjxx.c: 426: PacketToPC.BootloaderVersion = ((unsigned int)1 << 8)| 2;
	movlw	high(0102h)
	movwf	(1+(_PacketToPC+01h))&0ffh
	movlw	low(0102h)
	movwf	(0+(_PacketToPC+01h))&0ffh
	line	427
	
l3235:; BSR set to: 0

;boot_18fxxjxx.c: 427: PacketToPC.ApplicationVersion = *(const unsigned int*)0x1016;
	movlw	low((4118))
	movwf	tblptrl
	if	1	;There is more than 1 active tblptr byte
	movlw	high((4118))
	movwf	tblptrh
	endif
	if	1	;There are 3 active tblptr bytes
	movlw	low highword((4118))
	movwf	tblptru
	endif
	tblrd*+
	
	movff	tablat,0+(_PacketToPC+03h)
	tblrd*-
	
	movff	tablat,1+(_PacketToPC+03h)

	line	428
	
l3237:; BSR set to: 0

;boot_18fxxjxx.c: 428: PacketToPC.SignatureAddress = 0x1006;
	movlw	low(01006h)
	movwf	(0+(_PacketToPC+05h))&0ffh
	movlw	high(01006h)
	movwf	(1+(_PacketToPC+05h))&0ffh
	movlw	low highword(01006h)
	movwf	(2+(_PacketToPC+05h))&0ffh
	movlw	high highword(01006h)
	movwf	(3+(_PacketToPC+05h))&0ffh
	line	429
	
l3239:; BSR set to: 0

;boot_18fxxjxx.c: 429: PacketToPC.SignatureValue = 0x600D;
	movlw	high(0600Dh)
	movwf	(1+(_PacketToPC+09h))&0ffh
	movlw	low(0600Dh)
	movwf	(0+(_PacketToPC+09h))&0ffh
	line	430
	
l3241:; BSR set to: 0

;boot_18fxxjxx.c: 430: PacketToPC.ErasePageSize = 1024;
	movlw	low(0400h)
	movwf	(0+(_PacketToPC+0Bh))&0ffh
	movlw	high(0400h)
	movwf	(1+(_PacketToPC+0Bh))&0ffh
	movlw	low highword(0400h)
	movwf	(2+(_PacketToPC+0Bh))&0ffh
	movlw	high highword(0400h)
	movwf	(3+(_PacketToPC+0Bh))&0ffh
	line	431
	
l3243:; BSR set to: 0

;boot_18fxxjxx.c: 431: PacketToPC.Config1LMask = 0xFF;
	setf	(0+(_PacketToPC+0Fh))&0ffh
	line	432
	
l3245:; BSR set to: 0

;boot_18fxxjxx.c: 432: PacketToPC.Config1HMask = 0xFF;
	setf	(0+(_PacketToPC+010h))&0ffh
	line	433
	
l3247:; BSR set to: 0

;boot_18fxxjxx.c: 433: PacketToPC.Config2LMask = 0xFF;
	setf	(0+(_PacketToPC+011h))&0ffh
	line	434
	
l3249:; BSR set to: 0

;boot_18fxxjxx.c: 434: PacketToPC.Config2HMask = 0xFF;
	setf	(0+(_PacketToPC+012h))&0ffh
	line	435
	
l3251:; BSR set to: 0

;boot_18fxxjxx.c: 435: PacketToPC.Config3LMask = 0xFF;
	setf	(0+(_PacketToPC+013h))&0ffh
	line	436
	
l3253:; BSR set to: 0

;boot_18fxxjxx.c: 436: PacketToPC.Config3HMask = 0xFF;
	setf	(0+(_PacketToPC+014h))&0ffh
	line	437
	
l3255:; BSR set to: 0

;boot_18fxxjxx.c: 437: PacketToPC.Config4LMask = 0xFF;
	setf	(0+(_PacketToPC+015h))&0ffh
	line	438
	
l3257:; BSR set to: 0

;boot_18fxxjxx.c: 438: PacketToPC.Config4HMask = 0xFF;
	setf	(0+(_PacketToPC+016h))&0ffh
	line	439
	
l3259:; BSR set to: 0

;boot_18fxxjxx.c: 439: PacketToPC.Config5LMask = 0x00;
	clrf	(0+(_PacketToPC+017h))&0ffh
	line	440
	
l3261:; BSR set to: 0

;boot_18fxxjxx.c: 440: PacketToPC.Config5HMask = 0x00;
	clrf	(0+(_PacketToPC+018h))&0ffh
	line	441
	
l3263:; BSR set to: 0

;boot_18fxxjxx.c: 441: PacketToPC.Config6LMask = 0x00;
	clrf	(0+(_PacketToPC+019h))&0ffh
	line	442
	
l3265:; BSR set to: 0

;boot_18fxxjxx.c: 442: PacketToPC.Config6HMask = 0x00;
	clrf	(0+(_PacketToPC+01Ah))&0ffh
	line	443
	
l3267:; BSR set to: 0

;boot_18fxxjxx.c: 443: PacketToPC.Config7LMask = 0x00;
	clrf	(0+(_PacketToPC+01Bh))&0ffh
	line	444
	
l3269:; BSR set to: 0

;boot_18fxxjxx.c: 444: PacketToPC.Config7HMask = 0x00;
	clrf	(0+(_PacketToPC+01Ch))&0ffh
	line	445
	
l3271:; BSR set to: 0

;boot_18fxxjxx.c: 445: PacketToPC.Config8LMask = 0x00;
	clrf	(0+(_PacketToPC+01Dh))&0ffh
	line	446
	
l3273:; BSR set to: 0

;boot_18fxxjxx.c: 446: PacketToPC.Config8HMask = 0x00;
	clrf	(0+(_PacketToPC+01Eh))&0ffh
	line	449
	
l3275:; BSR set to: 0

;boot_18fxxjxx.c: 449: if(!ep1Bi.Stat.UOWN)
	movlb	13	; () banked
	btfsc	((3344))&0ffh,7	;volatile
	goto	u2191
	goto	u2190
u2191:
	goto	l614
u2190:
	line	451
	
l3277:; BSR set to: 13

;boot_18fxxjxx.c: 450: {
;boot_18fxxjxx.c: 451: HIDTxReport((char *)&PacketToPC, 0x40);
	movlw	low(040h)
	movwf	((c:HIDTxReport@len)),c
	movlw	(_PacketToPC)&0ffh
	
	call	_HIDTxReport
	goto	l3155
	line	456
	
l3281:; BSR set to: 0

;boot_18fxxjxx.c: 456: ResetDeviceCleanly();
	call	_ResetDeviceCleanly	;wreg free
	goto	l3155
	line	305
	
l3285:
	movlb	0	; () banked
	movf	((_PacketFromPC))&0ffh,w
	; Switch size 1, requested type "space"
; Number of cases is 9, Range of values is 2 to 12
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           28    15 (average)
;	Chosen strategy is simple_byte

	xorlw	2^0	; case 2
	skipnz
	goto	l3137
	xorlw	3^2	; case 3
	skipnz
	goto	l3157
	xorlw	4^3	; case 4
	skipnz
	goto	l3165
	xorlw	5^4	; case 5
	skipnz
	goto	l3177
	xorlw	6^5	; case 6
	skipnz
	goto	l3199
	xorlw	7^6	; case 7
	skipnz
	goto	l3205
	xorlw	8^7	; case 8
	skipnz
	goto	l3281
	xorlw	9^8	; case 9
	skipnz
	goto	l3229
	xorlw	12^9	; case 12
	skipnz
	goto	l3233
	goto	l3155

	line	464
	
l614:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_ProcessIO
	__end_of_ProcessIO:
	signat	_ProcessIO,88
	global	_WriteFlashSubBlock

;; *************** function _WriteFlashSubBlock *****************
;; Defined at:
;;		line 576 in file "../src/boot_18fxxjxx.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  WordToWrite     2    0        unsigned int 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_UnlockAndActivate
;; This function is called by:
;;		_ProcessIO
;; This function uses a non-reentrant model
;;
psect	text3,class=CODE,space=0,reloc=2
	line	576
global __ptext3
__ptext3:
psect	text3
	file	"../src/boot_18fxxjxx.c"
	line	576
	global	__size_of_WriteFlashSubBlock
	__size_of_WriteFlashSubBlock	equ	__end_of_WriteFlashSubBlock-_WriteFlashSubBlock
	
_WriteFlashSubBlock:
;incstack = 0
	opt	stack 26
	line	583
	
l3019:
;boot_18fxxjxx.c: 578: static unsigned char i;
;boot_18fxxjxx.c: 579: uint16_t WordToWrite;
;boot_18fxxjxx.c: 580: static uint32_t Address;
;boot_18fxxjxx.c: 583: i = 0;
	clrf	((c:WriteFlashSubBlock@i)),c
	line	584
;boot_18fxxjxx.c: 584: while(BufferedDataIndex > 0)
	goto	l3043
	line	587
	
l3021:
;boot_18fxxjxx.c: 585: {
;boot_18fxxjxx.c: 587: Address = (ProgrammedPointer - BufferedDataIndex);
	movf	((c:_BufferedDataIndex)),c,w
	movwf	(??_WriteFlashSubBlock+0+0)&0ffh,c
	movlw	0
	btfsc	(??_WriteFlashSubBlock+0+0)&0ffh,c,7
	movlw	255
	movwf	(??_WriteFlashSubBlock+0+0+1)&0ffh,c
	movwf	(??_WriteFlashSubBlock+0+0+2)&0ffh,c
	movwf	(??_WriteFlashSubBlock+0+0+3)&0ffh,c
	movf	(??_WriteFlashSubBlock+0+0),c,w
	subwf	((c:_ProgrammedPointer)),c,w
	movwf	((c:WriteFlashSubBlock@Address)),c
	movf	(??_WriteFlashSubBlock+0+1),c,w
	subwfb	((c:_ProgrammedPointer+1)),c,w
	movwf	1+((c:WriteFlashSubBlock@Address)),c
	
	movf	(??_WriteFlashSubBlock+0+2),c,w
	subwfb	((c:_ProgrammedPointer+2)),c,w
	movwf	2+((c:WriteFlashSubBlock@Address)),c
	
	movf	(??_WriteFlashSubBlock+0+3),c,w
	subwfb	((c:_ProgrammedPointer+3)),c,w
	movwf	3+((c:WriteFlashSubBlock@Address)),c
	line	588
	
l3023:
;boot_18fxxjxx.c: 588: TBLPTRU = Address >> 16;
	movff	0+((c:WriteFlashSubBlock@Address)+02h),(c:4088)	;volatile
	line	589
	
l3025:
;boot_18fxxjxx.c: 589: TBLPTRH = Address >> 8;
	movff	0+((c:WriteFlashSubBlock@Address)+01h),(c:4087)	;volatile
	line	590
	
l3027:
;boot_18fxxjxx.c: 590: TBLPTRL = (uint8_t)Address;
	movff	(c:WriteFlashSubBlock@Address),(c:4086)	;volatile
	line	592
	
l3029:
;boot_18fxxjxx.c: 592: TABLAT = ProgrammingBuffer[i];
	movlw	low(_ProgrammingBuffer)
	addwf	((c:WriteFlashSubBlock@i)),c,w
	movwf	c:fsr2l
	clrf	1+c:fsr2l
	movlw	high(_ProgrammingBuffer)
	addwfc	1+c:fsr2l
	movf	indf2,w
	movwf	((c:4085)),c	;volatile
	line	594
# 594 "../src/boot_18fxxjxx.c"
tblwtpostinc ;# 
psect	text3
	line	596
	
l3031:
;boot_18fxxjxx.c: 596: i++;
	incf	((c:WriteFlashSubBlock@i)),c
	line	597
	
l3033:
;boot_18fxxjxx.c: 597: TABLAT = ProgrammingBuffer[i];
	movlw	low(_ProgrammingBuffer)
	addwf	((c:WriteFlashSubBlock@i)),c,w
	movwf	c:fsr2l
	clrf	1+c:fsr2l
	movlw	high(_ProgrammingBuffer)
	addwfc	1+c:fsr2l
	movf	indf2,w
	movwf	((c:4085)),c	;volatile
	line	599
# 599 "../src/boot_18fxxjxx.c"
tblwt ;# 
psect	text3
	line	601
	
l3035:
;boot_18fxxjxx.c: 601: i++;
	incf	((c:WriteFlashSubBlock@i)),c
	line	617
	
l3037:
;boot_18fxxjxx.c: 617: EECON1 = 0b00100100;
	movlw	low(024h)
	movwf	((c:4006)),c	;volatile
	line	618
	
l3039:
;boot_18fxxjxx.c: 618: UnlockAndActivate(0xB5);
	movlw	(0B5h)&0ffh
	
	call	_UnlockAndActivate
	line	620
	
l3041:
;boot_18fxxjxx.c: 620: BufferedDataIndex = BufferedDataIndex - 0x02;
	movlw	(-2)&0ffh
	addwf	((c:_BufferedDataIndex)),c
	line	584
	
l3043:
		movf	((c:_BufferedDataIndex)),c,w
	xorlw	80h
	addlw	-(80h^01h)
	btfsc	status,0
	goto	u2011
	goto	u2010

u2011:
	goto	l3021
u2010:
	line	622
	
l673:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_WriteFlashSubBlock
	__end_of_WriteFlashSubBlock:
	signat	_WriteFlashSubBlock,88
	global	_USBDeviceTasks

;; *************** function _USBDeviceTasks *****************
;; Defined at:
;;		line 463 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_USBCheckBusStatus
;;		_USBCtrlTrfInHandler
;;		_USBCtrlTrfSetupHandler
;;		_USBProtocolResetHandler
;;		_USBSuspend
;;		_USBWakeFromSuspend
;; This function is called by:
;;		_BootMain
;;		_ProcessIO
;; This function uses a non-reentrant model
;;
psect	text4,class=CODE,space=0,reloc=2
	file	"../src/usb_device.c"
	line	463
global __ptext4
__ptext4:
psect	text4
	file	"../src/usb_device.c"
	line	463
	global	__size_of_USBDeviceTasks
	__size_of_USBDeviceTasks	equ	__end_of_USBDeviceTasks-_USBDeviceTasks
	
_USBDeviceTasks:
;incstack = 0
	opt	stack 24
	line	469
	
l2903:
;usb_device.c: 465: static volatile BDT* pBDTEntry;
;usb_device.c: 466: static uint8_t i;
;usb_device.c: 469: USBCheckBusStatus();
	call	_USBCheckBusStatus	;wreg free
	line	474
	
l2905:
;usb_device.c: 474: if(usb_device_state == 0) return;
	movf	((c:_usb_device_state)),c,w
	btfss	status,2
	goto	u1781
	goto	u1780
u1781:
	goto	l291
u1780:
	goto	l292
	
l291:
	line	480
;usb_device.c: 480: if(UIRbits.ACTVIF) USBWakeFromSuspend();
	btfss	((c:3938)),c,2	;volatile
	goto	u1791
	goto	u1790
u1791:
	goto	l2911
u1790:
	
l2909:
	call	_USBWakeFromSuspend	;wreg free
	line	485
	
l2911:
;usb_device.c: 485: if(UCONbits.SUSPND == 1) return;
	btfss	((c:3941)),c,1	;volatile
	goto	u1801
	goto	u1800
u1801:
	goto	l294
u1800:
	goto	l292
	
l294:
	line	493
;usb_device.c: 493: if(UIRbits.URSTIF) USBProtocolResetHandler();
	btfss	((c:3938)),c,0	;volatile
	goto	u1811
	goto	u1810
u1811:
	goto	l2917
u1810:
	
l2915:
	call	_USBProtocolResetHandler	;wreg free
	line	498
	
l2917:
;usb_device.c: 498: if(UIRbits.IDLEIF) USBSuspend();
	btfss	((c:3938)),c,4	;volatile
	goto	u1821
	goto	u1820
u1821:
	goto	l2921
u1820:
	
l2919:
	call	_USBSuspend	;wreg free
	line	515
	
l2921:
;usb_device.c: 515: if(usb_device_state < 3) return;
		movlw	03h-0
	cpfslt	((c:_usb_device_state)),c
	goto	u1831
	goto	u1830

u1831:
	goto	l297
u1830:
	goto	l292
	
l297:
	line	520
;usb_device.c: 520: for(bTRNIFCount = 0; bTRNIFCount < 4; bTRNIFCount++)
	clrf	((c:_bTRNIFCount)),c
	line	521
	
l298:
	line	522
;usb_device.c: 521: {
;usb_device.c: 522: if(UIRbits.TRNIF)
	btfss	((c:3938)),c,3	;volatile
	goto	u1841
	goto	u1840
u1841:
	goto	l292
u1840:
	line	525
	
l2929:
;usb_device.c: 523: {
;usb_device.c: 525: USTATSave = USTAT;
	movf	((c:3940)),c,w	;volatile
	line	526
	
l2931:
;usb_device.c: 526: if((USTAT & 0x7C) == ((0x00<<3)|(0<<2)))
	movff	(c:3940),??_USBDeviceTasks+0+0	;volatile
	movlw	07Ch
	andwf	(??_USBDeviceTasks+0+0),c
	btfss	status,2
	goto	u1851
	goto	u1850
u1851:
	goto	l2959
u1850:
	line	529
	
l2933:
;usb_device.c: 527: {
;usb_device.c: 529: if(USTATbits.PPBI == 0)
	btfsc	((c:3940)),c,1	;volatile
	goto	u1861
	goto	u1860
u1861:
	goto	l2937
u1860:
	line	532
	
l2935:
;usb_device.c: 530: {
;usb_device.c: 532: pBDTEntry = &ep0BoEven;
		movlw	low(3328)
	movwf	((c:USBDeviceTasks@pBDTEntry)),c
	movlw	high(3328)
	movwf	((c:USBDeviceTasks@pBDTEntry+1)),c

	line	533
;usb_device.c: 533: }
	goto	l2939
	line	537
	
l2937:
;usb_device.c: 534: else
;usb_device.c: 535: {
;usb_device.c: 537: pBDTEntry = &ep0BoOdd;
		movlw	low(3332)
	movwf	((c:USBDeviceTasks@pBDTEntry)),c
	movlw	high(3332)
	movwf	((c:USBDeviceTasks@pBDTEntry+1)),c

	line	541
	
l2939:
;usb_device.c: 538: }
;usb_device.c: 541: UIRbits.TRNIF = 0;
	bcf	((c:3938)),c,3	;volatile
	line	544
	
l2941:
;usb_device.c: 544: if(pBDTEntry->Stat.PID == 0b00001101)
	movff	(c:USBDeviceTasks@pBDTEntry),fsr2l
	movff	(c:USBDeviceTasks@pBDTEntry+1),fsr2h
	rrcf	(c:indf2),c,w
	rrcf	wreg,f
	andlw	(1<<4)-1
	xorlw	0Dh
	btfss	status,2
	goto	u1871
	goto	u1870
u1871:
	goto	l308
u1870:
	line	548
	
l2943:
;usb_device.c: 545: {
;usb_device.c: 548: for(i = 0; i < sizeof(CTRL_TRF_SETUP); i++)
	clrf	((c:USBDeviceTasks@i)),c
	line	550
	
l2949:
;usb_device.c: 549: {
;usb_device.c: 550: SetupPkt._byte[i] = *pBDTEntry->ADR++;
	lfsr	2,02h
	movf	((c:USBDeviceTasks@pBDTEntry)),c,w
	addwf	fsr2l
	movf	((c:USBDeviceTasks@pBDTEntry+1)),c,w
	addwfc	fsr2h
	movff	postinc2,??_USBDeviceTasks+0+0
	movff	postdec2,??_USBDeviceTasks+0+0+1
	movff	??_USBDeviceTasks+0+0,fsr2l
	movff	??_USBDeviceTasks+0+1,fsr2h
	movf	((c:USBDeviceTasks@i)),c,w
	addlw	low(_SetupPkt)
	movwf	fsr1l
	clrf	fsr1h
	movff	indf2,indf1
	
l2951:
	lfsr	2,02h
	movf	((c:USBDeviceTasks@pBDTEntry)),c,w
	addwf	fsr2l
	movf	((c:USBDeviceTasks@pBDTEntry+1)),c,w
	addwfc	fsr2h
	incf	postinc2
	movlw	0
	addwfc	postdec2
	line	548
	
l2953:
	incf	((c:USBDeviceTasks@i)),c
	
l2955:
		movlw	08h-1
	cpfsgt	((c:USBDeviceTasks@i)),c
	goto	u1881
	goto	u1880

u1881:
	goto	l2949
u1880:
	line	555
	
l2957:
;usb_device.c: 551: }
;usb_device.c: 555: USBCtrlTrfSetupHandler();
	call	_USBCtrlTrfSetupHandler	;wreg free
	line	556
;usb_device.c: 556: }
	goto	l2965
	line	563
	
l2959:
;usb_device.c: 563: else if(USTAT == ((0x00<<3)|(1<<2)))
		movlw	4
	xorwf	((c:3940)),c,w	;volatile
	btfss	status,2
	goto	u1891
	goto	u1890

u1891:
	goto	l309
u1890:
	line	566
	
l2961:
;usb_device.c: 564: {
;usb_device.c: 566: UIRbits.TRNIF = 0;
	bcf	((c:3938)),c,3	;volatile
	line	567
	
l2963:
;usb_device.c: 567: USBCtrlTrfInHandler();
	call	_USBCtrlTrfInHandler	;wreg free
	line	568
;usb_device.c: 568: }
	goto	l2965
	line	569
	
l309:
	line	575
;usb_device.c: 569: else
;usb_device.c: 570: {
;usb_device.c: 575: UIRbits.TRNIF = 0;
	bcf	((c:3938)),c,3	;volatile
	goto	l2965
	line	576
	
l308:
	line	520
;usb_device.c: 576: }
;usb_device.c: 577: }
	
l2965:
	incf	((c:_bTRNIFCount)),c
	
l2967:
		movlw	04h-1
	cpfsgt	((c:_bTRNIFCount)),c
	goto	u1901
	goto	u1900

u1901:
	goto	l298
u1900:
	line	584
	
l292:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBDeviceTasks
	__end_of_USBDeviceTasks:
	signat	_USBDeviceTasks,88
	global	_USBWakeFromSuspend

;; *************** function _USBWakeFromSuspend *****************
;; Defined at:
;;		line 701 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_USBCBWakeFromSuspend
;; This function is called by:
;;		_USBDeviceTasks
;; This function uses a non-reentrant model
;;
psect	text5,class=CODE,space=0,reloc=2
	line	701
global __ptext5
__ptext5:
psect	text5
	file	"../src/usb_device.c"
	line	701
	global	__size_of_USBWakeFromSuspend
	__size_of_USBWakeFromSuspend	equ	__end_of_USBWakeFromSuspend-_USBWakeFromSuspend
	
_USBWakeFromSuspend:
;incstack = 0
	opt	stack 25
	line	706
	
l2815:
;usb_device.c: 706: USBCBWakeFromSuspend();
	call	_USBCBWakeFromSuspend	;wreg free
	line	709
	
l2817:
;usb_device.c: 709: UCONbits.SUSPND = 0;
	bcf	((c:3941)),c,1	;volatile
	line	710
	
l2819:
;usb_device.c: 710: UIEbits.ACTVIE = 0;
	movlb	15	; () banked
	bcf	((3894))&0ffh,2	;volatile
	line	711
;usb_device.c: 711: while(UIRbits.ACTVIF){UIRbits.ACTVIF = 0;}
	goto	l319
	
l320:
	bcf	((c:3938)),c,2	;volatile
	
l319:
	btfsc	((c:3938)),c,2	;volatile
	goto	u1681
	goto	u1680
u1681:
	goto	l320
u1680:
	line	713
	
l322:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBWakeFromSuspend
	__end_of_USBWakeFromSuspend:
	signat	_USBWakeFromSuspend,88
	global	_USBCBWakeFromSuspend

;; *************** function _USBCBWakeFromSuspend *****************
;; Defined at:
;;		line 736 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_DelayRoutine
;; This function is called by:
;;		_USBWakeFromSuspend
;; This function uses a non-reentrant model
;;
psect	text6,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	736
global __ptext6
__ptext6:
psect	text6
	file	"../src/main.c"
	line	736
	global	__size_of_USBCBWakeFromSuspend
	__size_of_USBCBWakeFromSuspend	equ	__end_of_USBCBWakeFromSuspend-_USBCBWakeFromSuspend
	
_USBCBWakeFromSuspend:
;incstack = 0
	opt	stack 25
	line	742
	
l2671:
;main.c: 742: DelayRoutine(0x300);
	movlw	high(0300h)
	movwf	((c:DelayRoutine@DelayAmount+1)),c
	movlw	low(0300h)
	movwf	((c:DelayRoutine@DelayAmount)),c
	call	_DelayRoutine	;wreg free
	line	753
	
l93:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCBWakeFromSuspend
	__end_of_USBCBWakeFromSuspend:
	signat	_USBCBWakeFromSuspend,88
	global	_USBSuspend

;; *************** function _USBSuspend *****************
;; Defined at:
;;		line 609 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : F/F
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_USBCBSuspend
;; This function is called by:
;;		_USBDeviceTasks
;; This function uses a non-reentrant model
;;
psect	text7,class=CODE,space=0,reloc=2
	file	"../src/usb_device.c"
	line	609
global __ptext7
__ptext7:
psect	text7
	file	"../src/usb_device.c"
	line	609
	global	__size_of_USBSuspend
	__size_of_USBSuspend	equ	__end_of_USBSuspend-_USBSuspend
	
_USBSuspend:
;incstack = 0
	opt	stack 27
	line	646
	
l2821:
;usb_device.c: 611: static unsigned char UIESave;
;usb_device.c: 646: UIESave = UIE;
	movff	(3894),(c:USBSuspend@UIESave)	;volatile
	line	647
	
l2823:
;usb_device.c: 647: UIE = 0b00000100;
	movlw	low(04h)
	movlb	15	; () banked
	movwf	((3894))&0ffh	;volatile
	line	651
	
l2825:; BSR set to: 15

;usb_device.c: 651: UIRbits.IDLEIF = 0;
	bcf	((c:3938)),c,4	;volatile
	line	652
	
l2827:; BSR set to: 15

;usb_device.c: 652: UCONbits.SUSPND = 1;
	bsf	((c:3941)),c,1	;volatile
	line	659
	
l2829:; BSR set to: 15

;usb_device.c: 659: PIR2bits.USBIF = 0;
	bcf	((c:4001)),c,4	;volatile
	line	663
	
l2831:; BSR set to: 15

;usb_device.c: 663: PIE2bits.USBIE = 1;
	bsf	((c:4000)),c,4	;volatile
	line	672
	
l2833:; BSR set to: 15

;usb_device.c: 672: USBCBSuspend();
	call	_USBCBSuspend	;wreg free
	line	679
	
l2835:
;usb_device.c: 679: PIE2bits.USBIE = 0;
	bcf	((c:4000)),c,4	;volatile
	line	680
	
l2837:
;usb_device.c: 680: UIE |= UIESave;
	movf	((c:USBSuspend@UIESave)),c,w
	movlb	15	; () banked
	iorwf	((3894))&0ffh	;volatile
	line	684
	
l316:; BSR set to: 15

	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBSuspend
	__end_of_USBSuspend:
	signat	_USBSuspend,88
	global	_USBCBSuspend

;; *************** function _USBCBSuspend *****************
;; Defined at:
;;		line 772 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : F/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBSuspend
;; This function uses a non-reentrant model
;;
psect	text8,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	772
global __ptext8
__ptext8:
psect	text8
	file	"../src/main.c"
	line	772
	global	__size_of_USBCBSuspend
	__size_of_USBCBSuspend	equ	__end_of_USBCBSuspend-_USBCBSuspend
	
_USBCBSuspend:; BSR set to: 15

;incstack = 0
	opt	stack 27
	line	778
	
l2673:; BSR set to: 15

;main.c: 774: static unsigned char OSCCONSave;
;main.c: 778: LATCbits.LATC2 = 0;
	bcf	((c:3979)),c,2	;volatile
	line	784
;main.c: 784: OSCCONSave = OSCCON;
	movff	(c:4051),(c:USBCBSuspend@OSCCONSave)	;volatile
	line	785
# 785 "../src/main.c"
sleep ;# 
psect	text8
	line	787
;main.c: 787: while((PIR2bits.USBIF == 0) && (RCONbits.TO == 0))
	goto	l98
	
l99:
	line	789
# 789 "../src/main.c"
sleep ;# 
psect	text8
	line	790
	
l98:
	line	787
	btfsc	((c:4001)),c,4	;volatile
	goto	u1531
	goto	u1530
u1531:
	goto	l102
u1530:
	
l2675:
	btfss	((c:4048)),c,3	;volatile
	goto	u1541
	goto	u1540
u1541:
	goto	l99
u1540:
	
l102:
	line	793
;main.c: 790: }
;main.c: 793: OSCCON = OSCCONSave;
	movff	(c:USBCBSuspend@OSCCONSave),(c:4051)	;volatile
	line	802
	
l103:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCBSuspend
	__end_of_USBCBSuspend:
	signat	_USBCBSuspend,88
	global	_USBCtrlTrfSetupHandler

;; *************** function _USBCtrlTrfSetupHandler *****************
;; Defined at:
;;		line 812 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_USBCBCheckOtherReq
;;		_USBCheckStdRequest
;;		_USBCtrlEPServiceComplete
;; This function is called by:
;;		_USBDeviceTasks
;; This function uses a non-reentrant model
;;
psect	text9,class=CODE,space=0,reloc=2
	file	"../src/usb_device.c"
	line	812
global __ptext9
__ptext9:
psect	text9
	file	"../src/usb_device.c"
	line	812
	global	__size_of_USBCtrlTrfSetupHandler
	__size_of_USBCtrlTrfSetupHandler	equ	__end_of_USBCtrlTrfSetupHandler-_USBCtrlTrfSetupHandler
	
_USBCtrlTrfSetupHandler:
;incstack = 0
	opt	stack 24
	line	819
	
l2839:
;usb_device.c: 819: ep0Bi.Stat._byte = 0x00;
	movlb	13	; () banked
	clrf	((3336))&0ffh	;volatile
	line	820
;usb_device.c: 820: short_pkt_status = 0;
	clrf	((c:_short_pkt_status)),c
	line	825
;usb_device.c: 825: if(ep0BoEven.Stat.UOWN == 1)
	btfss	((3328))&0ffh,7	;volatile
	goto	u1691
	goto	u1690
u1691:
	goto	l331
u1690:
	line	827
	
l2841:; BSR set to: 13

;usb_device.c: 826: {
;usb_device.c: 827: ep0BoEven.Stat._byte = 0x00;
	clrf	((3328))&0ffh	;volatile
	line	828
;usb_device.c: 828: EP0OutOddNeedsArmingNext = 0;
	clrf	((c:_EP0OutOddNeedsArmingNext)),c
	line	829
	
l331:; BSR set to: 13

	line	830
;usb_device.c: 829: }
;usb_device.c: 830: if(ep0BoOdd.Stat.UOWN == 1)
	btfss	((3332))&0ffh,7	;volatile
	goto	u1701
	goto	u1700
u1701:
	goto	l2847
u1700:
	line	832
	
l2843:; BSR set to: 13

;usb_device.c: 831: {
;usb_device.c: 832: ep0BoOdd.Stat._byte = 0x00;
	clrf	((3332))&0ffh	;volatile
	line	833
	
l2845:; BSR set to: 13

;usb_device.c: 833: EP0OutOddNeedsArmingNext = 1;
	movlw	low(01h)
	movwf	((c:_EP0OutOddNeedsArmingNext)),c
	line	835
	
l2847:; BSR set to: 13

;usb_device.c: 834: }
;usb_device.c: 835: ctrl_trf_state = 0;
	clrf	((c:_ctrl_trf_state)),c
	line	836
	
l2849:; BSR set to: 13

;usb_device.c: 836: ctrl_trf_session_owner = 0;
	clrf	((c:_ctrl_trf_session_owner)),c
	line	837
	
l2851:; BSR set to: 13

;usb_device.c: 837: wCount.Val = 0;
	clrf	((c:_wCount)),c
	clrf	((c:_wCount+1)),c
	line	838
	
l2853:; BSR set to: 13

;usb_device.c: 838: UCONbits.PKTDIS = 0;
	bcf	((c:3941)),c,4	;volatile
	line	844
	
l2855:; BSR set to: 13

;usb_device.c: 844: USBCheckStdRequest();
	call	_USBCheckStdRequest	;wreg free
	line	845
	
l2857:
;usb_device.c: 845: USBCBCheckOtherReq();
	call	_USBCBCheckOtherReq	;wreg free
	line	848
	
l2859:
;usb_device.c: 848: USBCtrlEPServiceComplete();
	call	_USBCtrlEPServiceComplete	;wreg free
	line	850
	
l333:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCtrlTrfSetupHandler
	__end_of_USBCtrlTrfSetupHandler:
	signat	_USBCtrlTrfSetupHandler,88
	global	_USBCtrlEPServiceComplete

;; *************** function _USBCtrlEPServiceComplete *****************
;; Defined at:
;;		line 1169 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_LoadBDTandSetUOWN
;;		_USBCtrlTrfTxService
;; This function is called by:
;;		_USBCtrlTrfSetupHandler
;; This function uses a non-reentrant model
;;
psect	text10,class=CODE,space=0,reloc=2
	line	1169
global __ptext10
__ptext10:
psect	text10
	file	"../src/usb_device.c"
	line	1169
	global	__size_of_USBCtrlEPServiceComplete
	__size_of_USBCtrlEPServiceComplete	equ	__end_of_USBCtrlEPServiceComplete-_USBCtrlEPServiceComplete
	
_USBCtrlEPServiceComplete:
;incstack = 0
	opt	stack 26
	line	1173
	
l2735:
;usb_device.c: 1173: if(ctrl_trf_session_owner == 0)
	movf	((c:_ctrl_trf_session_owner)),c,w
	btfss	status,2
	goto	u1571
	goto	u1570
u1571:
	goto	l365
u1570:
	line	1178
	
l2737:
;usb_device.c: 1174: {
;usb_device.c: 1178: ep0Bi.Stat._byte = 0x04;
	movlw	low(04h)
	movlb	13	; () banked
	movwf	((3336))&0ffh	;volatile
	line	1179
	
l2739:; BSR set to: 13

;usb_device.c: 1179: ep0Bi.Stat._byte |= 0x80;
	bsf	(0+(7/8)+(3336))&0ffh,(7)&7	;volatile
	line	1180
	
l2741:; BSR set to: 13

;usb_device.c: 1180: TempBDT.Stat._byte = 0x04;
	movlw	low(04h)
	movwf	((c:_TempBDT)),c
	line	1181
	
l2743:; BSR set to: 13

;usb_device.c: 1181: if(EP0OutOddNeedsArmingNext == 1)
		decf	((c:_EP0OutOddNeedsArmingNext)),c,w
	btfss	status,2
	goto	u1581
	goto	u1580

u1581:
	goto	l2749
u1580:
	line	1183
	
l2745:; BSR set to: 13

;usb_device.c: 1182: {
;usb_device.c: 1183: LoadBDTandSetUOWN(1);
	movlw	(01h)&0ffh
	
	call	_LoadBDTandSetUOWN
	line	1184
	
l2747:
;usb_device.c: 1184: EP0OutOddNeedsArmingNext = 0;
	clrf	((c:_EP0OutOddNeedsArmingNext)),c
	line	1185
;usb_device.c: 1185: }
	goto	l376
	line	1188
	
l2749:; BSR set to: 13

;usb_device.c: 1186: else
;usb_device.c: 1187: {
;usb_device.c: 1188: LoadBDTandSetUOWN(0);
	movlw	(0)&0ffh
	
	call	_LoadBDTandSetUOWN
	line	1189
	
l2751:
;usb_device.c: 1189: EP0OutOddNeedsArmingNext = 1;
	movlw	low(01h)
	movwf	((c:_EP0OutOddNeedsArmingNext)),c
	goto	l376
	line	1192
	
l365:
	line	1194
;usb_device.c: 1192: else
;usb_device.c: 1193: {
;usb_device.c: 1194: if(SetupPkt.DataDir == 1)
	btfss	((c:_SetupPkt)),c,7
	goto	u1591
	goto	u1590
u1591:
	goto	l2773
u1590:
	line	1219
	
l2753:
;usb_device.c: 1195: {
;usb_device.c: 1219: ctrl_trf_state = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_state)),c
	line	1224
	
l2755:
;usb_device.c: 1224: if(SetupPkt.wLength < wCount.Val)
		movf	((c:_wCount)),c,w
	subwf	(0+((c:_SetupPkt)+06h)),c,w
	movf	((c:_wCount+1)),c,w
	subwfb	(1+((c:_SetupPkt)+06h)),c,w
	btfsc	status,0
	goto	u1601
	goto	u1600

u1601:
	goto	l2759
u1600:
	line	1225
	
l2757:
;usb_device.c: 1225: wCount.Val = SetupPkt.wLength;
	movff	0+((c:_SetupPkt)+06h),(c:_wCount)
	movff	1+((c:_SetupPkt)+06h),(c:_wCount+1)
	line	1229
	
l2759:
;usb_device.c: 1229: USBCtrlTrfTxService();
	call	_USBCtrlTrfTxService	;wreg free
	line	1233
	
l2761:
;usb_device.c: 1233: TempBDT.Stat._byte = 0x40 | 0x08;
	movlw	low(048h)
	movwf	((c:_TempBDT)),c
	line	1234
	
l2763:
;usb_device.c: 1234: LoadBDTandSetUOWN(1);
	movlw	(01h)&0ffh
	
	call	_LoadBDTandSetUOWN
	line	1235
	
l2765:
;usb_device.c: 1235: LoadBDTandSetUOWN(0);
	movlw	(0)&0ffh
	
	call	_LoadBDTandSetUOWN
	line	1240
	
l2767:
;usb_device.c: 1240: ep0Bi.ADR = (uint8_t*)&CtrlTrfData;
		movlw	low(3364)
	movlb	13	; () banked
	movwf	(0+(3336+02h))&0ffh	;volatile
	movlw	high(3364)
	movwf	(1+(3336+02h))&0ffh	;volatile

	line	1241
	
l2769:; BSR set to: 13

;usb_device.c: 1241: ep0Bi.Stat._byte = 0x40|0x08;
	movlw	low(048h)
	movwf	((3336))&0ffh	;volatile
	line	1242
	
l2771:; BSR set to: 13

;usb_device.c: 1242: ep0Bi.Stat._byte |= 0x80;
	bsf	(0+(7/8)+(3336))&0ffh,(7)&7	;volatile
	line	1243
;usb_device.c: 1243: }
	goto	l376
	line	1256
	
l2773:
;usb_device.c: 1244: else
;usb_device.c: 1245: {
;usb_device.c: 1256: ctrl_trf_state = 2;
	movlw	low(02h)
	movwf	((c:_ctrl_trf_state)),c
	line	1261
;usb_device.c: 1261: TempBDT.Stat._byte = 0x04;
	movlw	low(04h)
	movwf	((c:_TempBDT)),c
	line	1263
	
l2775:
;usb_device.c: 1263: if(SetupPkt.wLength == 0)
	movf	(0+((c:_SetupPkt)+06h)),c,w
iorwf	(1+((c:_SetupPkt)+06h)),c,w
	btfss	status,2
	goto	u1611
	goto	u1610

u1611:
	goto	l2779
u1610:
	line	1265
	
l2777:
;usb_device.c: 1264: {
;usb_device.c: 1265: TempBDT.Stat._byte = 0x40|0x08;
	movlw	low(048h)
	movwf	((c:_TempBDT)),c
	line	1268
	
l2779:
;usb_device.c: 1266: }
;usb_device.c: 1268: if(EP0OutOddNeedsArmingNext == 1)
		decf	((c:_EP0OutOddNeedsArmingNext)),c,w
	btfss	status,2
	goto	u1621
	goto	u1620

u1621:
	goto	l2785
u1620:
	line	1270
	
l2781:
;usb_device.c: 1269: {
;usb_device.c: 1270: LoadBDTandSetUOWN(1);
	movlw	(01h)&0ffh
	
	call	_LoadBDTandSetUOWN
	line	1271
	
l2783:
;usb_device.c: 1271: EP0OutOddNeedsArmingNext = 0;
	clrf	((c:_EP0OutOddNeedsArmingNext)),c
	line	1272
;usb_device.c: 1272: }
	goto	l2789
	line	1275
	
l2785:
;usb_device.c: 1273: else
;usb_device.c: 1274: {
;usb_device.c: 1275: LoadBDTandSetUOWN(0);
	movlw	(0)&0ffh
	
	call	_LoadBDTandSetUOWN
	line	1276
	
l2787:
;usb_device.c: 1276: EP0OutOddNeedsArmingNext = 1;
	movlw	low(01h)
	movwf	((c:_EP0OutOddNeedsArmingNext)),c
	line	1281
	
l2789:
;usb_device.c: 1277: }
;usb_device.c: 1281: if(SetupPkt.wLength == 0)
	movf	(0+((c:_SetupPkt)+06h)),c,w
iorwf	(1+((c:_SetupPkt)+06h)),c,w
	btfss	status,2
	goto	u1631
	goto	u1630

u1631:
	goto	l376
u1630:
	line	1284
	
l2791:
;usb_device.c: 1282: {
;usb_device.c: 1284: ep0Bi.Cnt = 0;
	movlb	13	; () banked
	clrf	(0+(3336+01h))&0ffh	;volatile
	line	1285
	
l2793:; BSR set to: 13

;usb_device.c: 1285: ep0Bi.Stat._byte = 0x40|0x08;
	movlw	low(048h)
	movwf	((3336))&0ffh	;volatile
	line	1286
	
l2795:; BSR set to: 13

;usb_device.c: 1286: ep0Bi.Stat._byte |= 0x80;
	bsf	(0+(7/8)+(3336))&0ffh,(7)&7	;volatile
	line	1296
	
l376:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCtrlEPServiceComplete
	__end_of_USBCtrlEPServiceComplete:
	signat	_USBCtrlEPServiceComplete,88
	global	_USBCheckStdRequest

;; *************** function _USBCheckStdRequest *****************
;; Defined at:
;;		line 1316 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : F/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_USBStdFeatureReqHandler
;;		_USBStdGetDscHandler
;;		_USBStdGetStatusHandler
;;		_USBStdSetCfgHandler
;; This function is called by:
;;		_USBCtrlTrfSetupHandler
;; This function uses a non-reentrant model
;;
psect	text11,class=CODE,space=0,reloc=2
	line	1316
global __ptext11
__ptext11:
psect	text11
	file	"../src/usb_device.c"
	line	1316
	global	__size_of_USBCheckStdRequest
	__size_of_USBCheckStdRequest	equ	__end_of_USBCheckStdRequest-_USBCheckStdRequest
	
_USBCheckStdRequest:
;incstack = 0
	opt	stack 24
	line	1318
	
l2697:; BSR set to: 13

;usb_device.c: 1318: if(SetupPkt.RequestType != 0x00) return;
	swapf	((c:_SetupPkt)),c,w
	rrcf	wreg,f
	andlw	(1<<2)-1
	iorlw	0
	btfsc	status,2
	goto	u1561
	goto	u1560
u1561:
	goto	l2733
u1560:
	goto	l380
	
l2699:; BSR set to: 13

	goto	l380
	line	1323
	
l2701:; BSR set to: 13

;usb_device.c: 1323: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1324
;usb_device.c: 1324: usb_device_state = 4;
	movlw	low(04h)
	movwf	((c:_usb_device_state)),c
	line	1326
;usb_device.c: 1326: break;
	goto	l380
	line	1328
	
l2703:; BSR set to: 13

;usb_device.c: 1328: USBStdGetDscHandler();
	call	_USBStdGetDscHandler	;wreg free
	line	1329
;usb_device.c: 1329: break;
	goto	l380
	line	1331
	
l2705:; BSR set to: 13

;usb_device.c: 1331: USBStdSetCfgHandler();
	call	_USBStdSetCfgHandler	;wreg free
	line	1332
;usb_device.c: 1332: break;
	goto	l380
	line	1334
	
l2707:; BSR set to: 13

;usb_device.c: 1334: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1335
	
l2709:; BSR set to: 13

;usb_device.c: 1335: pSrc.bRam = (uint8_t*)&usb_active_cfg;
		movlw	low(_usb_active_cfg)
	movwf	((c:_pSrc)),c
	clrf	((c:_pSrc+1)),c

	line	1336
	
l2711:; BSR set to: 13

;usb_device.c: 1336: usb_stat.ctrl_trf_mem = 0;
	bcf	((c:_usb_stat)),c,1
	line	1338
	
l2713:; BSR set to: 13

;usb_device.c: 1338: wCount.v[0] = 1;
	movlw	low(01h)
	movwf	((c:_wCount)),c
	line	1339
;usb_device.c: 1339: break;
	goto	l380
	line	1341
	
l2715:; BSR set to: 13

;usb_device.c: 1341: USBStdGetStatusHandler();
	call	_USBStdGetStatusHandler	;wreg free
	line	1342
;usb_device.c: 1342: break;
	goto	l380
	line	1345
	
l2717:; BSR set to: 13

;usb_device.c: 1344: case 3:
;usb_device.c: 1345: USBStdFeatureReqHandler();
	call	_USBStdFeatureReqHandler	;wreg free
	line	1346
;usb_device.c: 1346: break;
	goto	l380
	line	1348
	
l2719:; BSR set to: 13

;usb_device.c: 1348: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1349
	
l2721:; BSR set to: 13

;usb_device.c: 1349: pSrc.bRam = (uint8_t*)&usb_alt_intf+SetupPkt.bIntfID;
	movf	(0+((c:_SetupPkt)+04h)),c,w
	addlw	low(_usb_alt_intf)
	movwf	(??_USBCheckStdRequest+0+0)&0ffh,c
		movff	(??_USBCheckStdRequest+0+0),(c:_pSrc)
	clrf	((c:_pSrc+1)),c

	goto	l2711
	line	1354
	
l2727:; BSR set to: 13

;usb_device.c: 1354: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1355
	
l2729:; BSR set to: 13

;usb_device.c: 1355: usb_alt_intf[SetupPkt.bIntfID] = SetupPkt.bAltID;
	movf	(0+((c:_SetupPkt)+04h)),c,w
	addlw	low(_usb_alt_intf)
	movwf	fsr2l
	clrf	fsr2h
	movff	0+((c:_SetupPkt)+02h),indf2

	line	1356
;usb_device.c: 1356: break;
	goto	l380
	line	1320
	
l2733:; BSR set to: 13

	movf	(0+((c:_SetupPkt)+01h)),c,w
	; Switch size 1, requested type "space"
; Number of cases is 11, Range of values is 0 to 12
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           34    18 (average)
;	Chosen strategy is simple_byte

	xorlw	0^0	; case 0
	skipnz
	goto	l2715
	xorlw	1^0	; case 1
	skipnz
	goto	l2717
	xorlw	3^1	; case 3
	skipnz
	goto	l2717
	xorlw	5^3	; case 5
	skipnz
	goto	l2701
	xorlw	6^5	; case 6
	skipnz
	goto	l2703
	xorlw	7^6	; case 7
	skipnz
	goto	l2699
	xorlw	8^7	; case 8
	skipnz
	goto	l2707
	xorlw	9^8	; case 9
	skipnz
	goto	l2705
	xorlw	10^9	; case 10
	skipnz
	goto	l2719
	xorlw	11^10	; case 11
	skipnz
	goto	l2727
	xorlw	12^11	; case 12
	skipnz
	goto	l380
	goto	l380

	line	1363
	
l380:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCheckStdRequest
	__end_of_USBCheckStdRequest:
	signat	_USBCheckStdRequest,88
	global	_USBStdSetCfgHandler

;; *************** function _USBStdSetCfgHandler *****************
;; Defined at:
;;		line 1431 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : F/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_USBCBInitEP
;; This function is called by:
;;		_USBCheckStdRequest
;; This function uses a non-reentrant model
;;
psect	text12,class=CODE,space=0,reloc=2
	line	1431
global __ptext12
__ptext12:
psect	text12
	file	"../src/usb_device.c"
	line	1431
	global	__size_of_USBStdSetCfgHandler
	__size_of_USBStdSetCfgHandler	equ	__end_of_USBStdSetCfgHandler-_USBStdSetCfgHandler
	
_USBStdSetCfgHandler:
;incstack = 0
	opt	stack 24
	line	1435
	
l2573:; BSR set to: 13

;usb_device.c: 1433: static unsigned char i;
;usb_device.c: 1435: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1437
	
l2575:; BSR set to: 13

;usb_device.c: 1437: UEP1=0x00;UEP2=0x00;UEP3=0x00; UEP4=0x00;UEP5=0x00;UEP6=0x00;UEP7=0x00;;
	movlb	15	; () banked
	clrf	((3879))&0ffh	;volatile
	
l2577:; BSR set to: 15

	clrf	((3880))&0ffh	;volatile
	
l2579:; BSR set to: 15

	clrf	((3881))&0ffh	;volatile
	
l2581:; BSR set to: 15

	clrf	((3882))&0ffh	;volatile
	
l2583:; BSR set to: 15

	clrf	((3883))&0ffh	;volatile
	
l2585:; BSR set to: 15

	clrf	((3884))&0ffh	;volatile
	
l2587:; BSR set to: 15

	clrf	((3885))&0ffh	;volatile
	line	1439
	
l2589:; BSR set to: 15

;usb_device.c: 1439: for(i = 0; i < 1; i++)
	clrf	((c:USBStdSetCfgHandler@i)),c
	line	1441
	
l2593:
;usb_device.c: 1440: {
;usb_device.c: 1441: usb_alt_intf[i] = 0;
	movf	((c:USBStdSetCfgHandler@i)),c,w
	addlw	low(_usb_alt_intf)
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(0)
	movwf	indf2
	line	1439
	
l2595:
	incf	((c:USBStdSetCfgHandler@i)),c
	
l2597:
	movf	((c:USBStdSetCfgHandler@i)),c,w
	btfsc	status,2
	goto	u1381
	goto	u1380
u1381:
	goto	l2593
u1380:
	
l410:
	line	1445
;usb_device.c: 1442: }
;usb_device.c: 1445: usb_active_cfg = SetupPkt.bCfgValue;
	movff	0+((c:_SetupPkt)+02h),(c:_usb_active_cfg)
	line	1452
	
l2599:
;usb_device.c: 1452: USBCBInitEP(usb_active_cfg);
	movf	((c:_usb_active_cfg)),c,w
	
	call	_USBCBInitEP
	line	1454
	
l2601:
;usb_device.c: 1454: if(SetupPkt.bCfgValue == 0)
	movf	(0+((c:_SetupPkt)+02h)),c,w
	btfss	status,2
	goto	u1391
	goto	u1390
u1391:
	goto	l2605
u1390:
	line	1456
	
l2603:
;usb_device.c: 1455: {
;usb_device.c: 1456: usb_device_state = 5;
	movlw	low(05h)
	movwf	((c:_usb_device_state)),c
	line	1457
;usb_device.c: 1457: }
	goto	l413
	line	1460
	
l2605:
;usb_device.c: 1458: else
;usb_device.c: 1459: {
;usb_device.c: 1460: usb_device_state = 6;
	movlw	low(06h)
	movwf	((c:_usb_device_state)),c
	line	1462
	
l413:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBStdSetCfgHandler
	__end_of_USBStdSetCfgHandler:
	signat	_USBStdSetCfgHandler,88
	global	_USBStdGetStatusHandler

;; *************** function _USBStdGetStatusHandler *****************
;; Defined at:
;;		line 1480 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : F/D
;;		On exit  : F/D
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBCheckStdRequest
;; This function uses a non-reentrant model
;;
psect	text13,class=CODE,space=0,reloc=2
	line	1480
global __ptext13
__ptext13:
psect	text13
	file	"../src/usb_device.c"
	line	1480
	global	__size_of_USBStdGetStatusHandler
	__size_of_USBStdGetStatusHandler	equ	__end_of_USBStdGetStatusHandler-_USBStdGetStatusHandler
	
_USBStdGetStatusHandler:
;incstack = 0
	opt	stack 26
	line	1482
	
l2607:; BSR set to: 13

;usb_device.c: 1482: CtrlTrfData._byte0 = 0;
	clrf	((3364))&0ffh	;volatile
	line	1483
;usb_device.c: 1483: CtrlTrfData._byte1 = 0;
	clrf	(0+(3364+01h))&0ffh	;volatile
	line	1485
;usb_device.c: 1485: switch(SetupPkt.Recipient)
	goto	l2629
	line	1488
	
l2609:; BSR set to: 13

;usb_device.c: 1488: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1496
;usb_device.c: 1494: if(0 == 1)
	
l2613:; BSR set to: 13

;usb_device.c: 1496: if(usb_stat.RemoteWakeup == 1)
	btfss	((c:_usb_stat)),c,0
	goto	u1401
	goto	u1400
u1401:
	goto	l2631
u1400:
	line	1497
	
l2615:; BSR set to: 13

;usb_device.c: 1497: CtrlTrfData._byte0|=0b00000010;
	bsf	(0+(1/8)+(3364))&0ffh,(1)&7	;volatile
	goto	l2631
	line	1500
	
l2617:; BSR set to: 13

;usb_device.c: 1500: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1501
;usb_device.c: 1501: break;
	goto	l2631
	line	1503
	
l2619:; BSR set to: 13

;usb_device.c: 1503: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1507
	
l2621:; BSR set to: 13

;usb_device.c: 1507: pDst.bRam = (uint8_t*)&ep0BoEven+(SetupPkt.EPNum*8)+(SetupPkt.EPDir*4)+4;
	movf	(0+((c:_SetupPkt)+04h)),c,w
	andlw	(1<<4)-1
	mullw	08h
	movlw	low((3328))
	movwf	(??_USBStdGetStatusHandler+0+0)&0ffh,c
	movlw	high((3328))
	movwf	1+(??_USBStdGetStatusHandler+0+0)&0ffh,c
	movlw	04h
	addwf	(??_USBStdGetStatusHandler+0+0),c
	movlw	0
	addwfc	(??_USBStdGetStatusHandler+0+1),c
	movf	(prodl),c,w
	addwf	(??_USBStdGetStatusHandler+0+0),c
	movf	(prodh),c,w
	addwfc	(??_USBStdGetStatusHandler+0+1),c
	btfsc	(0+((c:_SetupPkt)+04h)),c,7
	goto	u1411
	goto	u1410
u1411:
	movlw	1
	goto	u1416
u1410:
	movlw	0
u1416:
	mullw	04h
	movf	(prodl),c,w
	addwf	(??_USBStdGetStatusHandler+0+0),c,w
	movwf	((c:_pDst)),c
	movf	(prodh),c,w
	addwfc	(??_USBStdGetStatusHandler+0+1),c,w
	movwf	1+((c:_pDst)),c
	line	1508
	
l2623:; BSR set to: 13

;usb_device.c: 1508: if(*pDst.bRam & 0x04)
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	btfss	indf2,(2)&7
	goto	u1421
	goto	u1420
u1421:
	goto	l2631
u1420:
	line	1509
	
l2625:; BSR set to: 13

;usb_device.c: 1509: CtrlTrfData._byte0=0x01;
	movlw	low(01h)
	movwf	((3364))&0ffh	;volatile
	goto	l2631
	line	1485
	
l2629:; BSR set to: 13

	movf	((c:_SetupPkt)),c,w
	andlw	(1<<5)-1
	; Switch size 1, requested type "space"
; Number of cases is 3, Range of values is 0 to 2
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           10     6 (average)
;	Chosen strategy is simple_byte

	xorlw	0^0	; case 0
	skipnz
	goto	l2609
	xorlw	1^0	; case 1
	skipnz
	goto	l2617
	xorlw	2^1	; case 2
	skipnz
	goto	l2619
	goto	l2631

	line	1513
	
l2631:; BSR set to: 13

;usb_device.c: 1513: if(ctrl_trf_session_owner == 1)
		decf	((c:_ctrl_trf_session_owner)),c,w
	btfss	status,2
	goto	u1431
	goto	u1430

u1431:
	goto	l425
u1430:
	line	1515
	
l2633:; BSR set to: 13

;usb_device.c: 1514: {
;usb_device.c: 1515: pSrc.bRam = (uint8_t*)&CtrlTrfData;
		movlw	low(3364)
	movwf	((c:_pSrc)),c
	movlw	high(3364)
	movwf	((c:_pSrc+1)),c

	line	1516
	
l2635:; BSR set to: 13

;usb_device.c: 1516: usb_stat.ctrl_trf_mem = 0;
	bcf	((c:_usb_stat)),c,1
	line	1517
	
l2637:; BSR set to: 13

;usb_device.c: 1517: wCount.v[0] = 2;
	movlw	low(02h)
	movwf	((c:_wCount)),c
	line	1519
	
l425:; BSR set to: 13

	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBStdGetStatusHandler
	__end_of_USBStdGetStatusHandler:
	signat	_USBStdGetStatusHandler,88
	global	_USBStdGetDscHandler

;; *************** function _USBStdGetDscHandler *****************
;; Defined at:
;;		line 1383 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, tblptrl, tblptrh, tblptru
;; Tracked objects:
;;		On entry : F/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBCheckStdRequest
;; This function uses a non-reentrant model
;;
psect	text14,class=CODE,space=0,reloc=2
	line	1383
global __ptext14
__ptext14:
psect	text14
	file	"../src/usb_device.c"
	line	1383
	global	__size_of_USBStdGetDscHandler
	__size_of_USBStdGetDscHandler	equ	__end_of_USBStdGetDscHandler-_USBStdGetDscHandler
	
_USBStdGetDscHandler:; BSR set to: 13

;incstack = 0
	opt	stack 26
	line	1385
	
l2545:; BSR set to: 13

;usb_device.c: 1385: if(SetupPkt.bmRequestType == 0x80)
		movlw	128
	xorwf	((c:_SetupPkt)),c,w
	btfss	status,2
	goto	u1351
	goto	u1350

u1351:
	goto	l404
u1350:
	goto	l2571
	line	1390
	
l2549:; BSR set to: 13

;usb_device.c: 1390: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1391
	
l2551:; BSR set to: 13

;usb_device.c: 1391: pSrc.bRom = (const uint8_t*)&device_dsc;
		movlw	low(_device_dsc)
	movwf	((c:_pSrc)),c
	movf	((c:_pSrc)),c,w
	btfss	status,2
	movlw	high(__smallconst)
	movwf	((c:_pSrc+1)),c

	line	1392
	
l2553:; BSR set to: 13

;usb_device.c: 1392: wCount.v[0] = sizeof(device_dsc);
	movlw	low(012h)
	movwf	((c:_wCount)),c
	line	1393
;usb_device.c: 1393: break;
	goto	l400
	line	1396
	
l2555:; BSR set to: 13

;usb_device.c: 1396: if(SetupPkt.bDscIndex < 1)
	movf	(0+((c:_SetupPkt)+02h)),c,w
	btfss	status,2
	goto	u1361
	goto	u1360
u1361:
	goto	l400
u1360:
	line	1398
	
l2557:; BSR set to: 13

;usb_device.c: 1397: {
;usb_device.c: 1398: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1399
	
l2559:; BSR set to: 13

;usb_device.c: 1399: pSrc.bRom = (const BYTE*)&CFG01;
		movlw	low(_CFG01)
	movwf	((c:_pSrc)),c
	movf	((c:_pSrc)),c,w
	btfss	status,2
	movlw	high(__smallconst)
	movwf	((c:_pSrc+1)),c

	line	1400
	
l2561:; BSR set to: 13

;usb_device.c: 1400: wCount.Val = sizeof(CFG01);
	movlw	high(029h)
	movwf	((c:_wCount+1)),c
	movlw	low(029h)
	movwf	((c:_wCount)),c
	goto	l400
	line	1404
	
l2563:; BSR set to: 13

;usb_device.c: 1404: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1405
	
l2565:; BSR set to: 13

;usb_device.c: 1405: pSrc.bRom = *(USB_SD_Ptr+SetupPkt.bDscIndex);
	movf	(0+((c:_SetupPkt)+02h)),c,w
	addlw	low(_USB_SD_Ptr)
	movwf	(??_USBStdGetDscHandler+0+0)&0ffh,c
	movff	(??_USBStdGetDscHandler+0+0),tblptrl
	if	1	;There is more than 1 active tblptr byte
	global __smallconst
movlw	high(__smallconst)
	movwf	tblptrh
	endif
	if	0	;tblptru may be non-zero
	clrf	tblptru
	endif
	if	1	;Program memory is > 0xFFFF, there are 3 active tblptr bytes
	movlw	low highword(__smallconst)
	movwf	tblptru
	endif
	tblrd*+
	
	movff	tablat,(c:_pSrc)
	global __smallconst
movlw	high(__smallconst)
	movwf	((c:_pSrc+1)),c

	line	1406
	
l2567:; BSR set to: 13

;usb_device.c: 1406: wCount.Val = *pSrc.bRom;
	movff	(c:_pSrc),tblptrl
	movff	(c:_pSrc+1),tblptrh
	movlw	low highword(__smallconst)
	movwf	tblptru
	
	movlw	high __ramtop-1
	cpfsgt	tblptrh
	bra	u1377
	tblrd	*
	
	movf	tablat,w
	bra	u1370
u1377:
	movff	tblptrl,fsr1l
	movff	tblptrh,fsr1h
	movf	indf1,w
u1370:
	movwf	((c:_wCount)),c
	clrf	((c:_wCount+1)),c
	line	1407
;usb_device.c: 1407: break;
	goto	l400
	line	1387
	
l2571:; BSR set to: 13

	movf	(0+((c:_SetupPkt)+03h)),c,w
	; Switch size 1, requested type "space"
; Number of cases is 3, Range of values is 1 to 3
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           10     6 (average)
;	Chosen strategy is simple_byte

	xorlw	1^0	; case 1
	skipnz
	goto	l2549
	xorlw	2^1	; case 2
	skipnz
	goto	l2555
	xorlw	3^2	; case 3
	skipnz
	goto	l2563
	goto	l400

	line	1408
	
l400:
	line	1410
;usb_device.c: 1410: usb_stat.ctrl_trf_mem = 1;
	bsf	((c:_usb_stat)),c,1
	line	1412
	
l404:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBStdGetDscHandler
	__end_of_USBStdGetDscHandler:
	signat	_USBStdGetDscHandler,88
	global	_USBStdFeatureReqHandler

;; *************** function _USBStdFeatureReqHandler *****************
;; Defined at:
;;		line 1538 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : F/D
;;		On exit  : F/D
;;		Unchanged: E/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBCheckStdRequest
;; This function uses a non-reentrant model
;;
psect	text15,class=CODE,space=0,reloc=2
	line	1538
global __ptext15
__ptext15:
psect	text15
	file	"../src/usb_device.c"
	line	1538
	global	__size_of_USBStdFeatureReqHandler
	__size_of_USBStdFeatureReqHandler	equ	__end_of_USBStdFeatureReqHandler-_USBStdFeatureReqHandler
	
_USBStdFeatureReqHandler:
;incstack = 0
	opt	stack 26
	line	1541
	
l2639:; BSR set to: 13

;usb_device.c: 1541: if((SetupPkt.bFeature == 0x01)&&(SetupPkt.Recipient == 0))
		decf	(0+((c:_SetupPkt)+02h)),c,w
	btfss	status,2
	goto	u1441
	goto	u1440

u1441:
	goto	l2649
u1440:
	
l2641:; BSR set to: 13

	movf	((c:_SetupPkt)),c,w
	andlw	(1<<5)-1
	iorlw	0
	btfss	status,2
	goto	u1451
	goto	u1450
u1451:
	goto	l2649
u1450:
	line	1543
	
l2643:; BSR set to: 13

;usb_device.c: 1542: {
;usb_device.c: 1543: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1544
	
l2645:; BSR set to: 13

;usb_device.c: 1544: if(SetupPkt.bRequest == 3)
		movlw	3
	xorwf	(0+((c:_SetupPkt)+01h)),c,w
	btfss	status,2
	goto	u1461
	goto	u1460

u1461:
	goto	l429
u1460:
	line	1545
	
l2647:; BSR set to: 13

;usb_device.c: 1545: usb_stat.RemoteWakeup = 1;
	bsf	((c:_usb_stat)),c,0
	goto	l2649
	line	1546
	
l429:; BSR set to: 13

	line	1547
;usb_device.c: 1546: else
;usb_device.c: 1547: usb_stat.RemoteWakeup = 0;
	bcf	((c:_usb_stat)),c,0
	line	1551
	
l2649:; BSR set to: 13

;usb_device.c: 1548: }
;usb_device.c: 1551: if((SetupPkt.bFeature == 0x00)&&(SetupPkt.Recipient == 2)&&(SetupPkt.EPNum != 0))
	movf	(0+((c:_SetupPkt)+02h)),c,w
	btfss	status,2
	goto	u1471
	goto	u1470
u1471:
	goto	l436
u1470:
	
l2651:; BSR set to: 13

	movf	((c:_SetupPkt)),c,w
	andlw	(1<<5)-1
	xorlw	02h
	btfss	status,2
	goto	u1481
	goto	u1480
u1481:
	goto	l436
u1480:
	
l2653:; BSR set to: 13

	movf	(0+((c:_SetupPkt)+04h)),c,w
	andlw	(1<<4)-1
	iorlw	0
	btfsc	status,2
	goto	u1491
	goto	u1490
u1491:
	goto	l436
u1490:
	line	1553
	
l2655:; BSR set to: 13

;usb_device.c: 1552: {
;usb_device.c: 1553: ctrl_trf_session_owner = 1;
	movlw	low(01h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	1555
	
l2657:; BSR set to: 13

;usb_device.c: 1555: pDst.bRam = (uint8_t*)&ep0BoEven+(SetupPkt.EPNum*8)+(SetupPkt.EPDir*4)+4;
	movf	(0+((c:_SetupPkt)+04h)),c,w
	andlw	(1<<4)-1
	mullw	08h
	movlw	low((3328))
	movwf	(??_USBStdFeatureReqHandler+0+0)&0ffh,c
	movlw	high((3328))
	movwf	1+(??_USBStdFeatureReqHandler+0+0)&0ffh,c
	movlw	04h
	addwf	(??_USBStdFeatureReqHandler+0+0),c
	movlw	0
	addwfc	(??_USBStdFeatureReqHandler+0+1),c
	movf	(prodl),c,w
	addwf	(??_USBStdFeatureReqHandler+0+0),c
	movf	(prodh),c,w
	addwfc	(??_USBStdFeatureReqHandler+0+1),c
	btfsc	(0+((c:_SetupPkt)+04h)),c,7
	goto	u1501
	goto	u1500
u1501:
	movlw	1
	goto	u1506
u1500:
	movlw	0
u1506:
	mullw	04h
	movf	(prodl),c,w
	addwf	(??_USBStdFeatureReqHandler+0+0),c,w
	movwf	((c:_pDst)),c
	movf	(prodh),c,w
	addwfc	(??_USBStdFeatureReqHandler+0+1),c,w
	movwf	1+((c:_pDst)),c
	line	1557
	
l2659:; BSR set to: 13

;usb_device.c: 1557: if(SetupPkt.bRequest == 3)
		movlw	3
	xorwf	(0+((c:_SetupPkt)+01h)),c,w
	btfss	status,2
	goto	u1511
	goto	u1510

u1511:
	goto	l432
u1510:
	line	1559
	
l2661:; BSR set to: 13

;usb_device.c: 1558: {
;usb_device.c: 1559: *pDst.bRam = 0x04;
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	movlw	low(04h)
	movwf	indf2
	line	1560
	
l2663:; BSR set to: 13

;usb_device.c: 1560: *pDst.bRam |= 0x80;
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	movlw	0+(7/8)
	bsf	plusw2,(7)&7
	line	1561
;usb_device.c: 1561: }
	goto	l436
	line	1562
	
l432:; BSR set to: 13

	line	1564
;usb_device.c: 1562: else
;usb_device.c: 1563: {
;usb_device.c: 1564: if(SetupPkt.EPDir == 1)
	btfss	(0+((c:_SetupPkt)+04h)),c,7
	goto	u1521
	goto	u1520
u1521:
	goto	l2667
u1520:
	line	1565
	
l2665:; BSR set to: 13

;usb_device.c: 1565: *pDst.bRam = 0x00|0x40;
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	movlw	low(040h)
	movwf	indf2
	goto	l436
	line	1568
	
l2667:; BSR set to: 13

;usb_device.c: 1566: else
;usb_device.c: 1567: {
;usb_device.c: 1568: *pDst.bRam = 0x00|0x08;
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	movlw	low(08h)
	movwf	indf2
	line	1569
	
l2669:; BSR set to: 13

;usb_device.c: 1569: *pDst.bRam |= 0x80;
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	movlw	0+(7/8)
	bsf	plusw2,(7)&7
	line	1573
	
l436:; BSR set to: 13

	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBStdFeatureReqHandler
	__end_of_USBStdFeatureReqHandler:
	signat	_USBStdFeatureReqHandler,88
	global	_USBCBCheckOtherReq

;; *************** function _USBCBCheckOtherReq *****************
;; Defined at:
;;		line 881 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_USBCheckHIDRequest
;; This function is called by:
;;		_USBCtrlTrfSetupHandler
;; This function uses a non-reentrant model
;;
psect	text16,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	881
global __ptext16
__ptext16:
psect	text16
	file	"../src/main.c"
	line	881
	global	__size_of_USBCBCheckOtherReq
	__size_of_USBCBCheckOtherReq	equ	__end_of_USBCBCheckOtherReq-_USBCBCheckOtherReq
	
_USBCBCheckOtherReq:; BSR set to: 13

;incstack = 0
	opt	stack 25
	line	883
	
l2677:
;main.c: 883: USBCheckHIDRequest();
	call	_USBCheckHIDRequest	;wreg free
	line	884
	
l110:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCBCheckOtherReq
	__end_of_USBCBCheckOtherReq:
	signat	_USBCBCheckOtherReq,88
	global	_USBCheckHIDRequest

;; *************** function _USBCheckHIDRequest *****************
;; Defined at:
;;		line 73 in file "../src/usb_device_hid.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_HIDGetReportHandler
;;		_HIDSetReportHandler
;; This function is called by:
;;		_USBCBCheckOtherReq
;; This function uses a non-reentrant model
;;
psect	text17,class=CODE,space=0,reloc=2
	file	"../src/usb_device_hid.c"
	line	73
global __ptext17
__ptext17:
psect	text17
	file	"../src/usb_device_hid.c"
	line	73
	global	__size_of_USBCheckHIDRequest
	__size_of_USBCheckHIDRequest	equ	__end_of_USBCheckHIDRequest-_USBCheckHIDRequest
	
_USBCheckHIDRequest:
;incstack = 0
	opt	stack 25
	line	75
	
l2389:
;usb_device_hid.c: 75: if(SetupPkt.Recipient != 1) return;
	movf	((c:_SetupPkt)),c,w
	andlw	(1<<5)-1
	decf	wreg
	btfsc	status,2
	goto	u1201
	goto	u1200
u1201:
	goto	l2393
u1200:
	goto	l495
	line	76
	
l2393:
;usb_device_hid.c: 76: if(SetupPkt.bIntfID != 0x00) return;
	movf	(0+((c:_SetupPkt)+04h)),c,w
	btfsc	status,2
	goto	u1211
	goto	u1210
u1211:
	goto	l2397
u1210:
	goto	l495
	line	83
	
l2397:
;usb_device_hid.c: 83: if(SetupPkt.bRequest == 6)
		movlw	6
	xorwf	(0+((c:_SetupPkt)+01h)),c,w
	btfss	status,2
	goto	u1221
	goto	u1220

u1221:
	goto	l2419
u1220:
	goto	l2417
	line	88
	
l2401:
;usb_device_hid.c: 88: ctrl_trf_session_owner = 2;
	movlw	low(02h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	89
	
l2403:
;usb_device_hid.c: 89: pSrc.bRom = &CFG01[18];
		movlw	low(_CFG01+012h)
	movwf	((c:_pSrc)),c
	movf	((c:_pSrc)),c,w
	btfss	status,2
	movlw	high(__smallconst)
	movwf	((c:_pSrc+1)),c

	line	90
	
l2405:
;usb_device_hid.c: 90: wCount.Val = sizeof(USB_HID_DSC);
	movlw	high(09h)
	movwf	((c:_wCount+1)),c
	movlw	low(09h)
	movwf	((c:_wCount)),c
	line	91
;usb_device_hid.c: 91: break;
	goto	l500
	line	93
	
l2407:
;usb_device_hid.c: 93: ctrl_trf_session_owner = 2;
	movlw	low(02h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	94
	
l2409:
;usb_device_hid.c: 94: { if(usb_active_cfg == 1) pSrc.bRom = (const uint8_t*)&hid_rpt01; };
		decf	((c:_usb_active_cfg)),c,w
	btfss	status,2
	goto	u1231
	goto	u1230

u1231:
	goto	l502
u1230:
	
l2411:
		movlw	low(_hid_rpt01)
	movwf	((c:_pSrc)),c
	movf	((c:_pSrc)),c,w
	btfss	status,2
	movlw	high(__smallconst)
	movwf	((c:_pSrc+1)),c

	
l502:
	line	95
;usb_device_hid.c: 95: { if(usb_active_cfg == 1) wCount.Val = sizeof(hid_rpt01); };
		decf	((c:_usb_active_cfg)),c,w
	btfss	status,2
	goto	u1241
	goto	u1240

u1241:
	goto	l500
u1240:
	
l2413:
	movlw	high(01Dh)
	movwf	((c:_wCount+1)),c
	movlw	low(01Dh)
	movwf	((c:_wCount)),c
	goto	l500
	line	85
	
l2417:
	movf	(0+((c:_SetupPkt)+03h)),c,w
	; Switch size 1, requested type "space"
; Number of cases is 3, Range of values is 33 to 35
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           10     6 (average)
;	Chosen strategy is simple_byte

	xorlw	33^0	; case 33
	skipnz
	goto	l2401
	xorlw	34^33	; case 34
	skipnz
	goto	l2407
	xorlw	35^34	; case 35
	skipnz
	goto	l500
	goto	l500

	line	100
	
l500:
	line	101
;usb_device_hid.c: 101: usb_stat.ctrl_trf_mem = 1;
	bsf	((c:_usb_stat)),c,1
	line	104
	
l2419:
;usb_device_hid.c: 102: }
;usb_device_hid.c: 104: if(SetupPkt.RequestType != 0x01) return;
	swapf	((c:_SetupPkt)),c,w
	rrcf	wreg,f
	andlw	(1<<2)-1
	decf	wreg
	btfsc	status,2
	goto	u1251
	goto	u1250
u1251:
	goto	l2453
u1250:
	goto	l495
	line	108
	
l2423:
;usb_device_hid.c: 108: HIDGetReportHandler();
	call	_HIDGetReportHandler	;wreg free
	line	109
;usb_device_hid.c: 109: break;
	goto	l495
	line	111
	
l2425:
;usb_device_hid.c: 111: HIDSetReportHandler();
	call	_HIDSetReportHandler	;wreg free
	line	112
;usb_device_hid.c: 112: break;
	goto	l495
	line	114
	
l2427:
;usb_device_hid.c: 114: ctrl_trf_session_owner = 2;
	movlw	low(02h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	115
	
l2429:
;usb_device_hid.c: 115: pSrc.bRam = (uint8_t*)&idle_rate;
		movlw	low(_idle_rate)
	movwf	((c:_pSrc)),c
	clrf	((c:_pSrc+1)),c

	line	116
	
l2431:
;usb_device_hid.c: 116: usb_stat.ctrl_trf_mem = 0;
	bcf	((c:_usb_stat)),c,1
	line	117
	
l2433:
;usb_device_hid.c: 117: wCount.v[0] = 1;
	movlw	low(01h)
	movwf	((c:_wCount)),c
	line	118
;usb_device_hid.c: 118: break;
	goto	l495
	line	120
	
l2435:
;usb_device_hid.c: 120: ctrl_trf_session_owner = 2;
	movlw	low(02h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	122
	
l2437:
;usb_device_hid.c: 122: idle_rate = SetupPkt.W_Value.v[1];
	movff	0+((c:_SetupPkt)+03h),(c:_idle_rate)
	line	123
;usb_device_hid.c: 123: break;
	goto	l495
	line	125
	
l2439:
;usb_device_hid.c: 125: ctrl_trf_session_owner = 2;
	movlw	low(02h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	126
	
l2441:
;usb_device_hid.c: 126: pSrc.bRam = (uint8_t*)&active_protocol;
		movlw	low(_active_protocol)
	movwf	((c:_pSrc)),c
	clrf	((c:_pSrc+1)),c

	goto	l2431
	line	131
	
l2447:
;usb_device_hid.c: 131: ctrl_trf_session_owner = 2;
	movlw	low(02h)
	movwf	((c:_ctrl_trf_session_owner)),c
	line	133
	
l2449:
;usb_device_hid.c: 133: active_protocol = SetupPkt.W_Value.v[0];
	movff	0+((c:_SetupPkt)+02h),(c:_active_protocol)
	line	134
;usb_device_hid.c: 134: break;
	goto	l495
	line	105
	
l2453:
	movf	(0+((c:_SetupPkt)+01h)),c,w
	; Switch size 1, requested type "space"
; Number of cases is 6, Range of values is 1 to 11
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           19    10 (average)
;	Chosen strategy is simple_byte

	xorlw	1^0	; case 1
	skipnz
	goto	l2423
	xorlw	2^1	; case 2
	skipnz
	goto	l2427
	xorlw	3^2	; case 3
	skipnz
	goto	l2439
	xorlw	9^3	; case 9
	skipnz
	goto	l2425
	xorlw	10^9	; case 10
	skipnz
	goto	l2435
	xorlw	11^10	; case 11
	skipnz
	goto	l2447
	goto	l495

	line	137
	
l495:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCheckHIDRequest
	__end_of_USBCheckHIDRequest:
	signat	_USBCheckHIDRequest,88
	global	_HIDSetReportHandler

;; *************** function _HIDSetReportHandler *****************
;; Defined at:
;;		line 144 in file "../src/usb_device_hid.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBCheckHIDRequest
;; This function uses a non-reentrant model
;;
psect	text18,class=CODE,space=0,reloc=2
	line	144
global __ptext18
__ptext18:
psect	text18
	file	"../src/usb_device_hid.c"
	line	144
	global	__size_of_HIDSetReportHandler
	__size_of_HIDSetReportHandler	equ	__end_of_HIDSetReportHandler-_HIDSetReportHandler
	
_HIDSetReportHandler:
;incstack = 0
	opt	stack 25
	line	148
	
l519:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_HIDSetReportHandler
	__end_of_HIDSetReportHandler:
	signat	_HIDSetReportHandler,88
	global	_HIDGetReportHandler

;; *************** function _HIDGetReportHandler *****************
;; Defined at:
;;		line 139 in file "../src/usb_device_hid.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBCheckHIDRequest
;; This function uses a non-reentrant model
;;
psect	text19,class=CODE,space=0,reloc=2
	line	139
global __ptext19
__ptext19:
psect	text19
	file	"../src/usb_device_hid.c"
	line	139
	global	__size_of_HIDGetReportHandler
	__size_of_HIDGetReportHandler	equ	__end_of_HIDGetReportHandler-_HIDGetReportHandler
	
_HIDGetReportHandler:
;incstack = 0
	opt	stack 25
	line	142
	
l516:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_HIDGetReportHandler
	__end_of_HIDGetReportHandler:
	signat	_HIDGetReportHandler,88
	global	_USBCtrlTrfInHandler

;; *************** function _USBCtrlTrfInHandler *****************
;; Defined at:
;;		line 1015 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_USBCtrlTrfTxService
;; This function is called by:
;;		_USBDeviceTasks
;; This function uses a non-reentrant model
;;
psect	text20,class=CODE,space=0,reloc=2
	file	"../src/usb_device.c"
	line	1015
global __ptext20
__ptext20:
psect	text20
	file	"../src/usb_device.c"
	line	1015
	global	__size_of_USBCtrlTrfInHandler
	__size_of_USBCtrlTrfInHandler	equ	__end_of_USBCtrlTrfInHandler-_USBCtrlTrfInHandler
	
_USBCtrlTrfInHandler:
;incstack = 0
	opt	stack 27
	line	1020
	
l2861:
;usb_device.c: 1020: if(usb_device_state == 4)
		movlw	4
	xorwf	((c:_usb_device_state)),c,w
	btfss	status,2
	goto	u1711
	goto	u1710

u1711:
	goto	l2871
u1710:
	line	1022
	
l2863:
;usb_device.c: 1021: {
;usb_device.c: 1022: UADDR = SetupPkt.bDevADR;
	movff	0+((c:_SetupPkt)+02h),(3896)	;volatile
	line	1023
	
l2865:
;usb_device.c: 1023: if(UADDR > 0)
	movlb	15	; () banked
	movf	((3896))&0ffh,w	;volatile
	btfsc	status,2
	goto	u1721
	goto	u1720
u1721:
	goto	l2869
u1720:
	line	1024
	
l2867:; BSR set to: 15

;usb_device.c: 1024: usb_device_state = 5;
	movlw	low(05h)
	movwf	((c:_usb_device_state)),c
	goto	l2871
	line	1026
	
l2869:; BSR set to: 15

;usb_device.c: 1025: else
;usb_device.c: 1026: usb_device_state = 3;
	movlw	low(03h)
	movwf	((c:_usb_device_state)),c
	line	1031
	
l2871:
;usb_device.c: 1027: }
;usb_device.c: 1031: if(ctrl_trf_state == 1)
		decf	((c:_ctrl_trf_state)),c,w
	btfss	status,2
	goto	u1731
	goto	u1730

u1731:
	goto	l345
u1730:
	line	1035
	
l2873:
;usb_device.c: 1032: {
;usb_device.c: 1035: USBCtrlTrfTxService();
	call	_USBCtrlTrfTxService	;wreg free
	line	1038
	
l2875:
;usb_device.c: 1038: if(short_pkt_status == 2)
		movlw	2
	xorwf	((c:_short_pkt_status)),c,w
	btfss	status,2
	goto	u1741
	goto	u1740

u1741:
	goto	l340
u1740:
	line	1042
	
l2877:
;usb_device.c: 1039: {
;usb_device.c: 1042: ep0Bi.Stat._byte = 0x04;
	movlw	low(04h)
	movlb	13	; () banked
	movwf	((3336))&0ffh	;volatile
	line	1043
	
l2879:; BSR set to: 13

;usb_device.c: 1043: ep0Bi.Stat._byte |= 0x80;
	bsf	(0+(7/8)+(3336))&0ffh,(7)&7	;volatile
	line	1044
;usb_device.c: 1044: }
	goto	l345
	line	1045
	
l340:
	line	1048
;usb_device.c: 1045: else
;usb_device.c: 1046: {
;usb_device.c: 1048: if(ep0Bi.Stat.DTS == 0)
	movlb	13	; () banked
	btfsc	((3336))&0ffh,6	;volatile
	goto	u1751
	goto	u1750
u1751:
	goto	l2883
u1750:
	line	1049
	
l2881:; BSR set to: 13

;usb_device.c: 1049: ep0Bi.Stat._byte = 0x40|0x08;
	movlw	low(048h)
	movwf	((3336))&0ffh	;volatile
	goto	l2885
	line	1051
	
l2883:; BSR set to: 13

;usb_device.c: 1050: else
;usb_device.c: 1051: ep0Bi.Stat._byte = 0x00|0x08;
	movlw	low(08h)
	movwf	((3336))&0ffh	;volatile
	line	1053
	
l2885:; BSR set to: 13

;usb_device.c: 1053: ep0Bi.Stat._byte |= 0x80;
	bsf	(0+(7/8)+(3336))&0ffh,(7)&7	;volatile
	line	1063
	
l345:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCtrlTrfInHandler
	__end_of_USBCtrlTrfInHandler:
	signat	_USBCtrlTrfInHandler,88
	global	_USBCtrlTrfTxService

;; *************** function _USBCtrlTrfTxService *****************
;; Defined at:
;;		line 1085 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru
;; Tracked objects:
;;		On entry : 0/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBCtrlTrfInHandler
;;		_USBCtrlEPServiceComplete
;; This function uses a non-reentrant model
;;
psect	text21,class=CODE,space=0,reloc=2
	line	1085
global __ptext21
__ptext21:
psect	text21
	file	"../src/usb_device.c"
	line	1085
	global	__size_of_USBCtrlTrfTxService
	__size_of_USBCtrlTrfTxService	equ	__end_of_USBCtrlTrfTxService-_USBCtrlTrfTxService
	
_USBCtrlTrfTxService:
;incstack = 0
	opt	stack 26
	line	1092
	
l2501:
;usb_device.c: 1087: static uint8_t bytes_to_send;
;usb_device.c: 1092: bytes_to_send = 8;
	movlw	low(08h)
	movwf	((c:USBCtrlTrfTxService@bytes_to_send)),c
	line	1093
	
l2503:
;usb_device.c: 1093: if(wCount.Val < 8)
		movf	((c:_wCount+1)),c,w
	bnz	u1271
	movlw	8
	subwf	 ((c:_wCount)),c,w
	btfsc	status,0
	goto	u1271
	goto	u1270

u1271:
	goto	l2515
u1270:
	line	1097
	
l2505:
;usb_device.c: 1094: {
;usb_device.c: 1097: bytes_to_send = wCount.Val;
	movff	(c:_wCount),(c:USBCtrlTrfTxService@bytes_to_send)
	line	1098
	
l2507:
;usb_device.c: 1098: if(short_pkt_status == 0)
	movf	((c:_short_pkt_status)),c,w
	btfss	status,2
	goto	u1281
	goto	u1280
u1281:
	goto	l2511
u1280:
	line	1100
	
l2509:
;usb_device.c: 1099: {
;usb_device.c: 1100: short_pkt_status = 1;
	movlw	low(01h)
	movwf	((c:_short_pkt_status)),c
	line	1101
;usb_device.c: 1101: }
	goto	l2515
	line	1102
	
l2511:
;usb_device.c: 1102: else if(short_pkt_status == 1)
		decf	((c:_short_pkt_status)),c,w
	btfss	status,2
	goto	u1291
	goto	u1290

u1291:
	goto	l2515
u1290:
	line	1104
	
l2513:
;usb_device.c: 1103: {
;usb_device.c: 1104: short_pkt_status = 2;
	movlw	low(02h)
	movwf	((c:_short_pkt_status)),c
	line	1109
	
l2515:
;usb_device.c: 1105: }
;usb_device.c: 1106: }
;usb_device.c: 1109: ep0Bi.Cnt = bytes_to_send;
	movff	(c:USBCtrlTrfTxService@bytes_to_send),0+(3336+01h)	;volatile
	line	1112
	
l2517:
;usb_device.c: 1112: wCount.Val -= bytes_to_send;
	movf	((c:USBCtrlTrfTxService@bytes_to_send)),c,w
	subwf	((c:_wCount)),c
	movlw	0
	subwfb	((c:_wCount+1)),c
	line	1117
	
l2519:
;usb_device.c: 1117: pDst.bRam = (uint8_t*)&CtrlTrfData;
		movlw	low(3364)
	movwf	((c:_pDst)),c
	movlw	high(3364)
	movwf	((c:_pDst+1)),c

	line	1118
	
l2521:
;usb_device.c: 1118: if(usb_stat.ctrl_trf_mem == 1)
	btfss	((c:_usb_stat)),c,1
	goto	u1301
	goto	u1300
u1301:
	goto	l2543
u1300:
	goto	l2533
	line	1122
	
l2525:
;usb_device.c: 1121: {
;usb_device.c: 1122: *pDst.bRam = *pSrc.bRom;
	movff	(c:_pSrc),tblptrl
	movff	(c:_pSrc+1),tblptrh
	movlw	low highword(__smallconst)
	movwf	tblptru
	
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	movlw	high __ramtop-1
	cpfsgt	tblptrh
	bra	u1317
	tblrd	*
	
	movf	tablat,w
	bra	u1310
u1317:
	movff	tblptrl,fsr1l
	movff	tblptrh,fsr1h
	movf	indf1,w
u1310:
	movwf	indf2
	line	1123
	
l2527:
;usb_device.c: 1123: pDst.bRam++;
	infsnz	((c:_pDst)),c
	incf	((c:_pDst+1)),c
	line	1124
	
l2529:
;usb_device.c: 1124: pSrc.bRom++;
	infsnz	((c:_pSrc)),c
	incf	((c:_pSrc+1)),c
	line	1125
	
l2531:
;usb_device.c: 1125: bytes_to_send--;
	decf	((c:USBCtrlTrfTxService@bytes_to_send)),c
	line	1120
	
l2533:
	movf	((c:USBCtrlTrfTxService@bytes_to_send)),c,w
	btfss	status,2
	goto	u1321
	goto	u1320
u1321:
	goto	l2525
u1320:
	goto	l362
	line	1132
	
l2535:
;usb_device.c: 1131: {
;usb_device.c: 1132: *pDst.bRam = *pSrc.bRam;
	movff	(c:_pSrc),tblptrl
	movff	(c:_pSrc+1),tblptrh
	movlw	low highword(__smallconst)
	movwf	tblptru
	
	movff	(c:_pDst),fsr2l
	movff	(c:_pDst+1),fsr2h
	movlw	high __ramtop-1
	cpfsgt	tblptrh
	bra	u1337
	tblrd	*
	
	movf	tablat,w
	bra	u1330
u1337:
	movff	tblptrl,fsr1l
	movff	tblptrh,fsr1h
	movf	indf1,w
u1330:
	movwf	indf2
	line	1133
	
l2537:
;usb_device.c: 1133: pDst.bRam++;
	infsnz	((c:_pDst)),c
	incf	((c:_pDst+1)),c
	line	1134
	
l2539:
;usb_device.c: 1134: pSrc.bRam++;
	infsnz	((c:_pSrc)),c
	incf	((c:_pSrc+1)),c
	line	1135
	
l2541:
;usb_device.c: 1135: bytes_to_send--;
	decf	((c:USBCtrlTrfTxService@bytes_to_send)),c
	line	1130
	
l2543:
	movf	((c:USBCtrlTrfTxService@bytes_to_send)),c,w
	btfss	status,2
	goto	u1341
	goto	u1340
u1341:
	goto	l2535
u1340:
	line	1139
	
l362:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCtrlTrfTxService
	__end_of_USBCtrlTrfTxService:
	signat	_USBCtrlTrfTxService,88
	global	_SignFlash

;; *************** function _SignFlash *****************
;; Defined at:
;;		line 476 in file "../src/boot_18fxxjxx.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  pROM            3    8[COMRAM] PTR  unsigned char 
;;		 -> ROM(131063), 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_ClearWatchdog
;;		_EraseFlashPage
;;		_UnlockAndActivate
;; This function is called by:
;;		_ProcessIO
;; This function uses a non-reentrant model
;;
psect	text22,class=CODE,space=0,reloc=2
	file	"../src/boot_18fxxjxx.c"
	line	476
global __ptext22
__ptext22:
psect	text22
	file	"../src/boot_18fxxjxx.c"
	line	476
	global	__size_of_SignFlash
	__size_of_SignFlash	equ	__end_of_SignFlash-_SignFlash
	
_SignFlash:
;incstack = 0
	opt	stack 25
	line	483
	
l3045:
;boot_18fxxjxx.c: 478: static unsigned int i;
;boot_18fxxjxx.c: 479: far const uint8_t* pROM;
;boot_18fxxjxx.c: 483: pROM = (far const uint8_t*)(0x1006 & (uint32_t)(0x1000000 - 1024));
		movlw	low(01000h)
	movwf	((c:SignFlash@pROM)),c
	movlw	high(01000h)
	movwf	((c:SignFlash@pROM+1)),c
	movlw	low highword(01000h)
	movwf	((c:SignFlash@pROM+2)),c

	line	484
	
l3047:
;boot_18fxxjxx.c: 484: for(i = 0; i < 1024; i++)
	clrf	((c:SignFlash@i)),c
	clrf	((c:SignFlash@i+1)),c
	line	486
	
l3051:
;boot_18fxxjxx.c: 485: {
;boot_18fxxjxx.c: 486: ProgrammingBuffer[i] = *pROM++;
	movff	(c:SignFlash@pROM),tblptrl
	movff	(c:SignFlash@pROM+1),tblptrh
	movff	(c:SignFlash@pROM+2),tblptru
	movlw	low(_ProgrammingBuffer)
	addwf	((c:SignFlash@i)),c,w
	movwf	c:fsr2l
	movlw	high(_ProgrammingBuffer)
	addwfc	((c:SignFlash@i+1)),c,w
	movwf	1+c:fsr2l
	tblrd	*
	
	movff	tablat,indf2
	
l3053:
	movlw	low(01h)
	addwf	((c:SignFlash@pROM)),c
	movlw	high(01h)
	addwfc	((c:SignFlash@pROM+1)),c
	movlw	low highword(01h)
	addwfc	((c:SignFlash@pROM+2)),c
	line	484
	
l3055:
	infsnz	((c:SignFlash@i)),c
	incf	((c:SignFlash@i+1)),c
	
l3057:
		movlw	4
	subwf	 ((c:SignFlash@i+1)),c,w
	btfss	status,0
	goto	u2021
	goto	u2020

u2021:
	goto	l3051
u2020:
	
l654:
	line	490
;boot_18fxxjxx.c: 487: }
;boot_18fxxjxx.c: 490: ProgrammingBuffer[(0x1006 & ~(uint32_t)(0x1000000 - 1024))] = (unsigned char)0x600D;
	movlw	low(0Dh)
	movff	wreg,0+(_ProgrammingBuffer+06h)

	line	491
;boot_18fxxjxx.c: 491: ProgrammingBuffer[(0x1006 & ~(uint32_t)(0x1000000 - 1024)) + 1] = (unsigned char)(0x600D >> 8);
	movlw	low(060h)
	movff	wreg,0+(_ProgrammingBuffer+07h)

	line	494
	
l3059:
;boot_18fxxjxx.c: 494: EraseFlashPage(0x1006 / 1024);
	movlw	high(04h)
	movwf	((c:EraseFlashPage@PageNumToErase+1)),c
	movlw	low(04h)
	movwf	((c:EraseFlashPage@PageNumToErase)),c
	call	_EraseFlashPage	;wreg free
	line	502
	
l3061:
;boot_18fxxjxx.c: 502: pROM = (far const uint8_t*)((0x1006 & (uint32_t)(0x1000000 - 1024)) + 1024 - 1);
		movlw	low(013FFh)
	movwf	((c:SignFlash@pROM)),c
	movlw	high(013FFh)
	movwf	((c:SignFlash@pROM+1)),c
	movlw	low highword(013FFh)
	movwf	((c:SignFlash@pROM+2)),c

	line	504
	
l3063:
;boot_18fxxjxx.c: 504: i = 1024 - 1;
	movlw	high(03FFh)
	movwf	((c:SignFlash@i+1)),c
	setf	((c:SignFlash@i)),c
	line	508
	
l3065:
;boot_18fxxjxx.c: 506: {
;boot_18fxxjxx.c: 508: TBLPTRU = (uint32_t)pROM >> 16;
	movff	0+((c:SignFlash@pROM)+02h),(c:4088)	;volatile
	line	509
	
l3067:
;boot_18fxxjxx.c: 509: TBLPTRH = (uint16_t)pROM >> 8;
	movff	0+((c:SignFlash@pROM)+01h),(c:4087)	;volatile
	line	510
	
l3069:
;boot_18fxxjxx.c: 510: TBLPTRL = (uint8_t)pROM;
	movff	(c:SignFlash@pROM),(c:4086)	;volatile
	line	514
	
l3071:
;boot_18fxxjxx.c: 514: TABLAT = ProgrammingBuffer[i];
	movlw	low(_ProgrammingBuffer)
	addwf	((c:SignFlash@i)),c,w
	movwf	c:fsr2l
	movlw	high(_ProgrammingBuffer)
	addwfc	((c:SignFlash@i+1)),c,w
	movwf	1+c:fsr2l
	movf	indf2,w
	movwf	((c:4085)),c	;volatile
	line	518
# 518 "../src/boot_18fxxjxx.c"
tblwt ;# 
psect	text22
	line	525
	
l3073:
;boot_18fxxjxx.c: 525: if((i % 64) == 0)
	movff	(c:SignFlash@i),??_SignFlash+0+0
	movlw	03Fh
	andwf	(??_SignFlash+0+0),c
	btfss	status,2
	goto	u2031
	goto	u2030
u2031:
	goto	l3081
u2030:
	line	528
	
l3075:
;boot_18fxxjxx.c: 526: {
;boot_18fxxjxx.c: 528: ClearWatchdog();
	call	_ClearWatchdog	;wreg free
	line	529
	
l3077:
;boot_18fxxjxx.c: 529: EECON1 = 0x04;
	movlw	low(04h)
	movwf	((c:4006)),c	;volatile
	line	530
	
l3079:
;boot_18fxxjxx.c: 530: UnlockAndActivate(0xB5);
	movlw	(0B5h)&0ffh
	
	call	_UnlockAndActivate
	line	533
	
l3081:
;boot_18fxxjxx.c: 531: }
;boot_18fxxjxx.c: 533: pROM--;
	movlw	low(01h)
	subwf	((c:SignFlash@pROM)),c
	movlw	high(01h)
	subwfb	((c:SignFlash@pROM+1)),c
	movlw	low highword(01h)
	subwfb	((c:SignFlash@pROM+2)),c
	line	536
# 536 "../src/boot_18fxxjxx.c"
tblrdpostdec ;# 
psect	text22
	line	543
	
l3083:
;boot_18fxxjxx.c: 543: if(i == 0)
	movf	((c:SignFlash@i)),c,w
iorwf	((c:SignFlash@i+1)),c,w
	btfss	status,2
	goto	u2041
	goto	u2040

u2041:
	goto	l3087
u2040:
	goto	l660
	line	547
	
l3087:
;boot_18fxxjxx.c: 546: }
;boot_18fxxjxx.c: 547: i--;
	decf	((c:SignFlash@i)),c
	btfss	status,0
	decf	((c:SignFlash@i+1)),c
	goto	l3065
	line	549
	
l660:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_SignFlash
	__end_of_SignFlash:
	signat	_SignFlash,88
	global	_EraseFlashPage

;; *************** function _EraseFlashPage *****************
;; Defined at:
;;		line 681 in file "../src/boot_18fxxjxx.c"
;; Parameters:    Size  Location     Type
;;  PageNumToEra    2    1[COMRAM] unsigned int 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         6       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_UnlockAndActivate
;; This function is called by:
;;		_ProcessIO
;;		_SignFlash
;; This function uses a non-reentrant model
;;
psect	text23,class=CODE,space=0,reloc=2
	line	681
global __ptext23
__ptext23:
psect	text23
	file	"../src/boot_18fxxjxx.c"
	line	681
	global	__size_of_EraseFlashPage
	__size_of_EraseFlashPage	equ	__end_of_EraseFlashPage-_EraseFlashPage
	
_EraseFlashPage:
;incstack = 0
	opt	stack 25
	line	686
	
l2887:
;boot_18fxxjxx.c: 683: static uint32_t TablePointerValue;
;boot_18fxxjxx.c: 686: if(PageNumToErase < ((uint32_t)0x1000/1024))
		movf	((c:EraseFlashPage@PageNumToErase+1)),c,w
	bnz	u1761
	movlw	4
	subwf	 ((c:EraseFlashPage@PageNumToErase)),c,w
	btfsc	status,0
	goto	u1761
	goto	u1760

u1761:
	goto	l2891
u1760:
	line	687
	
l2889:
;boot_18fxxjxx.c: 687: PageNumToErase = ((uint32_t)0x1000/1024);
	movlw	high(04h)
	movwf	((c:EraseFlashPage@PageNumToErase+1)),c
	movlw	low(04h)
	movwf	((c:EraseFlashPage@PageNumToErase)),c
	line	691
	
l2891:
;boot_18fxxjxx.c: 691: TablePointerValue = 1024 * (uint32_t)PageNumToErase;
	movf	((c:EraseFlashPage@PageNumToErase)),c,w
	movwf	(??_EraseFlashPage+0+0)&0ffh,c
	movf	((c:EraseFlashPage@PageNumToErase+1)),c,w
	movwf	1+(??_EraseFlashPage+0+0)&0ffh,c
	
	clrf	2+(??_EraseFlashPage+0+0)&0ffh,c
	
	clrf	3+(??_EraseFlashPage+0+0)&0ffh,c
	movlw	0Ah
u1775:
	bcf	status,0
	rlcf	(??_EraseFlashPage+0+0),c
	rlcf	(??_EraseFlashPage+0+1),c
	rlcf	(??_EraseFlashPage+0+2),c
	rlcf	(??_EraseFlashPage+0+3),c
	decfsz	wreg
	goto	u1775
	movff	??_EraseFlashPage+0+0,(c:EraseFlashPage@TablePointerValue)
	movff	??_EraseFlashPage+0+1,(c:EraseFlashPage@TablePointerValue+1)
	movff	??_EraseFlashPage+0+2,(c:EraseFlashPage@TablePointerValue+2)
	movff	??_EraseFlashPage+0+3,(c:EraseFlashPage@TablePointerValue+3)
	line	692
	
l2893:
;boot_18fxxjxx.c: 692: TBLPTRU = TablePointerValue >> 16;
	movff	0+((c:EraseFlashPage@TablePointerValue)+02h),(c:4088)	;volatile
	line	693
	
l2895:
;boot_18fxxjxx.c: 693: TBLPTRH = TablePointerValue >> 8;
	movff	0+((c:EraseFlashPage@TablePointerValue)+01h),(c:4087)	;volatile
	line	694
	
l2897:
;boot_18fxxjxx.c: 694: TBLPTRL = 0x00;
	clrf	((c:4086)),c	;volatile
	line	700
	
l2899:
;boot_18fxxjxx.c: 700: EECON1 = 0b00010100;
	movlw	low(014h)
	movwf	((c:4006)),c	;volatile
	line	701
	
l2901:
;boot_18fxxjxx.c: 701: UnlockAndActivate(0xB5);
	movlw	(0B5h)&0ffh
	
	call	_UnlockAndActivate
	line	702
	
l689:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_EraseFlashPage
	__end_of_EraseFlashPage:
	signat	_EraseFlashPage,4216
	global	_UnlockAndActivate

;; *************** function _UnlockAndActivate *****************
;; Defined at:
;;		line 635 in file "../src/boot_18fxxjxx.c"
;; Parameters:    Size  Location     Type
;;  UnlockKey       1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  UnlockKey       1    0[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_LowVoltageCheck
;; This function is called by:
;;		_SignFlash
;;		_WriteFlashSubBlock
;;		_EraseFlashPage
;; This function uses a non-reentrant model
;;
psect	text24,class=CODE,space=0,reloc=2
	line	635
global __ptext24
__ptext24:
psect	text24
	file	"../src/boot_18fxxjxx.c"
	line	635
	global	__size_of_UnlockAndActivate
	__size_of_UnlockAndActivate	equ	__end_of_UnlockAndActivate-_UnlockAndActivate
	
_UnlockAndActivate:
;incstack = 0
	opt	stack 26
;UnlockAndActivate@UnlockKey stored from wreg
	movwf	((c:UnlockAndActivate@UnlockKey)),c
	line	637
	
l2797:
;boot_18fxxjxx.c: 637: INTCONbits.GIE = 0;
	bcf	((c:4082)),c,7	;volatile
	line	640
	
l2799:
;boot_18fxxjxx.c: 640: LowVoltageCheck();
	call	_LowVoltageCheck	;wreg free
	line	644
	
l2801:
;boot_18fxxjxx.c: 644: if(UnlockKey != 0xB5)
		movlw	181
	xorwf	((c:UnlockAndActivate@UnlockKey)),c,w
	btfsc	status,2
	goto	u1641
	goto	u1640

u1641:
	goto	l2805
u1640:
	line	653
	
l2803:
;boot_18fxxjxx.c: 645: {
;boot_18fxxjxx.c: 653: OSCCON = 0x03;
	movlw	low(03h)
	movwf	((c:4051)),c	;volatile
	line	654
;boot_18fxxjxx.c: 654: while(1)
	
l677:
	line	656
# 656 "../src/boot_18fxxjxx.c"
sleep ;# 
psect	text24
	goto	l677
	line	662
	
l2805:
;boot_18fxxjxx.c: 659: }
;boot_18fxxjxx.c: 662: EECON2 = 0x55;
	movlw	low(055h)
	movwf	((c:4007)),c	;volatile
	line	663
;boot_18fxxjxx.c: 663: EECON2 = 0xAA;
	movlw	low(0AAh)
	movwf	((c:4007)),c	;volatile
	line	664
	
l2807:
;boot_18fxxjxx.c: 664: EECON1bits.WR = 1;
	bsf	((c:4006)),c,1	;volatile
	line	676
;boot_18fxxjxx.c: 676: while(EECON1bits.WR);
	
l680:
	btfsc	((c:4006)),c,1	;volatile
	goto	u1651
	goto	u1650
u1651:
	goto	l680
u1650:
	
l682:
	line	677
;boot_18fxxjxx.c: 677: EECON1bits.WREN = 0;
	bcf	((c:4006)),c,2	;volatile
	line	678
	
l683:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_UnlockAndActivate
	__end_of_UnlockAndActivate:
	signat	_UnlockAndActivate,4216
	global	_LowVoltageCheck

;; *************** function _LowVoltageCheck *****************
;; Defined at:
;;		line 635 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_BootMain
;;		_UnlockAndActivate
;; This function uses a non-reentrant model
;;
psect	text25,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	635
global __ptext25
__ptext25:
psect	text25
	file	"../src/main.c"
	line	635
	global	__size_of_LowVoltageCheck
	__size_of_LowVoltageCheck	equ	__end_of_LowVoltageCheck-_LowVoltageCheck
	
_LowVoltageCheck:
;incstack = 0
	opt	stack 26
	line	641
	
l2373:
;main.c: 641: if(WDTCONbits.LVDSTAT == 0)
	btfsc	((c:4032)),c,6	;volatile
	goto	u1171
	goto	u1170
u1171:
	goto	l90
u1170:
	line	646
	
l2375:
;main.c: 642: {
;main.c: 646: OSCCON = 0x03;
	movlw	low(03h)
	movwf	((c:4051)),c	;volatile
	line	647
	
l2377:
;main.c: 647: UCONbits.SUSPND = 0;
	bcf	((c:3941)),c,1	;volatile
	line	648
	
l2379:
;main.c: 648: UCONbits.USBEN = 0;
	bcf	((c:3941)),c,3	;volatile
	line	649
	
l2381:
;main.c: 649: INTCON = 0x00;
	clrf	((c:4082)),c	;volatile
	line	652
;main.c: 652: uint_delay_counter = 0x400;
	movlw	high(0400h)
	movwf	((c:_uint_delay_counter+1)),c
	movlw	low(0400h)
	movwf	((c:_uint_delay_counter)),c
	line	653
;main.c: 653: while(uint_delay_counter)
	goto	l2387
	
l86:
	line	655
;main.c: 654: {
;main.c: 655: if(WDTCONbits.LVDSTAT == 1)
	btfss	((c:4032)),c,6	;volatile
	goto	u1181
	goto	u1180
u1181:
	goto	l2385
u1180:
	line	657
	
l2383:
;main.c: 656: {
;main.c: 657: uint_delay_counter--;
	decf	((c:_uint_delay_counter)),c
	btfss	status,0
	decf	((c:_uint_delay_counter+1)),c
	line	658
;main.c: 658: }
	goto	l88
	line	661
	
l2385:
;main.c: 659: else
;main.c: 660: {
;main.c: 661: uint_delay_counter = 0x400;
	movlw	high(0400h)
	movwf	((c:_uint_delay_counter+1)),c
	movlw	low(0400h)
	movwf	((c:_uint_delay_counter)),c
	line	662
	
l88:
	line	663
# 663 "../src/main.c"
clrwdt ;# 
psect	text25
	line	653
	
l2387:
	movf	((c:_uint_delay_counter)),c,w
iorwf	((c:_uint_delay_counter+1)),c,w
	btfss	status,2
	goto	u1191
	goto	u1190

u1191:
	goto	l86
u1190:
	
l89:
	line	668
# 668 "../src/main.c"
reset ;# 
psect	text25
	line	670
	
l90:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_LowVoltageCheck
	__end_of_LowVoltageCheck:
	signat	_LowVoltageCheck,88
	global	_ResetDeviceCleanly

;; *************** function _ResetDeviceCleanly *****************
;; Defined at:
;;		line 561 in file "../src/boot_18fxxjxx.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_USBDisableWithLongDelay
;; This function is called by:
;;		_ProcessIO
;; This function uses a non-reentrant model
;;
psect	text26,class=CODE,space=0,reloc=2
	file	"../src/boot_18fxxjxx.c"
	line	561
global __ptext26
__ptext26:
psect	text26
	file	"../src/boot_18fxxjxx.c"
	line	561
	global	__size_of_ResetDeviceCleanly
	__size_of_ResetDeviceCleanly	equ	__end_of_ResetDeviceCleanly-_ResetDeviceCleanly
	
_ResetDeviceCleanly:
;incstack = 0
	opt	stack 25
	line	563
	
l3089:
;boot_18fxxjxx.c: 563: USBDisableWithLongDelay();
	call	_USBDisableWithLongDelay	;wreg free
	line	564
# 564 "../src/boot_18fxxjxx.c"
reset ;# 
psect	text26
	line	565
	
l3091:
;boot_18fxxjxx.c: 565: __nop();
	opt	asmopt_off
	nop
	opt	asmopt_on
	line	566
	
l3093:
;boot_18fxxjxx.c: 566: __nop();
	opt	asmopt_off
	nop
	opt	asmopt_on
	line	567
	
l663:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_ResetDeviceCleanly
	__end_of_ResetDeviceCleanly:
	signat	_ResetDeviceCleanly,88
	global	_HIDTxReport

;; *************** function _HIDTxReport *****************
;; Defined at:
;;		line 229 in file "../src/usb_device_hid.c"
;; Parameters:    Size  Location     Type
;;  buffer          1    wreg     PTR unsigned char 
;;		 -> PacketToPC(65), 
;;  len             1    0[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  buffer          1    2[COMRAM] PTR unsigned char 
;;		 -> PacketToPC(65), 
;;  i               1    3[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0
;; Tracked objects:
;;		On entry : F/D
;;		On exit  : F/D
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_ProcessIO
;; This function uses a non-reentrant model
;;
psect	text27,class=CODE,space=0,reloc=2
	file	"../src/usb_device_hid.c"
	line	229
global __ptext27
__ptext27:
psect	text27
	file	"../src/usb_device_hid.c"
	line	229
	global	__size_of_HIDTxReport
	__size_of_HIDTxReport	equ	__end_of_HIDTxReport-_HIDTxReport
	
_HIDTxReport:
;incstack = 0
	opt	stack 28
;HIDTxReport@buffer stored from wreg
	movwf	((c:HIDTxReport@buffer)),c
	line	237
	
l2977:
;usb_device_hid.c: 231: uint8_t i;
;usb_device_hid.c: 237: if(len > 64)
		movlw	041h-1
	cpfsgt	((c:HIDTxReport@len)),c
	goto	u1921
	goto	u1920

u1921:
	goto	l2981
u1920:
	line	238
	
l2979:
;usb_device_hid.c: 238: len = 64;
	movlw	low(040h)
	movwf	((c:HIDTxReport@len)),c
	line	243
	
l2981:
;usb_device_hid.c: 243: for (i = 0; i < len; i++)
	clrf	((c:HIDTxReport@i)),c
	goto	l2987
	line	244
	
l2983:
;usb_device_hid.c: 244: hid_report_in[i] = buffer[i];
	movf	((c:HIDTxReport@buffer)),c,w
	addwf	((c:HIDTxReport@i)),c,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(3436)
	addwf	((c:HIDTxReport@i)),c,w
	movwf	c:fsr1l
	clrf	1+c:fsr1l
	movlw	high(3436)
	addwfc	1+c:fsr1l
	movff	indf2,indf1
	line	243
	
l2985:
	incf	((c:HIDTxReport@i)),c
	
l2987:
		movf	((c:HIDTxReport@len)),c,w
	subwf	((c:HIDTxReport@i)),c,w
	btfss	status,0
	goto	u1931
	goto	u1930

u1931:
	goto	l2983
u1930:
	
l528:
	line	246
;usb_device_hid.c: 246: ep1Bi.Cnt = len;
	movff	(c:HIDTxReport@len),0+(3344+01h)	;volatile
	line	247
	
l2989:
;usb_device_hid.c: 247: { ep1Bi.Stat._byte &= 0x40; ep1Bi.Stat.DTS = !ep1Bi.Stat.DTS; ep1Bi.Stat._byte |= 0x08; ep1Bi.Stat._byte |= 0x80; };
	movlw	(040h)&0ffh
	movlb	13	; () banked
	andwf	((3344))&0ffh	;volatile
	btfss	((3344))&0ffh,6	;volatile
	goto	u1941
	goto	u1940
u1941:
	clrf	(??_HIDTxReport+0+0)&0ffh,c
	incf	(??_HIDTxReport+0+0)&0ffh,c
	goto	u1958
u1940:
	clrf	(??_HIDTxReport+0+0)&0ffh,c
u1958:
	swapf	(??_HIDTxReport+0+0),c
	rlncf	(??_HIDTxReport+0+0),c
	rlncf	(??_HIDTxReport+0+0),c
	movlb	13	; () banked
	movf	((3344))&0ffh,w	;volatile
	xorwf	(??_HIDTxReport+0+0),c,w
	andlw	not (((1<<1)-1)<<6)
	xorwf	(??_HIDTxReport+0+0),c,w
	movwf	((3344))&0ffh	;volatile
	
l2991:; BSR set to: 13

	bsf	(0+(3/8)+(3344))&0ffh,(3)&7	;volatile
	
l2993:; BSR set to: 13

	bsf	(0+(7/8)+(3344))&0ffh,(7)&7	;volatile
	line	249
	
l529:; BSR set to: 13

	return	;funcret
	opt stack 0
GLOBAL	__end_of_HIDTxReport
	__end_of_HIDTxReport:
	signat	_HIDTxReport,8312
	global	_HIDRxReport

;; *************** function _HIDRxReport *****************
;; Defined at:
;;		line 284 in file "../src/usb_device_hid.c"
;; Parameters:    Size  Location     Type
;;  buffer          1    wreg     PTR unsigned char 
;;		 -> PacketFromPC(65), 
;;  len             1    0[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  buffer          1    2[COMRAM] PTR unsigned char 
;;		 -> PacketFromPC(65), 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0
;; Tracked objects:
;;		On entry : F/D
;;		On exit  : F/D
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_ProcessIO
;; This function uses a non-reentrant model
;;
psect	text28,class=CODE,space=0,reloc=2
	line	284
global __ptext28
__ptext28:
psect	text28
	file	"../src/usb_device_hid.c"
	line	284
	global	__size_of_HIDRxReport
	__size_of_HIDRxReport	equ	__end_of_HIDRxReport-_HIDRxReport
	
_HIDRxReport:; BSR set to: 13

;incstack = 0
	opt	stack 28
;HIDRxReport@buffer stored from wreg
	movwf	((c:HIDRxReport@buffer)),c
	line	286
	
l2995:
;usb_device_hid.c: 286: hid_rpt_rx_len = 0;
	clrf	((c:_hid_rpt_rx_len)),c
	line	288
;usb_device_hid.c: 288: if(!ep1Bo.Stat.UOWN)
	movlb	13	; () banked
	btfsc	((3340))&0ffh,7	;volatile
	goto	u1961
	goto	u1960
u1961:
	goto	l537
u1960:
	line	294
	
l2997:; BSR set to: 13

;usb_device_hid.c: 289: {
;usb_device_hid.c: 294: if(len > ep1Bo.Cnt)
		movf	((c:HIDRxReport@len)),c,w
	subwf	(0+(3340+01h))&0ffh,w	;volatile
	btfsc	status,0
	goto	u1971
	goto	u1970

u1971:
	goto	l533
u1970:
	line	295
	
l2999:; BSR set to: 13

;usb_device_hid.c: 295: len = ep1Bo.Cnt;
	movff	0+(3340+01h),(c:HIDRxReport@len)	;volatile
	
l533:; BSR set to: 13

	line	300
;usb_device_hid.c: 300: for(hid_rpt_rx_len = 0; hid_rpt_rx_len < len; hid_rpt_rx_len++)
	clrf	((c:_hid_rpt_rx_len)),c
	goto	l3005
	line	301
	
l3001:
;usb_device_hid.c: 301: buffer[hid_rpt_rx_len] = hid_report_out[hid_rpt_rx_len];
	movlw	low(3372)
	addwf	((c:_hid_rpt_rx_len)),c,w
	movwf	c:fsr2l
	clrf	1+c:fsr2l
	movlw	high(3372)
	addwfc	1+c:fsr2l
	movf	((c:HIDRxReport@buffer)),c,w
	addwf	((c:_hid_rpt_rx_len)),c,w
	movwf	fsr1l
	clrf	fsr1h
	movff	indf2,indf1
	line	300
	
l3003:
	incf	((c:_hid_rpt_rx_len)),c
	
l3005:
		movf	((c:HIDRxReport@len)),c,w
	subwf	((c:_hid_rpt_rx_len)),c,w
	btfss	status,0
	goto	u1981
	goto	u1980

u1981:
	goto	l3001
u1980:
	line	306
	
l3007:
;usb_device_hid.c: 306: ep1Bo.Cnt = sizeof(hid_report_out);
	movlw	low(040h)
	movlb	13	; () banked
	movwf	(0+(3340+01h))&0ffh	;volatile
	line	307
	
l3009:; BSR set to: 13

;usb_device_hid.c: 307: { ep1Bo.Stat._byte &= 0x40; ep1Bo.Stat.DTS = !ep1Bo.Stat.DTS; ep1Bo.Stat._byte |= 0x08; ep1Bo.Stat._byte |= 0x80; };
	movlw	(040h)&0ffh
	andwf	((3340))&0ffh	;volatile
	
l3011:; BSR set to: 13

	btfss	((3340))&0ffh,6	;volatile
	goto	u1991
	goto	u1990
u1991:
	clrf	(??_HIDRxReport+0+0)&0ffh,c
	incf	(??_HIDRxReport+0+0)&0ffh,c
	goto	u2008
u1990:
	clrf	(??_HIDRxReport+0+0)&0ffh,c
u2008:
	swapf	(??_HIDRxReport+0+0),c
	rlncf	(??_HIDRxReport+0+0),c
	rlncf	(??_HIDRxReport+0+0),c
	movlb	13	; () banked
	movf	((3340))&0ffh,w	;volatile
	xorwf	(??_HIDRxReport+0+0),c,w
	andlw	not (((1<<1)-1)<<6)
	xorwf	(??_HIDRxReport+0+0),c,w
	movwf	((3340))&0ffh	;volatile
	
l3013:; BSR set to: 13

	bsf	(0+(3/8)+(3340))&0ffh,(3)&7	;volatile
	
l3015:; BSR set to: 13

	bsf	(0+(7/8)+(3340))&0ffh,(7)&7	;volatile
	line	312
	
l537:; BSR set to: 13

	return	;funcret
	opt stack 0
GLOBAL	__end_of_HIDRxReport
	__end_of_HIDRxReport:
	signat	_HIDRxReport,8313
	global	_InitializeSystem

;; *************** function _InitializeSystem *****************
;; Defined at:
;;		line 494 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_DelayRoutine
;;		_USBDeviceInit
;;		_UserInit
;; This function is called by:
;;		_BootMain
;; This function uses a non-reentrant model
;;
psect	text29,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	494
global __ptext29
__ptext29:
psect	text29
	file	"../src/main.c"
	line	494
	global	__size_of_InitializeSystem
	__size_of_InitializeSystem	equ	__end_of_InitializeSystem-_InitializeSystem
	
_InitializeSystem:; BSR set to: 13

;incstack = 0
	opt	stack 23
	line	509
	
l3095:
;main.c: 509: OSCCON = 0x60;
	movlw	low(060h)
	movwf	((c:4051)),c	;volatile
	line	510
	
l3097:
;main.c: 510: OSCTUNEbits.PLLEN = 1;
	bsf	((c:3995)),c,6	;volatile
	line	512
	
l3099:
;main.c: 512: DelayRoutine(0x300);
	movlw	high(0300h)
	movwf	((c:DelayRoutine@DelayAmount+1)),c
	movlw	low(0300h)
	movwf	((c:DelayRoutine@DelayAmount)),c
	call	_DelayRoutine	;wreg free
	line	527
	
l3101:
;main.c: 527: ANCON0 = 0x00;
	movlb	15	; () banked
	clrf	((3912))&0ffh	;volatile
	line	528
	
l3103:; BSR set to: 15

;main.c: 528: ANCON1 = 0x00;
	clrf	((3913))&0ffh	;volatile
	line	578
	
l3105:; BSR set to: 15

;main.c: 578: UserInit();
	call	_UserInit	;wreg free
	line	580
	
l3107:
;main.c: 580: LATCbits.LATC2 = 0;
	bcf	((c:3979)),c,2	;volatile
	line	581
	
l3109:
;main.c: 581: TRISCbits.TRISC2 = 0;
	bcf	((c:3988)),c,2	;volatile
	line	585
	
l3111:
;main.c: 585: USBDeviceInit();
	call	_USBDeviceInit	;wreg free
	line	587
	
l73:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_InitializeSystem
	__end_of_InitializeSystem:
	signat	_InitializeSystem,88
	global	_USBDeviceInit

;; *************** function _USBDeviceInit *****************
;; Defined at:
;;		line 317 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : D/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_USBCheckBusStatus
;;		_USBDisableWithLongDelay
;; This function is called by:
;;		_InitializeSystem
;; This function uses a non-reentrant model
;;
psect	text30,class=CODE,space=0,reloc=2
	file	"../src/usb_device.c"
	line	317
global __ptext30
__ptext30:
psect	text30
	file	"../src/usb_device.c"
	line	317
	global	__size_of_USBDeviceInit
	__size_of_USBDeviceInit	equ	__end_of_USBDeviceInit-_USBDeviceInit
	
_USBDeviceInit:
;incstack = 0
	opt	stack 23
	line	323
	
l2969:
;usb_device.c: 323: if(UCONbits.USBEN == 1)
	btfss	((c:3941)),c,3	;volatile
	goto	u1911
	goto	u1910
u1911:
	goto	l2973
u1910:
	line	328
	
l2971:
;usb_device.c: 324: {
;usb_device.c: 328: USBDisableWithLongDelay();
	call	_USBDisableWithLongDelay	;wreg free
	line	330
	
l2973:
;usb_device.c: 329: }
;usb_device.c: 330: DeviceIsSoftDetached = 0;
	clrf	((c:_DeviceIsSoftDetached)),c
	line	338
	
l2975:
;usb_device.c: 338: USBCheckBusStatus();
	call	_USBCheckBusStatus	;wreg free
	line	339
	
l272:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBDeviceInit
	__end_of_USBDeviceInit:
	signat	_USBDeviceInit,88
	global	_USBCheckBusStatus

;; *************** function _USBCheckBusStatus *****************
;; Defined at:
;;		line 397 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_USBSoftAttach
;; This function is called by:
;;		_USBDeviceInit
;;		_USBDeviceTasks
;; This function uses a non-reentrant model
;;
psect	text31,class=CODE,space=0,reloc=2
	line	397
global __ptext31
__ptext31:
psect	text31
	file	"../src/usb_device.c"
	line	397
	global	__size_of_USBCheckBusStatus
	__size_of_USBCheckBusStatus	equ	__end_of_USBCheckBusStatus-_USBCheckBusStatus
	
_USBCheckBusStatus:
;incstack = 0
	opt	stack 24
	line	402
	
l2809:
;usb_device.c: 402: if(DeviceIsSoftDetached == 1)
		decf	((c:_DeviceIsSoftDetached)),c,w
	btfss	status,2
	goto	u1661
	goto	u1660

u1661:
	goto	l282
u1660:
	goto	l283
	line	405
	
l282:
	line	431
;usb_device.c: 405: }
;usb_device.c: 431: if(UCONbits.USBEN == 0)
	btfsc	((c:3941)),c,3	;volatile
	goto	u1671
	goto	u1670
u1671:
	goto	l283
u1670:
	line	432
	
l2813:
;usb_device.c: 432: USBSoftAttach();
	call	_USBSoftAttach	;wreg free
	line	434
	
l283:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCheckBusStatus
	__end_of_USBCheckBusStatus:
	signat	_USBCheckBusStatus,88
	global	_USBSoftAttach

;; *************** function _USBSoftAttach *****************
;; Defined at:
;;		line 345 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_USBDisableWithLongDelay
;;		_USBProtocolResetHandler
;; This function is called by:
;;		_USBCheckBusStatus
;; This function uses a non-reentrant model
;;
psect	text32,class=CODE,space=0,reloc=2
	line	345
global __ptext32
__ptext32:
psect	text32
	file	"../src/usb_device.c"
	line	345
	global	__size_of_USBSoftAttach
	__size_of_USBSoftAttach	equ	__end_of_USBSoftAttach-_USBSoftAttach
	
_USBSoftAttach:
;incstack = 0
	opt	stack 24
	line	352
	
l2679:
;usb_device.c: 352: if(DeviceIsSoftDetached == 1)
		decf	((c:_DeviceIsSoftDetached)),c,w
	btfss	status,2
	goto	u1551
	goto	u1550

u1551:
	goto	l2683
u1550:
	line	354
	
l2681:
;usb_device.c: 353: {
;usb_device.c: 354: USBDisableWithLongDelay();
	call	_USBDisableWithLongDelay	;wreg free
	line	357
	
l2683:
;usb_device.c: 355: }
;usb_device.c: 357: UCON = 0;
	clrf	((c:3941)),c	;volatile
	line	358
	
l2685:
;usb_device.c: 358: UCFG = 0x10|0x00|0x04|0x01;
	movlw	low(015h)
	movlb	15	; () banked
	movwf	((3897))&0ffh	;volatile
	line	359
	
l2687:; BSR set to: 15

;usb_device.c: 359: UIE = 0;
	clrf	((3894))&0ffh	;volatile
	line	360
	
l2689:; BSR set to: 15

;usb_device.c: 360: UCONbits.USBEN = 1;
	bsf	((c:3941)),c,3	;volatile
	line	362
	
l2691:; BSR set to: 15

;usb_device.c: 362: USBProtocolResetHandler();
	call	_USBProtocolResetHandler	;wreg free
	line	363
	
l2693:
;usb_device.c: 363: usb_device_state = 1;
	movlw	low(01h)
	movwf	((c:_usb_device_state)),c
	line	364
	
l2695:
;usb_device.c: 364: DeviceIsSoftDetached = 0;
	clrf	((c:_DeviceIsSoftDetached)),c
	line	365
	
l276:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBSoftAttach
	__end_of_USBSoftAttach:
	signat	_USBSoftAttach,88
	global	_USBProtocolResetHandler

;; *************** function _USBProtocolResetHandler *****************
;; Defined at:
;;		line 744 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_ClearWatchdog
;;		_LoadBDTandSetUOWN
;;		_USBCBInitEP
;; This function is called by:
;;		_USBSoftAttach
;;		_USBDeviceTasks
;; This function uses a non-reentrant model
;;
psect	text33,class=CODE,space=0,reloc=2
	line	744
global __ptext33
__ptext33:
psect	text33
	file	"../src/usb_device.c"
	line	744
	global	__size_of_USBProtocolResetHandler
	__size_of_USBProtocolResetHandler	equ	__end_of_USBProtocolResetHandler-_USBProtocolResetHandler
	
_USBProtocolResetHandler:
;incstack = 0
	opt	stack 26
	line	746
	
l2461:
;usb_device.c: 746: usb_device_state = 3;
	movlw	low(03h)
	movwf	((c:_usb_device_state)),c
	line	747
	
l2463:
;usb_device.c: 747: UEIE = 0;
	movlb	15	; () banked
	clrf	((3895))&0ffh	;volatile
	line	748
	
l2465:; BSR set to: 15

;usb_device.c: 748: UIR = 0;
	clrf	((c:3938)),c	;volatile
	line	749
;usb_device.c: 749: UIE = 0b01111011;
	movlw	low(07Bh)
	movwf	((3894))&0ffh	;volatile
	line	750
	
l2467:; BSR set to: 15

;usb_device.c: 750: UADDR = 0x00;
	clrf	((3896))&0ffh	;volatile
	line	751
	
l2469:; BSR set to: 15

;usb_device.c: 751: UEP1=0x00;UEP2=0x00;UEP3=0x00; UEP4=0x00;UEP5=0x00;UEP6=0x00;UEP7=0x00;;
	clrf	((3879))&0ffh	;volatile
	
l2471:; BSR set to: 15

	clrf	((3880))&0ffh	;volatile
	
l2473:; BSR set to: 15

	clrf	((3881))&0ffh	;volatile
	
l2475:; BSR set to: 15

	clrf	((3882))&0ffh	;volatile
	
l2477:; BSR set to: 15

	clrf	((3883))&0ffh	;volatile
	
l2479:; BSR set to: 15

	clrf	((3884))&0ffh	;volatile
	
l2481:; BSR set to: 15

	clrf	((3885))&0ffh	;volatile
	line	752
;usb_device.c: 752: UEP0 = 0x06|0x10;
	movlw	low(016h)
	movwf	((3878))&0ffh	;volatile
	line	753
	
l2483:; BSR set to: 15

;usb_device.c: 753: UCONbits.PPBRST = 1;
	bsf	((c:3941)),c,6	;volatile
	line	754
;usb_device.c: 754: while(UIRbits.TRNIF == 1)
	goto	l2487
	
l326:
	line	756
;usb_device.c: 755: {
;usb_device.c: 756: UIRbits.TRNIF = 0;
	bcf	((c:3938)),c,3	;volatile
	line	757
	
l2485:
;usb_device.c: 757: ClearWatchdog();
	call	_ClearWatchdog	;wreg free
	line	754
	
l2487:
	btfsc	((c:3938)),c,3	;volatile
	goto	u1261
	goto	u1260
u1261:
	goto	l326
u1260:
	
l327:
	line	759
;usb_device.c: 758: }
;usb_device.c: 759: UCONbits.PPBRST = 0;
	bcf	((c:3941)),c,6	;volatile
	line	760
;usb_device.c: 760: UCONbits.PKTDIS = 0;
	bcf	((c:3941)),c,4	;volatile
	line	763
	
l2489:
;usb_device.c: 763: TempBDT.Stat._byte = 0x00|0x04;
	movlw	low(04h)
	movwf	((c:_TempBDT)),c
	line	764
	
l2491:
;usb_device.c: 764: LoadBDTandSetUOWN(0);
	movlw	(0)&0ffh
	
	call	_LoadBDTandSetUOWN
	line	765
	
l2493:
;usb_device.c: 765: EP0OutOddNeedsArmingNext = 1;
	movlw	low(01h)
	movwf	((c:_EP0OutOddNeedsArmingNext)),c
	line	766
	
l2495:
;usb_device.c: 766: usb_stat._byte = 0x00;
	clrf	((c:_usb_stat)),c
	line	767
	
l2497:
;usb_device.c: 767: usb_active_cfg = 0;
	clrf	((c:_usb_active_cfg)),c
	line	768
	
l2499:
;usb_device.c: 768: USBCBInitEP(0);
	movlw	(0)&0ffh
	
	call	_USBCBInitEP
	line	770
	
l328:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBProtocolResetHandler
	__end_of_USBProtocolResetHandler:
	signat	_USBProtocolResetHandler,88
	global	_USBCBInitEP

;; *************** function _USBCBInitEP *****************
;; Defined at:
;;		line 830 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;  Configuratio    1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Configuratio    1    0[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_HIDInitEP
;;		_UserInit
;; This function is called by:
;;		_USBProtocolResetHandler
;;		_USBStdSetCfgHandler
;; This function uses a non-reentrant model
;;
psect	text34,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	830
global __ptext34
__ptext34:
psect	text34
	file	"../src/main.c"
	line	830
	global	__size_of_USBCBInitEP
	__size_of_USBCBInitEP	equ	__end_of_USBCBInitEP-_USBCBInitEP
	
_USBCBInitEP:
;incstack = 0
	opt	stack 26
;USBCBInitEP@ConfigurationIndex stored from wreg
	movwf	((c:USBCBInitEP@ConfigurationIndex)),c
	line	839
	
l2355:
;main.c: 839: if(ConfigurationIndex == 1)
		decf	((c:USBCBInitEP@ConfigurationIndex)),c,w
	btfss	status,2
	goto	u1151
	goto	u1150

u1151:
	goto	l107
u1150:
	line	845
	
l2357:
;main.c: 840: {
;main.c: 845: HIDInitEP();
	call	_HIDInitEP	;wreg free
	line	848
	
l2359:; BSR set to: 13

;main.c: 848: UserInit();
	call	_UserInit	;wreg free
	line	855
	
l107:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBCBInitEP
	__end_of_USBCBInitEP:
	signat	_USBCBInitEP,4216
	global	_UserInit

;; *************** function _UserInit *****************
;; Defined at:
;;		line 237 in file "../src/boot_18fxxjxx.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : D/F
;;		On exit  : D/D
;;		Unchanged: C/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_InitializeSystem
;;		_USBCBInitEP
;; This function uses a non-reentrant model
;;
psect	text35,class=CODE,space=0,reloc=2
	file	"../src/boot_18fxxjxx.c"
	line	237
global __ptext35
__ptext35:
psect	text35
	file	"../src/boot_18fxxjxx.c"
	line	237
	global	__size_of_UserInit
	__size_of_UserInit	equ	__end_of_UserInit-_UserInit
	
_UserInit:
;incstack = 0
	opt	stack 26
	line	240
	
l2323:
;boot_18fxxjxx.c: 240: MaxPageToErase = ((((uint32_t)0x01FFF8)/1024) - 1);
	movlw	low(07Eh)
	movwf	((c:_MaxPageToErase)),c
	line	241
;boot_18fxxjxx.c: 241: ProgramMemStopAddress = ((((((uint32_t)0x01FFF8)/1024) - 1) + 1) * 1024);
	movlw	low(01FC00h)
	movwf	((c:_ProgramMemStopAddress)),c
	movlw	high(01FC00h)
	movwf	((c:_ProgramMemStopAddress+1)),c
	movlw	low highword(01FC00h)
	movwf	((c:_ProgramMemStopAddress+2)),c
	movlw	high highword(01FC00h)
	movwf	((c:_ProgramMemStopAddress+3)),c
	line	242
	
l2325:
;boot_18fxxjxx.c: 242: BootState = 0x00;
	clrf	((c:_BootState)),c
	line	243
	
l2327:
;boot_18fxxjxx.c: 243: ProgrammedPointer = 0xFFFFFFFF;
	setf	((c:_ProgrammedPointer)),c
	setf	((c:_ProgrammedPointer+1)),c
	setf	((c:_ProgrammedPointer+2)),c
	setf	((c:_ProgrammedPointer+3)),c
	line	244
	
l2329:
;boot_18fxxjxx.c: 244: BufferedDataIndex = 0;
	clrf	((c:_BufferedDataIndex)),c
	line	245
	
l606:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_UserInit
	__end_of_UserInit:
	signat	_UserInit,88
	global	_HIDInitEP

;; *************** function _HIDInitEP *****************
;; Defined at:
;;		line 171 in file "../src/usb_device_hid.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : F/D
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBCBInitEP
;; This function uses a non-reentrant model
;;
psect	text36,class=CODE,space=0,reloc=2
	file	"../src/usb_device_hid.c"
	line	171
global __ptext36
__ptext36:
psect	text36
	file	"../src/usb_device_hid.c"
	line	171
	global	__size_of_HIDInitEP
	__size_of_HIDInitEP	equ	__end_of_HIDInitEP-_HIDInitEP
	
_HIDInitEP:
;incstack = 0
	opt	stack 26
	line	173
	
l2331:
;usb_device_hid.c: 173: hid_rpt_rx_len =0;
	clrf	((c:_hid_rpt_rx_len)),c
	line	175
	
l2333:
;usb_device_hid.c: 175: UEP1 = 0x0E|0x10;
	movlw	low(01Eh)
	movlb	15	; () banked
	movwf	((3879))&0ffh	;volatile
	line	178
;usb_device_hid.c: 178: ep1Bo.Cnt = sizeof(hid_report_out);
	movlw	low(040h)
	movlb	13	; () banked
	movwf	(0+(3340+01h))&0ffh	;volatile
	line	179
	
l2335:; BSR set to: 13

;usb_device_hid.c: 179: ep1Bo.ADR = (uint8_t*)&hid_report_out;
		movlw	low(3372)
	movwf	(0+(3340+02h))&0ffh	;volatile
	movlw	high(3372)
	movwf	(1+(3340+02h))&0ffh	;volatile

	line	180
	
l2337:; BSR set to: 13

;usb_device_hid.c: 180: ep1Bo.Stat._byte = 0x00|0x08;
	movlw	low(08h)
	movwf	((3340))&0ffh	;volatile
	line	181
	
l2339:; BSR set to: 13

;usb_device_hid.c: 181: ep1Bo.Stat._byte |= 0x80;
	bsf	(0+(7/8)+(3340))&0ffh,(7)&7	;volatile
	line	194
	
l2341:; BSR set to: 13

;usb_device_hid.c: 194: ep1Bi.ADR = (uint8_t*)&hid_report_in;
		movlw	low(3436)
	movwf	(0+(3344+02h))&0ffh	;volatile
	movlw	high(3436)
	movwf	(1+(3344+02h))&0ffh	;volatile

	line	195
	
l2343:; BSR set to: 13

;usb_device_hid.c: 195: ep1Bi.Stat._byte = 0x00|0x40;
	movlw	low(040h)
	movwf	((3344))&0ffh	;volatile
	line	197
	
l522:; BSR set to: 13

	return	;funcret
	opt stack 0
GLOBAL	__end_of_HIDInitEP
	__end_of_HIDInitEP:
	signat	_HIDInitEP,88
	global	_LoadBDTandSetUOWN

;; *************** function _LoadBDTandSetUOWN *****************
;; Defined at:
;;		line 1583 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;  BDTIndexToLo    1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  BDTIndexToLo    1    0[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/D
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBProtocolResetHandler
;;		_USBCtrlEPServiceComplete
;; This function uses a non-reentrant model
;;
psect	text37,class=CODE,space=0,reloc=2
	file	"../src/usb_device.c"
	line	1583
global __ptext37
__ptext37:
psect	text37
	file	"../src/usb_device.c"
	line	1583
	global	__size_of_LoadBDTandSetUOWN
	__size_of_LoadBDTandSetUOWN	equ	__end_of_LoadBDTandSetUOWN-_LoadBDTandSetUOWN
	
_LoadBDTandSetUOWN:; BSR set to: 13

;incstack = 0
	opt	stack 27
;LoadBDTandSetUOWN@BDTIndexToLoad stored from wreg
	movwf	((c:LoadBDTandSetUOWN@BDTIndexToLoad)),c
	line	1591
	
l2361:
;usb_device.c: 1585: static volatile BDT* pBDTEntry;
;usb_device.c: 1591: TempBDT.Cnt = 8;
	movlw	low(08h)
	movwf	(0+((c:_TempBDT)+01h)),c
	line	1592
;usb_device.c: 1592: TempBDT.ADR = (uint8_t*)&EP0OutOddBuf[0];
		movlw	low(3356)
	movwf	(0+((c:_TempBDT)+02h)),c
	movlw	high(3356)
	movwf	(1+((c:_TempBDT)+02h)),c

	line	1593
	
l2363:
;usb_device.c: 1593: if(BDTIndexToLoad == 0)
	movf	((c:LoadBDTandSetUOWN@BDTIndexToLoad)),c,w
	btfss	status,2
	goto	u1161
	goto	u1160
u1161:
	goto	l2367
u1160:
	line	1595
	
l2365:
;usb_device.c: 1594: {
;usb_device.c: 1595: TempBDT.ADR = (uint8_t*)&EP0OutEvenBuf[0];
		movlw	low(3348)
	movwf	(0+((c:_TempBDT)+02h)),c
	movlw	high(3348)
	movwf	(1+((c:_TempBDT)+02h)),c

	line	1596
;usb_device.c: 1596: pBDTEntry = (volatile BDT*)0xD00;
		movlw	low(0D00h)
	movwf	((c:LoadBDTandSetUOWN@pBDTEntry)),c
	movlw	high(0D00h)
	movwf	((c:LoadBDTandSetUOWN@pBDTEntry+1)),c

	line	1597
;usb_device.c: 1597: }
	goto	l2369
	line	1600
	
l2367:
;usb_device.c: 1598: else
;usb_device.c: 1599: {
;usb_device.c: 1600: pBDTEntry = (volatile BDT*)(0xD00 + 4);
		movlw	low(0D04h)
	movwf	((c:LoadBDTandSetUOWN@pBDTEntry)),c
	movlw	high(0D04h)
	movwf	((c:LoadBDTandSetUOWN@pBDTEntry+1)),c

	line	1604
	
l2369:
;usb_device.c: 1601: }
;usb_device.c: 1604: *pBDTEntry = TempBDT;
	movff	(c:LoadBDTandSetUOWN@pBDTEntry),fsr2l
	movff	(c:LoadBDTandSetUOWN@pBDTEntry+1),fsr2h
	movff	(c:_TempBDT),postinc2
	movff	(c:_TempBDT+1),postinc2
	movff	(c:_TempBDT+2),postinc2
	movff	(c:_TempBDT+3),postinc2

	line	1607
	
l2371:
;usb_device.c: 1607: pBDTEntry->Stat.UOWN = 1;
	movff	(c:LoadBDTandSetUOWN@pBDTEntry),fsr2l
	movff	(c:LoadBDTandSetUOWN@pBDTEntry+1),fsr2h
	bsf	c:indf2,7
	line	1608
	
l443:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_LoadBDTandSetUOWN
	__end_of_LoadBDTandSetUOWN:
	signat	_LoadBDTandSetUOWN,4216
	global	_USBDisableWithLongDelay

;; *************** function _USBDisableWithLongDelay *****************
;; Defined at:
;;		line 1615 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_DelayRoutine
;; This function is called by:
;;		_USBDeviceInit
;;		_USBSoftAttach
;;		_ResetDeviceCleanly
;; This function uses a non-reentrant model
;;
psect	text38,class=CODE,space=0,reloc=2
	line	1615
global __ptext38
__ptext38:
psect	text38
	file	"../src/usb_device.c"
	line	1615
	global	__size_of_USBDisableWithLongDelay
	__size_of_USBDisableWithLongDelay	equ	__end_of_USBDisableWithLongDelay-_USBDisableWithLongDelay
	
_USBDisableWithLongDelay:
;incstack = 0
	opt	stack 24
	line	1617
	
l2455:
;usb_device.c: 1617: UCONbits.SUSPND = 0;
	bcf	((c:3941)),c,1	;volatile
	line	1618
;usb_device.c: 1618: UCON = 0x00;
	clrf	((c:3941)),c	;volatile
	line	1619
	
l2457:
;usb_device.c: 1619: DelayRoutine(0xFFFF);
	movlw	high(0FFFFh)
	movwf	((c:DelayRoutine@DelayAmount+1)),c
	setf	((c:DelayRoutine@DelayAmount)),c
	call	_DelayRoutine	;wreg free
	line	1620
	
l2459:
;usb_device.c: 1620: usb_device_state = 0;
	clrf	((c:_usb_device_state)),c
	line	1621
	
l446:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_USBDisableWithLongDelay
	__end_of_USBDisableWithLongDelay:
	signat	_USBDisableWithLongDelay,88
	global	_DelayRoutine

;; *************** function _DelayRoutine *****************
;; Defined at:
;;		line 1625 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;  DelayAmount     2    0[COMRAM] unsigned int 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_ClearWatchdog
;; This function is called by:
;;		_InitializeSystem
;;		_USBCBWakeFromSuspend
;;		_USBDisableWithLongDelay
;; This function uses a non-reentrant model
;;
psect	text39,class=CODE,space=0,reloc=2
	line	1625
global __ptext39
__ptext39:
psect	text39
	file	"../src/usb_device.c"
	line	1625
	global	__size_of_DelayRoutine
	__size_of_DelayRoutine	equ	__end_of_DelayRoutine-_DelayRoutine
	
_DelayRoutine:
;incstack = 0
	opt	stack 25
	line	1627
	
l2347:
;usb_device.c: 1627: while(DelayAmount)
	goto	l2353
	line	1629
	
l2349:
;usb_device.c: 1628: {
;usb_device.c: 1629: ClearWatchdog();
	call	_ClearWatchdog	;wreg free
	line	1630
	
l2351:
;usb_device.c: 1630: DelayAmount--;
	decf	((c:DelayRoutine@DelayAmount)),c
	btfss	status,0
	decf	((c:DelayRoutine@DelayAmount+1)),c
	line	1627
	
l2353:
	movf	((c:DelayRoutine@DelayAmount)),c,w
iorwf	((c:DelayRoutine@DelayAmount+1)),c,w
	btfss	status,2
	goto	u1141
	goto	u1140

u1141:
	goto	l2349
u1140:
	line	1632
	
l452:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_DelayRoutine
	__end_of_DelayRoutine:
	signat	_DelayRoutine,4216
	global	_ClearWatchdog

;; *************** function _ClearWatchdog *****************
;; Defined at:
;;		line 1642 in file "../src/usb_device.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_USBProtocolResetHandler
;;		_DelayRoutine
;;		_ProcessIO
;;		_SignFlash
;; This function uses a non-reentrant model
;;
psect	text40,class=CODE,space=0,reloc=2
	line	1642
global __ptext40
__ptext40:
psect	text40
	file	"../src/usb_device.c"
	line	1642
	global	__size_of_ClearWatchdog
	__size_of_ClearWatchdog	equ	__end_of_ClearWatchdog-_ClearWatchdog
	
_ClearWatchdog:
;incstack = 0
	opt	stack 25
	line	1644
	
l2345:
# 1644 "../src/usb_device.c"
clrwdt ;# 
psect	text40
	line	1645
	
l455:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_ClearWatchdog
	__end_of_ClearWatchdog:
	signat	_ClearWatchdog,88
	global	_BlinkUSBStatus

;; *************** function _BlinkUSBStatus *****************
;; Defined at:
;;		line 611 in file "../src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/F
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_BootMain
;; This function uses a non-reentrant model
;;
psect	text41,class=CODE,space=0,reloc=2
	file	"../src/main.c"
	line	611
global __ptext41
__ptext41:
psect	text41
	file	"../src/main.c"
	line	611
	global	__size_of_BlinkUSBStatus
	__size_of_BlinkUSBStatus	equ	__end_of_BlinkUSBStatus-_BlinkUSBStatus
	
_BlinkUSBStatus:
;incstack = 0
	opt	stack 29
	line	616
	
l2109:
;main.c: 614: static unsigned int led_count = 0;
;main.c: 616: led_count--;
	decf	((c:BlinkUSBStatus@led_count)),c
	btfss	status,0
	decf	((c:BlinkUSBStatus@led_count+1)),c
	line	617
	
l2111:
;main.c: 617: if(led_count == 0)
	movf	((c:BlinkUSBStatus@led_count)),c,w
iorwf	((c:BlinkUSBStatus@led_count+1)),c,w
	btfss	status,2
	goto	u921
	goto	u920

u921:
	goto	l81
u920:
	line	619
	
l2113:
;main.c: 618: {
;main.c: 619: led_count = 0x4E00;
	movlw	high(04E00h)
	movwf	((c:BlinkUSBStatus@led_count+1)),c
	movlw	low(04E00h)
	movwf	((c:BlinkUSBStatus@led_count)),c
	line	620
	
l2115:
;main.c: 620: if(usb_device_state < 6)
		movlw	06h-0
	cpfslt	((c:_usb_device_state)),c
	goto	u931
	goto	u930

u931:
	goto	l2119
u930:
	line	622
	
l2117:
;main.c: 621: {
;main.c: 622: LATCbits.LATC2 = 1;
	bsf	((c:3979)),c,2	;volatile
	line	623
;main.c: 623: }
	goto	l81
	line	626
	
l2119:
;main.c: 624: else
;main.c: 625: {
;main.c: 626: LATCbits.LATC2 = !LATCbits.LATC2;
	btfss	((c:3979)),c,2	;volatile
	goto	u941
	goto	u940
u941:
	clrf	(??_BlinkUSBStatus+0+0)&0ffh,c
	incf	(??_BlinkUSBStatus+0+0)&0ffh,c
	goto	u958
u940:
	clrf	(??_BlinkUSBStatus+0+0)&0ffh,c
u958:
	rlncf	(??_BlinkUSBStatus+0+0),c
	rlncf	(??_BlinkUSBStatus+0+0),c
	movf	((c:3979)),c,w	;volatile
	xorwf	(??_BlinkUSBStatus+0+0),c,w
	andlw	not (((1<<1)-1)<<2)
	xorwf	(??_BlinkUSBStatus+0+0),c,w
	movwf	((c:3979)),c	;volatile
	line	630
	
l81:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_BlinkUSBStatus
	__end_of_BlinkUSBStatus:
	signat	_BlinkUSBStatus,88
psect	smallconst
	db 0	; dummy byte at the end
	global	__smallconst
	global	__mediumconst
	GLOBAL	__activetblptr
__activetblptr	EQU	3
	psect	intsave_regs,class=BIGRAM,space=1,noexec
	PSECT	rparam,class=COMRAM,space=1,noexec
	GLOBAL	__Lrparam
	FNCONF	rparam,??,?
	GLOBAL	___rparam_used
	___rparam_used EQU 1
	GLOBAL	___param_bank
	___param_bank EQU 16
GLOBAL	__Lparam, __Hparam
GLOBAL	__Lrparam, __Hrparam
__Lparam	EQU	__Lrparam
__Hparam	EQU	__Hrparam
	end
