/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.05.05.01 [25 Nov 2020]
* Device(s)    : R5F100MJ
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 2022-03-22
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
unsigned char f_timer_500ms;
unsigned char f_seg_timer_500ms;
extern unsigned char f_timer_100us;
extern unsigned char f_timer_10ms;

unsigned char f_timer_30ms;
unsigned char i,p_tx1,p_tx2;
unsigned char flag_digit_1;
unsigned char tx[3];
unsigned char test[6]={"HELLO\n"};
unsigned char tx2_buffer[10]={"123456789"};
unsigned char tx1_buffer[6]={"abcdef"};

unsigned char rx_buffer1[64];
unsigned char rx_buffer2[64];

unsigned char bufferEvent[64];
unsigned char d_timer_30ms;
unsigned char d_timer_500ms;

unsigned char key1_data, key2_data;
unsigned char state,event;
unsigned char e_rp,e_wp;
unsigned char rx1_rp,rx1_wp;
unsigned char rx2_rp,rx2_wp;


unsigned char uart_tx1_flag,uart_tx2_flag;
unsigned char flag_state_tx1, flag_state_tx;

unsigned char digit1,digit2;
char seven_segment_table[17] = {	0b1111110,	// '0'
		    	0b0110000,	// '1'	
		   	0b1101101,	// '2'
			0b1111001,	// '3'
			0b0110011,	// '4'
			0b1011011,	// '5'
			0b1011111,	// '6'
			0b1110000,	// '7'
			0b1111111,	// '8'
			0b1111011,	// '9'
			0b1111101,	// 'a'  --10
			0b0011111,	// 'b'  --11
			0b0001101,	// 'c'  --12
			0b0111101,	// 'd'  --13
			0b1101111,	// 'e'	--14 
			0b1000111,	// 'f'  --15
			0b0000001 	// '-'  --16

};	

void task_timer(void);
void counting_task(void);
void uart_TX2_task(void);
void uart_TX1_task(void);
void uart_RX1_task(void);
void uart_RX2_task(void);
void led_display_task(void);
void key_read_task(void);
void main_task(void);
void setEvent(unsigned char event);
unsigned char getEvent(void);
void seven_segment_driver(char input);
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    R_TAU0_Channel0_Start();
    R_TAU0_Channel1_Start();
    R_UART1_Start();
    R_UART3_Start();
    LED=1;
    pin_digit1=1;
    pin_digit2=0;
    digit1=0;
    digit2=0;
  	
	
    while (1U)
    {	
	  
	     task_timer();
	     led_display_task();
	     key_read_task();
  	    
	     uart_RX2_task();
	     uart_RX1_task();
	     
	     main_task();
    }
   
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */

    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */



void uart_RX2_task(void)
{
	
	if(rx2_rp==rx2_wp) return;
	
	switch(rx_buffer2[rx2_rp++])
	{
		case 'a':
			digit2=10;
			break;
		case 'b':
			digit2=11;
			break;
		case 'c':
			digit2=12;
			break;
		case 'd':
			digit2=13;
			break;
		case 'e':
			digit2=14;
			break;
		case 'f':
			digit2=15;
			break;
		default:
			break;
	}
	
	if(rx2_rp>63){
    		rx2_rp=0;
   	 }
    	
	
}


void uart_RX1_task(void)
{
	
	if(rx1_rp==rx1_wp) return;

	switch(rx_buffer1[rx1_rp++])
	{	
		case '0':
			digit1=0;
			break;
		case '1':
			digit1=1;
			break;
		case '2':
			digit1=2;
			break;
		case '3':
			digit1=3;
			break;
			
		case '4':
			digit1=4;	
			break;
		case '5':
			digit1=5;
			break;
		case '6':
			digit1=6;
			break;
		case '7':
			digit1=7;
			break;
		case '8':
			digit1=8;
			break;
		case '9':
			digit1=9;			
			break;
		default:
			break; 
	}
	
	if(rx1_rp>63){
    		rx1_rp=0;
   	 }
    
}

void led_display_task(void)
{
   if(!f_timer_100us) return;  		
   f_timer_100us =0;
      
   if(pin_digit1^=1){
   	seven_segment_driver(seven_segment_table[digit1]);
   }
   if(pin_digit2^=1){
 	seven_segment_driver(seven_segment_table[digit2]);
   }
    
/*	
   flag_digit_1^=1;
   
   if(flag_digit_1){
   	pin_digit1 =1;
   	pin_digit2 =0;
   	seven_segment_driver(seven_segment_table[digit1]);
	
   }else{
   	pin_digit1 =0;
   	pin_digit2 =1;
   	seven_segment_driver(seven_segment_table[digit2]);
   }
   */
}

