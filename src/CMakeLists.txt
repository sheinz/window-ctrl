# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

set(ARDUINO_DEFAULT_BOARD diecimila) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified

add_subdirectory(lib/LiquidCrystal)   

# for eclipse indexer
#add_definitions(-DARDUINO=105)


set(SOURCES 
    main.cpp 
    AFMotor.cpp 
    CTaskMgr.cpp 
    CWindow.cpp 
    CKeyboard.cpp 
    CKeyHandler.cpp
)
    

generate_arduino_firmware(window-temp-ctrl
    SRCS ${SOURCES}
    LIBS LiquidCrystalLib
    BOARD mega2560)

