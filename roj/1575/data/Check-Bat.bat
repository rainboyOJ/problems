@echo off
if "%1"=="" goto loop
copy apple%1.in apple.in >nul
echo �������������ɹ��� CB(Check-Bat)
echo Data %1
time<enter
apple.exe
time<enter
fc apple.out apple%1.out
pause
goto end
:loop
for %%i in (1 2 3 4 5 6 7 8 9 10 11 12 13) do call %0 %%i
:end
del apple.in
del apple.out

@Rem Stein 2007 10-17 ���������������ɹ��� CB(Check-Bat)����
@Rem QQ:383025560 Email:AdStein@126.com �˲���һ�� ������