IF DEFINED ANANASENV GOTO MAKE
SET ANANASENV=1
SET BCC=c:\Borland\bcc55
SET ISC="C:\Program Files\Inno Setup 5"
SET QTDIR="c:\qt\3.2.1Noncommercial"
SET QMAKESPEC=win32-borland
SET PATH=%bcc%\bin;%QTDIR%\bin;%QTDIR%\plugins\designer;%ISC%;%PATH%
:MAKE
make -f Makefile.bcc %1
exit
