@echo off
if "%1"=="" goto loop
copy pie%1.in pie.in>nul
echo pie TEST
echo Data %1
time<enter
pie
time<enter
copy pie.out pie%1.out
pause
del pie.in
del pie.out
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8) do call %0 %%i
:end
