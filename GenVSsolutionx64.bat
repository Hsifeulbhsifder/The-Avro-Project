@echo off

echo Generating Visual Studio 64-bit solution

mkdir VS-2013x64
cd VS-2013x64

cmake -G "Visual Studio 12 Win64" ../
echo.
echo.
echo Solution generated in /VS-2013x64
pause
exit