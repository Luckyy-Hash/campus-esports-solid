@echo off
echo ========================================================
echo Campus Esports Tournament Registration System - Build
echo Student: P. Latheesh Reddy (23BCE0329)
echo Course:  BCSE102L - Structured and Object-Oriented Programming
echo ========================================================
echo.

echo Compiling Modular C++ Project with g++...
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src\EmailNotification.cpp src\SMSNotification.cpp src\SoloRegistration.cpp src\SquadRegistration.cpp src\RegistrationManager.cpp -o campus_esports.exe

if %ERRORLEVEL% equ 0 (
    echo [SUCCESS] Compilation finished successfully!
    echo Binary generated: campus_esports.exe
    echo.
    echo Running Campus Esports Registration System:
    echo ----------------------------------------------------
    campus_esports.exe
    echo ----------------------------------------------------
) else (
    echo [ERROR] Compilation failed.
)

