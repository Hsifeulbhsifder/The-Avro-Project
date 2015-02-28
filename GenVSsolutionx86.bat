@echo off

echo Generating Visual Studio 32-bit solution

mkdir VS-2013x86
cd VS-2013x86

cmake -G "Visual Studio 12" ../
echo.
echo.
echo Solution generated in /VS-2013x86
pause
exit