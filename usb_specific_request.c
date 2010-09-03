/**
 * @file
 *
 * @brief user call-back functions
 *
 * This file contains the user call-back functions corresponding to the
 * application:
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

#include "config.h"
#include "conf_usb.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "usb_specific_request.h"
#if ((USB_DEVICE_SN_USE==true) && (USE_DEVICE_SN_UNIQUE==true))
#include "lib_mcu/flash/flash_drv.h"
#endif

//_____ D E F I N I T I O N ____________________________________________________

extern PGM_VOID_P pbuffer;
extern uint8_t data_to_transfer;
extern PROGMEM S_usb_hid_report_descriptor usb_hid_report_descriptor;
uint8_t jump_bootloader = 0;

uint8_t g_u8_report_rate = 0;

//_____ D E C L A R A T I O N __________________________________________________

void hid_get_report_descriptor( void );
void usb_hid_set_report_ouput( void );
void usb_hid_set_idle( uint8_t u8_report_id, uint8_t u8_duration );
void usb_hid_get_idle( uint8_t u8_report_id );
void hid_get_hid_descriptor( void );
void usb_hid_set_report_feature( void );

/**
 * @brief Check the specific request and if known then process it
 *
 * @param type      corresponding at bmRequestType (see USB specification)
 * @param request   corresponding at bRequest (see USB specification)
 *
 * @return true,  when the request is processed
 * @return false, if the request is'nt know (STALL handshake is managed by the main standard request function).
 */
bool usb_user_read_request( uint8_t type, uint8_t request )
    {
    uint8_t wValue_msb;
    uint8_t wValue_lsb;

    // Read wValue
    wValue_lsb = Usb_read_byte();
    wValue_msb = Usb_read_byte();

    // Specific request from Class HID
    if( USB_SETUP_GET_STAND_INTERFACE == type )
        {
        switch( request )
            {
        case SETUP_GET_DESCRIPTOR :
            switch( wValue_msb )
                // Descriptor ID
                {
            case DESCRIPTOR_HID :
                hid_get_hid_descriptor();
                return true;
                break;

            case DESCRIPTOR_REPORT :
                hid_get_report_descriptor();
                return true;

            case DESCRIPTOR_PHYSICAL :
                // TODO
                break;
                }
            break;
            }
        }
    if( USB_SETUP_SET_CLASS_INTER == type )
        {
        switch( request )
            {
        case SETUP_HID_SET_REPORT :
            // The MSB wValue field specifies the Report Type
            // The LSB wValue field specifies the Report ID
            switch( wValue_msb )
                {
            case REPORT_TYPE_INPUT :
                // TODO
                break;

            case REPORT_TYPE_OUTPUT :
                usb_hid_set_report_ouput();
                return true;
                break;

            case REPORT_TYPE_FEATURE :
                usb_hid_set_report_feature();
                return true;
                break;
                }
            break;

        case SETUP_HID_SET_IDLE :
            usb_hid_set_idle( wValue_lsb, wValue_msb );
            return true;

        case SETUP_HID_SET_PROTOCOL :
            // TODO
            break;
            }
        }
    if( USB_SETUP_GET_CLASS_INTER == type )
        {
        switch( request )
            {
        case SETUP_HID_GET_REPORT :
            // TODO
            break;
        case SETUP_HID_GET_IDLE :
            usb_hid_get_idle( wValue_lsb );
            return true;
        case SETUP_HID_GET_PROTOCOL :
            // TODO
            break;
            }
        }
    return false; // No supported request
    }

/**
 * @brief Configure the endpoints
 *
 * @param conf_nb configuration number choosed by USB host
 */
void usb_user_endpoint_init( uint8_t conf_nb )
    {
    usb_configure_endpoint( EP_HID_IN,
        TYPE_INTERRUPT,
        DIRECTION_IN,
        SIZE_8,
        ONE_BANK,
        NYET_ENABLED);

    usb_configure_endpoint( EP_HID_OUT,
        TYPE_INTERRUPT,
        DIRECTION_OUT,
        SIZE_8,
        ONE_BANK,
        NYET_ENABLED);
    }

/**
 * @brief Return the interface alternate setting
 *
 * @param wInterface         Interface selected
 *
 * @return alternate setting configurated
 */
uint8_t usb_user_interface_get( uint16_t wInterface )
    {
    return 0; // Only one alternate setting possible for all interface
    }

