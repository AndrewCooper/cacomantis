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

//_____ I N C L U D E S ____________________________________________________

//_____ M A C R O S ________________________________________________________

//_____ D E C L A R A T I O N ______________________________________________

void USART0_Init( unsigned int baudrate );

unsigned char USART0_Receive( void );

void USART0_Transmit( unsigned char data );
