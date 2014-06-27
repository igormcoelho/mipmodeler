// ==============================
// Simple class for MIP modeling
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - LGPLv3
// ==============================

#include<iostream>

#include "MIPModel.hpp"

using namespace std;

int main()
{

    MIPMinimize model;

    vector<MIPVar*> x;
    for(unsigned i=0; i<10; i++)
    {
	x.push_back(new MIPVar(0, MIPInf, true)); 
    }

    x[0]->setLowerBound(10).setUpperBound(100).setName("x_0");
    x[1]->setUpperBound(100);

    model.add(0.8, x[0]);
    model.add(-0.9, x[1]);

    MIPCons c1('>', 5);
    c1.add(1.0, x[0]);
    c1.add(0.0, x[1]);

    model.add(&c1);

    model.printLP();

    return 0;
}
