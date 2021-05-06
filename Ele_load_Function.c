#include "Main_Define.h"

Ele_load_Sent_Data_struct_define Ele_load_Sent;

void Set_Ele_load(){ //設定電子附載機
    do{ WriteEleLoadSetting(0x00, 0x00, BuzzMusicType); } while(Ele_load_Data.WriteIF=0); //寫蜂鳴器響的音樂
    do{ WriteEleLoadSetting(0x04, 0x00, 0x00);} while(Ele_load_Data.WriteIF=0);//寫0安時
    do{ WriteEleLoadSetting(0x05, 0x00, 0x00);} while(Ele_load_Data.WriteIF=0);//寫0安時
    do{ WriteEleLoadSetting(0x07, StopVoltage>>8, StopVoltage&0xFF);} while(Ele_load_Data.WriteIF=0);//放40V截止
    do{ WriteEleLoadSetting(0x08, DisChargeCurrent>>8, DisChargeCurrent&0xFF);} while(Ele_load_Data.WriteIF=0); //放電電流
    Ele_load_Data.Init=YES;
}

void ReadEleLoadState(){ //讀取電子附載機的狀態
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

void ReadAllEleLoadData(){ //讀取所有電子附載機的資料
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

void WriteEleLoadState(unsigned char math_c, unsigned char math_d){ //寫入電子附載機的狀態
    unsigned int math_a;
    unsigned char math_b;
            
		Ele_load_Sent.ID=0x01;
		Ele_load_Sent.Fuc=0x05;	
		
		Ele_load_Sent.Reg_H = 0x00;
		Ele_load_Sent.Reg_L = math_c;//放電=0x00 結束=0x01
        
        Ele_load_Sent.Data_H = math_d;//放電/已經結束=0xFF  停止放電/尚未開始或者尚未結束=0x00
        Ele_load_Sent.Data_L = 0x00;
        
        Ele_load_Sent.W_R = Write;
		
		Ele_load_Sent.Index=6;
		Ele_load_Sent.RTIndex=0;
        
		
        Ele_load_Get.RIF=0;		
		Ele_load_Sent.TIF=0;	
        Ele_load_Data.WriteIF=0;
        
				
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
		
		U2TXREG=Ele_load_Sent.ID;		
		Ele_load_Sent.RTIndex++;
        	
}


void WriteEleLoadSetting(unsigned char math_c, unsigned char math_d, unsigned char math_e){ //寫入電子附載機的設定
    unsigned int math_a;
    unsigned char math_b;
    
		Ele_load_Sent.ID=0x01;
		Ele_load_Sent.Fuc=0x06;	
		
		Ele_load_Sent.Reg_H = 0x00;
		Ele_load_Sent.Reg_L = math_c;//蜂鳴器音樂=0x00 BaudRate=0x01 ID=0x02 容量=0x03&0x04 截止電壓=0x07 放電電流=0x08
        
        Ele_load_Sent.Data_H = math_d;
        Ele_load_Sent.Data_L = math_e;//寫入值
        
        Ele_load_Sent.W_R = Write;
		
		Ele_load_Sent.Index=6;
		Ele_load_Sent.RTIndex=0;

		
        Ele_load_Get.RIF=0;		
		Ele_load_Sent.TIF=0;	
        Ele_load_Data.WriteIF=0;
        
				
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
		
		U2TXREG=Ele_load_Sent.ID;		
		Ele_load_Sent.RTIndex++;
        
}