/**
 * \file
 *
 * \brief Main functions for MSC example
 *
 * Copyright (c) 2009-2014 Atmel Corporation. All rights reserved.
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

#include "main.h"

static volatile bool main_b_msc_enable = false;


/**
 * \brief Function for starting application
 *
 * This function will configure the WDT module and enable it. The LED is
 * kept toggling till WDT reset occurs.
 */
void start_application(void)
{
	struct wdt_conf wdt_config;
	
	/* Turn off LED */
	port_pin_set_output_level(BOOT_LED, false);
	
	/* Get WDT default configuration */
	wdt_get_config_defaults(&wdt_config);
	
	/* Set the required clock source and timeout period */
	wdt_config.clock_source   = GCLK_GENERATOR_4;
	wdt_config.timeout_period = WDT_PERIOD_256CLK;
	
	/* Initialize and enable the Watchdog with the user settings */
	wdt_set_config(&wdt_config);
	
	/* Turn ON LED after watchdog has initialized */
	port_pin_set_output_level(BOOT_LED, true);
	
	while (1) {
		/* Wait for watchdog reset */
	}
}

/**
 * \brief Function for checking whether to enter boot mode or application mode
 *
 * This function will check the state of BOOT_LOAD_PIN. If it is pressed, it
 * continues execution in bootloader mode. Else, it reads the first location
 * from the application section and checks whether it is 0xFFFFFFFF. If yes,
 * then the application section is empty and it waits indefinitely there. If
 * not, it jumps to the application and starts execution from there.
 * Access to direct peripheral registers are made in this routine to enable
 * quick decision on application or bootloader mode.
 */
void check_boot_mode(void)
{
	uint32_t app_check_address;
	uint32_t *app_check_address_ptr;
	
	/* Check if WDT is locked */
	if (!(WDT->CTRL.reg & WDT_CTRL_ALWAYSON)) {
		/* Disable the Watchdog module */
		WDT->CTRL.reg &= ~WDT_CTRL_ENABLE;
	}
	
	delay_init();
	
	volatile PortGroup *boot_port = (volatile PortGroup *)(&(PORT->Group[BOOT_LOAD_PIN / 32]));
	volatile bool boot_en;
	
	/* Enable the input mode in Boot GPIO Pin */
	boot_port->DIRCLR.reg = GPIO_BOOT_PIN_MASK;
	boot_port->PINCFG[BOOT_LOAD_PIN & 0x1F].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	boot_port->OUTSET.reg = GPIO_BOOT_PIN_MASK;
	delay_ms(8); // Allow 100nF debouncing capacitor to charge
	
	/* Read the BOOT_LOAD_PIN status */
	boot_en = ((boot_port->IN.reg) & GPIO_BOOT_PIN_MASK);
	
	/* Check the BOOT pin or the reset cause is Watchdog */
	if ((boot_en) || (PM->RCAUSE.reg & PM_RCAUSE_WDT)) {
		app_check_address = APP_START_ADDRESS;
		app_check_address_ptr = (uint32_t *) app_check_address;
		
		/*
		 * Read the first location of application section
		 * which contains the address of stack pointer.
		 * If it is 0xFFFFFFFF then the application section is empty.
		 */
		if (*app_check_address_ptr == 0xFFFFFFFF) {
			while (1) {
				/* Wait indefinitely */
			}
		}
		/* Pointer to the Application Section */
		void (*application_code_entry)(void);
		
		/* Rebase the Stack Pointer */
		__set_MSP(*(uint32_t *) APP_START_ADDRESS);
		
		/* Rebase the vector table base address */
		SCB->VTOR = ((uint32_t) APP_START_ADDRESS & SCB_VTOR_TBLOFF_Msk);
		
		/* Load the Reset Handler address of the application */
		application_code_entry = (void (*)(void))(unsigned *)(*(unsigned *)(APP_START_ADDRESS + 4));
		
		/* Jump to user Reset Handler in the application */
		application_code_entry();
	}
}


/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	struct nvm_config config;
	
	/* Check switch state to enter boot mode or application mode */
	check_boot_mode();
	
	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();
	system_init();
	
	/* Get NVM default configuration and load the same */
	nvm_get_config_defaults(&config);
	nvm_set_config(&config);
	
	/* Turn on LED */
	port_pin_set_output_level(BOOT_LED, true);

	ui_init();
	ui_powerdown();

	// Start USB stack to authorize VBus monitoring
	udc_start();

	// The main loop manages only the power mode
	// because the USB management is done by interrupt
	while (true) {
		if (main_b_msc_enable) {
			if (!udi_msc_process_trans()) {
				sleepmgr_enter_sleep();
			}
		}else{
			sleepmgr_enter_sleep();
		}
	}
	
	start_application();
}

void main_suspend_action(void)
{
	ui_powerdown();
}

void main_resume_action(void)
{
	ui_wakeup();
}

void main_sof_action(void)
{
	if (!main_b_msc_enable)
		return;
	ui_process(udd_get_frame_number());
}

bool main_msc_enable(void)
{
	main_b_msc_enable = true;
	return true;
}

void main_msc_disable(void)
{
	main_b_msc_enable = false;
}

/**
 * \mainpage ASF USB Device MSC
 *
 * \section intro Introduction
 * This example shows how to implement a USB Device Mass Storage
 * on Atmel MCU with USB module.
 *
 * \section startup Startup
 * The example uses all memories available on the board and connects these to
 * USB Device Mass Storage stack. After loading firmware, connect the board
 * (EVKxx,Xplain,...) to the USB Host. When connected to a USB host system
 * this application allows to display all available memories as a
 * removable disks in the Unix/Mac/Windows operating systems.
 * \note
 * This example uses the native MSC driver on Unix/Mac/Windows OS, except for Win98.
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB Device stack and MSC modules:
 *   <br>services/usb/
 *   <br>services/usb/udc/
 *   <br>services/usb/class/msc/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h   configuration of each module
 *       - ui.c        implement of user's interface (leds)
 *
 * <SUP>1</SUP> The memory data transfers are done outside USB interrupt routine.
 * This is done in the MSC process ("udi_msc_process_trans()") called by main loop.
 */
