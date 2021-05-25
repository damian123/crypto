Checkout the code from GitHub using
git clone --recursive <<REPO_URL>>
or 
git submodule add https://github.com/damian123/CryptoData.git cpp/src/external/CryptoData
git submodule add https://github.com/xlladdins/xll.git cpp/src/external/xll
git submodule update --init --recursive
git submodule update --recursive --remote

Open a x64 Native Tools Command Prompt for VS 2019
cd cpp
mkdir build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\dev\trading\crypto\cpp\src\external\CryptoData\cpp\src\external\vcpkg\scripts\buildsystems\vcpkg.cmake