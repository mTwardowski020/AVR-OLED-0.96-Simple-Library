/*
 * OLED_TEST1.c
 *
 * Created: 15.08.2018 11:11:10
 *  Author: Marek Twardowski
 *  Biblioteka oparta na poradnikach mirekk36 z forum atnel.pl
 *  Zbudowana na podstawie gotowej biblioteki Adafruit
 */
#define F_CPU 1000000UL //_delay_ms();
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



#include "MK_OLED/mk_ssd1306.h"
#include "bitmap3.c"

int main(void)
{
	
    /* Replace with your application code */
	
	mk_ssd1306_init(SSD1306_SWITCHCAPVCC, REFRESH_MID);
	
	// mk_ssd1306_setPixel ( 48, 45, 1);  // wyswietlenie jednego pixela
	
	
	/*
	 uint8_t i;
	for (i=0; i<128; i++)
	mk_ssd1306_setPixel(i, 20, 1);  // wyswietlenie linii poziomej z pixeli
	mk_ssd1306_display();
	_delay_ms(1000);
	*/
	
	
	/*
	mk_ssd1306_cls();
	mk_ssd1306_drawBitmap_P(0,0,bitmap3,128,64,1); // wyswietlenie bitmapy
	mk_ssd1306_display();
	_delay_ms(1000);
	*/ 
	
	/*
	mk_ssd1306_cls();
	mk_ssd1306_drawLine(0, 63, 127, 0, 1);
	mk_ssd1306_drawLine(0, 0, 127, 63, 1);  // rysowanie prostych funkcj¹
	mk_ssd1306_display();
	*/

	/*
	mk_ssd1306_cls();
	mk_ssd1306_fillRect( 20, 20, 20 , 30, 1 );	  // rysowanie prostokatow funkcja
	mk_ssd1306_display();
	*/
	
	
	
	/*
	mk_ssd1306_cls();
	mk_ssd1306_drawChar(25, 0, 'T', 1, 0, 1);  // wyœwietlenie pojedynczej literki z fontu i o okreslonym rozmiarze
	mk_ssd1306_drawChar(25+8, 0, 'E', 1, 0, 1); 
	mk_ssd1306_drawChar(25+16, 0, 'S', 1, 0, 1); 
	mk_ssd1306_drawChar(25+24, 0, 'T', 1, 0, 1); 
	mk_ssd1306_display();
	*/
	
	/*
	int i;
	for (i=0; i<500; i++){
	mk_ssd1306_cls();
	_delay_ms(25);
	mk_ssd1306_puts(15,25,"NAPIS1",2,1,0);  // Wyswietlenie stringa 
	mk_ssd1306_display();
	_delay_ms(2000);
	mk_ssd1306_display();
	mk_ssd1306_puts(15,25,"NAPIS2",2,1,0);  
	mk_ssd1306_display();
	_delay_ms(2000);
	mk_ssd1306_display();
	mk_ssd1306_puts(15,25,"NAPIS3",2,1,0); 
	mk_ssd1306_display();
	_delay_ms(2000);
	}
	*/

	
	int i=0, j=0;
	for (i=0; i<24 ; i++){
		for (j=0; j<60; j++){
			mk_ssd1306_cls();
			mk_ssd1306_puts(0,0,"TIMER MODE ",2,1,0);
			mk_ssd1306_puts_int(10,30,i,3,1,0);
			mk_ssd1306_puts(55,30,"m",2,1,0);
			mk_ssd1306_puts_int(80,30,j,3,1,0);  //jakiœ tam przykladowy licznik niezwi¹zany z prawdziwym czasem
			mk_ssd1306_puts(117,30,"s",2,1,0);
			mk_ssd1306_display();
			_delay_ms(200);
		}
	
	}
	
    while (1) 
    {
		
    }
}

