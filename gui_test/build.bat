@echo off
setlocal
cd /d "%~dp0"

set "VCVARS=C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" (
  echo Could not find vcvars64.bat
  exit /b 1
)

call "%VCVARS%" >nul

if not exist "bin" mkdir bin

cl /nologo /EHsc /O2 /std:c++17 /DUNICODE /D_UNICODE /DWIN32_LEAN_AND_MEAN ^
  /I"..\imgui" /I"..\inc" /I"." ^
  main.cpp ^
  ..\imgui\imgui.cpp ^
  ..\imgui\imgui_draw.cpp ^
  ..\imgui\imgui_tables.cpp ^
  ..\imgui\imgui_widgets.cpp ^
  ..\imgui\imgui_impl_win32.cpp ^
  ..\imgui\imgui_impl_dx11.cpp ^
  /Fe:bin\GuiStyleTest.exe /Fo:bin\ ^
  /link /SUBSYSTEM:WINDOWS d3d11.lib dxgi.lib user32.lib gdi32.lib shell32.lib xinput.lib

if errorlevel 1 (
  echo Build failed.
  exit /b 1
)

echo.
echo Built: gui_test\bin\GuiStyleTest.exe
start "" "bin\GuiStyleTest.exe"
endlocal
