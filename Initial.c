#include "Main_Define.h"

Coulomb_Data_struct_define Coulomb_Data; 
Ele_load_Data_define Ele_load_Data; 
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
	AD1PCFGL=0xFFFF; //1=數位輸入
	AD1PCFGH=0xFFFF;	

	BUZZ = BUZZ_ON;
    POWER = StopCharge;
	
	TRISE_U1RX = Input; 
	TRISE_U1TX = Output;	
}

void Initial_Timer1(void)
{
	T1CON=0; 
	IEC0bits.T1IE=1; // TIMER中斷允許位 1=允許
	IFS0bits.T1IF=0; // TIMER中斷標誌狀態位 0=未受到中斷
	T1CONbits.TCKPS=1;//1:8
	T1CONbits.TCS=0; //內部clock (FOSC/2
	T1CONbits.TON=1; //打開TIMER功能
	PR1=2000; //1秒做一次 但不知道公式
}

void Initial_Coulomb_UART(void)
{
	U1MODE=0x0008;//只使用UxTX跟UxRX腳位 UxRX腳位空閒電位為0	
	U1STA=0x2440;//UxTX腳位空閒電位為1
	U1STAbits.URXISEL=1;
	
	U1BRG = BR_9600;
		
	RPINR18bits.U1RXR = 30; //把RPINR18的U1RXR的功能 指向RP30 //rx在RP30
	RPOR8bits.RP16R = 3; //把RPOR8bits.RP16R的腳位 指向功能3 //TX在RP16
	
	IFS0bits.U1RXIF = 0;		// Clear Interrupt flag11
	IFS0bits.U1TXIF = 0;		
	IEC0bits.U1RXIE = 1;		// Enable UART Interrupt
	IEC0bits.U1TXIE = 1;		// Enable UART Interrupt
		
	IPC2bits.U1RXIP=6; //接收優先權
	IPC3bits.U1TXIP=6; //送出優先權
	U1MODEbits.UARTEN=1; //允許tx
	U1STAbits.UTXEN=1;
	


	T4CON=0;
	IEC1bits.T4IE=1; //TIMER中斷允許位 1=允許
	IFS1bits.T4IF=0; //TIMER中斷標誌狀態位 0=未受到中斷
	T4CONbits.TCKPS=1;
	T4CONbits.TCS=0; //內部clock (FOSC/2
    PR4=15000;
    T4CONbits.TON=1;// 啟動timer1
	
}
void Initial_Ele_load_UART(void)
{
	
	U2MODE=0x000A;//高速模式 //偶校驗
	U2STA=0x2440;//UxTX腳位空閒電位為1
	U2STAbits.URXISEL=1;	
	U2BRG = BR_9600;
	
	RPINR19bits.U2RXR = 10;//把RPINR19的U2RXR的功能 指向RP10 //rx在RP10
 	RPOR8bits.RP17R = 5;	//把RPOR8bits.RP17R的腳位 指向功能5 //TX在RP17 

	IFS1bits.U2RXIF = 0;		// Clear Interrupt flag11
	IFS1bits.U2TXIF = 0;		
	IEC1bits.U2RXIE = 1;		// Enable UART Interrupt
	IEC1bits.U2TXIE = 1;		// Enable UART Interrupt
		
	IPC7bits.U2RXIP=5; //接收優先權
	IPC7bits.U2TXIP=5; //送出優先權
	U2STAbits.UTXEN=1; //允許TX
	U2MODEbits.UARTEN=1;
    

	
	T2CON=0;
	IEC0bits.T2IE=1;            //TIMER中斷允許位 1=允許
	IFS0bits.T2IF=0;            //TIMER中斷標誌狀態位 0=未受到中斷
	T2CONbits.TCKPS=1;
	T2CONbits.TCS=0;            //內部clock (FOSC/2
	PR2=15000;                   //反正就跟g5一樣
    T2CONbits.TON=1;// 啟動timer2
		
}
void Initial_G5_UART(void)
{
	
	U3MODE=0x0008;//只使用UxTX跟UxRX腳位 UxRX腳位空閒電位為0	
	U3STA=0x2440;//UxTX腳位空閒電位為1
	U3STAbits.URXISEL=1;	
	U3BRG = BR_115200;
	
	RPINR17bits.U3RXR = 7;//把RPINR17的U3RXR的功能 指向RP7
	RPOR3bits.RP6R = 28;	//把RPOR3bits.RP7R的腳位 指向功能28 
			
	IFS5bits.U3RXIF = 0;		// Clear Interrupt flag11
	IFS5bits.U3TXIF = 0;		
	IEC5bits.U3RXIE = 1;		// Enable UART Interrupt
	IEC5bits.U3TXIE = 1;		// Enable UART Interrupt
		
	IPC20bits.U3RXIP=7;
	IPC20bits.U3TXIP=7;
	U3STAbits.UTXEN=1;
	U3MODEbits.UARTEN=1;	

	T3CON=0;
	IEC0bits.T3IE=1;            //TIMER中斷允許位 1=允許
	IFS0bits.T3IF=0;            //TIMER中斷標誌狀態位 0=未受到中斷
	T3CONbits.TCKPS=1;
	T3CONbits.TCS=0;            //內部clock (FOSC/2
	PR3=1250;                   //0.625去一次 _T3Interrupt
    T3CONbits.TON=1;// 啟動timer3
}

