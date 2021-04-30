#ifndef Ele_load_Define_H
#define Ele_load_Define_H


typedef struct tagEle_load_Data {	
    unsigned char 	ID;						//編號 //0xAA
    unsigned char 	Fuc;					//關鍵字 //46
    unsigned char 	CurrentMin;				//電流最小值 
    unsigned char 	CurrentMax;				//電流最大值 
    unsigned char 	Current;				//電流 //轉10進制後-17
    unsigned char 	Voltage;				//電壓 //轉10進制後-512
    unsigned char 	StopVoltage;			//斷電電壓 
    unsigned char 	Capacity;				//容量 
    unsigned char 	Temperature;			//溫度
    unsigned char 	StopFuc;                //啟停命令
    unsigned char 	End;                    //尾碼
  									
 	union
	{
		unsigned						IF:1;
		struct
		{
			unsigned  			 	TIF :1;		//資料傳送完成
			unsigned  			 	RIF :1;		//資料接收完成
			unsigned  			 	ERRIF:1;	//資料接收或傳送錯誤				
		};
	};
	
  unsigned char Index;						//要收資料
  unsigned char RTIndex;					//已收資料
}Ele_load_Data_define;

extern Ele_load_Data_define Ele_load_Data; 


#endif
