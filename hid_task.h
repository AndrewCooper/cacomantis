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

//_____ I N C L U D E S ____________________________________________________


#include "config.h"

//_____ M A C R O S ________________________________________________________


//_____ T Y P E S __________________________________________________________

struct hid_report
	{
	/*
	 * Inputs, 1bit * 13
	 * Usage: Generic Desktop / Gamepad / Button
	 */
	U8		b1:1;
	U8		b2:1;
	U8		b3:1;
	U8		b4:1;
	U8		b5:1;
	U8		b6:1;
	U8		b7:1;
	U8		b8:1;
	U8		b9:1;
	U8		b10:1;
	U8		b11:1;
	U8		b12:1;
	U8		b13:1;

	/*
	 * Padding, 1bit * 3
	 */
	U8		pad1:3;

	/*
	 * Inputs: 4bit * 1
	 * Usage: Generic Desktop / Gamepad
	 * Logical: 0..7
	 * Physical: 0..315
	 */
	/// hatswitch
	U8		hat:4;

	/*
	 * Padding 4bit * 1
	 */
	U8		pad2:4;

	/*
	 * Inputs: 8bit * 4
	 * Usage: Generic Desktop / Gamepad
	 * Logical: 0..255
	 * Physical: 0..255
	 */
	/// X axis
	U8		x;
	/// Y axis
	U8		y;
	/// Z axis
	U8		z;
	/// Rz axis
	U8		Rz;

	/*
	 * Inputs: 8bit * 12
	 * Usage: Generic Desktop / 65280 (Vendor)
	 */
	/// Usage 0x20
	U8		iVendorX20;
	/// Usage 0x21
	U8		iVendorX21;
	/// Usage 0x22
	U8		iVendorX22;
	/// Usage 0x23
	U8		iVendorX23;
	/// Usage 0x24
	U8		iVendorX24;
	/// Usage 0x25
	U8		iVendorX25;
	/// Usage 0x26
	U8		iVendorX26;
	/// Usage 0x27
	U8		iVendorX27;
	/// Usage 0x28
	U8		iVendorX28;
	/// Usage 0x29
	U8		iVendorX29;
	/// Usage 0x2A
	U8		iVendorX2A;
	/// Usage 0x2B
	U8		iVendorX2B;

	/*
	 * Features: 8bit * 8
	 * Usage: Generic Desktop / 65280 (Vendor)
	 */
	/// Usage 0x2621
	U8		iFeatureD2621_1;
	U8		iFeatureD2621_2;
	U8		iFeatureD2621_3;
	U8		iFeatureD2621_4;
	U8		iFeatureD2621_5;
	U8		iFeatureD2621_6;
	U8		iFeatureD2621_7;
	U8		iFeatureD2621_8;

	/*
	 * Outputs: 8bit * 8
	 * Usage: Generic Desktop / 65280 (Vendor)
	 */
	/// Usage 0x2621
	U8		iOutputD2621_1;
	U8		iOutputD2621_2;
	U8		iOutputD2621_3;
	U8		iOutputD2621_4;
	U8		iOutputD2621_5;
	U8		iOutputD2621_6;
	U8		iOutputD2621_7;
	U8		iOutputD2621_8;

	/*
	 * Inputs: 16bit * 4
	 * Usage: Generic Destop / 65280 (Vendor)
	 * Logical: 0..1023
	 * Physical: 0..1023
	 */
	/// Usage 0x2C
	U16		iInputX2C;
	/// Usage 0x2D
	U16		iInputX2D;
	/// Usage 0x2E
	U16		iInputX2E;
	/// Usage 0x2F
	U16		iInputx2F;
	};



#endif /* _HID_TASK_H_ */

