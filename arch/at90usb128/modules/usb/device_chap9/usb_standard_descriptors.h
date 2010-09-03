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

//_____ I N C L U D E S ________________________________________________________

/// USB Request
typedef struct
    {
	uint8_t bmRequestType; ///< Characteristics of the request
	uint8_t bRequest; ///< Specific request
	uint16_t wValue; ///< field that varies according to request
	uint16_t wIndex; ///< field that varies according to request
	uint16_t wLength; ///< Number of bytes to transfer if Data
    } S_UsbRequest;

/// USB Device Descriptor
typedef struct
    {
	uint8_t bLength; ///< Size of this descriptor in bytes
	uint8_t bDescriptorType; ///< DEVICE descriptor type
	uint16_t bscUSB; ///< Binay Coded Decimal Spec. release
	uint8_t bDeviceClass; ///< Class code assigned by the USB
	uint8_t bDeviceSubClass; ///< Sub-class code assigned by the USB
	uint8_t bDeviceProtocol; ///< Protocol code assigned by the USB
	uint8_t bMaxPacketSize0; ///< Max packet size for EP0
	uint16_t idVendor; ///< Vendor ID. ATMEL = 0x03EB
	uint16_t idProduct; ///< Product ID assigned by the manufacturer
	uint16_t bcdDevice; ///< Device release number
	uint8_t iManufacturer; ///< Index of manu. string descriptor
	uint8_t iProduct; ///< Index of prod. string descriptor
	uint8_t iSerialNumber; ///< Index of S.N.  string descriptor
	uint8_t bNumConfigurations; ///< Number of possible configurations
    } S_usb_device_descriptor;

/// USB Configuration Descriptor
typedef struct
    {
	uint8_t bLength; ///< size of this descriptor in bytes
	uint8_t bDescriptorType; ///< CONFIGURATION descriptor type
	uint16_t wTotalLength; ///< total length of data returned
	uint8_t bNumInterfaces; ///< number of interfaces for this conf.
	uint8_t bConfigurationValue; ///< value for SetConfiguration resquest
	uint8_t iConfiguration; ///< index of string descriptor
	uint8_t bmAttributes; ///< Configuration characteristics
	uint8_t MaxPower; ///< maximum power consumption
    } S_usb_configuration_descriptor;

/// USB Interface Descriptor
typedef struct
    {
	uint8_t bLength; ///< size of this descriptor in bytes
	uint8_t bDescriptorType; ///< INTERFACE descriptor type
	uint8_t bInterfaceNumber; ///< Number of interface
	uint8_t bAlternateSetting; ///< value to select alternate setting
	uint8_t bNumEndpoints; ///< Number of EP except EP 0
	uint8_t bInterfaceClass; ///< Class code assigned by the USB
	uint8_t bInterfaceSubClass; ///< Sub-class code assigned by the USB
	uint8_t bInterfaceProtocol; ///< Protocol code assigned by the USB
	uint8_t iInterface; ///< Index of string descriptor
    } S_usb_interface_descriptor;

/// USB Endpoint Descriptor
typedef struct
    {
	uint8_t bLength; ///< Size of this descriptor in bytes
	uint8_t bDescriptorType; ///< ENDPOINT descriptor type
	uint8_t bEndpointAddress; ///< Address of the endpoint
	uint8_t bmAttributes; ///< Endpoint's attributes
	uint16_t wMaxPacketSize; ///< Maximum packet size for this EP
	uint8_t bInterval; ///< Interval for polling EP in ms
    } S_usb_endpoint_descriptor;

/// USB Language Descriptor
typedef struct
    {
	uint8_t bLength; ///< size of this descriptor in bytes
	uint8_t bDescriptorType; ///< STRING descriptor type
	uint16_t wLangId; ///< language id
    } S_usb_language_id;

/// USB String Descriptor Header
typedef struct
    {
	uint8_t bLength; ///< size of this descriptor in bytes
	uint8_t bDescriptorType; ///< STRING descriptor type
    } S_usb_string_descriptor_header;

#endif /* _USB_STANDARD_DESCRIPTORS_H */
