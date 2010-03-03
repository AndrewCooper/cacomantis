/**
 * @file
 *
 * @brief This file contains the usb HID definition constant parameters
 *
 * Firmware Specification Version 1.11
 *
 * - Compiler:           IAR EWAVR and GNU GCC for AVR
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

#ifndef _USB_COMMUN_HID_H_
#define _USB_COMMUN_HID_H_

/**
 * @name Global Class, SubClass & Protocol constants for HID
 * 	@{
 */
#define HID_CLASS                            0x03
#define HID_SUB_CLASS_BOOT                   0x01    ///< Is used to signal the BIOS BOOT support (0=no no sub class,1=boot interface SubClass)
#define HID_PROTOCOL_KEYBOARD                0x01    ///< Protocol keyboard standard
#define HID_PROTOCOL_MOUSE                   0x02    ///< Protocol mouse standard
/**
 * @name Specific setup requests from HID driver
 * (USB_SETUP_SET_CLASS_INTER or USB_SETUP_GET_CLASS_INTER)
 * 		@{
 */
#define SETUP_HID_GET_REPORT                 0x01
#define SETUP_HID_GET_IDLE                   0x02
#define SETUP_HID_GET_PROTOCOL               0x03
#define SETUP_HID_SET_REPORT                 0x09
#define SETUP_HID_SET_IDLE                   0x0A
#define SETUP_HID_SET_PROTOCOL               0x0B
///		@}

/**
 * @name HID Report type (used by SETUP_HID_GET_REPORT & SETUP_HID_SET_REPORT)
 * 			@{
 */
#define REPORT_TYPE_INPUT                    0x01
#define REPORT_TYPE_OUTPUT                   0x02
#define REPORT_TYPE_FEATURE                  0x03
///			@}

/**
 * @name HID Report Item Size Constants
 * 			@{
 */
#define REPORT_ITEM_SIZE0 0x0
#define REPORT_ITEM_SIZE1 0x1
#define REPORT_ITEM_SIZE2 0x2
#define REPORT_ITEM_SIZE4 0x3
///			@}

#define REPORT_ITEM_SHORT0( bType ) bType | REPORT_ITEM_SIZE0

#define REPORT_ITEM_SHORT1( bType, data1 ) \
	bType | REPORT_ITEM_SIZE1, \
		0xff & ( data1 )

#define REPORT_ITEM_SHORT2( bType, data2 ) \
	bType | REPORT_ITEM_SIZE2, \
		0xff & ( data2 ), \
		0xff & ( ( data2 ) >> 8)

#define REPORT_ITEM_SHORT4( bType, data4 ) \
	bType | REPORT_ITEM_SIZE4, \
		0xff & ( data4 ), \
		0xff & ( ( data4 ) >> 8) \
		0xff & ( ( data4 ) >> 16) \
		0xff & ( ( data4 ) >> 24)

#define REPORT_LONG( )

/**
 * @name HID Report Global Items
 * 			@{
 */
#define GLOBAL_USAGE_PAGE					0x04
#define GLOBAL_LOGICAL_MIN					0x14
#define GLOBAL_LOGICAL_MAX					0x24
#define GLOBAL_PHYSICAL_MIN					0x34
#define GLOBAL_PHYSICAL_MAX					0x44
#define GLOBAL_UNIT_EXP						0x54
#define GLOBAL_UNIT							0x64
#define GLOBAL_REPORT_SIZE					0x74
#define GLOBAL_REPORT_ID					0x84
#define GLOBAL_REPORT_COUNT					0x94
#define GLOBAL_PUSH							0xA4
#define GLOBAL_POP							0xB4
///			@}

/**
 * @name HID Report Main Items
 * 			@{
 */
#define	MAIN_INPUT							0x80
#define MAIN_OUTPUT							0x90
#define MAIN_COLLECTION						0xA0
#define MAIN_FEATURE						0xB0
#define MAIN_ENDCOLLECTION					0xC0
///			@}

/**
 * @name HID Report Local Items
 * 			@{
 */
