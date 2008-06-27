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
}

#endif // ACALC_H
