/**
 * @file
 *
 * @brief This file contains the low level macros and definition for USB KEY board
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

#ifndef USB_KEY_H
#define USB_KEY_H

//_____ I N C L U D E S ________________________________________________________

#include "config.h"
#if (TARGET_BOARD==USBKEY)

//_____ M A C R O S ____________________________________________________________


/**
 * @defgroup USB_KEY_module USBKEY
 * This module contains low level hardware abstraction layer for AT90USBkey board
 * @image html avrusbkey.gif
 * @{
 */

/**
 * @defgroup USB_key_leds Leds Management
 * Macros to manage Leds on USB KEY
 * The led 0 correspond at led D2 RED
 * The led 1 correspond at led D2 GREEN
 * The led 2 correspond at led D5 GREEN
 * The led 3 correspond at led D5 RED
 * @{
 */
#define  LED_PORT             PORTD
#define  LED_DDR              DDRD
#define  LED_PIN              PIND
#define  LED0_BIT             PIND4
#define  LED1_BIT             PIND5
#define  LED2_BIT             PIND6
#define  LED3_BIT             PIND7

#define  Leds_init()          (LED_DDR |= (1<<LED0_BIT) | (1<<LED1_BIT) | (1<<LED2_BIT) | (1<<LED3_BIT))
#define  Leds_on()            (LED_PORT |= (1<<LED0_BIT) | (1<<LED1_BIT) | (1<<LED2_BIT) | (1<<LED3_BIT))
#define  Leds_off()           (LED_PORT &= ~((1<<LED0_BIT) | (1<<LED1_BIT) | (1<<LED2_BIT) | (1<<LED3_BIT)))
#define  Leds_set_val(c)      (Leds_off(),LED_PORT |= (c<<4)&((1<<LED0_BIT) | (1<<LED1_BIT) | (1<<LED2_BIT) | (1<<LED3_BIT)))
#define  Leds_get_val()       (LED_PORT>>4)

#define  Led0_on()            (LED_PORT |=  (1<<LED0_BIT))
#define  Led1_on()            (LED_PORT |=  (1<<LED1_BIT))
#define  Led2_on()            (LED_PORT |=  (1<<LED2_BIT))
#define  Led3_on()            (LED_PORT |=  (1<<LED3_BIT))
#define  Led0_off()           (LED_PORT &= ~(1<<LED0_BIT))
#define  Led1_off()           (LED_PORT &= ~(1<<LED1_BIT))
#define  Led2_off()           (LED_PORT &= ~(1<<LED2_BIT))
#define  Led3_off()           (LED_PORT &= ~(1<<LED3_BIT))
#define  Led0_toggle()        (LED_PIN  |=  (1<<LED0_BIT))
#define  Led1_toggle()        (LED_PIN  |=  (1<<LED1_BIT))
#define  Led2_toggle()        (LED_PIN  |=  (1<<LED2_BIT))
#define  Led3_toggle()        (LED_PIN  |=  (1<<LED3_BIT))
#define  Is_led0_on()         (LED_PIN  &   (1<<LED0_BIT) ? true : false)
#define  Is_led1_on()         (LED_PIN  &   (1<<LED1_BIT) ? true : false)
#define  Is_led2_on()         (LED_PIN  &   (1<<LED2_BIT) ? true : false)
#define  Is_led3_on()         (LED_PIN  &   (1<<LED3_BIT) ? true : false)
/// @}

/**
 * @defgroup USB_key_joy Joystick Management
 * Macros to manage Joystick on USB KEY
 * @{
 */
#define  Joy_init()           (DDRB &= ~((1<<PINB7)|(1<<PINB6)|(1<<PINB5)), PORTB |= ((1<<PINB7)|(1<<PINB6)|(1<<PINB5)), DDRE &= ~((1<<PINE5)|(1<<PINE4)), PORTE |= ((1<<PINE5)|(1<<PINE4)))

#define  Is_btn_left()        Is_hwb()
#define  Is_btn_middle()      ((PINB & (1<<PINB5)) ?  false : true)
#define  Is_btn_right()       false

#define  Is_joy_up()          ((PINB & (1<<PINB7)) ?  false : true)
#define  Is_joy_left()        ((PINB & (1<<PINB6)) ?  false : true)
#define  Is_joy_down()        ((PINE & (1<<PINE5)) ?  false : true)
#define  Is_joy_right()       ((PINE & (1<<PINE4)) ?  false : true)