/**
 * @brief Select (and resets) the interface alternate setting
 *
 * @param wInterface         Interface selected
 * @param alternate_setting  alternate setting selected
 */
void usb_user_interface_reset( uint16_t wInterface, uint8_t alternate_setting )
    {
    // default setting selected = reset data toggle
    if( INTERFACE_NB == wInterface )
        {
        // Interface HID
        Usb_select_endpoint(EP_HID_IN);
        Usb_disable_stall_handshake();
        Usb_reset_endpoint(EP_HID_IN);
        Usb_reset_data_toggle();
        Usb_select_endpoint(EP_HID_OUT);
        Usb_disable_stall_handshake();
        Usb_reset_endpoint(EP_HID_OUT);
        Usb_reset_data_toggle();
        }
    }

/**
 * @brief Fill the global descriptor
 *
 * @param type      corresponding at MSB of wValue (see USB specification)
 * @param string    corresponding at LSB of wValue (see USB specification)
 *
 * @return false, if the global descriptor no filled
 */
bool usb_user_get_descriptor( uint8_t type, uint8_t string )
    {
    switch( type )
        {
    case DESCRIPTOR_STRING :
        switch( string )
            {
        case LANG_ID :
            data_to_transfer = sizeof( usb_user_language_id );
            pbuffer = & ( usb_user_language_id.bLength );
            return true;
            break;

        case MAN_INDEX :
            data_to_transfer = sizeof( usb_user_manufacturer_string_descriptor );
            pbuffer = & ( usb_user_manufacturer_string_descriptor.bLength );
            return true;
            break;

        case PROD_INDEX :
            data_to_transfer = sizeof( usb_user_product_string_descriptor );
            pbuffer = & ( usb_user_product_string_descriptor.bLength );
            return true;
            break;

#if (USB_DEVICE_SN_USE==true)
            case SN_INDEX:
            data_to_transfer = sizeof (usb_user_serial_number);
            pbuffer = &(usb_user_serial_number.bLength);
#if (USE_DEVICE_SN_UNIQUE==true)
            f_get_serial_string=true;
            data_to_transfer += (SN_LENGTH*4);
#endif
            return true;
            break;
#endif
            }
        break;
        }
    return false;
    }

/**
 * @brief Manage HID get report request.
 */
void hid_get_report_descriptor( void )
    {
    uint16_t wLength;
    uint8_t nb_byte;
    bool zlp = false;
    uint16_t wInterface;

    BYTEn( wInterface, 0 ) = Usb_read_byte();
    BYTEn( wInterface, 1 ) = Usb_read_byte();

    data_to_transfer = sizeof( usb_hid_report_descriptor );
    pbuffer = & ( usb_hid_report_descriptor.report[0] );

    BYTEn( wLength, 0 ) = Usb_read_byte();
    BYTEn( wLength, 1 ) = Usb_read_byte();
    Usb_ack_receive_setup();

    if( wLength > data_to_transfer )
        {
        if( ( data_to_transfer % EP_CONTROL_LENGTH ) == 0 )
            {
            zlp = true;
            }
        else
            {
            zlp = false;
            }
        }
    else
        {
        data_to_transfer = ( uint8_t )wLength; // send only requested number of data
        }

    while( ( data_to_transfer != 0 ) && ( ! Is_usb_receive_out() ) )
        {
        while( ! Is_usb_read_control_enabled() )
            ;

        nb_byte = 0;
        while( data_to_transfer != 0 ) // Send data until necessary
            {
            if( nb_byte++ == EP_CONTROL_LENGTH ) // Check endpoint 0 size
                {
                break;
                }
            //warning with AVRGCC assumes devices descriptors are stored in the lower 64Kbytes of on-chip flash memory
            Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
            data_to_transfer-- ;
            }
        Usb_send_control_in();
        }

    if( Is_usb_receive_out() )
        {
        // abort from Host
        Usb_ack_receive_out();
        return;
        }
    if( zlp == true )
        {
        while( ! Is_usb_read_control_enabled() )
            ;
        Usb_send_control_in();
        }

    while( ! Is_usb_receive_out() )
        ;
    Usb_ack_receive_out();
    }

/**
 * @brief Manage HID set report request.
 */
void usb_hid_set_report_ouput( void )
    {
    Usb_ack_receive_setup();
    Usb_send_control_in();

    while( ! Is_usb_receive_out() )
        ;
    Usb_ack_receive_out();
    Usb_send_control_in();
    }

