# prerequisites
Visual Studio 2019
Conan dependency and package manager `pip install conan`
(optional) Update submodules `git submodule update --init --recursive` or `git pull --recurse-submodules` or `git submodule update --remote --merge`

# Build
Open a x64 Native Tools Command Prompt for VS 2019
mkdir build
cd build
conan install .. -s compiler="Visual Studio" -s compiler.version=16 -sbuild_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS_CRYPTO=on
cmake --build . --parallel --config Debug

# Test
`cd build\bin\bin`
`ctest`

# Running
If the tests or Excel addin fails to load it might be because it can't find the dependent dll shared libraries. 
To fix this add the path to the missing libraries before loading. 
`set PATH=D:\dev\trading\crypto\build\bin;%PATH%`
"C:\Program Files\Microsoft Office\root\Office16\EXCEL.EXE" cryptoXL.xll

# Debugging
In a command prompt
`set PATH=D:\dev\trading\crypto\build\bin;%PATH%`
`"C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\Common7\IDE\devenv.exe"`

TODO: The xll is not loading directly when debugging in Visual Studio

# Install 
cmake --install . --prefix install

Conan already copied the dependent .dlls to the install directory.
