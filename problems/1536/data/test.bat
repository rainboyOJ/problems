@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy stars%1.in stars.in >nul
time <enter
stars
time <enter
fc stars%1.out stars.out
pause
del stars.in
del stars.out
goto end
:loop
  for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end