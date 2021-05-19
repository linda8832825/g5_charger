#ifndef Ele_load_Define_H
#define Ele_load_Define_H


typedef struct tagEle_load_Data {	
    unsigned int 	ID;						//�s�� //0x01
    unsigned int 	Buzzing;        		//��q���� //0x00=���ﾹ�S���b�s 0x01=���ﾹ�b�s //0x00 0x01 //�e���O���S���s �᭱�O�s������
    unsigned int 	BaudRate;				//BaudRate  //0x25 0x80
    unsigned int    ID_decide;				//�i�M�wid //0x00 0x01
    unsigned int 	Voltage;				//�q�� // Voltage/100=��ڹq��
    union
	{			
		struct   //�e��8�ӬO�����P�{�b���A �᭱�K�ӬO�e�q�����줸
		{	
            unsigned Capacity_H         :8;     //�e�q���줸
            unsigned DisCharge          :1;     //1=�O��q���A�F0=�O����A
            unsigned End            	:1;		//1=�O��ܤw�g�����A0=�O�|���}�l�Ϊ̩|������
            unsigned OverTemperature	:1;		//1=�O�L�ūO�@�Ȱ����A�A0=�O���`���A
            unsigned twoZero            :2;		//���0
            unsigned type               :3;		//���� 001
		};		
	};
    unsigned int 	Capacity_L;				//�e�q�C�줸
    unsigned int 	Temperature;			//�ū� // Temperature/10=��ڷū�
    unsigned int 	StopVoltage;            //�I��q�� // StopVoltage/100=��ںI��q��
    unsigned int 	DisChargeCurrent;       //��q�q�y // DisChargeCurrent /10=��ک�q�q�y
    unsigned int    Watt;                   //�\�v 
    
    unsigned    DisChargeDone:1;                    //��q����
    unsigned    GoTo_Write_Ele_load:1;              //�O���O�n�h�g�J�q�l������
    unsigned    Init:2;                             //�]�w�q�l���������ȬO���O�n�F 0=�@�}�l�٤��γ]�w�� 1=���b�]�wor�]�w���� 2=�]�w���\ 
  	
    
 	union
	{
		unsigned						IF:1;
		struct
		{
            unsigned                WriteIF:1;  //�g�J�q�l������������ //0=������ 1=����
			unsigned  			 	TIF :1;		//��ƶǰe����
			unsigned  			 	RIF :1;		//��Ʊ�������
			unsigned  			 	ERRIF:1;	//��Ʊ����ζǰe���~				
		};
	};
	
  unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w�����
}Ele_load_Data_define;
extern Ele_load_Data_define Ele_load_Data; 

typedef struct tagEle_load_Sent_Data_struct {	
  unsigned char 	ID;						//�s��
  unsigned char 	Fuc;					//�\�� //0x01 0x04 0x05 0x06
	union
	{
		struct
		{
			unsigned char 	Reg_H;          //�}�l��m
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
		  unsigned char 	Data_H;         //�Ӽ�
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
            unsigned                    	RIF :1;		//��Ʊ�������
            unsigned                       	ERRIF:1;	//��Ʊ����ζǰe���~
		};
	};
	unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w����� 
}Ele_load_Sent_Data_struct_define;
extern Ele_load_Sent_Data_struct_define Ele_load_Sent;

typedef struct tagEle_load_Get_Data_struct {	
  unsigned char 	ID;						//�s��
  unsigned char 	Fuc;					//�\�� //0x01 0x04 0x05 0x06
	union
	{
		struct
		{
			unsigned char 	Reg_H;	//�]���ǿ�ɭԬO���ǿ鰪�줸����A�ǿ�C�줸
		  unsigned char 	Reg_L;  //�i�OPIC�O���q�C�줸�}�l�\��A�ҥH�|�����C�줸�洫�����D
		};												//�GREG�|�O��Ӱ��C�줸�A�˪����p�A�G���ᦳ�ӭ��s��z���B��
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
            unsigned                    	RIF :1;		//��Ʊ�������
            unsigned                        SORT:1;     //1=��Ʊ������i�H�ƦC�F
            unsigned                       	ERRIF:1;	//��Ʊ����ζǰe���~
		};
	};
	unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w����� 
}Ele_load_Get_Data_struct_define;
extern Ele_load_Get_Data_struct_define Ele_load_Get;

#endif
