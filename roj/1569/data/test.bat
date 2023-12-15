@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy merge%1.in merge.in >nul
time <enter
merge
time <enter
fc merge%1.out merge.out
pause
del merge.in
del merge.out
goto end
:loop
  for %%i in (0 1 2 3 4 5 6 7 8 9) do call %0 %%i
:end