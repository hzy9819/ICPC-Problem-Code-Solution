@echo
:loop
	make.exe
	A.exe
	cpp.exe
fc std.out A.out
if not errorlevel1 goto loop
pause