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

unsigned int CRC_Check(void) //howmuch是有多少個!!  5格數字就填5    不是從0開始數
{
	unsigned int CRC_CODE=0xFFFF,math_a,math_b;
	unsigned char CRC_Length=0,i,*CRC_Address;
	


	CRC_Address=&G5_Get.ID;
	CRC_Length=G5_Get.RTIndex-2;	
	
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
		

	CRC_Address=&G5_Get.ID;
	CRC_Address+=G5_Get.RTIndex-2;	

	
	math_a=*CRC_Address;
	math_a=math_a<<8;
	CRC_Address++;
	math_a=math_a|(*CRC_Address);
	
	//因為當初寫錯了其實CRC應該是先L 在H 可是寫反了 所以 變成先H在L 或者先L在H 都可以
	math_b=*CRC_Address;
	math_b=math_b<<8;
	CRC_Address--;
	math_b=math_b|(*CRC_Address);
	
	if (CRC_CODE == math_a || CRC_CODE == math_b)//當CRC確認之後 將資料重新整理
	{
		return 1;	
	}
	else 
	{
		return 0;
	}	
	
}
unsigned int CRC_Check_Ele_load(void) //howmuch是有多少個!!  5格數字就填5    不是從0開始數
{
	unsigned int CRC_CODE=0xFFFF,math_a,math_b;
	unsigned char CRC_Length=0,i,*CRC_Address;
	


	CRC_Address=&Ele_load_Get.ID;
	CRC_Length=Ele_load_Get.RTIndex-2;	
	
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
		

	CRC_Address=&Ele_load_Get.ID;
	CRC_Address+=Ele_load_Get.RTIndex-2;	

	
	math_a=*CRC_Address;
	math_a=math_a<<8;
	CRC_Address++;
	math_a=math_a|(*CRC_Address);
	
	//因為當初寫錯了其實CRC應該是先L 在H 可是寫反了 所以 變成先H在L 或者先L在H 都可以
	math_b=*CRC_Address;
	math_b=math_b<<8;
	CRC_Address--;
	math_b=math_b|(*CRC_Address);
	
	if (CRC_CODE == math_a || CRC_CODE == math_b)//當CRC確認之後 將資料重新整理
	{
		return 1;	
	}
	else 
	{
		return 0;
	}	
	
}
	
void delayms(unsigned int i){
    unsigned int math_a,math_b;
    math_b=i;
    math_a=IC_Data.time.ms;
    while((math_a - IC_Data.time.ms) < math_b);
    math_b=0;
}

void delay (unsigned char i){
    unsigned 	char math_a,math_b;
    math_b=i;
    math_a=IC_Data.time.Second;
    if(math_a>=(0x1F-math_b)) math_a=0x00; //如果剛好取到第30秒就 歸到0
    while((IC_Data.time.Second - math_a) < math_b);
}
unsigned char delayThirtySecond(void){
    unsigned 	char math_a, math_b;

    if(math_a==0){
        math_b=1;
        IC_Data.time.Second=0;//時間歸0
        math_b=IC_Data.time.Thirty_Second_Count;
    }
    else{
        if(math_b!=IC_Data.time.Thirty_Second_Count) {
            return 1;
        }
        else return 0;
    }
}