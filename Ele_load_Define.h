#ifndef Ele_load_Define_H
#define Ele_load_Define_H


typedef struct tagEle_load_Data {	
    unsigned char 	ID;						//�s�� //0x01
    unsigned char 	Fuc;					//�\�� //0x01 0x04 0x05
    unsigned char 	BuzzMusic;				//���ﾹ���� //0=�L�n 1�B2�B3=�ӧO������ ��q�����I���I�N�|�}�l�ۺq //0x00 0x01
    unsigned char 	BaudRate;				//BaudRate  //0x25 0x80
    unsigned char   ID_decide;				//�i�M�wid //0x00 0x01
    unsigned char 	Voltage;				//�q�� // Voltage/100=��ڹq��
    union
	{
		unsigned int x1;						//�e��8�ӬO�����P�{�b���A �᭱�K�ӬO�e�q�����줸
		struct
		{	
			unsigned type               :3;		//���� 001
			unsigned twoZero            :2;		//���0
			unsigned OverTemperature	:1;		//1=�O�L�ūO�@�Ȱ����A�A0=�O���`���A
			unsigned End            	:1;		//1=�O��ܤw�g�����A0=�O�|���}�l�Ϊ̩|������
            unsigned DisCharge          :1;     //1=�O��q���A�F0=�O����A
            unsigned Capacity_H         :8;     //�e�q���줸
		};		
	};
    unsigned char 	Capacity_L;				//�e�q�C�줸
    unsigned char 	Temperature;			//�ū� // Temperature/10=��ڷū�
    unsigned char 	StopVoltage;            //�I��q�� // StopVoltage/100=��ںI��q��
    unsigned char 	DisCharge;              //��q�q�y // DisCharge/10=��ک�q�q�y
    unsigned char   Watt;                   //�\�v 
    
    unsigned Write_Ele_load:2;              //���L�g�J�q�l���������\
  									
 	union
	{
		unsigned						IF:1;
		struct
		{
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
            unsigned                       	ERRIF:1;	//��Ʊ����ζǰe���~
		};
	};
	unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w����� 
}Ele_load_Get_Data_struct_define;
extern Ele_load_Get_Data_struct_define Ele_load_Get;

#endif
