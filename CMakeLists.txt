cmake_minimum_required(VERSION 3.6)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_C_COMPILER arm-vita-eabi-gcc)
SET(CMAKE_CXX_COMPILER arm-vita-eabi-g++)
 
SET(COMMON_FLAGS "-g -Wl,-q -ffat-lto-objects -flto")
SET(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=gnu++11")
SET(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -ffunction-sections -ffat-lto-objects -flto")

project(vitapp C CXX)

if (DEFINED ENV{VITASDK})
    SET(CMAKE_INSTALL_PREFIX $ENV{VITASDK}/arm-vita-eabi CACHE PATH "" FORCE)
    MESSAGE(STATUS "Install to ${CMAKE_INSTALL_PREFIX}")
endif ()

add_subdirectory(libpromoter)
add_subdirectory(libvitapp)

install(FILES vitapp.hh DESTINATION include)
