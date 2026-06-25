@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
cd /d "C:\Users\asus\Desktop\code\pet1.0\build2"
cmake ..\Mandarin -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=C:/Qt/6.6.3/msvc2019_64
cmake --build .
