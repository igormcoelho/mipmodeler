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

	EXPR sumObj = SumIn(vi, Set("I"), body_obj);

	mk.setObj(sumObj);

	//cout << sumObj.toLatex() << endl;

	// --------------

	EXPR sumC1 = SumIn(vi, Set("I"), Op(Par1Index("w", vi), '*', Var1Index("x", vi)));

	CONS c1 = Cons("c1", sumC1, '<', Par("C"));


	mk.addCons(c1);

	return mk.clone();
}


int main()
{
    Model& mk = knapsack();
    mk.print();

    cout << endl;
    cout << "LaTeX:" << endl;
    cout << mk.toLatex() << endl;

    cout << "Finished successfully!" << endl;

    return 0;
}

