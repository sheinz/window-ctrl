
include_directories(
      ./
      ../OneWire/
    )

generate_arduino_library(DS18B20_lib
        SRCS DS18B20.cpp
        HDRS DS18B20.h
        LIBS OneWire_lib
        BOARD mega2560)
