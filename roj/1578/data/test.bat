@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy strategi%1.in strategi.in >nul
time <enter
strategi
time <enter
fc strategi%1.out strategi.out
pause
del strategi.in
del strategi.out
goto end
:loop
  for %%i in (1 2 3 4 5) do call %0 %%i
:end