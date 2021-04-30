#ifndef Ele_load_Define_H
#define Ele_load_Define_H


typedef struct tagEle_load_Data {	
    unsigned char 	ID;						//�s�� //0xAA
    unsigned char 	Fuc;					//����r //46
    unsigned char 	CurrentMin;				//�q�y�̤p�� 
    unsigned char 	CurrentMax;				//�q�y�̤j�� 
    unsigned char 	Current;				//�q�y //��10�i���-17
    unsigned char 	Voltage;				//�q�� //��10�i���-512
    unsigned char 	StopVoltage;			//�_�q�q�� 
    unsigned char 	Capacity;				//�e�q 
    unsigned char 	Temperature;			//�ū�
    unsigned char 	StopFuc;                //�Ұ��R�O
    unsigned char 	End;                    //���X
  									
 	union
	{
		unsigned						IF:1;
		struct
		{
			unsigned  			 	TIF :1;		//��ƶǰe����
			unsigned  			 	RIF :1;		//��Ʊ�������
			unsigned  			 	ERRIF:1;	//��Ʊ����ζǰe���~				
		};
	};
	
  unsigned char Index;						//�n�����
  unsigned char RTIndex;					//�w�����
}Ele_load_Data_define;

extern Ele_load_Data_define Ele_load_Data; 


#endif
