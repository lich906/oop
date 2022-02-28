@echo off

set PROGRAM_PATH="%~1"

rem Неверное количество параметров
%PROGRAM_PATH% tests\12312312345.txt %TEMP%\out.txt > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\invalid-args.expect.txt
if ERRORLEVEL 1 goto err

%PROGRAM_PATH% tests\12312312345.txt %TEMP%\out.txt 8573 23 593 3 > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\invalid-args.expect.txt
if ERRORLEVEL 1 goto err

rem Несуществующий входной файл
%PROGRAM_PATH% tests\cba.txt %TEMP%\out.txt 1 2 > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\bad-input-file.expect.txt
if ERRORLEVEL 1 goto err

rem Исполняемая программа в качестве выходного файла
%PROGRAM_PATH% tests\brown-fox.txt %PROGRAM_PATH% fox dog > %TEMP%\out.txt
if NOT ERRORLEVEL 1 goto err
fc %TEMP%\out.txt tests\bad-output-file.expect.txt
if ERRORLEVEL 1 goto err

rem Пустая строка поиска
%PROGRAM_PATH% tests\brown-fox.txt %TEMP%\empty-search-string.txt "" hello
if ERRORLEVEL 1 goto err
fc %TEMP%\empty-search-string.txt tests\brown-fox.txt
if ERRORLEVEL 1 goto err

rem Замена "ma" на "mama"
%PROGRAM_PATH% tests\mama.txt %TEMP%\mama.txt ma mama
if ERRORLEVEL 1 goto err
fc %TEMP%\mama.txt tests\mama.expect.txt
if ERRORLEVEL 1 goto err

rem Замена подстроки "1231234" в строке "12312312345"
%PROGRAM_PATH% tests\12312312345.txt %TEMP%\12312312345.txt 1231234 "works fine"
if ERRORLEVEL 1 goto err
fc %TEMP%\12312312345.txt tests\12312312345.expect.txt
if ERRORLEVEL 1 goto err

rem Замена "dog" на "cat" в панграмме.
%PROGRAM_PATH% tests\brown-fox.txt %TEMP%\brown-fox.txt dog cat
if ERRORLEVEL 1 goto err
fc %TEMP%\brown-fox.txt tests\brown-fox.expect.txt
if ERRORLEVEL 1 goto err

%PROGRAM_PATH% tests\input.txt %TEMP%\output.txt a bb
if ERRORLEVEL 1 goto err

echo All tests successfully passed!
exit 0

:err
echo Testing failed
exit 1
