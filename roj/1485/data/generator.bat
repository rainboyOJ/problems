@echo off
if "%1"=="" goto loop
copy generator%1.in generator.in >nul
echo Problem Test
echo Data %1
time<enter
generator
time<enter
fc generator.out generator%1.out
del generator.in
del generator.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
