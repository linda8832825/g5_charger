#include "Main_Define.h"

User_Data_struct_define User_Data; 

void SortUserData(void) {
    
    unsigned int *index1, *index2, *index3;
    unsigned int i;
    unsigned int math_a;
    unsigned char math_b;
    
    index1=&G5_Data.ID;
    index2=&Ele_load_Data.ID;
    index3=&User_Data.ID_G5;
    
    for(i=0; i<18; i++){
        *index3=*index1;
        index1++;
        index3++;
    }
    for(i=0; i<11; i++){
        *index3=*index2;
        index2++;
        index3++;
    }
    
    User_Data.Index=0x3A; //29*2­Ó¸ê®Æ
    User_Data.RTIndex=0;   
    
    math_a=CRC_Make(&User_Data,User_Data.Index);
		
    math_b = math_a&0xFF;
    User_Data.CRC_L = math_b;

    math_b = (math_a&0xFF00)>>8;
    User_Data.CRC_H = math_b;
    
    User_Data.Index+=2;

    User_Data.RTIndex=1;
    
    if(!U4STAbits.UTXEN) U4STAbits.UTXEN=1;
    
    while(IFS5bits.U4TXIF){
        IFS5bits.U4TXIF=0;
        IEC5bits.U4TXIE=1;
    }
    U4TXREG=User_Data.ID_G5;	
    
}
