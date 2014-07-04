// ==================================================
// Class for MIP modeling and automatic code deriving
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - Gnu Public License v3 - GPLv3
// ==================================================

#include<iostream>

#include "EMIPModeler.h"

#include "MIPModel.h"
#include "MIPVarArray.h"

using namespace std;
using namespace EMIP;

MIPModel mipk()
{
	// ==================
	// user configuration
	// ==================

	int N = 10;
	vector<int> I; // auxiliar set 'I'
	for(int i=0; i<N; i++)
		I.push_back(i);

	vector<double> p(N, 1.0);
	vector<double> w(N, 2.0);
	int C = 8;


	// ====================
	// automatic generation
	// ====================

	MIPModel model(MIPMaximize);

	MIPVarArray x(N, "x");
	for(int i: I)
		x[i] = MIPVar(MIPBinary, 0, 1);
	x.renameVars();

	for(unsigned i=0; i<N; ++i)
		model.add(p[i], x[i]);

	MIPCons cap('<', C); // could use name also: cap("capacity", '<', C)
	for(unsigned i=0; i<N; ++i)
		cap.add(w[i], x[i]);

	model.add(cap);

	return model;
}


Modeler& knapsack()
{
	Modeler mk(EMIP::Maximize);

	INDEX vi = Index("i", Integer);

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

