#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) 
{
    if(I2C_Data.TIF==0 && I2C1STATbits.TBF==0){ //���\�ǰe �� TxBuffer�ŤF
        if(!I2C1STATbits.BCL){ //�`�u�Ĭ�
            if(I2C1STATbits.S){ //�����ǰe�L�{�A�Ϊ̱ҰʰT��
//                if(I2C_Data.R_W==I2C_read){ }//�P�_�O���OŪ�� //�@ ���S�Ψ�Ū���ҥH�����ק�
                if(I2C_Data.R_W==I2C_write){ //�g�J
                    I2C1TRN = I2C_Buffer;
                    I2C_Data.TIF=1; //��ƶǰe����                 
                }			
            }
        }
    }
	IFS1bits.MI2C1IF=0;
} 