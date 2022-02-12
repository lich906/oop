@echo off

set PROGRAM_PATH="%~1"

set CUR_TEST_NAME="Empty file"
%PROGRAM_PATH% tests\empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\empty.txt tests\empty.txt
if ERRORLEVEL 1 goto err

echo Test %CUR_TEST_NAME% passed

set CUR_TEST_NAME="Single line file"
%PROGRAM_PATH% tests\single-line.txt %TEMP%\single-line.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\single-line.txt tests\single-line.txt
if ERRORLEVEL 1 goto err

echo Test %CUR_TEST_NAME% passed

set CUR_TEST_NAME="Multiple line file"
%PROGRAM_PATH% tests\multi-line.txt %TEMP%\multi-line.txt
if ERRORLEVEL 1 goto err
fc %TEMP%\multi-line.txt tests\multi-line.txt
if ERRORLEVEL 1 goto err

echo Test %CUR_TEST_NAME% passed

set CUR_TEST_NAME="Non existing input file"
%PROGRAM_PATH% tests\non-existing-input-file.txt %TEMP%\non-existing-input-file.txt > %TEMP%\non-existing-input-file-output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\non-existing-input-file-output.txt tests\non-existing-input-file-expected-output.txt
if ERRORLEVEL 1 goto err

echo Test %CUR_TEST_NAME% passed

set CUR_TEST_NAME="Unwritable output file"
%PROGRAM_PATH% tests\multi-line.txt %PROGRAM_PATH% > %TEMP%\unwritable-output-file-output.txt
if not ERRORLEVEL 1 goto err
fc %TEMP%\unwritable-output-file-output.txt tests\unwritable-output-file-expected-output.txt

echo Test %CUR_TEST_NAME% passed

echo All tests successfully passed
exit 0

:err
echo Test %CUR_TEST_NAME% failed
exit 1
