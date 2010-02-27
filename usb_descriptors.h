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

//_____ I N C L U D E S ____________________________________________________

#include "config.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "conf_usb.h"

//_____ M A C R O S ________________________________________________________

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
#define VENDOR_ID             VID_ATMEL
#define PRODUCT_ID            PID_MegaHIDGeneric
#define RELEASE_NUMBER        0x1000
#define MAN_INDEX             0x01
#define PROD_INDEX            0x02
#if (USB_DEVICE_SN_USE==ENABLE)
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
#define EP_IN_LENGTH        8
#define EP_SIZE_1           EP_IN_LENGTH
#define EP_INTERVAL_1       20 //interrupt pooling from host
// USB Endpoint 1 descriptor FS
#define ENDPOINT_NB_2       (EP_HID_OUT)
#define EP_ATTRIBUTES_2     0x03          // BULK = 0x02, INTERUPT = 0x03
#define EP_OUT_LENGTH       8
#define EP_SIZE_2           EP_OUT_LENGTH
#define EP_INTERVAL_2       20 //interrupt pooling from host
#define SIZE_OF_REPORT        0x35
#define LENGTH_OF_REPORT_IN   0x08
#define LENGTH_OF_REPORT_OUT  0x08

#define DEVICE_STATUS         USB_DEVICE_STATUS_BUS_POWERED

#define LANG_ID               0x00

#define USB_MN_LENGTH         5
#define USB_MANUFACTURER_NAME \
{ Usb_unicode('A') \
, Usb_unicode('T') \
, Usb_unicode('M') \
, Usb_unicode('E') \
, Usb_unicode('L') \
}

