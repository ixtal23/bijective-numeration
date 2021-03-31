#
# Copyright © 2021 Maxim Morozov. All rights reserved.
#
# Created by Maxim Morozov on 31/03/2021.
#
# bijective-numeration
#
# CMakeLists.txt
#

cmake_minimum_required(VERSION 2.8)

project(bijective-numeration CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_SKIP_RPATH TRUE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

set(APPLICATION_INCLUDE_DIR include)
set(APPLICATION_SOURCE_DIR src)
set(APPLICATION_INSTALL_DIR bin)

set(APPLICATION_HEADERS
    ${APPLICATION_INCLUDE_DIR}/BijectiveNumeration.h
    ${APPLICATION_INCLUDE_DIR}/BijectiveNumerationTest.h
)

set(APPLICATION_SOURCES
    ${APPLICATION_SOURCE_DIR}/main.cpp
)

include_directories(${APPLICATION_INCLUDE_DIR})

add_compile_options(-pedantic -Wall -Werror -Wextra)

add_executable(${PROJECT_NAME} ${APPLICATION_HEADERS} ${APPLICATION_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${APPLICATION_INSTALL_DIR})
