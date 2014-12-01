/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIPEXPR_HPP_
#define EMIPEXPR_HPP_

#include<iostream>
#include<sstream>
#include<limits>
#include<vector>
#include<algorithm>

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "EMIPBase.hpp"

using namespace std;

namespace EMIP
{

class Expr
{
private:
	Expr* mimic;

public:
	string exprName; // do not set manually (use get)

protected:

	Expr() :
			mimic(NULL), exprName("")
	{
	}

public:

	Expr(string _exprName) :
			mimic(NULL), exprName(_exprName)
	{
	}

	Expr(const Expr& expr)
	{
		if (expr.mimic)
			mimic = &expr.mimic->clone();
		else
			mimic = &expr.clone();
	}

	virtual ~Expr()
	{
		if (mimic)
			delete mimic;
	}

	virtual string& getExprName()
	{
		if (mimic)
			return mimic->exprName;
		return exprName;
	}

	virtual const string& getExprName() const
	{
		if (mimic)
			return mimic->exprName;
		return exprName;
	}

	virtual Id id() const
	{
		if (mimic)
			return mimic->id();
		return IdExpr;
	}

	virtual string toString() const
	{
		if (mimic)
			return mimic->toString();
		stringstream ss;
		ss << "Expr('" << exprName << "') ";
		return ss.str();
	}

	// add braces before? (only for Expr classes)
	virtual string toLatex(bool br = true) const
	{
		if (mimic)
			return mimic->toLatex(br);
		stringstream ss;
		ss << "\\\\label{eq:" << exprName << "} ";
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		if (mimic)
			return mimic->toMIP(var);
		GenMIP r;
		if (var != "")
		{
			cout << "Expr::toMIP():ERROR! NOT A VALUE TO PUT IN '" << var << "'" << endl;
			exit(1);
		}

		return r;
	}

	virtual void print() const
	{
		if (mimic)
			return mimic->print();
		std::cout << toString() << std::endl;
	}

	virtual Expr& clone() const
	{
		return *new Expr(*this);
	}

	Expr& operator=(const Expr& e)
	{
		if (&e == this)
			return *this;
		cout << "DISABLED OPERATOR= FOR EXPR! (TODO)" << endl;
		exit(1);
		return *this;
	}
};

class Num: public Expr
{
protected:
	double d;
public:
	Num(double _d) :
			d(_d)
	{
	}

	virtual ~Num()
	{
	}

	virtual Id id() const
	{
		return IdNum;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPNum(" << d << ")";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << d;
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		GenMIP r;
		stringstream ss;
		if (var != "")
			ss << var << " += " << d << "; /* ';' added by Num */\n";
		else
			ss << d;
		r.now = ss.str();
		return r;
	}

	virtual Expr& clone() const
	{
		return *new Num(d);
	}
};

class Index: public Expr
{
public:
	// TODO: protected
	Type type;
	string name;
public:

	Index(string _name, Type _type) :
			type(_type), name(_name)
	{
	}

	virtual ~Index()
	{
	}

	inline bool isInteger() const
	{
		return type == Integer;
	}

	inline bool isBinary() const
	{
		return type == Binary;
	}

	inline bool isReal() const
	{
		return type == Real;
	}

	virtual Id id() const
	{
		return IdVar;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPIndex(";
		if (isInteger())
			ss << "Integer,";
		else if (isBinary())
			ss << "Binary,";
		else if (isReal())
			ss << "Real,";
		else
			ss << "";
		ss << "'" << name << "')";

		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		GenMIP r;
		if (var == "")
			r.now = name;
		else
		{
			stringstream ss;
			ss << var << " += " << name << "; /* ';' added by Index */\n";
		}
		return r;
	}

	virtual string indexToMIP() const
	{
		return name;
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name;
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return cloneIndex();
	}

	virtual Index& cloneIndex() const
	{
		return *new Index(name, type);
	}
};

}


#endif /* EMIPEXPR_HPP_ */
