//###########################################################//
//    日期   : 2021.05.28                                    //
//    版本   : v1.0                                          //
//  更新紀錄 : G5充電器reset安時                             //
//    作者   : linda                                         //
//###########################################################//

#include "Main_Define.h"

_CONFIG1( WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & BKBUG_ON & GWRP_OFF & GCP_OFF & JTAGEN_OFF  )
_CONFIG2( IESO_OFF & FNOSC_FRCPLL & FCKSM_CSDCMD & OSCIOFNC_OFF   )



void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void){
	INTCON1bits.OSCFAIL = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void){
	unsigned char math_a=1;
	INTCON1bits.ADDRERR = 	0;
	while(math_a);     
}

void __attribute__((interrupt, no_auto_psv))_StackError(void){
	INTCON1bits.STKERR = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _MathError(void){
	INTCON1bits.MATHERR = 0;
	while(1);     
}

IC_Data_Define IC_Data;
unsigned int WriteWholeAh=0; //是否寫入滿安時數
unsigned int DisCharging=0;//是否開始放電


int main (void) 
{
    unsigned int    math_a=0; //計數資料要不到多少次
    unsigned int    math_b=0; //無法寫0.1安時進去的次數
    unsigned int    math_c=0; //無法寫滿安時進去的次數
    unsigned int    math_d=0; //放庫論計是否設好初始值的結果
    
  
    
	Initial_Clock(); 	
	
	//一些數值的初始化設定-----------------------------------------------
    IC_Data.time.ms=1000;
    IC_Data.time.Regual_Read_G5=120;//20秒後才能常態與g5通訊
    IC_Data.GetTheWhatYouWant=NO;
    IC_Data.DoIamStarted=NO;
    IC_Data.WriteZeroAh=NO;
    Ele_load_Data.GoTo_Write_Ele_load=NO;
    Ele_load_Data.WriteIF=0; //寫入電子附載機失敗
    Ele_load_Data.Init=0;
    Ele_load_Data.DisChargeDone=NO;
	//--------------------------------------------------------------------
     
	Initial_IO();
    Initial_Coulomb_UART();
    Initial_Ele_load_UART();
	Initial_G5_UART();
    Initial_Timer1();
    Initial_I2C();
    LCD_Init(DriverIC_I2C_LCD_Addr);
    
    
    BUZZ = BUZZ_ON;
    LED = Turn_ON;
    delay(1);
    BUZZ = BUZZ_OFF;
    LED = Turn_OFF;
    delay(3);
	LCD_write_Char(1, 1 , " iNer");
    LCD_write_Char(2, 1 , " iNer");
    LCD_write_Char(3, 1 , " iNer");
    LCD_write_Char(4, 1 , " iNer");
 
	while(1)
	{
        //------------------------------啟動-----------------------------------//
        if(SW==SW_Push){    //如果啟動鈕被按下
            while(SW==SW_Push){//到按鈕被放開才會繼續做
                Initial_Variable(); //變數初始化
                IC_Data.DoIamStarted = YES; //按鈕被按下過
                BUZZ = BUZZ_ON;
                delay(1);
                BUZZ = BUZZ_OFF;
            }
        }
        //---------------------------------------------------------------------//
        
            
        //-----------------------------嘗試與G5連接-------------------------------//
        if(IC_Data.DoIamStarted == YES && IC_Data.GetTheWhatYouWant == NO ){ //啟動了且還沒拿到G5資料
            if((G5_Get.RIF != 1) && (math_a<=3) && (IC_Data.GetTheWhatYouWant == NO)){//如果在四次內還沒收到資料
                Read_ALL_G5_Data(); //跟G5要資料
                delay(1);
                Read_ALL_Coulomb_Data(); //跟庫倫計要資料
                delay(1);
                math_d=Prevention_Zero_Ah();
                
                if((G5_Data.ID == My_ID) && (Coulomb_Data.ID == Coulomb_ID) && math_d){//有要到正確資料
                    POWER = StopCharge;
                    do{Write_G5_Data(0x05,0x01F4); delay(3); Read_ALL_G5_Data(); G5_Get.RIF=0; delay(2);}while(G5_Data.Nominal_Battery_Capacity!=0x01F4); //將滿安時數改成50ah
                    do{Write_G5_Data(0x06,0x0190); delay(3); Read_ALL_G5_Data(); G5_Get.RIF=0; delay(2);}while(G5_Data.x2!=0x0190);//將g5reset電壓點降成40v    //此時目前安時數會為52.5ah
                    do{Write_G5_Data(0x06,0x0253); delay(3); Read_ALL_G5_Data(); G5_Get.RIF=0; delay(2);}while(G5_Data.x2!=0x0253);//將g5reset電壓點改回59.5v  //此時目前安時數會為52.5ah
                    IC_Data.GetTheWhatYouWant = YES;
                    IC_Data.time.Regual_Read_G5=0; //之後可以常態的與G5通訊
                    math_a=0;
                }
                else{// 沒有要到正確資料 就充電三十秒
                    if(delayThirtySecond()==0){
                        POWER = Charge;
                        LCD_Clear();
                        delay(1);
                        LCD_write_Char(1, 1 , "Charging");
                    }
                    else{
                        POWER = StopCharge;
                        math_a++;
                        LCD_Clear();
                        delay(1);
                        if(math_a>3){//充電4次都沒辦法讓g5傳資料出來就宣告失敗
                            POWER = StopCharge;
                            IC_Data.GetTheWhatYouWant= NO; 
                            IC_Data.DoIamStarted = NO; //等待啟動鈕再被按下
                            BUZZ = BUZZ_ON;
                            BatteryError = Turn_ON; //battery燈亮 代表g5沒電了
                            WriteError = Turn_OFF;
                            LCD_Clear();
                            delay(1);
                            LCD_write_Char(1, 1 , "Connection To G5 error occurred");
                            math_a = 0;
                        }
                    }
                }
                
            }
        }
        //----------------------------------------------------------------------------//
        
        
        //-----------------------------已與G5連接-----------------------------------//
        if(IC_Data.GetTheWhatYouWant == YES){//如果要到資料就放電到電流=0
            //---------------------顯示g5資料-----------------------------------//
            ShowG5DataOnLCD(0);
            //-----------------------------------------------------------------//

            //----------------------------放電---------------------------------//
            if(IC_Data.WriteZeroAh == NO){//寫入0.1AH尚未成功

                if(Ele_load_Data.ID == Ele_load_ID){ //如果讀到電子附載機的資料是正確的

                    //-----------------------------------設定電子附載機-----------------------------------------//
                    if(Ele_load_Data.Init!=2) Set_Ele_load();
                    //------------------------------------------------------------------------------------------//
                    else{
                        //----------------------------------放電-----------------------------------------------------//
                        if((Ele_load_Data.DisChargeDone==NO) && (DisCharging!=YES)){
                            if(Ele_load_Data.DisCharge==0x0){
                                do{ WriteEleLoadState(0x00, 0xFF); delay(1); } while(Ele_load_Data.WriteIF==0);//放電
                                ReadAllEleLoadData();
                                delay(1);
                                if(Ele_load_Data.DisCharge==0x1) {
                                    DisCharging=YES;
                                    Ele_load_Data.GoTo_Write_Ele_load=NO; //不需要再次寫入電子附載機 恢復timer1裡的讀取電子附載機
                                }
                            }
                        }
                        //-----------------------------------------------------------------------------------------//
                        
                        //---------------------------------停止放電------------------------------------------------//
                        else{
                            
                            if(Ele_load_Data.Buzzing!=0){//蜂鳴器叫了
                                IC_Data.time.Regual_Read_G5=500;//g5關機的時候不要傳
                                
                                do{ WriteEleLoadState(0x01, 0x00);  delay(1); } while(Ele_load_Data.WriteIF==0);//停止
                                do{ WriteEleLoadSetting(0x00, 0x00, BuzzMusicType); delay(1); } while(Ele_load_Data.WriteIF==0); //寫蜂鳴器響的音樂
                                ReadAllEleLoadData();
                                delay(2);
                                if(Ele_load_Data.Buzzing==0) {
                                    POWER=Charge; 
                                    delay(20); 
                                    G5_Data.ID=0x00;
                                    do{ Read_ALL_G5_Data(); delay(1); }while(G5_Data.ID!=0x01);//跟G5要資料 
                                    POWER=StopCharge;
                                    Ele_load_Data.DisChargeDone=YES;
                                }
                                
                            }
                            else Ele_load_Data.GoTo_Write_Ele_load=NO; //不需要再次寫入電子附載機 恢復timer1裡的讀取電子附載機
                            
                            if(Ele_load_Data.DisChargeDone==YES){

                                do{Write_G5_Data(0x06,0x0190); delay(3); Read_ALL_G5_Data(); delay(2); G5_Get.RIF=0; delay(1);}while(G5_Data.x2!=0x0190);//將g5reset電壓點降成40v    //此時目前安時數會為52.5ah
                                do{Write_G5_Data(0x06,0x0253); delay(3); Read_ALL_G5_Data(); delay(2); G5_Get.RIF=0; delay(1);}while(G5_Data.x2!=0x0253);//將g5reset電壓點改回59.5v  //此時目前安時數會為52.5ah
                                
                                if((G5_Data.Current == 0x00) && (G5_Data.Voltage <= Discharge_Voltage)){//放電完成
                                    Ele_load_Data.DisChargeDone=YES;

                                    do{Write_G5_Data(0x07,0x02); delay(3); Read_ALL_G5_Data(); delay(2); G5_Get.RIF=0; delay(1); }while(G5_Data.Residual_Electricity>0x0002);//寫0.2Ah進去 01 06 00 07 00 02 crc
                                    
                                    if(G5_Data.Residual_Electricity <= 0x0002){//確認是否為0.1或0.2Ah
                                        IC_Data.WriteZeroAh = YES; //寫入0.2安時數成功
                                        math_b=0;
                                        BUZZ = BUZZ_ON;
                                        delay(5);
                                        BUZZ = BUZZ_OFF;
                                        LCD_Init(DriverIC_I2C_LCD_Addr);
                                        delay(2);
                                        LCD_write_Char(1, 1 , "Write 0.2Ah To G5 complete");
                                        Ele_load_Data.GoTo_Write_Ele_load=YES;//不需要再跟電子附載機通訊了
                                        IC_Data.time.Regual_Read_G5=0;//恢復每秒讀g5
                                        
                                    }
                                    else{//沒有的話再寫一次
                                        math_b++;
                                    }
                                    if(math_b>=5){//寫入0.1安時失敗
                                        WriteError = Turn_ON;
                                        BUZZ = BUZZ_ON;
                                        delay(3);
//                                        WriteError = Turn_OFF;
                                        LCD_Init(DriverIC_I2C_LCD_Addr);
                                        delay(2);
                                        LCD_write_Char(1, 1 , "Write Ah To G5 error occurred");
                                        delay(5);
                                    }
                                }
                            }
                            
                        }
                        //-----------------------------------------------------------------------------------------------//
                    }
                }
            }
            //-----------------------------------------------------------------//

            //-----------------------------充電--------------------------------//
            if(IC_Data.WriteZeroAh == YES){//寫好0.1安時後開始充電
                    POWER = Charge;
//                    ShowG5DataOnLCD(1);
                    if((G5_Data.Current <= Charge_Stop_Current) && (G5_Data.Voltage>Discharge_Voltage)){//充電完畢
                        
                        POWER = StopCharge;
                        
                        do{Write_G5_Data(0x09 , Coulomb_Data.Residual_Electricity); delay(3); Read_ALL_G5_Data(); G5_Get.RIF=0; delay(2); }while(G5_Data.Now_Total_Capacity != Coulomb_Data.Residual_Electricity);//跟G5說將現在的安時數寫到滿安時數 01 06 00 09 00 01 crc
                        
                        if(G5_Data.Now_Total_Capacity == G5_Data.Residual_Electricity){//確認是否將現在的安時數寫到滿安時數
                            WriteWholeAh = YES; //寫入滿安時數成功
                            BUZZ = BUZZ_ON;
                            delay(5);
                            BUZZ = BUZZ_OFF;
                            LCD_Init(DriverIC_I2C_LCD_Addr);
                            delay(2);
                            LCD_write_Char(1, 1 , "Write Whole Ah To G5 complete");
                            IC_Data.DoIamStarted=NO; //不需要再進main做事了
                        }
                        else{//沒有的話再寫一次
                            math_c++;
                        }
                        if(math_c>=3){//寫入滿安時失敗
                            WriteError = Turn_ON;
                            BUZZ = BUZZ_ON;
                            delay(3);
                            WriteError = Turn_OFF;
                            LCD_Init(DriverIC_I2C_LCD_Addr);
                            delay(2);
                            LCD_write_Char(1, 1 , "Write Whole Ah To G5 error occurred");
                        }

                    }
                //------------------------------------------------------------------//
            }
        }
        //----------------------------------------------------------------------//        
            
        //---------------------------接收G5資料---------------------------------//
        if(G5_Get.RIF) G5_Get.RIF=0;
        //----------------------------------------------------------------------//  
        
        //---------------------------接收電子附載機資料---------------------------------//
        if(Ele_load_Get.RIF) Ele_load_Get.RIF=0;
     	//----------------------------------------------------------------------//	
      }
    return 1;
}    	