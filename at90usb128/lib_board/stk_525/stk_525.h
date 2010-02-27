/**
 * @file
 *
 * @brief This file contains the low level macros and definition for stk525 board
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

#ifndef STK_525_H
#define STK_525_H

//_____ I N C L U D E S ____________________________________________________
#include "config.h"

#if (TARGET_BOARD==STK525)

//_____ M A C R O S ________________________________________________________

/**
 * @defgroup STK525_module STK525
 * This module contains low level hardware abstraction layer for STK525 board
 * @image html stk525.gif
 * @{
 */

/// @defgroup STK_525_leds Leds Management
/// Macros to manage Leds on STK525
/// @{
#define  LED_PORT             PORTD
#define  LED_DDR              DDRD
#define  LED_PIN              PIND
#define  LED0_BIT             PIND4
#define  LED1_BIT             PIND5
#define  LED2_BIT             PIND6
#define  LED3_BIT             PIND7

#define  Leds_init()          (LED_DDR  |=  (1<<LED0_BIT) | (1<<LED1_BIT) | (1<<LED2_BIT) | (1<<LED3_BIT))
#define  Leds_on()            (LED_PORT |=  (1<<LED0_BIT) | (1<<LED1_BIT) | (1<<LED2_BIT) | (1<<LED3_BIT))
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
#define  Is_led0_on()         (LED_PIN  &   (1<<LED0_BIT) ? TRUE : FALSE)
#define  Is_led1_on()         (LED_PIN  &   (1<<LED1_BIT) ? TRUE : FALSE)
#define  Is_led2_on()         (LED_PIN  &   (1<<LED2_BIT) ? TRUE : FALSE)
#define  Is_led3_on()         (LED_PIN  &   (1<<LED3_BIT) ? TRUE : FALSE)
/// @}

/// @defgroup STK_525_joy Joystick Management
/// Macros to manage Joystick on STK525
/// @{
#define  Joy_init()           (DDRB &= ~((1<<PINB7)|(1<<PINB6)|(1<<PINB5)), PORTB |= ((1<<PINB7)|(1<<PINB6)|(1<<PINB5)), DDRE &= ~((1<<PINE5)|(1<<PINE4)), PORTE |= ((1<<PINE5)|(1<<PINE4)))

#define  Is_btn_left()        Is_hwb()
#define  Is_btn_middle()      ((PINB & (1<<PINB5)) ?  FALSE : TRUE)
#define  Is_btn_right()       FALSE

#define  Is_joy_left()        ((PINB & (1<<PINB6)) ?  FALSE : TRUE)
#define  Is_joy_up()          ((PINB & (1<<PINB7)) ?  FALSE : TRUE)
#define  Is_joy_down()        ((PINE & (1<<PINE5)) ?  FALSE : TRUE)
#define  Is_joy_right()       ((PINE & (1<<PINE4)) ?  FALSE : TRUE)

#define  Is_btn_not_left()    Is_not_hwb()
#define  Is_btn_not_middle()  ((PINB & (1<<PINB5)) ?  TRUE : FALSE)
#define  Is_btn_not_right()   TRUE

#define  Is_joy_not_up()      ((PINB & (1<<PINB7)) ?  TRUE : FALSE)
#define  Is_joy_not_left()    ((PINB & (1<<PINB6)) ?  TRUE : FALSE)
#define  Is_joy_not_down()    ((PINE & (1<<PINE5)) ?  TRUE : FALSE)
#define  Is_joy_not_right()   ((PINE & (1<<PINE4)) ?  TRUE : FALSE)

* Enable interrupts for switches (PINB5 to PINB7)
* - Set up interrupts for switches
* - clear flag
* - enable interrupt
#define  Switches_enable_it() {  \
      PCMSK0 |= (1<<PCINT5)|(1<<PCINT6)|(1<<PCINT7);\
      PCIFR |= (1<<PCIF0);       \
      PCICR |= (1<<PCIE0);}

