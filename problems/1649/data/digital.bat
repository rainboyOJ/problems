@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy digital%1.in digital.in >nul
time <enter
digital
time <enter
fc digital%1.ans digital.out
pause
del digital.in
del digital.out
goto end
:loop
  for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end