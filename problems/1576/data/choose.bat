@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy choose%1.in choose.in >nul
time <enter
choose
time <enter
fc choose%1.out choose.out
pause
del choose.in
del choose.out
goto end
:loop
  for %%i in (0 1 2 3 4 5) do call %0 %%i
:end