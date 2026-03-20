@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64
cd /d "%~dp0"
if exist build rmdir /s /q build
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release "-DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-skse -DVCPKG_OVERLAY_TRIPLETS=cmake
if %errorlevel% neq 0 exit /b %errorlevel%
cmake --build build
