@echo off
setlocal
:: this .bat file location
set workDir=%~pd0
set workDir=%workDir:~0,-1%

call %workDir%\setup_env.bat

echo removing %build_dir%
rmdir /s/q %build_dir%

endlocal
