@echo off

set Password=%1
set CertName=%2

rem set SETUP_FOLDER=%~dp0
rem cd %SETUP_FOLDER%

CertUtil -f -p %Password% -importpfx %CertName%

pause 