#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
	if(G5_MOXA.RTIndex>0) //如果已經收到資料了
	{
		if(G5_MOXA.Fuc==0x06) //寫入一筆資料
		{
			if(G5_MOXA.RTIndex==8)
			{
				G5_MOXA.RIF=1;
			}		
			else
			{
				G5_MOXA.ERRIF=1;	
				G5_MOXA.RTIndex=0;
			}							
		}
		else if(G5_MOXA.Fuc==0x03) //讀取多筆資料
		{
			if(G5_MOXA.RTIndex==8)
			{
				G5_MOXA.RIF=1;
			}		
			else
			{
				G5_MOXA.ERRIF=1;	
				G5_MOXA.RTIndex=0;
			}				
		}
		else if(G5_MOXA.Fuc==0x10) //寫入多筆資料
		{
			if (G5_MOXA.Index==G5_MOXA.RTIndex)
			{
				G5_MOXA.RIF=1;		
			}
			else
			{
				G5_MOXA.ERRIF=1;	
				G5_MOXA.RTIndex=0;
			}				
		}	
		else
		{
			G5_MOXA.ERRIF=1;	
			G5_MOXA.RTIndex=0;		
		}	
	
	}
	T3CONbits.TON=0; //第三個計時關閉
	IFS0bits.T3IF=0;  //timer3未發生中斷請求
			
}	

void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void)
{		
		unsigned int math_a;
		static unsigned char *index;
		static unsigned char Fuction;
		
		if(G5_MOXA.RIF==0)
		{
			TMR3=0;		
			if(!T3CONbits.TON)
			{
				T3CONbits.TON=1;
			}
			if(G5_MOXA.RTIndex==0)
			{
				index=&G5_Data.ID;
				*index=U3RXREG;
				index++;
				G5_MOXA.RTIndex++;	
				Fuction=0;
			}
			else
			{
				if(G5_Data.ID==My_ID||G5_Data.ID==0x00)
				{
					TMR3=0;
					*index=U3RXREG;
					G5_MOXA.RTIndex++;
					if(G5_MOXA.RTIndex==2&&*index==0x10)Fuction=*index;
					if(G5_MOXA.RTIndex==7&&Fuction==0x10)
					{
							G5_MOXA.Index=*index+9;
					}					
					index++;
				}	
				else
				{
					T3CONbits.TON=0;
					math_a=U3RXREG;
					G5_MOXA.RTIndex=0;	
				}
			}		
		}
		else
		{
			math_a=U3RXREG;
		}
		IFS5bits.U3RXIF=0;
}	

void __attribute__((interrupt, no_auto_psv)) _U3TXInterrupt(void)
{		
	
	static unsigned char *index;
	unsigned int math_a;
	
	if(G5_MOXA.RTIndex < G5_MOXA.Index)
	{
		if(G5_MOXA.RTIndex==1)index=&G5_MOXA.Fuc;
		U3TXREG=*index;
		index++;
		G5_MOXA.RTIndex++;
		for (math_a=0;math_a<=20;math_a++)
		{
			asm("Nop");
		}	
	}
	else 
	{
		G5_MOXA.RTIndex=0;
		G5_MOXA.Index=0;
	}	

	IFS5bits.U3TXIF=0;
}


