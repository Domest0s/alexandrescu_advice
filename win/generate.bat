@echo off
setlocal

:: this .bat file location
set work_dir=%~pd0
set work_dir=%work_dir:~0,-1%

@REM echo setting up environment with %work_dir%\setup_env.bat
call %work_dir%\setup_env.bat

cmake -S %source_dir% -B %build_dir%

endlocal
