@echo off
if "%1"=="" goto loop
copy fish%1.in fish.in >nul
echo Problem Test
echo Data %1
time<enter
fish
time<enter
fc fish.out fish%1.out
del fish.in
del fish.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
