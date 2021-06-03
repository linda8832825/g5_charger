#ifndef Coulomb_UART_define_H
#define Coulomb_UART_define_H


typedef struct tagCoulomb_Sent_Data_struct {	
  unsigned char 	ID;						//�s��
  unsigned char 	Fuc;					//�\��
	union
	{
		struct
		{
			unsigned char 	Reg_H;	//�]���ǿ�ɭԬO���ǿ鰪�줸����A�ǿ�C�줸
		  unsigned char 	Reg_L;  //�i�OPIC�O���q�C�줸�}�l�\��A�ҥH�|�����C�줸�洫�����D
		};												//�GREG�|�O��Ӱ��C�줸�A�˪����p�A�G���ᦳ�ӭ��s��z���B��
	};	  
	union
	{
		unsigned int DATA[2];	
		struct
		{
			unsigned char 	Quantity_H;
		  unsigned char 	Quantity_L;  
		  unsigned char 	Total_Byte;		  
		};
		struct
		{
			unsigned						:8;
			unsigned						:8;
		  unsigned char 			CRC_L;		
		  unsigned char 			CRC_H;				    
		};		
	};
												
 	union
	{
		struct
		{		
			unsigned						IF:3;	
			unsigned						  :5;	
			unsigned						W_R:2;				
		};
		struct
		{
	//		unsigned  			 	TIF :1;		//��ƶǰe����
		//	unsigned  			 	RIF :1;		//��Ʊ�������
		//	unsigned  			 	ERRIF:1;	//��Ʊ����ζǰe���~			
		};
	};
	unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w����� 
}Coulomb_Sent_Data_struct_define;
extern Coulomb_Sent_Data_struct_define Coulomb_Sent; 



typedef struct tagCoulomb_Receiver_Data_struct {	
  unsigned char 	ID;						//�s��
  unsigned char 	Fuc;					//�\��
	union
	{
		struct
		{
			unsigned char 	Reg_H;	//�]���ǿ�ɭԬO���ǿ鰪�줸����A�ǿ�C�줸
		  unsigned char 	Reg_L;  //�i�OPIC�O���q�C�줸�}�l�\��A�ҥH�|�����C�줸�洫�����D
		};												//�GREG�|�O��Ӱ��C�줸�A�˪����p�A�G���ᦳ�ӭ��s��z���B��
	};	  
	union
	{
		unsigned int DATA[400];	
		struct
		{
			unsigned char 	Quantity_H;
		  unsigned char 	Quantity_L;  
		  unsigned char 	Total_Byte;		  
		};
		struct
		{
			unsigned						:8;
			unsigned						:8;
		  unsigned char 			CRC_L;		
		  unsigned char 			CRC_H;				    
		};		
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
		struct
		{		
			unsigned						IF:3;	
			unsigned						  :5;	
		};
		struct
		{
			unsigned  			 	TIF :1;		//��ƶǰe����
			unsigned  			 	RIF :1;		//��Ʊ�������
			unsigned  			 	ERRIF:1;	//��Ʊ����ζǰe���~		
			unsigned  			 	BusyIF:1;	//��Ʊ����ζǰe���~		
			unsigned  			 	ERR_Count:4;	//��Ʊ����ζǰe���~						
		};
	};
	unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w����� 
}Coulomb_Receiver_Data_define;
extern Coulomb_Receiver_Data_define Coulomb_Receiver; 


typedef struct tagCoulomb_Data_struct {	
	
	unsigned int ID;
	unsigned int InterFace;						// 	
 	union
	{
		unsigned int x1;										//H:Voltage states L:Current states 0x03=��  0x13=�t
		struct
		{	
			unsigned Current_Point	:4;		//�q����p���I
			unsigned Current_statue	:4;		//
			unsigned Voltage_Point	:4;		//�q�y��p���I(�j��)
			unsigned Voltage_statue	:4;		//		
		};		
	};
	unsigned int Voltage;										//0x0003  �q��	0.000~50.000V or 50.00~400.00V
	unsigned int Current;										//0x0004  �q�y	0.000~50.000A or 50.00~655.35A
	unsigned int Temperature1;							//0x0005  �ū�1	-55.0~125.0
	unsigned int Temperature2;							//0x0006  �ū�2 -55.0~125.0
	unsigned int Residual_Electricity; 			//0x0007  �ѤU�q�q0.0~6553.5Ah
	unsigned int Power_Consumption;					//0x0008  �q�q���� 0~65535Wh
	unsigned int Nominal_Battery_Capacity; 	//0x0009  �зǹq���e�q 0.0~6553.5AH
	unsigned int x2;		//0x000A  if the Voltage exceeds the setting ,reset 100% 0.0~400.0V
	unsigned int Battery_Power;							//0x000B  �ʤ���γѾl�q�q0.00~100.00%
	unsigned int Alert_H_Voltage_;					//0x000C  �W���q��ĵ�i	0~6553.5V			
	unsigned int Alert_L_Voltaget;					//0x000D  �U���q��ĵ�i 0~6553.5V		
	unsigned int Alert_H_Current;						//0x000E  �W���q�yĵ�i	0~6553.5A			
	unsigned int Alert_L_Current;						//0x000F  �U���q�yĵ�i 0~6553.5A					
	unsigned int Alert_H_Temp1;							//0x0010  �W���ū�1ĵ�i	0~125.0			
	unsigned int Alert_L_Temp1;							//0x0011  �U���ū�1ĵ�i 0~125.0				
	unsigned int Alert_H_Temp2;							//0x0012  �W���ū�2ĵ�i	0~125.0			
	unsigned int Alert_L_Temp2;							//0x0013  �U���ū�2ĵ�i 0~125.0						
	unsigned int Allow_over_Warning_Time;		//0x0014  0~1000Min
	unsigned int x4;												//0x0015  while Electric Current <Set(address0x0016) Automatically turn off the LCD background light 0~1000min
	unsigned int x5;												//0x0016  while Electric Current >Set(0~655.35A) Automatically Turn on the LCD background light
	unsigned int Fix_Voltage;								//0x0017  (Note: non professionals don't change it)  
	unsigned int Electric_Current_range;		//0x0018  (75mV 0.0~1000.0A)
	unsigned int x6;												//0x0019  offset	0.00~0.99A
	unsigned int x7;												//0x001A  Line loss fix A+0.00~100.00mV
	unsigned int Uart_Mode;									//0x001B  0:HEX 1:TXT 2:Modbus
	unsigned int x8_0x001C;				
	unsigned int x9_0x001D;	
	unsigned int x10_0x001E;	
	unsigned int x11_0x001F;	
	unsigned int x12_0x0020;	
	unsigned int x13_0x0021;	
	unsigned int x14_0x0022;
	struct
	{
		unsigned  			 	IF1 :1;		//��ƶǰe����
		unsigned  			 	IF2 :1;		//��Ʊ�������
		unsigned  			 	IF3 :1;	  //��Ʊ����ζǰe���~	
		
	};		
	
}Coulomb_Data_struct_define;

extern Coulomb_Data_struct_define Coulomb_Data; 


#endif
