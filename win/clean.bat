@echo off
setlocal

:: this .bat file location
set work_dir=%~pd0
set work_dir=%work_dir:~0,-1%
call %work_dir%\setup_env.bat

@REM remove build directory
if EXIST %build_dir% (
    echo removing build directory %build_dir% ...
    rmdir /s/q %build_dir%
) ELSE (
    echo build directory %build_dir% does not exist.
)

@REM removing installation directory
if EXIST %install_dir% (
    echo removing install directory %install_dir% ...
    rmdir /s/q %install_dir%
) ELSE (
    echo install directory %install_dir% does not exist.
)

endlocal
