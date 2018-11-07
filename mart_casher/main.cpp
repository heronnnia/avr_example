/*
 * mart_casher.cpp
 *
 * Created: 2018-11-07 오전 9:32:28
 * Author : jeong
 */ 

#include <avr/io.h>
#include "myfunc.h"

#define NORMAL_MODE 0
#define MENU_MODE 1
#define CALC_MODE 2




unsigned int tcnt =0, hour = 0, min = 0, sec = 0;

ISR(TIMER0_OVF_vect)
{
	tcnt++;
	if(tcnt >= 61)
	{
		sec++;
		if(sec >60) {sec = 0; min++;}
		if(min >60) {min = 0; hour++;}
		if(hour > 23){hour = min = sec = 0;}
		tcnt = 0;
	}
	
}

int main(void)
{
	init();

    /* Replace with your application code */
    while (1) 
    {
		int input = getkey();		
		displayclk(hour,min,sec);

			 char str[16];
			sprintf(str,"%3d",input);
			lcd_putsf(0,1,(unsigned char *)str);			


    }
}

