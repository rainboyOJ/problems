@echo off
if "%1"=="" goto loop
copy award%1.in award.in >nul
echo Problem Test
echo Data %1
time<enter
award.exe
time<enter
fc award.out award%1.out
del award.in
del award.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end
