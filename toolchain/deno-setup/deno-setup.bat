@echo off
setlocal enabledelayedexpansion

set DENO_DIR=tools
set DENO_BIN=%DENO_DIR%\deno.exe

if not exist "%DENO_DIR%" (
    mkdir "%DENO_DIR%"
)

if exist "%DENO_BIN%" (
    exit /b 0
)

set PLATFORM=pc-windows-msvc

set DENO_VERSION=v2.2.12
set DENO_ZIP=deno-x86_64-%PLATFORM%.zip
set DENO_URL=https://github.com/denoland/deno/releases/download/%DENO_VERSION%/%DENO_ZIP%

powershell -Command "Invoke-WebRequest -Uri %DENO_URL% -OutFile %DENO_DIR%\deno.zip"

powershell -Command "Expand-Archive -Path %DENO_DIR%\deno.zip -DestinationPath %DENO_DIR% -Force"
del "%DENO_DIR%\deno.zip"
@echo on