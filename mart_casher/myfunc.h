/*
 * myfunc.h
 *
 * Created: 2018-09-12 오후 2:09:29
 *  Author: USER
 */ 


#ifndef MYFUNC_H_
#define MYFUNC_H_

#include <avr/io.h>
#define F_CPU 16000000
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define KEY_1 238
#define KEY_2 222
#define KEY_3 190
#define KEY_4 237
#define KEY_5 221
#define KEY_6 189
#define KEY_7 235
#define KEY_8 219
#define KEY_9 187
#define KEY_0 231
#define KEY_Sum 126
#define KEY_ENT 125
#define KEY_MENU 123
#define KEY_ROB 119
#define KEY_DIV 183

unsigned int hour = 0, min = 0, sec = 0;

void init()
{
	DDRA = 0xff;
	DDRD = 0x0f;
	
	lcd_init();
	lcd_clear();
	
	for(int i = 0; i< 2; i++)
	{
		lcd_putsf(0,0,(unsigned char *)" 	market   ");
		lcd_putsf(0,1,(unsigned char *)"    system    ");
		PORTA = 0b00000000;
		_delay_ms(100);
		lcd_clear();
		PORTA = 0b11100000;
		_delay_ms(100);		
	}
	sei();
}

// display setting
void displayclk()
{
	char str[16];
	sprintf(str,"  %2d:%2d:%2d", hour,min,sec);
	lcd_putsf(0,0,(unsigned char *)"  welcome!!  ");
	lcd_putsf(0,1,(unsigned char *)str);
}

unsigned char getkey()
{
	unsigned char key = 0;
	for(int i = 0; i< 4; i++)
	{
		PORTD = ~(0x00 | (1 << i));
		_delay_ms(5);
		key = ~PIND & 0xf0;
		if(key) return PIND;
	}	
	return 0;
}

#endif /* MYFUNC_H_ */