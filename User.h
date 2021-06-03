#ifndef USER_H
#define	USER_H

typedef struct tagUser_Data_struct {	
	
	unsigned int ID_G5;
	unsigned int InterFace;                 // 	
 	union
	{					
		struct                              //0x01 H:Voltage states L:Current states 0x03=正  0x13=負
		{	
			unsigned Current_Point	:4;		//電流後小數點 
			unsigned Current_statue	:4;		//
			unsigned Voltage_Point	:4;		//電壓後小數點
			unsigned Voltage_statue	:4;		//		
		};		
	};
	unsigned int Voltage_G5;							//0x02  電壓	0.000~50.000V or 50.00~400.00V
	unsigned int Current_G5;							//0x03  電流	0.000~50.000A or 50.00~655.35A
	unsigned int Residual_Electricity;              //0x04  剩下電量0.0~6553.5Ah
    unsigned int Nominal_Battery_Capacity;          //0x05  標準電池容量 0.0~6553.5AH
    unsigned int Battery_Power;						//0x06  百分比或剩餘電量0.00~100.00%
    unsigned int Temperature1;						//0x07  溫度1	-55.0~125.0
    
	unsigned int Battery_ID;						//0x08  讀取Battery_ID(機台號碼 客戶可以自行設定)
	unsigned int Car_Statue;                        //0x09  讀取車子狀態
	unsigned int Month;								//0x000A  讀取使用月份
	unsigned int Day;                               //0x0B  讀取使用日期			
	unsigned int Hour;                              //0x0C  讀取使用小時	
	unsigned int minute;                            //0x0D  讀取使用分鐘			
	unsigned int Now_Total_Capacity;				//0x0E  讀取電池老化後，電池所剩餘的殘餘滿額容量				
	unsigned int Fake_Voltage;						//0x0F  讀取假電壓
    unsigned int x2;                        		//0x10  讀取reset電壓點
    
    //18個2byte
    
    unsigned int 	ID_Ele_load;					//編號 //0x01
    unsigned int 	Buzzing;        		//放電結束 //0x00=蜂鳴器沒有在叫 0x01=蜂鳴器在叫 //0x00 0x01 //前面是有沒有叫 後面是叫的音樂
    unsigned int 	BaudRate;				//BaudRate  //0x25 0x80
    unsigned int    ID_decide;				//可決定id //0x00 0x01
    unsigned int 	Voltage_Ele_load;				//電壓 // Voltage/100=實際電壓
    union
	{			
		struct   //前面8個是型號與現在狀態 後面八個是容量的高位元
		{	
            unsigned Capacity_H         :8;     //容量高位元
            unsigned DisCharge          :1;     //1=是放電狀態；0=是停止狀態
            unsigned End            	:1;		//1=是表示已經結束，0=是尚未開始或者尚未結束
            unsigned OverTemperature	:1;		//1=是過溫保護暫停狀態，0=是正常狀態
            unsigned twoZero            :2;		//兩個0
            unsigned type               :3;		//型號 001
		};		
	};
    unsigned int 	Capacity_L;				//容量低位元
    unsigned int 	Temperature;			//溫度 // Temperature/10=實際溫度
    unsigned int 	StopVoltage;            //截止電壓 // StopVoltage/100=實際截止電壓
    unsigned int 	DisChargeCurrent;       //放電電流 // DisChargeCurrent /10=實際放電電流
    unsigned int    Watt;                   //功率 
	
    //29個2byte
    
    unsigned char 	CRC_L;
    unsigned char 	CRC_H;
    

	unsigned char Index;						//要收資料
    unsigned char RTIndex;					//已收資料 
	
}User_Data_struct_define;
extern User_Data_struct_define User_Data; 

#endif

