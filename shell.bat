@echo off

set VCVARSALL_NAME=vcvarsall.bat
set VCVARSALL_PATH=null
set NOT_FOUND_STRING=Searched in ^"C:\Program Files^" and ^"C:\Program Files ^(x86^)^" but could not find %VCVARSALL_NAME%

if defined DevEnvDir (
    @echo Environment already set up!
    goto :end
) else (
    
    for /R "C:\Program Files\Microsoft Visual Studio\" %%f in (*) do (
        if %%~nxf==%VCVARSALL_NAME% (
            set VCVARSALL_PATH=%%f
            goto :foundvc
        )
    )
    
    for /R "C:\Program Files (x86)\Microsoft Visual Studio\" %%f in (*) do (
        if %%~nxf==%VCVARSALL_NAME% (
            set VCVARSALL_PATH=%%f
            goto :foundvc
        )
    )

    if "%VCVARSALL_PATH%"=="null" (
        @echo %NOT_FOUND_STRING%
        goto :end
    )
)


:foundvc
call "%VCVARSALL_PATH%" x64

:end
