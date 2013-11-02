# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

set(ARDUINO_DEFAULT_BOARD diecimila) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified

add_subdirectory(lib/LiquidCrystal)   

# for eclipse indexer
#add_definitions(-DARDUINO=105)


#====================================================================#
# Advanced firwmare example
#====================================================================#
generate_arduino_firmware(window-temp-ctrl
    SRCS main.cpp AFMotor.cpp
    LIBS LiquidCrystalLib
    BOARD mega2560)

