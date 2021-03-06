/*
 *  sharedthetan.cpp
 *  Dotur
 *
 *  Created by Sarah Westcott on 1/8/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "sharedthetan.h"

/***********************************************************************/
EstOutput ThetaN::getValues(vector<SharedRAbundVector*> shared) {
	try {	
		data.resize(1,0);
		
		double Atotal, Btotal, tempA, tempB;
		Atotal = 0; Btotal = 0; 
		double numerator, denominator, thetaN, sumSharedA, sumSharedB, a, b, d;
		numerator = 0.0; denominator = 0.0; thetaN = 0.0; sumSharedA = 0.0; sumSharedB = 0.0; a = 0.0; b = 0.0; d = 0.0;
		
		//get the total values we need to calculate the theta denominator sums
		for (int i = 0; i < shared[0]->getNumBins(); i++) {
			//store in temps to avoid multiple repetitive function calls
			Atotal += shared[0]->get(i);
			Btotal += shared[1]->get(i);
		}
		
		//calculate the theta denominator sums
		for (int j = 0; j < shared[0]->getNumBins(); j++) {
			//store in temps to avoid multiple repetitive function calls
			tempA = shared[0]->get(j);
			tempB = shared[1]->get(j);
			
			//they are shared
			if (!util.isEqual(tempA, 0) && !util.isEqual(tempB, 0)) {
				if (!util.isEqual(Atotal, 0))	{ sumSharedA = (tempA / (float)Atotal); }
				if (!util.isEqual(Btotal, 0))	{ sumSharedB = (tempB / (float)Btotal); }
			
				a += sumSharedA;
				b += sumSharedB;
			}
		}

		thetaN = (a * b) / (a + b - (a * b));
		
		if (isnan(thetaN) || isinf(thetaN)) { thetaN = 0; }
		
		data[0] = 1.0 - thetaN;
		
		return data;
	}
	catch(exception& e) {
		m->errorOut(e, "ThetaN", "getValues");
		exit(1);
	}
}

/***********************************************************************/
