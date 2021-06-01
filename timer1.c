#include "Main_Define.h"

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
                Read_ALL_Coulomb_Data(); //跟庫倫計要資料
                SortUserData();//整理user資料
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
