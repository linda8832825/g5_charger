#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) 
{
	if(!I2C1STATbits.BCL)//�`�u�Ĭ�
	{
		if(I2C1STATbits.S)//�����ǰe�L�{�A�Ϊ̱ҰʰT��
		{
			if(I2C_Data.R_W==I2C_read)//�P�_�O���OŪ�� //�@ ���S�Ψ�Ū���ҥH�����ק�
			{
//				if(I2C_Data.Address_IF || I2C_Data.ASK_IF)//���W�@�Ӱʧ@�O�ǰe��m��ƩΪ�ASK�A�p�G�O��m�N��n�}�l�Ĥ@�Ӹ��Ū��
//				{//�p�G�O�ǰe��ASK�T���A�h�}�l�U�@�Ӹ�Ʊ���
//					if(I2C_Data.RTIndex < (I2C_Data.Index1 + I2C_Data.Index2))//�����쪺��Ƽƶq�O�_��ݭn����Ƽƶq�ۦP
//					{	
//						I2C1CONbits.RCEN = 1;
//						I2C_Data.RCEN_IF = 1;//�]�w�{�b�ʧ@�O����
//						I2C_Data.ASK_IF = 0;
//						I2C_Data.Address_IF = 0;
//					}
//					else if(I2C_Data.RTIndex > (I2C_Data.Index1+I2C_Data.Index2))//�����D!
//					{
//						while(1);
//					}
//					else//��������
//					{
//							I2C1CONbits.PEN = 1;	
//							I2C_Data.Address_IF = 0;
//							I2C_Data.ASK_IF = 0;
//							I2C_Data.Busy_IF=0;
//					}						
//				}
//				else if(I2C_Data.RCEN_IF)//���W�@�Ӱʧ@�O�Ұʱ����\��A�A�ӭn��˸m�ݶǰeASK�T���Ϊ�NASK�T��
//				{
//					*I2C_Buffer_index=I2C1RCV;
//					I2C_Buffer_index++;
//					I2C_Data.RTIndex++;
//					if(I2C_Data.RTIndex==I2C_Data.Index1 + I2C_Data.Index2)I2C1CONbits.ACKDT = 1;
//					else I2C1CONbits.ACKDT = 0;
//					I2C1CONbits.ACKEN = 1;
//					I2C_Data.ASK_IF = 1;//�]�w�{�b�ʧ@�OASK�άONASK
//					I2C_Data.RCEN_IF = 0;
//					
//				}					
				
			}	
			else //�g�J
			{
                I2C1TRN = I2C_Buffer_index;
                
//				if(I2C_Data.RStart_IF==0)//��誺�ҰʰT���A�O���ƱҰ��٬O�@��Ұ�
//				{
//					if(I2C_Data.RTIndex==I2C_Data.Index1 && I2C_Data.Data_R_W==Comand_read)//�p�G�OŪ�� �P�_�O���O�ĤT�Ӹ�ƶǧ�(����m1+��Ʀ�m2) �p�G�ǧ��N�|���s�Ұ�
//					{
//						I2C1CONbits.RSEN = 1;
//						I2C_Data.RStart_IF=1;					
//					}
//					else if (I2C_Data.RTIndex == I2C_Data.Index1 + I2C_Data.Index2)//��p�G�O�g�J���� �N���Ƥw�g�g���F
//					{
//						I2C1CONbits.PEN = 1;	
//						I2C_Data.RTIndex=0;	
//						I2C_Data.Busy_IF=0;						
//					}	
//					else if (I2C_Data.RTIndex > (I2C_Data.Index1 + I2C_Data.Index2))//�����D!
//					{
//						while(1);						
//					}		
//					else //��p�G�O�g�J���� �N�|�@���g �i�O�p�G�OŪ�� �ĤT�Ӹ�ƶǧ�(����m1+��Ʀ�m2) �o��N���|�i��
//					{
//						if(I2C_Data.RTIndex==1 && I2C1STATbits.ACKSTAT==1)//�]��EEPROM�g�J�ݭn�j��5ms�ɶ�  �b�o�����A�n���չ��O�_����
//						{//�u�ण�_��"�Ұ�(S)" �ǰe"��m(address)"�T���A�T�{��観ask��nask nask���ܴN�n�ǰe"����(P)" ����A"�Ұ�(S)"
//							I2C_Buffer_index--;				
//							I2C_Data.RTIndex--;				
//							I2C_Data.Device_Busy_IF=1;
//							I2C1CONbits.PEN = 1;			
//						}
//						else
//						{
//							I2C1TRN = *I2C_Buffer_index;
//							I2C_Buffer_index++;//���Ʀ�m+1
//							I2C_Data.RTIndex++;//��p�ƾ�+1
//							if(I2C_Data.RTIndex == I2C_Data.Index1 && I2C_Data.Data_R_W==Comand_write)
//							{
//								I2C_Buffer_index=(unsigned char *)I2C_Data.Data_Addr;
//							}
//						}
//					}										
//				}
//				else //�w�g�ǰe�����s�Ұ� �n�A�ǰe�@�����Address �åB�N�ۤv�]�w��Address�X�г]1
//				{
//					I2C_Data.R_W = 			Comand_read;
//					I2C_Buffer_index = (unsigned char *)I2C_Data.Data_Addr;
//					I2C1TRN = I2C_Data.Address;
//					I2C_Data.Address_IF=1;
//				}
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
	IFS1bits.MI2C1IF=0;
} 