#include "Main_Define.h"

void __attribute__((interrupt, no_auto_psv)) _U4TXInterrupt(void)
{		
	
	static unsigned char *index;
	unsigned int math_a;
	
	if(User_Data.RTIndex < User_Data.Index)
	{
		if(User_Data.RTIndex==1) index=&User_Data.InterFace;
		U4TXREG=*index;
		index++;
		User_Data.RTIndex++;
		for (math_a=0;math_a<=20;math_a++)
		{
			asm("Nop");
		}	
	}
	else 
	{
		User_Data.RTIndex=0;
		User_Data.Index=0;
	}	

	IFS5bits.U4TXIF=0;
}

