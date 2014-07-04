// ==================================================
// Class for MIP modeling and automatic code deriving
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - Gnu Public License v3 - GPLv3
// ==================================================

#ifndef EMIPMODELER_HPP
#define EMIPMODELER_HPP

#include<iostream>
#include<sstream>
#include<limits>
#include<vector>
#include<algorithm>

#include<stdio.h>
#include<stdlib.h>

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
	IdExpr, IdVar, IdVar1Index, IdVar2Index, IdVar3Index, IdVar4Index, IdVar5Index, IdPar, IdPar1Index, IdPar2Index, IdPar3Index, IdPar4Index, IdPar5Index, IdNum, IdOp, IdMultiOp, IdComp, IdBoolOp, IdBool, IdNot, IdSet, IdSetElem, IdSetCard, IdSetOp, IdSum, IdSumIn, IdSumTo, IdForAll, IdForAllIn, IdForAllTo, IdCons, IdIfElse
};

struct GenMIP
{
	string now;
	string before;
	string after;
};


class Expr
{
public:
	string exprName;

	Expr(string _exprName = "") :
			exprName(_exprName)
	{
	}

	virtual ~Expr()
	{
	}

	virtual Id id() const
	{
		return IdExpr;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "Expr('" << exprName << "') ";
		return ss.str();
	}

