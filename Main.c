//###########################################################//
//    日期   : 2021.04.08                                    //
//    版本   : v1.0                                          //
//  更新紀錄 :                        //
//    作者   :                                   //
//###########################################################//

#include "Main_Define.h"

_CONFIG1( WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & BKBUG_ON & GWRP_OFF & GCP_OFF & JTAGEN_OFF  )
_CONFIG2( IESO_OFF & FNOSC_FRCPLL & FCKSM_CSDCMD & OSCIOFNC_OFF   )



void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void)
{
	INTCON1bits.OSCFAIL = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void)
{
	unsigned char math_a=1;
	INTCON1bits.ADDRERR = 	0;
	while(math_a);     
}

void __attribute__((interrupt, no_auto_psv))_StackError(void)
{
	INTCON1bits.STKERR = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _MathError(void)
{
	INTCON1bits.MATHERR = 0;
	while(1);     
}

IC_Data_Define IC_Data;
//IC_Data_IF IC_Data_Save_IF;


int main (void) 
{
    unsigned int    math_a=0; //計數資料要不到多少次
    unsigned int    math_b=0; //取現在的秒數
    unsigned int    math_c=0; //無法寫0.1安時進去的次數
    
	Initial_Clock(); 	
	IC_Data.ms=1000;
	
	//IC_Data.Wait_Coulomb_Read=0;
	
	
	//一些數值的初始化設定-----------------------------------------------
    IC_Data.GetTheWhatYouWant=NO;
    IC_Data.DoIamStarted=NO;
//	IC_Data.Wait_Coulomb_Read=1480;
//	IC_Data.Charge_Voltage_Avg=0;		
//	IC_Data.Charge_Voltage_Avg_Count=0;	
//    IC_Data.Return_ID=0x06;
	//--------------------------------------------------------------------


	         
	Initial_IO();
	Initial_G5_UART();
    Timer1_initial();
    I2C_Initial();

    
    BUZZ = BUZZ_ON;
    LED = Turn_ON;
    while(IC_Data.Second <1);
    BUZZ = BUZZ_OFF;
    LED = Turn_OFF;
    

//	Initial_Coulomb_UART();    
//	Initial_UART2();

		
    //寫入庫倫計--------------------------------------------------------
//    Unlock_Coulomb();
//    Write_Coulomb_Data(0x0009,0x01);//0x0009  標準電池容量 0.0~6553.5AH
//    while(!ModBus_Receiver.TIF);
//    ModBus_Receiver.TIF=0;		
    //----------------------------------------------------------------
    

    
	while(1)
	{
//                LCD_Init(DriverIC_I2C_LCD_Addr);
//    LCD_Clear();
//    LCD_Set_Cursor(1, 1);
//    LCD_Write_String(" 1");
	
    
        if(SW==SW_Push){    //如果啟動鈕被按下
            while(SW==SW_Push){//到按鈕被放開才會繼續做
                IC_Data.DoIamStarted = YES; //按鈕被按下過
                //然後在清空之前設的所有變數
                //要不要寫個函式高級些
            }
        }
            
        if(IC_Data.DoIamStarted == YES){
            if((G5_Get.RIF != 1) && (math_a<=3) && (IC_Data.GetTheWhatYouWant == NO)){//如果還沒收到資料
                BUZZ = BUZZ_ON;
                math_b=IC_Data.Second;
                while(math_b == IC_Data.Second);
                BUZZ = BUZZ_OFF;
                Read_ALL_G5_Data(); //跟G5要資料
                if(G5_Data.ID == My_ID){//有要到正確資料
                    IC_Data.GetTheWhatYouWant = YES;
                }
                else{// 沒有要到正確資料 就充電三十秒
                    math_a++;
                    IC_Data.Thirty_Second_Count=0;
                    POWER = Turn_ON;
                    while(IC_Data.Thirty_Second_Count==1);
                    POWER = Turn_OFF;
                }
            }
            else{//充電4次都沒辦法讓g5傳資料出來就
                IC_Data.GetTheWhatYouWant= NO; 
                BatteryError = Turn_ON; //battery燈亮 代表g5沒電了
                math_a = 0;
            }
            if(IC_Data.GetTheWhatYouWant == YES){//如果要到資料就放電到電流=0
                //放電
                while(G5_Data.Current > 0x00);
                //放電中止
                if(G5_Data.Residual_Electricity == 0x01){//確認是否為0.1Ah
                    IC_Data.WriteZeroAh = YES;
                }
                else{//沒有的話再寫一次///////////////////////////////
                    Write_G5_Data(0x07 , 0x01); //寫0.1Ah進去 01 06 00 07 00 01 crc
                    math_c++;
                }
                if(math_c>=3){
                    //寫入0.1安時失敗
                }
            }
                
                
    }
            
            
            

//            do
//            {	
//                G5_Receiver.IF = 0;
//                Read_ALL_G5_Data(); //跟G5要資料
//
////                Coulomb_Data.Read_Timer=500; ///////////////////////////////////////////////////
//                while(G5_Receiver.IF==0); //等待G5回應資料
//                math_b++;
//                if(math_b>1){
//                    math_c++; //計數充電次數
//                    //G5板子沒有通電 要先充電
//                    //叫電源供應器充電30秒
//                }
//                if(math_c >= read_G5_times_limt){ //充電次數高於設定值
//                    // lcd顯示battery error
//                    BUZZ = BUZZ_ON; // 蜂鳴器叫
//                        //過一段時間停掉
//                }
//            }while(G5_Receiver.ERRIF==1);
            
            
            
//            if(G5_Data.Voltage <= Discharge_Voltage){//如果電壓小於放電截止點 
//                G5_reset_work(); //reset安時數
//            }
//            else{
//                do{
//                     跟電子附載機通訊讓他放電到 Discharge_Voltage
//                
//                }while(G5_Data.Voltage <=  Discharge_Voltage);
//                G5_reset_work(); //reset安時數
//            }
            
            
            
            //讓LCD顯示------------------------------------------------------
//            LCD_Init(LCD_I2C_Addr<<1); // Initialize LCD module with I2C address = 01001110
//            LCD_Set_Cursor(1, 1);
//            LCD_Write_String(" 1");
            //--------------------------------------------------------------


            //電子附載機那邊接收到東西-------------------------------------------
//            if(ModBus_Receiver.RIF==1)
//            {
//                if(T4CONbits.TON==0)Timer4_initial(); //如果timer結束 就讓timer開始
//
//                ModBus_Receiver.ERR_Count=0;	//資料接收或傳送錯誤	
//
//                			
//                ModBus_Receiver.RIF=0;
//
//                if(U2STAbits.OERR)  while(U2STAbits.OERR) math_a=U2RXREG; //如果接收緩衝區溢出了//就把接收緩衝區清空
//            }
//            else if(ModBus_Receiver.ERRIF)   ModBus_Receiver.ERRIF=0; //資料接收或傳送錯誤	
            //-----------------------------------------------------------------
			
       
            //I2C--------------------------------------------------------------
//            if(!I2C_Data.Busy_IF) //如果要傳送的對象沒有忙碌中
//            {
//                if(EEPROM.Save_IF)
//                {
//                    Write_EEROM_information();
//                }
//            }	
            
            //-----------------------------------------------------------------
        		
        
    }
}
		