cmake_minimum_required(VERSION 3.5)


########################################################################
# version
########################################################################
set(APP_NAME "cpp-skeleton")
set(APP_EXECUTABLE_NAME "cpp-skeleton")

set(APP_VERSION_MAJOR 2)
set(APP_VERSION_MINOR 0)
set(APP_VERSION_PATCH 0)
SET(APP_VERSION_LONG "${APP_VERSION_MAJOR}.${APP_VERSION_MINOR}.${APP_VERSION_PATCH}")
project(cpp-skeleton VERSION "${APP_VERSION_LONG}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/utils/Common.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/Common.h)

########################################################################
# Install directories
########################################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CONFIGURATION_TYPES Release Debug)

########################################################################
# define output directories
########################################################################

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

########################################################################
# lib and includes
########################################################################

set(LOCAL_LIBRARY /opt/local/lib)
set(LOCAL_HEADERS /opt/local/include)

link_directories(${LOCAL_LIBRARY})
include_directories(${LOCAL_HEADERS})

########################################################################
# Find build dependencies
########################################################################
#boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message(STATUS "Found BOOST: ${Boost_INCLUDE_DIR}")
endif()

#opencv
find_package(OpenCV)
if(OpenCV_FOUND)
    message(STATUS "Found OpenCV: ${OpenCV_INCLUDE_DIR}")
endif()


find_package(PQXX)
if(PQXX_FOUND)
    message(STATUS "Found PQXX")
endif()




########################################################################
# project specific
########################################################################

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

#set(LIBUSB_HEADERS ${LOCAL_HEADERS}/libusb-1.0/)
#set(LIBUSB_LIBRARY ${LOCAL_LIBRARY}/libusb-1.0.so)

set(PROJECT_SPECIFIC_INCLUDES
        ${CMAKE_SOURCE_DIR}/src/**/*.h
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/**/**/*.h
        ${CMAKE_SOURCE_DIR}/src/**/*.hpp
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        ${CMAKE_SOURCE_DIR}/src/**/**/*.hpp)

set(PROJECT_INCLUDES
        ${OpenCV_INCLUDE_DIR}
        ${PostgreSQL_INCLUDE_DIR}
        ${PQXX_INCLUDE_DIRECTORIES}
        ${Boost_INCLUDE_DIR}
        ${PROJECT_SPECIFIC_INCLUDES})

set(PROJECT_LIBRARIES
        ${OpenCV_LIBS}
        ${PostgreSQL_LIBRARY}
        ${Boost_LIBRARIES}
        ${PQXX_LIBRARIES})
#  LIBSERIAL_FOUND, if false, do not try to link to LibSerial
#  LIBSERIAL_LIBRARY, where to find LibSerial
#  LIBSERIAL_INCLUDE_DIR, where to find SerialPort.h

FILE(GLOB SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/**/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/**/**/*.cpp)
########################################################################
# Subdirectory
########################################################################

add_subdirectory(docs)
add_subdirectory(src)
add_subdirectory(test)
