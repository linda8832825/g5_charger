//###########################################################//
//    ���   : 2021.05.06                                    //
//    ����   : v1.0                                          //
//  ��s���� :                        //
//    �@��   :                                   //
//###########################################################//

#include "Main_Define.h"

_CONFIG1( WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & BKBUG_ON & GWRP_OFF & GCP_OFF & JTAGEN_OFF  )
_CONFIG2( IESO_OFF & FNOSC_FRCPLL & FCKSM_CSDCMD & OSCIOFNC_OFF   )



void __attribute__((interrupt, no_auto_psv)) _OscillatorFail(void){
	INTCON1bits.OSCFAIL = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _AddressError(void){
	unsigned char math_a=1;
	INTCON1bits.ADDRERR = 	0;
	while(math_a);     
}

void __attribute__((interrupt, no_auto_psv))_StackError(void){
	INTCON1bits.STKERR = 0;
	while(1);     
}

void __attribute__((interrupt, no_auto_psv)) _MathError(void){
	INTCON1bits.MATHERR = 0;
	while(1);     
}

IC_Data_Define IC_Data;
unsigned int WriteWholeAh=0; //�O�_�g�J���w�ɼ�
unsigned int FirstWriteLCD=1; //�O�_�Ĥ@���g�JLCD
unsigned int LcdWriteComplete=0; //LCD�g�J����
//IC_Data_IF IC_Data_Save_IF;


int main (void) 
{
    unsigned int    math_a=0; //�p�Ƹ�ƭn����h�֦�
    unsigned int    math_b=0; //�L�k�g0.1�w�ɶi�h������
    unsigned int    math_c=0; //�L�k�g���w�ɶi�h������
    unsigned int    math_d=0; //�Φb�Ƭ��
    unsigned int    math_e=0; //�P�_�n���n��sLCD
    unsigned int    math_f=0; //100����LCD������s
    unsigned int    math_g=0; //�Φb�Pg5Ū�����ƪ��R�q��30�����
    unsigned int    math_h=0; //�Φb�P�_�n���n�����k0
    
  
    
	Initial_Clock(); 	
	
	//�@�ǼƭȪ���l�Ƴ]�w-----------------------------------------------
    IC_Data.time.ms=1000;
    IC_Data.time.Regual_Read_G5=20;//20���~��`�A�Pg5�q�T
    IC_Data.GetTheWhatYouWant=NO;
    IC_Data.DoIamStarted=NO;
    IC_Data.WriteZeroAh=NO;
    Ele_load_Data.GoTo_Write_Ele_load=NO;
    Ele_load_Data.WriteIF=0; //�g�J�q�l����������
    Ele_load_Data.Init=0; 
	//--------------------------------------------------------------------
     
	Initial_IO();
	Initial_G5_UART();
    Initial_Ele_load_UART();
    Timer1_initial();
    I2C_Initial();
    LCD_Init(DriverIC_I2C_LCD_Addr);
    
    
    BUZZ = BUZZ_ON;
    LED = Turn_ON;
    delay(1);
    BUZZ = BUZZ_OFF;
    LED = Turn_OFF;
    delay(3);
	LCD_write_Char(1, 1 , " iNer");
    LCD_write_Char(2, 1 , " iNer");
    LCD_write_Char(3, 1 , " iNer");
    LCD_write_Char(4, 1 , " iNer");
 
	while(1)
	{
        //------------------------------�Ұ�-----------------------------------//
        if(SW==SW_Push){    //�p�G�Ұʶs�Q���U
            while(SW==SW_Push){//����s�Q��}�~�|�~��
                IC_Data.DoIamStarted = YES; //���s�Q���U�L
                BUZZ = BUZZ_ON;
                delay(1);
                BUZZ = BUZZ_OFF;
                //�M��b�M�Ť��e�]���Ҧ��ܼ�
                //�n���n�g�Ө禡���Ũ�
            }
        }
        //---------------------------------------------------------------------//
        
            
        //-----------------------------���ջPG5�s��-------------------------------//
        if(IC_Data.DoIamStarted == YES && IC_Data.GetTheWhatYouWant == NO && WriteWholeAh == NO){ //�ҰʤF�B�٨S����G5��Ƥ]�٨S�g0�w��
            if((G5_Get.RIF != 1) && (math_a<=3) && (IC_Data.GetTheWhatYouWant == NO)){//�p�G�b�|�����٨S������
                Read_ALL_G5_Data(); //��G5�n���
                delay(2);
                if(G5_Data.ID == My_ID){//���n�쥿�T���
                    IC_Data.GetTheWhatYouWant = YES;
                    math_a=0;
                }
                else{// �S���n�쥿�T��� �N�R�q�T�Q��
                    if(math_h==0){
                        math_h=1;
                        IC_Data.time.Second=0;//�ɶ��k0
                        math_g=IC_Data.time.Thirty_Second_Count;
                        POWER = Charge;
                        LCD_Clear();
                        delay(1);
                        LCD_write_Char(1, 1 , "Charging");
                    }
                    if((math_g!=IC_Data.time.Thirty_Second_Count) && (math_h==1)) {
                        POWER = StopCharge;
                        math_h=0;
                        math_a++;
                        LED=~LED;
                        LCD_Clear();
                        delay(1);
                        if(math_a>3){//�R�q4�����S��k��g5�Ǹ�ƥX�ӴN�ŧi����
                            
                            POWER = StopCharge;
                            IC_Data.GetTheWhatYouWant= NO; 
                            IC_Data.DoIamStarted = NO;
                            BatteryError = Turn_ON; //battery�O�G �N��g5�S�q�F
                            WriteError = Turn_OFF;
                            LCD_Clear();
                            delay(1);
                            LCD_write_Char(1, 1 , "Connection To G5 error occurred");
                            math_a = 0;
                        }
                    }
                }
                
            }
        }
        //----------------------------------------------------------------------------//
        
        
        //-----------------------------�w�PG5�s��-----------------------------------//
        if(IC_Data.GetTheWhatYouWant == YES){//�p�G�n���ƴN��q��q�y=0
            //---------------------���g5���-----------------------------------//
            if(LcdWriteComplete==NO){
                delay(1);
                if((FirstWriteLCD == YES) || (math_f>=4)) { //120��n��s���LCD
                    First_Write_to_LCD();
                    FirstWriteLCD=NO;
                    math_f=0;
                }
                else{//30���s�@��LCD
                    if(math_e==0){
                        math_d=IC_Data.time.Thirty_Second_Count;
                        math_e=1;
                    }
                    if((math_d!=IC_Data.time.Thirty_Second_Count) && (math_e==1)){
                        led_Toggle();
                        Other_Time_Write_to_LCD();
                        math_e=0;
                        math_f++;
                    }
                }
                LcdWriteComplete=YES;
            }
            //-----------------------------------------------------------------//



            //----------------------------��q---------------------------------//
            if((IC_Data.WriteZeroAh == NO) && (LcdWriteComplete==YES)){//�g�J0.1AH�|�����\
                
                if(Ele_load_Data.ID == Ele_load_ID){ //�p�GŪ��q�l����������ƬO���T��
                    
                    //-----------------------------------�]�w�q�l������-----------------------------------------//
                    if(Ele_load_Data.Init!=2) Set_Ele_load();
                    //------------------------------------------------------------------------------------------//
                    else{
                        //----------------------------------��q-----------------------------------------------------//
                        if(Ele_load_Data.DisCharge==0x0){
                            do{ WriteEleLoadState(0x00, 0xFF); delay(1); } while(Ele_load_Data.WriteIF==0);//��q
                            ReadAllEleLoadData();
                            delay(1);
                        }
                        else    Ele_load_Data.GoTo_Write_Ele_load=NO; //���ݭn�A���g�J�q�l������ ��_timer1�̪�Ū���q�l������
                        //------------------------------------------------------------------------------------------//


                        //---------------------------------�����q------------------------------------------------//
                        if((G5_Data.Current == 0x00) && (G5_Data.Voltage <= Discharge_Voltage)){//��q����

                            if(Ele_load_Data.DisCharge==0x1){ //�p�G�q�l�������O�b��q�����A
                                do{ WriteEleLoadState(0x00, 0x00); delay(1); } while(Ele_load_Data.WriteIF==0);//��q����
                                ReadAllEleLoadData();
                                delay(1);
                            }
                            else Ele_load_Data.GoTo_Write_Ele_load=NO; //���ݭn�A���g�J�q�l������ ��_timer1�̪�Ū���q�l������

                            if(Ele_load_Data.Buzzing!=0){//���ﾹ�s�F
                                do{ WriteEleLoadState(0x01, 0x00);  delay(1); } while(Ele_load_Data.WriteIF==0);//����
                                do{ WriteEleLoadSetting(0x00, 0x00, BuzzMusicType); delay(1); } while(Ele_load_Data.WriteIF==0); //�g���ﾹ�T������
                                ReadAllEleLoadData();
                                delay(1);
                            }
                            else Ele_load_Data.GoTo_Write_Ele_load=NO; //���ݭn�A���g�J�q�l������ ��_timer1�̪�Ū���q�l������


                            if(G5_Data.Residual_Electricity == 0x01){//�T�{�O�_��0.1Ah
                                IC_Data.WriteZeroAh = YES; //�g�J0.1�w�ɼƦ��\
                                LCD_Clear();
                                LCD_write_Char(1, 1 , "Write 0.1Ah To G5 complete");
                            }
                            else{//�S�����ܦA�g�@��
                                Write_G5_Data(0x07 , 0x01); //�g0.1Ah�i�h 01 06 00 07 00 01 crc
                                math_b++;
                            }
                            if(math_b>=3){//�g�J0.1�w�ɥ���
                                WriteError = Turn_ON;
                                BUZZ = BUZZ_ON;
                                delay(3);
                                WriteError = Turn_OFF;
                                LCD_Clear();
                                LCD_write_Char(1, 1 , "Write Ah To G5 error occurred");
                            }
                        }
                        //-----------------------------------------------------------------------------------------------//
                    }
                    
                }
                LcdWriteComplete=NO;
            }
            //-----------------------------------------------------------------//


            //-----------------------------�R�q--------------------------------//
            if(IC_Data.WriteZeroAh == YES){//�g�n0.1�w�ɫ�}�l�R�q
                POWER = Charge;
                if(G5_Data.Current <= Charge_Stop_Current){//�R�q����

                    if(G5_Data.Now_Total_Capacity == G5_Data.Residual_Electricity){//�T�{�O�_�N�{�b���w�ɼƼg�캡�w�ɼ�
                        WriteWholeAh = YES; //�g�J���w�ɼƦ��\
                        LCD_Clear();
                        LCD_write_Char(1, 1 , "Write Whole Ah To G5 complete");
                    }
                    else{//�S�����ܦA�g�@��
                        Write_G5_Data(0x09 , 0x01); //��G5���N�{�b���w�ɼƼg�캡�w�ɼ� 01 06 00 09 00 01 crc
                        math_c++;
                    }
                    if(math_c>=3){//�g�J0.1�w�ɥ���
                        WriteError = Turn_ON;
                        BUZZ = BUZZ_ON;
                        delay(3);
                        WriteError = Turn_OFF;
                        LCD_Clear();
                        LCD_write_Char(1, 1 , "Write Whole Ah To G5 error occurred");
                    }

                }

            }
            //------------------------------------------------------------------//
        }
        //----------------------------------------------------------------------//        
            
        //---------------------------����G5���---------------------------------//
        if(G5_Get.RIF) G5_Get.RIF=0;
        //----------------------------------------------------------------------//  
        
        //---------------------------�����q�l���������---------------------------------//
        if(Ele_load_Get.RIF) Ele_load_Get.RIF=0;
     	//----------------------------------------------------------------------//	
      }
    return 1;
}    	