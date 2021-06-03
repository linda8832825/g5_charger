#ifndef USER_H
#define	USER_H

typedef struct tagUser_Data_struct {	
	
	unsigned int ID_G5;
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
	unsigned int Voltage_G5;							//0x02  �q��	0.000~50.000V or 50.00~400.00V
	unsigned int Current_G5;							//0x03  �q�y	0.000~50.000A or 50.00~655.35A
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
    
    //18��2byte
    
    unsigned int 	ID_Ele_load;					//�s�� //0x01
    unsigned int 	Buzzing;        		//��q���� //0x00=���ﾹ�S���b�s 0x01=���ﾹ�b�s //0x00 0x01 //�e���O���S���s �᭱�O�s������
    unsigned int 	BaudRate;				//BaudRate  //0x25 0x80
    unsigned int    ID_decide;				//�i�M�wid //0x00 0x01
    unsigned int 	Voltage_Ele_load;				//�q�� // Voltage/100=��ڹq��
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
	
    //29��2byte
    
    unsigned char 	CRC_L;
    unsigned char 	CRC_H;
    

	unsigned char Index;						//�n�����
    unsigned char RTIndex;					//�w����� 
	
}User_Data_struct_define;
extern User_Data_struct_define User_Data; 

#endif

