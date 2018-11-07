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
		PORTA = 0b11111111;
		_delay_ms(100);		
	}

}

// FREQ SETTING

// getkey func
//unsigned char getkey()
//{
	//unsigned char key = 0;    // 변수 선언 key
	//for (int i=0; i<3; i++)
	//{
		//PORTE = ~(0x00 | (1 << i));  // 11111111 | 1 << i
		 ////porte :11111110(port d0), 11111101(port d1), 11111011(port d2), 11110111(port d3);
		//_delay_ms(5);
		//key = (~PINE & 0xf0);  // port in d 0000 1111 & 1111 0000 = 00000000
		 ////port in d 0000 0001 & 1111 0000 = 00001110
		 ////port in d 0000 0010 & 1111 0000 = 00001101
		 ////port in d 0000 0100 & 1111 0000 = 00001011
		//
		//if (key) return (key | (PORTE & 0x0f));// return key or 0b00001111
	//}
	//return 0; // 작업을 완료하고 0으로 리턴
//}

unsigned int my_getkey()
	{
	unsigned int key = 0, result = 0;
	for(int i=0;i<3;i++){
		if(i==0) PORTE = 0b11111110;
		if(i==1) PORTE = 0b11111101; //
		if(i==2) PORTE = 0b11111011;
		
		_delay_us(5);
		
		key = (~PINE & 0xf0); // 0001 0000 & 1111 0000 = 0001 0000
		if(key)
		{
			result = key | (PORTE & 0x0f); // 0001 0000 | 0000 1110  == 00011110
			return result;
		}
	}
	return 0;
}

#endif /* MYFUNC_H_ */