/*This file is prepared for Doxygen automatic documentation generation.*/
/**
 * @file
 *
 * @brief This file contains the system configuration definition.
 *
 * - Compiler:           IAR EWAVR and GNU GCC for AVR
 * - Supported devices:  AT90USB1287, AT90USB1286, AT90USB647, AT90USB646
 *
 * @author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 */

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

//_____ I N C L U D E S ________________________________________________________

#include <avr/io.h>                    // Use AVR-GCC library

//_____ C O N S T A N T S ______________________________________________________

/**
 * @defgroup global_config Application configuration
 * @{
 */

#include "conf/conf_scheduler.h" ///< Scheduler tasks declaration
// Board defines (do not change these settings)
#define  STK525   1
#define  USBKEY   2

/**
 * Enable or not the ADC usage
 */
#undef USE_ADC

/**
 * To include proper target hardware definitions, select
 * target board (USBKEY or STK525)
 */
#define TARGET_BOARD USBKEY

#if (TARGET_BOARD==USBKEY)
/**
 * @warning for USBKEY_HAS_321_DF, only first prototypes versions have AT45DB321C memories
 * should be undefined for std series
 */
#define USBKEY_HAS_321_DF
#include "lib_board/usb_key/usb_key.h"
#elif (TARGET_BOARD==STK525)
#include "lib_board/stk_525/stk_525.h"
#else
#error TARGET_BOARD must be defined somewhere
#endif

/// CPU core frequency in kHz
#define FOSC 8000

// -------- END Generic Configuration -------------------------------------

// UART Sample configuration, if we have one ... __________________________
#define USART_BAUDRATE        57600

#define uart_putchar putchar
#define r_uart_ptchar int
#define p_uart_ptchar int

#define USART_RX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */

// ADC Sample configuration, if we have one ... ___________________________

/// ADC Prescaler value
#define ADC_PRESCALER 64
/// Right adjust
#define ADC_RIGHT_ADJUST_RESULT 1
/// AVCC As reference voltage (See adc_drv.h)
#define ADC_INTERNAL_VREF  2

//------------------------------------------------------------------------------
// F r e e R T O S    T a s k    C o n f i g u r a t i o n
//------------------------------------------------------------------------------

#define kUART_TASK_PRIORITY             ( 1 )
#define kUSB_TASK_PRIORITY              ( 1 )
#define kHID_TASK_PRIORITY              ( 1 )

/// @}

#endif // _CONFIG_H_
