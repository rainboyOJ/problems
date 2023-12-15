@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy interval%1.in interval.in >nul
time <enter
interval
time <enter
fc interval%1.out interval.out
pause
del interval.in
del interval.out
goto end
:loop
  for %%i in (1 2 3 4 5) do call %0 %%i
:end