* Disable interrupts for switches (PINB5 to PINB7)
* - disable interrupt
* - clear flag
* - Clear mask
#define  Switches_disable_it() { \
      PCICR  &= ~(1<<PCIE0);     \
      PCIFR  |= (1<<PCIF0);      \
      PCMSK0 &= ~((1<<PCINT5)|(1<<PCINT6)|(1<<PCINT7));}
/// @}


/// @defgroup USB_key_HWB HWB button management
/// HWB button is connected to PE2 and can also
/// be used as generic push button
/// @{
#define  Hwb_button_init()    (DDRE  &= ~(1<<PINE2), PORTE |= (1<<PINE2))
#define  Is_hwb()             ((PINE &   (1<<PINE2)) ?  FALSE : TRUE)
#define  Is_not_hwb()         ((PINE &   (1<<PINE2)) ?  TRUE : FALSE)
/// @}


/// @defgroup STK_525_df_STK525 ATMEL Hardware data flash configuration
/// Macros to init the environnement for DF on STK525
/// @{

// One AT45DB321C
#define DF_4_MB
#define DF_NB_MEM          1

// PINB0 : SPI Slave Select pin, this pin must be disable (disable input mode) because it is used by joystick
//         Note: the joystick can work fine in Output mode, because the pull-up resistor is activated and the level pin can be read.
// PINB1 : the SCK signal direction is OUTPUT
// PINB2 : the SI signal direction is OUTPUT
// PINB3 : the SO signal direction is INPUT
// PINB4 : the CS signal direction is OUTPUT
#define  Df_init_spi()     (DDRB  &= ~((1<<PINB3)), \
                            DDRB  |=  ((1<<PINB4)|(1<<PINB2)|(1<<PINB1)|(1<<PINB0)), \
                            PORTB |=  ((1<<PINB4)|(1<<PINB3)|(1<<PINB2)|(1<<PINB1)|(1<<PINB0)) )
#define  Df_select_0()     (PORTB &= ~(1<<PINB4))
#define  Df_desel_all()    (PORTB |=  (1<<PINB4))
/// @}

/// @}


///STK 525 ADC Potentiometer Channel Definition
#define ADC_POT_CH   0x01
#define ADC_MIC_CH   0x02
#define ADC_TEMP_CH  0x00

#ifdef USE_ADC       ///< this define is set in config.h file
/**
 * @brief Get_adc_mic_val.
 *
 * This function performs an ADC conversion from the stk525 MIC channel
 * an returns the 10 bits result in an U16 value.
 *
 * @warning USE_ADC should be defined in config.h
 *
 * @param none
 *
 * @return U16 microphone sample value.
 */
U16 Get_adc_mic_val(void);

/**
 * @brief Get_adc_temp_val.
 *
 * This function performs an ADC conversion from the stk525 TEMP channel
 * an returns the 10 bits result in an U16 value.
 *
 * @warning USE_ADC should be defined in config.h
 *
 * @param none
 *
 * @return U16 analog sensor temperature value.
 */
U16 Get_adc_temp_val(void);

/**
 * @brief Get_adc_pot_val.
 *
 * This function performs an ADC conversion from the stk525 POT channel
 * an returns the 10 bits result in an U16 value.
 *
 * @warning USE_ADC should be defined in config.h
 *
 * @param none
 *
 * @return U16 analog potentiometer value.
 */
U16 Get_adc_pot_val(void);

/**
 * @brief Read_temperature.
 *
 * This function performs an ADC conversion from the stk525 POT channel
 * an returns the 10 bits result of the temperature (in °C) in an S16 value.
 *
 * @warning USE_ADC should be defined in config.h
 *
 * @param none
 *
 * @return S16 temperature value in °C.
 */
S16 Read_temperature(void);

#endif   // USE_ADC
#endif   // TARGET_BOARD==STK525
#endif   // STK_525_H