	// add braces before? (only for Expr classes)
	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\\\label{eq:" << exprName << "} ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		return r;
	}

	virtual void print() const
	{
		std::cout << toString() << std::endl;
	}

	virtual Expr& clone() const
	{
		return *new Expr(exprName);
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		stringstream ss;
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
public: // TODO: protected
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
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
			ss << "Real,";
		else
			ss << "";
		ss << "'" << name << "')";

		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		r.now = name;
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



class Var: public Expr
{
protected:
	Type type;
	string name;
public:

	Var(string _name, Type _type = Unknown) :
			type(_type), name(_name)
	{
	}

	virtual ~Var()
	{
	}

	inline string getName() const
	{
		return name;
	}

	inline Var& setName(string _name)
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
		return IdVar;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPVar(";
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		r.now = name;
		return r;
	}

	virtual Expr& clone() const
	{
		return cloneVar();
	}

	virtual Var& cloneVar() const
	{
		return *new Var(name, type);
	}
};

class Var1Index: public Var
{
protected:
	Expr& i1;
public:

	Var1Index(string _name, const Expr& _i1, Type _type = Unknown) :
			Var(_name, _type), i1(_i1.clone())
	{
	}

	virtual ~Var1Index()
	{
	}

	virtual Id id() const
	{
		return IdVar1Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPVar1Index(";
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		GenMIP ri1 = i1.toMIP();
		stringstream ss;
		r.before = ri1.before;
		ss << name << "[" << ri1.now << "]";
		r.now = ss.str();
		r.after = ri1.after;
		return r;
	}

	virtual Var& cloneVar() const
	{
		return *new Var1Index(name, i1, type);
	}
};

class Var2Index: public Var
{
protected:
	Expr& i1;
	Expr& i2;
public:

	Var2Index(string _name, const Expr& _i1, const Expr& _i2, Type _type = Unknown) :
			Var(_name, _type), i1(_i1.clone()), i2(_i2.clone())
	{
	}

	virtual ~Var2Index()
	{
	}

	virtual Id id() const
	{
		return IdVar2Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPVar2Index(";
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		stringstream ss;
		stringstream ssbef;
		stringstream ssaft;

		GenMIP ri1 = i1.toMIP();
		GenMIP ri2 = i2.toMIP();

		ssbef << ri1.before;
		ssbef << ri2.before;
		r.before = ssbef.str();

		ss << name << "[" << ri1.now << "][" << ri2.now << "]";
		r.now = ss.str();

		ssaft << ri1.after;
		ssaft << ri2.after;

		r.after = ssaft.str();
		return r;
	}

	virtual Var& cloneVar() const
	{
		return *new Var2Index(name, i1, i2, type);
	}
};

class Var3Index: public Var
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
public:

	Var3Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, Type _type = Unknown) :
			Var(_name, _type), i1(_i1.clone()), i2(_i2.clone()), i3(_i3.clone())
	{
	}

	virtual ~Var3Index()
	{
	}

	virtual Id id() const
	{
		return IdVar3Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPVar3Index(";
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual Var& cloneVar() const
	{
		return *new Var3Index(name, i1, i2, i3, type);
	}
};

class Var4Index: public Var
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
public:

	Var4Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4, Type _type = Unknown) :
			Var(_name, _type), i1(_i1.clone()), i2(_i2.clone()), i3(_i3.clone()), i4(_i4.clone())
	{
	}

	virtual ~Var4Index()
	{
	}

	virtual Id id() const
	{
		return IdVar4Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPVar4Index(";
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual Var& cloneVar() const
	{
		return *new Var4Index(name, i1, i2, i3, i4, type);
	}
};

class Var5Index: public Var
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
	Expr& i5;
public:

	Var5Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4, const Expr& _i5, Type _type = Unknown) :
			Var(_name, _type), i1(_i1.clone()), i2(_i2.clone()), i3(_i3.clone()), i4(_i4.clone()), i5(_i5.clone())
	{
	}

	virtual ~Var5Index()
	{
	}

	virtual Id id() const
	{
		return IdVar5Index;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPVar5Index(";
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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
		ss << name << "_{" << i1.toLatex() << "," << i2.toLatex() << "," << i3.toLatex() << "," << i4.toLatex() << i5.toLatex() << "}";
		return ss.str();
	}

	virtual Var& cloneVar() const
	{
		return *new Var5Index(name, i1, i2, i3, i4, i5, type);
	}
};

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
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		r.now = name;
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
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		GenMIP ri1 = i1.toMIP();
		stringstream ss;
		r.before = ri1.before;
		ss << name << "[" << ri1.now << "]";
		r.now = ss.str();
		r.after = ri1.after;
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
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		stringstream ss;
		stringstream ssbef;
		stringstream ssaft;

		GenMIP ri1 = i1.toMIP();
		GenMIP ri2 = i2.toMIP();

		ssbef << ri1.before;
		ssbef << ri2.before;
		r.before = ssbef.str();

		ss << name << "[" << ri1.now << "][" << ri2.now << "]";
		r.now = ss.str();

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
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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
		if(isInteger())
			ss << "Integer,";
		else if(isBinary())
			ss << "Binary,";
		else if(isReal())
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

class Op: public Expr
{
protected:
	char op;
	Expr& e1;
	Expr& e2;

public:
	Op(const Expr& _e1, char _op, const Expr& _e2) :
			e1(_e1.clone()), op(_op), e2(_e2.clone())
	{
		if((op != '+') && (op != '-') && (op != '*') && (op != '/'))
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
		if(br)
			ss << "\\left(";
		ss << e1.toLatex() << " ";
		if(op == '*')
			ss << "\\times";
		else
			ss << op;

		ss << " " << e2.toLatex();
		if(br)
			ss << "\\right)";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		stringstream ss;
		stringstream ssbef;
		stringstream ssaft;

		GenMIP r1 = e1.toMIP();
		ssbef << r1.before;
		ssaft << r1.after;
		GenMIP r2 = e2.toMIP();
		ssbef << r2.before;
		ssaft << r2.after;

		ss << "(" << r1.now << " " << op << " " << r2.now << ") ";
		if(r1.now == "")
			ss << "ERROR(EMPTY '" << e1.toString() << "')";
		if(r2.now == "")
			ss << "ERROR(EMPTY '" << e2.toString() << "')";

		r.before = ssbef.str();
		r.after  = ssaft.str();
		r.now    = ss.str();

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
		for(unsigned i = 0; i < mop.list.size(); ++i)
			list.push_back(make_pair(mop.list[i].first, &mop.list[i].second->clone()));
	}

	virtual ~MultiOp()
	{
	}

	MultiOp& add(char op, const Expr& e)
	{
		if((op != '+') && (op != '-') && (op != '*') && (op != '/'))
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
		for(unsigned i = 0; i < list.size(); i++)
			ss << " " << list[i].first << " " << list[i].second->toString();
		ss << " ) ";

		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		if(br)
			ss << "\\left(";
		ss << first.toLatex() << " ";
		for(unsigned i = 0; i < list.size(); ++i)
			ss << list[i].first << " " << list[i].second->toLatex() << " ";
		if(br)
			ss << "\\right)";
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return *new MultiOp(*this);
	}
};

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
	string op;
	Expr& e1;
	Expr& e2;
public:

	Comp(const Expr& _e1, string _op, const Expr& _e2) :
			e1(_e1.clone()), op(_op), e2(_e2.clone())
	{
		if((op != "!=") && (op != "=") && (op != ">") && (op != "<"))
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
		if(br)
			ss << "\\left(";
		ss << e1.toLatex() << " " << op << e2.toLatex();
		if(br)
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
	Comp& e2;
	string op;
public:

	BoolOp(Comp& _e1, string _op, Comp& _e2) :
			e1(_e1), op(_op), e2(_e2)
	{
		if((op != "and") && (op != "or"))
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

class Set
{
protected:
	string name;

public:

	Set(string _name) :
			name(_name)
	{
	}

	virtual ~Set()
	{
	}

	virtual Id id() const
	{
		return IdSet;
	}

	string getName() const
	{
		return name;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSet('" << name << "') ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << " ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		r.now = name;
		return r;
	}

	virtual Set& clone() const
	{
		return *new Set(name);
	}
};


// TODO: create MIPRange{n1..n2} : Set

class SetElem: public Set
{
protected:
	Expr& elem;

public:

	SetElem(const Expr& _elem) :
			Set("anonSet"), elem(_elem.clone())
	{
	}

	virtual ~SetElem()
	{
	}

	virtual Id id() const
	{
		return IdSetElem;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSetElem({" << elem.toString() << "}) ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\{" << elem.toLatex() << " \\} ";
		return ss.str();
	}

	virtual Set& clone() const
	{
		return *new SetElem(elem);
	}
};

class SetCard: public Expr
{
protected:
	Set& s1;

public:
	// cardinality
	SetCard(const Set& _s1) :
			s1(_s1.clone())
	{
	}

	virtual ~SetCard()
	{
	}

	virtual Id id() const
	{
		return IdSetCard;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSetCard(|" << s1.toString() << "|) ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "|" << s1.toLatex() << "|";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		stringstream ss;
		ss << s1.getName() << ".size() ";
		r.now = ss.str();
		return r;
	}

	virtual Expr& clone() const
	{
		return *new SetCard(s1);
	}
};

class SetOp: public Set
{
protected:
	Set& s1;
	string op;
	Set& s2;

public:

	SetOp(const Set& _s1, string _op, const Set& _s2) :
			Set(""), s1(_s1.clone()), op(_op), s2(_s2.clone())
	{
		if((op != "U") && (op != "-") && (op != "\\") && (op != "C") && (op != "C="))
		{
			cout << "UNKNOWN SET OPERATION '" << op << "'" << endl;
			exit(1);
		}
	}

	virtual ~SetOp()
	{
	}

	virtual Id id() const
	{
		return IdSetOp;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSetOp(" << s1.toString() << " " << op << " " << s2.toString() << ") ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		if(br)
			ss << "\\left(";

		ss << s1.toLatex() << " ";

		if(op == "U")
			ss << "\\cup ";
		else if(op == "-")
			ss << "- ";
		else if(op == "\\")
			ss << "\\setminus ";
		else if(op == "C")
			ss << "\\subset ";
		else if(op == "C=")
			ss << "\\subseteq ";

		ss << s2.toLatex();

		if(br)
			ss << " \\right) ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		stringstream ss;
		cout << "TODO: IMPLEMENT setOp toMIP()!" << endl;
		exit(1);
		r.now = ss.str();
		return r;
	}

	virtual Set& clone() const
	{
		return *new SetOp(s1, op, s2);
	}
};

class Sum: public Expr
{
public: // TODO: protect
	Expr& body;

public:
	Sum(const Expr& _body, string exprName="") :
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
public: // protect
	Index& v;
	Set& s;
	Boolean& st; // such that

public:
	SumIn(const Index& _v, const Set& _s, const Expr& body, string exprName="") :
			Sum(body, exprName), v(_v.cloneIndex()), s(_s.clone()), st(*new Boolean)
	{
	}

	SumIn(const Index& _v, const Set& _s, const Expr& body, const Boolean& _st, string exprName="") :
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;

		stringstream ssbefore;
		stringstream ssnow;
		stringstream ssafter;

		GenMIP rs = s.toMIP();
		ssbefore << rs.before;
		ssafter  << rs.after;

		GenMIP rbody = body.toMIP();
		ssbefore << rbody.before;
		ssafter  << rbody.after;

		ssbefore << "{\nIloExpr _sumin(env);\n";
		ssbefore << "for(";
		if(v.type == Integer)
			ssbefore << "int";
		else if(v.type == Binary)
			ssbefore << "bool";
		else
			ssbefore << "double";
 		ssbefore << " " << v.indexToMIP() << ": " << rs.now << ")\n";
		ssbefore << "\t_sumin += " << rbody.now << ";\n";
		if(rbody.now == "")
			ssbefore << "ERROR(EMPTY '" << body.toString() << "')";

		ssnow << "_sumin";
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
public: // TODO: protect
	Index& v;
	Expr& begin;
	Expr& end;
	Boolean& st; // such that
public:

	SumTo(const SumIn& sin, int start = 0) :
		Sum(sin.body, sin.exprName), v(sin.v.cloneIndex()), begin(* new Num(start)), end(start==0?(Expr&)* new Op(SetCard(sin.s), '-', Num(1)):(Expr&)* new SetCard(sin.s)), st(sin.st.clone())
	{
	}

	SumTo(const Index& _v, const Expr& _begin, const Expr& _end, const Expr& body, string exprName="") :
			Sum(body, exprName), v(_v.cloneIndex()), begin(_begin.clone()), end(_end.clone()), st(*new Boolean)
	{
	}

	SumTo(const Index& _v, const Expr& _begin, const Expr& _end, const Expr& body, const Boolean& _st, string exprName="") :
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

	virtual GenMIP toMIP() const
	{
		GenMIP r;

		stringstream ssbefore;
		stringstream ssnow;
		stringstream ssafter;

		GenMIP rb = begin.toMIP();
		ssbefore << rb.before;
		ssafter  << rb.after;

		GenMIP re = end.toMIP();
		ssbefore << re.before;
		ssafter  << re.after;

		GenMIP rbody = body.toMIP();
		ssbefore << rbody.before;
		ssafter  << rbody.after;

		ssbefore << "{\nIloExpr _sumto(env);\n";
		ssbefore << "for(";
		if(v.type == Integer)
			ssbefore << "int";
		else if(v.type == Binary)
			ssbefore << "bool";
		else
			ssbefore << "double";
 		ssbefore << " " << v.indexToMIP() << " = " << rb.now << "; " << v.indexToMIP() << " <= " << re.now << "; ++" << v.indexToMIP() << ")\n";
		ssbefore << "{\n\t_sumto += " << rbody.now << ";\n}\n";
		if(rbody.now == "")
			ssbefore << "ERROR(EMPTY '" << body.toString() << "')";

		ssnow << "_sumto";
		ssafter << "}\n";

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
public://protected:
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
		if(st.id() != IdBool)
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
		ssafter  << rs.after;

		ssbefore << "for(";
		if(v.type == Integer)
			ssbefore << "int";
		else if(v.type == Binary)
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
public://protected:
	Index& v;
	Expr& begin;
	Expr& end;
	Boolean& st; // such that
public:

	ForAllTo(const ForAllIn& sin, int start = 0) :
		v(sin.v.cloneIndex()), begin(* new Num(start)), end(start==0?(Expr&)* new Op(SetCard(sin.s), '-', Num(1)):(Expr&)* new SetCard(sin.s)), st(sin.st.clone())
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
		if(st.id() != IdBool)
			ss << "|" << st.toLatex() << " ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;

		stringstream ssbefore;
		stringstream ssafter;

		GenMIP rb = begin.toMIP();
		ssbefore << rb.before;
		ssafter  << rb.after;

		GenMIP re = end.toMIP();
		ssbefore << re.before;
		ssafter  << re.after;

		ssbefore << "for(";
		if(v.type == Integer)
			ssbefore << "int";
		else if(v.type == Binary)
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
		if(signal == '=')
			ss << "=";
		else if(signal == '<')
			ss << "\\leq";
		else if(signal == '>')
			ss << "\\geq";

		ss << " & " << rhs.toLatex(false) << " & " << fa.toLatex();
		if(name != "")
			ss << " \\label{eq:" << name << "} ";
		if(linebreak)
			ss << " \\\\";

		return ss.str();
	}

	virtual string toMIP() const
	{
		if(name == "")
			return "";

		stringstream ss;

		GenMIP retFA = fa.toMIP();
		ss << retFA.before;
		// unused retFA.now

		GenMIP retRhs = rhs.toMIP();
		ss << retRhs.before;
		if(retRhs.now == "")
			ss << "MIPCons::toMIP:ERROR! empty rhs.now = '" << rhs.toString() << "'" << endl;

		ss << "IloExpr " << name << "(env);\n";
		ss << retRhs.after;

		GenMIP retLhs = lhs.toMIP();
		ss << retLhs.before;
		if(retLhs.now == "")
			ss << "MIPCons::toMIP:ERROR! empty lhs.now = '" << lhs.toString() << "'" << endl;

		ss << name << " += " << retLhs.now << ";\n";
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
		for(unsigned i=0; i < ifelse.vif.size(); ++i)
			vif.push_back(&ifelse.vif[i]->clone());
		for(unsigned i=0; i < ifelse.velse.size(); ++i)
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
		for(unsigned i = 0; i < vif.size(); i++)
			ss << vif[i]->toString() << " ";
		ss << " } else { " << endl;
		for(unsigned i = 0; i < velse.size(); i++)
			ss << vif[i]->toString() << " ";
		ss << " } ";

		return ss.str();
	}

	virtual string toLatex() const
	{
		stringstream ss;
		ss << "If $" << condition.toLatex() << "$ then: \\\n";
		ss << "\\begin{align}\n";
		for(int i = 0; i < ((int) vif.size()); ++i)
			ss << vif[i]->toLatex(i != ((int) vif.size()) - 1) << endl;
		ss << "\\end{align}\n";

		if(velse.size() == 0)
			return ss.str();

		ss << "Else: \\\n";
		ss << "\\begin{align}\n";
		for(int i = 0; i < ((int) velse.size()); ++i)
			ss << velse[i]->toLatex(i != ((int) velse.size()) - 1) << endl;
		ss << "\\end{align}\n";

		return ss.str();
	}

	virtual IfElse& clone() const
	{
		return * new IfElse(*this);
	}
};

class Modeler
{
protected:
	ProblemType type;
	Expr* obj;
	vector<Cons*> constraints;
	vector<IfElse*> condCons;

	vector<Par*> dependPar;
	vector<Set*> dependSet;
	vector<Var*> dependVar;

public:

	Modeler(const Modeler& model) :
			type(model.type)
	{
		obj = model.obj;
		if(model.obj)
			obj = &model.obj->clone();
		for(unsigned i = 0; i < model.constraints.size(); ++i)
			constraints.push_back(&model.constraints[i]->clone());
		for(unsigned i = 0; i < model.condCons.size(); ++i)
			condCons.push_back(&model.condCons[i]->clone());
		for(unsigned i = 0; i < model.dependPar.size(); ++i)
			dependPar.push_back(&model.dependPar[i]->clonePar());
		for(unsigned i = 0; i < model.dependVar.size(); ++i)
			dependVar.push_back(&model.dependVar[i]->cloneVar());
		for(unsigned i = 0; i < model.dependSet.size(); ++i)
			dependSet.push_back(&model.dependSet[i]->clone());
	}

	Modeler(ProblemType _type) :
			type(_type), obj(NULL)
	{
	}

	Modeler(ProblemType _type, const Expr& _obj) :
			type(_type), obj(&_obj.clone())
	{
	}

	virtual ~Modeler()
	{
	}

	Modeler& setObj(const Expr& _obj)
	{
		if(obj)
			delete obj;

		obj = &_obj.clone();

		return *this;
	}

	Modeler& addCons(const Cons& cons)
	{
		constraints.push_back(&cons.clone());
		return *this;
	}

	Modeler& addCondCons(const IfElse& cond)
	{
		condCons.push_back(&cond.clone());
		return *this;
	}

	Modeler& depend(const Par& p)
	{
		dependPar.push_back(&p.clonePar());
		return *this;
	}

	Modeler& depend(const Var& v)
	{
		dependVar.push_back(&v.cloneVar());
		return *this;
	}

	Modeler& depend(const Set& s)
	{
		dependSet.push_back(&s.clone());
		return *this;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPModel(";
		if(type == Minimize)
			ss << "Minimize";
		else
			ss << "Maximize";

		if(!obj)
		{
			ss << " !NO-OBJECTIVE)";
			return ss.str();
		}

		ss << " { " << obj->toString() << "} " << endl;
		ss << " subject to: {" << endl;
		for(unsigned i = 0; i < constraints.size(); ++i)
			ss << constraints[i]->toString() << endl;
		ss << "})";

		return ss.str();
	}

	virtual string toLatex() const
	{
		if(!obj)
			return "";

		stringstream ss;
		ss << "\\begin{equation}\n";

		if(type == Minimize)
			ss << "min: ";
		else
			ss << "max: ";
		ss << obj->toLatex() << " ";
		if(obj->exprName != "")
			ss << "\\label{eq:" << obj->exprName << "}";
		ss << "\n\\end{equation}\n\n";

		ss << "\\begin{align}\n";
		for(int i = 0; i < ((int) constraints.size()); ++i)
			ss << constraints[i]->toLatex(i != ((int) constraints.size()) - 1) << endl;
		ss << "\\end{align}\n";

		for(unsigned j=0; j<condCons.size(); ++j)
			ss << condCons[j]->toLatex() << endl;

		return ss.str();
	}

	virtual string toConcertOld() const
	{

		stringstream ss;
		ss << "MIPModel model(";
		if(type == Minimize)
			ss << "MIPMinimize";
		else
			ss << "MIPMaximize";
		ss << ");\n\n";

		for(unsigned i=0; i<dependPar.size(); i++)
			ss << "// depend on parameter '" << dependPar[i]->toString() << "'" << endl;
		for(unsigned i=0; i<dependVar.size(); i++)
			ss << "// depend on variable '" << dependVar[i]->toString() << "'" << endl;
		for(unsigned i=0; i<dependSet.size(); i++)
			ss << "// depend on set '" << dependSet[i]->toString() << "'" << endl;
		ss << endl;


		return ss.str();
	}

	virtual string toMIP() const
	{
		if(obj->exprName == "")
		{
			cout << "ERROR! EMPTY NAME FOR OBJ" << endl;
			exit(1);
			return "";
		}

		stringstream ss;
		ss << "IloEnv env;\n";
		ss << "IloModel model(env);\n\n";
		ss << "IloExpr " << obj->exprName << "(env);\n";

		ss << "// " << obj->toLatex() << endl;
		GenMIP exprobj = obj->toMIP();
		ss << exprobj.before;
		ss << obj->exprName << " += " << exprobj.now << ";\n";
		ss << exprobj.after;

		ss << "\n";
		ss << "model.add(";
		if(type == Minimize)
			ss << "IloMinimize";
		else
			ss << "IloMaximize";

		ss << "(env, " << obj->exprName << "));\n\n";


		for(unsigned i=0; i<constraints.size(); i++)
		{
			ss << "// constraints: " << constraints[i]->toLatex(false) << endl; 
			ss << constraints[i]->toMIP() << endl;
		}

		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}

	virtual Modeler& clone() const
	{
		return *new Modeler(*this);
	}
};

// defining const expression
typedef const Expr& EXPR;
typedef const Index& INDEX;
typedef const Var& VAR;
typedef const Par& PAR;
typedef const Boolean& BOOLEAN;
typedef const Set& SET;
typedef const ForAll& FORALL;
typedef const Cons& CONS;
typedef const IfElse& IFELSE;
typedef const Modeler& MODELER;

}

#endif

