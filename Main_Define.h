#ifndef MAIN_define_H
#define MAIN_define_H


//T4CON 目前用在 計時用
//T1CON 目前用在 庫倫計的接收資料整理
//T2CON 用在電子附載機的資料整理
//T3CON G5的接收資料整理


#include "p24FJ128GA106.h"

#include "Ele_load_Define.h"

#include "G5_define.h"

#include "I2C_LCD.h"

#include "Coulomb.h"

#include "User.h"

#include "stdio.h"

typedef struct tedIC_Data_Struct{
    struct{
        unsigned 	char 	Second;	
        unsigned 	int 	ms;	
        unsigned    int     Thirty_Second_Count;
        unsigned    int     Regual_Read_G5;
    }time;
    unsigned    DoIamStarted       : 1; //有無被按下啟動鈕
    unsigned    GetTheWhatYouWant  : 1; //有無拿到正確資料
    unsigned    WriteZeroAh        : 1; //有時寫入0.1安時數成功
}IC_Data_Define;
extern IC_Data_Define IC_Data;


typedef struct tedI2C_Data_Struct{
        struct
		{
            unsigned        R_W :1; //讀或寫
            unsigned  		TIF :1;//資料傳送完成
		};
    
}I2C_Data_Define;
extern I2C_Data_Define I2C_Data;

extern  unsigned char I2C_Buffer;

#define BR_9600                     415
#define BR_115200                   34

#define Write                       1
#define Read                        2

#define I2C_write                   0
#define I2C_read                    1

#define Discharge_Voltage           0x0226 //55.0v 知道放電完的點
#define Charge_Voltage              0x0253 //59.5v 知道充電完的點
#define Charge_Stop_Current         0x0A //1.0A 知道充電完的點

#define My_ID                       0x01
#define DriverIC_I2C_LCD_Addr       0x4E //LCD的ID
#define Ele_load_ID                 0x01 //電子附載機的ID
#define Coulomb_ID                  0x01 //庫倫計id

#define BuzzMusicType               0x02   //蜂鳴器響的時候的音樂
#define DISCHARGECURRENT            0x0064   //10A放電
#define STOPVILTAGE                 0x0FA0 //40V截止


#define YES                         1//有被按下啟動鈕
#define NO                          0//無被按下啟動鈕

#define Charge              1//充電器開始充電
#define StopCharge          0

#define Turn_ON 			0
#define Turn_OFF 			1

#define SW_Push 			0
#define SW_NoPush 			1

#define Output 				0
#define Input 				1

#define BUZZ_ON 			1  // 1
#define BUZZ_OFF 			0  // 0


#define WriteError              LATEbits.LATE2  //黃 寫值進G5四次都失敗
#define BatteryError            LATEbits.LATE3  //紅 g5充電4次也救不起來的錯誤
#define POWER                   LATEbits.LATE4  //充電器的開與關
#define LED         			LATEbits.LATE5  //藍 狀態led，每次讀G5資料對反轉狀態
#define SW       				PORTEbits.RE6   //啟動鈕
#define BUZZ     				LATEbits.LATE7  //開機叫一聲


#define TRISE_WriteError        TRISEbits.TRISE2
#define TRISE_BatteryError      TRISEbits.TRISE3 
#define TRISE_POWER             TRISEbits.TRISE4 
#define TRISE_LED               TRISEbits.TRISE5 //1為輸入 0為輸出
#define TRISE_SW      			TRISEbits.TRISE6	
#define TRISE_BUZZ              TRISEbits.TRISE7


#define TRISE_U1RX		 		TRISFbits.TRISF2
#define TRISE_U1TX		 		TRISFbits.TRISF3

#define TRISx_SCL		 		TRISGbits.TRISG2
#define TRISx_SDA		 		TRISGbits.TRISG3

#define LATx_SCL		 		LATGbits.LATG2
#define LATx_SDA		 		LATGbits.LATG3

#define led_Toggle()            LED = ~LED;
  

void Initial_IO(void);
void Initial_Clock(void); 
void Initial_Variable(void); //變數的初始化
void Initial_Coulomb_UART(void);
void Initial_Ele_load_UART(void);
void Initial_G5_UART(void);
void Initial_User_UART(void);
void Initial_Timer1(void);
void Initial_I2C(void);	


unsigned int CRC_Check(unsigned char* crc_address, unsigned char crc_length);
unsigned int CRC_Make(unsigned char *Buffer , unsigned char Quantity);
void delay(unsigned char i);
void delayms(unsigned int i);
unsigned char delayThirtySecond(void);


void Read_ALL_G5_Data(void);
void Write_G5_Data(unsigned int Regest,unsigned int Data);


void Set_Ele_load(void);
void ReadEleLoadState(void);
void ReadAllEleLoadData(void);
void WriteEleLoadState(unsigned char math_c, unsigned char math_d);
void WriteEleLoadSetting(unsigned char math_c, unsigned char math_d, unsigned char math_e);


void Unlock_Coulomb(void);
void Write_Coulomb_Data(unsigned int Regest,unsigned int Data);
void Read_ALL_Coulomb_Data(void);
unsigned int Prevention_Zero_Ah(void);


void SortUserData(void);


#endif
