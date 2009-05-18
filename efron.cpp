/*
 *  efron.cpp
 *  Mothur
 *
 *  Created by Thomas Ryabin on 5/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "efron.h"
#include <math.h>

/***********************************************************************/
EstOutput Efron::getValues(SAbundVector* rank){

	try {
		data.resize(1,0);
		
		double n = (double)rank->getNumSeqs();
		if(m > n) {
			cout << "Error in the 'efron' calculator. 'size' must be less than the length of the smallest sabund vector.\n";
			data[0] = 0;
			return data;
		}
		
		double sum = 0;
		for(int i = 1; i < rank->size(); i++)
			sum += pow(-1, (double)(i+1)) * pow(((double)m / n), i) * (double)(rank->get(i));

		data[0] = sum;
		
		return data;
	}
	catch(exception& e) {
		cout << "Standard Error: " << e.what() << " has occurred in the Coverage class Function getValues. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
	catch(...) {
		cout << "An unknown error has occurred in the Coverage class function getValues. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}	
};


/***********************************************************************/
