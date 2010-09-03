/**
 * @file
 *
 * @brief This file contains the low level functions for the ADC
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

//_____  I N C L U D E S ___________________________________________________

#include "config.h"
#include "stk_525.h"

#if (TARGET_BOARD==STK525)

/// this define is set on config.h file
#ifdef USE_ADC
#include "lib_mcu/adc/adc_drv.h"

//_____ M A C R O S ________________________________________________________


//_____ P R I V A T E    D E C L A R A T I O N _____________________________


//_____ D E F I N I T I O N ________________________________________________

/**
 * The following table give the correspondance between the ADC code and the temperature
 * Each elements of the table corresponds to an ADC code value.
 * The index in the table give the corresponding temperature (in°C) with
 * the following formula : Tempeature=index-20.
 * table[O] corresponds to -20°C temperature code
 * The following table gives the ADC code for VCC=3.3V and Aref=AVcc
 */
code uint16_t temperature_code[]=
	{0x3B4,0x3B0,0x3AB,0x3A6,0x3A0,0x39A,0x394,0x38E,0x388,0x381,0x37A,0x373,
	0x36B,0x363,0x35B,0x353,0x34A,0x341,0x338,0x32F,0x325,0x31B,0x311,0x307,
	0x2FC,0x2F1,0x2E6,0x2DB,0x2D0,0x2C4,0x2B8,0x2AC,0x2A0,0x294,0x288,0x27C,
	0x26F,0x263,0x256,0x24A,0x23D,0x231,0x225,0x218,0x20C,0x200,0x1F3,0x1E7,
	0x1DB,0x1CF,0x1C4,0x1B8,0x1AC,0x1A1,0x196,0x18B,0x180,0x176,0x16B,0x161,
	0x157,0x14D,0x144,0x13A,0x131,0x128,0x11F,0x117,0x10F,0x106,0xFE,0xF7,
	0xEF,0xE8,0xE1,0xDA,0xD3,0xCD,0xC7,0xC0,0xBA,0xB5,0xAF,0xAA,0xA4,0x9F,
	0x9A,0x96,0x91,0x8C,0x88,0x84,0x80,0x7C,0x78,0x74,0x71,0x6D,0x6A,0x67,
	0x64,0x61,0x5E,0x5B,0x58,0x55,0x53,0x50,0x4E,0x4C,0x49,0x47,0x45,0x43,
	0x41,0x3F,0x3D,0x3C,0x3A,0x38};

//_____ D E C L A R A T I O N __________________________________________________

#ifdef __ICCAVR__
#pragma diag_suppress=Pa082
#endif

uint16_t Get_adc_mic_val(void)
	{
	Start_conv_channel(ADC_MIC_CH);
	while (!Is_adc_conv_finished());
	return Adc_get_10_bits_result();
	}

uint16_t Get_adc_pot_val(void)
	{
	Start_conv_channel(ADC_POT_CH);
	while (!Is_adc_conv_finished());
	return Adc_get_10_bits_result();
	}

uint16_t Get_adc_temp_val(void)
	{
	Start_conv_channel(ADC_TEMP_CH);
	while (!Is_adc_conv_finished());
	return Adc_get_10_bits_result();
	}

int16_t Read_temperature(void)
	{
#ifndef __GNUC__
	uint16_t adc_code;
	int8_t index=0;
	adc_code=Get_adc_temp_val();
	if(adc_code>temperature_code[0])
		{
		return (int16_t)(-20);
		}
	else
		{
		while(temperature_code[index++]>adc_code);
		return (int16_t)(index-1-20);
		}
#else
	uint16_t adc_code;
	int8_t index=0;
	adc_code=Get_adc_temp_val();
	if(adc_code>pgm_read_word_near(&temperature_code))
		{
		return (int16_t)(-20);
		}
	else
		{
		while(pgm_read_word_near(&temperature_code[index++])>adc_code);
		return (int16_t)(index-1-20);
		}

#endif
	}

#endif   // USE_ADC
#endif   // (TARGET_BOARD==STK525)
