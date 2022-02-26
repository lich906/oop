@echo off

set PROGRAM_PATH="%~1"

rem Неверное количество входных параметров
%PROGRAM_PATH% abcd xyz 04 > %TEMP%\output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\output.txt tests\invalid-arg-count.expect.txt
if ERRORLEVEL 1 goto err

rem Недопустимая операция
%PROGRAM_PATH% abcd tests\test-binary.jpeg %TEMP%\crypted.bin 35 > %TEMP%\output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\output.txt tests\unknown-operation.expect.txt
if ERRORLEVEL 1 goto err

rem Несуществующий входной файл
%PROGRAM_PATH% crypt tests\test.jpeg %TEMP%\crypted.bin 35 > %TEMP%\output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\output.txt tests\non-existing-input-file.expect.txt
if ERRORLEVEL 1 goto err

rem Входной и выходной файлы совпадают
%PROGRAM_PATH% crypt tests\test-binary.jpeg tests\test-binary.jpeg 35 > %TEMP%\output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\output.txt tests\input-output-files-match.expect.txt
if ERRORLEVEL 1 goto err

rem Некорректный ключ (с нецифровыми символами)
%PROGRAM_PATH% crypt tests\test-binary.jpeg %TEMP%\crypted.bin 35ghdfg > %TEMP%\output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\output.txt tests\invalid-crypt-key.expect.txt
if ERRORLEVEL 1 goto err

rem Некорректный ключ (число не помещается в байт)
%PROGRAM_PATH% crypt tests\test-binary.jpeg %TEMP%\crypted.bin 35945 > %TEMP%\output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\output.txt tests\invalid-crypt-key.expect.txt
if ERRORLEVEL 1 goto err

rem   Шифруем исходный файл с ключем 45 => полученный файл шифруем ключем 234 => 
rem   => дешифруем ключем 234 => дешифруем ключем 45 => получаем исходный файл
%PROGRAM_PATH% crypt tests\test-binary.jpeg %TEMP%\crypted1.bin 45
if ERRORLEVEL 1 goto err
%PROGRAM_PATH% crypt %TEMP%\crypted1.bin %TEMP%\crypted2.bin 234
if ERRORLEVEL 1 goto err
%PROGRAM_PATH% decrypt %TEMP%\crypted2.bin %TEMP%\decrypted2.bin 234
if ERRORLEVEL 1 goto err
%PROGRAM_PATH% decrypt %TEMP%\decrypted2.bin %TEMP%\decrypted1.bin 45
if ERRORLEVEL 1 goto err
fc tests\test-binary.jpeg %TEMP%\decrypted1.bin
if ERRORLEVEL 1 goto err

echo All tests successfully passed
exit 0

:err
echo Testing failed
exit 1
