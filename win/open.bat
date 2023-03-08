@echo off
setlocal

:: this .bat file location
set workDir=%~pd0
set workDir=%workDir:~0,-1%

call %workDir%\setup_env.bat

cmake --open %workDir%\%build_dir%

endlocal
