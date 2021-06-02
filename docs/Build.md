# prerequisites
Visual Studio 2019
Conan dependency and package manager `pip install conan`
(optional) Update submodules `git submodule update --init --recursive` or `git pull --recurse-submodules` or `git submodule update --remote --merge`

# Build
Open a x64 Native Tools Command Prompt for VS 2019
mkdir build
cd build
conan install .. -s compiler="Visual Studio" -s compiler.version=16 -sbuild_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=on
cmake --build . --parallel --config Debug

TODO: The xll is not loading directly when debugging in Visual Studio

Done. Automate this manual intervention.. In C:\dev\trading\crypto\cpp\src\external\xll\CMakeLists.txt at the end of the file make sure only add_subdirectory(xll) is there.
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release "-DCMAKE_TOOLCHAIN_FILE=C:\dev\trading\crypto\cpp\src\external\CryptoData\cpp\src\external\vcpkg\scripts\buildsystems\vcpkg.cmake"
ninja
TODO: adding "-DVCPKG_TARGET_TRIPLET=x64-windows-static" to cmake gives a linker error: tbb.lib(tbb_main.obj) : error LNK2005: DllMain already defined in xll.lib(dllmain.cpp.obj)