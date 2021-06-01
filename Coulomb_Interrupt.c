#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{	
	unsigned char math_a,math_c,math_d;
	unsigned int 	math_b;
	unsigned int 	*index1;
	unsigned char *index2,Quantity,*index3;
	
	unsigned char Erro_IF;
	
	index1=&Coulomb_Sent.ID;
	index3=&Coulomb_Sent.ID;
	index2=&Coulomb_Receiver.ID;
	
	Erro_IF=0;
	
//	IC_Data.Coulomb_No_Reback = Coulomb_No_Reback_Time;//�w�ۭp���ɭp�ɾ����p�ɴ_�k
	if(Coulomb_Receiver.RTIndex>0)
	{
		if(Coulomb_Sent.W_R == Read)
		{
			if(CRC_Check(&Coulomb_Receiver.ID, Coulomb_Receiver.RTIndex))
			{
//				IC_Data.Coulomb_No_Reback=0;	//�T�w��ƥ��T�������w�ۭp���ɭp�ɾ�
				Coulomb_Receiver.ERR_Count=0;
				Coulomb_Receiver.Value_L=Coulomb_Sent.Reg_L;
				Coulomb_Receiver.Value_H=Coulomb_Sent.Reg_H;
				index1=&Coulomb_Data.ID;
				index1=index1+(Coulomb_Receiver.Value);	
				//���o�w�۸�ư}�C�q����m�}�l����
							
				Quantity = Coulomb_Receiver.Reg_H/2;
				index2=&Coulomb_Receiver.Reg_L;
				for(Quantity=Quantity;Quantity>0;Quantity--)
				{
					Coulomb_Receiver.Value_H = *index2;
					*index2++;
					Coulomb_Receiver.Value_L = *index2;
					*index1 = Coulomb_Receiver.Value;
					index1++;
					index2++;
				}
				Coulomb_Receiver.RIF=1;
				Coulomb_Receiver.BusyIF=0;
				Coulomb_Receiver.RTIndex=0;
			}
			else
			{
				Coulomb_Receiver.RTIndex=0;
				Coulomb_Receiver.ERRIF=1;
				Coulomb_Receiver.BusyIF=0;
			}
			
		}
		else if(Coulomb_Sent.W_R == Write)
		{
			if(Coulomb_Receiver.RTIndex==8)
			{
				Erro_IF=0;
				for(math_a=0;math_a<8;math_a++)
				{
					math_c = *index3;
					math_d = *index2;
					if( 	math_c != math_d )Erro_IF=1;
					index3++;
					index2++;
				}
				if(Erro_IF)Coulomb_Receiver.ERRIF=1;
				else Coulomb_Receiver.TIF=1;
				Coulomb_Receiver.BusyIF=0;
			}		
			else
			{
				Coulomb_Receiver.ERRIF=1;	
				Coulomb_Sent.RTIndex=0;
				Coulomb_Receiver.BusyIF=0;
			}			
		}
	}	

	if(U1STAbits.OERR)
	{
		while(U1STAbits.OERR)
		{
			math_a=U1RXREG;
		}
	}
	T4CONbits.TON=0;	
	IFS1bits.T4IF=0;
}	

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{		unsigned int math_a;
		static unsigned char *index;
		static unsigned char Data_Statue;   //1=Master_Command  2=Slaver_return;	
		
		TMR4=0;		
		if(!T4CONbits.TON)
		{
			T4CONbits.TON=1;
		}
		if(Coulomb_Receiver.RTIndex==0)
		{
			index=&Coulomb_Receiver.ID;
			*index=U1RXREG;
			index++;
			Coulomb_Receiver.RTIndex++;	
		}
		else
		{
			TMR4=0;
			math_a=sizeof(Coulomb_Receiver);
			if(Coulomb_Receiver.RTIndex<math_a)
			{
				*index=U1RXREG;
				index++;
				Coulomb_Receiver.RTIndex++;			
			}
			else
			{
				*index=U1RXREG;
				Coulomb_Receiver.RTIndex=0;
			}

			
		}		
		IFS0bits.U1RXIF = 0;		// Clear Interrupt flag11
}	
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
	static unsigned char *index;
	unsigned int math_a;
	
	if(Coulomb_Sent.RTIndex<Coulomb_Sent.Index)
	{
		if(Coulomb_Sent.RTIndex==1)index=&Coulomb_Sent.Fuc;
		while(!U1STAbits.UTXBF && Coulomb_Sent.RTIndex < Coulomb_Sent.Index)
		{
			U1TXREG=*index;
			index++;
			Coulomb_Sent.RTIndex++;
		}	
	}
	else 
	{
		Coulomb_Sent.RTIndex=0;
		Coulomb_Sent.Index=0;
	}		
	IFS0bits.U1TXIF = 0;		// Clear Interrupt flag11
}