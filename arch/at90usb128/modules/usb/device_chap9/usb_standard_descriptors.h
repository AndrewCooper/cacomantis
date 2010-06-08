/**
 * @file
 *
 * @brief standard USB descriptors
 *
 * This file contains structure definitions for descriptors as outlined in
 * Chapter 9 of the USB 2.0 Specification.
 *
 * @author Andrew Cooper<andrew.cooper@hkcreations.org>
 *
 */

#ifndef _USB_STANDARD_DESCRIPTORS_H_
#define _USB_STANDARD_DESCRIPTORS_H_

//_____ I N C L U D E S ____________________________________________________

/// USB Request
typedef struct
    {
	U8 bmRequestType; ///< Characteristics of the request
	U8 bRequest; ///< Specific request
	U16 wValue; ///< field that varies according to request
	U16 wIndex; ///< field that varies according to request
	U16 wLength; ///< Number of bytes to transfer if Data
    } S_UsbRequest;

/// USB Device Descriptor
typedef struct
    {
	U8 bLength; ///< Size of this descriptor in bytes
	U8 bDescriptorType; ///< DEVICE descriptor type
	U16 bscUSB; ///< Binay Coded Decimal Spec. release
	U8 bDeviceClass; ///< Class code assigned by the USB
	U8 bDeviceSubClass; ///< Sub-class code assigned by the USB
	U8 bDeviceProtocol; ///< Protocol code assigned by the USB
	U8 bMaxPacketSize0; ///< Max packet size for EP0
	U16 idVendor; ///< Vendor ID. ATMEL = 0x03EB
	U16 idProduct; ///< Product ID assigned by the manufacturer
	U16 bcdDevice; ///< Device release number
	U8 iManufacturer; ///< Index of manu. string descriptor
	U8 iProduct; ///< Index of prod. string descriptor
	U8 iSerialNumber; ///< Index of S.N.  string descriptor
	U8 bNumConfigurations; ///< Number of possible configurations
    } S_usb_device_descriptor;

/// USB Configuration Descriptor
typedef struct
    {
	U8 bLength; ///< size of this descriptor in bytes
	U8 bDescriptorType; ///< CONFIGURATION descriptor type
	U16 wTotalLength; ///< total length of data returned
	U8 bNumInterfaces; ///< number of interfaces for this conf.
	U8 bConfigurationValue; ///< value for SetConfiguration resquest
	U8 iConfiguration; ///< index of string descriptor
	U8 bmAttributes; ///< Configuration characteristics
	U8 MaxPower; ///< maximum power consumption
    } S_usb_configuration_descriptor;

/// USB Interface Descriptor
typedef struct
    {
	U8 bLength; ///< size of this descriptor in bytes
	U8 bDescriptorType; ///< INTERFACE descriptor type
	U8 bInterfaceNumber; ///< Number of interface
	U8 bAlternateSetting; ///< value to select alternate setting
	U8 bNumEndpoints; ///< Number of EP except EP 0
	U8 bInterfaceClass; ///< Class code assigned by the USB
	U8 bInterfaceSubClass; ///< Sub-class code assigned by the USB
	U8 bInterfaceProtocol; ///< Protocol code assigned by the USB
	U8 iInterface; ///< Index of string descriptor
    } S_usb_interface_descriptor;

/// USB Endpoint Descriptor
typedef struct
    {
	U8 bLength; ///< Size of this descriptor in bytes
	U8 bDescriptorType; ///< ENDPOINT descriptor type
	U8 bEndpointAddress; ///< Address of the endpoint
	U8 bmAttributes; ///< Endpoint's attributes
	U16 wMaxPacketSize; ///< Maximum packet size for this EP
	U8 bInterval; ///< Interval for polling EP in ms
    } S_usb_endpoint_descriptor;

/// USB Language Descriptor
typedef struct
    {
	U8 bLength; ///< size of this descriptor in bytes
	U8 bDescriptorType; ///< STRING descriptor type
	U16 wLangId; ///< language id
    } S_usb_language_id;

/// USB String Descriptor Header
typedef struct
    {
	U8 bLength; ///< size of this descriptor in bytes
	U8 bDescriptorType; ///< STRING descriptor type
    } S_usb_string_descriptor_header;

#endif /* _USB_STANDARD_DESCRIPTORS_H */
