cmake_minimum_required(VERSION 3.21)
project(OculusLib C)

set(CMAKE_C_STANDARD 99)

add_library(OculusLib SHARED library.c)
