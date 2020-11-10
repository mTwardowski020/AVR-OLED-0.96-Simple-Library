/*
 * mk_ssd1306.c
 *
 * Created: 15.08.2018 11:11:10
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


//bufor wyswietlacza
uint8_t ssd1306_buf[BUF_SIZE]= {
	
};

static void SPIwrite (uint8_t dat) {   //static bo bedzie uzywana w ramach tylko tego modulu
	
	uint8_t i;
	for (i = 0x80; i; i>>=1){
		SCK_LO;
		if (dat & i) MOSI_HI;
		else MOSI_LO;
		SCK_HI;
	}
}

void mk_ssd1306_cmd (uint8_t cmd){  // funkcja do wysylania komendy
	
	#if USE_CS == 1
		CS_HI;
	#endif

	DC_LO;	// stan niski na linie DC aby poinformowac sterownik ze przesylamy komende
	
	#if USE_CS == 1
		CS_LO;
	#endif
	
	SPIwrite(cmd);
	
	#if USE_CS == 1
		CS_HI;
	#endif
}

void mk_ssd1306_data(uint8_t dat){ // funkcja do wysylania danych 
	
	#if USE_CS == 1
		CS_HI;
	#endif
	
	DC_HI;
	
	#if USE_CS == 1
		CS_LO;
	#endif
	
	SPIwrite(dat);
	
	#if USE_CS == 1
		CS_HI;
	#endif
}

void mk_ssd1306_display (void){
	
	mk_ssd1306_cmd (SSD1306_SETLOWCOLUMN | 0x0);
	mk_ssd1306_cmd (SSD1306_SETHIGHCOLUMN | 0x0);
	mk_ssd1306_cmd (SSD1306_SETSTARTLINE | 0x0);
	
	#if USE_CS == 1
		CS_HI;
	#endif
	DC_HI;
	#if USE_CS == 1
		CS_LO;
	#endif
	
	for (uint16_t i=0; i<(SSD1306_WIDTH*SSD1306_HEIGHT/8);i++)
	{
		SPIwrite( ssd1306_buf[i]);
	}
	
	#if USE_CS == 1
		CS_HI;
	#endif
}


void ssd1306_InitSpi(void){
	
	MOSI_DDR |= MOSI;
	
	SCK_DDR |= SCK;
	SCK_DDR |= SCK;
	
	#if USE_RST == 1
		RST_DDR |= RST;
		RST_PORT |= RST;
	#endif 
	
	DC_DDR |= DC;
	
	#if USE_CS == 1
		CS_DDR |= CS;
		CS_PORT |= CS;
	#endif
}


//funckja do wyswietlenia jednego pixela
void mk_ssd1306_setPixel (int x, int y, uint8_t bw){
	
	if ((x<0) || (x>=SSD1306_WIDTH) || (y<0) || (y>= SSD1306_HEIGHT))
	return;
	
	if (bw) ssd1306_buf[x+ (y/8)*SSD1306_WIDTH] |= (1<<(y%8)); //zapal pixel
	else ssd1306_buf[x+ (y/8)*SSD1306_WIDTH] &= ~(1<<(y%8));   //zgas pixel
}

//czyszczenie wyswietlacza
void mk_ssd1306_cls(void){
	
	memset (ssd1306_buf, 0x00, (BUF_SIZE));
}


void mk_ssd1306_init (uint8_t vcc, uint8_t refresh) {
	
		
	ssd1306_InitSpi();
	
	#if USE_RST == 1
		RST_HI;
		_delay_ms(25);
		RST_LO;
		_delay_ms(25);
		RST_HI;
	#else
		CS_HI;
		_delay_ms(25);
		CS_LO;
		_delay_ms(25);
		CS_HI;
	#endif

	mk_ssd1306_cmd (SSD1306_DISPLAYOFF);
	mk_ssd1306_cmd (SSD1306_SETDISPLAYCLOCKDIV);
	mk_ssd1306_cmd (refresh);
	
	mk_ssd1306_cmd (SSD1306_SETDISPLAYOFFSET);
	mk_ssd1306_cmd (0x0);
	mk_ssd1306_cmd (SSD1306_SETSTARTLINE | 0x0);
	mk_ssd1306_cmd (SSD1306_CHARGEPUMP);
	
	if (vcc == SSD1306_EXTERNALVCC) mk_ssd1306_cmd (0x10);
	else mk_ssd1306_cmd (0x14);
	
	mk_ssd1306_cmd (SSD1306_MEMORYMODE);
	mk_ssd1306_cmd (0x00);
	mk_ssd1306_cmd (SSD1306_SERGEMAP | 0x1);
	mk_ssd1306_cmd (SSD1306_COMSCANDEC);
	
	mk_ssd1306_cmd (SSD1306_SETCONTRAST);
	
	if (vcc == SSD1306_EXTERNALVCC) mk_ssd1306_cmd (0x9F);
	else mk_ssd1306_cmd (0xCF);
	
	mk_ssd1306_cmd (SSD1306_SETPRECHARGE);
	
	//ssd1306 - 128x32
	#if defined SSD1306_128_32
		mk_ssd1306_cmd (SSD1306_SETMULTIPLEX);
		mk_ssd1306_cmd (0x1F);
	
		mk_ssd1306_cmd (SSD1306_SETCOMPINS);
		mk_ssd1306_cmd (0x02);
	#endif
		
	//ssd1306 -128x64
	#if defined SSD1306_128_64
		mk_ssd1306_cmd(SSD1306_SETMULTIPLEX);
		mk_ssd1306_cmd (0x3F);
				
		mk_ssd1306_cmd (SSD1306_SETCOMPINS);
		mk_ssd1306_cmd (0x12);
	#endif
	
	mk_ssd1306_cmd (SSD1306_DISPLAYALLON_RESUME);
	mk_ssd1306_cmd (SSD1306_NORMALDISPLAY);
	
	mk_ssd1306_cmd (SSD1306_DISPLAYON);
	
	
	
}


