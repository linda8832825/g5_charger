#ifndef G5_define_H
#define G5_define_H

typedef struct tagG5_Data_struct {	
	
	unsigned int ID;
	unsigned int InterFace;                 // 	
 	union
	{					
		struct                              //0x01 H:Voltage states L:Current states 0x03=��  0x13=�t
		{	
			unsigned Current_Point	:4;		//�q�y��p���I
			unsigned Current_statue	:4;		//
			unsigned Voltage_Point	:4;		//�q����p���I
			unsigned Voltage_statue	:4;		//		
		};		
	};
	unsigned int Voltage;							//0x02  �q��	0.000~50.000V or 50.00~400.00V
	unsigned int Current;							//0x03  �q�y	0.000~50.000A or 50.00~655.35A
	unsigned int Residual_Electricity;              //0x04  �ѤU�q�q0.0~6553.5Ah
    unsigned int Nominal_Battery_Capacity;          //0x05  �зǹq���e�q 0.0~6553.5AH
    unsigned int Battery_Power;						//0x06  �ʤ���γѾl�q�q0.00~100.00%
    unsigned int Temperature1;						//0x07  �ū�1	-55.0~125.0
    
	unsigned int Battery_ID;						//0x08  Ū��Battery_ID(���x���X �Ȥ�i�H�ۦ�]�w)
	unsigned int Car_Statue;                        //0x09  Ū�����l���A
	unsigned int Month;								//0x000A  Ū���ϥΤ��
	unsigned int Day;                               //0x0B  Ū���ϥΤ��			
	unsigned int Hour;                              //0x0C  Ū���ϥΤp��	
	unsigned int minute;                            //0x0D  Ū���ϥΤ���			
	unsigned int Now_Total_Capacity;				//0x0E  Ū���q���Ѥƫ�A�q���ҳѾl���ݾl���B�e�q				
	unsigned int Fake_Voltage;						//0x0F  Ū�����q��
    unsigned int x2;                        		//0x10  Ū��reset�q���I
	struct
	{
		unsigned  			 	IF1 :1;             //��ƶǰe����
		unsigned  			 	IF2 :1;             //��Ʊ�������
		unsigned  			 	IF3 :1;             //��Ʊ����ζǰe���~
	};		
	
}G5_Data_struct_define;
extern G5_Data_struct_define G5_Data; 

typedef struct tagG5_Sent_Data_struct {	
  unsigned char 	ID;						//�s��
  unsigned char 	Fuc;					//�\��
	union
	{
		struct
		{
			unsigned char 	Reg_H;          //�]���ǿ�ɭԬO���ǿ鰪�줸����A�ǿ�C�줸
		  unsigned char 	Reg_L;          //�i�OPIC�O���q�C�줸�}�l�\��A�ҥH�|�����C�줸�洫�����D
		};									//�GREG�|�O��Ӱ��C�줸�A�˪����p�A�G���ᦳ�ӭ��s��z���B��
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
            unsigned                    	RIF :1;		//��Ʊ�������
            unsigned                       	ERRIF:1;	//��Ʊ����ζǰe���~
		};
	};
	unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w����� 
}G5_Sent_Data_struct_define;
extern G5_Sent_Data_struct_define G5_Sent; 

typedef struct tagG5_Get_Data_struct {	
  unsigned char 	ID;						//�s��
  unsigned char 	Fuc;					//�\��
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
}G5_Get_Data_struct_define;
extern G5_Get_Data_struct_define G5_Get;

#endif
