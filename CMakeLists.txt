cmake_minimum_required(VERSION 3.19)

project(crypto VERSION 1.0.0 LANGUAGES CXX C )

option(BUILD_TESTS_CRYPTO "Build the tests." OFF)
option(BUILD_DOCS "Build the documentation" OFF)
#option(CRYPTO_PEDANTIC "Enable extra warnings and expensive tests." OFF)
#option(CRYPTO_WERROR   "Halt the compilation with an error on compiler warnings." OFF)

set(CMAKE_CXX_STANDARD 20)
if (WIN32)
  set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /J /utf-8 /Wv:18 /EHsc")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  #TODO: Do I need this for the Excel SDK?
  #set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  #set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif()

include_directories(SYSTEM src/external)
include_directories(SYSTEM src/external/CryptoData/cpp/src/external/websocketpp)

add_subdirectory(src/external/CryptoData)
add_subdirectory(src/external/xll)

add_subdirectory(src/adaptors/xll)

if (BUILD_TESTS_CRYPTO)
  message(STATUS "Building tests")
  add_subdirectory(src/test ${CMAKE_BINARY_DIR}/bin/bin)
endif()

if (BUILD_DOCS)
  message(STATUS "Building docs")
  add_subdirectory(src/docs)
endif()

