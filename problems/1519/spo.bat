@echo off
if "%1"=="" goto loop
copy spo%1.in spo.in >nul
echo Problem Test
echo Data %1
time<enter
spo
time<enter
spo_chk spo.in spo.out spo%1.out > res.txt
type res.txt
del spo.in
del spo.out
del res.txt
pause
goto end
:loop
for %%i in (0 1 2 3 4 5 6 7 8 9 10 11 12 13) do call %0 %%i
:end
