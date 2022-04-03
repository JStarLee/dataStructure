@echo off
echo Show my skipList
set flag=0
for /l %%i  in  (1,1,3) do (
    .\code\skipList.exe .\show\input\input_%%i.txt .\show\output\output_%%i.txt -S >nul 2>nul
    echo show %%i
)
echo down.