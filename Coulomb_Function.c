#include "Main_Define.h"

Coulomb_Sent_Data_struct_define Coulomb_Sent; 
Coulomb_Receiver_Data_define Coulomb_Receiver; 

unsigned int Prevention_Zero_Ah(void){
    Unlock_Coulomb();
    //------------------------------更改目前安時數------------------------------------//
    do{ Write_Coulomb_Data(0x07,0x0190); }while(!Coulomb_Receiver.TIF);//0x0009  標準電池容量 0.0~6553.5AH  將reset安時數設為0.2ah
    Coulomb_Receiver.TIF=0;
    //--------------------------------------------------------------------------------//
    
    //------------------------------更改reset安時數-----------------------------------//
    do{ Write_Coulomb_Data(0x09,0x01F4); }while(!Coulomb_Receiver.TIF);//0x0009  標準電池容量 0.0~6553.5AH  將reset安時數設為0.2ah
    Coulomb_Receiver.TIF=0;
    //--------------------------------------------------------------------------------//

    //--------------------------------降低reset電壓-----------------------------------//
    do{ Write_Coulomb_Data(0x0A,0x0190); }while(!Coulomb_Receiver.TIF); //將reset電壓改為40.0v
    Coulomb_Receiver.TIF=0;
    //--------------------------------------------------------------------------------//
    
    
    delay(2);

            
    Coulomb_Receiver.RIF=0;
    do{ Read_ALL_Coulomb_Data(); } while(!Coulomb_Receiver.RIF); //跟G5要資料                                
    if((Coulomb_Data.Residual_Electricity<=0x01F4) && (Coulomb_Data.Residual_Electricity>0x01EF)) {
        
       //--------------------------------改回reset電壓------------------------------------//
        do{ Write_Coulomb_Data(0x0A,0x02BC); }while(!Coulomb_Receiver.TIF); //將reset電壓改為70v
        Coulomb_Receiver.TIF=0;
        //---------------------------------------------------------------------------------// 
            
        return 1;
    }
    else return 0;

}

void Unlock_Coulomb(void)
{
    Coulomb_Sent.ID='p';
    Coulomb_Sent.Fuc='w'; 

    Coulomb_Sent.Reg_H = 'd';
    Coulomb_Sent.Reg_L = '=';

    Coulomb_Sent.Quantity_H= '0';
    Coulomb_Sent.Quantity_L = '6';
    Coulomb_Sent.CRC_L = '3';
    Coulomb_Sent.CRC_H = '0';

    Coulomb_Sent.Index=8;
    Coulomb_Sent.RTIndex=0;

    Coulomb_Receiver.BusyIF=1;
    Coulomb_Receiver.RIF=0;  
    Coulomb_Receiver.TIF=0;  


    Coulomb_Sent.W_R = Write;
    Coulomb_Sent.RTIndex=1;
    if(IEC0bits.U1TXIE == 0)IEC0bits.U1TXIE = 1;
    U1TXREG=Coulomb_Sent.ID;  
    while(Coulomb_Sent.Index!=0); //等待庫倫計回應資料
    Coulomb_Receiver.BusyIF=0;   
}

void Read_ALL_Coulomb_Data(void)
{
	if(Coulomb_Receiver.BusyIF==0)
	{
		unsigned int math_a;
		unsigned char math_b;

		
		Coulomb_Sent.ID=0x01;
		Coulomb_Sent.Fuc=0x03;	
		
		Coulomb_Sent.Reg_H = 0;
		Coulomb_Sent.Reg_L = 0;
		
		Coulomb_Sent.Quantity_H= 0;
		Coulomb_Sent.Quantity_L = 0x22;
		
		Coulomb_Sent.Index=6;
		Coulomb_Sent.RTIndex=0;

		
		Coulomb_Receiver.Index=0;
		Coulomb_Receiver.RTIndex=0;
		Coulomb_Receiver.BusyIF=1;
		Coulomb_Receiver.RIF=0;		
		Coulomb_Receiver.TIF=0;		
				
		math_a=CRC_Make(&Coulomb_Sent,Coulomb_Sent.Index);
		
		math_b = math_a&0xFF;
		Coulomb_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		Coulomb_Sent.CRC_H = math_b;
		Coulomb_Sent.Index+=2;			
		Coulomb_Sent.W_R = Read;
		Coulomb_Sent.RTIndex=1;
		if(IEC0bits.U1TXIE == 0)IEC0bits.U1TXIE = 1;
		U1TXREG=Coulomb_Sent.ID;		
		
	}
}	


void Write_Coulomb_Data(unsigned int Regest,unsigned int Data)
{
	unsigned int math_a;
	unsigned char math_b;
	
	if(Coulomb_Receiver.BusyIF==0)
	{	

		Coulomb_Sent.ID=0x01;
		Coulomb_Sent.Fuc=0x06;	
		
		Coulomb_Sent.Reg_H = (Regest&0xFF00)>>8;
		Coulomb_Sent.Reg_L = Regest&0xFF;
		
		Coulomb_Sent.Quantity_H = (Data & 0xFF00)>>8;
		Coulomb_Sent.Quantity_L = Data & 0xFF;
		
		Coulomb_Sent.Index=6;
		Coulomb_Sent.RTIndex=0;	
		
		Coulomb_Receiver.Index=0;
		Coulomb_Receiver.RTIndex=0;
		Coulomb_Receiver.BusyIF=1;
		Coulomb_Receiver.RIF=0;		
		Coulomb_Receiver.TIF=0;						
		
		math_a=CRC_Make(&Coulomb_Sent,Coulomb_Sent.Index);
		
		math_b = math_a&0xFF;
		Coulomb_Sent.CRC_L = math_b;
		
		math_b = (math_a&0xFF00)>>8;
		Coulomb_Sent.CRC_H = math_b;
		Coulomb_Sent.Index+=2;			
		
		Coulomb_Sent.W_R = Write;
		Coulomb_Sent.RTIndex=1;
		if(IEC0bits.U1TXIE == 0)IEC0bits.U1TXIE = 1;
		U1TXREG=Coulomb_Sent.ID;	
		
	}	
}	
