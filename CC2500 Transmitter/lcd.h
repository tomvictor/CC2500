/*
 * lcd.h
 *
 *  Created on: Mar 14, 2015
 *      Author: tom victor
 */
#ifndef LCD_H_
#define LCD_H_

#include <msp430g2553.h>

#define LCD_PxOUT         P2OUT
#define LCD_PxDIR         P2DIR
#define LCD_D4 BIT0
#define LCD_D5 BIT1
#define LCD_D6 BIT2
#define LCD_D7 BIT3
#define LCD_EN BIT4
#define LCD_RS BIT5
#define LCD_RW BIT6
#define DR LCD_PxOUT = LCD_PxOUT | LCD_RS // define RS high
#define CWR LCD_PxOUT = LCD_PxOUT & (~LCD_RS) // define RS low
#define READ LCD_PxOUT |= LCD_RW // define Read signal R/W = 1 for reading
#define WRITE P1OUT = P1OUT & (~LCD_RW) // define Write signal R/W = 0 for writing
#define ENABLE_HIGH LCD_PxOUT = LCD_PxOUT | LCD_EN // define Enable high signal
#define ENABLE_LOW LCD_PxOUT = LCD_PxOUT & (~LCD_EN) // define Enable Low signal
unsigned int i;
unsigned int j;
//void delay(unsigned int k)
//{

//for(j=0;j<=k;j++)
//{
//for(i=0;i<100;i++);
//}}
void data_write(void)
{
ENABLE_HIGH;
__delay_cycles(2000);

ENABLE_LOW;
}

void data_read(void)
{
ENABLE_LOW;
__delay_cycles(2000);

ENABLE_HIGH;
}
void check_busy(void)
{
	LCD_PxDIR &= ~(LCD_D7); // make P1.3 as input
while((LCD_PxDIR&LCD_D7)==1)
{
data_read();
}
LCD_PxDIR |= LCD_D7; // make P1.3 as output
}
void send_command(unsigned char cmd)
{
check_busy();
WRITE;
CWR;
LCD_PxOUT = (LCD_PxOUT & 0xF0)|((cmd>>4) & 0x0F); // send higher nibble
data_write(); // give enable trigger
LCD_PxOUT = (LCD_PxOUT & 0xF0)|(cmd & 0x0F); // send lower nibble
data_write(); // give enable trigger
}
void send_data(unsigned char data)
{
check_busy();
WRITE;
DR;
LCD_PxOUT = (LCD_PxOUT & 0xF0)|((data>>4) & 0x0F); // send higher nibble
data_write(); // give enable trigger
LCD_PxOUT = (LCD_PxOUT & 0xF0)|(data & 0x0F); // send lower nibble
data_write(); // give enable trigger
}
void send_string(char *s)
{
while(*s)
{
send_data(*s);
s++;
}
}
void lcd_init(void)
{
LCD_PxDIR |= 0xFF;
LCD_PxOUT &= 0x00;
P1OUT |=0xFF;
send_command(0x33);//33
send_command(0x32);
send_command(0x28); // 4 bit mode
send_command(0x0E); // clear the screen
send_command(0x01); // display on cursor on
send_command(0x06); // increment cursor
send_command(0x80); // row 1 column 1
}


#endif /* LCD_H_ */
