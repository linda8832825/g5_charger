#include "Main_Define.h"

void Timer1_initial(void)
{
	T1CON=0; //timer1中斷智能
	IEC0bits.T1IE=1; // TIMER中斷允許位 1=允許
	IFS0bits.T1IF=0; // TIMER中斷標誌狀態位 0=未受到中斷
	T1CONbits.TCKPS=1;//1:8
	T1CONbits.TCS=0; //內部clock (FOSC/2
	T1CONbits.TON=1; //打開TIMER功能
	PR1=2000; //1秒做一次 但不知道公式
}
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void){


    //使用時間計時		
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

    IFS0bits.T1IF=0; //每進來一次要把中斷狀態歸為未受到中斷
}
