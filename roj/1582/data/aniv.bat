@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy aniv%1.in aniv.in >nul
time <enter
aniv
time <enter
fc aniv%1.out aniv.out
pause
del aniv.in
del aniv.out
goto end
:loop
  for %%i in (1 2 3 4 5 6 7 8 9 10 11) do call %0 %%i
:end