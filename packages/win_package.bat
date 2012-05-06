REM Creates the Windows Package for Bwock

REM Variable Names
REM --------------
set PACKAGE_FOLDER=windows\package
set BIN_FOLDER=..\bin


REM Replace previous existing package folder
REM ----------------------------------------
rmdir /S /Q %PACKAGE_FOLDER%
mkdir %PACKAGE_FOLDER%
mkdir %PACKAGE_FOLDER%\licenses
mkdir %PACKAGE_FOLDER%\resources


REM Copy the contents of the Windows folder
REM ---------------------------------------
COPY windows\* %PACKAGE_FOLDER%


REM Copy the licenses folder
REM ------------------------
xcopy /S ..\licenses %PACKAGE_FOLDER%\licenses


REM Add the Bwock license
REM ---------------------
copy ..\COPYING %PACKAGE_FOLDER%\licenses
rename %PACKAGE_FOLDER%\licenses\COPYING bwock.txt


REM Copy the release binary
REM ---------------------------------------
copy %BIN_FOLDER%\Release\*.exe %PACKAGE_FOLDER%


REM Copy the executable's dependencies
REM ----------------------------------
copy %BIN_FOLDER%\IrrKlang.dll %PACKAGE_FOLDER%
copy %BIN_FOLDER%\settings.txt %PACKAGE_FOLDER%


REM Copy the resources 
REM ------------------
xcopy /S %BIN_FOLDER%\resources %PACKAGE_FOLDER%\resources

