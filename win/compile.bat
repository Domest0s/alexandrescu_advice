@echo off
setlocal

:: this .bat file location
set workDir=%~pd0
set workDir=%workDir:~0,-1%

call %workDir%\setup_env.bat

set /a nJobs = %NUMBER_OF_PROCESSORS% / 2

cmake --build %build_dir% --parallel %nJobs% --config Debug

endlocal
