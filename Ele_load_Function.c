#include "Main_Define.h"

Ele_load_Sent_Data_struct_define Ele_load_Sent;

void Set_Ele_load(){ //�]�w�q�l������
    Ele_load_Data.Init=1; //���b�]�wor�]�w����
    do{ 
        Ele_load_Data.GoTo_Write_Ele_load=YES; 
        WriteEleLoadSetting(0x00, 0x00, BuzzMusicType); 
        delay(1); 
    } while(Ele_load_Data.WriteIF==0); //�g���ﾹ�T������
    do{ 
        Ele_load_Data.GoTo_Write_Ele_load=YES; 
        WriteEleLoadSetting(0x04, 0x00, 0x00); 
        delay(1); 
    } while(Ele_load_Data.WriteIF==0);//�g0�w��
    do{ 
        Ele_load_Data.GoTo_Write_Ele_load=YES; 
        WriteEleLoadSetting(0x05, 0x00, 0x00); 
        delay(1); 
    } while(Ele_load_Data.WriteIF==0);//�g0�w��
    do{ 
        Ele_load_Data.GoTo_Write_Ele_load=YES; 
        WriteEleLoadSetting(0x07, STOPVILTAGE>>8, STOPVILTAGE&0xFF); 
        delay(1);
    } while(Ele_load_Data.WriteIF==0);//��40V�I��
    do{ 
        Ele_load_Data.GoTo_Write_Ele_load=YES; 
        WriteEleLoadSetting(0x08, DISCHARGECURRENT>>8, DISCHARGECURRENT&0xFF); 
        delay(1); 
    } while(Ele_load_Data.WriteIF==0); //��q�q�y
    if((Ele_load_Data.Capacity_H==0x00) && (Ele_load_Data.Capacity_L==0x0000) && (Ele_load_Data.StopVoltage==STOPVILTAGE)
             && (Ele_load_Data.DisChargeCurrent==DISCHARGECURRENT)) Ele_load_Data.Init=2; //�]�w���\
    else Ele_load_Data.Init=NO;
}

void ReadEleLoadState(){ //Ū���q�l�����������A
    unsigned int math_a;
    unsigned char math_b;
    
		Ele_load_Sent.ID=0x01;
		Ele_load_Sent.Fuc=0x01;	
		
		Ele_load_Sent.Reg_H = 0x00;
		Ele_load_Sent.Reg_L = 0x00;
        
        Ele_load_Sent.Data_H = 0x00;
        Ele_load_Sent.Data_L = 0x01;
        
        Ele_load_Sent.W_R = Read;
		
		Ele_load_Sent.Index=6;
		Ele_load_Sent.RTIndex=0;
        
        Ele_load_Get.RIF=0;		
		Ele_load_Sent.TIF=0;	
		
		math_a=CRC_Make(&Ele_load_Sent, Ele_load_Sent.Index);
		
		math_b = math_a&0xFF;
		Ele_load_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		Ele_load_Sent.CRC_H = math_b;
		Ele_load_Sent.Index+=2;			
		
        
        if(!U2STAbits.UTXEN){
            U2STAbits.UTXEN=1;
        }
        while(IFS1bits.U2TXIF){
            IFS1bits.U2TXIF=0;
            IEC1bits.U2TXIE=1;
        }
		
		U2TXREG = Ele_load_Sent.ID;		
		Ele_load_Sent.RTIndex++;
}

void ReadAllEleLoadData(){ //Ū���Ҧ��q�l�����������
    unsigned int math_a;
    unsigned char math_b;
    
		Ele_load_Sent.ID=0x01;
		Ele_load_Sent.Fuc=0x04;	
		
		Ele_load_Sent.Reg_H = 0x00;
		Ele_load_Sent.Reg_L = 0x00;
        
        Ele_load_Sent.Data_H = 0x00;
        Ele_load_Sent.Data_L = 0x0A;
        
        Ele_load_Sent.W_R = Read;
		
		Ele_load_Sent.Index=6;
		Ele_load_Sent.RTIndex=0;
		
		math_a=CRC_Make(&Ele_load_Sent, Ele_load_Sent.Index);
		
		math_b = math_a&0xFF;
		Ele_load_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		Ele_load_Sent.CRC_H = math_b;
		Ele_load_Sent.Index+=2;			
		
        
        if(!U2STAbits.UTXEN){
            U2STAbits.UTXEN=1;
        }
        while(IFS1bits.U2TXIF){
            IFS1bits.U2TXIF=0;
            IEC1bits.U2TXIE=1;
        }
        
        Ele_load_Get.RIF=0;		
		Ele_load_Sent.TIF=0;	
		
		U2TXREG = Ele_load_Sent.ID;		
		Ele_load_Sent.RTIndex++;	
}

