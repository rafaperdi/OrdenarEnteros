@echo off
setlocal EnableExtensions DisableDelayedExpansion

set "BUILD_CONFIG=Release"
set "BUILD_NAME=release"
set "BUILD_ARCH=x64"
set "VCVARS_ARCH=x64"
set "BUILD_SHARED=OFF"
set "BUILD_TESTING=OFF"
set "NATIVE_OPTIMIZATION=OFF"
set "USE_VCPKG=AUTO"

:parse_arguments
if "%~1"=="" goto arguments_ready

if /I "%~1"=="Release" (
    set "BUILD_CONFIG=Release"
    set "BUILD_NAME=release"
    shift
    goto parse_arguments
)
if /I "%~1"=="RelWithDebInfo" (
    set "BUILD_CONFIG=RelWithDebInfo"
    set "BUILD_NAME=relwithdebinfo"
    shift
    goto parse_arguments
)
if /I "%~1"=="Debug" (
    set "BUILD_CONFIG=Debug"
    set "BUILD_NAME=debug"
    shift
    goto parse_arguments
)
if /I "%~1"=="x64" (
    set "BUILD_ARCH=x64"
    set "VCVARS_ARCH=x64"
    shift
    goto parse_arguments
)
if /I "%~1"=="x86" (
    set "BUILD_ARCH=x86"
    set "VCVARS_ARCH=x86"
    shift
    goto parse_arguments
)
if /I "%~1"=="arm64" (
    set "BUILD_ARCH=arm64"
    set "VCVARS_ARCH=x64_arm64"
    shift
    goto parse_arguments
)
if /I "%~1"=="--shared" (
    set "BUILD_SHARED=ON"
    shift
    goto parse_arguments
)
if /I "%~1"=="--static" (
    set "BUILD_SHARED=OFF"
    shift
    goto parse_arguments
)
if /I "%~1"=="--tests" (
    set "BUILD_TESTING=ON"
    shift
    goto parse_arguments
)
if /I "%~1"=="--native" (
    set "NATIVE_OPTIMIZATION=ON"
    shift
    goto parse_arguments
)
if /I "%~1"=="--vcpkg" (
    set "USE_VCPKG=ON"
    shift
    goto parse_arguments
)
if /I "%~1"=="--no-vcpkg" (
    set "USE_VCPKG=OFF"
    shift
    goto parse_arguments
)
if /I "%~1"=="--help" goto usage
if /I "%~1"=="-h" goto usage

echo ERROR: argumento no reconocido: %~1
goto usage_error

:arguments_ready
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VS_ROOT="

if defined VSINSTALLDIR if exist "%VSINSTALLDIR%\VC\Auxiliary\Build\vcvarsall.bat" (
    set "VS_ROOT=%VSINSTALLDIR%"
)

if not defined VS_ROOT if exist "%VSWHERE%" (
    for /f "usebackq tokens=*" %%I in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        if not defined VS_ROOT set "VS_ROOT=%%I"
    )
)

if not defined VS_ROOT (
    echo ERROR: no se encontro Visual Studio con las herramientas de C++.
    echo Instala la carga de trabajo "Desarrollo de escritorio con C++".
    exit /b 1
)

set "VCVARS=%VS_ROOT%\VC\Auxiliary\Build\vcvarsall.bat"
if not exist "%VCVARS%" (
    echo ERROR: no se encontro: %VCVARS%
    exit /b 1
)

chcp 65001 >nul
set "VSLANG=1033"
call "%VCVARS%" %VCVARS_ARCH% >nul
if errorlevel 1 exit /b %errorlevel%
rem Ninja necesita el prefijo ingles de /showIncludes para filtrar dependencias.
set "VSLANG=1033"

set "CMAKE_EXE=%VS_ROOT%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
if not exist "%CMAKE_EXE%" set "CMAKE_EXE="
if not defined CMAKE_EXE (
    for /f "delims=" %%I in ('where.exe cmake 2^>nul') do if not defined CMAKE_EXE set "CMAKE_EXE=%%I"
)
if not defined CMAKE_EXE (
    echo ERROR: no se encontro CMake ni en Visual Studio ni en PATH.
    exit /b 1
)
set "CTEST_EXE=%CMAKE_EXE:cmake.exe=ctest.exe%"

set "NINJA_EXE=%VS_ROOT%\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe"
if not exist "%NINJA_EXE%" set "NINJA_EXE="
if not defined NINJA_EXE (
    for /f "delims=" %%I in ('where.exe ninja 2^>nul') do if not defined NINJA_EXE set "NINJA_EXE=%%I"
)

for %%I in ("%CMAKE_EXE%") do set "PATH=%%~dpI;%PATH%"
if defined NINJA_EXE for %%I in ("%NINJA_EXE%") do set "PATH=%%~dpI;%PATH%"

