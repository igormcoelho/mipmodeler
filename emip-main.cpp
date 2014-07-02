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

const Expr& knapsack()
{
	Model mk(EMIP::Maximize);

	const Expr& vi = Var("i");
	vi.print();

	const Expr& p1 = Par1Index("p", Var("i"));
	p1.print();

	const Expr& body_obj = Op(Par1Index("p", Var("i")), '*', Var1Index("x", Var("i")));
	cout << "first: ";
	body_obj.print();


	//Expr sum = SumIn(Var("i"), Set("S"), body_obj);
	//mk.setObj(sum);
	return body_obj;
}


int main()
{
    //EMIP::Model mk = knapsack();
	const Expr& mk = knapsack();
	cout << "final: ";
    mk.print();

    cout << "Finished successfully!" << endl;

    return 0;
}