#define LOCAL_USAGE							0x08
#define LOCAL_USAGE_MIN						0x18
#define LOCAL_USAGE_MAX						0x28
#define LOCAL_DESIGNATOR_IDX				0x38
#define LOCAL_DESIGNATOR_MIN				0x48
#define LOCAL_DESIGNATOR_MAX				0x58
#define LOCAL_STRING_IDX					0x78
#define LOCAL_STRING_MIN					0x88
#define LOCAL_STRING_MAX					0x98
#define LOCAL_DELIMITER						0xA8
///			@}

/**
 * @name HID Report Usage Page Tags
 * 			@{
 */
#define USAGE_PAGE_UNDEFINED				0x00
#define USAGE_PAGE_GENERIC_DESKTOP			0x01
#define USAGE_PAGE_SIMULATION				0x02
#define USAGE_PAGE_VR						0x03
#define USAGE_PAGE_SPORT					0x04
#define USAGE_PAGE_GAME						0x05
#define USAGE_PAGE_GENERIC_DEVICE			0x06
#define USAGE_PAGE_KEYBOARD					0x07
#define USAGE_PAGE_LEDS						0x08
#define USAGE_PAGE_BUTTON					0x09
#define USAGE_PAGE_ORDINAL					0x0A
#define USAGE_PAGE_TELEPHONY				0x0B
#define USAGE_PAGE_CONSUMER					0x0C
#define USAGE_PAGE_DIGITIZER				0x0D
//		RESERVED							0x0E
#define USAGE_PAGE_PID_PAGE					0x0F
#define USAGE_PAGE_UNICODE					0x10
//		RESERVED							0x11
//		RESERVED							0x12
//		RESERVED							0x13
#define USAGE_PAGE_ALPHANUMERIC_DISPLAY		0x14
//		RESERVED							0x15
//		...									...
//		RESERVED							0x3F
#define USAGE_PAGE_MEDICAL_INSTRUMENTS		0x40
//		RESERVED							0x41
//		...									...
//		RESERVED							0x7F
#define USAGE_PAGE_MONITOR_PAGE0			0x80
#define USAGE_PAGE_MONITOR_PAGE1			0x81
#define USAGE_PAGE_MONITOR_PAGE2			0x82
#define USAGE_PAGE_MONITOR_PAGE3			0x83
#define USAGE_PAGE_POWER_PAGE0				0x84
#define USAGE_PAGE_POWER_PAGE1				0x85
#define USAGE_PAGE_POWER_PAGE2				0x06
#define USAGE_PAGE_POWER_PAGE3				0x07
//		RESERVED							0x88
//		...									...
//		RESERVED							0x8B
#define USAGE_PAGE_BARCODE_SCANNER			0x8C
#define USAGE_PAGE_SCALE					0x8D
#define USAGE_PAGE_MAGNETIC_STRIPE			0x8E
#define USAGE_PAGE_POINT_OF_SALE			0x8F
#define USAGE_PAGE_CAMERA_CONTROL			0x90
#define USAGE_PAGE_ARCADE					0x91
//		RESERVED							0x92
//		...									...
//		RESERVED							0xFEFF
//		VENDOR-DEFINED						0xFF00
//		...									...
//		VENDOR-DEFINED						0xFFFF
///			@}

/**
 * @name HID Report Usage - Generic Desktop
 * 			@{
 */
