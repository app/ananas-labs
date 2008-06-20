IF DEFINED ANANASENV GOTO MAKE
SET ANANASENV=1
SET ISC="C:\Program Files\Inno Setup 4"
rem SET QTDIR="c:\qt\3.3.4"
SET QMAKESPEC=win32-borland
SET PATH=%QTDIR%\bin;%QTDIR%\plugins\designer;%ISC%;%PATH%
:MAKE
make -f Makefile.bcc %1
exit
