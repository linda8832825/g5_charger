#include "Main_Define.h"

G5_Sent_Data_struct_define G5_Sent; 
G5_Get_Data_struct_define G5_Get;


void Write_G5_Data(unsigned int Regest,unsigned int Data) //�μg�J�w�ɼ�
{
    //���g5�q����42(�����)
    //�gresidual_electricity(0x07)��0x01
    //
    //�A�ӵ���q��>=253h
    //�g(0x09)��0x01
    
	unsigned int math_a;
	unsigned char math_b;
	

        
		G5_Sent.ID=0x01;
		G5_Sent.Fuc=0x06;	
		
		G5_Sent.Reg_H = (Regest&0xFF00)>>8;
		G5_Sent.Reg_L = Regest&0xFF;
		
		G5_Sent.Data_H = (Data & 0xFF00)>>8;
		G5_Sent.Data_L = Data & 0xFF;
		
		G5_Sent.Index=6;
		G5_Sent.RTIndex=0;	
		
		
		G5_Sent.RTIndex=0;
		G5_Get.RIF=0;		
		G5_Sent.TIF=0;	
        G5_Sent.W_R = Write;
		
		math_a=CRC_Make(&G5_Sent,G5_Sent.Index);
		
		math_b = math_a&0xFF;
		G5_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		G5_Sent.CRC_H = math_b;
		G5_Sent.Index+=2;			
		
	
		G5_Sent.RTIndex=1;
		if(IEC5bits.U3TXIE == 0)IEC5bits.U3TXIE = 1;
		U3TXREG=G5_Sent.ID;	
		
	
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
    
		G5_Sent.ID=0x01;
		G5_Sent.Fuc=0x03;	
		
		G5_Sent.Reg_H = 0x00;
		G5_Sent.Reg_L = 0x01;
        
        G5_Sent.Data_H = 0x00;
        G5_Sent.Data_L = 0x0F;
		
		G5_Sent.Index=6;
		G5_Sent.RTIndex=0;

		
		G5_Sent.RTIndex=0;
        G5_Sent.W_R = Read;
				
		math_a=CRC_Make(&G5_Sent, G5_Sent.Index);
		
		math_b = math_a&0xFF;
		G5_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		G5_Sent.CRC_H = math_b;
		G5_Sent.Index+=2;			
		
        
        if(!U3STAbits.UTXEN){
            U3STAbits.UTXEN=1;
        }
        while(IFS5bits.U3TXIF){
            IFS5bits.U3TXIF=0;
            IEC5bits.U3TXIE=1;
        }
		
		U3TXREG=G5_Sent.ID;		
		G5_Sent.RTIndex++;
	
}


