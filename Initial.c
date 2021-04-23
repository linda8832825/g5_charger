#include "Main_Define.h"

G5_Data_struct_define G5_Data; 

void Initial_Clock(void)
{	
	CLKDIVbits.RCDIV=0;
	CLKDIVbits.DOZEN=0;
	while(OSCCONbits.COSC != 1);			// Wait for new Oscillator to become FRC w/ PLL 
	while(OSCCONbits.LOCK != 1);			// Wait for Pll to Lock */  	
}

void Initial_IO(void)
{
    TRISE_Battery           = Output;
    TRISE_POWER             = Output;
	TRISE_BUZZ 				= Output;
	TRISE_LED           	= Output; 		
	TRISE_SW                = Input; 
	AD1PCFGL=0xFFFF;
	AD1PCFGH=0xFFFF;	
	

//	ODCFbits.ODF2 = 1;
//	ODCFbits.ODF3 = 1;

//	ODCFbits.ODF2 = 1;
//	ODCFbits.ODF3 = 1;

	BUZZ = BUZZ_ON;
	
	TRISE_U1RX = Input; 
	TRISE_U1TX = Output;	
	
}

void Initial_G5_UART(void)
{
	
	U3MODE=0x0008;//�u�ϥ�UxTX��UxRX�}�� UxRX�}��Ŷ��q�쬰0	
	U3STA=0x2440;//UxTX�}��Ŷ��q�쬰1
	U3STAbits.URXISEL=1;	
	U3BRG = BR_115200;
	
/*
	��U�����ﶵ���VPRx
	RPINR18.U1RXR<5:0>
	RPINR19.U2RXR<5:0>
	RPINR17.U3RXR<5:0>
	RPINR27.U4RXR<5:0>
	
	
	��RPORxbits.RPxR���V�U�������@�ﶵ
	3 U1TX UART1 Transmit
	5 U2TX UART2 Transmit
	28 U3TX UART3 Transmit
	30 U4TX UART4 Transmit	
*/
	
		//CON5	
//	RPINR17bits.U3RXR = 2;//��RPINR17��U3RXR���\�� ���VRP7
//	RPOR2bits.RP4R = 28;	//��RPOR3bits.RP7R���}�� ���V�\��28 	
	
		//CON4�쥻
	RPINR17bits.U3RXR = 7;//��RPINR17��U3RXR���\�� ���VRP7
	RPOR3bits.RP6R = 28;	//��RPOR3bits.RP7R���}�� ���V�\��28 
	
		//CON3
//	RPINR17bits.U3RXR = 10;
//	RPOR8bits.RP17R = 28;


			
	IFS5bits.U3RXIF = 0;		// Clear Interrupt flag11
	IFS5bits.U3TXIF = 0;		
	IEC5bits.U3RXIE = 1;		// Enable UART Interrupt
	IEC5bits.U3TXIE = 1;		// Enable UART Interrupt
		
	IPC20bits.U3RXIP=5;
	IPC20bits.U3TXIP=5;
	U3STAbits.UTXEN=1;
	U3MODEbits.UARTEN=1;	
	
	
	
	T3CON=0;
	IEC0bits.T3IE=1; //TIMER���_���\�� 1=���\
	IFS0bits.T3IF=0; //TIMER���_�лx���A�� 0=�����줤�_
	T3CONbits.TCKPS=1;
	T3CONbits.TCS=0; //����clock (FOSC/2
	PR3=1250; //0.625�h�@�� _T3Interrupt
    T3CONbits.TON=1;// �Ұ�timer3
		
}

void I2C_Initial(void)
{
	TRISx_SCL = 1 ;
	TRISx_SDA = 1 ;

	LATx_SCL = 0;
	LATx_SDA = 0;

	
	I2C1CON=0x0000;
	I2C1STAT=0x0000;
	I2C1BRG=511;//180
	
	
	I2C1ADD=0x10 >>1; //����
	I2C1MSK=0xFFFF;
	
	IEC1bits.MI2C1IE=1; //�����_
	IEC1bits.SI2C1IE=1;
	IPC4bits.SI2C1IP=4;
	IPC4bits.MI2C1IP=4;
//	I2C1CONbits.IPMIEN=1;
	I2C1CONbits.STREN=1;
	I2C1CONbits.SMEN=1;
	I2C1CONbits.I2CEN=1;
	
	
}	

void wait(unsigned int i){
    while(i--);
}
