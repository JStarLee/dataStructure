@echo off
echo Test my skipList
setlocal EnableDelayedExpansion
rm .\log\cmd.log
set flag=0
for /l %%i  in  (0,1,9) do (
    @echo test input_%%i.txt ...
    rm .\myOutput\output_%%i.txt
    .\code\skipList.exe .\data\input\input_%%i.txt .\myOutput\output_%%i.txt>nul 2>nul
    fc ".\myOutput\output_%%i.txt" ".\data\output\output_%%i.txt" >> .\log\cmd.log
    if !errorlevel!==0 (
        echo Passed.
    ) else (
        echo False.
        set flag=1
    )
)
if %flag% == 0 (
    echo ---------------------------------
    echo Congradulations.All Passed.
) else (
    echo ---------------------------------
    echo There are something wrong.Come on.
)