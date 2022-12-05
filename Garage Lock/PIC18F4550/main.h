#include <18F4550.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(crystal=4000000)
#use FIXED_IO( A_outputs=PIN_A1,PIN_A0 )
#define motorForward   PIN_A0
#define motorBackward   PIN_A1

char pressedBtn = 'I';
int isBtnPressed = 0;

char getPressedBtn()
{
   
   //Check Col1
   output_high(pin_d0);
   if(input(pin_d3))
   {
      delay_ms(25);
      //printf(lcd_putc,"\f1");
      isBtnPressed = 1;
      return '1';
   }
   else if(input(pin_d4))
   {
      delay_ms(25);
      //printf(lcd_putc,"\f4");
      isBtnPressed = 1;
      return '4';
   }
   else if(input(pin_d5))
   {
      delay_ms(25);
      //printf(lcd_putc,"\f7");
      isBtnPressed = 1;
      return '7';
   }
   else if(input(pin_d6))
   {
      delay_ms(25);
      //printf(lcd_putc,"\f*");
      isBtnPressed = 1;
      return '*';
   }
   
   output_low(pin_d0);

   //Check Col2
   output_high(pin_d1);
   if(input(pin_d3))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f2");
      return '2';
   }
   else if(input(pin_d4))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f5");
      return '5';
   }
   else if(input(pin_d5))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f8");
      return '8';
   }
   else if(input(pin_d6))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f0");
      return '0';
   }
   output_low(pin_d1);

   //Check Col3
   output_high(pin_d2);
   
   if(input(pin_d3))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f3");
      return '3';
   }
   else if(input(pin_d4))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f6");
      return '6';
   }
   else if(input(pin_d5))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f9");
      return '9';
   }
   else if(input(pin_d6))
   {
      delay_ms(25);
      isBtnPressed = 1;
      //printf(lcd_putc,"\f#");
      return '#';
   }
   
   output_low(pin_d2);
   delay_ms(25);
   return 'I'; //Herhangi bir tu�a bas�lmad�
}