#define GENERIC_DESKTOP_UNDEFINED			0x00
#define GENERIC_DESKTOP_POINTER				0x01
#define GENERIC_DESKTOP_MOUSE				0x02
//		RESERVED							0x03
#define GENERIC_DESKTOP_JOYSTICK			0x04
#define GENERIC_DESKTOP_GAMEPAD				0x05
#define GENERIC_DESKTOP_KEYBOARD			0x06
#define GENERIC_DESKTOP_KEYPAD				0x07
#define GENERIC_DESKTOP_MULTIAXIS			0x08
#define GENERIC_DESKTOP_TABLETPC			0x09
//		RESERVED							0x0A
//		...									...
//		RESERVED							0x2F
#define GENERIC_DESKTOP_X					0x30
#define GENERIC_DESKTOP_Y					0x31
#define GENERIC_DESKTOP_Z					0x32
#define GENERIC_DESKTOP_RX					0x33
#define GENERIC_DESKTOP_RY					0x34
#define GENERIC_DESKTOP_RZ					0x35
#define GENERIC_DESKTOP_SLIDER				0x36
#define GENERIC_DESKTOP_DIAL				0x37
#define GENERIC_DESKTOP_WHEEL				0x38
#define GENERIC_DESKTOP_HATSWITCH			0x39
#define GENERIC_DESKTOP_COUNTED_BUFFER		0x3A
#define GENERIC_DESKTOP_BYTE_COUNT			0x3B
#define GENERIC_DESKTOP_MOTION_WAKEUP		0x3C
#define GENERIC_DESKTOP_START				0x3D
#define GENERIC_DESKTOP_SELECT				0x3E
//		RESERVED							0x3F
#define GENERIC_DESKTOP_VX					0x40
#define GENERIC_DESKTOP_VY					0x41
#define GENERIC_DESKTOP_VZ					0x42
#define GENERIC_DESKTOP_VBRX				0x43
#define GENERIC_DESKTOP_VBRY				0x44
#define GENERIC_DESKTOP_VBRZ				0x45
#define GENERIC_DESKTOP_VNO								0x46
#define GENERIC_DESKTOP_FEATURE_NOTIFICATION			0x47
#define GENERIC_DESKTOP_RESOLUTION_MULTIPLIER			0x48
//		RESERVED										0x49
//		...												...
//		RESERVED										0x7F
#define GENERIC_DESKTOP_SYSTEM_CONTROL					0x80
#define GENERIC_DESKTOP_SYSTEM_POWERDOWN				0x81
#define GENERIC_DESKTOP_SYSTEM_SLEEP					0x82
#define GENERIC_DESKTOP_SYSTEM_WAKEUP					0x83
#define GENERIC_DESKTOP_SYSTEM_CONTEXT_MENU				0x84
#define GENERIC_DESKTOP_SYSTEM_MAIN_MENU				0x85
#define GENERIC_DESKTOP_SYSTEM_APP_MENU					0x86
#define GENERIC_DESKTOP_SYSTEM_MENU_HELP				0x87
#define GENERIC_DESKTOP_SYSTEM_MENU_EXIT				0x88
#define GENERIC_DESKTOP_SYSTEM_MENU_SELECT				0x89
#define GENERIC_DESKTOP_SYSTEM_MENU_RIGHT				0x8A
#define GENERIC_DESKTOP_SYSTEM_MENU_LEFT				0x8B
#define GENERIC_DESKTOP_SYSTEM_MENU_UP					0x8C
#define GENERIC_DESKTOP_SYSTEM_MENU_DOWN				0x8D
#define GENERIC_DESKTOP_SYSTEM_COLD_RESTART				0x8E
#define GENERIC_DESKTOP_SYSTEM_WARM_RESTART				0x8F
#define GENERIC_DESKTOP_DPAD_UP							0x90
#define GENERIC_DESKTOP_DPAD_DOWN						0x91
#define GENERIC_DESKTOP_DPAD_RIGHT						0x92
#define GENERIC_DESKTOP_DPAD_LEFT						0x93
//		RESERVED										0x94
//		...												...
//		RESERVED										0x9F
#define GENERIC_DESKTOP_SYSTEM_DOCK						0xA0
#define GENERIC_DESKTOP_SYSTEM_UNDOCK					0xA1
#define GENERIC_DESKTOP_SYSTEM_SETUP					0xA2
#define GENERIC_DESKTOP_SYSTEM_BREAK					0xA3
#define GENERIC_DESKTOP_SYSTEM_DEBUGGER_BREAK			0xA4
#define GENERIC_DESKTOP_APPLICATION_BREAK				0xA5
#define GENERIC_DESKTOP_APPLICATION_DEBUGGER_BREAK		0xA6
#define GENERIC_DESKTOP_SYSTEM_SPEAKER_MUTE				0xA7
#define GENERIC_DESKTOP_SYSTEM_HIBERNATE				0xA8
//		RESERVED										0xA9
//		...												...
//		RESERVED										0xAF
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_INVERT			0xB0
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_INTERNAL			0xB1
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_EXTERNAL			0xB2
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_BOTH				0xB3
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_DUAL				0xB4
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_TOGGLE			0xB5
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_SWAP				0xB6
#define GENERIC_DESKTOP_SYSTEM_DISPLAY_LCD_AUTOSCALE	0xB7
//		RESERVED							0xB8
//		...									...
//		RESERVED							0xFFFF

