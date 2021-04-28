#include "Main_Define.h"

unsigned char RS, i2c_add, BackLight_State = LCD_BACKLIGHT;
I2C_Data_Define I2C_Data;
unsigned char I2C_Buffer_index;

//---------------[ I2C Routines ]-------------------
//--------------------------------------------------
void I2C_Master_Wait()
{
    while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
}
void I2C_Master_Start()
{
  I2C_Master_Wait();
  I2C1CONbits.SEN = 1;
}
void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  I2C1CONbits.RSEN = 1;
}
void I2C_Master_Stop()
{
  I2C_Master_Wait();
  I2C1CONbits.PEN = 1;
}
void I2C_ACK(void)
{
  I2C1CONbits.ACKDT = 0; // 0 -> ACK
  I2C_Master_Wait();
  I2C1CONbits.ACKEN = 1; // Send ACK
}
void I2C_NACK(void)
{
  I2C1CONbits.ACKDT = 1; // 1 -> NACK
  I2C_Master_Wait();
  I2C1CONbits.ACKEN = 1; // Send NACK
}
unsigned char I2C_Master_Write(unsigned char data){
  I2C_Buffer_index=data;//放資料到I2C_DATA陣列去
  I2C_Data.R_W=I2C_write;//在中斷會把這個值傳出去
  while(I2C1STATbits.TBF); //0 =發送完成，I2CxTRN為空
  while(!IFS1bits.MI2C1IF); // 等待傳輸
  IFS1bits.MI2C1IF = 0; //傳輸完成之後會為1，要用軟體回歸0
  return I2C1STATbits.ACKSTAT;//回傳有沒有收到確認，有的話是0
}
//unsigned char I2C_Read_Byte(void)
//{
//  //---[ Receive & Return A Byte ]---
//  I2C_Master_Wait();
//  I2C1CONbits.RCEN = 1; // Enable & Start Reception
//  while(!IFS1bits.MI2C1IF); // Wait Until Completion
//  IFS1bits.MI2C1IF = 0; // Clear The Interrupt Flag Bit
//  I2C_Master_Wait();
//  return I2C1RCV; // Return The Received Byte
//}
//======================================================
//---------------[ LCD Routines ]----------------
//-----------------------------------------------
void LCD_write(unsigned char I2C_Add, unsigned char ROW, unsigned char COL , char* Str){
    while(I2C1STATbits.BCL) I2C1STATbits.BCL=0; //總線出現衝突後歸為未發生衝突
    I2C_Master_Wait(); //空閒時在做之後的動作
    LCD_Init(I2C_Add);
    LCD_Set_Cursor(ROW, COL);
    LCD_Write_String(Str);
}

void LCD_Init(unsigned char I2C_Add)
{
  i2c_add = I2C_Add;
  IO_Expander_Write(0x00);
//  wait(1000);
  delayms(60);
  LCD_CMD(0x03);
//  wait(200);
  delayms(10);
  LCD_CMD(0x03);
//  wait(200);
  delayms(10);
  LCD_CMD(0x03);
//  wait(200);
  delayms(10);
  LCD_CMD(LCD_RETURN_HOME);
//  wait(200);
  delayms(10);
  LCD_CMD(0x20 | (LCD_TYPE << 2));
//  wait(200);
  delayms(100);
  LCD_CMD(LCD_TURN_ON);
//  wait(200);
  delayms(100);
  LCD_CMD(LCD_CLEAR);
//  wait(200);
  delayms(100);
  LCD_CMD(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
//  wait(200);
    delayms(100);
}
void IO_Expander_Write(unsigned char Data)
{
  I2C_Master_Start();
  I2C_Master_Write(i2c_add); 
  I2C_Master_Write(Data | BackLight_State);
  I2C_Master_Stop();
}
void LCD_Write_4Bit(unsigned char Nibble)
{
  // Get The RS Value To LSB OF Data
  Nibble |= RS;
  IO_Expander_Write(Nibble | 0x04);
  IO_Expander_Write(Nibble & 0xFB);
//  wait(50);
  delayms(5);
}
void LCD_CMD(unsigned char CMD)
{
  RS = 0; // Command Register Select
  LCD_Write_4Bit(CMD & 0xF0);
  LCD_Write_4Bit((CMD << 4) & 0xF0);
}
void LCD_Write_Char(char Data)
{
  RS = 1; // Data Register Select
  LCD_Write_4Bit(Data & 0xF0);
  LCD_Write_4Bit((Data << 4) & 0xF0);
}
void LCD_Write_String(char* Str)
{
  int i=0;
  for(i=0; Str[i]!='\0'; i++)
    LCD_Write_Char(Str[i]);
}
void LCD_Set_Cursor(unsigned char ROW, unsigned char COL)
{
  switch(ROW) 
  {
    case 2:
      LCD_CMD(0xC0 + COL-1);
      break;
    case 3:
      LCD_CMD(0x94 + COL-1);
      break;
    case 4:
      LCD_CMD(0xD4 + COL-1);
      break;
    // Case 1
    default:
      LCD_CMD(0x80 + COL-1);
  }
}
void Backlight()
{
  BackLight_State = LCD_BACKLIGHT;
  IO_Expander_Write(0);
}
void noBacklight()
{
  BackLight_State = LCD_NOBACKLIGHT;
  IO_Expander_Write(0);
}
void LCD_SL()
{
  LCD_CMD(0x18);
//  wait(50);
  delayms(5);
}
void LCD_SR()
{
  LCD_CMD(0x1C);
//  wait(50);
  delayms(5);
}
void LCD_Clear()
{
  LCD_CMD(0x01);
//  wait(50);
  delayms(5);
}