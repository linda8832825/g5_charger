#include "Main_Define.h"

unsigned int CRC_Make(unsigned char *Buffer , unsigned char Quantity) //howmuch是有多少個!!  5格數字就填5    不是從0開始數
{
	unsigned int CRC_CODE=0xFFFF;
	unsigned char CRC_Length=0,i,*CRC_Address;	
	
	CRC_Address=Buffer;
	CRC_Length=Quantity;		

	while(CRC_Length--)
	{
		CRC_CODE^=*CRC_Address++;//先XOR完後再把地址+1
		for(i=0;i<8;i++)
		{
			if(CRC_CODE&0x01)//如果最後一個位元是1把CRC_CODE右移1位之後與0xA001做XOR
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
	