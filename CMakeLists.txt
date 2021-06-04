cmake_minimum_required(VERSION 3.19)
project(crypto CXX C)

option(BUILD_TESTS "Build the tests." OFF)
option(BUILD_DOCS "Build the documentation" OFF)
#option(CRYPTO_PEDANTIC "Enable extra warnings and expensive tests." OFF)
#option(CRYPTO_WERROR   "Halt the compilation with an error on compiler warnings." OFF)

set(CRYPTO_MAJOR_VERSION 1)
set(CRYPTO_MINOR_VERSION 0)
set(CRYPTO_PATCH_VERSION 0)
set(CRYPTO_VERSION
    ${CRYPTO_MAJOR_VERSION}.${CRYPTO_MINOR_VERSION}.${CRYPTO_PATCH_VERSION})

set(CMAKE_CXX_STANDARD 20)
if (WIN32)
  set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /J /utf-8 /Wv:18 /EHsc")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  #TODO: Do I need this for the Excel SDK?
  #set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  #set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

include_directories(SYSTEM cpp/src/external)
include_directories(SYSTEM cpp/src/external/websocketpp)

add_subdirectory(cpp/src/external/CryptoData)
add_subdirectory(cpp/src/external/xll)

add_subdirectory(cpp/src/adaptors/xll)

if (BUILD_TESTS)
  message(STATUS "Building tests")
  add_subdirectory(cpp/src/test)
endif()

if (BUILD_DOCS)
  message(STATUS "Building docs")
  add_subdirectory(cpp/docs)
endif()
