// =========================================
// Simple class for MIP modeling
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - LGPLv3 (Gnu Lesser GPLv3)
// =========================================

#include<iostream>

#include "MIPModel.h"
#include "MIPVarArray.h"

using namespace std;


int main()
{
    // model MIPModel(type={MIPMinimize;MIPMaximize})
    // methods: add(double obj_coefficient, MIPVar&), add(MIPCons&), print(), writeLP(string filename)

    // Arrays: 'MIPVarArray([optional: string name], [optional: size])', 'MIPVarArray2' ... 'MIPVarArray5', access by [][]...[]
    // methods: print(), renameVars)(), access by []

    // Variable: MIPVar([optional: string name], type, lowerbound, upperbound)
    // type can be: MIPInteger, MIPBinary, MIPReal
    // lowerbound can be any number, or -MIPInf
    // upperbound can be any number, or MIPInf
    // methods: toString(), print(), setName(s), getName, setLowerBound(lb), getLowerBound, setUpperBound(ub), getUpperBound()

    // Constraint: MIPCons([optional: string name], char signal {'<', '=', '>'}, double right_hand_side)
    // all methods add to left hand side: add(double coefficient, MIPVar&), add(double constant), setName(s), getName()

    MIPModel model(MIPMaximize);

    MIPVarArray x(10, "x");
    x[0].setLowerBound(10).setUpperBound(100);
    x[1].setUpperBound(100);
    x.print();

    for(unsigned i=0; i<10; i++)
    {
        x[i]=MIPVar(MIPInteger, 0, MIPInf);
    }
    x.print();
    x.renameVars();
    x.print();

    model.add(0.8, x[0]);
    model.add(-0.9, x[1]);

    MIPCons c1('>', 5);
    c1.add(1.0, x[0]);
    c1.add(0.0, x[1]);

    model.add(c1);

    model.print();

    c1.setName("restriction_name");
    x[0] = MIPVar("new_x_0", MIPReal, 4, MIPInf);

    model.print();

    model.writeLP("test.lp");

    cout << "Finished successfully!" << endl;

    return 0;
}

