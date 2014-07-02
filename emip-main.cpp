// ==============================
// Simple class for MIP modeling
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - LGPLv3
// ==============================

#include<iostream>

#include "EMIPModel.h"

using namespace std;

EMIP::Model knapsack()
{
	EMIP::Model mk(EMIP::Maximize);

	


	return mk;
}


int main()
{
    EMIP::Model mk = knapsack();
    mk.print();

    cout << "Finished successfully!" << endl;

    return 0;
}

