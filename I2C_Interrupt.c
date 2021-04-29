#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) 
{
    if(I2C_Data.TIF==0 && I2C1STATbits.TBF==0){ //允許傳送 跟 TxBuffer空了
        if(!I2C1STATbits.BCL){ //總線衝突
            if(I2C1STATbits.S){ //接收傳送過程，或者啟動訊號
//                if(I2C_Data.R_W==I2C_read){ }//判斷是不是讀取 //一 為沒用到讀取所以先不修改
                if(I2C_Data.R_W==I2C_write){ //寫入
                    I2C1TRN = I2C_Buffer;
                    I2C_Data.TIF=1; //資料傳送完成                 
                }			
            }
        }
    }
	IFS1bits.MI2C1IF=0;
} 