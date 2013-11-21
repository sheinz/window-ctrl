# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

set(ARDUINO_DEFAULT_BOARD diecimila) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified

add_subdirectory(lib/LiquidCrystal)
add_subdirectory(lib/OneWire)
add_subdirectory(lib/DS18B20)
add_subdirectory(lib/AFMotor)

# for eclipse indexer
#add_definitions(-DARDUINO=105)
# 
include_directories(
    lib/DS18B20
    lib/OneWire
    lib/LiquidCrystal
    lib/AFMotor
)



set(SOURCES 
    main.cpp 
    CTaskMgr.cpp 
    CWindow.cpp 
    CKeyboard.cpp 
    CKeyHandler.cpp
    CBeep.cpp
    CDisplay.cpp
    CTempController.cpp
    CTempProvider.cpp
    CLifeCycle.cpp
)

set(LIBRARIES
    LiquidCrystalLib
    OneWire_lib
    DS18B20_lib
    AFMotor_lib
    )

generate_arduino_firmware(window-temp-ctrl
    SRCS ${SOURCES}
    LIBS ${LIBRARIES}
    BOARD mega2560)

