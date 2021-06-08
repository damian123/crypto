@echo off
if not exist build mkdir build
cd build
conan install .. -s compiler="Visual Studio" -s compiler.version=16 -sbuild_type=Release
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS_CRYPTO=on
cmake --build . --parallel --config Release
