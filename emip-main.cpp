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

Model knapsack()
{
	Model mk(EMIP::Maximize);

	const Expr& body_obj = Op(Par1Index("p", Var("i")), '*', Var1Index("x", Var("i")));
	body_obj.print();
	Expr sum = SumIn(Var("i"), Set("S"), body_obj);

	mk.setObj(sum);


	return mk;
}


int main()
{
    EMIP::Model mk = knapsack();
    mk.print();

    cout << "Finished successfully!" << endl;

    return 0;
}

