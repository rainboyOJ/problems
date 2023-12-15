@echo off
if "%1"=="" goto loop
copy ant%1.in ant.in >nul
echo Problem Test
echo Data %1
time<enter
ant
time<enter
fc ant.out ant%1.out
del ant.in
del ant.out
pause
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8 9) do call %0 %%i
:end
