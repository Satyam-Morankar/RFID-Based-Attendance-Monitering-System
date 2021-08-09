#include<reg51.h>
#include<string.h>
#include<stdio.h>
#define lcdport P1

sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
sbit m1=P2^4;
sbit m2=P2^5;
sbit buzzer=P2^6;
char i,rx_data[50];
char rfid[13],ch=0;
int count1, count2, count3;
unsigned char result[1];

 void delay(int itime)
{
    int i,j;
    for(i=0;i<itime;i++)
    for(j=0;j<1275;j++);
}

void daten()
{
    rs=1;
    rw=0;
    en=1;
    delay(5);
    en=0;
}

void lcddata(unsigned char ch)
{
    lcdport=ch & 0xf0;
    daten();
    lcdport=(ch<<4) & 0xf0;
    daten();
}

void cmden(void)
{
    rs=0;
    en=1;
    delay(5);
    en=0;
}

void lcdcmd(unsigned char ch)
{
    lcdport=ch & 0xf0;
    cmden();
    lcdport=(ch<<4) & 0xf0;
    cmden();
}

void lcdstring(char *str)
{
    while(*str)
    {
        lcddata(*str);
        str++;
    }
}

void lcd_init(void)
{
    lcdcmd(0x02);
    lcdcmd(0x28);
    lcdcmd(0x0e);
    lcdcmd(0x01);
}

void uart_init()
{
 TMOD=0x20;
 SCON=0x50;
 TH1=0xfd;
 TR1=1;
}
char rxdata()
{
  while(!RI);
    ch=SBUF;    
    RI=0;
    return ch;
}

void main()
{
    buzzer=1;
    uart_init();
    lcd_init();
    lcdstring("  RFID Based    ");
    lcdcmd(0xc0);
    lcdstring("Attendance Systm"); 
    delay(400);
    while(1)
    {
        lcdcmd(1);
        lcdstring("Place Your Card:");
        lcdcmd(0xc0);
        i=0;
        for(i=0;i<12;i++)
        rfid[i]=rxdata();
        rfid[i]='\0';
        lcdcmd(1);
        lcdstring("Your ID No. is:");
        lcdcmd(0xc0);
        for(i=0;i<12;i++)
        lcddata(rfid[i]);
        delay(100);
        if(strncmp(rfid,"160066A5EC39",12)==0)
        {
            count1++;
            lcdcmd(1);
            lcdstring(" Attendance ");
            lcdcmd(0xc0);
            lcdstring(" Registered");
            delay(200);
            lcdcmd(1);
            lcdstring(" Student1 ");
            lcdcmd(0xc0);
            lcdstring("Attnd. No.: ");
            sprintf(result, "%d", count1);
            lcdstring(result);
            
            m1=1;
            m2=0;
            delay(300);
            m1=0;
            m2=0;
            delay(200);
            m1=0;
            m2=1;
            delay(300);
            m1=0;
            m2=0;
        }
        
        else if(strncmp(rfid,"160066BD7AB7",12)==0)
            {
            count2++;
            lcdcmd(1);
            lcdstring(" Attendance ");
            lcdcmd(0xc0);
            lcdstring(" Registered");
            delay(200);
            lcdcmd(1);
            lcdstring(" Student2 ");
            lcdcmd(0xc0);
            lcdstring("Attnd. No.: ");
            sprintf(result, "%d", count2);
            lcdstring(result);
            
            m1=1;
            m2=0;
            delay(300);
            m1=0;
            m2=0;
            delay(200);
            m1=0;
            m2=1;
            delay(300);
            m1=0;
            m2=0;
      }
            
                else if(strncmp(rfid,"160066203060",12)==0)
            {
                count3++;
            lcdcmd(1);
            lcdstring(" Attendance ");
            lcdcmd(0xc0);
            lcdstring(" Registered");
            delay(200);
            lcdcmd(1);
            lcdstring(" Student3 ");
            lcdcmd(0xc0);
            lcdstring("Attnd. No.: ");
            sprintf(result, "%d", count3);
            lcdstring(result);
            
            m1=1;
            m2=0;
            delay(300);
            m1=0;
            m2=0;
            delay(200);
            m1=0;
            m2=1;
            delay(300);
            m1=0;
            m2=0;

            }

        else 
        {
           lcdcmd(1);
           lcdstring("Invalid Card");
           buzzer=0;
           delay(300);
           buzzer=1;
        }
  }
}