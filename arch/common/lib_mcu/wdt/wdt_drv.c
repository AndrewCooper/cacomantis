/**
 * @file
 *
 * @brief This file contains the Watchdog low level driver definition
 *
 * - Compiler:           IAR EWAVR and GNU GCC for AVR
 * - Supported devices:  AT90USB162, AT90USB82
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

//_____ I N C L U D E S ________________________________________________________
#include <avr/interrupt.h>
#include "config.h"
#include "wdt_drv.h"

//_____ M A C R O S ____________________________________________________________

#define  Wdt_reset_instruction()    wdt_reset()

/**
 * @brief Stop the hardware watchdog timer.
 */
void wdtdrv_disable( void )
    {
    cli();
    Ack_wdt_reset();
    wdt_disable();
    sei();
    }

/**
 * @brief Activate the hardware watchdog timer System Reset Mode only
 *
 * @param timeout (WDTO_x)
 */
void wdtdrv_enable( uint8_t timeout )
    {
    cli();
    Ack_wdt_reset();
    wdt_enable(timeout);
    sei();
    }

/**
 * @brief Activate the hardware watchdog timer Interrupt Mode only
 *
 * @param timeout (WDTO_x)
 */
void wdtdrv_interrupt_enable( uint8_t timeout )
    {
    Ack_wdt_reset();
    __asm__ __volatile__ (
        "in __tmp_reg__,__SREG__" "\n\t"
        "cli" "\n\t"
        "wdr" "\n\t"
        "sts %0,%1" "\n\t"
        "out __SREG__,__tmp_reg__" "\n\t"
        "sts %0,%2"
        : /* no outputs */
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)),
        "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)),
        "r" ((uint8_t) ((timeout & 0x08 ? _WD_PS3_MASK : 0x00) |
                _BV(WDIE) | (timeout & 0x07)) )
        : "r0"
    );
    sei();
    }

/**
 * @brief Activate the hardware watchdog timer Interrupt & System Reset Mode
 *
 * @param timeout (WDTO_x)
 */
void wdtdrv_interrupt_reset_enable( uint8_t timeout )
    {
    cli();
    Ack_wdt_reset();
    __asm__ __volatile__ (
        "in __tmp_reg__,__SREG__" "\n\t"
        "cli" "\n\t"
        "wdr" "\n\t"
        "sts %0,%1" "\n\t"
        "out __SREG__,__tmp_reg__" "\n\t"
        "sts %0,%2"
        : /* no outputs */
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)),
        "r" (_BV(_WD_CHANGE_BIT) | _BV(WDE)),
        "r" ((uint8_t) ((timeout & 0x08 ? _WD_PS3_MASK : 0x00) |
                _BV(WDE) | _BV(WDIE) | (timeout & 0x07)) )
        : "r0"
    );
    sei();
    }
