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
#define TOTAL_MODE 3
long long tcnt =0, hour = 0, min = 0, sec = 0;
int mode = 0;
int flag = 0;
unsigned int current_price = 0;
unsigned int total_price = 0;
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
		if(mode == NORMAL_MODE)
		{
			displayclk(hour,min,sec);
			if(input == KEY_MENU)
			mode = MENU_MODE;
			
			
		}
		else if(mode == MENU_MODE)
		{
			lcd_clear();
			lcd_putsf(0,0,(unsigned char *)"1. calculation");
			lcd_putsf(0,1,(unsigned char *)"2. total sales");
			if(input == KEY_1)
			{
				mode = CALC_MODE;
				
			}
			else if(input == KEY_2)
			{
				mode = TOTAL_MODE;
			}
		}
		else if(mode == CALC_MODE)
		{
			lcd_clear();
			lcd_putsf(0,0,(unsigned char *)" calculation mode");
			if (flag == 0)
			{
				if(input == KEY_1) current_price = (current_price * 10) + 1;
				else if(input == KEY_2) current_price = (current_price * 10) + 2;		
				else if(input == KEY_3) current_price = (current_price * 10) + 3;
				else if(input == KEY_4) current_price = (current_price * 10) + 4;	
				else if(input == KEY_5) current_price = (current_price * 10) + 5;				
				else if(input == KEY_6) current_price = (current_price * 10) + 6;				
				else if(input == KEY_7) current_price = (current_price * 10) + 7;				
				else if(input == KEY_8) current_price = (current_price * 10) + 8;				
				else if(input == KEY_9) current_price = (current_price * 10) + 9;
				else if(input == KEY_0) current_price = (current_price * 10) + 0;		
				else if(input == KEY_Sum) {
					total_price = total_price +current_price;
					current_price = 0;
					}
				flag = 1;													
			}
			if(input == 0) flag = 0;
			char str[16];
			sprintf(str,"%lld", current_price);
			lcd_putsf(0,1,(unsigned char *)str);
			
		}
		else if(mode == TOTAL_MODE)
		{

			lcd_putsf(0,0,(unsigned char *)" total sales ");
		}

    }
}

