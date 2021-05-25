//###########################################################//
//    日期   : 2021.05.06                                    //
//    版本   : v1.0                                          //
//  更新紀錄 :                        //
//    作者   :                                   //
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
//unsigned int FirstWriteLCD=1; //是否第一次寫入LCD
//unsigned int LcdWriteComplete=0; //LCD寫入完畢
unsigned int DisCharging=0;//是否開始放電
//IC_Data_IF IC_Data_Save_IF;


int main (void) 
{
    unsigned int    math_a=0; //計數資料要不到多少次
    unsigned int    math_b=0; //無法寫0.1安時進去的次數
    unsigned int    math_c=0; //無法寫滿安時進去的次數
//    unsigned int    math_d=0; //用在數秒數
//    unsigned int    math_e=0; //判斷要不要更新LCD
//    unsigned int    math_f=0; //100秒整個LCD頁面更新
    
  
    
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
	Initial_G5_UART();
    Initial_Ele_load_UART();
    Timer1_initial();
    I2C_Initial();
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
                IC_Data.DoIamStarted = YES; //按鈕被按下過
                BUZZ = BUZZ_ON;
                delay(1);
                BUZZ = BUZZ_OFF;
                //然後在清空之前設的所有變數
                //要不要寫個函式高級些
            }
        }
        //---------------------------------------------------------------------//
        
            
        //-----------------------------嘗試與G5連接-------------------------------//
        if(IC_Data.DoIamStarted == YES && IC_Data.GetTheWhatYouWant == NO ){ //啟動了且還沒拿到G5資料也還沒寫0安時
            if((G5_Get.RIF != 1) && (math_a<=3) && (IC_Data.GetTheWhatYouWant == NO)){//如果在四次內還沒收到資料
                Read_ALL_G5_Data(); //跟G5要資料
                delay(2);
                if(G5_Data.ID == My_ID){//有要到正確資料
                    POWER = StopCharge;
                    if(G5_Data.Residual_Electricity==0x00) {
                        Write_G5_Data(0x06,0x01); //將g5reset電壓點降低
                        delay(3);
                        Write_G5_Data(0x05,0x01); //將g5reset調回59.5v //此時剩餘電量會是0.1或0.2安時
                        delay(3);
                    }
                    if(G5_Data.x2!=0x0253){
                        Write_G5_Data(0x05,0x01); //將g5reset調回59.5v //此時剩餘電量會是0.1或0.2安時
                        delay(3);
                    }
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
            ShowG5DataOnLCD();
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
//                            else {
//                                Ele_load_Data.GoTo_Write_Ele_load=NO; //不需要再次寫入電子附載機 恢復timer1裡的讀取電子附載機
//                                DisCharging=YES;
//                            }
                        }
                        //-----------------------------------------------------------------------------------------//
                        
                        //---------------------------------停止放電------------------------------------------------//
                        else{
                            if(Ele_load_Data.End==0x1) {
                                Ele_load_Data.GoTo_Write_Ele_load=YES; //允許寫入電子附載機 讓timer1裡的讀電子附載機的動作停下來
                                Ele_load_Data.DisChargeDone=YES;
                                delayThirtySecond(); //因為g5斷電會重新啟動 那時候讀不到資料
                            }
                            if((G5_Data.Current == 0x00) && (G5_Data.Voltage <= Discharge_Voltage)){//放電完成
                                Ele_load_Data.DisChargeDone=YES;

                                if(Ele_load_Data.Buzzing!=0){//蜂鳴器叫了
                                    do{ WriteEleLoadState(0x01, 0x00);  delay(1); } while(Ele_load_Data.WriteIF==0);//停止
                                    do{ WriteEleLoadSetting(0x00, 0x00, BuzzMusicType); delay(1); } while(Ele_load_Data.WriteIF==0); //寫蜂鳴器響的音樂
                                    ReadAllEleLoadData();
                                    delay(1);
                                }
                                else Ele_load_Data.GoTo_Write_Ele_load=NO; //不需要再次寫入電子附載機 恢復timer1裡的讀取電子附載機


                                if(G5_Data.Residual_Electricity == 0x01){//確認是否為0.1Ah
                                    IC_Data.WriteZeroAh = YES; //寫入0.1安時數成功
                                    LCD_Clear();
                                    LCD_write_Char(1, 1 , "Write 0.1Ah To G5 complete");
                                }
                                else{//沒有的話再寫一次
                                    Write_G5_Data(0x07 , 0x01); //寫0.1Ah進去 01 06 00 07 00 01 crc
                                    math_b++;
                                }
                                if(math_b>=3){//寫入0.1安時失敗
                                    WriteError = Turn_ON;
                                    BUZZ = BUZZ_ON;
                                    delay(3);
                                    WriteError = Turn_OFF;
                                    LCD_Clear();
                                    LCD_write_Char(1, 1 , "Write Ah To G5 error occurred");
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
                if(delayThirtySecond()){
                    POWER = Charge;
                    if(G5_Data.Current <= Charge_Stop_Current){//充電完畢
                        
                        POWER = StopCharge;
                        if(G5_Data.Now_Total_Capacity == G5_Data.Residual_Electricity){//確認是否將現在的安時數寫到滿安時數
                            WriteWholeAh = YES; //寫入滿安時數成功
                            LCD_Clear();
                            LCD_write_Char(1, 1 , "Write Whole Ah To G5 complete");
                            IC_Data.DoIamStarted=NO; //不需要再進main做事了
                        }
                        else{//沒有的話再寫一次
                            Write_G5_Data(0x09 , 0x01); //跟G5說將現在的安時數寫到滿安時數 01 06 00 09 00 01 crc
                            math_c++;
                        }
                        if(math_c>=3){//寫入滿安時失敗
                            WriteError = Turn_ON;
                            BUZZ = BUZZ_ON;
                            delay(3);
                            WriteError = Turn_OFF;
                            LCD_Clear();
                            LCD_write_Char(1, 1 , "Write Whole Ah To G5 error occurred");
                        }

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