/**
 * @file
 *
 * @brief API for AT90USB128x USART module
 *
 * @author               Andrew Cooper
 *
 */

/* Copyright (c) 2009 Andrew Cooper. All rights reserved.
 *
 */

//_____ I N C L U D E S ________________________________________________________

#include <stdbool.h>

//_____ M A C R O S ____________________________________________________________

//_____ D E C L A R A T I O N __________________________________________________

/**
 * Initialize USART0 hardware, buffers and interrupt handlers.
 *
 * @param baudrate target bit clock for USART, already in proper format for UBRR
 */
void USART0_Init( unsigned int baudrate );

/**
 * Read a byte from the data buffer. Blocks if no bytes are available.
 * @return next received byte
 */
unsigned char USART0_Receive( void );

/**
 * Add a byte to the data buffer to be transmitted. Blocks if no space is available.
 * @param txdata
 */
void USART0_Transmit( unsigned char txdata );

/**
 * Indicates USART0 is Ready-To-Read i.e. there is data in the receive buffer
 * @return
 */
bool USART0_RTR( void );

/**
 * Indicates USART0 is Clear-To-Send i.e. there is empty room in transmit buffer
 * @return
 */
bool USART0_CTS( void );
