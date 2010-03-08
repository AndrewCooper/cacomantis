/**
 * @file
 *
 * @brief This file manages the generic HID IN/OUT task.
 *
 * - Compiler:           IAR EWAVR and GNU GCC for AVR
 * - Supported devices:  AT90USB1287, AT90USB1286, AT90USB647, AT90USB646
 *
 * @author               Andrew Cooper
 *
 */

/* Copyright (c) 2010 Andrew Cooper. All rights reserved.
 */

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "at90usb128//lib_mcu/usart/usart.h"

//_____ M A C R O S ________________________________________________________


//_____ V A R I A B L E S __________________________________________________


//_____ P R O C E D U R E S ________________________________________________


/**
 * @brief Initialize the target USART module
 */
void uart_task_init( void )
	{
	USART0_Init( USART_BAUDRATE );
	}


/**
 * @brief Interpret any received commands, send any pending responses
 */
void uart_task( void )
	{

	}

