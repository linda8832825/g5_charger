#ifndef Ele_load_Define_H
#define Ele_load_Define_H


typedef struct tagEle_load_Data {	
    unsigned int 	ID;						//編號 //0x01
    unsigned int 	Buzzing;        		//放電結束 //0x00=蜂鳴器沒有在叫 0x01=蜂鳴器在叫 //0x00 0x01 //前面是有沒有叫 後面是叫的音樂
    unsigned int 	BaudRate;				//BaudRate  //0x25 0x80
    unsigned int    ID_decide;				//可決定id //0x00 0x01
    unsigned int 	Voltage;				//電壓 // Voltage/100=實際電壓
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
    
    unsigned    DisChargeDone:1;                    //放電完畢
    unsigned    GoTo_Write_Ele_load:1;              //是不是要去寫入電子附載機
    unsigned    Init:2;                             //設定電子附載機的值是不是好了 0=一開始還不用設定時 1=正在設定or設定失敗 2=設定成功 
  	
    
 	union
	{
		unsigned						IF:1;
		struct
		{
            unsigned                WriteIF:1;  //寫入電子附載機的完成 //0=未完成 1=完成
			unsigned  			 	TIF :1;		//資料傳送完成
			unsigned  			 	RIF :1;		//資料接收完成
			unsigned  			 	ERRIF:1;	//資料接收或傳送錯誤				
		};
	};
	
  unsigned char Index;						//要收資料
  unsigned char RTIndex;					//已收資料
}Ele_load_Data_define;
extern Ele_load_Data_define Ele_load_Data; 

typedef struct tagEle_load_Sent_Data_struct {	
  unsigned char 	ID;						//編號
  unsigned char 	Fuc;					//功能 //0x01 0x04 0x05 0x06
	union
	{
		struct
		{
			unsigned char 	Reg_H;          //開始位置
		  unsigned char 	Reg_L;          
		};									
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
		  unsigned char 	Data_H;         //個數
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
}Ele_load_Sent_Data_struct_define;
extern Ele_load_Sent_Data_struct_define Ele_load_Sent;

typedef struct tagEle_load_Get_Data_struct {	
  unsigned char 	ID;						//編號
  unsigned char 	Fuc;					//功能 //0x01 0x04 0x05 0x06
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
            unsigned                        SORT:1;     //1=資料接收完可以排列了
            unsigned                       	ERRIF:1;	//資料接收或傳送錯誤
		};
	};
	unsigned char Index;						//要收資料
  unsigned char RTIndex;					//已收資料 
}Ele_load_Get_Data_struct_define;
extern Ele_load_Get_Data_struct_define Ele_load_Get;

#endif
