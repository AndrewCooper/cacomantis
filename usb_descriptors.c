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
//_____ I N C L U D E S ________________________________________________________
#include <avr/pgmspace.h>
#include "config.h"
#include "conf_usb.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "usb_specific_request.h"
#if ((USB_DEVICE_SN_USE==true) && (USE_DEVICE_SN_UNIQUE==true))
#include "lib_mcu/flash/flash_drv.h"
#endif
//_____ M A C R O S ____________________________________________________________
//_____ D E F I N I T I O N ____________________________________________________
// usb_user_device_descriptor
PROGMEM S_usb_device_descriptor usb_dev_desc =
    {
    sizeof( usb_dev_desc ),
    DESCRIPTOR_DEVICE,
    USB_SPECIFICATION,
    DEVICE_CLASS,
    DEVICE_SUB_CLASS,
    DEVICE_PROTOCOL,
    EP_CONTROL_LENGTH,
    VENDOR_ID,
    PRODUCT_ID,
    RELEASE_NUMBER,
    MAN_INDEX,
    PROD_INDEX,
    SN_INDEX,
    NB_CONFIGURATION
    };
// usb_user_configuration_descriptor FS
PROGMEM S_usb_user_configuration_descriptor usb_conf_desc =
    {
    .cfg =
    {
        .bLength = sizeof(S_usb_configuration_descriptor),
        .bDescriptorType = DESCRIPTOR_CONFIGURATION,
        .wTotalLength = sizeof(S_usb_configuration_descriptor)
        + sizeof(S_usb_interface_descriptor)
        + sizeof(S_usb_hid_descriptor)
        + sizeof(S_usb_endpoint_descriptor)
        + sizeof(S_usb_endpoint_descriptor),
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
        .wDescriptorLength = sizeof(S_usb_hid_report_descriptor)
    },
    .ep1 =
    {
        .bLength = sizeof(S_usb_endpoint_descriptor),
        .bDescriptorType = DESCRIPTOR_ENDPOINT,
        .bEndpointAddress = ENDPOINT_NB_1,
        .bmAttributes = EP_ATTRIBUTES_1,
        .wMaxPacketSize = EP_SIZE_1,
        .bInterval = EP_INTERVAL_1
    },
    .ep2 =
    {
        .bLength = sizeof(S_usb_endpoint_descriptor),
        .bDescriptorType = DESCRIPTOR_ENDPOINT,
        .bEndpointAddress = ENDPOINT_NB_2,
        .bmAttributes = EP_ATTRIBUTES_2,
        .wMaxPacketSize = EP_SIZE_2,
        .bInterval = EP_INTERVAL_2
    }
    };
// usb_user_manufacturer_string_descriptor
PROGMEM S_usb_manufacturer_string_descriptor usb_user_manufacturer_string_descriptor =
    {
    .bLength = sizeof( usb_user_manufacturer_string_descriptor ),
    .bDescriptorType = DESCRIPTOR_STRING,
    .wString = USB_MANUFACTURER_NAME
    };
// usb_user_product_string_descriptor
PROGMEM S_usb_product_string_descriptor usb_user_product_string_descriptor =
    {
    .bLength = sizeof( usb_user_product_string_descriptor ),
    .bDescriptorType = DESCRIPTOR_STRING,
    .wString = USB_PRODUCT_NAME
    };
