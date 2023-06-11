#include<reg51.h>
#define lcd P3
sbit FLAME=P1^0;
sbit GAS=P1^1;
sbit rs=P2^0; //register select
sbit rw=P2^1; //RW
sbit en=P2^2; //enable
sbit buzzer = P2^3;

void lcd_init();
void cmd(unsigned char);
void dat(unsigned char);
void delay(unsigned int);
void lcd_string(char *s);
 
void main()
{
    lcd_init();
    while(1) {
    if(GAS == 1 || FLAME == 1) 
		{
			cmd(0x01);
			cmd(0x80);
			lcd_string("     WARNING    ");
      cmd(0xc0);
      lcd_string("  Fire Detected ");
			buzzer = 1;
      		delay(100);
    } else 
		{
			cmd(0x01);
			cmd(0x80);
			lcd_string("   FIRE ALARM   ");
      cmd(0xc0);
      lcd_string("     NORMAL     ");
			buzzer = 0;
			delay(100);
        }
    }
}
 
void lcd_init()
{
    cmd(0x38);
    cmd(0x0e);
    cmd(0x06);
    cmd(0x01);
    cmd(0x80);
}
 
void cmd(unsigned char a)
{
    lcd=a;
    rs=0;
    rw=0;
    en=1;
    delay(1);
    en=0;
}
 
void dat(unsigned char b)
{
    lcd=b;
    rs=1;
    rw=0;
    en=1;
    delay(1);
    en=0;
}
 
void lcd_string(char *s)
{
    while(*s) {
       dat(*s++);
     }
}
 
void delay(unsigned int t)
{
    unsigned int i,z;
    for(i=0;i<t;i++)
    for (z=0; z<500; z++) ;
}
