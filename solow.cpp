/*
 *  solow.cpp
 *  Mothur
 *
 *  Created by Thomas Ryabin on 5/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "solow.h"
#include <math.h>

	
/***********************************************************************/	
EstOutput Solow::getValues(SAbundVector* rank){

	try {
		data.resize(1,0);
		
		double n = (double)rank->getNumSeqs();
		double f1 = (double)rank->get(1);
		double f2 = (double)rank->get(2);

		data[0] = f1*f1/2/f2 * (1 - pow(1 - 2*f2/n/f1, m));
		
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
