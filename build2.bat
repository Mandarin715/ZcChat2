@echo off
set "LOGFILE=C:\Users\asus\Desktop\code\pet1.0\build_result.txt"
echo ===== CMake Configure ===== > "%LOGFILE%"
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >/dev/null 2>&1
cd /d "C:\Users\asus\Desktop\code\pet1.0"
if not exist build2 mkdir build2
cd build2
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:/Qt/6.5.3/msvc2019_64 >> "%LOGFILE%" 2>&1
echo ===== CMake Build ===== >> "%LOGFILE%"
cmake --build . --config Release >> "%LOGFILE%" 2>&1
echo ===== Done ===== >> "%LOGFILE%"
