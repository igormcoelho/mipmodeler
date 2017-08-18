/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIP_CONS_HPP_
#define EMIP_CONS_HPP_

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

class Cons
{
protected:
	string name;
	ForAll& fa;
	Expr& lhs;
	char signal;
	Expr& rhs;
public:

	Cons(string _name, const Expr& _lhs, char _signal, const Expr& _rhs) :
			name(_name), fa(*new ForAll), lhs(_lhs.clone()), signal(_signal), rhs(_rhs.clone())
	{
	}

	Cons(string _name, const ForAll& _fa, const Expr& _lhs, char _signal, const Expr& _rhs) :
			name(_name), fa(_fa.clone()), lhs(_lhs.clone()), signal(_signal), rhs(_rhs.clone())
	{
	}

	virtual ~Cons()
	{
	}

	virtual Id id() const
	{
		return IdCons;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPCons('" << name << "', " << fa.toString() << ": " << lhs.toString() << " '" << signal << "' " << rhs.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool linebreak) const
	{
		stringstream ss;
		ss << lhs.toLatex(false) << " ";
		if (signal == '=')
			ss << "=";
		else if (signal == '<')
			ss << "\\leq";
		else if (signal == '>')
			ss << "\\geq";

		ss << " & " << rhs.toLatex(false) << " & " << fa.toLatex();
		if (name != "")
			ss << " \\label{eq:" << name << "} ";
		if (linebreak)
			ss << " \\\\";

		return ss.str();
	}

	virtual string toMIP() const
	{
		if (name == "")
			return "";

		stringstream ss;

		GenMIP retFA = fa.toMIP();
		ss << retFA.before;
		// unused retFA.now

		GenMIP retRhs = rhs.toMIP("");
		ss << retRhs.before;
		if (retRhs.now == "")
			ss << "MIPCons::toMIP:ERROR! empty rhs.now = '" << rhs.toString() << "'" << endl;

		ss << "IloExpr " << name << "(env);\n";
		ss << retRhs.after;

		GenMIP retLhs = lhs.toMIP("");
		ss << retLhs.before;
		if (retLhs.now == "")
			ss << "MIPCons::toMIP:ERROR! empty lhs.now = '" << lhs.toString() << "'" << endl;

		ss << name << " += " << retLhs.now << "; /* ';' added by Cons '" << name << "' */ \n";
		ss << retLhs.after;
		ss << "model.add(" << name << " " << signal << " " << retRhs.now << ");\n";

		ss << retFA.after;

		return ss.str();
	}

	virtual Cons& clone() const
	{
		return *new Cons(name, fa, lhs, signal, rhs);
	}
};

class IfElse
{
protected:
	Boolean& condition;
	vector<Cons*> vif;
	vector<Cons*> velse;
public:
	IfElse(const Boolean& _condition) :
			condition(_condition.clone())
	{
	}

	IfElse(const IfElse& ifelse) :
			condition(ifelse.condition.clone())
	{
		for (unsigned i = 0; i < ifelse.vif.size(); ++i)
			vif.push_back(&ifelse.vif[i]->clone());
		for (unsigned i = 0; i < ifelse.velse.size(); ++i)
			velse.push_back(&ifelse.velse[i]->clone());
	}

	virtual ~IfElse()
	{
	}

	IfElse& addIf(const Cons& cons)
	{
		vif.push_back(&cons.clone());
		return *this;
	}

	IfElse& addElse(const Cons& cons)
	{
		velse.push_back(&cons.clone());
		return *this;
	}

	virtual Id id() const
	{
		return IdIfElse;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPIfElse(if(" << condition.toString() << ") { ";
		for (unsigned i = 0; i < vif.size(); i++)
			ss << vif[i]->toString() << " ";
		ss << " } else { " << endl;
		for (unsigned i = 0; i < velse.size(); i++)
			ss << vif[i]->toString() << " ";
		ss << " } ";

		return ss.str();
	}

	virtual string toLatex() const
	{
		stringstream ss;
		ss << "If $" << condition.toLatex() << "$ then: \\\n";
		ss << "\\begin{align}\n";
		for (int i = 0; i < ((int) vif.size()); ++i)
			ss << vif[i]->toLatex(i != ((int) vif.size()) - 1) << endl;
		ss << "\\end{align}\n";

		if (velse.size() == 0)
			return ss.str();

		ss << "Else: \\\n";
		ss << "\\begin{align}\n";
		for (int i = 0; i < ((int) velse.size()); ++i)
			ss << velse[i]->toLatex(i != ((int) velse.size()) - 1) << endl;
		ss << "\\end{align}\n";

		return ss.str();
	}

	virtual IfElse& clone() const
	{
		return *new IfElse(*this);
	}
};

}


#endif /* EMIP_CONS_HPP_ */
