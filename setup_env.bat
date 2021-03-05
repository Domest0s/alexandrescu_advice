@echo off

:: run this script to modify environment

call :NORMALIZATION "..\alexandrescu_sorting_build"
set build_dir=%RETVAL%

exit /B

:: ======= FUNCTIONS =======
:NORMALIZATION
  set RETVAL=%~f1
  exit /B
