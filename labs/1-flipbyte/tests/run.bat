@echo off

set PROGRAM_PATH="%~1"
set check_err=if ERRORLEVEL 1 goto err

%PROGRAM_PATH% 345 34 23 h4 > %TEMP%\test1.txt
fc %TEMP%\test1.txt tests\invalid-arguments-count.txt
%check_err%

%PROGRAM_PATH% > %TEMP%\test2.txt
fc %TEMP%\test2.txt tests\invalid-arguments-count.txt
%check_err%

%PROGRAM_PATH% 345 > %TEMP%\test3.txt
fc %TEMP%\test3.txt tests\out-of-range.txt
%check_err%

%PROGRAM_PATH% 0000000000000082375 > %TEMP%\test4.txt
fc %TEMP%\test4.txt tests\out-of-range.txt
%check_err%

%PROGRAM_PATH% 95gje4 > %TEMP%\test5.txt
fc %TEMP%\test5.txt tests\not-a-number.txt
%check_err%

%PROGRAM_PATH% 000000000000000000000000000000094fj34f > %TEMP%\test6.txt
fc %TEMP%\test6.txt tests\not-a-number.txt
%check_err%

%PROGRAM_PATH% 230 > %TEMP%\test7.txt
%check_err%
fc %TEMP%\test7.txt tests\230.txt
%check_err%

%PROGRAM_PATH% 0000056 > %TEMP%\test8.txt
%check_err%
fc %TEMP%\test8.txt tests\0000056.txt
%check_err%

%PROGRAM_PATH% 123 > %TEMP%\test9.txt
%check_err%
fc %TEMP%\test9.txt tests\123.txt
%check_err%

%PROGRAM_PATH% 0 > %TEMP%\test10.txt
%check_err%
fc %TEMP%\test10.txt tests\0.txt
%check_err%

%PROGRAM_PATH% 255 > %TEMP%\test11.txt
%check_err%
fc %TEMP%\test11.txt tests\255.txt
%check_err%

%PROGRAM_PATH% 129 > %TEMP%\test12.txt
%check_err%
fc %TEMP%\test12.txt tests\129.txt
%check_err%

echo All tests successfully passed!
exit 0

:err
echo Testing failed
exit 1
