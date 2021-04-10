@echo
:loop
	make.exe
	code.exe
	bf.exe
	fc B.out bf.out
if not errorlevel 1 goto loop
pause
goto loop