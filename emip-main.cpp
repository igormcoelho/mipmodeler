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
using namespace EMIP;


Model& knapsack()
{
	Model mk(EMIP::Maximize);

	VAR vi = Var("i");

	EXPR body_obj = Op(Par1Index("p", vi), '*', Var1Index("x", vi));

	EXPR sum = SumIn(vi, Set("I"), body_obj);

	mk.setObj(sum);

	return mk.clone();
}


int main()
{
    Model& mk = knapsack();
    mk.print();

    cout << "Finished successfully!" << endl;

    return 0;
}

