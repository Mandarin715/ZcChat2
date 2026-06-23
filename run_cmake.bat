@echo off
set "PATH=C:\Program Files\CMake\bin;%PATH%"
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >/dev/null 2>&1
cd /d "C:\Users\asus\Desktop\code\pet1.0\build2"
cmake "C:\Users\asus\Desktop\code\pet1.0\ZcChat2" -G "NMake Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.5.3/msvc2019_64" -DCMAKE_BUILD_TYPE=Release 2>&1