/**
 * @name HID Report Input, Output, and Feature Items
 * 			@{
 */
#define INPUT_DATA							0<<0
#define INPUT_CONSTANT						1<<0
#define INPUT_ARRAY							0<<1
#define INPUT_VARIABLE						1<<1
#define INPUT_ABSOLUTE						0<<2
#define INPUT_RELATIVE						1<<2
#define INPUT_NO_WRAP						0<<3
#define INPUT_WRAP							1<<3
#define INPUT_LINEAR						0<<4
#define INPUT_NONLINEAR						1<<4
#define INPUT_PREFERRED_STATE				0<<5
#define INPUT_NO_PREFERRED_STATE			1<<5
#define INPUT_NO_NULL_POSITION				0<<6
#define INPUT_NULL_STATE					1<<6
#define INPUT_RESERVED						0<<7
#define INPUT_BITFIELD						0<<8
#define INPUT_BUFFERED						1<<8

#define OUTPUT_DATA							0<<0
#define OUTPUT_CONSTANT						1<<0
#define OUTPUT_ARRAY						0<<1
#define OUTPUT_VARIABLE						1<<1
#define OUTPUT_ABSOLUTE						0<<2
#define OUTPUT_RELATIVE						1<<2
#define OUTPUT_NO_WRAP						0<<3
#define OUTPUT_WRAP							1<<3
#define OUTPUT_LINEAR						0<<4
#define OUTPUT_NONLINEAR					1<<4
#define OUTPUT_PREFERRED_STATE				0<<5
#define OUTPUT_NO_PREFERRED_STATE			1<<5
#define OUTPUT_NO_NULL_POSITION				0<<6
#define OUTPUT_NULL_STATE					1<<6
#define OUTPUT_NONVOLATILE					0<<7
#define OUTPUT_VOLATILE						1<<7
#define OUTPUT_BITFIELD						0<<8
#define OUTPUT_BUFFERED						1<<8

#define FEATURE_DATA						0<<0
#define FEATURE_CONSTANT					1<<0
#define FEATURE_ARRAY						0<<1
#define FEATURE_VARIABLE					1<<1
#define FEATURE_ABSOLUTE					0<<2
#define FEATURE_RELATIVE					1<<2
#define FEATURE_NO_WRAP						0<<3
#define FEATURE_WRAP						1<<3
#define FEATURE_LINEAR						0<<4
#define FEATURE_NONLINEAR					1<<4
#define FEATURE_PREFERRED_STATE				0<<5
#define FEATURE_NO_PREFERRED_STATE			1<<5
#define FEATURE_NO_NULL_POSITION			0<<6
#define FEATURE_NULL_STATE					1<<6
#define FEATURE_NONVOLATILE					0<<7
#define FEATURE_VOLATILE					1<<7
#define FEATURE_BITFIELD					0<<8
#define FEATURE_BUFFERED					1<<8
///			@}

/**
 * @name HID Report Input, Output, and Feature Items
 * 			@{
 */
#define COLLECTION_PHYSICAL					0x00
#define COLLECTION_APPLICATION				0x01
#define COLLECTION_LOGICAL					0x02
#define COLLECTION_REPORT					0x03
#define COLLECTION_NAMED_ARRAY				0x04
#define COLLECTION_USAGE_SWITCH				0x05
#define COLLECTION_USAGE_MODIFIER			0x06
///			@}

