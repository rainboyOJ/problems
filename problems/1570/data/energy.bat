@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy energy%1.in energy.in >nul
time <enter
energy
time <enter
fc energy%1.ans energy.out
pause
del energy.in
del energy.out
goto end
:loop
  for %%i in (0 1 2 3 4 5 6 7 8 9) do call %0 %%i
:end