# SAMD-MSD-Bootloader

USB MSD (Mass Storage Device) bootloader for Atmel SAMD21 chips

A USB Mass Storage Class device (MSC or MSD) bootloader can be optionally installed.
This will allow programming of the FLASH without an external programmer. Additionally,
no special software is required on the host computer. The bootloader occupies the first
16KB of FLASH, leaving the rest for the user firmware. On the MT-D21E, the BOOTPROT fuse
bits (2:0) are set 0x01, which will protect the first 16KB of FLASH from internal or
external programming (from 0x00000000 to 0x00004000).

If you need a bootloader with both CDC and MSD, see https://github.com/watterott/SAM-BAR.


## Configuring the Bootloader

You can modify the button and LED pin assignments in mt-d21e/board/user_board.h.
You can modify the the USB vendor ID, product ID, and other USB MSC class device strings
in mt-d21e/conf_usb.h.


## Building the Bootloader

The source code depends on Atmel ASF. I used the Atmel Standalone ARM Toolchain (gcc)
for Linux to build. The Makefile is in mt-d21e/gcc (change to this directory before
making). You will need to edit config.mk in this same directory. It is setup for the
samd21e18a by default. You will need to edit the following:

* PRJ_PATH
* PART
* TARGET_FLASH
* LINKER_SCRIPT_FLASH
* CPPFLAGS (the line with __SAMD21E18A__)

You will need ASF 3.19+ installed in the directory indicated in config.mk (PRJ_PATH)
(../../../../../opt/xdk-asf-3.19.0 on my system). The source code is setup such that
it must be built within the ASF directory tree. In my case, I created a symbolic link
in the xdk-asf-3.19.0 directory called 'SAMD-MSD-Bootloader', pointing to the source
code in '/home/cygnus/SAMD-MSD-Bootloader'.


## Compiling Firmware to use the Bootloader

Because the user firmware will begin executing at FLASH byte address 0x00004000, you
must pass the following flag to the linker (typically LDFLAGS in your makefile):

```
-Wl,--section-start=.text=0x4000
```

Be sure to generate a binary (.bin) file. Many makefiles are set up to generate an elf,
hex, and bin already. You will need to rename the binary file to FLASH.BIN.


## Entering the Bootloader and Programming the Firmware

Enter the bootloader by pressing the bootloader button while powering up the board from
USB. Or, hold the bootloader button while pressing and releasing reset. On the MT-D21E,
the bootloader button must be connected to pin A27 via solder jumper J13 (this will
already be soldered if you ordered the bootloader option). Note that when no user
firmware is installed, the bootloader will not automatically run, so you must always use
the bootloader button. When the bootloader is run for the first time, the host operating
system may take a small amount of time to install drivers. Drivers are already included
with the OS, so there is nothing more to download.

Once loaded, the LED will begin blinking at 2Hz. Mount the “FLASH disk” if it is not
mounted automatically. The only file on the entire volume will be FLASH.BIN. This file
represents the entire FLASH contents and will always exist. The file date will always be
the same upon mounting (2/14/1989). You can read this file simply by copying it to your
hard drive. It will include the installed firmware plus 0xFF for the remainder of the
file (up to the end of the FLASH).

Program the FLASH by copying your new FLASH.BIN over the existing copy on the
“FLASH disk”. On Windows, you can do this with a file manager. On OS X (and possibly
Linux), you will need to use the cp command, which should already be present. Open up a
console (Terminal on OS X) and type (adjust for your system):

```
cp FLASH.BIN '/run/media/cygnus/MT-D21E MSD'
```

Be sure to unmount the volume before running your new firmware, so that any disk caches
are flushed. To run your firmware, simply reset or cycle power without pressing the
bootloader button.


## Technical Notes

First, this is an MSC device (MSD), which merely transfers 512 byte blocks of data
between the host and the flash memory. MSC devices to not need any filesystem
implementation. It is the host that needs to understand the filesystem. Some devices
(cellphones) do implement FAT, but must unmount the filesystem from the phone OS before
mounting to the computer OS using USB MSC (because it is simply a block device to the
computer). Second, the flash memory must not actually contain any FAT structures (like
the file allocation tables themselves). It can only contain the binary file that is
transferred.

With these two things in mind, a minimal FAT implementation was needed, with FAT
structures stored in the bootloader itself rather than anywhere in the rest of the flash.
That's where the Virtual Memory folder comes in. This code basically can tell the
difference between the FAT structures and the user binary, and it inserts/removes the FAT
portions from the 512 byte blocks. This piece of code is the core of this bootloader, and
it was written by Dean Camera of LUFA (www.lufa-lib.org) for an MSC bootloader for AVR
8-bit devices. Brilliant!

Note that ASF includes examples for an MSC based bootloader
(sam0/applications/usb_msc_bootloader). However, this bootloader uses USB host mode to
transfer data from a connected USB flash memory stick. I basically combined this ASF
bootloader with the LUFA virtual memory code and some parts of another ASF example (USB
MSC related).


### Boot Process

The startup portion of the bootloader will run prior to executing your firmware.
This startup code will enable the bootloader button pullup resistor, wait 8ms for the
debouncing capacitor to charge (MT-D21E), then test the state of the button. If it is
not pressed, the user firmware will be executed as follows:

* The stack pointer location will be rebased to 0x00004000
* The interrupt vector table will be rebased to (0x00004000 & SCB_VTOR_TBLOFF_Msk)
* A jump will be perfomed to the user firmware reset vector.


## Bootloader Entry when USB is connected

To enable running the bootloader if USB is connected (run application otherwise),
set BOOT_TEST_VBUS_VALUE in main.h to a non-zero value that represents the voltage
threshold.The value 0x0660 represents about 0.4V. When using the voltage divider on
the MT-D21E (200K top resistor and 20K bottom resistor), this value is reached when
the Vbus pin is at 4.4V. In order to prevent leakage current from one of the diodes
from triggering a false Vbus > 4.4V condition, keep the diode below 70C (158F).

## Known Issues

* You may need to delete the existing FLASH.BIN file prior to copying over the new one.
* On some Linux systems, the bootloader does not work consistently.
* When compiling, you will get warnings about inefficient access to unaligned struct
  members. These can be ignored, as gcc will generate code to access the members
  to avoid unaligned access. Do not add code that references these structs via a pointer.


## Legal

See LICENSE
