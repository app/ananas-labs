#!/usr/bin/perl
#-----------------------------------------------------------------------------#
# $Id: gui-design-new-bs.pl,v 1.3 2006/02/07 08:30:38 app Exp $
# This test creates new empty business scheme open it in Ananas.Designer 
# and leavs Ananas.Designer window opened.
#-----------------------------------------------------------------------------#
# Copyright (c) Andrey Paskal <app at lrn dot ru>, Yoshkar-Ola, 2005
#
# This file is part of the Ananas Project -
# automation accounting system.
#
# This file may be distributed and/or modified under the terms of the
# GNU General Public License version 2 as published by the Free Software
# Foundation and appearing in the file LICENSE.GPL included in the
# packaging of this file.
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#

## Pragmas/Directives/Diagnostics ##
use strict;
use warnings;
use POSIX qw(strftime);

## Imports (use [MODULE] qw/[IMPORTLIST]/;) ##
use X11::GUITest qw/
	StartApp
	FindWindowLike
	WaitWindowClose
	WaitWindowViewable
	SendKeys
	SetEventSendDelay
/;

## Constants (sub [CONSTANT]() { [VALUE]; }) ##

## Variables (my [SIGIL][VARIABLE] = [INITIALVALUE];) ##
my $MainWin = 0;
my $AlertWin = 0;
my $AboutWin = 0;
my $TestName = 'gui-design-new-bs';
my $LogName = $TestName . '.log';
my $HomeDir = $ENV{HOME};

## Core ##
my $dtstamp = strftime( "%Y%m%d-%H%M%S", localtime);
print  strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $TestName Script Start \n";

## Windows titles
my $IB = 'Information base';
my $hIB = 0;
my $RF = 'Resource file';
my $hRF = 0;
my $AD = 'Ananas: Designer';
my $hAD = 0;
my $WIN_SAVE = 'save';
my $hWIN_SAVE = 0;

# Start the application
StartApp('ananas-designer --lang en');
# Wait at most 20 seconds for it to come up
($hIB) = WaitWindowViewable($IB, undef, 5) or die("Could not find $IB window!");

print strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $IB : open ok\n";
SendKeys('{DOW}');
SendKeys('%(n)');

($hRF) = WaitWindowViewable($RF, undef, 5) or die("Could not find $RF window!");
print strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $RF window : open ok\n";
SendKeys('{TAB}');
SendKeys('+({TAB})');
SendKeys($HomeDir."/".'myrc-'.$dtstamp);
SendKeys('{TAB 2}');
SendKeys($TestName.$dtstamp);
SendKeys('{TAB}');
SendKeys($TestName.$dtstamp);
SendKeys('{TAB}');
# db driver choice (None,Internal,MySQL,PosgreSQL)
SendKeys('{DOW}');
SendKeys('{DOW}');
SendKeys('{TAB}');
SendKeys('localhost');
SendKeys('{TAB 2}');
SendKeys('root');
SendKeys('{TAB 2}');
SendKeys('/tmp');
SendKeys('{TAB}');
SendKeys($HomeDir."/".$TestName."-".$dtstamp.".cfg");
SendKeys('{TAB 2}');
SendKeys('{ENT 2}');


#($hWIN_SAVE) = WaitWindowViewable($WIN_SAVE, undef, 5) or die("Could not find $WIN_SAVE window!");
if (($hWIN_SAVE) = WaitWindowViewable($WIN_SAVE, undef, 5)) {
	SendKeys('^{ENT}');
} else {
	print strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: info :: $WIN_SAVE window : not found \n";
}
if (($hAD) = WaitWindowViewable($AD, undef, 5)) {
	print strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: info :: $AD window : open ok\n";
} else {
	or die("Could not find $AD window!");
}

print strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: info :: $TestName Script End (Success)\n";

## EOF ##
