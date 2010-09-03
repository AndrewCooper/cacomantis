/**
 * @file
 *
 * @brief This file manages the uart task for communicating with a PC
 * @author               Andrew Cooper
 *
 *
 *
 */

/* Copyright (c) 2010 Andrew Cooper. All rights reserved.
 */

//_____  I N C L U D E S _______________________________________________________

#include <stdbool.h>
#include <avr/interrupt.h>
#include "config.h"
#include "lib_mcu/usart/usart.h"

//_____ M A C R O S ____________________________________________________________


//_____ V A R I A B L E S ______________________________________________________


static uint8_t rx_buffer[USART_RX_BUFFER_SIZE];
static int rx_head;
static bool rx_overflow;
static int rx_tail;

static uint8_t tx_buffer[USART_TX_BUFFER_SIZE];
static int tx_head;
static int tx_tail;

//_____ D E F I N I T I O N S __________________________________________________


/**
 * @brief Interpret any received commands, send any pending responses
 */
void uart_task( void )
{

}

/**
 * @brief Initialize the target USART module
 */
void uart_task_init( void )
{
    /** Initialize buffer variables                                          **/
    rx_head = 0;
    rx_overflow = false;
    rx_tail = 0;
    tx_head = 0;
    tx_tail = 0;

}

