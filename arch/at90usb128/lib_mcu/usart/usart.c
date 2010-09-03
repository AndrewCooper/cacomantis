// AVR306: Using the AVR UART in C
// Routines for interrupt controlled USART
// Last modified: 02-06-21
// Modified by: AR

/* Includes */
#include <stdbool.h>
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

bool USART0_CTS( void )
{
    unsigned char tmphead;

    /* Calculate buffer index */
    tmphead = ( USART_TxHead + 1 ) & USART_TX_BUFFER_MASK;

    /* Return 0 (false) if the transmit buffer is full */
    return ( tmphead == USART_TxTail );
}

void USART0_Init( unsigned int baudrate )
{
    unsigned char x;

    /* Set the baud rate */
    UBRR1H = ( unsigned char )( baudrate >> 8 );
    UBRR1L = ( unsigned char )baudrate;

    /* Enable UART receiver and transmitter */
    UCSR1B = ( ( 1 << RXCIE1 ) | ( 1 << RXEN1 ) | ( 1 << TXEN1 ) );

    /* Set frame format: 8 data 2stop */
    //For devices with Extended IO
    UCSR1C = ( 1 << USBS1 ) | ( 1 << UCSZ11 ) | ( 1 << UCSZ10 );

    //For devices without Extended IO
    //UCSR0C = (1<<URSEL)|(1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);

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

    /* Store new index */
    USART_RxHead = tmphead;

    if( tmphead == USART_RxTail )
    {
        /* ERROR! Receive buffer overflow */
    }

    /* Store received data in buffer */
    USART_RxBuf[tmphead] = rxdata;
}

ISR(USART1_TX_vect)
{
    unsigned char tmptail;

    /* Check if all data is transmitted */
    if( USART_TxHead != USART_TxTail )
    {
        /* Calculate buffer index */
        tmptail = ( USART_TxTail + 1 ) & USART_TX_BUFFER_MASK;

        /* Store new index */
        USART_TxTail = tmptail;

        /* Start transmition */
        UDR1 = USART_TxBuf[tmptail];
    }
    else
    {
        /* Disable UDRE interrupt */
        UCSR1B &= ~( 1 << UDRIE1 );
    }
}

unsigned char USART0_Receive( void )
{
    unsigned char tmptail;

    /* Wait for incomming data */
    while( USART_RxHead == USART_RxTail )
        ;

    /* Calculate buffer index */
    tmptail = ( USART_RxTail + 1 ) & USART_RX_BUFFER_MASK;

    /* Store new index */
    USART_RxTail = tmptail;

    /* Return data */
    return USART_RxBuf[tmptail];
}

bool USART0_RTR( void )
{
    /* Return 0 (false) if the receive buffer is empty */
    return ( USART_RxHead != USART_RxTail );
}

void USART0_Transmit( unsigned char txdata )
{
    unsigned char tmphead;

    /* Calculate buffer index */
    tmphead = ( USART_TxHead + 1 ) & USART_TX_BUFFER_MASK;

    /* Wait for free space in buffer */
    while( tmphead == USART_TxTail )
        ;

    /* Store data in buffer */
    USART_TxBuf[tmphead] = txdata;

    /* Store new index */
    USART_TxHead = tmphead;

    /* Enable UDRE interrupt */
    UCSR1B |= ( 1 << UDRIE1 );
}
