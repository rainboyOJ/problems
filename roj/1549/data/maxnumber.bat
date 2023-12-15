@echo off
if "%1"=="" goto loop
copy maxnumber%1.in maxnumber.in >nul
echo Problem Test
echo Data %1
time<enter
maxnumber.exe
time<enter
fc maxnumber.out maxnumber%1.out
del maxnumber.in
del maxnumber.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8) do call %0 %%i
:end
