#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void) //讀完g5或寫完 收到的資料做整理
{
        unsigned char math_a,math_c,math_d;
        unsigned int 	math_b;
        unsigned int 	*index1;
        unsigned char   *index2, Quantity,*index3;

        unsigned char Erro_IF;

        index1=&G5_MOXA.ID;
        index3=&G5_MOXA.ID;
//        index2=&G5_Data.Current_Point; //第一個DATA放的位置

        Erro_IF=0;


        if((G5_MOXA.RTIndex>0) && (IC_Data.DoIamStarted == YES))
        {
            if(G5_MOXA.W_R == Read)
            {
                if(CRC_Check())
                {
                    G5_MOXA.Value_L=G5_MOXA.Reg_L;
                    G5_MOXA.Value_H=G5_MOXA.Reg_H;
                    index1=&G5_Data.ID;
                    *index1=G5_MOXA.ID;
                    index1+=2;
//                    index1=index1+(G5_MOXA.Value);	
                    //取得g5資料陣列從哪位置開始放資料

                    Quantity = G5_MOXA.Reg_H/2; //資料比數
                    index2=&G5_MOXA.Reg_L; //第一筆data
                    for(Quantity=Quantity;Quantity>0;Quantity--)
                    {
                        G5_MOXA.Value_H = *index2;
                        *index2++;
                        G5_MOXA.Value_L = *index2;
                        *index1 = G5_MOXA.Value; //把DATA放進G5的資料儲存陣列裡
                        index1++;
                        index2++;
                    }
                    G5_MOXA.RIF=1;
                    G5_MOXA.RTIndex=0;
                }
                else
                {
                    G5_MOXA.RTIndex=0;
                    G5_MOXA.ERRIF=1;
                }

            }
            else if(G5_MOXA.W_R == Write)
            {
                if(G5_MOXA.RTIndex==8)
                {
                    Erro_IF=0;
                    for(math_a=0;math_a<8;math_a++)
                    {
                        math_c = *index3; //收到的ID
                        if( math_c != My_ID )Erro_IF=1;
                        index3++;
                    }
                    if(Erro_IF)G5_MOXA.ERRIF=1;
                    else G5_MOXA.TIF=1;
                }		
                else
                {
                    G5_MOXA.ERRIF=1;	
                    G5_MOXA.RTIndex=0;
                }			
            }
        }	

        if(U3STAbits.OERR)
        {
            while(U3STAbits.OERR)
            {
                math_a=U3RXREG;
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
        if((G5_MOXA.RIF==0) && (IC_Data.DoIamStarted==YES))
		{
			TMR3=0;		
			if(!T3CONbits.TON)
			{
				T3CONbits.TON=1;
			}
			if(G5_MOXA.RTIndex==0)
			{
				index=&G5_MOXA.ID;
				*index=U3RXREG;
				index++;
				G5_MOXA.RTIndex++;	
				Fuction=0;
			}
			else
			{
				if(G5_MOXA.ID==My_ID||G5_MOXA.ID==0x00)
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