/**
 * @name Constants for descriptor S_usb_hid_descriptor
 * 		@{
 */

/**
 * @name HID Descriptor types
 * 			@{
 */
#define DESCRIPTOR_HID                       0x21
#define DESCRIPTOR_REPORT                    0x22
#define DESCRIPTOR_PHYSICAL                  0x23
///			@}

/**
 * Constant value for bcdHIDVer
 *
 * Numeric expression identifying the HID Class Specification release (here V1.11)
 */
#define HID_BCD                              0x0111

/**
 * @brief Minimum value for bNumDescriptors
 *
 * Numeric expression specifying the number of class descriptors
 * (always at least one i.e. Report descriptor.)
 */
#define HID_CLASS_DESC_NB_DEFAULT            0x01

/**
 * @name Values of bCountryCode
 * 			@{
 */
#define HID_NO_COUNTRY_CODE                  0       // Not Supported
#define HID_COUNTRY_ARABIC                   1       // Arabic
#define HID_COUNTRY_BELGIAN                  2       // Belgian
#define HID_COUNTRY_CANADIAN_BILINGUAL       3       // Canadian-Bilingual
#define HID_COUNTRY_CANADIAN_FRENCH          4       // Canadian-French
#define HID_COUNTRY_CZECH_REPUBLIC           5       // Czech Republic
#define HID_COUNTRY_DANISH                   6       // Danish
#define HID_COUNTRY_FINNISH                  7       // Finnish
#define HID_COUNTRY_FRENCH                   8       // French
#define HID_COUNTRY_GERMAN                   9       // German
#define HID_COUNTRY_GREEK                    10      // Greek
#define HID_COUNTRY_HEBREW                   11      // Hebrew
#define HID_COUNTRY_HUNGARY                  12      // Hungary
#define HID_COUNTRY_INTERNATIONAL_ISO        13      // International (ISO)
#define HID_COUNTRY_ITALIAN                  14      // Italian
#define HID_COUNTRY_JAPAN_KATAKANA           15      // Japan (Katakana)
#define HID_COUNTRY_KOREAN                   16      // Korean
#define HID_COUNTRY_LATIN_AMERICAN           17      // Latin American
#define HID_COUNTRY_NETHERLANDS_DUTCH        18      // Netherlands/Dutch
#define HID_COUNTRY_NORWEGIAN                19      // Norwegian
#define HID_COUNTRY_PERSIAN_FARSI            20      // Persian (Farsi)
#define HID_COUNTRY_POLAND                   21      // Poland
#define HID_COUNTRY_PORTUGUESE               22      // Portuguese
#define HID_COUNTRY_RUSSIA                   23      // Russia
#define HID_COUNTRY_SLOVAKIA                 24      // Slovakia
#define HID_COUNTRY_SPANISH                  25      // Spanish
#define HID_COUNTRY_SWEDISH                  26      // Swedish
#define HID_COUNTRY_SWISS_FRENCH             27      // Swiss/French
#define HID_COUNTRY_SWISS_GERMAN             28      // Swiss/German
#define HID_COUNTRY_SWITZERLAND              29      // Switzerland
#define HID_COUNTRY_TAIWAN                   30      // Taiwan
#define HID_COUNTRY_TURKISH_Q                31      // Turkish-Q
#define HID_COUNTRY_UK                       32      // UK
#define HID_COUNTRY_US                       33      // US
#define HID_COUNTRY_YUGOSLAVIA               34      // Yugoslavia
#define HID_COUNTRY_TURKISH_F                35      // Turkish-F
///			@}
///		@}
///	@}


/**
 * @name HID KEYS values
 * 	@{
 */