void WriteEleLoadState(unsigned char math_c, unsigned char math_d){ //�g�J�q�l�����������A
    unsigned int math_a;
    unsigned char math_b;
    
    Ele_load_Data.GoTo_Write_Ele_load=YES; //���\�g�J�q�l������ ��timer1�̪�Ū�q�l���������ʧ@���U��
            
		Ele_load_Sent.ID=0x01;
		Ele_load_Sent.Fuc=0x05;	
		
		Ele_load_Sent.Reg_H = 0x00;
		Ele_load_Sent.Reg_L = math_c;//��q=0x00 ����=0x01
        
        Ele_load_Sent.Data_H = math_d;//��q/�w�g����=0xFF  �����q/�|���}�l�Ϊ̩|������=0x00
        Ele_load_Sent.Data_L = 0x00;
        
        Ele_load_Sent.W_R = Write;
        
		Ele_load_Data.WriteIF=0;
		Ele_load_Sent.Index=6;
		Ele_load_Sent.RTIndex=0;
        				
		math_a=CRC_Make(&Ele_load_Sent, Ele_load_Sent.Index);
		
		math_b = math_a&0xFF;
		Ele_load_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		Ele_load_Sent.CRC_H = math_b;
		Ele_load_Sent.Index+=2;			
		
        
        if(!U2STAbits.UTXEN){
            U2STAbits.UTXEN=1;
        }
        while(IFS1bits.U2TXIF){
            IFS1bits.U2TXIF=0;
            IEC1bits.U2TXIE=1;
        }
        
        Ele_load_Get.RIF=0;		
		Ele_load_Sent.TIF=0;	
		
		U2TXREG=Ele_load_Sent.ID;		
		Ele_load_Sent.RTIndex++;
}


void WriteEleLoadSetting(unsigned char math_c, unsigned char math_d, unsigned char math_e){ //�g�J�q�l���������]�w
    unsigned int math_a;
    unsigned char math_b;
    
		Ele_load_Sent.ID=0x01;
		Ele_load_Sent.Fuc=0x06;	
		
		Ele_load_Sent.Reg_H = 0x00;
		Ele_load_Sent.Reg_L = math_c;//���ﾹ����=0x00 BaudRate=0x01 ID=0x02 �e�q=0x03&0x04 �I��q��=0x07 ��q�q�y=0x08
        
        Ele_load_Sent.Data_H = math_d;
        Ele_load_Sent.Data_L = math_e;//�g�J��
        
        Ele_load_Sent.W_R = Write;
        
		Ele_load_Data.WriteIF=0;
        Ele_load_Sent.Index=6;
		Ele_load_Sent.RTIndex=0;
	
		math_a=CRC_Make(&Ele_load_Sent, Ele_load_Sent.Index);
		
		math_b = math_a&0xFF;
		Ele_load_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		Ele_load_Sent.CRC_H = math_b;
		Ele_load_Sent.Index+=2;			
		
        
        if(!U2STAbits.UTXEN){
            U2STAbits.UTXEN=1; //���\�o�e
        }
        while(IFS1bits.U2TXIF){
            IFS1bits.U2TXIF=0; //���o�ͤ��_�ШD
            IEC1bits.U2TXIE=1; //���त�_�ШD
        }

        Ele_load_Get.RIF=0;		
		Ele_load_Sent.TIF=0;	
		
		U2TXREG=Ele_load_Sent.ID;		
		Ele_load_Sent.RTIndex++;    
}