@echo off
setlocal

set "VS_ROOT=C:\Program Files\Microsoft Visual Studio\18\Community"
set "CMAKE=%VS_ROOT%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
set "NINJA=%VS_ROOT%\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe"
set "VCVARS=%VS_ROOT%\VC\Auxiliary\Build\vcvars64.bat"
set "BUILD_CONFIG=%~1"

if "%BUILD_CONFIG%"=="" set "BUILD_CONFIG=Release"
if /I not "%BUILD_CONFIG%"=="Release" if /I not "%BUILD_CONFIG%"=="Debug" (
    echo ERROR: Configuracion no valida: %BUILD_CONFIG%
    echo Uso: build_windows_portable.cmd [Release^|Debug]
    exit /b 1
)

if not exist "%CMAKE%" (
    echo ERROR: No se encuentra CMake de Visual Studio 2026:
    echo %CMAKE%
    exit /b 1
)

if not exist "%NINJA%" (
    echo ERROR: No se encuentra Ninja de Visual Studio 2026:
    echo %NINJA%
    exit /b 1
)

if not exist "%VCVARS%" (
    echo ERROR: No se encuentra el entorno C++ de Visual Studio 2026:
    echo %VCVARS%
    exit /b 1
)

rem Ninja necesita el prefijo ingles de /showIncludes para filtrar dependencias.
set "VSLANG=1033"

call "%VCVARS%" >nul
if errorlevel 1 exit /b %errorlevel%

set "BUILD_DIR=%~dp0build_windows_ninja_%BUILD_CONFIG%"

"%CMAKE%" -S "%~dp0." -B "%BUILD_DIR%" -G Ninja ^
    -DCMAKE_MAKE_PROGRAM="%NINJA%" ^
    -DCMAKE_BUILD_TYPE="%BUILD_CONFIG%" ^
    -DTARGET_PLATFORM=Windows ^
    -DBUILD_SHARED_LIBS=OFF ^
    -DMSVC_STATIC_RUNTIME=ON ^
    -DBUILD_TESTS=OFF
if errorlevel 1 exit /b %errorlevel%

"%CMAKE%" --build "%BUILD_DIR%" --parallel
exit /b %errorlevel%
