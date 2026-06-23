@echo off
set LOGFILE=C:\Users\asus\Desktop\code\pet1.0\build_log.txt
echo ===== Build started at %date% %time% ===== > %LOGFILE%
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >> %LOGFILE% 2>&1
echo VCVARS completed >> %LOGFILE%
cd /d C:\Users\asus\Desktop\code\pet1.0 >> %LOGFILE% 2>&1
if not exist build mkdir build
cd build
echo Running CMake configure... >> %LOGFILE%
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:/Qt/6.5.3/msvc2019_64 >> %LOGFILE% 2>&1
echo CMake configure exit code: %ERRORLEVEL% >> %LOGFILE%
echo Running CMake build... >> %LOGFILE%
cmake --build . --config Release >> %LOGFILE% 2>&1
echo CMake build exit code: %ERRORLEVEL% >> %LOGFILE%
echo ===== Build finished at %date% %time% ===== >> %LOGFILE%
