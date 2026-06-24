@echo off
title Mandarin Launcher
cd /d "%~dp0"
echo ========================================
echo    Mandarin - One Click Start
echo ========================================
echo.

:: 自动查找 vits-simple-api 目录（适配任意版本号）
set "VITS_DIR="
for /d %%d in ("vits-simple-api*") do (
    if exist "%%d\py310\python.exe" (
        set "VITS_DIR=%%d"
    )
)
if "%VITS_DIR%"=="" (
    for /d %%d in ("..\vits-simple-api*") do (
        if exist "%%d\py310\python.exe" (
            set "VITS_DIR=%%d"
        )
    )
)

if "%VITS_DIR%"=="" (
    echo [INFO] Voice service not found, text-only mode.
    echo        To enable voice: download vits-simple-api and extract to this folder.
    echo.
    start "" "Mandarin.exe"
    pause
    exit
)

echo [INFO] Voice service found: %VITS_DIR%
echo [INFO] Starting voice service...
start "VITS" /MIN "%VITS_DIR%\py310\python.exe" "%VITS_DIR%\app.py"
echo [INFO] Starting Mandarin...
start "" "Mandarin.exe"
echo [INFO] All done! Voice service warming up in background.
pause
exit
