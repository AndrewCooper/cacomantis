/*This file is prepared for Doxygen automatic documentation generation.*/
/**
 * @file
 *
 * @brief This file contains the function declarations
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

#ifndef _HID_TASK_H_
#define _HID_TASK_H_

//_____ I N C L U D E S ________________________________________________________


#include "config.h"

//_____ M A C R O S ____________________________________________________________


//_____ T Y P E S __________________________________________________________

struct hid_report
{
    /*
     * Inputs, 1bit * 13
     * Usage: Generic Desktop / Gamepad / Button
     */
    union
    {
        struct
        {
        uint8_t b1 :1;
        uint8_t b2 :1;
        uint8_t b3 :1;
        uint8_t b4 :1;
        uint8_t b5 :1;
        uint8_t b6 :1;
        uint8_t b7 :1;
        uint8_t b8 :1;
        uint8_t b9 :1;
        uint8_t b10 :1;
        uint8_t b11 :1;
        uint8_t b12 :1;
        uint8_t b13 :1;

        /*
         * Padding, 1bit * 3
         */
        uint8_t pad1 :3;
        } bits;

        uint16_t raw;
    } buttons;

    /*
     * Inputs: 4bit * 1
     * Usage: Generic Desktop / Gamepad
     * Logical: 0..7
     * Physical: 0..315
     */
    /// hatswitch
    uint8_t hat :4;

    /*
     * Padding 4bit * 1
     */
    uint8_t pad2 :4;

    /*
     * Inputs: 8bit * 4
     * Usage: Generic Desktop / Gamepad
     * Logical: 0..255
     * Physical: 0..255
     */
    /// X axis
    uint8_t x;
    /// Y axis
    uint8_t y;
    /// Z axis
    uint8_t z;
    /// Rz axis
    uint8_t Rz;

    /*
     * Inputs: 8bit * 12
     * Usage: Generic Desktop / 65280 (Vendor)
     */
    /// Usage 0x20
    uint8_t iVendorX20;
    /// Usage 0x21
    uint8_t iVendorX21;
    /// Usage 0x22
    uint8_t iVendorX22;
    /// Usage 0x23
    uint8_t iVendorX23;
    /// Usage 0x24
    uint8_t iVendorX24;
    /// Usage 0x25
    uint8_t iVendorX25;
    /// Usage 0x26
    uint8_t iVendorX26;
    /// Usage 0x27
    uint8_t iVendorX27;
    /// Usage 0x28
    uint8_t iVendorX28;
    /// Usage 0x29
    uint8_t iVendorX29;
    /// Usage 0x2A
    uint8_t iVendorX2A;
    /// Usage 0x2B
    uint8_t iVendorX2B;

    /*
     * Features: 8bit * 8
     * Usage: Generic Desktop / 65280 (Vendor)
     */
    /// Usage 0x2621
    uint8_t iFeatureD2621_1;
    uint8_t iFeatureD2621_2;
    uint8_t iFeatureD2621_3;
    uint8_t iFeatureD2621_4;
    uint8_t iFeatureD2621_5;
    uint8_t iFeatureD2621_6;
    uint8_t iFeatureD2621_7;
    uint8_t iFeatureD2621_8;

    /*
     * Outputs: 8bit * 8
     * Usage: Generic Desktop / 65280 (Vendor)
     */
    /// Usage 0x2621
    uint8_t iOutputD2621_1;
    uint8_t iOutputD2621_2;
    uint8_t iOutputD2621_3;
    uint8_t iOutputD2621_4;
    uint8_t iOutputD2621_5;
    uint8_t iOutputD2621_6;
    uint8_t iOutputD2621_7;
    uint8_t iOutputD2621_8;

    /*
     * Inputs: 16bit * 4
     * Usage: Generic Destop / 65280 (Vendor)
     * Logical: 0..1023
     * Physical: 0..1023
     */
    /// Usage 0x2C
    uint16_t iInputX2C;
    /// Usage 0x2D
    uint16_t iInputX2D;
    /// Usage 0x2E
    uint16_t iInputX2E;
    /// Usage 0x2F
    uint16_t iInputx2F;
};

#endif /* _HID_TASK_H_ */

