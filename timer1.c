#include "Main_Define.h"

void Timer1_initial(void)
{
	T1CON=0; 
	IEC0bits.T1IE=1; // TIMER���_���\�� 1=���\
	IFS0bits.T1IF=0; // TIMER���_�лx���A�� 0=�����줤�_
	T1CONbits.TCKPS=1;//1:8
	T1CONbits.TCS=0; //����clock (FOSC/2
	T1CONbits.TON=1; //���}TIMER�\��
	PR1=2000; //1���@�� �������D����
}
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void){


    
    //�ϥήɶ��p��		
    if(IC_Data.time.ms==0){
        IC_Data.time.ms=1000;
        if(IC_Data.time.Second==30){
            IC_Data.time.Thirty_Second_Count=~IC_Data.time.Thirty_Second_Count;
            IC_Data.time.Second=0;
        }
        else{
            IC_Data.time.Second++;
            if((IC_Data.time.Regual_Read_G5<=0) && (IC_Data.GetTheWhatYouWant == YES)){
                Read_ALL_G5_Data();     //��G5�n���
                if(G5_Data.ID == My_ID) IC_Data.GetTheWhatYouWant = YES;//���n�쥿�T���
                else IC_Data.GetTheWhatYouWant = NO;
                if((Ele_load_Data.GoTo_Write_Ele_load ==NO) && (IC_Data.time.Second %2 ==0) && (Ele_load_Data.Init!=1)){ 
                    ReadAllEleLoadData();   //�C����q�l�������n���
                }
            }
            else{
                IC_Data.time.Regual_Read_G5--;
            }
            
        }
    }
    else
    {
        IC_Data.time.ms--;
    }

    IFS0bits.T1IF=0; //�C�i�Ӥ@���n�⤤�_���A�k�������줤�_
}
