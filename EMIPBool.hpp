/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIP_BOOL_HPP_
#define EMIP_BOOL_HPP_

#include<iostream>
#include<sstream>
#include<limits>
#include<vector>
#include<algorithm>

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "EMIPExpr.hpp"

using namespace std;

namespace EMIP
{

class Boolean
{
public:

	Boolean()
	{
	}

	virtual ~Boolean()
	{
	}

	virtual Id id() const
	{
		return IdBool;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPTrue() ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		return "";
	}

	virtual Boolean& clone() const
	{
		return *new Boolean;
	}
};

class Comp: public Boolean
{
protected:
	Expr& e1;
	string op;
	Expr& e2;
public:

	Comp(const Expr& _e1, string _op, const Expr& _e2) :
			e1(_e1.clone()), op(_op), e2(_e2.clone())
	{
		if ((op != "!=") && (op != "=") && (op != ">") && (op != "<"))
		{
			cout << "ERROR: UNKNOWN COMPARISON '" << op << "'" << endl;
			exit(1);
		}
	}

	virtual ~Comp()
	{
	}

	virtual Id id() const
	{
		return IdComp;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPComp(" << e1.toString() << " " << op << " " << e2.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		if (br)
			ss << "\\left(";
		ss << e1.toLatex() << " " << op << e2.toLatex();
		if (br)
			ss << " \\right) ";
		return ss.str();
	}

	virtual Boolean& clone() const
	{
		return cloneComp();
	}

	virtual Comp& cloneComp() const
	{
		return *new Comp(e1, op, e2);
	}
};

class Not: public Boolean
{
protected:
	Boolean& e1;
	string op;
public:

	Not(const Boolean& _e1) :
			e1(_e1.clone())
	{
	}

	virtual ~Not()
	{
	}

	virtual Id id() const
	{
		return IdNot;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPNot(" << e1.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "not(" << e1.toLatex() << ")";
		return ss.str();
	}
};

class BoolOp: public Boolean
{
protected:
	Comp& e1;
	string op;
	Comp& e2;
public:

	BoolOp(Comp& _e1, string _op, Comp& _e2) :
			e1(_e1), op(_op), e2(_e2)
	{
		if ((op != "and") && (op != "or"))
		{
			cout << "ERROR! UNKNOWN BoolOp '" << op << "'" << endl;
			exit(1);
		}
	}

	virtual ~BoolOp()
	{
	}

	virtual Id id() const
	{
		return IdBoolOp;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPBoolOp(" << e1.toString() << " " << op << " " << e2.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\left(" << e1.toLatex() << " " << op << e2.toLatex() << " \\right) ";
		return ss.str();
	}
};

}


#endif /* EMIP_BOOL_HPP_ */
