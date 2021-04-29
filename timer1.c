#include "Main_Define.h"

void Timer1_initial(void)
{
	T1CON=0; //timer1���_����
	IEC0bits.T1IE=1; // TIMER���_���\�� 1=���\
	IFS0bits.T1IF=0; // TIMER���_�лx���A�� 0=�����줤�_
	T1CONbits.TCKPS=1;//1:8
	T1CONbits.TCS=0; //����clock (FOSC/2
	T1CONbits.TON=1; //���}TIMER�\��
	PR1=2000; //1���@�� �������D����
}
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void){


    //�ϥήɶ��p��		
    if(IC_Data.ms==0){
        IC_Data.ms=1000;		

        if(IC_Data.Second==30){
            IC_Data.Thirty_Second_Count=1;
            IC_Data.Second=0;
        }
        else 	IC_Data.Second++;
    }
    else
    {
        IC_Data.ms--;
    }

    IFS0bits.T1IF=0; //�C�i�Ӥ@���n�⤤�_���A�k�������줤�_
}
