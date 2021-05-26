#include "Main_Define.h"

Ele_load_Data_define Ele_load_Data; 
Ele_load_Get_Data_struct_define Ele_load_Get;
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) //Ū���q�l������Ū�μg�� ���쪺��ư���z
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
                    //�O��04Ū����
                    Ele_load_Get.Value_L=Ele_load_Get.Reg_L;
                    Ele_load_Get.Value_H=Ele_load_Get.Reg_H;
                    index1=&Ele_load_Data.ID;
                    *index1=Ele_load_Get.ID;
                    index1++;
                    //���o�q�l��������ư}�C�q����m�}�l����

                    Quantity = Ele_load_Get.Reg_H/2; //��Ƥ��
                    index2=&Ele_load_Get.Reg_L; //�Ĥ@��data
                    for(Quantity=Quantity;Quantity>0;Quantity--)
                    {
                        Ele_load_Get.Value_H = *index2;
                        *index2++;
                        Ele_load_Get.Value_L = *index2;
                        *index1 = Ele_load_Get.Value; //��DATA��i�q�l������������x�s�}�C��
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
                    math_c = *index3; //���쪺ID
                    if( math_c != Ele_load_ID ) Erro_IF=1;
                    index3++;
                    
                    if(Erro_IF){
                        Ele_load_Data.WriteIF=0;//�g�J�q�l����������
                        Ele_load_Get.TIF=0;
                        Ele_load_Get.ERRIF=1;
                    }
                    else{
//                        Ele_load_Data.GoTo_Write_Ele_load=NO; //���ݭn�A���g�J�q�l������
                        Ele_load_Data.WriteIF=1;//�g�J�q�l���������\
                        Ele_load_Get.ERRIF=0;
                        Ele_load_Get.RTIndex=0;
                        Ele_load_Get.TIF=1;
                    }
                }
                else{
                    Ele_load_Data.WriteIF=0;//�g�J�q�l����������
                    Ele_load_Data.GoTo_Write_Ele_load=YES; //���b����g�J�R�O
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

        IFS0bits.T2IF=0;  //timer2���o�ͤ��_�ШD
}	

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void)
{		
		unsigned int math_a;
		static unsigned char *index;
		static unsigned char Fuction;
        if(Ele_load_Get.RIF==0)
		{
			TMR2=0;		
//			if(!T2CONbits.TON) //u2��������F��ɤ~�|��timer3�Ұ�
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