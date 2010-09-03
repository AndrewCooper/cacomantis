/**
 * @file
 *
 * @brief Specific enumeration process requests header file
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

#ifndef _USB_SPECIFIC_REQUEST_H_
#define _USB_SPECIFIC_REQUEST_H_

//_____ I N C L U D E S ________________________________________________________

#include <avr/pgmspace.h>
#include <stdbool.h>


#include "config.h"

//_____ M A C R O S ____________________________________________________________

extern PROGMEM S_usb_device_descriptor usb_dev_desc;
extern PROGMEM S_usb_user_configuration_descriptor usb_conf_desc;
extern PROGMEM S_usb_manufacturer_string_descriptor
	usb_user_manufacturer_string_descriptor;
extern PROGMEM S_usb_product_string_descriptor usb_user_product_string_descriptor;
#if (USB_DEVICE_SN_USE==true)
extern PROGMEM S_usb_serial_number usb_user_serial_number;
#endif
extern PROGMEM S_usb_language_id usb_user_language_id;

//_____ D E F I N I T I O N ____________________________________________________

bool usb_user_read_request(uint8_t, uint8_t);
void usb_user_endpoint_init(uint8_t);
uint8_t usb_user_interface_get(uint16_t wInterface);
void usb_user_interface_reset(uint16_t wInterface, uint8_t alternate_setting);
bool usb_user_get_descriptor(uint8_t, uint8_t);

/**
 * Usb HID Report Descriptor HID generic
 */
typedef struct
    {
	uint8_t report[SIZE_OF_REPORT];
    } S_usb_hid_report_descriptor;

#endif
