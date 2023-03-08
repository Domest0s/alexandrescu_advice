@echo off

:: run this script to modify environment

set source_dir=.
set build_dir=build
set install_dir=install

:: an example of using NORMALIZATION function
@REM call :NORMALIZATION "..\alexandrescu_sorting_build"
@REM set build_dir=%RETVAL%

exit /B

:: ======= FUNCTIONS =======
:NORMALIZATION
  set RETVAL=%~f1
  exit /B
