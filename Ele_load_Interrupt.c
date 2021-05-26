#include "Main_Define.h"

Ele_load_Data_define Ele_load_Data; 
Ele_load_Get_Data_struct_define Ele_load_Get;
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) //讀完電子附載機讀或寫完 收到的資料做整理
{
        unsigned char math_a,math_c;
        unsigned int 	*index1;
        unsigned char   *index2, Quantity,*index3;

        unsigned char Erro_IF;

        index1=&Ele_load_Get.ID;
        index3=&Ele_load_Get.ID;

        Erro_IF=0;

        if(Ele_load_Get.RTIndex>0)
//        if((Ele_load_Get.RTIndex>0) && (Ele_load_Get.SORT==YES))
        {
            if(Ele_load_Sent.W_R == Read)
            {
                if(CRC_Check_Ele_load())
                {
                    //是用04讀取的
                    Ele_load_Get.Value_L=Ele_load_Get.Reg_L;
                    Ele_load_Get.Value_H=Ele_load_Get.Reg_H;
                    index1=&Ele_load_Data.ID;
                    *index1=Ele_load_Get.ID;
                    index1++;
                    //取得電子附載機資料陣列從哪位置開始放資料

                    Quantity = Ele_load_Get.Reg_H/2; //資料比數
                    index2=&Ele_load_Get.Reg_L; //第一筆data
                    for(Quantity=Quantity;Quantity>0;Quantity--)
                    {
                        Ele_load_Get.Value_H = *index2;
                        *index2++;
                        Ele_load_Get.Value_L = *index2;
                        *index1 = Ele_load_Get.Value; //把DATA放進電子附載機的資料儲存陣列裡
                        index1++;
                        index2++;
                    }
                    Ele_load_Get.RIF=1;
                    Ele_load_Get.RTIndex=0;
                }
                else
                {
                    Ele_load_Get.RTIndex=0;
                    Ele_load_Get.ERRIF=1;
                }

            }
            else if(Ele_load_Sent.W_R == Write)
            {
                if(Ele_load_Get.RTIndex==0x08)
                {
                    Erro_IF=0;
                    math_c = *index3; //收到的ID
                    if( math_c != Ele_load_ID ) Erro_IF=1;
                    index3++;
                    
                    if(Erro_IF){
                        Ele_load_Data.WriteIF=0;//寫入電子附載機失敗
                        Ele_load_Get.TIF=0;
                        Ele_load_Get.ERRIF=1;
                    }
                    else{
//                        Ele_load_Data.GoTo_Write_Ele_load=NO; //不需要再次寫入電子附載機
                        Ele_load_Data.WriteIF=1;//寫入電子附載機成功
                        Ele_load_Get.ERRIF=0;
                        Ele_load_Get.RTIndex=0;
                        Ele_load_Get.TIF=1;
                    }
                }
                else{
                    Ele_load_Data.WriteIF=0;//寫入電子附載機失敗
                    Ele_load_Data.GoTo_Write_Ele_load=YES; //正在執行寫入命令
                    Ele_load_Get.ERRIF=1;
                    Ele_load_Get.RTIndex=0;
                }			
            }
        }	

        if(U2STAbits.OERR)
        {
            while(U2STAbits.OERR)
            {
                math_a=U2RXREG;
            }
        }

        IFS0bits.T2IF=0;  //timer2未發生中斷請求
}	

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{		
		unsigned int math_a;
		static unsigned char *index;
		static unsigned char Fuction;
        if(Ele_load_Get.RIF==0)
		{
			TMR2=0;		
//			if(!T2CONbits.TON) //u2有接收到東西時才會讓timer3啟動
//			{
//				T2CONbits.TON=1;
//			}
			if(Ele_load_Get.RTIndex==0)
			{
				index=&Ele_load_Get.ID;
				*index=U2RXREG;
				index++;
				Ele_load_Get.RTIndex++;	
				Fuction=0;
			}
			else
			{
				if(Ele_load_Get.ID==Ele_load_ID)
				{
					TMR2=0;
					*index=U2RXREG;
					Ele_load_Get.RTIndex++;			
					index++;
				}	
				else
				{
//					T2CONbits.TON=0;
					math_a=U2RXREG;
					Ele_load_Get.RTIndex=0;	
				}
			}		
		}
		else
		{
			math_a=U2RXREG;
		}
		IFS1bits.U2RXIF=0;
}	

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
{		
	
	static unsigned char *index;
	unsigned int math_a;
	
	if(Ele_load_Sent.RTIndex < Ele_load_Sent.Index)
	{
		if(Ele_load_Sent.RTIndex==1) index=&Ele_load_Sent.Fuc;
		U2TXREG=*index;
		index++;
		Ele_load_Sent.RTIndex++;
		for (math_a=0;math_a<=20;math_a++)
		{
			asm("Nop");
		}	
	}
	else 
	{
		Ele_load_Sent.RTIndex=0;
		Ele_load_Sent.Index=0;
	}	

	IFS1bits.U2TXIF=0;
}