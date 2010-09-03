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

//_____ M A C R O S ____________________________________________________________

//_____ D E C L A R A T I O N __________________________________________________

/**
 * Initialize USART0 hardware, buffers and interrupt handlers.
 *
 * @param baudrate target bit clock for USART, already in proper format for UBRR
 */
void USART0_Init( unsigned int baudrate );

/**
 * Copy any received frames into data.
 *
 * @param data buffer for received frames
 * @param size of data buffer
 * @return number of frames copied
 */
int USART0_Receive( unsigned char * data, int size );

/**
 * Copy frames to transmit queue.
 *
 * @param data buffer for outgoing data
 * @param size of data buffer
 * @return number of frames copied; may be less than size if queue becomes full
 */
int USART0_Transmit( unsigned char const * data, int size );
