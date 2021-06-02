add_library(cryptoXL SHARED   
  TickStream.cpp)

target_compile_definitions (cryptoXL PUBLIC UNICODE)
target_compile_definitions (cryptoXL PUBLIC _UNICODE)

target_include_directories(cryptoXL PRIVATE 
  xll 
  ${CMAKE_SOURCE_DIR}/cpp/src/external/xll 
  ${CMAKE_SOURCE_DIR}/cpp/src/external/CryptoData/cpp/src/marketdata
  ${CMAKE_SOURCE_DIR}/cpp/src/external/CryptoData/cpp/src/feed/exchange/FTX
  ${CMAKE_SOURCE_DIR}/cpp/src/external/CryptoData/cpp/src/external)

target_link_libraries(cryptoXL 
  xll 
  XLCALL32 
  streaming
  ${Boost_LIBRARIES} 
  ${OPENSSL_LIBRARIES} 
  TBB::tbb 
  fmt::fmt)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	target_link_directories(cryptoXL PRIVATE ${CMAKE_SOURCE_DIR}/cpp/src/external/xll/xll/x64)
else()
	target_link_directories(cryptoXL PRIVATE ${CMAKE_SOURCE_DIR}/cpp/src/external/xll/xll)		
endif()
set_target_properties(cryptoXL PROPERTIES SUFFIX ".xll")
set_target_properties(cryptoXL PROPERTIES VS_DEBUGGER_COMMAND "$(registry:HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\excel.exe)")
set_target_properties(cryptoXL PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS $(OutDir)$(TargetName).xll)
