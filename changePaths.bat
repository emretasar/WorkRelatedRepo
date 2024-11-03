@echo off
setlocal enabledelayedexpansion

REM Check if a filename is provided
if "%~1"=="" (
    echo Please provide a JSON file as an argument.
    exit /b 1
)

set "inputFile=%~1"
set "tempFile=%temp%\tempfile.json"

REM Check if the input file exists
if not exist "%inputFile%" (
    echo File "%inputFile%" not found.
    exit /b 1
)

REM Create a temporary file with modified content
(for /f "usebackq delims=" %%A in ("%inputFile%") do (
    set "line=%%A"
    REM Replace /c/ with C:/
    set "line=!line:/c/=C:/!"
    REM Replace /d/ with D:/
    set "line=!line:/d/=D:/!"
    REM Replace -I/D: with -ID:
    set "line=!line:-I/D:=-ID:!"
    REM Replace -I/C: with -IC:
    set "line=!line:-I/C:=-IC:!"
    echo !line!
)) > "%tempFile%"

REM Replace original file with modified content
move /Y "%tempFile%" "%inputFile%" > nul

echo Path replacements complete for "%inputFile%".
endlocal
