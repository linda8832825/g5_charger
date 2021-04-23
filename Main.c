//###########################################################//
//    ���   : 2021.04.08                                    //
//    ����   : v1.0                                          //
//  ��s���� :                        //
//    �@��   :                                   //
//###########################################################//

#include "Main_Define.h"

_CONFIG1( WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & BKBUG_ON & GWRP_OFF & GCP_OFF & JTAGEN_OFF  )
_CONFIG2( IESO_OFF & FNOSC_FRCPLL & FCKSM_CSDCMD & OSCIOFNC_OFF   )



void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void)
{
	INTCON1bits.OSCFAIL = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void)
{
	unsigned char math_a=1;
	INTCON1bits.ADDRERR = 	0;
	while(math_a);     
}

void __attribute__((interrupt, no_auto_psv))_StackError(void)
{
	INTCON1bits.STKERR = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _MathError(void)
{
	INTCON1bits.MATHERR = 0;
	while(1);     
}

IC_Data_Define IC_Data;
//IC_Data_IF IC_Data_Save_IF;


int main (void) 
{
    unsigned int    math_a=0; //�p�Ƹ�ƭn����h�֦�
    unsigned int    math_b=0; //���{�b�����
    unsigned int    math_c=0; //�L�k�g0.1�w�ɶi�h������
    
	Initial_Clock(); 	
	IC_Data.ms=1000;
	
	//IC_Data.Wait_Coulomb_Read=0;
	
	
	//�@�ǼƭȪ���l�Ƴ]�w-----------------------------------------------
    IC_Data.GetTheWhatYouWant=NO;
    IC_Data.DoIamStarted=NO;
//	IC_Data.Wait_Coulomb_Read=1480;
//	IC_Data.Charge_Voltage_Avg=0;		
//	IC_Data.Charge_Voltage_Avg_Count=0;	
//    IC_Data.Return_ID=0x06;
	//--------------------------------------------------------------------


	         
	Initial_IO();
	Initial_G5_UART();
    Timer1_initial();
    I2C_Initial();

    
    BUZZ = BUZZ_ON;
    LED = Turn_ON;
    while(IC_Data.Second <1);
    BUZZ = BUZZ_OFF;
    LED = Turn_OFF;
    

//	Initial_Coulomb_UART();    
//	Initial_UART2();

		
    //�g�J�w�ۭp--------------------------------------------------------
//    Unlock_Coulomb();
//    Write_Coulomb_Data(0x0009,0x01);//0x0009  �зǹq���e�q 0.0~6553.5AH
//    while(!ModBus_Receiver.TIF);
//    ModBus_Receiver.TIF=0;		
    //----------------------------------------------------------------
    

    
	while(1)
	{
//                LCD_Init(DriverIC_I2C_LCD_Addr);
//    LCD_Clear();
//    LCD_Set_Cursor(1, 1);
//    LCD_Write_String(" 1");
	
    
        if(SW==SW_Push){    //�p�G�Ұʶs�Q���U
            while(SW==SW_Push){//����s�Q��}�~�|�~��
                IC_Data.DoIamStarted = YES; //���s�Q���U�L
                //�M��b�M�Ť��e�]���Ҧ��ܼ�
                //�n���n�g�Ө禡���Ũ�
            }
        }
            
        if(IC_Data.DoIamStarted == YES){
            if((G5_Get.RIF != 1) && (math_a<=3) && (IC_Data.GetTheWhatYouWant == NO)){//�p�G�٨S������
                BUZZ = BUZZ_ON;
                math_b=IC_Data.Second;
                while(math_b == IC_Data.Second);
                BUZZ = BUZZ_OFF;
                Read_ALL_G5_Data(); //��G5�n���
                if(G5_Data.ID == My_ID){//���n�쥿�T���
                    IC_Data.GetTheWhatYouWant = YES;
                }
                else{// �S���n�쥿�T��� �N�R�q�T�Q��
                    math_a++;
                    IC_Data.Thirty_Second_Count=0;
                    POWER = Turn_ON;
                    while(IC_Data.Thirty_Second_Count==1);
                    POWER = Turn_OFF;
                }
            }
            else{//�R�q4�����S��k��g5�Ǹ�ƥX�ӴN
                IC_Data.GetTheWhatYouWant= NO; 
                BatteryError = Turn_ON; //battery�O�G �N��g5�S�q�F
                math_a = 0;
            }
            if(IC_Data.GetTheWhatYouWant == YES){//�p�G�n���ƴN��q��q�y=0
                //��q
                while(G5_Data.Current > 0x00);
                //��q����
                if(G5_Data.Residual_Electricity == 0x01){//�T�{�O�_��0.1Ah
                    IC_Data.WriteZeroAh = YES;
                }
                else{//�S�����ܦA�g�@��///////////////////////////////
                    Write_G5_Data(0x07 , 0x01); //�g0.1Ah�i�h 01 06 00 07 00 01 crc
                    math_c++;
                }
                if(math_c>=3){
                    //�g�J0.1�w�ɥ���
                }
            }
                
                
    }
            
            
            

//            do
//            {	
//                G5_Receiver.IF = 0;
//                Read_ALL_G5_Data(); //��G5�n���
//
////                Coulomb_Data.Read_Timer=500; ///////////////////////////////////////////////////
//                while(G5_Receiver.IF==0); //����G5�^�����
//                math_b++;
//                if(math_b>1){
//                    math_c++; //�p�ƥR�q����
//                    //G5�O�l�S���q�q �n���R�q
//                    //�s�q���������R�q30��
//                }
//                if(math_c >= read_G5_times_limt){ //�R�q���ư���]�w��
//                    // lcd���battery error
//                    BUZZ = BUZZ_ON; // ���ﾹ�s
//                        //�L�@�q�ɶ�����
//                }
//            }while(G5_Receiver.ERRIF==1);
            
            
            
//            if(G5_Data.Voltage <= Discharge_Voltage){//�p�G�q���p���q�I���I 
//                G5_reset_work(); //reset�w�ɼ�
//            }
//            else{
//                do{
//                     ��q�l�������q�T���L��q�� Discharge_Voltage
//                
//                }while(G5_Data.Voltage <=  Discharge_Voltage);
//                G5_reset_work(); //reset�w�ɼ�
//            }
            
            
            
            //��LCD���------------------------------------------------------
//            LCD_Init(LCD_I2C_Addr<<1); // Initialize LCD module with I2C address = 01001110
//            LCD_Set_Cursor(1, 1);
//            LCD_Write_String(" 1");
            //--------------------------------------------------------------


            //�q�l���������䱵����F��-------------------------------------------
//            if(ModBus_Receiver.RIF==1)
//            {
//                if(T4CONbits.TON==0)Timer4_initial(); //�p�Gtimer���� �N��timer�}�l
//
//                ModBus_Receiver.ERR_Count=0;	//��Ʊ����ζǰe���~	
//
//                			
//                ModBus_Receiver.RIF=0;
//
//                if(U2STAbits.OERR)  while(U2STAbits.OERR) math_a=U2RXREG; //�p�G�����w�İϷ��X�F//�N�Ⱶ���w�İϲM��
//            }
//            else if(ModBus_Receiver.ERRIF)   ModBus_Receiver.ERRIF=0; //��Ʊ����ζǰe���~	
            //-----------------------------------------------------------------
			
       
            //I2C--------------------------------------------------------------
//            if(!I2C_Data.Busy_IF) //�p�G�n�ǰe����H�S�����L��
//            {
//                if(EEPROM.Save_IF)
//                {
//                    Write_EEROM_information();
//                }
//            }	
            
            //-----------------------------------------------------------------
        		
        
    }
}
		