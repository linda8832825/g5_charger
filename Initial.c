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
    TRISE_WriteError        = Output;
    TRISE_BatteryError      = Output;
    TRISE_POWER             = Output;
	TRISE_BUZZ 				= Output;
	TRISE_LED           	= Output; 		
	TRISE_SW                = Input; 
	AD1PCFGL=0xFFFF; //1=�Ʀ��J
	AD1PCFGH=0xFFFF;	
	

//	ODCFbits.ODF2 = 1;
//	ODCFbits.ODF3 = 1;

//	ODCFbits.ODF2 = 1;
//	ODCFbits.ODF3 = 1;

	BUZZ = BUZZ_ON;
	
	TRISE_U1RX = Input; 
	TRISE_U1TX = Output;	
	
}
void Initial_Ele_load_UART(void)
{
	
	U2MODE=0x0008;//�u�ϥ�UxTX��UxRX�}�� UxRX�}��Ŷ��q�쬰0	
	U2STA=0x2440;//UxTX�}��Ŷ��q�쬰1
	U2STAbits.URXISEL=1;	
	U2BRG = BR_9600;
	
	RPINR19bits.U2RXR = 10;//��RPINR19��U2RXR���\�� ���VRP10 //rx�bRP10
 	RPOR8bits.RP17R = 5;	//��RPOR8bits.RP17R���}�� ���V�\��28 //TX�bRP17

	IFS1bits.U2RXIF = 0;		// Clear Interrupt flag11
	IFS1bits.U2TXIF = 0;		
	IEC1bits.U2RXIE = 1;		// Enable UART Interrupt
	IEC1bits.U2TXIE = 1;		// Enable UART Interrupt
		
	IPC7bits.U2RXIP=5; //�����u���v
	IPC7bits.U2TXIP=5; //�e�X�u���v
	U2STAbits.UTXEN=1; //���\TX
	U2MODEbits.UARTEN=1;	
    

	
	T2CON=0;
	IEC0bits.T2IE=1;            //TIMER���_���\�� 1=���\
	IFS0bits.T2IF=0;            //TIMER���_�лx���A�� 0=�����줤�_
	T2CONbits.TCKPS=1;
	T2CONbits.TCS=0;            //����clock (FOSC/2
	PR2=15000;                   //�ϥ��N��g5�@��
    T2CONbits.TON=1;// �Ұ�timer2
		
}
void Initial_G5_UART(void)
{
	
	U3MODE=0x0008;//�u�ϥ�UxTX��UxRX�}�� UxRX�}��Ŷ��q�쬰0	
	U3STA=0x2440;//UxTX�}��Ŷ��q�쬰1
	U3STAbits.URXISEL=1;	
	U3BRG = BR_115200;
	
		//CON4�쥻
	RPINR17bits.U3RXR = 7;//��RPINR17��U3RXR���\�� ���VRP7
	RPOR3bits.RP6R = 28;	//��RPOR3bits.RP7R���}�� ���V�\��28 
			
	IFS5bits.U3RXIF = 0;		// Clear Interrupt flag11
	IFS5bits.U3TXIF = 0;		
	IEC5bits.U3RXIE = 1;		// Enable UART Interrupt
	IEC5bits.U3TXIE = 1;		// Enable UART Interrupt
		
	IPC20bits.U3RXIP=7;
	IPC20bits.U3TXIP=7;
	U3STAbits.UTXEN=1;
	U3MODEbits.UARTEN=1;	

	T3CON=0;
	IEC0bits.T3IE=1;            //TIMER���_���\�� 1=���\
	IFS0bits.T3IF=0;            //TIMER���_�лx���A�� 0=�����줤�_
	T3CONbits.TCKPS=1;
	T3CONbits.TCS=0;            //����clock (FOSC/2
	PR3=1250;                   //0.625�h�@�� _T3Interrupt
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
	I2C1BRG=0x13;//�i�w�v180 //0000 0001 1111 1111
	
	
//	I2C1ADD=0X10>>1;
	I2C1MSK=0x0000; //�n�a�}�����@�ˤ~��ǰt
    
    I2C1TRN=0x00;
	
	IEC1bits.MI2C1IE=1;
	IEC1bits.SI2C1IE=0;
	IPC4bits.SI2C1IP=0;
	IPC4bits.MI2C1IP=4; //���_�u���v
//	I2C1CONbits.IPMIEN=1;
//	I2C1CONbits.SMEN=1; //�ҥο�X�ŦXi2c�q��
	I2C1CONbits.I2CEN=1; //i2c����
//    I2C1CONbits.I2CSIDL = 0;//0 =�b�Ŷ��Ҧ��U�~��Ҷ��B��
//    I2C1CONbits.A10M=0;//0 = I2CxADD�O7��slave�a�}
//    I2C1CONbits.I2CSIDL=1; //1 =��]�ƶi�J�Ŷ��Ҧ��ɰ���Ҷ��B��
//    I2C1CONbits.DISSLW=1; //1 =�T��slew rate����
	
	
}	
