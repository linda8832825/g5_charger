#include "Main_Define.h"

unsigned char RS, i2c_add, BackLight_State = LCD_BACKLIGHT;
I2C_Data_Define I2C_Data;
unsigned char I2C_Buffer;
//---------------[ LCD應用]-------------------
//--------------------------------------------------
void First_Write_to_LCD(){
    LCD_Clear();
    delay(2);
    LCD_write_Char(1, 1 , "Voltage:");//顯示電壓 //1-8
    LCD_write_Variable(1, 9 , G5_Data.Voltage); //9-12  
    LCD_write_Char(1, 13 , "V");//13
    LCD_write_Char(1, 14 , "       ");//14-20

    delay(1);
    LCD_write_Char(2, 1 , "Current:");//顯示電流 //1-8
    LCD_write_Variable(2, 9 , G5_Data.Current); //9-12
    if(G5_Data.Current < 0x64){ //小於10A
        LCD_write_Char(2, 12 , "A"); //12
        LCD_write_Char(2, 13 , "        ");//13-20
    }
    else{
        LCD_write_Char(2, 13 , "A"); //13
        LCD_write_Char(2, 14 , "       ");//14-20
    }

    delay(1);
    LCD_write_Char(3, 1 , "NowAh:");//顯示現在安時數 //1-6
    LCD_write_Variable(3, 7 , G5_Data.Residual_Electricity); //7-10
    LCD_write_Char(3, 11 , "Ah");//11-12
    LCD_write_Char(3, 13 , "        ");//13-20

    delay(1);
    LCD_write_Char(4, 1 , "FullAh:");//顯示滿安時數 //可能要在還沒做完前不需要顯示這個嗎? 或是看看之前回來寫過多少安時數了 //1-7
    LCD_write_Variable(4, 8 , G5_Data.Nominal_Battery_Capacity); //8-11
    LCD_write_Char(4, 12 , "Ah"); //12-13
    LCD_write_Char(4, 14 , "       "); //14-20
    delay(2);
}
void Other_Time_Write_to_LCD(){
    delay(1);
    LCD_write_Variable(1, 9 , G5_Data.Voltage);    
    LCD_write_Variable(2, 9 , G5_Data.Current);
    LCD_write_Variable(3, 7 , G5_Data.Residual_Electricity);
    LCD_write_Variable(4, 8 , G5_Data.Nominal_Battery_Capacity);
    delay(1);
}
void LCD_write_Char(unsigned char ROW, unsigned char COL , char* Str){
    while(I2C1STATbits.BCL) I2C1STATbits.BCL=0; //總線出現衝突後歸為未發生衝突
    LCD_Set_Cursor(ROW, COL);
    LCD_Write_String(Str);
}
void LCD_write_Variable(unsigned char ROW, unsigned char COL , unsigned int variable){
    char no;
    int row,col,math_a;
    row=ROW;
    col=COL;
    while(I2C1STATbits.BCL) I2C1STATbits.BCL=0; //總線出現衝突後歸為未發生衝突
    LCD_Set_Cursor(row, col);
    sprintf(&no, "%d", variable/10); 
    LCD_Write_String(&no);//十位數和個位數
    if(variable < 0x64) math_a=1;//如果要顯示的數只有個位數 例如電流
    else math_a=2;
    LCD_Set_Cursor(row, col+math_a);
    LCD_Write_String(".");
    LCD_Set_Cursor(row, (col+math_a+1));
    sprintf(&no, "%d", variable%10); //第幾顆電池
    LCD_Write_String(&no);//小數點後第一位
}
//======================================================
//---------------[ I2C Routines ]-------------------
//--------------------------------------------------
void I2C_Master_Wait(){
    while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
}
void I2C_Master_Start(){
    I2C_Master_Wait();
    I2C1CONbits.SEN = 1;
}
void I2C_Master_RepeatedStart(){
    I2C_Master_Wait();
    I2C1CONbits.RSEN = 1;
}
void I2C_Master_Stop(){
    I2C_Master_Wait();
    I2C1CONbits.PEN = 1;
}
void I2C_ACK(void){
    I2C1CONbits.ACKDT = 0; // 0 -> ACK
    I2C_Master_Wait();
    I2C1CONbits.ACKEN = 1; // Send ACK
}
void I2C_NACK(void){
    I2C1CONbits.ACKDT = 1; // 1 -> NACK
    I2C_Master_Wait();
    I2C1CONbits.ACKEN = 1; // Send NACK
}
unsigned char I2C_Master_Write(unsigned char data){
    I2C_Buffer=data;//放資料到I2C_DATA陣列去
    I2C_Data.R_W=I2C_write;//在中斷會把這個值傳出去
    I2C_Data.TIF=0;//允許傳送
    while(I2C1STATbits.TBF && IFS1bits.MI2C1IF); //0 =發送完成，I2CxTRN為空  // 等待傳輸
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
//
//---------------[ LCD Routines ]----------------
//-----------------------------------------------
void LCD_Init(unsigned char I2C_Add)
{
    i2c_add = I2C_Add;
    IO_Expander_Write(0x00);
    delayms(30);
    LCD_CMD(0x03);
    delayms(5);
    LCD_CMD(0x03);
    delayms(5);
    LCD_CMD(0x03);
    delayms(5);
    LCD_CMD(LCD_RETURN_HOME);
    delayms(5);
    LCD_CMD(0x20 | (LCD_TYPE << 2));
    delayms(50);
    LCD_CMD(LCD_TURN_ON);
    delayms(50);
    LCD_CMD(LCD_CLEAR);
    delayms(50);
    LCD_CMD(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
    delayms(50);
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
  delayms(1);
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
  delayms(1);
}
void LCD_SR()
{
  LCD_CMD(0x1C);
  delayms(1);
}
void LCD_Clear()
{
  LCD_CMD(0x01);
  delayms(1);
}