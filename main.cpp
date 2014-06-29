// ==============================
// Simple class for MIP modeling
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - LGPLv3
// ==============================

#include<iostream>

#include "MIPModel.h"
#include "MIPVarArray.h"

using namespace std;

int main()
{

    MIPMinimize model;

    MIPVarArray x("x");
    x.print();
    for(unsigned i=0; i<10; i++)
    {
	x.push_back(MIPVar(0, MIPInf, true)); 
    }

    x[0].setLowerBound(10).setUpperBound(100);
    x[1].setUpperBound(100);
    x.print();
    x.renameVars();
    x.print();

    model.add(0.8, x[0]);
    model.add(-0.9, x[1]);

    MIPCons c1('>', 5);
    c1.add(1.0, x[0]);
    c1.add(0.0, x[1]);

    model.add(c1);

    model.printLP();

    return 0;
}
