/**
 * @file
 *
 * @brief HID generic Identifers.
 *
 * This file contains the usb parameters that uniquely identify the
 * application through descriptor tables.
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

#ifndef _USB_DESCRIPTORS_H_
#define _USB_DESCRIPTORS_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "modules/usb/device_chap9/usb_standard_descriptors.h"
#include "conf_usb.h"

//_____ M A C R O S ____________________________________________________________

#define Usb_get_dev_desc_pointer()        (&(usb_dev_desc.bLength))
#define Usb_get_dev_desc_length()         (sizeof (usb_dev_desc))
#define Usb_get_conf_desc_pointer()       (&(usb_conf_desc.cfg.bLength))
#define Usb_get_conf_desc_length()        (sizeof (usb_conf_desc))

//_____ U S B    D E F I N E _______________________________________________

// USB Device descriptor
#define USB_SPECIFICATION     0x0200
#define DEVICE_CLASS          0      // each configuration has its own class
#define DEVICE_SUB_CLASS      0      // each configuration has its own sub-class
#define DEVICE_PROTOCOL       0      // each configuration has its own protocol
#define EP_CONTROL_LENGTH     64
#define VENDOR_ID             0x12BA // (Sony Computer Entertainment America)
#define PRODUCT_ID            0x0200 // "Harmonix Guitar for PlayStation\2563"
#define RELEASE_NUMBER        0x0200
#define MAN_INDEX             0x01
#define PROD_INDEX            0x02
#if (USB_DEVICE_SN_USE==true)
#define SN_INDEX              0x03
#else
#define SN_INDEX              0x00  // No serial number field
#endif
#define NB_CONFIGURATION      1

// HID generic CONFIGURATION
#define NB_INTERFACE       1           // Number of interfaces
#define CONF_NB            1
#define CONF_INDEX         0
#define CONF_ATTRIBUTES    USB_CONFIG_BUSPOWERED
#define MAX_POWER          50          // 100 mA
// USB Interface descriptor
#define INTERFACE_NB        0          // Interface's number
#define ALTERNATE           0
#define NB_ENDPOINT         2
#define INTERFACE_CLASS     HID_CLASS // HID Class
#define INTERFACE_SUB_CLASS NO_SUBCLASS
#define INTERFACE_PROTOCOL  NO_PROTOCOL
#define INTERFACE_INDEX     0

// USB Endpoint 1 descriptor FS
#define ENDPOINT_NB_1       (EP_HID_IN | USB_ENDPOINT_IN)
#define EP_ATTRIBUTES_1     0x03          // BULK = 0x02, INTERUPT = 0x03
#define EP_SIZE_1           64
#define EP_INTERVAL_1       10 //interrupt pooling from host
// USB Endpoint 2 descriptor FS
#define ENDPOINT_NB_2       (EP_HID_OUT)
#define EP_ATTRIBUTES_2     0x03          // BULK = 0x02, INTERUPT = 0x03
#define EP_SIZE_2           64
#define EP_INTERVAL_2       1 //interrupt pooling from host
#define SIZE_OF_REPORT        156

#define DEVICE_STATUS         USB_DEVICE_STATUS_BUS_POWERED

#define LANG_ID               0x00

// "Licensed by Sony Computer Entertainment America"
#define USB_MN_LENGTH         47
#define USB_MANUFACTURER_NAME \
{ Usb_unicode('L') \
, Usb_unicode('i') \
, Usb_unicode('c') \
, Usb_unicode('e') \
, Usb_unicode('n') \
, Usb_unicode('s') \
, Usb_unicode('e') \
, Usb_unicode('d') \
, Usb_unicode(' ') \
, Usb_unicode('b') \
, Usb_unicode('y') \
, Usb_unicode(' ') \
, Usb_unicode('S') \
, Usb_unicode('o') \
, Usb_unicode('n') \
, Usb_unicode('y') \
, Usb_unicode(' ') \
, Usb_unicode('C') \
, Usb_unicode('o') \
, Usb_unicode('m') \
, Usb_unicode('p') \
, Usb_unicode('u') \
, Usb_unicode('t') \
, Usb_unicode('e') \
, Usb_unicode('r') \
, Usb_unicode(' ') \
, Usb_unicode('E') \
, Usb_unicode('n') \
, Usb_unicode('t') \
, Usb_unicode('e') \
, Usb_unicode('r') \
, Usb_unicode('t') \
, Usb_unicode('a') \
, Usb_unicode('i') \
, Usb_unicode('n') \
, Usb_unicode('m') \
, Usb_unicode('e') \
, Usb_unicode('n') \
, Usb_unicode('t') \
, Usb_unicode(' ') \
, Usb_unicode('A') \
, Usb_unicode('m') \
, Usb_unicode('e') \
, Usb_unicode('r') \
, Usb_unicode('i') \
, Usb_unicode('c') \
, Usb_unicode('a') \
}

//"Harmonix Guitar for PlayStation\2563"
#define USB_PN_LENGTH         36
#define USB_PRODUCT_NAME \
{ Usb_unicode('H') \
 ,Usb_unicode('a') \
 ,Usb_unicode('r') \
 ,Usb_unicode('m') \
 ,Usb_unicode('o') \
 ,Usb_unicode('n') \
 ,Usb_unicode('i') \
 ,Usb_unicode('x') \
 ,Usb_unicode(' ') \
 ,Usb_unicode('G') \
 ,Usb_unicode('u') \
 ,Usb_unicode('i') \
 ,Usb_unicode('t') \
 ,Usb_unicode('a') \
 ,Usb_unicode('r') \
 ,Usb_unicode(' ') \
 ,Usb_unicode('f') \
 ,Usb_unicode('o') \
 ,Usb_unicode('r') \
 ,Usb_unicode(' ') \
 ,Usb_unicode('P') \
 ,Usb_unicode('l') \
 ,Usb_unicode('a') \
 ,Usb_unicode('y') \
 ,Usb_unicode('s') \
 ,Usb_unicode('t') \
 ,Usb_unicode('a') \
 ,Usb_unicode('t') \
 ,Usb_unicode('i') \
 ,Usb_unicode('o') \
 ,Usb_unicode('n') \
 ,Usb_unicode('\\') \
 ,Usb_unicode('2') \
 ,Usb_unicode('5') \
 ,Usb_unicode('6') \
 ,Usb_unicode('3') \
}

#define USB_SN_LENGTH         0x05
#define USB_SERIAL_NUMBER \
{ Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
 ,Usb_unicode('0') \
}

#define LANGUAGE_ID           0x0409

//_____ U S B   M A N U F A C T U R E R   D E S C R I P T O R _______________


/// manufacturer string
typedef struct
{
    /// size of this descriptor in bytes
    uint8_t bLength;
    /// STRING descriptor type
    uint8_t bDescriptorType;
    /// unicode characters
    uint16_t wString[USB_MN_LENGTH];
} S_usb_manufacturer_string_descriptor;

//_____ U S B   P R O D U C T   D E S C R I P T O R _________________________


/// product string
typedef struct
{
    /// size of this descriptor in bytes
    uint8_t bLength;
    /// STRING descriptor type
    uint8_t bDescriptorType;
    /// unicode characters
    uint16_t wString[USB_PN_LENGTH];
} S_usb_product_string_descriptor;

//_____ U S B   S E R I A L   N U M B E R   D E S C R I P T O R _____________


#if (USB_DEVICE_SN_USE==true)
/// device serial number
typedef struct
{
    /// size of this descriptor in bytes
    uint8_t bLength;
    /// STRING descriptor type
    uint8_t bDescriptorType;
#if (USE_DEVICE_SN_UNIQUE==true)

#else
/// unicode characters
uint16_t wString[USB_SN_LENGTH];
#endif
} S_usb_serial_number;
#endif

/*_____ U S B   H I D   D E S C R I P T O R __________________________________*/

/// USB configuration descriptor
typedef struct
{
    S_usb_configuration_descriptor cfg;
    S_usb_interface_descriptor ifc;
    S_usb_hid_descriptor hid;
    S_usb_endpoint_descriptor ep1;
    S_usb_endpoint_descriptor ep2;
} S_usb_user_configuration_descriptor;

#endif

