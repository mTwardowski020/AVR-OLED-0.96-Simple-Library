/*
 * mk_ssd1306.h
 *
 * Created: 15.08.2018 11:11:10
 *  Author: Marek Twardowski
 *  Biblioteka oparta na poradnikach mirekk36 z atnel.pl 
 *  Zbudowana na podstawie gotowej biblioteki Adafruit
 */ 

#define F_CPU 1000000UL //_delay_ms();
#ifndef MK_SSD1306_H_
#define MK_SSD1306_H_

//definicje stalych preprocesora

// rozdzielczosc OLED
#define SSD1306_128_64
// #define SSD_1306_128_32  *alternatywnie*

#define USE_CS	0
#define USE_RST 1   //Zdefiniowanie czy uzywamy pinu 5 jako RST czy jako CS, poniewaz niektóre wyœwietlacze posiadaj¹ tylko jeden z tych dwoch pinów i jest to bardziej uniwersalna biblioteka


#define SCK	 (1<<7)		//		<----- SCL  ----- CLK
#define MOSI (1<<6)		//		<----- SDA  ----- DIN
#define RST  (1<<5)		//		<----- RST  ----- RES
#define DC	 (1<<4)		//		<----- D/C  ----- DC

#define CS	 (1<<5)     //		<----- CS   ----- CS


#define SCK_PORT	PORTA
#define SCK_DDR		DDRA

#define MOSI_PORT	PORTA
#define MOSI_DDR	DDRA

#define RST_PORT	PORTA		// To pozwoli nam pozniej na dowolna konfiguracje portów dla ka¿dej nó¿ki osobno
#define RST_DDR		DDRA

#define DC_PORT		PORTA
#define DC_DDR		DDRA

#define CS_PORT		PORTA
#define	CS_DDR		DDRA




#define RST_LO	RST_PORT	&= ~RST
#define RST_HI 	RST_PORT	|= RST

#define CS_LO	CS_PORT	&= ~CS
#define CS_HI 	CS_PORT	|= CS

#define DC_LO	DC_PORT	&= ~DC
#define DC_HI 	DC_PORT	|= DC

#define SCK_LO	SCK_PORT	&= ~SCK
#define SCK_HI 	SCK_PORT	|= SCK

#define MOSI_LO	MOSI_PORT	&= ~MOSI
#define MOSI_HI 	MOSI_PORT	|= MOSI




#define SSD1306_WIDTH			128		//definicje stalych wymiarow wyswietlacza

#if defined SSD1306_128_64
	#define SSD1306_HEIGHT		64
#endif
#if defined SSD1306_128_32
	#define SSD1306_HEIGHT		32
#endif

#define BUF_SIZE (SSD1306_WIDTH*SSD1306_HEIGHT/8)

#define REFRESH_MIN 0x80				// definicje odswiezania dla wyswietlacza
#define REFRESH_MID	0xB0
#define REFRESH_MAX	0xF0


				// definicje z AdaFruit
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define	SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF	0xAE
#define SSD1306_DISPLAYON	0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE	0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE	0x20

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SERGEMAP	0xA0

#define	SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A


#define swap(a, b) { int16_t t = a; a = b; b = t; }


//deklaracje zmiennych

extern const uint8_t font[];
extern int cursor_x, cursor_y;



//deklaracje funkcji

void mk_ssd1306_init (uint8_t vcc, uint8_t refresh);
void mk_ssd1306_cmd (uint8_t cmd);
void mk_ssd1306_data(uint8_t dat);


void mk_ssd1306_display (void);
void mk_ssd1306_setPixel (int x, int y, uint8_t bw);
void mk_ssd1306_cls(void);


						// funkcje *graficzne*
void mk_ssd1306_drawBitmap_P( int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
void mk_ssd1306_drawChar (int x, int y, char c, uint8_t color, uint8_t bg, uint8_t size);
void mk_ssd1306_puts(int x, int y, char * str, uint8_t txt_size, uint8_t color, uint8_t bg);
void mk_ssd1306_puts_int(int x, int y, int data, uint8_t txt_size, uint8_t color, uint8_t bg);
void mk_ssd1306_fillRect(int x, int y, int w, int h, uint8_t color );
void mk_ssd1306_drawFastVLine(int x, int y, int h, uint8_t color);
void mk_ssd1306_drawLine(int x0, int y0, int x1, int y1, uint8_t color );


#endif /* MK_SSD1306_H_ */