set "VCPKG_ROOT_DETECTED="
if defined VCPKG_ROOT if exist "%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" (
    set "VCPKG_ROOT_DETECTED=%VCPKG_ROOT%"
)
if not defined VCPKG_ROOT_DETECTED if exist "%VS_ROOT%\VC\vcpkg\scripts\buildsystems\vcpkg.cmake" (
    set "VCPKG_ROOT_DETECTED=%VS_ROOT%\VC\vcpkg"
)
if defined VCPKG_ROOT_DETECTED (
    set "VCPKG_ROOT=%VCPKG_ROOT_DETECTED%"
    set "PATH=%VCPKG_ROOT%;%PATH%"
)

if /I "%USE_VCPKG%"=="ON" if not defined VCPKG_ROOT_DETECTED (
    echo ERROR: se solicito vcpkg pero no se encontro un toolchain valido.
    exit /b 1
)

set "USE_VCPKG_TOOLCHAIN=OFF"
if /I "%USE_VCPKG%"=="ON" set "USE_VCPKG_TOOLCHAIN=ON"
if /I "%USE_VCPKG%"=="AUTO" if defined VCPKG_ROOT_DETECTED set "USE_VCPKG_TOOLCHAIN=ON"

set "VCPKG_TRIPLET=%BUILD_ARCH%-windows"
if /I "%BUILD_SHARED%"=="OFF" set "VCPKG_TRIPLET=%BUILD_ARCH%-windows-static"

set "BUILD_DIR=%~dp0out\build\windows-%BUILD_ARCH%-%BUILD_NAME%"
set "GENERATOR=NMake Makefiles"
if defined NINJA_EXE set "GENERATOR=Ninja"

rem El toolchain solo se selecciona durante la primera configuracion. Si ya
rem existe cache, CMake reutiliza el valor guardado y evitamos un warning.
if exist "%BUILD_DIR%\CMakeCache.txt" set "USE_VCPKG_TOOLCHAIN=OFF"

echo.
echo OrdenarEnteros - entorno Windows portable
echo   Visual Studio: %VS_ROOT%
echo   CMake:        %CMAKE_EXE%
if defined NINJA_EXE echo   Ninja:        %NINJA_EXE%
if defined VCPKG_ROOT_DETECTED echo   vcpkg:       %VCPKG_ROOT_DETECTED%
echo   Generador:    %GENERATOR%
echo   Configuracion:%BUILD_CONFIG%
echo   Arquitectura: %BUILD_ARCH%
echo   Build:         %BUILD_DIR%
echo.

if /I "%USE_VCPKG_TOOLCHAIN%"=="ON" (
    "%CMAKE_EXE%" -S "%~dp0." -B "%BUILD_DIR%" -G "%GENERATOR%" ^
        "-DCMAKE_BUILD_TYPE=%BUILD_CONFIG%" ^
        "-DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT_DETECTED%\scripts\buildsystems\vcpkg.cmake" ^
        "-DVCPKG_TARGET_TRIPLET=%VCPKG_TRIPLET%" ^
        "-DBUILD_SHARED_LIBS=%BUILD_SHARED%" ^
        "-DBUILD_TESTING=%BUILD_TESTING%" ^
        "-DMSVC_STATIC_RUNTIME=ON" ^
        "-DORDENARENT_NATIVE_OPTIMIZATION=%NATIVE_OPTIMIZATION%"
) else (
    "%CMAKE_EXE%" -S "%~dp0." -B "%BUILD_DIR%" -G "%GENERATOR%" ^
        "-DCMAKE_BUILD_TYPE=%BUILD_CONFIG%" ^
        "-DBUILD_SHARED_LIBS=%BUILD_SHARED%" ^
        "-DBUILD_TESTING=%BUILD_TESTING%" ^
        "-DMSVC_STATIC_RUNTIME=ON" ^
        "-DORDENARENT_NATIVE_OPTIMIZATION=%NATIVE_OPTIMIZATION%"
)
if errorlevel 1 exit /b %errorlevel%

"%CMAKE_EXE%" --build "%BUILD_DIR%" --parallel
if errorlevel 1 exit /b %errorlevel%

if /I "%BUILD_TESTING%"=="ON" (
    "%CTEST_EXE%" --test-dir "%BUILD_DIR%" --output-on-failure
    if errorlevel 1 exit /b %errorlevel%
)

echo.
echo Compilacion completada:
echo   %BUILD_DIR%\bin\OrdenarEnteros.exe
exit /b 0

:usage
echo Uso:
echo   build_windows_portable.cmd [Release^|RelWithDebInfo^|Debug] [x64^|x86^|arm64] [opciones]
echo.
echo Opciones:
echo   --static       Biblioteca estatica (predeterminado)
echo   --shared       Biblioteca DLL
echo   --tests        Compilar y ejecutar tests
echo   --native       Optimizar para la CPU local; el binario sera menos portable
echo   --vcpkg        Exigir el toolchain de vcpkg
echo   --no-vcpkg     No usar vcpkg
echo   --help         Mostrar esta ayuda
exit /b 0

:usage_error
call :usage
exit /b 1
