#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) 
{
    if(I2C_Data.TIF==0){
        if(!I2C1STATbits.BCL)//總線衝突
        {
            if(I2C1STATbits.S)//接收傳送過程，或者啟動訊號
            {
                if(I2C_Data.R_W==I2C_read)//判斷是不是讀取 //一 為沒用到讀取所以先不修改
                {
  				

                }	
                if(I2C_Data.R_W==I2C_write) //寫入
                {
                    I2C1TRN = I2C_Buffer;
                    I2C_Data.TIF=1; //資料傳送完成                   

                }			
            }
            else if (I2C1STATbits.P)
            {
                I2C1CONbits.SEN = 1;
    //			if(I2C_Data.Device_Busy_IF)
    //			{
    //				I2CStat;				// 發出啟始位元		
    //				I2C_Data.Device_Busy_IF=0;
    //			}
    //			else
    //			{
    //				//這裡少寫一個，發生無法偵測到對方位置時候
    //				if(I2C_Data.Data_R_W==Comand_read)
    //				{
    //					I2C_Data.RIF = 1;
    //				}
    //				else 
    //				{
    //					I2C_Data.TIF = 1;
    //				}				
    //			}
            }

        }
        else
        {
            I2C1CONbits.PEN = 1;
        }
    }
	IFS1bits.MI2C1IF=0;
} 