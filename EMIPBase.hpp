/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIPBASE_HPP_
#define EMIPBASE_HPP_

#include<iostream>
#include<sstream>
#include<limits>
#include<vector>
#include<algorithm>

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

using namespace std;

namespace EMIP
{

const double Inf = numeric_limits<double>::infinity();

enum ProblemType
{
	Minimize, Maximize
};

enum Type
{
	Real, Binary, Integer, Unknown
};
// (?)

enum Id
{
	IdExpr, IdVar, IdVar1Index, IdVar2Index, IdVar3Index, IdVar4Index, IdVar5Index, IdPar, IdPar1Index, IdPar2Index, IdPar3Index, IdPar4Index, IdPar5Index, IdNum, IdOp, IdMultiOp, IdComp, IdBoolOp, IdBool, IdNot, IdSet, IdSetElem, IdSetSet, IdSetSetElem, IdSetCard, IdSetOp, IdSum, IdSumIn, IdSumTo, IdForAll, IdForAllIn, IdForAllTo, IdCons, IdIfElse
};

struct GenMIP
{
	string now;
	string before;
	string after;
};

}


#endif /* EMIPBASE_HPP_ */
