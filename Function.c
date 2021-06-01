#include "Main_Define.h"
unsigned char math_DelayThirtySecond_a=0; //�Φb�����O�_�Ĥ@���i��delay30���
unsigned char math_DelayThirtySecond_b=0; //�Φb����delay30��Ϫ�IC_Data.time.Thirty_Second_Count

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

unsigned int CRC_Check(unsigned char* crc_address, unsigned char crc_length) //howmuch�O���h�֭�!!  5��Ʀr�N��5    ���O�q0�}�l��
{
	unsigned int CRC_CODE=0xFFFF,math_a,math_b;
	unsigned char CRC_Length=0,i,*CRC_Address;
	


	CRC_Address=crc_address;
	CRC_Length=crc_length-2;	
	
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
		

	CRC_Address=crc_address;
	CRC_Address+=crc_length-2;	

	
	math_a=*CRC_Address;
	math_a=math_a<<8;
	CRC_Address++;
	math_a=math_a|(*CRC_Address);
	
	//�]�����g���F���CRC���ӬO��L �bH �i�O�g�ϤF �ҥH �ܦ���H�bL �Ϊ̥�L�bH ���i�H
	math_b=*CRC_Address;
	math_b=math_b<<8;
	CRC_Address--;
	math_b=math_b|(*CRC_Address);
	
	if (CRC_CODE == math_a || CRC_CODE == math_b)//��CRC�T�{���� �N��ƭ��s��z
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
    if(math_a>=math_b)  while((math_a - IC_Data.time.ms) < math_b);//����
    else {//������
        math_c=math_b-math_a;//�p�⪽��0�@��e����������delay�@���
        while(IC_Data.time.ms > (0x03E8-math_c));
    }
}

void delay (unsigned char i){
    unsigned 	char math_a,math_b,math_c,math_d;
    math_d=0x1E;//30��
    math_b=i;
    math_a=IC_Data.time.Second;
    if((math_d-math_a)>=math_b) while((IC_Data.time.Second - math_a) < math_b); //����
    else{ //������
        math_c=math_b-(math_d-math_a);
        while(IC_Data.time.Second<math_c);
    }
}

unsigned char delayThirtySecond(void){

    if(math_DelayThirtySecond_a==0){
        math_DelayThirtySecond_a=1;
        IC_Data.time.Second=0;//�ɶ��k0
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