#define USB_PN_LENGTH         16
#define USB_PRODUCT_NAME \
{ Usb_unicode('A') \
 ,Usb_unicode('V') \
 ,Usb_unicode('R') \
 ,Usb_unicode(' ') \
 ,Usb_unicode('U') \
 ,Usb_unicode('S') \
 ,Usb_unicode('B') \
 ,Usb_unicode(' ') \
 ,Usb_unicode('H') \
 ,Usb_unicode('I') \
 ,Usb_unicode('D') \
 ,Usb_unicode(' ') \
 ,Usb_unicode('D') \
 ,Usb_unicode('E') \
 ,Usb_unicode('M') \
 ,Usb_unicode('O') \
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

/// Usb Request
typedef struct
	{
		/// Characteristics of the request
		U8 bmRequestType;
		/// Specific request
		U8 bRequest;
		/// field that varies according to request
		U16 wValue;
		/// field that varies according to request
		U16 wIndex;
		/// Number of bytes to transfer if Data
		U16 wLength;
	} S_UsbRequest;

/// Usb Device Descriptor
typedef struct
	{
		/// Size of this descriptor in bytes
		U8 bLength;
		/// DEVICE descriptor type
		U8 bDescriptorType;
		/// Binay Coded Decimal Spec. release
		U16 bscUSB;
		/// Class code assigned by the USB
		U8 bDeviceClass;
		/// Sub-class code assigned by the USB
		U8 bDeviceSubClass;
		/// Protocol code assigned by the USB
		U8 bDeviceProtocol;
		/// Max packet size for EP0
		U8 bMaxPacketSize0;
		/// Vendor ID. ATMEL = 0x03EB
		U16 idVendor;
		/// Product ID assigned by the manufacturer
		U16 idProduct;
		/// Device release number
		U16 bcdDevice;
		/// Index of manu. string descriptor
		U8 iManufacturer;
		/// Index of prod. string descriptor
		U8 iProduct;
		/// Index of S.N.  string descriptor
		U8 iSerialNumber;
		/// Number of possible configurations
		U8 bNumConfigurations;
	} S_usb_device_descriptor;

/// Usb Configuration Descriptor
typedef struct
	{
		/// size of this descriptor in bytes
		U8 bLength;
		/// CONFIGURATION descriptor type
		U8 bDescriptorType;
		/// total length of data returned
		U16 wTotalLength;
		/// number of interfaces for this conf.
		U8 bNumInterfaces;
		/// value for SetConfiguration resquest
		U8 bConfigurationValue;
		/// index of string descriptor
		U8 iConfiguration;
		/// Configuration characteristics
		U8 bmAttributes;
		/// maximum power consumption
		U8 MaxPower;
	} S_usb_configuration_descriptor;

/// Usb Interface Descriptor
typedef struct
	{
		/// size of this descriptor in bytes
		U8 bLength;
		/// INTERFACE descriptor type
		U8 bDescriptorType;
		/// Number of interface
		U8 bInterfaceNumber;
		/// value to select alternate setting
		U8 bAlternateSetting;
		/// Number of EP except EP 0
		U8 bNumEndpoints;
		/// Class code assigned by the USB
		U8 bInterfaceClass;
		/// Sub-class code assigned by the USB
		U8 bInterfaceSubClass;
		/// Protocol code assigned by the USB
		U8 bInterfaceProtocol;
		/// Index of string descriptor
		U8 iInterface;
	} S_usb_interface_descriptor;

/// Usb Endpoint Descriptor
typedef struct
	{
		/// Size of this descriptor in bytes
		U8 bLength;
		/// ENDPOINT descriptor type
		U8 bDescriptorType;
		/// Address of the endpoint
		U8 bEndpointAddress;
		/// Endpoint's attributes
		U8 bmAttributes;
		/// Maximum packet size for this EP
		U16 wMaxPacketSize;
		/// Interval for polling EP in ms
		U8 bInterval;
	} S_usb_endpoint_descriptor;

/// Usb Language Descriptor
typedef struct
	{
		/// size of this descriptor in bytes
		U8 bLength;
		/// STRING descriptor type
		U8 bDescriptorType;
		/// language id
		U16 wLangId;
	} S_usb_language_id;

//_____ U S B   M A N U F A C T U R E R   D E S C R I P T O R _______________


/// manufacturer string
typedef struct
	{
		/// size of this descriptor in bytes
		U8 bLength;
		/// STRING descriptor type
		U8 bDescriptorType;
		/// unicode characters
		U16 wString[USB_MN_LENGTH];
	} S_usb_manufacturer_string_descriptor;

//_____ U S B   P R O D U C T   D E S C R I P T O R _________________________


/// product string
typedef struct
	{
		/// size of this descriptor in bytes
		U8 bLength;
		/// STRING descriptor type
		U8 bDescriptorType;
		/// unicode characters
		U16 wString[USB_PN_LENGTH];
	} S_usb_product_string_descriptor;

//_____ U S B   S E R I A L   N U M B E R   D E S C R I P T O R _____________


#if (USB_DEVICE_SN_USE==ENABLE)
/// device serial number
typedef struct
	{
	/// size of this descriptor in bytes
	U8 bLength;
	/// STRING descriptor type
	U8 bDescriptorType;
#if (USE_DEVICE_SN_UNIQUE==ENABLE)

#else
	/// unicode characters
	U16 wString[USB_SN_LENGTH];
#endif
	}S_usb_serial_number;
#endif

/*_____ U S B   H I D   D E S C R I P T O R __________________________________*/

/// HID descriptor
typedef struct
	{
		/// Size of this descriptor in bytes
		U8 bLength;
		/// HID descriptor type
		U8 bDescriptorType;
		/// Binay Coded Decimal Spec. release
		U16 bcdHIDVer;
		/// Hardware target country
		U8 bCountryCode;
		/// Number of HID class descriptors to follow
		U8 bNumDescriptors;
		/// Report descriptor type
		U8 bRDescriptorType;
		/// Total length of Report descriptor
		U16 wDescriptorLength;
	} S_usb_hid_descriptor;

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

