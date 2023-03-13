@echo off
setlocal

:: this .bat file location
set work_dir=%~pd0
set work_dir=%work_dir:~0,-1%

call %work_dir%\setup_env.bat

set /a nJobs = %NUMBER_OF_PROCESSORS% / 2

cmake --build %build_dir% --parallel %nJobs% --config Debug

endlocal
