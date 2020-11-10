/*
 * mk_graphic.c
 *
 * Created: 15.08.2018 15:22:48
 *  Author: Marek Twardowski
 *  Biblioteka oparta na poradnikach mirekk36 z atnel.pl
 *  Zbudowana na podstawie gotowej biblioteki dla Arduino tj. Adafruit
 */

#define F_CPU 1000000UL //_delay_ms();
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "mk_ssd1306.h"

int cursor_x, cursor_y;


// funkcja do rysowania bitmapy
void mk_ssd1306_drawBitmap_P( int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color) {
	
	int i,j, byteWidth = ( w + 7 ) / 8;  //jezeli chcemy wyswietlic cos co nie ma pe³nego bajtu dlatego trzeba tez przewidziec mozliwosc wyswietlenia bitu
	
	for (j=0; j<h; j++){
		for (i=0; i<w; i++){
			if( pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)) ){
				mk_ssd1306_setPixel(x+i, y+j, color);
			}
		}
	}
}


// funkcja do rysowania pojedynczego znaku
void mk_ssd1306_drawChar (int x, int y, char c, uint8_t color, uint8_t bg, uint8_t size){
	
	if ((x >= SSD1306_WIDTH) || (y >= SSD1306_HEIGHT) || ((x + 6 * size - 1) < 0) || ((y + 8 * size - 1) < 0))
	return;
	
	uint8_t line;
	
	for (int8_t i=0; i<6; i++ ){
		
		if (i == 5)
		line = 0x0;
		else
		line = pgm_read_byte(font+(c*5)+i);
		
		for (int8_t j = 0; j<8; j++ ){
			if (line & 0x1) {
				if (size == 1)
				mk_ssd1306_fillRect(x+i, y+j,size, size, color);
				else {
					mk_ssd1306_fillRect(x+(i*size), y+(j*size), size, size, color);
				}
				} else if (bg != color) {
				if (size == 1)
				mk_ssd1306_setPixel(x+i, y+j, bg);
				else {
					mk_ssd1306_fillRect(x+i*size, y+j*size, size, size, bg);
				}
			}
			line >>= 1;
		}
	}
}


void mk_ssd1306_puts(int x, int y, char * str, uint8_t txt_size, uint8_t color, uint8_t bg){
	
	cursor_x = x;
	cursor_y = y;
	
	while (*str) {
		mk_ssd1306_drawChar(cursor_x, cursor_y, *str++, color, bg, txt_size);
		cursor_x += txt_size*6;
	}
	
}

void mk_ssd1306_puts_int(int x, int y, int data, uint8_t txt_size, uint8_t color, uint8_t bg){
	
	char buf[16];
	mk_ssd1306_puts( x, y, itoa( data, buf, 10 ), txt_size, color, bg);
	
}



void mk_ssd1306_fillRect(int x, int y, int w, int h, uint8_t color ){
	
	for (int16_t i=x; i<x+w; i++)
	{
		mk_ssd1306_drawFastVLine(i, y, h, color);
	}
	
}

void mk_ssd1306_drawFastVLine(int x, int y, int h, uint8_t color){
	
	mk_ssd1306_drawLine(x, y, x, y+h-1, color);
	
}

void mk_ssd1306_drawLine(int x0, int y0, int x1, int y1, uint8_t color ){
	
	int steep = abs(y1 - y0) > abs (x1 - x0);
	
	if (steep){
		swap (x0, y0);
		swap (x1, y1);
	}
	
	if (x0 > x1) {
		swap (x0, x1);
		swap (y0, y1);
	}
	
	int dx, dy;
	dx = x1-x0;
	dy = abs(y1 - y0);
	
	int err= dx / 2;
	int ystep;
	
	if (y0 < y1){
			ystep = 1;
		}
		else{
			ystep = -1;
		}
		
	for (; x0 <= x1; x0++) {
		if(steep){
			mk_ssd1306_setPixel(y0,x0,color);
		}else {
			mk_ssd1306_setPixel(x0,y0,color);
		}		
		err -= dy;
		if (err < 0){
			y0 += ystep;
			err +=dx; 
		}
		}	
}

