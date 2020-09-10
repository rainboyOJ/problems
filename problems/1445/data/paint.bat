@echo off
if "%1"=="" goto loop
copy paint%1.in paint.in >nul
echo Problem Test
echo Data %1
time<enter
paint
time<enter
fc paint.out paint%1.out
del paint.in
del paint.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8) do call %0 %%i
:end
