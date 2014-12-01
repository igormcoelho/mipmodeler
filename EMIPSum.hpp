/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIP_SUM_HPP_
#define EMIP_SUM_HPP_

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

class Sum: public Expr
{
public:
	// TODO: protect
	Expr& body;

public:
	Sum(const Expr& _body, string exprName = "") :
			Expr(exprName), body(_body.clone())
	{
	}

	virtual ~Sum()
	{
	}

	virtual Id id() const
	{
		return IdSum;
	}

	virtual string toString() const = 0;

	virtual string toLatex(bool br = true) const = 0;

	virtual Expr& clone() const = 0;
};

class SumIn: public Sum
{
public:
	// protect
	Index& v;
	Set& s;
	Boolean& st; // such that

public:
	SumIn(const Index& _v, const Set& _s, const Expr& body, string exprName = "") :
			Sum(body, exprName), v(_v.cloneIndex()), s(_s.clone()), st(*new Boolean)
	{
	}

	SumIn(const Index& _v, const Set& _s, const Expr& body, const Boolean& _st, string exprName = "") :
			Sum(body, exprName), v(_v.cloneIndex()), s(_s.clone()), st(_st.clone())
	{
	}

	virtual ~SumIn()
	{
	}

	virtual Id id() const
	{
		return IdSumIn;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSumIn(" << v.toString() << " in " << s.toString() << "{" << Sum::body.toString() << "}) ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\sum_{" << v.toLatex() << " \\in " << s.toLatex(false) << "}" << body.toLatex(false) << " ";
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		GenMIP r;

		stringstream ssbefore;
		stringstream ssnow;
		stringstream ssafter;

		GenMIP rs = s.toMIP();
		ssbefore << rs.before;
		ssafter << rs.after;

		GenMIP rbody = body.toMIP(var);
		ssbefore << rbody.before;
		ssafter << rbody.after;

		if (var == "")
			ssbefore << "{\nIloExpr _sumin(env);\n";
		ssbefore << "for(";
		if (v.type == Integer)
			ssbefore << "int";
		else if (v.type == Binary)
			ssbefore << "bool";
		else
			ssbefore << "double";
		ssbefore << " " << v.indexToMIP() << ": " << rs.now << ")\n";
		if (var == "")
			ssnow << "_sumin += ";
		ssnow << rbody.now;
		if (var == "")
			ssnow << ";\n";

		if (var == "")
			ssafter << "}\n";

		r.before = ssbefore.str();
		r.now = ssnow.str();
		r.after = ssafter.str();

		return r;
	}

	virtual Expr& clone() const
	{
		return *new SumIn(v, s, body, st, Expr::exprName);
	}
};

class SumTo: public Sum
{
public:
	// TODO: protect
	Index& v;
	Expr& begin;
	Expr& end;
	Boolean& st; // such that
public:

	SumTo(const SumIn& sin, int start = 0) :
			Sum(sin.body, sin.getExprName()), v(sin.v.cloneIndex()), begin(*new Num(start)), end(start == 0 ? (Expr&) *new Op(SetCard(sin.s), '-', Num(1)) : (Expr&) *new SetCard(sin.s)), st(sin.st.clone())
	{
	}

	SumTo(const Index& _v, const Expr& _begin, const Expr& _end, const Expr& body, string exprName = "") :
			Sum(body, exprName), v(_v.cloneIndex()), begin(_begin.clone()), end(_end.clone()), st(*new Boolean)
	{
	}

	SumTo(const Index& _v, const Expr& _begin, const Expr& _end, const Expr& body, const Boolean& _st, string exprName = "") :
			Sum(body, exprName), v(_v.cloneIndex()), begin(_begin.clone()), end(_end.clone()), st(_st.clone())
	{
	}

	virtual ~SumTo()
	{
	}

	virtual Id id() const
	{
		return IdSumTo;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSumTo(" << v.toString() << " <- " << begin.toString() << " to " << end.toString() << "{ " << Sum::body.toString() << "}) ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\sum_{" << v.toLatex() << " = " << begin.toLatex(false) << "}^{" << end.toLatex(false) << "}" << body.toLatex(false) << " ";
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		GenMIP r;

		stringstream ssbefore;
		stringstream ssnow;
		stringstream ssafter;

		GenMIP rb = begin.toMIP("");
		ssbefore << rb.before;
		ssafter << rb.after;

		GenMIP re = end.toMIP("");
		ssbefore << re.before;
		ssafter << re.after;

		GenMIP rbody = body.toMIP(var);

		if (var == "")
			ssbefore << "{\nIloExpr _sumto(env);\n";
		ssbefore << "for(";
		if (v.type == Integer)
			ssbefore << "int";
		else if (v.type == Binary)
			ssbefore << "bool";
		else
			ssbefore << "double";
		ssbefore << " " << v.indexToMIP() << " = " << rb.now << "; " << v.indexToMIP() << " <= " << re.now << "; ++" << v.indexToMIP() << ")\n{ // begin for " << v.indexToMIP() << " \n";
		if (var == "")
			ssnow << "_sumto += ";
		ssnow << rbody.now;
		if (var == "")
			ssnow << "; /* ';' from for " << v.indexToMIP() << " */\n";
		ssafter << "\n} // end for " << v.indexToMIP() << "\n";

		if (var == "") // _sumto
			ssafter << "\n} // end _sum scope\n";

		ssbefore << rbody.before;
		ssafter << rbody.after;

		r.before = ssbefore.str();
		r.now = ssnow.str();
		r.after = ssafter.str();

		return r;
	}

	virtual Expr& clone() const
	{
		return *new SumTo(v, begin, end, body, st, Sum::exprName);
	}
};

}


#endif /* EMIP_SUM_HPP_ */
