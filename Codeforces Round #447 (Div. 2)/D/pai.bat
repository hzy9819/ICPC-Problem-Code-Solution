@ehco off
:loop
	make.exe
	bf.exe
	cpp.exe
	fc std.out D.out
if not errorlevel 1 goto loop
pause
goto loop