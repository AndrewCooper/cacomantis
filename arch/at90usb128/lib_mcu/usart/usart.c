// AVR306: Using the AVR UART in C
// Routines for interrupt controlled USART
// Last modified: 02-06-21
// Modified by: AR

/* Includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"
#include "usart.h"

/* UART Buffer Defines */
#define USART_RX_BUFFER_MASK ( USART_RX_BUFFER_SIZE - 1 )
#define USART_TX_BUFFER_MASK ( USART_TX_BUFFER_SIZE - 1 )
#if ( USART_RX_BUFFER_SIZE & USART_RX_BUFFER_MASK )
#error RX buffer size is not a power of 2
#endif
#if ( USART_TX_BUFFER_SIZE & USART_TX_BUFFER_MASK )
#error TX buffer size is not a power of 2
#endif

/* Static Variables */
static unsigned char USART_RxBuf[USART_RX_BUFFER_SIZE];
static volatile unsigned char USART_RxHead;
static volatile unsigned char USART_RxTail;
static unsigned char USART_TxBuf[USART_TX_BUFFER_SIZE];
static volatile unsigned char USART_TxHead;
static volatile unsigned char USART_TxTail;

/**
 *  Initialize USART
 */
void USART0_Init( unsigned int baudrate )
{
    unsigned char x;

    /* Set the baud rate */
    UBRR1H = ( unsigned char )( baudrate >> 8 );
    UBRR1L = ( unsigned char )baudrate;

    /* Enable UART receiver and transmitter */
    UCSR1B = ( ( 1 << RXCIE1 ) | ( 1 << RXEN1 ) | ( 1 << TXEN1 ) );

    /* Set frame format: 8 data 2stop */
    UCSR1C = ( 1 << USBS1 ) | ( 1 << UCSZ11 ) | ( 1 << UCSZ10 ); //For devices with Extended IO
    //UCSR0C = (1<<URSEL)|(1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);   //For devices without Extended IO

    /* Flush receive buffer */
    x = 0;

    USART_RxTail = x;
    USART_RxHead = x;
    USART_TxTail = x;
    USART_TxHead = x;
}

/**
 * Interrupt handler called when USART1 receives a byte
 */
ISR(USART1_RX_vect)
{
    unsigned char rxdata;
    unsigned char tmphead;

    /* Read the received data */
    rxdata = UDR1;
    /* Calculate buffer index */
    tmphead = ( USART_RxHead + 1 ) & USART_RX_BUFFER_MASK;
    USART_RxHead = tmphead; /* Store new index */

    if( tmphead == USART_RxTail )
    {
        /* ERROR! Receive buffer overflow */
    }

    USART_RxBuf[tmphead] = rxdata; /* Store received data in buffer */
}

/**
 * Interrupt handler called when USART1 is ready to send
 */
ISR(USART1_TX_vect)
{
    unsigned char tmptail;

    /* Check if all data is transmitted */
    if( USART_TxHead != USART_TxTail )
    {
        /* Calculate buffer index */
        tmptail = ( USART_TxTail + 1 ) & USART_TX_BUFFER_MASK;
        USART_TxTail = tmptail; /* Store new index */

        UDR1 = USART_TxBuf[tmptail]; /* Start transmition */
    }
    else
    {
        UCSR1B &= ~( 1 << UDRIE1 ); /* Disable UDRE interrupt */
    }
}

/**
 * Read a byte from the data buffer. Blocks if no bytes are available.
 * @return next received byte
 */
unsigned char USART0_Receive( void )
{
    unsigned char tmptail;

    while( USART_RxHead == USART_RxTail )
        /* Wait for incomming data */
        ;
    tmptail = ( USART_RxTail + 1 ) & USART_RX_BUFFER_MASK;/* Calculate buffer index */

    USART_RxTail = tmptail; /* Store new index */

    return USART_RxBuf[tmptail]; /* Return data */
}

/**
 * Add a byte to the data buffer to be transmitted. Blocks if no space is available.
 * @param txdata
 */
void USART0_Transmit( unsigned char txdata )
{
    unsigned char tmphead;
    /* Calculate buffer index */
    tmphead = ( USART_TxHead + 1 ) & USART_TX_BUFFER_MASK; /* Wait for free space in buffer */
    while( tmphead == USART_TxTail )
        ;

    USART_TxBuf[tmphead] = txdata; /* Store data in buffer */
    USART_TxHead = tmphead; /* Store new index */

    UCSR1B |= ( 1 << UDRIE1 ); /* Enable UDRE interrupt */
}

/**
 *
 * @return
 */
unsigned char DataInReceiveBuffer( void )
{
    return ( USART_RxHead != USART_RxTail ); /* Return 0 (false) if the receive buffer is empty */
}
