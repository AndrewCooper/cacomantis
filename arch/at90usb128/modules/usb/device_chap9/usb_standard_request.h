/**
 * @file
 *
 * @brief Process USB device enumeration requests header file.
 *
 * This file contains the USB endpoint 0 management routines corresponding to
 * the standard enumeration process (refer to chapter 9 of the USB
 * specification.
 * This file calls routines of the usb_specific_request.c file for non-standard
 * request management.
 * The enumeration parameters (descriptor tables) are contained in the
 * usb_descriptors.c file.
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

#ifndef _USB_STANDARD_REQUEST_H_
#define _USB_STANDARD_REQUEST_H_

//_____ I N C L U D E S ____________________________________________________

#include "modules/usb/usb_task.h"
#include "usb_descriptors.h"

//_____ M A C R O S ________________________________________________________

//_____ S T A N D A R D    D E F I N I T I O N S ___________________________

/**
 * @defgroup std_request USB device standard requests decoding
 * @{
 */

// Device State
#define ATTACHED                          0
#define POWERED                           1
#define DEFAULT                           2
#define ADDRESSED                         3
#define CONFIGURED                        4
#define SUSPENDED                         5

#define USB_REMOTE_WAKEUP       1
#define OTG_B_HNP_ENABLE        3
#define OTG_A_HNP_SUPPORT       4
#define OTG_A_ALT_HNP_SUPPORT   5

//_____ D E C L A R A T I O N ______________________________________________

/**
 * Returns true when device connected and correctly enumerated with an host.
 * The device high level application should tests this before performing any applicative requests
 */
#define Is_device_enumerated()            ((usb_configuration_nb!=0)   ? true : false)
#define Is_device_not_enumerated()        ((usb_configuration_nb!=0)   ? false : true)

void usb_process_request( void );

void usb_generate_remote_wakeup( void );

extern uint8_t usb_configuration_nb;
extern uint8_t remote_wakeup_feature;

#if (USE_DEVICE_SN_UNIQUE==true)
extern uint8_t f_get_serial_string;
#endif

/// @}

#endif  // _USB_STANDARD_REQUEST_H_