void task_timer(void)
{
	if(!f_timer_10ms) return;       // checking if 10 ms timer interrupt is set (10 ms), if set then do timer task
	f_timer_10ms =0;		// clear the flag to wait next interupt
	
	d_timer_30ms++;			// count timer for 30 ms interval
				// count timer for LED interval
	
	if(d_timer_30ms==3)		// checking if the count reached 30 ms 
	{
		d_timer_30ms =0;	// assign "0" to repeat counting
		f_timer_30ms=1;		// Set flag to inform 30 ms timer is done counting 
	}
	
	d_timer_500ms++;
	if(d_timer_500ms==50)     // checking if the count reached LED interval 
	{
		d_timer_500ms=0;
		f_timer_500ms=1;// assign "0" to repeat counting
		
	}

	
}

void key_read_task(void)
{
	if(!f_timer_30ms) return;  		 // Checking if 30 ms counting is done
	f_timer_30ms =0;          		 // clear the flag to wait next counting 
	
	key1_data = key1_data<<1;      		 //Preparing to read KEY1 Input
	key1_data &= 0b00001110;
	key1_data |= KEY1;			 // Read KEY1 Input
	
	key2_data = key2_data<<1;		 //Preparing to read KEY2 Input
	key2_data &= 0b00001110;
	key2_data |= KEY2;			 // Read KEY2 Input
	
	if(key1_data == KEY_PRESSED)    	 // Checking if KEY1 is pressed
	{
		setEvent(EVENT_KEY1_PRESSED);    // Store the event in buffer
	}
		
	if(key1_data == KEY_RELEASED)		//  Checking if KEY1 is released
	{
		setEvent(EVENT_KEY1_RELEASED); // Store the event in buffer
	}
	
	if(key2_data == KEY_PRESSED)		// Checking if KEY2 is pressed
	{
		setEvent(EVENT_KEY2_PRESSED); // Store the event in buffer
	}
	
	if(key2_data == KEY_RELEASED)		//  Checking if KEY2 is released
	{
		setEvent(EVENT_KEY2_RELEASED); // Store the event in buffer
	}
	
}


void main_task(void)
{
	
	if (e_rp!=e_wp){ 
		event = getEvent();   // if there is event then get the event from buffer	
	}else{
		event= EVENT_NO_ENTRY;
	}
	switch(state)
	
	{       case STATE_IDLE:		// if KEY1 was pressed then start up counting
			
			
			switch(event)
			{
			case EVENT_KEY1_PRESSED:
					
				state = STATE_TX1;
				break;
					
			case EVENT_KEY2_PRESSED:
					
				state = STATE_TX2;
				break;	
			}	
			
			break;
		
		
		case STATE_TX1:	     // if KEY2 was pressed then start down counting
			
			uart_TX1_task();
			switch(event)
			{
			 case EVENT_NO_ENTRY:
					
				break;
			
			 case EVENT_KEY1_RELEASED:
					
				state = STATE_IDLE;
				break;					
			}
			
			break;
			
			
		case STATE_TX2:	     // if KEY2 was pressed then start down counting
			
			uart_TX2_task();
			switch(event)
			{
			case EVENT_NO_ENTRY:
			
				break;
			
			case EVENT_KEY2_RELEASED:
		
				state = STATE_IDLE;
				break;
					
			}
			
			break;
	}
	
}


void uart_TX1_task(void)
{
	
	if(!f_timer_500ms) return;  		 // Checking if 30 ms counting is done
	f_timer_500ms =0; 
	
	TXD1 = tx1_buffer[p_tx1++];
	
	if(p_tx1>5){
	p_tx1=0;
	}
	
}

void uart_TX2_task(void)
{
	
	if(!f_timer_500ms) return;  		 // Checking if 30 ms counting is done
	f_timer_500ms =0; 
		
	TXD3 = tx2_buffer[p_tx2++];
	
	if(p_tx2>8){
	p_tx2=0;
	}
	
}

void setEvent(unsigned char event)
{
	bufferEvent[e_wp] = event;
	e_wp++;
	if (e_wp>63)
	{
		e_wp=0;
	}
}


unsigned char getEvent(void)
{
	unsigned char event = bufferEvent[e_rp];
	e_rp++;
	if (e_rp>63)
	{
		e_rp=0;
	}
 	 return event;
}

void seven_segment_driver(char input)
{
	if(input&0b0000001){
		pin_g=0;
	}else{
		pin_g=1;
	}
	
	if(input&0b0000010){
		pin_f=0;
	}else{
		pin_f=1;
	}
	
	if(input&0b0000100){
		pin_e=0;
	}else{
		pin_e=1;
	}
	
	if(input&0b0001000){
		pin_d=0;
	}else{
		pin_d=1;
	}
		
	if(input&0b0010000){
		pin_c=0;
	}else{
		pin_c=1;
	}	
	
	if(input&0b0100000){
		pin_b=0;
	}else{
		pin_b=1;
	}
	
	if(input&0b1000000){
		pin_a=0;
	}else{
		pin_a=1;
	}
}


 
/* End user code. Do not edit comment generated here */
