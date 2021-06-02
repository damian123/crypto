Checkout the code from GitHub using
git clone --recursive <<REPO_URL>>
or 
git submodule add https://github.com/damian123/CryptoData.git cpp/src/external/CryptoData
git submodule add https://github.com/xlladdins/xll.git cpp/src/external/xll
git submodule update --init --recursive
git submodule update --recursive --remote
git pull --recurse-submodules

Open a x64 Native Tools Command Prompt for VS 2019
cd cpp
mkdir build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=C:\dev\trading\crypto\cpp\src\external\CryptoData\cpp\src\external\vcpkg\scripts\buildsystems\vcpkg.cmake"
TODO: The xll is not loading directly when debugging in Visual Studio

Relese build using ninja
TODO: Automate this manual intervention.. In C:\dev\trading\crypto\cpp\src\external\xll\CMakeLists.txt at the end of the file make sure only add_subdirectory(xll) is there.
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release "-DCMAKE_TOOLCHAIN_FILE=C:\dev\trading\crypto\cpp\src\external\CryptoData\cpp\src\external\vcpkg\scripts\buildsystems\vcpkg.cmake"
ninja
TODO: adding "-DVCPKG_TARGET_TRIPLET=x64-windows-static" to cmake gives a linker error: tbb.lib(tbb_main.obj) : error LNK2005: DllMain already defined in xll.lib(dllmain.cpp.obj)