#define HID_A                4
#define HID_B                5
#define HID_C                6
#define HID_D                7
#define HID_E                8
#define HID_F                9
#define HID_G                10
#define HID_H                11
#define HID_I                12
#define HID_J                13
#define HID_K                14
#define HID_L                15
#define HID_M                16
#define HID_N                17
#define HID_O                18
#define HID_P                19
#define HID_Q                20
#define HID_R                21
#define HID_S                22
#define HID_T                23
#define HID_U                24
#define HID_V                25
#define HID_W                26
#define HID_X                27
#define HID_Y                28
#define HID_Z                29
#define HID_1                30
#define HID_2                31
#define HID_3                32
#define HID_4                33
#define HID_5                34
#define HID_6                35
#define HID_7                36
#define HID_8                37
#define HID_9                38
#define HID_0                39
#define HID_ENTER            40
#define HID_ESCAPE           41
#define HID_BACKSPACE        42
#define HID_TAB              43
#define HID_SPACEBAR         44
#define HID_UNDERSCORE       45
#define HID_PLUS             46
/*
 #define HID_[ {              47
 #define HID_] }              48
 */
#define HID_BACKSLASH        49
/*
 #define HID_# ~              50
 #define HID_; :              51
 #define HID_� "              52
 */
#define HID_TILDE            53
#define HID_COMMA            54
#define HID_DOT              55
#define HID_SLASH            56
#define HID_CAPS LOCK        57
#define HID_F1               58
#define HID_F2               59
#define HID_F3               60
#define HID_F4               61
#define HID_F5               62
#define HID_F6               63
#define HID_F7               64
#define HID_F8               65
#define HID_F9               66
#define HID_F10              67
#define HID_F11              68
#define HID_F12              69
#define HID_PRINTSCREEN      70
#define HID_SCROLL LOCK      71
#define HID_PAUSE            72
#define HID_INSERT           73
#define HID_HOME             74
#define HID_PAGEUP           75
#define HID_DELETE           76
#define HID_END              77
#define HID_PAGEDOWN         78
#define HID_RIGHT            79
#define HID_LEFT             80
#define HID_DOWN             81
#define HID_UP               82
#define HID_KEYPAD_NUM_LOCK  83
#define HID_KEYPAD_DIVIDE    84
#define HID_KEYPAD_AT        85
#define HID_KEYPAD_MULTIPLY  85
#define HID_KEYPAD_MINUS     86
#define HID_KEYPAD_PLUS      87
#define HID_KEYPAD_ENTER     88
#define HID_KEYPAD_1         89
#define HID_KEYPAD_2         90
#define HID_KEYPAD_3         91
#define HID_KEYPAD_4         92
#define HID_KEYPAD_5         93
#define HID_KEYPAD_6         94
#define HID_KEYPAD_7         95
#define HID_KEYPAD_8         96
#define HID_KEYPAD_9         97
#define HID_KEYPAD_0         98

/**
 * @name HID modifier values
 * 		@{
 */
#define HID_MODIFIER_NONE          0x00
#define HID_MODIFIER_LEFT_CTRL     0x01
#define HID_MODIFIER_LEFT_SHIFT    0x02
#define HID_MODIFIER_LEFT_ALT      0x04
#define HID_MODIFIER_LEFT_GUI      0x08
#define HID_MODIFIER_RIGHT_CTRL    0x10
#define HID_MODIFIER_RIGHT_SHIFT   0x20
#define HID_MODIFIER_RIGHT_ALT     0x40
#define HID_MODIFIER_RIGHT_GUI     0x80
///		@}

///	@}

/// USB HID Descriptor
typedef struct
	{
		U8 bLength; ///< Size of this descriptor in bytes
		U8 bDescriptorType; ///< HID descriptor type
		U16 bscHID; ///< Binay Coded Decimal Spec. release
		U8 bCountryCode; ///< Hardware target country
		U8 bNumDescriptors; ///< Number of HID class descriptors to follow
		U8 bRDescriptorType; ///< Report descriptor type
		U16 wDescriptorLength; ///< Total length of Report descriptor
	} S_usb_hid_descriptor;

#endif   // _USB_COMMUN_HID_H_
