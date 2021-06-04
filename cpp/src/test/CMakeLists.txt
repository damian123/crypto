include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add test cpp file
add_executable(crypto_test
    main.cpp
    #staticdata/testsecurities.cpp
    marketdata/testStreamingMarketData.cpp
)

target_include_directories(crypto_test PRIVATE 
  securities streaming
  ${CMAKE_SOURCE_DIR}/cpp/src/external/xll 
  ${CMAKE_SOURCE_DIR}/cpp/src/external/CryptoData/cpp/src/marketdata
  ${CMAKE_SOURCE_DIR}/cpp/src/external/CryptoData/cpp/src/feed/exchange/FTX
  ${CMAKE_SOURCE_DIR}/cpp/src/external/CryptoData/cpp/src/external
  ${CMAKE_SOURCE_DIR}/cpp/src/external/CryptoData/cpp/src/external/websocketpp)

target_link_libraries(crypto_test PRIVATE 
  securities
  streaming
  ws
  rest
  ${CONAN_LIBS})

set_target_properties(crypto_test PROPERTIES LINK_FLAGS "/ignore:4099")

#add_test(
#    NAME crypto_test
#    COMMAND crypto_test
#)

