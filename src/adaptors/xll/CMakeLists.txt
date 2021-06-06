include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(cryptoXL SHARED   
  TickStream.cpp)

target_compile_definitions (cryptoXL PUBLIC UNICODE)
target_compile_definitions (cryptoXL PUBLIC _UNICODE)

target_include_directories(cryptoXL PRIVATE 
  xll 
  ${CMAKE_SOURCE_DIR}/src/external/xll 
  ${CMAKE_SOURCE_DIR}/src/external/CryptoData/cpp/src/marketdata
  ${CMAKE_SOURCE_DIR}/src/external/CryptoData/cpp/src/feed/exchange/FTX
  ${CMAKE_SOURCE_DIR}/src/external/CryptoData/cpp/src/external
  ${CMAKE_SOURCE_DIR}/src/external/CryptoData/cpp/src/external/websocketpp)

target_link_libraries(cryptoXL 
  xll 
  XLCALL32 
  streaming
  ws
  rest
  ${CONAN_LIBS})  

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_link_directories(cryptoXL PRIVATE ${CMAKE_SOURCE_DIR}/src/external/xll/xll/x64)
else()
  target_link_directories(cryptoXL PRIVATE ${CMAKE_SOURCE_DIR}/src/external/xll/xll)		
endif()

#Turn off linker warnings for missing debug symbol files from Conan
set_target_properties(cryptoXL PROPERTIES LINK_FLAGS "/ignore:4099")

set_target_properties(cryptoXL PROPERTIES SUFFIX ".xll")
set_target_properties(cryptoXL PROPERTIES VS_DEBUGGER_COMMAND "$(registry:HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\excel.exe)")
set_target_properties(cryptoXL PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS $(OutDir)$(TargetName).xll)

install(TARGETS cryptoXL DESTINATION bin)
