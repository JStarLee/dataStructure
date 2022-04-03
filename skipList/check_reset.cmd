@echo off
for /l %%i  in  (0,1,9) do (
    echo Check_reset input_%%i.txt ...
    .\code\skipList.exe .\data\input\input_%%i.txt .\check\check.txt -C>nul 2>nul
    .\code\skipList.exe .\data\input\input_%%i.txt .\check\check_reset.txt -CE >nul 2>nul
    echo without reset
    type .\check\check.txt
    echo .
    echo reset
    type .\check\check_reset.txt
    echo .
)
@echo Check_reset input_9.txt ...
.\code\skipList.exe .\data\input\input_9.txt .\check\check.txt -C>nul 2>nul
.\code\skipList.exe .\data\input\input_9.txt .\check\check_reset.txt -CE >nul 2>nul
echo without reset
type .\check\check.txt
echo .
echo reset
type .\check\check_reset.txt