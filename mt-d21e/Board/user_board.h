/**
 * \file
 *
 * \brief MT-D21E board definition
 *
 * Copyright (c) 2014 Atmel Corporation. All rights reserved.
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

#ifndef MT_D21E_H_INCLUDED
#define MT_D21E_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup MT_D21E_group MT-D21E board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup MT_D21E_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "MT_D21E"

/** \name Resonator definitions (SAMD MSD bootloader derives clock from USB)
 *  @{ */
#define BOARD_FREQ_SLCK_XTAL      (32768U)
#define BOARD_FREQ_SLCK_BYPASS    (32768U)
#define BOARD_FREQ_MAINCK_XTAL    0 /* Not Mounted */
#define BOARD_FREQ_MAINCK_BYPASS  0 /* Not Mounted */
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625
/** @} */

/** \name LED definitions
 *  @{ */
#define LED0_PIN                  PIN_PA28
#define LED0_ACTIVE               true
#define LED0_INACTIVE             !LED0_ACTIVE
/** @} */

/** \name SWA definitions (SAMD MSD bootloader entry button)
 *  @{ */
#define SWA_PIN                   PIN_PA27
#define SWA_ACTIVE                false
#define SWA_INACTIVE              !SWA_ACTIVE
#define SWA_EIC_PIN               PIN_PA27A_EIC_EXTINT27
#define SWA_EIC_MUX               MUX_PA27A_EIC_EXTINT27
#define SWA_EIC_PINMUX            PINMUX_PA27A_EIC_EXTINT27
#define SWA_EIC_LINE              27
/** @} */

/** \name SWB definitions (unused in SAMD MSD bootloader)
 *  @{ */
#define SWB_PIN                   PIN_PA31
#define SWB_ACTIVE                false
#define SWB_INACTIVE              !SWB_ACTIVE
#define SWB_EIC_PIN               PIN_PA31A_EIC_EXTINT31
#define SWB_EIC_MUX               MUX_PA31A_EIC_EXTINT31
#define SWB_EIC_PINMUX            PINMUX_PA31A_EIC_EXTINT31
#define SWB_EIC_LINE              31
/** @} */

/**
 * \name LED definitions
 *
 * Wrapper macros for LED, to ensure common naming across all Xplained Pro
 *
 *  @{ */
#define LED_NAME                "LED (blue)"
#define LED_PIN                 LED0_PIN
#define LED_ACTIVE              LED0_ACTIVE
#define LED_INACTIVE            LED0_INACTIVE
#define LED_GPIO                LED0_PIN
#define LED                     LED0_PIN
	 
 /* These are unused in the SAMD MSD Bootloader */
#define LED_PWM4CTRL_MODULE     TCC0
#define LED_PWM4CTRL_CHANNEL    0
#define LED_PWM4CTRL_OUTPUT     0
#define LED_PWM4CTRL_PIN        PIN_PA28E_TCC0_WO0
#define LED_PWM4CTRL_MUX        MUX_PA28E_TCC0_WO0
#define LED_PWM4CTRL_PINMUX     PINMUX_PA28E_TCC0_WO0
/** @} */

/** Number of on-board LEDs */
#define LED_COUNT                 1

/**
 * \name Button A definitions
 *
 * Wrapper macros for button A
 *
 *  @{ */
#define BUTTON_A_NAME             "SWA"
#define BUTTON_A_PIN              SWA_PIN
#define BUTTON_A_ACTIVE           SWA_ACTIVE
#define BUTTON_A_INACTIVE         SWA_INACTIVE
#define BUTTON_A_EIC_PIN          SWA_EIC_PIN
#define BUTTON_A_EIC_MUX          SWA_EIC_MUX
#define BUTTON_A_EIC_PINMUX       SWA_EIC_PINMUX
#define BUTTON_A_EIC_LINE         SWA_EIC_LINE
/** @} */

/**
 * \name Button B definitions
 *
 * Wrapper macros for button B
 *
 *  @{ */
#define BUTTON_B_NAME             "SWB"
#define BUTTON_B_PIN              SWB_PIN
#define BUTTON_B_ACTIVE           SWB_ACTIVE
#define BUTTON_B_INACTIVE         SWB_INACTIVE
#define BUTTON_B_EIC_PIN          SWB_EIC_PIN
#define BUTTON_B_EIC_MUX          SWB_EIC_MUX
#define BUTTON_B_EIC_PINMUX       SWB_EIC_PINMUX
#define BUTTON_B_EIC_LINE         SWB_EIC_LINE
/** @} */

/** Number of on-board buttons */
#define BUTTON_COUNT 2


/** \name USB definitions
 * @{
 */
#define USB_ID
#define USB_TARGET_DP_PIN            PIN_PA25G_USB_DP
#define USB_TARGET_DP_MUX            MUX_PA25G_USB_DP
#define USB_TARGET_DP_PINMUX         PINMUX_PA25G_USB_DP
#define USB_TARGET_DM_PIN            PIN_PA24G_USB_DM
#define USB_TARGET_DM_MUX            MUX_PA24G_USB_DM
#define USB_TARGET_DM_PINMUX         PINMUX_PA24G_USB_DM

/* These are unused in the SAMD MSD Bootloader */
#define USB_VBUS_PIN                 PIN_PA7
#define USB_VBUS_EIC_LINE            7
#define USB_VBUS_EIC_MUX             MUX_PA7A_EIC_EXTINT7
#define USB_VBUS_EIC_PINMUX          PINMUX_PA7A_EIC_EXTINT7
#define USB_ID_PIN                   PIN_PA03
#define USB_ID_EIC_LINE              3
#define USB_ID_EIC_MUX               MUX_PA03A_EIC_EXTINT3
#define USB_ID_EIC_PINMUX            PINMUX_PA03A_EIC_EXTINT3
/** @} */


/** @} */


/**
 * \brief Turns off the specified LEDs.
 *
 * \param led_gpio LED to turn off (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Off(led_gpio)     port_pin_set_output_level(led_gpio,false)

/**
 * \brief Turns on the specified LEDs.
 *
 * \param led_gpio LED to turn on (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_On(led_gpio)      port_pin_set_output_level(led_gpio,true)

/**
 * \brief Toggles the specified LEDs.
 *
 * \param led_gpio LED to toggle (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Toggle(led_gpio)  port_pin_toggle_output_level(led_gpio)

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* MT_D21E_H_INCLUDED */
