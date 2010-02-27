/**
 * @file
 *
 * @brief  USB parameters.
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
//_____ I N C L U D E S ____________________________________________________
#include "config.h"
#include "conf_usb.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "usb_specific_request.h"
#if ((USB_DEVICE_SN_USE==ENABLE) && (USE_DEVICE_SN_UNIQUE==ENABLE))
#include "lib_mcu/flash/flash_drv.h"
#endif
//_____ M A C R O S ________________________________________________________
//_____ D E F I N I T I O N ________________________________________________
// usb_user_device_descriptor
code S_usb_device_descriptor usb_dev_desc =
	{
	sizeof( usb_dev_desc ),
	DESCRIPTOR_DEVICE,
	Usb_write_word_enum_struc(USB_SPECIFICATION),
	DEVICE_CLASS,
	DEVICE_SUB_CLASS,
	DEVICE_PROTOCOL,
	EP_CONTROL_LENGTH,
	Usb_write_word_enum_struc(VENDOR_ID),
	Usb_write_word_enum_struc(PRODUCT_ID),
	Usb_write_word_enum_struc(RELEASE_NUMBER),
	MAN_INDEX,
	PROD_INDEX,
	SN_INDEX,
	NB_CONFIGURATION
	};
// usb_user_configuration_descriptor FS
code S_usb_user_configuration_descriptor usb_conf_desc =
	{
	.cfg =
		{
		.bLength = sizeof(S_usb_configuration_descriptor),
		.bDescriptorType = DESCRIPTOR_CONFIGURATION,
		.wTotalLength = Usb_write_word_enum_struc(sizeof(S_usb_configuration_descriptor)
			+sizeof(S_usb_interface_descriptor)
			+sizeof(S_usb_hid_descriptor)
			+sizeof(S_usb_endpoint_descriptor)
			+sizeof(S_usb_endpoint_descriptor)),
		.bNumInterfaces = NB_INTERFACE,
		.bConfigurationValue = CONF_NB,
		.iConfiguration = CONF_INDEX,
		.bmAttributes = CONF_ATTRIBUTES,
		.MaxPower = MAX_POWER
		},
	.ifc =
		{
		.bLength = sizeof(S_usb_interface_descriptor),
		.bDescriptorType = DESCRIPTOR_INTERFACE,
		.bInterfaceNumber = INTERFACE_NB,
		.bAlternateSetting = ALTERNATE,
		.bNumEndpoints = NB_ENDPOINT,
		.bInterfaceClass = INTERFACE_CLASS,
		.bInterfaceSubClass = INTERFACE_SUB_CLASS,
		.bInterfaceProtocol = INTERFACE_PROTOCOL,
		.iInterface = INTERFACE_INDEX
		},
	.hid =
		{
		.bLength = sizeof(S_usb_hid_descriptor),
		.bDescriptorType = DESCRIPTOR_HID,
		.bcdHIDVer = HID_BCD,
		.bCountryCode = HID_NO_COUNTRY_CODE,
		.bNumDescriptors = HID_CLASS_DESC_NB_DEFAULT,
		.bRDescriptorType = DESCRIPTOR_REPORT,
		.wDescriptorLength = Usb_write_word_enum_struc(sizeof(S_usb_hid_report_descriptor))
		},
	.ep1 =
		{
		.bLength = sizeof(S_usb_endpoint_descriptor),
		.bDescriptorType = DESCRIPTOR_ENDPOINT,
		.bEndpointAddress = ENDPOINT_NB_1,
		.bmAttributes = EP_ATTRIBUTES_1,
		.wMaxPacketSize = Usb_write_word_enum_struc(EP_SIZE_1),
		.bInterval = EP_INTERVAL_1
		},
	.ep2 =
		{
		.bLength = sizeof(S_usb_endpoint_descriptor),
		.bDescriptorType = DESCRIPTOR_ENDPOINT,
		.bEndpointAddress = ENDPOINT_NB_2,
		.bmAttributes = EP_ATTRIBUTES_2,
		.wMaxPacketSize = Usb_write_word_enum_struc(EP_SIZE_2),
		.bInterval = EP_INTERVAL_2
		}
	};
// usb_user_manufacturer_string_descriptor
code S_usb_manufacturer_string_descriptor usb_user_manufacturer_string_descriptor =
	{
	.bLength = sizeof( usb_user_manufacturer_string_descriptor ),
	.bDescriptorType = DESCRIPTOR_STRING,
	.wString = USB_MANUFACTURER_NAME
	};
// usb_user_product_string_descriptor
code S_usb_product_string_descriptor usb_user_product_string_descriptor =
	{
	.bLength = sizeof( usb_user_product_string_descriptor ),
	.bDescriptorType = DESCRIPTOR_STRING,
	.wString = USB_PRODUCT_NAME
	};
// usb_user_serial_number
#if (USB_DEVICE_SN_USE==ENABLE)
code S_usb_serial_number usb_user_serial_number =
	{
#if (USE_DEVICE_SN_UNIQUE==ENABLE)
	sizeof(usb_user_serial_number)+4*SN_LENGTH,
	DESCRIPTOR_STRING
#else
	sizeof(usb_user_serial_number),
	DESCRIPTOR_STRING,
	USB_SERIAL_NUMBER
#endif
	};
#endif

// usb_user_language_id

code S_usb_language_id usb_user_language_id =
	{
	.bLength = sizeof( usb_user_language_id ),
	.bDescriptorType = DESCRIPTOR_STRING,
	.wLangId = Usb_write_word_enum_struc(LANGUAGE_ID)
	};
code S_usb_hid_report_descriptor usb_hid_report_descriptor =
	{
		{
		0x06,
		0xFF,
		0xFF, // 04|2   , Usage Page (vendordefined?)
		0x09,
		0x01, // 08|1   , Usage      (vendordefined
		0xA1,
		0x01, // A0|1   , Collection (Application)
		// IN report
		0x09,
		0x02, // 08|1   , Usage      (vendordefined)
		0x09,
		0x03, // 08|1   , Usage      (vendordefined)
		0x15,
		0x00, // 14|1   , Logical Minimum(0 for signed byte?)
		0x26,
		0xFF,
		0x00, // 24|1   , Logical Maximum(255 for signed byte?)
		0x75,
		0x08, // 74|1   , Report Size(8) = field size in bits = 1 byte
		0x95,
		LENGTH_OF_REPORT_IN, // 94|1:ReportCount(size) = repeat count of previous item
		0x81,
		0x02, // 80|1: IN report (Data,Variable, Absolute)
		// OUT report
		0x09,
		0x04, // 08|1   , Usage      (vendordefined)
		0x09,
		0x05, // 08|1   , Usage      (vendordefined)
		0x15,
		0x00, // 14|1   , Logical Minimum(0 for signed byte?)
		0x26,
		0xFF,
		0x00, // 24|1   , Logical Maximum(255 for signed byte?)
		0x75,
		0x08, // 74|1   , Report Size(8) = field size in bits = 1 byte
		0x95,
		LENGTH_OF_REPORT_OUT, // 94|1:ReportCount(size) = repeat count of previous item
		0x91,
		0x02, // 90|1: OUT report (Data,Variable, Absolute)
		// Feature report
		0x09,
		0x06, // 08|1   , Usage      (vendordefined)
		0x09,
		0x07, // 08|1   , Usage      (vendordefined)
		0x15,
		0x00, // 14|1   , LogicalMinimum(0 for signed byte)
		0x26,
		0xFF,
		0x00, // 24|1   , Logical Maximum(255 for signed byte)
		0x75,
		0x08, // 74|1   , Report Size(8) =field size in bits = 1 byte
		0x95,
		0x04, // 94|1:ReportCount
		0xB1,
		0x02, // B0|1:   Feature report
		0xC0
		// C0|0    , End Collection
		}
	};

