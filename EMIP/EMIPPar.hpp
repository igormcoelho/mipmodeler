/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIP_PAR_HPP_
#define EMIP_PAR_HPP_

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

class Par: public Expr
{
protected:
	Type type;
	string name;
public:

	Par(string _name, Type _type = Unknown) :
			type(_type), name(_name)
	{
	}

	virtual ~Par()
	{
	}

	inline string getName() const
	{
		return name;
	}

	inline Par& setName(string _name)
	{
		name = _name;
		return *this;
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
		return IdPar;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPPar(";
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

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name;
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
			ss << var << " += " << name << "; /* ';' added by Par */\n";
		}
		return r;
	}

	virtual Expr& clone() const
	{
		return clonePar();
	}

	virtual Par& clonePar() const
	{
		return *new Par(name, type);
	}
};

class Par1Index: public Par
{
protected:
	Expr& i1;
public:

	Par1Index(string _name, const Expr& _i1, Type _type = Unknown) :
			Par(_name, _type), i1(_i1.clone())
	{
	}

	virtual ~Par1Index()
	{
	}

	virtual Id id() const
	{
		return IdPar1Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPPar1Index(";
		if (isInteger())
			ss << "Integer,";
		else if (isBinary())
			ss << "Binary,";
		else if (isReal())
			ss << "Real,";
		else
			ss << "";
		ss << "'" << name << "')";
		ss << "[" << i1.toString() << "] ";

		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << "_{" << i1.toLatex() << "}";
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		GenMIP r;
		GenMIP ri1 = i1.toMIP("");
		stringstream ss;
		r.before = ri1.before;
		if (var != "")
			ss << var << " += ";
		ss << name << "[" << ri1.now << "]";
		r.now = ss.str();
		stringstream ssaft;
		if (var != "")
			ssaft << "; /* ';' added by Par1Index */\n";
		ssaft << ri1.after;
		r.after = ssaft.str();
		return r;
	}

	virtual Expr& clone() const
	{
		return clonePar();
	}

	virtual Par& clonePar() const
	{
		return *new Par1Index(name, i1, type);
	}
};

class Par2Index: public Par
{
protected:
	Expr& i1;
	Expr& i2;
public:

	Par2Index(string _name, const Expr& _i1, const Expr& _i2, Type _type = Unknown) :
			Par(_name, _type), i1(_i1.clone()), i2(_i2.clone())
	{
	}

	virtual ~Par2Index()
	{
	}

	virtual Id id() const
	{
		return IdPar2Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPPar2Index(";
		if (isInteger())
			ss << "Integer,";
		else if (isBinary())
			ss << "Binary,";
		else if (isReal())
			ss << "Real,";
		else
			ss << "";
		ss << "'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "] ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << "_{" << i1.toLatex() << "," << i2.toLatex() << "}";
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		GenMIP r;
		stringstream ss;
		stringstream ssbef;
		stringstream ssaft;

		GenMIP ri1 = i1.toMIP("");
		GenMIP ri2 = i2.toMIP("");

		ssbef << ri1.before;
		ssbef << ri2.before;
		r.before = ssbef.str();

		if (var != "")
			ss << var << " += ";
		ss << name << "[" << ri1.now << "][" << ri2.now << "]";
		r.now = ss.str();

		if (var != "")
			ssaft << "; /* ';' from Par2Index */\n";
		ssaft << ri1.after;
		ssaft << ri2.after;

		r.after = ssaft.str();
		return r;
	}

	virtual Expr& clone() const
	{
		return *new Par2Index(name, i1, i2, type);
	}
};

class Par3Index: public Par
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
public:

	Par3Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, Type _type = Unknown) :
			Par(_name, _type), i1(_i1.clone()), i2(_i2.clone()), i3(_i3.clone())
	{
	}

	virtual ~Par3Index()
	{
	}

	virtual Id id() const
	{
		return IdPar3Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPPar3Index(";
		if (isInteger())
			ss << "Integer,";
		else if (isBinary())
			ss << "Binary,";
		else if (isReal())
			ss << "Real,";
		else
			ss << "";
		ss << "'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "] ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << "_{" << i1.toLatex() << "," << i2.toLatex() << "," << i3.toLatex() << "}";
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return *new Par3Index(name, i1, i2, i3, type);
	}
};

class Par4Index: public Par
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
public:

	Par4Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4, Type _type = Unknown) :
			Par(_name, _type), i1(_i1.clone()), i2(_i2.clone()), i3(_i3.clone()), i4(_i4.clone())
	{
	}

	virtual ~Par4Index()
	{
	}

	virtual Id id() const
	{
		return IdPar4Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPPar4Index(";
		if (isInteger())
			ss << "Integer,";
		else if (isBinary())
			ss << "Binary,";
		else if (isReal())
			ss << "Real,";
		else
			ss << "";
		ss << "'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "]";
		ss << "[" << i4.toString() << "] ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << "_{" << i1.toLatex() << "," << i2.toLatex() << "," << i3.toLatex() << "," << i4.toLatex() << "}";
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return *new Par4Index(name, i1, i2, i3, i4, type);
	}
};

class Par5Index: public Par
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
	Expr& i5;
public:

	Par5Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4, const Expr& _i5, Type _type = Unknown) :
			Par(_name, _type), i1(_i1.clone()), i2(_i2.clone()), i3(_i3.clone()), i4(_i4.clone()), i5(_i5.clone())
	{
	}

	virtual ~Par5Index()
	{
	}

	virtual Id id() const
	{
		return IdPar5Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPPar5Index(";
		if (isInteger())
			ss << "Integer,";
		else if (isBinary())
			ss << "Binary,";
		else if (isReal())
			ss << "Real,";
		else
			ss << "";
		ss << "'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "]";
		ss << "[" << i4.toString() << "]";
		ss << "[" << i5.toString() << "] ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << "_{" << i1.toLatex() << "," << i2.toLatex() << "," << i3.toLatex() << "," << i4.toLatex() << "," << i5.toLatex() << "}";
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return *new Par5Index(name, i1, i2, i3, i4, i5, type);
	}
};

}


#endif /* EMIP_PAR_HPP_ */
