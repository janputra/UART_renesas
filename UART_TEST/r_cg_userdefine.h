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
* File Name    : r_cg_userdefine.h
* Version      : CodeGenerator for RL78/G13 V2.05.05.01 [25 Nov 2020]
* Device(s)    : R5F100MJ
* Tool-Chain   : CCRL
* Description  : This file includes user definition.
* Creation Date: 2022-02-22
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */
#define KEY1 P12_bit.no4
#define KEY2 P12_bit.no3
#define LED  P10_bit.no0

#define EVENT_NO_ENTRY 0
#define EVENT_KEY1_PRESSED 1
#define EVENT_KEY2_PRESSED 2
#define EVENT_KEY1_RELEASED 3
#define EVENT_KEY2_RELEASED 4
#define EVENT_UART2_RX 5
#define EVENT_UART3_RX 6


#define STATE_IDLE 0
#define STATE_TX 1
#define STATE_RX 2
//#define STATE_IDLE 2
//#define STATE_IDLE 3
//#define STATE_IDLE 4

#define KEY_PRESSED 0b1100     // 
#define KEY_RELEASED 0b0011

#define pin_a  P14_bit.no7
#define pin_b  P11_bit.no0
#define pin_c  P5_bit.no4
#define pin_d  P5_bit.no5
//#define pin_d  P0_bit.no3
#define pin_e  P14_bit.no6
#define pin_f  P1_bit.no0
#define pin_g  P11_bit.no1
#define pin_digit1 P0_bit.no3
#define pin_digit2 P0_bit.no2

/* End user code. Do not edit comment generated here */
#endif
