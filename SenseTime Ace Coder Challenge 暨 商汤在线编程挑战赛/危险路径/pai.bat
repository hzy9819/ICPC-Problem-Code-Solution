@echo off
:loop
	code.exe
	cpp.exe
	std.exe
fc std.out G.out
if not errorlevel 1 goto loop
pause
goto loop