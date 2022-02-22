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
* Creation Date: 2022-02-22
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
extern unsigned char f_timer_100us;
extern unsigned char f_timer_10ms;
unsigned char f_timer_30ms;
unsigned char i,p_tx1,p_tx2;
unsigned char flag_digit_1;
unsigned char tx[3];
unsigned char test[6]={"HELLO\n"};
unsigned char tx_buffer1[10]={0,1,2,3,4,5,6,7,8,9};
unsigned char tx_buffer2[6]={10,11,12,13,14,15};
unsigned char rx_buffer1[64];
unsigned char rx_buffer2[64];
unsigned char* p_rx_buffer1;
unsigned char* p_rx_buffer2;
unsigned char rx_buffer1_count;
unsigned char rx_buffer2_count;
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

MD_STATUS g_uart3_tx_end = 0U;

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
			0b1111101,	// 'a'
			0b0011111,	// 'b'
			0b0001101,	// 'c'
			0b0111101,	// 'd'
			0b1101111,	// 'e'
			0b1000111,	// 'f'
			0b0000001 	// '-'

};	

void task_timer(void);
void counting_task(void);
void uart_transmit_task(void);
void uart_receive_task(void);
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
    R_UART2_Start();
     R_UART3_Start();
    LED=1;
    digit1=9;
    digit2=0;
    
    
    /*
    pin_a =0;
    pin_b =0;
    pin_c =1;
    pin_d =0;
    pin_e =0;
    pin_f =0;
    pin_g =0;
    */
    //seven_segment_driver(seven_segment_data[15]);
        
    while (1U)
    {
	     task_timer();
	     led_display_task();
	     key_read_task();
	     //uart_transmit_task();
	     //uart_receive_task();
	     main_task();
	   
	   /*
       
	   
	   
	   
	    */			
	
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

void counting_task (void)
{
	if(!f_timer_500ms) return;  		 // Checking if 30 ms counting is done
	f_timer_500ms =0; 
	
	
	digit1++;
	if (digit1>9){
	  digit1=0;
	}
	
	if (digit2==0){
	  digit2=10;
	}
	digit2--;
	
	
}


void uart_transmit_task(void)
{
	
	if(!f_timer_500ms) return;  		 // Checking if 30 ms counting is done
	f_timer_500ms =0; 
	
	if(uart_tx1_flag) {  		 	
	
		R_UART2_Send(&tx_buffer1[p_tx1],1);
	
		p_tx1++;
		if(p_tx1>9)
		{
			p_tx1=0;
		
		}
	}
	
	if(uart_tx2_flag) {  		 	
	
	R_UART3_Send(&tx_buffer2[p_tx2],1);
	
	p_tx2++;
	if(p_tx2>5)
	{
		p_tx2=0;
	}
	}
}

void uart_receive_task(void)
{
	if (rx1_wp!=rx1_rp)
	{
		setEvent(EVENT_UART2_RX);
	}
	if(rx2_wp!=rx2_rp)
	{
		setEvent(EVENT_UART3_RX);
	}

}

void led_display_task(void)
{
   if(!f_timer_100us) return;  		
   f_timer_100us =0;
	
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
	
	//if(!f_timer_500ms) return;       // checking if 10 ms timer interrupt is set (10 ms), if set then do timer task
	
	d_timer_500ms++;
	if(d_timer_500ms==50)     // checking if the count reached LED interval 
	{
		d_timer_500ms=0;
		f_timer_500ms=1;// assign "0" to repeat counting
		//setEvent(EVENT_TIMER_500MS);	// Set flag to inform LED interval timer is done counting	
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
						
						//uart_tx1_flag=0;
						state = STATE_TX;
						break;
						
					case EVENT_KEY2_PRESSED:
						
						//uart_tx2_flag=0;
						state = STATE_TX;
						break;
					/*	
					case EVENT_UART2_RX:
						flag_state_tx=0;
						state = STATE_RX;
						break;
						
					case EVENT_UART3_RX:
						flag_state_tx=0;
						state = STATE_RX;
						break;
						
					default: 
						break;
					*/;
			
			}	
			
			break;
		
		
		case STATE_TX:	     // if KEY2 was pressed then start down counting
			
			
			switch(event)
				{
				
					case EVENT_KEY1_RELEASED:
						
						//uart_tx1_flag=0;
						state = STATE_IDLE;
						break;
						
					case EVENT_KEY2_RELEASED:
						
						//uart_tx2_flag=0;
						state = STATE_IDLE;
						break;
					/*	
					case EVENT_UART2_RX:
						flag_state_tx=1;
						state = STATE_RX;
						break;
						
					case EVENT_UART3_RX:
						flag_state_tx=1;
						state = STATE_RX;
					break;
					*/	
					
				}
			
			
			counting_task();
			break;
		/*	
		case STATE_RX:
			
			if(event==EVENT_UART2_RX){
				 digit1= rx_buffer1[rx1_rp];
				 rx1_rp++;
				 if(rx1_rp>63){
			 		 rx1_rp=0;
			 	 }
			}
			else if(event==EVENT_UART3_RX)
				digit2= rx_buffer2[rx2_rp];
			   	 rx2_rp++;
    				if(rx2_rp>63){
    					rx2_rp=0;
    				}
			if (flag_state_tx)
			{
				state = STATE_TX;
			}else{
				state = STATE_IDLE;
			}
		
			break;
		
		*/
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
