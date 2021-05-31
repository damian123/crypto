Find missing .dll dependencies by using one of these options

A) Use Depdencies from https://github.com/lucasg/Dependencies and open the .xll file

B) Use process exporer from sysinternals to monitor what files are opened in the Windows system.
Install ``choco install sysinternals`
Run `procexp64`
File -> Run -> "C:\Program Files\Microsoft Office\root\Office16\EXCEL.EXE" D:\dev\trading\crypto\build\cpp\src\adaptors\xll\Debug\cryptoXL.xll /p D:\dev\trading\crypto\build\cpp\src\adaptors\xll\Debug
The filter by process Excel.exe
Load the .xll and see what .dll files can't be found in the result column saying NAME NOT FOUND