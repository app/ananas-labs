/****************************************************************************
** $Id$
**
** Source file of Ananas project
* 
** Copyright (C) 2008 Andrey Paskal.
**
** This file is part of the extention of the Ananas
** automation accounting system.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
**********************************************************************/

#ifndef ACALC_H
#define ACALC_H

#include "aextension.h"
#include "aminicalc.h"

class ANANAS_EXPORT aCalc : public AExtension
{
		Q_OBJECT
	public: 		
		aCalc();
		~aCalc();
	
	public slots:
		void	Show();
		
	protected:
		MiniCalc*	calcInstance;
};

#endif // ACALC_H