// usb_user_serial_number
#if (USB_DEVICE_SN_USE==true)
PROGMEM S_usb_serial_number usb_user_serial_number =
{
#if (USE_DEVICE_SN_UNIQUE==true)
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

PROGMEM S_usb_language_id usb_user_language_id =
    {
    .bLength = sizeof( usb_user_language_id ),
    .bDescriptorType = DESCRIPTOR_STRING,
    .wLangId = LANGUAGE_ID
    };
PROGMEM S_usb_hid_report_descriptor usb_hid_report_descriptor =
    {
    .report =
    {
        REPORT_ITEM_SHORT1( GLOBAL_USAGE_PAGE, USAGE_PAGE_GENERIC_DESKTOP ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, GENERIC_DESKTOP_GAMEPAD ),
        REPORT_ITEM_SHORT1( MAIN_COLLECTION, COLLECTION_APPLICATION ),
        REPORT_ITEM_SHORT1( GLOBAL_LOGICAL_MIN, 0 ),
        REPORT_ITEM_SHORT1( GLOBAL_LOGICAL_MAX, 1 ),
        REPORT_ITEM_SHORT1( GLOBAL_PHYSICAL_MIN, 0 ),
        REPORT_ITEM_SHORT1( GLOBAL_PHYSICAL_MAX, 1 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_SIZE, 1 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 13 ),
        REPORT_ITEM_SHORT1( GLOBAL_USAGE_PAGE, USAGE_PAGE_BUTTON ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE_MIN, 1 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE_MAX, 13 ),
        REPORT_ITEM_SHORT1( MAIN_INPUT, INPUT_DATA |
            INPUT_VARIABLE |
            INPUT_ABSOLUTE |
            INPUT_NO_WRAP |
            INPUT_LINEAR |
            INPUT_PREFERRED_STATE |
            INPUT_NO_NULL_POSITION |
            INPUT_BITFIELD ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 3 ),
        REPORT_ITEM_SHORT1( MAIN_INPUT, INPUT_CONSTANT |
            INPUT_ARRAY |
            INPUT_ABSOLUTE ),
        REPORT_ITEM_SHORT1( GLOBAL_USAGE_PAGE, USAGE_PAGE_GENERIC_DESKTOP ),
        REPORT_ITEM_SHORT1( GLOBAL_LOGICAL_MAX, 7 ),
        REPORT_ITEM_SHORT2( GLOBAL_PHYSICAL_MAX, 315 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_SIZE, 4 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 1 ),
        REPORT_ITEM_SHORT1( GLOBAL_UNIT, 20 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, GENERIC_DESKTOP_HATSWITCH ),
        REPORT_ITEM_SHORT1( MAIN_INPUT, INPUT_DATA |
            INPUT_VARIABLE |
            INPUT_ABSOLUTE |
            INPUT_NO_WRAP |
            INPUT_LINEAR |
            INPUT_PREFERRED_STATE |
            INPUT_NULL_STATE |
            INPUT_BITFIELD ),
        REPORT_ITEM_SHORT1( GLOBAL_UNIT, 0 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 1 ),
        REPORT_ITEM_SHORT1( MAIN_INPUT, INPUT_CONSTANT |
            INPUT_ARRAY |
            INPUT_ABSOLUTE ),
        REPORT_ITEM_SHORT2( GLOBAL_LOGICAL_MAX, 255 ),
        REPORT_ITEM_SHORT2( GLOBAL_PHYSICAL_MAX, 255 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, GENERIC_DESKTOP_X ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, GENERIC_DESKTOP_Y ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, GENERIC_DESKTOP_Z ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, GENERIC_DESKTOP_RZ ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_SIZE, 8 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 4 ),
        REPORT_ITEM_SHORT1( MAIN_INPUT, INPUT_DATA |
            INPUT_VARIABLE |
            INPUT_ABSOLUTE |
            INPUT_NO_WRAP |
            INPUT_LINEAR |
            INPUT_PREFERRED_STATE |
            INPUT_NO_NULL_POSITION |
            INPUT_BITFIELD ),
        REPORT_ITEM_SHORT2( GLOBAL_USAGE_PAGE, 65280 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x20 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x21 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x22 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x23 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x24 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x25 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x26 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x27 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x28 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x29 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x2a ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x2b ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 12 ),
        REPORT_ITEM_SHORT1( MAIN_INPUT, INPUT_DATA |
            INPUT_VARIABLE |
            INPUT_ABSOLUTE |
            INPUT_NO_WRAP |
            INPUT_LINEAR |
            INPUT_PREFERRED_STATE |
            INPUT_NO_NULL_POSITION |
            INPUT_BITFIELD ),
        REPORT_ITEM_SHORT2( LOCAL_USAGE, 0x2621 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 8 ),
        REPORT_ITEM_SHORT1( MAIN_FEATURE, FEATURE_DATA |
            FEATURE_VARIABLE |
            FEATURE_ABSOLUTE |
            FEATURE_NO_WRAP |
            FEATURE_LINEAR |
            FEATURE_PREFERRED_STATE |
            FEATURE_NO_NULL_POSITION |
            FEATURE_NONVOLATILE |
            FEATURE_BITFIELD ),
        REPORT_ITEM_SHORT2( LOCAL_USAGE, 0x2621 ),
        REPORT_ITEM_SHORT1( MAIN_OUTPUT, OUTPUT_DATA |
            OUTPUT_VARIABLE |
            OUTPUT_ABSOLUTE |
            OUTPUT_NO_WRAP |
            OUTPUT_LINEAR |
            OUTPUT_PREFERRED_STATE |
            OUTPUT_NO_NULL_POSITION |
            OUTPUT_NONVOLATILE |
            OUTPUT_BITFIELD ),
        REPORT_ITEM_SHORT2( GLOBAL_LOGICAL_MAX, 1023 ),
        REPORT_ITEM_SHORT2( GLOBAL_PHYSICAL_MAX, 1023 ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x2c ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x2d ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x2e ),
        REPORT_ITEM_SHORT1( LOCAL_USAGE, 0x2f ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_SIZE, 16 ),
        REPORT_ITEM_SHORT1( GLOBAL_REPORT_COUNT, 4 ),
        REPORT_ITEM_SHORT1( MAIN_INPUT, INPUT_DATA |
            INPUT_VARIABLE |
            INPUT_ABSOLUTE |
            INPUT_NO_WRAP |
            INPUT_LINEAR |
            INPUT_PREFERRED_STATE |
            INPUT_NO_NULL_POSITION |
            INPUT_BITFIELD ),
        REPORT_ITEM_SHORT0( MAIN_ENDCOLLECTION )
    }
    };

