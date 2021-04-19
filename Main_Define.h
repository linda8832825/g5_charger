#ifndef MAIN_define_H
#define MAIN_define_H


//T1CON �ثe�Φb �p�ɥ�
//T2CON �ثe�Φb �w�ۭp��������ƭp�ɾ�


#include "p24FJ128GA106.h"

//#include "./Coulomb/Coulomb_define.h"
//
//#include "./I2C/I2C_define.h"
////
//#include "./I2C/I2C_LCD.h"
//
#include "G5_define.h"


#define BR_115200 			34

#define Write 				1
#define Read 				2

#define Discharge_Voltage   0x01A4 //42.0v
#define Charge_Voltage      0x0253 //59.5v

#define My_ID               0x01

#define read_G5_times_limt 5

#define LED_ON 				0
#define LED_OFF 			1

#define SW_Push 			0
#define SW_NoPush 			1

#define Output 				0
#define Input 				1

#define BUZZ_ON 			1  // 1
#define BUZZ_OFF 			0  // 0


#define Flick_Fast 			2000  //�V�p�V��
#define Flick_Middle 		5000
#define Flick_Slow 			8000
#define Brightness_Hz 		100
#define Flick_Freq 			Flick_Slow 


#define LED         			LATEbits.LATE5
#define SW       				PORTEbits.RE6   //Ū���{�b���A
#define BUZZ     				LATEbits.LATE7


#define TRISE_LED               TRISEbits.TRISE5 //1����J 0����X
#define TRISE_SW      			TRISEbits.TRISE6	
#define TRISE_BUZZ              TRISEbits.TRISE7


#define TRISE_U1RX		 		TRISFbits.TRISF2
#define TRISE_U1TX		 		TRISFbits.TRISF3

#define TRISx_SCL		 		TRISGbits.TRISG2
#define TRISx_SDA		 		TRISGbits.TRISG3

#define LATx_SCL		 		LATGbits.LATG2
#define LATx_SDA		 		LATGbits.LATG3

#define led_Toggle()             do { LATEbits.LATE5 = ~LATEbits.LATE5; } while(0)


void Initial_Clock(void); 
void Initial_IO(void);
void Initial_Coulomb_UART(void);
void Initial_G5_UART(void);
void Timer1_initial(void);
void Initial_UART2(void);
void I2C_Initial(void);	
void master_init(void);
void G5_reset_work(void);
void Read_ALL_G5_Data(void);
void Write_G5_Data(unsigned int Regest,unsigned int Data);
unsigned int G5_CRC_Check(void);
unsigned int CRC_Make(unsigned char *Buffer , unsigned char Quantity);
void wait(unsigned int i);
#endif
