cmake_minimum_required(VERSION 3.6)

if (DEFINED ENV{VITASDK})
    SET(CMAKE_VITASDK $ENV{VITASDK} CACHE PATH "" FORCE)
    SET(CMAKE_VITASDK_PREFIX ${CMAKE_VITASDK}/bin/arm-vita-eabi-)
else ()
    MESSAGE(FATAL_ERROR "You must setup $VITASDK first!")
endif ()

SET(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_C_COMPILER ${CMAKE_VITASDK_PREFIX}gcc)
SET(CMAKE_CXX_COMPILER ${CMAKE_VITASDK_PREFIX}g++)

SET(COMMON_FLAGS "-g -Wl,-q -ffat-lto-objects -flto")
SET(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=gnu++11")
SET(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -ffunction-sections -ffat-lto-objects -flto")

project(vitapp C CXX)

SET(CMAKE_INSTALL_PREFIX ${CMAKE_VITASDK}/arm-vita-eabi CACHE PATH "" FORCE)
MESSAGE(STATUS "Install to ${CMAKE_INSTALL_PREFIX}")

add_subdirectory(libpromoter)
add_subdirectory(libvitapp)

install(FILES vitapp.hh DESTINATION include)
