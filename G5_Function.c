#include "Main_Define.h"

G5_MOXA_Data_struct_define G5_MOXA;

unsigned int G5_CRC_Check(void) //howmuch�O���h�֭�!!  5��Ʀr�N��5    ���O�q0�}�l��
{
	unsigned int CRC_CODE=0xFFFF,math_a,math_b;
	unsigned char CRC_Length=0,i,*CRC_Address;
	


	CRC_Address=&G5_MOXA.ID;
	CRC_Length=G5_MOXA.RTIndex-2;	
	
	while(CRC_Length--)
	{
		CRC_CODE^=*CRC_Address++;//��XOR����A��a�}+1
		for(i=0;i<8;i++)
		{
			if(CRC_CODE&0x01)//�p�G�̫�@�Ӧ줸�O1��CRC_CODE�k��1�줧��P0xA001��XOR
			{
				CRC_CODE=(CRC_CODE>>1)^0xA001;
			}
			else
			{
				CRC_CODE=(CRC_CODE>>1);
			}	
		}
	}		
		

	CRC_Address=&G5_MOXA.ID;
	CRC_Address+=G5_MOXA.RTIndex-2;	

	
	math_a=*CRC_Address;
	math_a=math_a<<8;
	CRC_Address++;
	math_a=math_a|(*CRC_Address);
	
	//�]�����g���F���CRC���ӬO��L �bH �i�O�g�ϤF �ҥH �ܦ���H�bL �Ϊ̥�L�bH ���i�H
	math_b=*CRC_Address;
	math_b=math_b<<8;
	CRC_Address--;
	math_b=math_b|(*CRC_Address);
	
	if (CRC_CODE == math_a || CRC_CODE == math_b)//��CRC�T�{���� �N��ƭ��s��z
	{
		return 1;	
	}
	else 
	{
		return 0;
	}	
	
}

void Write_G5_Data(unsigned int Regest,unsigned int Data) //�μg�J�w�ɼ�
{
    //���g5�q����42(�����)
    //�gresidual_electricity(0x07)��0x01
    //
    //�A�ӵ���q��>=253h
    //�g(0x09)��0x01
    
	unsigned int math_a;
	unsigned char math_b;
	
//	if(G5_MOXA.BusyIF==0)
//	{	
        
		G5_MOXA.ID=0x01;
		G5_MOXA.Fuc=0x06;	
		
		G5_MOXA.Reg_H = (Regest&0xFF00)>>8;
		G5_MOXA.Reg_L = Regest&0xFF;
		
		G5_MOXA.Quantity_H = (Data & 0xFF00)>>8;
		G5_MOXA.Quantity_L = Data & 0xFF;
		
		G5_MOXA.Index=6;
		G5_MOXA.RTIndex=0;	
		
		
		G5_MOXA.RTIndex=0;
		G5_MOXA.RIF=0;		
		G5_MOXA.TIF=0;						
		
		math_a=CRC_Make(&G5_MOXA,G5_MOXA.Index);
		
		math_b = math_a&0xFF;
		G5_MOXA.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		G5_MOXA.CRC_H = math_b;
		G5_MOXA.Index+=2;			
		
	
		G5_MOXA.RTIndex=1;
		if(IEC5bits.U3TXIE == 0)IEC5bits.U3TXIE = 1;
		U3TXREG=G5_MOXA.ID;	
		
	
}

void Read_ALL_G5_Data(void)
{
    unsigned int math_a;
    unsigned char math_b;
    //�@�}�l��Ūg5�����
    //���g5�q����42(�����)
    //�A�����᪺��
    //
    //�R�q�L�{���@��Ūg5���
    //����q��>=253h
    //�A�g
    
//	if(G5_MOXA.BusyIF==0)
//	{
		G5_MOXA.ID=0x01;
		G5_MOXA.Fuc=0x03;	
		
		G5_MOXA.Reg_H = 0x00;
		G5_MOXA.Reg_L = 0x01;
        
        G5_MOXA.Data_H = 0x00;
        G5_MOXA.Data_L = 0x0E;
		
		G5_MOXA.Index=6;
		G5_MOXA.RTIndex=0;

		
		G5_MOXA.RTIndex=0;
//		G5_MOXA.BusyIF=1;
//		G5_MOXA.RIF=0;		
//		G5_MOXA.TIF=1;		
				
		math_a=CRC_Make(&G5_MOXA, G5_MOXA.Index);
		
		math_b = math_a&0xFF;
		G5_MOXA.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		G5_MOXA.CRC_H = math_b;
		G5_MOXA.Index+=2;			
		
        
        if(!U3STAbits.UTXEN){
            U3STAbits.UTXEN=1;
        }
        while(IFS5bits.U3TXIF){
            IFS5bits.U3TXIF=0;
            IEC5bits.U3TXIE=1;
        }
		
		U3TXREG=G5_MOXA.ID;		
		G5_MOXA.RTIndex++;
	
}


