#include "Main_Define.h"

G5_MOXA_Data_struct_define G5_MOXA;

unsigned int G5_CRC_Check(void) //howmuch是有多少個!!  5格數字就填5    不是從0開始數
{
	unsigned int CRC_CODE=0xFFFF,math_a,math_b;
	unsigned char CRC_Length=0,i,*CRC_Address;
	


	CRC_Address=&G5_MOXA.ID;
	CRC_Length=G5_MOXA.RTIndex-2;	
	
	while(CRC_Length--)
	{
		CRC_CODE^=*CRC_Address++;//先XOR完後再把地址+1
		for(i=0;i<8;i++)
		{
			if(CRC_CODE&0x01)//如果最後一個位元是1把CRC_CODE右移1位之後與0xA001做XOR
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
	
	//因為當初寫錯了其實CRC應該是先L 在H 可是寫反了 所以 變成先H在L 或者先L在H 都可以
	math_b=*CRC_Address;
	math_b=math_b<<8;
	CRC_Address--;
	math_b=math_b|(*CRC_Address);
	
	if (CRC_CODE == math_a || CRC_CODE == math_b)//當CRC確認之後 將資料重新整理
	{
		return 1;	
	}
	else 
	{
		return 0;
	}	
	
}

void Write_G5_Data(unsigned int Regest,unsigned int Data) //用寫入安時數
{
    //放到g5電壓為42(之後測)
    //寫residual_electricity(0x07)為0x01
    //
    //再來等到電壓>=253h
    //寫(0x09)為0x01
    
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
    //一開始先讀g5的資料
    //放到g5電壓為42(之後測)
    //再做之後的事
    //
    //充電過程中一直讀g5資料
    //直到電壓>=253h
    //再寫
    
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


