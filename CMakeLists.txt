cmake_minimum_required(VERSION 3.10)
project(crypto CXX C)

# Determine if CRYPTO is built as a subproject (using add_subdirectory)
# or if it is the master project.
if (NOT DEFINED CRYPTO_MASTER_PROJECT)
  set(CRYPTO_MASTER_PROJECT OFF)
  if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CRYPTO_MASTER_PROJECT ON)
    message(STATUS "CMake version: ${CMAKE_VERSION}")
  endif ()
endif ()

option(CRYPTO_PEDANTIC "Enable extra warnings and expensive tests." OFF)
option(CRYPTO_WERROR   "Halt the compilation with an error on compiler warnings." OFF)

# Options that control generation of various targets.
option(CRYPTO_TEST "Generate the test target." OFF) #${CRYPTO_MASTER_PROJECT})
option(CRYPTO_DOC "Generate the doc target" OFF) #${CRYPTO_MASTER_PROJECT})

# Joins arguments and places the results in ${result_var}.
function(join result_var)
  set(result )
  foreach (arg ${ARGN})
    set(result "${result}${arg}")
  endforeach ()
  set(${result_var} "${result}" PARENT_SCOPE)
endfunction()

# Get version from core.h
file(READ cpp/include/CRYPTO/core.h core_h)
if (NOT core_h MATCHES "CRYPTO_VERSION ([0-9]+)([0-9][0-9])([0-9][0-9])")
  message(FATAL_ERROR "Cannot get CRYPTO_VERSION from core.h.")
endif ()
# Use math to skip leading zeros if any.
math(EXPR CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MATCH_1})
math(EXPR CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MATCH_2})
math(EXPR CPACK_PACKAGE_VERSION_PATCH ${CMAKE_MATCH_3})
join(CRYPTO_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
message(STATUS "Crypto Data Version: ${CRYPTO_VERSION}")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 20)
if (WIN32)
  set(CMAKE_CXX_FLAGS "-D_WIN32_WINNT=0x0601 /J /utf-8 /Wv:18  /EHsc")  
  set(CMAKE_CXX_FLAGS_RELEASE "/MT")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
elseif (UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -Werror -Wfatal-errors -Wpedantic -Wextra -Wmissing-include-dirs -Wconversion -Wsign-conversion -pthread")
	add_compile_options(-Wall -Werror -Wfatal-errors -Wpedantic -Wextra -Wmissing-include-dirs -Wconversion -Wsign-conversion -pthread)

	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -march=native -g")
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.71 REQUIRED COMPONENTS random)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

find_package(OpenSSL 1.1 REQUIRED)
include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})

find_package(TBB CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include_directories(SYSTEM cpp/src/external)

add_subdirectory(cpp/src/external/CryptoData)
add_subdirectory(cpp/src/external/xll)

add_subdirectory(cpp/src/adaptors/xll)

if (CRYPTO_TEST)
  message(STATUS "Building tests")
  add_subdirectory(cpp/src/test)
endif()
if (CRYPTO_DOC)
  message(STATUS "Building documentaion")
  add_subdirectory(cpp/docs)
endif()
