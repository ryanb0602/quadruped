@echo off
setlocal enabledelayedexpansion

:: Create the flattened directory if it doesn't exist
if not exist "C:\Users\Ryan Berube\Documents\Quadruped\simulate\__TEMP_BUILD_DIR" (
    mkdir "C:\Users\Ryan Berube\Documents\Quadruped\simulate\__TEMP_BUILD_DIR"
)

:: Copy all .cpp and .h files from nested folders to the flattened directory, excluding files with unwanted dependencies
for /r "C:\Users\Ryan Berube\Documents\Quadruped\lib" %%f in (*.cpp *.h) do (
    findstr /C:"#include <Arduino.h>" "%%f" >nul
    if errorlevel 1 (
        copy "%%f" "C:\Users\Ryan Berube\Documents\Quadruped\simulate\__TEMP_BUILD_DIR"
    )
)

:: Compile the necessary files
g++ -I"C:\Users\Ryan Berube\Documents\Quadruped\simulate\__TEMP_BUILD_DIR" -fPIC -shared -m64 -o kinecore.dll "C:\Users\Ryan Berube\Documents\Quadruped\simulate\__TEMP_BUILD_DIR\*.cpp" simlink.cpp

rmdir /s /q "C:\Users\Ryan Berube\Documents\Quadruped\simulate\__TEMP_BUILD_DIR"

endlocal