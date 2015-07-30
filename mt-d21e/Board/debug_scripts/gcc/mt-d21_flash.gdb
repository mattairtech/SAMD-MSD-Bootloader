#*******************************************************
#
#  Connect to J-Link and debug application in flash.
#

# define 'reset' command
define reset

# Connect to the J-Link gdb server
target remote localhost:2331

# Reset the chip to get to a known state
monitor reset

# Select flash device
# ATSAMD21E15A ATSAMD21E16A ATSAMD21E17A ATSAMD21E18A
# ATSAMD21G15A ATSAMD21G16A ATSAMD21G17A ATSAMD21G18A
# ATSAMD21J15A ATSAMD21J16A ATSAMD21J17A ATSAMD21J18A
monitor flash device = ATSAMD21E18A

# Enable flash download and flash breakpoints
monitor flash download = 1

# Load the program
load

# Initializing PC and stack pointer
mon reg sp=(0x00000000)
mon reg pc=(0x00000004)
info reg

# end of 'reset' command
end
