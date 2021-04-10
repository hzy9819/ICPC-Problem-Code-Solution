@echo
:loop
	make.exe
	cpp.exe
	E.exe
fc E.out std.out
if %errorlevel%==0 goto loop
pause