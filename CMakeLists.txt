#=============================================================================#
# Author: 
# Date:  28.10.2013 
#                                                                             #
# Description: Arduino Temperature controller
#                                                                             #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain


cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(window-temp-ctrl C CXX)

print_board_list()
print_programmer_list()

add_subdirectory(src)