#define  Is_btn_not_left()    Is_not_hwb()
#define  Is_btn_not_middle()  ((PINB & (1<<PINB5)) ?  true : false)
#define  Is_btn_not_right()   true

#define  Is_joy_not_up()      ((PINB & (1<<PINB7)) ?  true  : false)
#define  Is_joy_not_left()    ((PINB & (1<<PINB6)) ?  true : false)
#define  Is_joy_not_down()    ((PINE & (1<<PINE5)) ?  true : false)
#define  Is_joy_not_right()   ((PINE & (1<<PINE4)) ?  true : false)

/**
 * Enable interrupts for switches (PINB5 to PINB7)
 * - Set up interrupts for switches
 * - clear flag
 * - enable interrupt
 */
#define  Switches_enable_it() {  \
      PCMSK0 |= (1<<PCINT5)|(1<<PCINT6)|(1<<PCINT7);\
      PCIFR |= (1<<PCIF0);       \
      PCICR |= (1<<PCIE0);}

/**
 * Disable interrupts for switches (PINB5 to PINB7)
 * - disable interrupt
 * - clear flag
 * - Clear mask
 */
#define  Switches_disable_it() { \
      PCICR  &= ~(1<<PCIE0);     \
      PCIFR  |= (1<<PCIF0);      \
      PCMSK0 &= ~((1<<PCINT5)|(1<<PCINT6)|(1<<PCINT7));}
/// @}


/**
 * @defgroup USB_key_HWB HWB button management
 * HWB button is connected to PE2 and can also
 * be used as generic push button
 * @{
 */
#define Hwb_button_init()      (DDRE  &= ~(1<<PINE2), PORTE |= (1<<PINE2))
#define Is_hwb()               ((PINE &   (1<<PINE2)) ?  false : true)
#define Is_not_hwb()           ((PINE &   (1<<PINE2)) ?  true : false)
/// @}


/**
 * @defgroup USB_key_df USB KEY Hardware data flash configuration
 * Macros to init the environnement for DF on USB KEY
 * @{
 */

/// One AT45DB642D
#define DF_8_MB
#define DF_NB_MEM          2

// PINB0 : SPI Slave Select pin, this pin must be disable (disable input mode) because it is used by joystick
//         Note: the joystick can work fine in Output mode, because the pull-up resistor is activated and the level pin can be read.
// PINB1 : the SCK signal direction is OUTPUT
// PINB2 : the SI signal direction is OUTPUT
// PINB3 : the SO signal direction is INPUT
// PINE0 : the CS0 signal direction is OUTPUT
// PINE1 : the CS1 signal direction is OUTPUT
#define  Df_init_spi()     (DDRB  &= ~((1<<PINB3)), \
                            DDRB  |=  ((1<<PINB2)|(1<<PINB1)|(1<<PINB0)), \
                            PORTB |=  ((1<<PINB3)|(1<<PINB2)|(1<<PINB1)|(1<<PINB0)),\
                            DDRE  |=  ((1<<PINE1)|(1<<PINE0)), \
                            PORTE |=  ((1<<PINE1)|(1<<PINE0)) )
#define  Df_select_0()     (PORTE &= ~(1<<PINE0))
#define  Df_select_1()     (PORTE &= ~(1<<PINE1))
#define  Df_desel_all()    (PORTE |=  ((1<<PINE1)|(1<<PINE0)))

/// @}

///@}


/// USB KEY ADC Channel Definition
#define ADC_TEMP_CH  0x00

#ifdef USE_ADC       ///< this define is set in config.h file
/**
 * @brief This function performs an ADC conversion from the USB KEY TEMP channel
 * an returns the 10 bits result in an uint16_t value.
 *
 * @warning USE_ADC should be defined in config.h
 *
 * @param none
 *
 * @return uint16_t analog sensor temperature value.
 */
uint16_t Get_adc_temp_val(void);

/**
 * @brief This function performs an ADC conversion from the USB KEY TEMP channel
 * an returns the 10 bits result of the temperature (in °C) in an int16_t value.
 *
 * @warning USE_ADC should be defined in config.h
 *
 * @param none
 *
 * @return int16_t temperature value in °C.
 */
int16_t Read_temperature(void);

#endif   // USE_ADC
#endif   // TARGET_BOARD==USBKEY
#endif   // USB_KEY_H
