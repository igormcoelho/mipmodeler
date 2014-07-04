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
	//for(int i: I) // TODO: USE C++11
	for(int i=0; i<N; i++)
		x[i] = MIPVar(MIPBinary, 0, 1);
	x.renameVars();

	for(int i=0; i<N; ++i)
		model.add(p[i], x[i]);

	MIPCons cap('<', C); // could use name also: cap("capacity", '<', C)
	for(int i=0; i<N; ++i)
		cap.add(w[i], x[i]);

	model.add(cap);

	return model;
}


Modeler& knapsack()
{
	Modeler mk(EMIP::Maximize);
	//mk.depend(Par("p"));
	//mk.depend(Par("w"));
	//mk.depend(Set("I"));
	
	INDEX vi = Index("i", Integer);

	EXPR body_obj = Op(Par1Index("p", vi), '*', Var1Index("x", vi));

	EXPR sumObj = SumTo(SumIn(vi, Set("I"), body_obj, "objfunction1"));
	cout << "name: " << sumObj.exprName << endl;

	mk.setObj(sumObj);

	//cout << sumObj.toLatex() << endl;

	// --------------

	EXPR sumC1 = SumTo(SumIn(vi, Set("I"), Op(Par1Index("w", vi), '*', Var1Index("x", vi))));

	CONS c1 = Cons("c1", sumC1, '<', Par("C"));


	mk.addCons(c1);

	return mk.clone();
}

Modeler& tsp()
{
	Modeler mk(EMIP::Minimize);
	
	INDEX i = Index("i", Integer);
	INDEX j = Index("j", Integer);
	SET S = Set("S");

	EXPR body_obj = Op(Par2Index("c", i, j), '*', Var2Index("x", i, j));

	EXPR sumObj1 = SumTo(j, Num(0), Par("N"), body_obj); //SumTo(SumIn(j, S, body_obj));
	EXPR sumObj2 = SumTo(SumIn(i, S, sumObj1, "objfunc1"));
	cout << "name: " << sumObj2.exprName << endl;

	mk.setObj(sumObj2);

	//cout << sumObj.toLatex() << endl;

	// --------------

	FORALL faC1 = ForAllTo(ForAllIn(i, S));
	EXPR bodyC1 = Var2Index("x", Num(0), i);

	CONS c1 = Cons("c1", faC1, bodyC1, '<', Num(1));


	mk.addCons(c1);

	return mk.clone();
}


int main()
{
    Modeler& mk = tsp();
    cout << "EMIP tree structure:" << endl;
    mk.print();

    cout << endl << endl;

    cout << "LaTeX:" << endl;
    cout << mk.toLatex() << endl;

    cout << endl << endl;

    cout << "MIP:" << endl;
    string mstr = mk.toMIP();
    FILE* cmodel = fopen("model.c", "w");
    fprintf(cmodel, "#include<iostream>\nint main()\n{\n");
    fprintf(cmodel, "%s\n", mstr.c_str());
    fprintf(cmodel, "return 0;\n}\n");
    fclose(cmodel);

    system("indent model.c");
    system("cat model.c");

    cout << "Finished successfully!" << endl;

    return 0;
}

