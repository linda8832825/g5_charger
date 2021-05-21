#include "Main_Define.h"

void Timer1_initial(void)
{
	T1CON=0; 
	IEC0bits.T1IE=1; // TIMER中斷允許位 1=允許
	IFS0bits.T1IF=0; // TIMER中斷標誌狀態位 0=未受到中斷
	T1CONbits.TCKPS=1;//1:8
	T1CONbits.TCS=0; //內部clock (FOSC/2
	T1CONbits.TON=1; //打開TIMER功能
	PR1=2000; //1秒做一次 但不知道公式
}
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void){


    
    //使用時間計時		
    if(IC_Data.time.ms==0){
        IC_Data.time.ms=1000;
        if(IC_Data.time.Second==30){
            IC_Data.time.Thirty_Second_Count=~IC_Data.time.Thirty_Second_Count;
            IC_Data.time.Second=0;
        }
        else{
            IC_Data.time.Second++;
            if((IC_Data.time.Regual_Read_G5<=0) && (IC_Data.GetTheWhatYouWant == YES)){
                Read_ALL_G5_Data();     //跟G5要資料
                if(G5_Data.ID == My_ID) IC_Data.GetTheWhatYouWant = YES;//有要到正確資料
                else IC_Data.GetTheWhatYouWant = NO;
                if((Ele_load_Data.GoTo_Write_Ele_load ==NO) && (IC_Data.time.Second %2 ==0) && (Ele_load_Data.Init!=1)){ 
                    ReadAllEleLoadData();   //每兩秒跟電子附載機要資料
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

    IFS0bits.T1IF=0; //每進來一次要把中斷狀態歸為未受到中斷
}
