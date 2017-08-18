// ==================================================
// Class for MIP modeling and automatic code deriving
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - Gnu Public License v3 - GPLv3
// ==================================================

#include<iostream>

#include "EMIP/EMIPModeler.hpp"

#include "SimpleMIP/MIPModel.hpp"
#include "SimpleMIP/MIPVarArray.hpp"

//#include "EMIPReader.h"

using namespace std;
using namespace EMIP;

/*
MIPModel mipk()
{
	// ==================
	// user configuration
	// ==================

	int N = 10;
	vector<int> I; // auxiliar set 'I'
	for (int i = 0; i < N; i++)
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
	for (int i = 0; i < N; i++)
		x[i] = MIPVar(MIPBinary, 0, 1);
	x.renameVars();

	for (int i = 0; i < N; ++i)
		model.add(p[i], x[i]);

	MIPCons cap('<', C); // could use name also: cap("capacity", '<', C)
	for (int i = 0; i < N; ++i)
		cap.add(w[i], x[i]);

	model.add(cap);

	return model;
}
*/

Modeler& knapsack()
{
    cout << "modeling knapsack" << endl;
    Modeler mk(EMIP::Maximize);

    Index i("i", Integer);
    Set I("I");

    mk.gi.declare(i);
    mk.gi.declare(I);

    Expr body_obj = Op(Par1Index("p", i), '*', Var1Index("x", i));

    Expr sumObj = SumTo(SumIn(i, I, body_obj, "objfunction1"));
    cout << "name: " << sumObj.getExprName() << endl;

    mk.setObj(sumObj);

    //cout << sumObj.toLatex() << endl;

    // --------------

    Expr sumC1 = SumTo(SumIn(i, I, Op(Par1Index("w", i), '*', Var1Index("x", i))));

    Cons c1("c1", sumC1, '<', Par("C"));

    mk.addCons(c1);

    return mk.clone();
}

Modeler& tsp()
{
    Modeler mk(EMIP::Minimize);

    INDEX i = Index("i", Integer);
    INDEX j = Index("j", Integer);
    INDEX k = Index("k", Integer);
    INDEX r = Index("r", Integer);
    INDEX s = Index("s", Integer);
    INDEX t = Index("t", Integer);

    PAR appFix = Par("appFix");

    SET S = Set("S"); // REMOVE!

    SETSET R = SetSet("R");
    SET T = Set("T"); // 0..|T|
    SETSET I = SetSet("I");
    SETSET Il = SetSet("I^l");
    SETSET Ix = SetSet("I^x");
    SET Ir = SetSetElem(I, r);
    SET Ils = SetSetElem(Il, s);
    SET Ixs = SetSetElem(Ix, s);
    EXPR Jsi = Par2Index("J", s, i);
    EXPR Ksij = Par3Index("K", s, i, j);
    SET Krij = Set("Krij");
    SET RM = Set("RM");

    EXPR tm1 = Op(t, '-', Num(1));
    EXPR deltasr = Par2Index("delta", s, r);
    EXPR tmdelta = Op(t, '-', deltasr);

    SET RrRM = SetOp(SetSetElem(R, r), "U", RM);

    // constraints 1

    EXPR Vrt = Var2Index("V", r, t);
    EXPR Vrtm1 = Var2Index("V", r, tm1);

    EXPR sum_1 = SumTo(k, Num(0), Ksij, Var5Index("x", s, i, t, j, k));

    EXPR body1 = Op(Op(Vrtm1, '-', Vrt), '+', SumIn(s, RrRM, SumIn(i, Ixs, SumTo(j, Num(0), Jsi, sum_1))));
    EXPR body2 = Op(body1, '+', SumIn(s, RrRM, SumIn(i, Ils, Var3Index("l", s, i, t))));

    FORALL fa_r = ForAllIn(r, RM);
    //FORALL fa_rt = ForAllTo(ForAllIn(r, T, fa_r));

    CONS c2 = Cons("c1", fa_r, body2, '=', appFix);

    cout << c2.toLatex(false) << endl;

    EXPR obj = SumIn(i, T, Num(1), "obj");
    mk.setObj(obj);

    mk.addCons(c2);

    return mk.clone();
}

void compileLaTeX(Modeler& m, string name)
{
    cout << "compiling " << name << ".tex" << endl;
    stringstream ss;
    ss << "output/" << name << ".tex";
    FILE* fknp = fopen(ss.str().c_str(), "w");
    fprintf(fknp, "\\documentclass{article}\n");
    fprintf(fknp, "\\usepackage{amsmath}\n");
    fprintf(fknp, "\\begin{document}\n");
    fprintf(fknp, "%s\n", m.toLatex().c_str());
    fprintf(fknp, "\\end{document}\n");
    fclose(fknp);
    stringstream ss2;
    ss2 << "cd output && pdflatex " << name << " > /dev/null";
    int k = system(ss2.str().c_str());
    if (k == 0)
        cout << "output file: " << name << ".pdf" << endl;
}

int main()
{

    //Reader r;
    //Modeler& mkread = r.readFile("test.mathprog");
    //mkread.print();
    //return 1;

    Modeler& mkn = knapsack();
    //cout << "EMIP tree structure:" << endl;
    //mkn.print();
    cout << "LaTeX:" << endl;
    cout << mkn.toLatex() << endl;
    cout << "% finish knapsack" << endl << endl;
    compileLaTeX(mkn, "knapsack");

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

