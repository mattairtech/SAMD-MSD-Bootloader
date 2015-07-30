#
# Copyright (c) 2011 Atmel Corporation. All rights reserved.
#
# \asf_license_start
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
#    Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# \asf_license_stop
#

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = ../../../../../opt/xdk-asf-3.19.0

# Target CPU architecture: cortex-m3, cortex-m4
ARCH = cortex-m0plus

# Target part:
# samd21e15a samd21e16a samd21e17a samd21e18a
# samd21g15a samd21g16a samd21g17a samd21g18a
# samd21j15a samd21j16a samd21j17a samd21j18a
PART = samd21e18a

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET_FLASH = msd_bootloader_samd21e18a_flash.elf

# List of C source files.
CSRCS = \
       SAMD-MSD-Bootloader/main.c                              \
       SAMD-MSD-Bootloader/ui.c                                \
       SAMD-MSD-Bootloader/virtual_flash_mem/virtual_flash_mem.c \
       SAMD-MSD-Bootloader/virtual_flash_mem/VirtualFAT.c      \
       SAMD-MSD-Bootloader/mt-d21e/Board/board_init.c          \
       common/services/sleepmgr/samd/sleepmgr.c           \
       common/services/storage/ctrl_access/ctrl_access.c  \
       common/services/usb/class/msc/device/udi_msc.c     \
       common/services/usb/class/msc/device/udi_msc_desc.c \
       common/services/usb/udc/udc.c                      \
       common/utils/interrupt/interrupt_sam_nvic.c        \
       common2/services/delay/sam0/systick_counter.c      \
       sam0/drivers/nvm/nvm.c                             \
       sam0/drivers/extint/extint.c                       \
       sam0/drivers/extint/extint_callback.c              \
       sam0/drivers/port/port.c                           \
       sam0/drivers/system/clock/clock_samd21_r21/clock.c \
       sam0/drivers/system/clock/clock_samd21_r21/gclk.c  \
       sam0/drivers/system/interrupt/system_interrupt.c   \
       sam0/drivers/system/pinmux/pinmux.c                \
       sam0/drivers/system/system.c                       \
       sam0/drivers/wdt/wdt.c                             \
       sam0/drivers/wdt/wdt_callback.c                    \
       sam0/drivers/usb/stack_interface/usb_device_udd.c  \
       sam0/drivers/usb/stack_interface/usb_dual.c        \
       sam0/drivers/usb/usb.c                             \
       sam0/utils/cmsis/samd21/source/gcc/startup_samd21.c \
       sam0/utils/cmsis/samd21/source/system_samd21.c     \
       sam0/utils/syscalls/gcc/syscalls.c

# List of assembler source files.
ASSRCS = 

# List of include paths.
INC_PATH = \
       SAMD-MSD-Bootloader                                     \
       SAMD-MSD-Bootloader/mt-d21e                             \
       SAMD-MSD-Bootloader/mt-d21e/gcc                         \
       SAMD-MSD-Bootloader/mt-d21e/Board                       \
       SAMD-MSD-Bootloader/mt-d21e/Board/board_config          \
       SAMD-MSD-Bootloader/virtual_flash_mem                   \
       SAMD-MSD-Bootloader/virtual_flash_mem/module_config     \
       common/boards                                      \
       common/services/sleepmgr                           \
       common/services/storage/ctrl_access                \
       common/services/usb                                \
       common/services/usb/class/msc                      \
       common/services/usb/class/msc/device               \
       common/services/usb/udc                            \
       common/utils                                       \
       common2/services/delay                             \
       common2/services/delay/sam0                        \
       sam0/boards                                        \
       sam0/drivers/nvm                                   \
       sam0/drivers/extint                                \
       sam0/drivers/port                                  \
       sam0/drivers/system                                \
       sam0/drivers/system/clock                          \
       sam0/drivers/system/clock/clock_samd21_r21         \
       sam0/drivers/system/interrupt                      \
       sam0/drivers/system/interrupt/system_interrupt_samd21 \
       sam0/drivers/system/pinmux                         \
       sam0/drivers/wdt                                   \
       sam0/drivers/usb                                   \
       sam0/drivers/usb/stack_interface                   \
       sam0/utils                                         \
       sam0/utils/cmsis/samd21/include                    \
       sam0/utils/cmsis/samd21/source                     \
       sam0/utils/header_files                            \
       sam0/utils/preprocessor                            \
       thirdparty/CMSIS/Include                           \
       thirdparty/CMSIS/Lib/GCC

# Additional search paths for libraries.
LIB_PATH =  \
       thirdparty/CMSIS/Lib/GCC                          

# List of libraries to use during linking.
LIBS =  \
       arm_cortexM0l_math                                

# Path relative to top level directory pointing to a linker script.
# samd21e15a samd21e16a samd21e17a samd21e18a
# samd21g15a samd21g16a samd21g17a samd21g18a
# samd21j15a samd21j16a samd21j17a samd21j18a
LINKER_SCRIPT_FLASH = sam0/utils/linker_scripts/samd21/gcc/samd21e18a_flash.ld

# Path relative to top level directory pointing to a linker script.
DEBUG_SCRIPT_FLASH = SAMD-MSD-Bootloader/mt-d21e/Board/debug_scripts/gcc/mt-d21_flash.gdb

# Project type parameter: all, sram or flash (flash only for SAMD MSD Bootloader)
PROJECT_TYPE        = flash

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os (was -O1)
OPTIMIZATION = -Os

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
#CFLAGS = -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -ffunction-sections
CFLAGS =

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
#
# __SAMD21E15A__ __SAMD21E16A__ __SAMD21E17A__ __SAMD21E18A__
# __SAMD21G15A__ __SAMD21G16A__ __SAMD21G17A__ __SAMD21G18A__
# __SAMD21J15A__ __SAMD21J16A__ __SAMD21J17A__ __SAMD21J18A__
CPPFLAGS = \
       -D ACCESS_USB_ENABLED                              \
       -D ARM_MATH_CM0=true                               \
       -D BOARD=USER_BOARD                                \
       -D EXTINT_CALLBACK_MODE=true                       \
       -D UDD_ENABLE                                      \
       -D USB_DEVICE_LPM_SUPPORT                          \
       -D VIRTUAL_MEMORY_ENABLE                           \
       -D WDT_CALLBACK_MODE=true                          \
       -D SYSTICK_MODE                                    \
       -D __SAMD21E18A__
       
# Extra flags to use when linking
LDFLAGS = \
                                                          \
       -Wl,--defsym,STACK_SIZE=0x700                      \
       -Wl,--defsym,__stack_size__=0x700

# Pre- and post-build commands
PREBUILD_CMD = 
POSTBUILD_CMD = 