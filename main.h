/**
 * \file
 *
 * \brief Declaration of main function used by MSC example
 *
 * Copyright (c) 2009-2011 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include <asf.h>
//#include <compiler.h>
#include "ui.h"
#include "mt-d21e/conf_usb.h"
#include "mt-d21e/conf_bootloader.h"

/* To enable running the bootloader if USB is connected (run application otherwise),
 * set BOOT_TEST_VBUS_VALUE to a non-zero value that represents the voltage threshold.
 * This value represents about 0.4V. When using the voltage divider on the MT-D21E
 * (200K top resistor and 20K bottom resistor), this value is reached when the
 * Vbus pin is at 4.4V. In order to prevent leakage current from one of the diodes
 * from triggering a false Vbus > 4.4V condition, keep the diode below 70C.
 */ 
//#define BOOT_TEST_VBUS_VALUE	0x0660
#define BOOT_TEST_VBUS_VALUE	0

void start_application(void);
void configure_adc(void);
void check_boot_mode(void);

/*! \brief Called by MSC interface
 * Callback running when USB Host enable MSC interface
 *
 * \retval true if MSC startup is ok
 */
bool main_msc_enable(void);

/*! \brief Called by MSC interface
 * Callback running when USB Host disable MSC interface
 */
void main_msc_disable(void);

/*! \brief Called when a start of frame is received on USB line
 */
void main_sof_action(void);

/*! \brief Enters the application in low power mode
 * Callback called when USB host sets USB line in suspend state
 */
void main_suspend_action(void);

/*! \brief Called by UDD when the USB line exit of suspend state
 */
void main_resume_action(void);

#endif // _MAIN_H_
