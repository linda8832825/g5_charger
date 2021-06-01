#include "Main_Define.h"
unsigned char math_DelayThirtySecond_a=0; //用在紀錄是否第一次進到delay30秒區
unsigned char math_DelayThirtySecond_b=0; //用在紀錄delay30秒區的IC_Data.time.Thirty_Second_Count

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

unsigned int CRC_Check(unsigned char* crc_address, unsigned char crc_length) //howmuch是有多少個!!  5格數字就填5    不是從0開始數
{
	unsigned int CRC_CODE=0xFFFF,math_a,math_b;
	unsigned char CRC_Length=0,i,*CRC_Address;
	


	CRC_Address=crc_address;
	CRC_Length=crc_length-2;	
	
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
		

	CRC_Address=crc_address;
	CRC_Address+=crc_length-2;	

	
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
    unsigned int math_a,math_b,math_c;
    math_b=i;
    math_a=IC_Data.time.ms;
    if(math_a>=math_b)  while((math_a - IC_Data.time.ms) < math_b);//夠扣
    else {//不夠扣
        math_c=math_b-math_a;//計算直到0毫秒前夠不夠扣完delay毫秒數
        while(IC_Data.time.ms > (0x03E8-math_c));
    }
}

void delay (unsigned char i){
    unsigned 	char math_a,math_b,math_c,math_d;
    math_d=0x1E;//30秒
    math_b=i;
    math_a=IC_Data.time.Second;
    if((math_d-math_a)>=math_b) while((IC_Data.time.Second - math_a) < math_b); //夠扣
    else{ //不夠扣
        math_c=math_b-(math_d-math_a);
        while(IC_Data.time.Second<math_c);
    }
}

unsigned char delayThirtySecond(void){

    if(math_DelayThirtySecond_a==0){
        math_DelayThirtySecond_a=1;
        IC_Data.time.Second=0;//時間歸0
        IC_Data.time.Thirty_Second_Count=0;
        math_DelayThirtySecond_b=IC_Data.time.Thirty_Second_Count;
        return 0;
    }
    else{
        if(math_DelayThirtySecond_b!=IC_Data.time.Thirty_Second_Count) {
            math_DelayThirtySecond_a=0;
            return 1;
        }
        else return 0;
    }
}