@echo off
if "%1"=="" goto loop
copy cashier%1.in cashier.in >nul
echo Problem Test
echo Data %1
time<enter
cashier
time<enter
fc cashier.out cashier%1.ans
del cashier.in
del cashier.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end

