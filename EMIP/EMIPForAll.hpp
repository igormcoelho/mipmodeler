/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIP_FORALL_HPP_
#define EMIP_FORALL_HPP_

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

class ForAll
{
public:

	ForAll()
	{
	}

	virtual ~ForAll()
	{
	}

	virtual Id id() const
	{
		return IdForAll;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPForAll() ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		return "";
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		return r;
	}

	virtual ForAll& clone() const
	{
		return *new ForAll;
	}
};

class ForAllIn: public ForAll
{
public:
	//protected:
	Index& v;
	Set& s;
	Boolean& st; // such that
public:
	ForAllIn(const Index& _v, const Set& _s) :
			v(_v.cloneIndex()), s(_s.clone()), st(*new Boolean)
	{
	}

	ForAllIn(const Index& _v, const Set& _s, const Boolean& _st) :
			v(_v.cloneIndex()), s(_s.clone()), st(_st.clone())
	{
	}

	virtual ~ForAllIn()
	{
	}

	virtual Id id() const
	{
		return IdForAllIn;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPForAllIn(" << v.toString() << " in " << s.toString() << "| " << st.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\forall " << v.toLatex() << " \\in " << s.toLatex(false);
		if (st.id() != IdBool)
			ss << "|" << st.toLatex() << " ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;

		stringstream ssbefore;
		stringstream ssafter;

		GenMIP rs = s.toMIP();
		ssbefore << rs.before;
		ssafter << rs.after;

		ssbefore << "for(";
		if (v.type == Integer)
			ssbefore << "int";
		else if (v.type == Binary)
			ssbefore << "bool";
		else
			ssbefore << "double";
		ssbefore << " " << v.indexToMIP() << ": " << rs.now << ")\n";
		ssbefore << "{\n";
		ssafter << "}\n";

		r.before = ssbefore.str();
		r.after = ssafter.str();

		return r;
	}

	virtual ForAll& clone() const
	{
		return *new ForAllIn(v, s, st);
	}
};

class ForAllTo: public ForAll
{
public:
	//protected:
	Index& v;
	Expr& begin;
	Expr& end;
	Boolean& st; // such that
public:

	ForAllTo(const ForAllIn& sin, int start = 0) :
			v(sin.v.cloneIndex()), begin(*new Num(start)), end(start == 0 ? (Expr&) *new Op(SetCard(sin.s), '-', Num(1)) : (Expr&) *new SetCard(sin.s)), st(sin.st.clone())
	{
	}

	ForAllTo(const Index& _v, const Expr& _begin, const Expr& _end) :
			v(_v.cloneIndex()), begin(_begin.clone()), end(_end.clone()), st(*new Boolean)
	{
	}

	ForAllTo(const Index& _v, const Expr& _begin, const Expr& _end, const Boolean& _st) :
			v(_v.cloneIndex()), begin(_begin.clone()), end(_end.clone()), st(_st.clone())
	{
	}

	virtual ~ForAllTo()
	{
	}

	virtual Id id() const
	{
		return IdForAllTo;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPForAllTo(" << v.toString() << " <- " << begin.toString() << " to " << end.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\forall " << v.toLatex() << " = " << begin.toLatex(false) << " to " << end.toLatex(false) << " ";
		if (st.id() != IdBool)
			ss << "|" << st.toLatex() << " ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;

		stringstream ssbefore;
		stringstream ssafter;

		GenMIP rb = begin.toMIP("");
		ssbefore << rb.before;
		ssafter << rb.after;

		GenMIP re = end.toMIP("");
		ssbefore << re.before;
		ssafter << re.after;

		ssbefore << "for(";
		if (v.type == Integer)
			ssbefore << "int";
		else if (v.type == Binary)
			ssbefore << "bool";
		else
			ssbefore << "double";
		ssbefore << " " << v.indexToMIP() << " = " << rb.now << "; " << v.indexToMIP() << " <= " << re.now << "; ++" << v.indexToMIP() << ")\n";
		ssbefore << "{\n";
		ssafter << "}\n";

		r.before = ssbefore.str();
		r.after = ssafter.str();

		return r;
	}

	virtual ForAll& clone() const
	{
		return *new ForAllTo(v, begin, end, st);
	}
};

}


#endif /* EMIP_FORALL_HPP_ */
