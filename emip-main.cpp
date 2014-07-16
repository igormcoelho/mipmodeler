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

#include "EMIPReader.h"

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
    INDEX k = Index("k", Integer);
    INDEX r = Index("r", Integer);
    INDEX s = Index("s", Integer);
    INDEX t = Index("t", Integer);

    PAR appFix = Par("appFix");

    SET S = Set("S"); // REMOVE!

    SETSET R = SetSet("R");
    SET T  = Set("T"); // 0..|T|
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

    EXPR body1 = Op(Op(Vrtm1, '-', Vrt), '+', SumIn(s, RrRM, SumIn(i, Ixs, SumTo(j, Num(0), Jsi, sum_1) ) ));
    EXPR body2 = Op(body1, '+', SumIn(s, RrRM, SumIn(i, Ils, Var3Index("l", s, i , t )) ) );

    FORALL fa_r = ForAllIn(r, RM);
    //FORALL fa_rt = ForAllTo(ForAllIn(r, T, fa_r));

    CONS c2 = Cons("c1", fa_r, body2, '=', appFix);

    cout << c2.toLatex(false) << endl;

    EXPR obj = SumIn(i, T, Num(1), "obj");
    mk.setObj(obj);


    mk.addCons(c2);

    return mk.clone();
}


int main()
{

    Reader r;
    Modeler& mkread = r.readFile("test.mathprog");

    mkread.print();
    return 1;


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

