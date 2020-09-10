@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy dis%1.in dis.in >nul
time <enter
a
time <enter
fc dis%1.out dis.out
pause
del dis.in
del dis.out
goto end
:loop
  for %%i in (0 1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end