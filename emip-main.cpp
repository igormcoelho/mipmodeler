// ==================================================
// Class for MIP modeling and automatic code deriving
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - Gnu Public License v3 - GPLv3
// ==================================================

#include<iostream>

#include "EMIPModeler.h"

using namespace std;
using namespace EMIP;


Modeler& knapsack()
{
	Modeler mk(EMIP::Maximize);

	VAR vi = Var("i");

	EXPR body_obj = Op(Par1Index("p", vi), '*', Var1Index("x", vi));

	EXPR sumObj = SumIn(vi, Set("I"), body_obj, "objfunction");
	cout << "name: " << sumObj.exprName << endl;

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
    Modeler& mk = knapsack();
    cout << "EMIP tree structure:" << endl;
    mk.print();

    cout << endl << endl;

    cout << "LaTeX:" << endl;
    cout << mk.toLatex() << endl;

    cout << endl << endl;

    cout << "MIP:" << endl;
    cout << mk.toMIP() << endl;

    cout << "Finished successfully!" << endl;

    return 0;
}

