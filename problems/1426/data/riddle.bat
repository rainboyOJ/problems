@echo off
if "%1"=="" goto loop
copy riddle%1.in riddle.in >nul
echo Problem Test
echo Data %1
time<enter
riddle
time<enter
fc riddle.out riddle%1.out
del riddle.in
del riddle.out
pause
goto end
:loop
for %%i in (1 2 3 4 5) do call %0 %%i
:end