/**
 * @brief Manages HID set idle request.
 *
 * @param u8_duration
 * 			When the upper byte of wValue is 0 (zero), the duration is
 * 			indefinite else from 0.004 to 1.020 seconds
 *
 * @param u8_report_id
 * 			0 the idle rate applies to all input reports,
 * 			else only applies to the Report ID
 */
void usb_hid_set_idle( uint8_t u8_report_id, uint8_t u8_duration )
    {
    uint16_t wInterface;

    // Get interface number to put in idle mode
    BYTEn( wInterface, 0 ) = Usb_read_byte();
    BYTEn( wInterface, 1 ) = Usb_read_byte();
    Usb_ack_receive_setup();

    g_u8_report_rate = u8_duration;

    Usb_send_control_in();
    while( ! Is_usb_in_ready() )
        ;
    }

/**
 * @brief Manage HID get idle request.
 *
 * @param u8_report_id
 * 			0 the idle rate applies to all input reports,
 * 			else only applies to the Report ID
 */
void usb_hid_get_idle( uint8_t u8_report_id )
    {
    uint16_t wLength;
    uint16_t wInterface;

    // Get interface number to put in idle mode
    BYTEn( wInterface, 0 ) = Usb_read_byte();
    BYTEn( wInterface, 1 ) = Usb_read_byte();
    BYTEn( wLength, 0 ) = Usb_read_byte();
    BYTEn( wLength, 1 ) = Usb_read_byte();
    Usb_ack_receive_setup();

    if( wLength != 0 )
        {
        Usb_write_byte(g_u8_report_rate);
        Usb_send_control_in();
        }

    while( ! Is_usb_receive_out() )
        ;
    Usb_ack_receive_out();
    }

void usb_hid_set_report_feature( void )
    {

    Usb_ack_receive_setup();
    Usb_send_control_in();

    while( ! Is_usb_receive_out() )
        ;

    if( Usb_read_byte() == 0x55 )
        if( Usb_read_byte() == 0xAA )
            if( Usb_read_byte() == 0x55 )
                if( Usb_read_byte() == 0xAA )
                    {
                    jump_bootloader = 1;
                    }
    Usb_ack_receive_out();
    Usb_send_control_in();
    while( ! Is_usb_in_ready() )
        ;
    }

/**
 * @brief Manage HID get hid descriptor request.
 */
void hid_get_hid_descriptor( void )
    {
    uint16_t wLength;
    uint8_t nb_byte;
    bool zlp = false;
    uint16_t wInterface;

    BYTEn( wInterface, 0 ) = Usb_read_byte();
    BYTEn( wInterface, 1 ) = Usb_read_byte();

    data_to_transfer = sizeof( usb_conf_desc.hid );
    pbuffer = & ( usb_conf_desc.hid.bLength );

    BYTEn( wLength, 0 ) = Usb_read_byte();
    BYTEn( wLength, 1 ) = Usb_read_byte();
    Usb_ack_receive_setup();

    if( wLength > data_to_transfer )
        {
        if( ( data_to_transfer % EP_CONTROL_LENGTH ) == 0 )
            {
            zlp = true;
            }
        else
            {
            zlp = false;
            } // no need of zero length packet
        }
    else
        {
        data_to_transfer = ( uint8_t )wLength; // send only requested number of data
        }

    while( ( data_to_transfer != 0 ) && ( ! Is_usb_receive_out() ) )
        {
        while( ! Is_usb_read_control_enabled() )
            ;

        nb_byte = 0;
        while( data_to_transfer != 0 ) // Send data until necessary
            {
            if( nb_byte++ == EP_CONTROL_LENGTH ) // Check endpoint 0 size
                {
                break;
                }
            //warning with AVRGCC assumes devices descriptors are stored in the lower 64Kbytes of on-chip flash memory
            Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
            data_to_transfer-- ;
            }
        Usb_send_control_in();
        }

    if( Is_usb_receive_out() )
        {
        // abort from Host
        Usb_ack_receive_out();
        return;
        }
    if( zlp == true )
        {
        while( ! Is_usb_read_control_enabled() )
            ;
        Usb_send_control_in();
        }

    while( ! Is_usb_receive_out() )
        ;
    Usb_ack_receive_out();
    }

