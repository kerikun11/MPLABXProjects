/*******************************************************************************
*  LCD2 - �h�Q�b�ڑ����^�k�b�c���W���[���̃T���v���\�[�X�v���O����             *
*                                                                              *
*  ����:�@�h�Q�b�M�����̃v���A�b�v��R�͂o�h�b�������g���Ă��܂��B             *
*                                                                              *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2013-07-25  ���ޒ��H�[(���ނ���)  Create                            *
* ============================================================================ *
*  PIC 16F1827 (SSP1���g�p���Ă��܂�)                                          *
*  MPLAB IDE(V8.84)                                                            *
*  MPLAB(R) XC8 C Compiler Version 1.00                                        *
*******************************************************************************/
#include <xc.h>
#include "skI2Clib.h"
#include "skI2CLCDlib.h"
// 5x7�h�b�g�̃L�����N�^�ł��A1�ŕ\���@0�ŏ���
char heart[7] = {
  0b01010,
  0b11011,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
} ;
// �R���t�B�M�����[�V�����P�̐ݒ�
// CLKOUT��݂�RA6��݂Ŏg�p����(CLKOUTEN_OFF)�F�����ۯ����g�p����(FOSC_INTOSC)
// �O���ۯ��Ď����Ȃ�(FCMEN_OFF)�F�O���E�����ۯ��̐ؑւ��ł̋N���͂Ȃ�(IESO_OFF)
// �d���d���~���펞�Ď��@�\ON(BOREN_ON)�F�d��ON����64ms�����۸��т��J�n����(PWRTEN_ON)
// �����ޯ����ϰ����(WDTE_OFF)�F
// �O��ؾ�ĐM���͎g�p�������޼��ٓ���(RA5)��݂Ƃ���(MCLRE_OFF)
// ��۸�����ذ��ی삵�Ȃ�(CP_OFF)�F�ް���ذ��ی삵�Ȃ�(CPD_OFF)
__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF) ;
// �R���t�B�M�����[�V�����Q�̐ݒ�
// ����N���b�N��32MHz�ł͓��삳���Ȃ�(PLLEN_OFF)
// �X�^�b�N���I�[�o�t���[��A���_�[�t���[�����烊�Z�b�g������(STVREN_ON)
// ��d���v���O���~���O�@�\�g�p���Ȃ�(LVP_OFF)
// Flash��ذ��ی삵�Ȃ�(WRT_OFF)�F�d���d���~���펞�Ď��d��(2.5V)�ݒ�(BORV_HI)
__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF) ;
/*******************************************************************************
*  InterFunction()   ���荞�݂̏���                                            *
*******************************************************************************/
void interrupt InterFunction( void )
{
     // �h�Q�b�֘A�̊��荞�ݏ���
     InterI2C() ;
}
/*******************************************************************************
*  ���C���̏���                                                                *
*******************************************************************************/
void main()
{
     OSCCON     = 0b01110010 ; // �����N���b�N�͂W�l�g���Ƃ���
     OPTION_REG = 0b00000000 ; // �f�W�^��I/O�ɓ����v���A�b�v��R���g�p����
     ANSELA     = 0b00000000 ; // AN0-AN4�͎g�p���Ȃ��S�ăf�W�^��I/O�Ƃ���
     ANSELB     = 0b00000000 ; // AN5-AN11�͎g�p���Ȃ��S�ăf�W�^��I/O�Ƃ���
     TRISA      = 0b00000000 ; // �s��(RA)�͑S�ďo�͂Ɋ����Ă�(RA5�͓��݂͂̂ƂȂ�)
     TRISB      = 0b00010010 ; // �s��(RB)��RB4(SCL1)/RB1(SDA1)�̂ݓ���
     WPUB       = 0b00010010 ; // RB1/4�͓����v���A�b�v��R���w�肷��
     PORTA      = 0b00000000 ; // RA�o�̓s���̏�����(�S��LOW�ɂ���)
     PORTB      = 0b00000000 ; // RB�o�̓s���̏�����(�S��LOW�ɂ���)

     // �k�b�c���W���[���̏���������
     LCD_Init() ;

     LCD_CreateChar(0x00,heart) ;   // 1�ԂɃI���W�i���L�����N�^��o�^����

     LCD_SetCursor(0,0) ;        // �\���ʒu��ݒ肷��
     LCD_Puts("Hello") ;
     //LCD_Putc(0x00) ;            // 1�Ԃɓo�^�����L������\������
     LCD_SetCursor(2,1) ;        // �\���ʒu��ݒ肷��
     LCD_Puts("World!") ;

     while(1) {
     }

}