@ehco off
:loop
	make.exe
	cpp.exe
	bf.exe
	fc E.out std.out
if not errorlevel 1 goto loop
pause
goto loop