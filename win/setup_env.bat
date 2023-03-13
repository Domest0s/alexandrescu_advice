@echo off
:: run this script to modifies environment

:: this .bat file location
set work_dir=%~pd0
set work_dir=%work_dir:~0,-1%

call :NORMALIZATION ".."
set root_dir=%RETVAL%


set source_dir=%root_dir%
set build_dir=%root_dir%\build
set install_dir=%root_dir%\install




:: ======= FUNCTIONS =======

exit /B

:NORMALIZATION
  set RETVAL=%~f1
  exit /B

:: an example of using NORMALIZATION function
@REM call :NORMALIZATION "..\alexandrescu_sorting_build"
@REM set build_dir=%RETVAL%
