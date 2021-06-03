#ifndef G5_define_H
#define G5_define_H

typedef struct tagG5_Data_struct {	
	
	unsigned int ID;
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
	unsigned int Voltage;							//0x02  電壓	0.000~50.000V or 50.00~400.00V
	unsigned int Current;							//0x03  電流	0.000~50.000A or 50.00~655.35A
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
	struct
	{
		unsigned  			 	IF1 :1;             //資料傳送完成
		unsigned  			 	IF2 :1;             //資料接收完成
		unsigned  			 	IF3 :1;             //資料接收或傳送錯誤
	};		
	
}G5_Data_struct_define;
extern G5_Data_struct_define G5_Data; 

typedef struct tagG5_Sent_Data_struct {	
  unsigned char 	ID;						//編號
  unsigned char 	Fuc;					//功能
	union
	{
		struct
		{
			unsigned char 	Reg_H;          //因為傳輸時候是先傳輸高位元之後再傳輸低位元
		  unsigned char 	Reg_L;          //可是PIC是先從低位元開始擺放，所以會有高低位元交換的問題
		};									//故REG會是整個高低位元顛倒的情況，故之後有個重新整理的運算
       	struct
		{
			unsigned char 	Chx;
		  unsigned char 	Regest; 
		};	
    };	  
	union
	{
        struct
		{
		  unsigned char 	Data_H;
			unsigned char 	Data_L;
			unsigned char 	CRC_L;
			unsigned char 	CRC_H;
		};
	};
												
 	union
	{
        unsigned                            IF:3;
		struct
		{		
            unsigned                        W_R:2;
			unsigned						TIF:1;	
            unsigned                    	RIF :1;		//資料接收完成
            unsigned                       	ERRIF:1;	//資料接收或傳送錯誤
		};
	};
	unsigned char Index;						//要收資料
  unsigned char RTIndex;					//已收資料 
}G5_Sent_Data_struct_define;
extern G5_Sent_Data_struct_define G5_Sent; 

typedef struct tagG5_Get_Data_struct {	
  unsigned char 	ID;						//編號
  unsigned char 	Fuc;					//功能
	union
	{
		struct
		{
			unsigned char 	Reg_H;	//因為傳輸時候是先傳輸高位元之後再傳輸低位元
		  unsigned char 	Reg_L;  //可是PIC是先從低位元開始擺放，所以會有高低位元交換的問題
		};												//故REG會是整個高低位元顛倒的情況，故之後有個重新整理的運算
       	struct
		{
			unsigned char 	Chx;
		  unsigned char 	Regest; 
		};	
    };	  
	union
	{
        struct
		{
		  unsigned char 	Data_H;
			unsigned char 	Data_L;
			unsigned char 	CRC_L;
			unsigned char 	CRC_H;
		};
		struct
		{
			unsigned char 	Quantity_H;
		  unsigned char 	Quantity_L;  
		  unsigned char 	Total_Byte;		  
		};
        unsigned int DATA[30];	
		unsigned int Quantity;	
	};
    union
    {		 
		unsigned int Value;
		struct
		{
		  unsigned char 	Value_L;  
			unsigned char 	Value_H;	  
		};		
	};
												
 	union
	{
        unsigned                            IF:3;
		struct
		{		
            unsigned                        W_R:2;
			unsigned						TIF:1;	
            unsigned                    	RIF :1;		//資料接收完成
            unsigned                       	ERRIF:1;	//資料接收或傳送錯誤
		};
	};
	unsigned char Index;						//要收資料
  unsigned char RTIndex;					//已收資料 
}G5_Get_Data_struct_define;
extern G5_Get_Data_struct_define G5_Get;

#endif
