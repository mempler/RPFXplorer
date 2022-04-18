@echo off

call :isAdmin

if %errorlevel% == 0 (
  goto :run
) else (
  echo Requesting administrative privileges...
  goto :UACPrompt
)

:isAdmin
  fsutil dirty query %systemdrive% >nul
exit /b

:run
  taskkill /F /IM "explorer.exe"

  cd %~1

  cd bin\Debug
    regsvr32 /s "RPFXplorer.Win64.dll"
  cd ..\..
  
  start explorer.exe
  exit
exit /b

:UACPrompt
  echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
  echo UAC.ShellExecute "cmd.exe", "/c %~s0 %~1 %cd%", "", "runas", 1 >> "%temp%\getadmin.vbs"
  
  "%temp%\getadmin.vbs"
  del "%temp%\getadmin.vbs"
exit /B`
