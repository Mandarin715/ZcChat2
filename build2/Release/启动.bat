@echo off
title ZcChat2 Launcher
cd /d "%~dp0"

echo ========================================
echo    Mandarin v1.5 - One Click Start
echo ========================================
echo.

if not exist "vits-simple-api\py310\python.exe" (
    echo [INFO] Voice service not found, text-only mode.
    echo Download voice pack:
    echo   https://github.com/Artrajz/vits-simple-api/releases
    echo.
    echo Starting Mandarin...
    start "" "Mandarin.exe"
    pause
    exit
)

echo [1/2] Starting voice service...
cd vits-simple-api
start "VITS" /MIN py310\python.exe app.py
cd ..

echo [2/2] Waiting for voice service...
:wait
timeout /t 3 /nobreak >nul
curl -s http://127.0.0.1:23456/voice/speakers >nul 2>&1
if errorlevel 1 goto wait

echo Starting Mandarin!
start "" "Mandarin.exe"

echo Mandarin closed. Stopping voice service...
taskkill /fi "WINDOWTITLE eq VITS" /f >nul 2>&1
pause
exit
