#include <main.h>
#include <string.h>
#define LCD_ENABLE_PIN PIN_B5
#define LCD_RS_PIN PIN_B7
#define LCD_RW_PIN PIN_B6
#define LCD_DATA4 PIN_B3
#define LCD_DATA5 PIN_B2
#define LCD_DATA6 PIN_B1
#define LCD_DATA7 PIN_B0

#define use_portb_lcd TRUE
#include <lcd.c>
//#include <Flex_kbd.c> // http://www.ccsinfo.com/forum/viewtopic.php?t=26333

char *password1[] = {'1','2','3','4'};
char *password2[] = {'9','7','5','3'};
char *enteredPW[] = {'X', 'X', 'X', 'X'};

int openingTime = 2; // Kap? A??lma S?resi, sn
int openDoorTime = 10; // Kap? A??k Kalma S?resi, sn
int closingTime = 2; // Kap? Kapanma S?resi, sn

void lcdClear()
{
   lcd_send_byte(0, 0x1);  
}

void CursorBlink()
{
   lcd_send_byte(0, 0x0F);  
}

int checkPW()
{
   int tryCnt1 = 0, tryCnt2 = 0;
   for(int i = 0; i < 4; i++)
   {
      if(enteredPW[i] == password1[i]) tryCnt1++;
   }
   
   for(i = 0; i < 4; i++)
   {
      if(enteredPW[i] == password2[i]) tryCnt2++;
   }
   
   if(tryCnt1 == 4 || tryCnt2 == 4) 
      {
         printf(lcd_putc, "\f   SIFRE DOGRU");
         delay_ms(2000);
         return 1; //?ifre Do?ru
      }
   else
      {
         printf(lcd_putc, "\f  SIFRE HATALI");
         delay_ms(2000);
         return 0;
      }
}

void openDoor()
{     
      printf(lcd_putc, "\f LUTFEN BEKLEYIN");
      printf(lcd_putc, "\nKAPI ACILIYOR...");
      output_low(motorForward);
      output_high(motorBackward);
      delay_ms(openingTime * 1000); //Kap? a??lma s?resi
      output_low(motorForward);
      output_low(motorBackward);
      for(int i = openDoorTime; i > 0; --i)
      {
         printf(lcd_putc, "\f   KAPI ACIK\n       %d",i);
         delay_ms(1000); //Kap? A??k Kalma S?resi
      }
}
void closeDoor()
{      
      output_high(motorForward);
      output_low(motorBackward);
      printf(lcd_putc, "\fKAPI KAPANIYOR...");
      delay_ms(closingTime * 1000); //Kap? Kapanma s?resi
      output_low(motorForward);
      output_low(motorBackward);
      printf(lcd_putc, "\f KAPI KAPANDI");
      delay_ms(2000);
}

void delFunc()
{
   for(int i = 0; i < 4; i++){enteredPW[i] = 'X';}
      
   printf(lcd_putc,"\fSIFRENIZ: %c", enteredPW[0]);
   for(i = 1; i <= 3; i++)
      {
         printf(lcd_putc,"%c", enteredPW[i]);
      }
   printf(lcd_putc, "\n#: GIRIS *: SIL");
   delay_ms(250);
}

void welcomeMsg()
{
   printf(lcd_putc, "\f LUTFEN SIFREYI\n    GIRINIZ   ");
}


void main()
{
   set_tris_d(0b01111000);
   int cnt = 0;

   lcd_init(); // LCD Display Initialize
   lcdClear(); // Clear LCD Display
   welcomeMsg();
   //loop
   for(;;)
   {  
      pressedBtn = getPressedBtn();
      if(pressedBtn != 'I' && pressedBtn != '*' && pressedBtn != '#')
      {
         //0-9 Say?lar?ndan Biri Tu?land?ysa
         //Art Arda 4 Say?dan Fazla Girilirse 4.den Sonras?n? Alma
         if(isBtnPressed && cnt < 4){
            enteredPW[cnt] = pressedBtn;
            printf(lcd_putc,"\fSIFRENIZ: %c",enteredPW[0]);
            for(int i = 1; i <= 3; i++)
            {
               printf(lcd_putc,"%c", enteredPW[i]);
            }
            printf(lcd_putc, "\n#: GIRIS *: SIL");
            delay_ms(250);
            isBtnPressed = 0;
            cnt++;
         }
      }
      
      if(pressedBtn == '#' && isBtnPressed)
      {
         int status = checkPW();
         isBtnPressed = 0;
         //?ifre girildi ?ifreyi kontrol et do?ruysa a?
         if(status == 1)
         {
            delay_ms(1000);
            openDoor();
            delay_ms(1000);
            closeDoor();
         }
         welcomeMsg();
         for(int i = 0; i < 4; i++){enteredPW[i] = 'X';}
         cnt = 0;
      }
      
      if(pressedBtn == '*' && isBtnPressed)
      {
         isBtnPressed = 0;
         //Girilen ?ifrenin Son Hanesini Sil
         cnt = 0;
         delFunc();
      }
   }
}