void Initial_User_UART(void)
{
	U4MODE=0x0008;//只使用UxTX跟UxRX腳位 UxRX腳位空閒電位為0	
	U4STA=0x2440;//UxTX腳位空閒電位為1
	U4STAbits.URXISEL=1;	
	U4BRG = BR_9600;
		
	RPINR27bits.U4RXR = 2;  //把RPINR27的U4RXR的功能 指向RP2     //rx在pr2
	RPOR2bits.RP4R = 30;	//把RPOR2bits.RP4R的腳位 指向功能30  //tx在pr4
			
	IFS5bits.U4RXIF = 0;		// Clear Interrupt flag11
	IFS5bits.U4TXIF = 0;		
	IEC5bits.U4RXIE = 1;		// Enable UART Interrupt
	IEC5bits.U4TXIE = 1;		// Enable UART Interrupt
		
	IPC22bits.U4RXIP=4;
	IPC22bits.U4TXIP=4;
	U4STAbits.UTXEN=1; //TX智能
	U4MODEbits.UARTEN=1;	//UART智能

//	T4CON=0;
//	IEC1bits.T4IE=1;            //TIMER中斷允許位 1=允許
//	IFS1bits.T4IF=0;            //TIMER中斷標誌狀態位 0=未受到中斷
//	T4CONbits.TCKPS=1;
//	T4CONbits.TCS=0;            //內部clock (FOSC/2
////	PR4=15000;                   //1秒去一次 _T3Interrupt
//    T4CONbits.TON=1;// 啟動timer4
}


void Initial_I2C(void)
{
	TRISx_SCL = 1 ;
	TRISx_SDA = 1 ;

	LATx_SCL = 0;
	LATx_SDA = 0;

	
	I2C1CON=0x0000;
	I2C1STAT=0x0000;
	I2C1BRG=0x13;//波德率180 //0000 0001 1111 1111
	
	
	I2C1MSK=0x0000; //要地址完全一樣才能匹配
    
    I2C1TRN=0x00;
	
	IEC1bits.MI2C1IE=1;
	IEC1bits.SI2C1IE=0;
	IPC4bits.SI2C1IP=0;
	IPC4bits.MI2C1IP=4; //中斷優先權
	I2C1CONbits.I2CEN=1; //i2c智能
}	
void Initial_Variable(void){
    IC_Data.time.ms=1000;
    IC_Data.time.Regual_Read_G5=120;//20秒後才能常態與g5通訊
    IC_Data.GetTheWhatYouWant=NO;
    IC_Data.DoIamStarted=NO;
    IC_Data.WriteZeroAh=NO;
    Ele_load_Data.GoTo_Write_Ele_load=NO;
    Ele_load_Data.WriteIF=0; //寫入電子附載機失敗
    Ele_load_Data.Init=0;
    Ele_load_Data.DisChargeDone=NO;

}
