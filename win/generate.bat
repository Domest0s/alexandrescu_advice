@echo off
setlocal

:: this .bat file location
set workDir=%~pd0
set workDir=%workDir:~0,-1%

@REM echo setting up environment with %workDir%\setup_env.bat
call %workDir%\setup_env.bat

cmake -S %workDir%\%source_dir% -B %workDir%\%build_dir%

endlocal
