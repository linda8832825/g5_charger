#include "Main_Define.h"

Ele_load_Data_define Ele_load_Data; 
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
	if(Ele_load_Data.RTIndex>0)
	{
		if((Ele_load_Data.Fuc == Ele_load_Keyword) && (Ele_load_Data.StopFuc == Ele_load_StopFuc) && (Ele_load_Data.End == Ele_load_End))
		{
			if(Ele_load_Data.RTIndex==11)
			{
				Ele_load_Data.RIF=1;
			}		
			else
			{
				Ele_load_Data.ERRIF=1;	
				Ele_load_Data.RTIndex=0;
			}							
		}	
		else
		{
			Ele_load_Data.ERRIF=1;	
			Ele_load_Data.RTIndex=0;		
		}	
	
	}
	T2CONbits.TON=0;	
	IFS0bits.T2IF=0;
			
}	

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{		
		unsigned int math_a;
		static unsigned char *index;
		static unsigned char Fuction;
		
		if(Ele_load_Data.RIF==0)
		{
			TMR2=0;		
			if(!T2CONbits.TON)
			{
				T2CONbits.TON=1;
			}
			if(Ele_load_Data.RTIndex==0)
			{
				index=&Ele_load_Data.ID;
				*index=U2RXREG;
				index++;
				Ele_load_Data.RTIndex++;	
				Fuction=0;
			}
			else
			{
				if(Ele_load_Data.ID == Ele_load_Addr)
				{
					TMR2=0;
					*index=U2RXREG;
					Ele_load_Data.RTIndex++; //放第二筆資料
//					if(Ele_load_Data.RTIndex==2&&*index==0x10)Fuction=*index;
//					if(Ele_load_Data.RTIndex==7&&Fuction==0x10)
//					{
//							Ele_load_Data.Index=*index+9;
//					}					
					index++;
				}	
				else
				{
					T2CONbits.TON=0;
					math_a=U2RXREG;
					Ele_load_Data.RTIndex=0;	
				}
				
			}		
		}
		else
		{
			math_a=U2RXREG;
		}
		IFS1bits.U2RXIF=0;
}	

//void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void)
//{		
//	
//	static unsigned char *index;
//	unsigned int math_a;
//	
//	if(Ele_load_Data.RTIndex<Ele_load_Data.Index)
//	{
//		if(MOXA.RTIndex==1)index=&MOXA.Fuc;
//		U3TXREG=*index;
//		index++;
//		MOXA.RTIndex++;
//		for (math_a=0;math_a<=20;math_a++)
//		{
//			asm("Nop");
//		}	
//	}
//	else 
//	{
//		MOXA.RTIndex=0;
//		MOXA.Index=0;
//	}	
//
//	IFS5bits.U3TXIF=0;
//}


