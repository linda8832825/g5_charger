#include "Main_Define.h"

unsigned int CRC_Make(unsigned char *Buffer , unsigned char Quantity) //howmuch�O���h�֭�!!  5��Ʀr�N��5    ���O�q0�}�l��
{
	unsigned int CRC_CODE=0xFFFF;
	unsigned char CRC_Length=0,i,*CRC_Address;	
	
	CRC_Address=Buffer;
	CRC_Length=Quantity;		

	while(CRC_Length--)
	{
		CRC_CODE^=*CRC_Address++;//��XOR����A��a�}+1
		for(i=0;i<8;i++)
		{
			if(CRC_CODE&0x01)//�p�G�̫�@�Ӧ줸�O1��CRC_CODE�k��1�줧��P0xA001��XOR
			{
				CRC_CODE=(CRC_CODE>>1)^0xA001;
			}
			else
			{
				CRC_CODE=(CRC_CODE>>1);
			}	
		}
	}
	return CRC_CODE;
	
}	
	