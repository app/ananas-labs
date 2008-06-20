#!/usr/bin/perl
#-----------------------------------------------------------------------------#
# $Id: bs-choice-open-close.pl,v 1.2 2005/12/19 12:42:12 gr Exp $ 
# Simple test opens and closes business scheme choice screen dialog. 
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
my $hIB = 0;
my $TestName = 'bs-choice-open-close';
my $LogName = $TestName . '.log';

## Core ##
print  strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $TestName :: Ok :: Script Start \n";

## Windows titles
my $IB = 'Information base';

# Start the application
StartApp('ananas-designer --lang en');
# Wait at most 20 seconds for it to come up
($hIB) = WaitWindowViewable($IB, undef, 5) or die('Could not find Ananas window!');

print  strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $TestName :: Ok :: $IB window open \n";
SendKeys('{TAB 5}');
SendKeys('{ENT}');

#WaitWindowClose($hIB) or die('Could not close IB Window!');
if (WaitWindowClose($hIB)) {
	print  strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $TestName :: Ok :: $IB window close \n";
} else {
	print  strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $TestName :: Error :: $IB window close \n";
	die('Could not close IB Window!');
}


print strftime( "%Y-%m-%d %H:%M:%S", localtime)," :: $TestName :: Ok :: Script End (Success)\n";

## EOF ##
