@echo off

set BATCH_FILE_DIR=%~dp0
mkdir %BATCH_FILE_DIR%\..\build
pushd %BATCH_FILE_DIR%\..\build

set COMPILER_FLAGS=-nologo -Zi -Od
set LINKER_FLAGS=-incremental:no user32.lib
cl %COMPILER_FLAGS% ..\src\main.c /link %LINKER_FLAGS%

popd