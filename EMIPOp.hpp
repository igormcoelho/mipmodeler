/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIP_OP_HPP_
#define EMIP_OP_HPP_

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

class Op: public Expr
{
protected:
	Expr& e1;
	char op;
	Expr& e2;

public:
	Op(const Expr& _e1, char _op, const Expr& _e2) :
			e1(_e1.clone()), op(_op), e2(_e2.clone())
	{
		if ((op != '+') && (op != '-') && (op != '*') && (op != '/'))
		{
			cout << "ERROR: UNKNOWN OPERATION '" << op << "'" << endl;
			exit(1);
		}
	}

	virtual ~Op()
	{
	}

	virtual Id id() const
	{
		return IdOp;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPOp(" << e1.toString() << " " << op << " " << e2.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		if (br)
			ss << "\\left(";
		ss << e1.toLatex() << " ";
		if (op == '*')
			ss << "\\cdot";
		else
			ss << op;

		ss << " " << e2.toLatex();
		if (br)
			ss << "\\right)";
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{

		GenMIP r;
		stringstream ss;
		stringstream ssbef;
		stringstream ssaft;

		GenMIP r1 = e1.toMIP("");
		ssbef << r1.before;

		GenMIP r2 = e2.toMIP("");
		ssbef << r2.before;

		if (var != "")
			ss << var << " += ";

		ss << "(" << r1.now << " " << op << " " << r2.now << ") ";
		if (r1.now == "")
			ss << "ERROR(EMPTY '" << e1.toString() << "')";
		if (r2.now == "")
			ss << "ERROR(EMPTY '" << e2.toString() << "')";

		if (var != "")
			ss << "; /* ';' from op " << op << " */\n";

		ssaft << r1.after;
		ssaft << r2.after;

		r.before = ssbef.str();
		r.after = ssaft.str();
		r.now = ss.str();

		return r;
	}

	virtual Expr& clone() const
	{
		return *new Op(e1, op, e2);
	}
};

class MultiOp: public Expr
{
protected:
	Expr& first;
	vector<pair<char, Expr*> > list;
public:
	MultiOp(const Expr& _first) :
			first(_first.clone())
	{
	}

	MultiOp(const MultiOp& mop) :
			first(mop.first.clone())
	{
		for (unsigned i = 0; i < mop.list.size(); ++i)
			list.push_back(make_pair(mop.list[i].first, &mop.list[i].second->clone()));
	}

	virtual ~MultiOp()
	{
	}

	MultiOp& add(char op, const Expr& e)
	{
		if ((op != '+') && (op != '-') && (op != '*') && (op != '/'))
		{
			cout << "ERROR: UNKNOWN OPERATION '" << op << "'" << endl;
			exit(1);
		}
		list.push_back(make_pair(op, &e.clone()));
		return *this;
	}

	virtual Id id() const
	{
		return IdMultiOp;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPMultiOp(SIZE=" << list.size() << "; " << first.toString();
		for (unsigned i = 0; i < list.size(); i++)
			ss << " " << list[i].first << " " << list[i].second->toString();
		ss << " ) ";

		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		if (br)
			ss << "\\left(";
		ss << first.toLatex() << " ";
		for (unsigned i = 0; i < list.size(); ++i)
			ss << list[i].first << " " << list[i].second->toLatex() << " ";
		if (br)
			ss << "\\right)";
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return *new MultiOp(*this);
	}
};

}


#endif /* EMIP_OP_HPP_ */
