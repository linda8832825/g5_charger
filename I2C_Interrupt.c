#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) 
{
    if(I2C_Data.TIF==0){
        if(!I2C1STATbits.BCL)//�`�u�Ĭ�
        {
            if(I2C1STATbits.S)//�����ǰe�L�{�A�Ϊ̱ҰʰT��
            {
                if(I2C_Data.R_W==I2C_read)//�P�_�O���OŪ�� //�@ ���S�Ψ�Ū���ҥH�����ק�
                {
  				

                }	
                if(I2C_Data.R_W==I2C_write) //�g�J
                {
                    I2C1TRN = I2C_Buffer;
                    I2C_Data.TIF=1; //��ƶǰe����                   

                }			
            }
            else if (I2C1STATbits.P)
            {
                I2C1CONbits.SEN = 1;
    //			if(I2C_Data.Device_Busy_IF)
    //			{
    //				I2CStat;				// �o�X�ҩl�줸		
    //				I2C_Data.Device_Busy_IF=0;
    //			}
    //			else
    //			{
    //				//�o�ּ̤g�@�ӡA�o�͵L�k���������m�ɭ�
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