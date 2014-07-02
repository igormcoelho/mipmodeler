// ==================================================
// Class for MIP modeling and automatic code deriving
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - LGPLv3
// ==================================================

#ifndef EMIPMODEL_HPP
#define EMIPMODEL_HPP

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

enum ProblemType { Minimize, Maximize };

enum VarType { Real, Binary, Integer }; // (?)

enum Id { IdExpr, IdVar, IdVar1Index, IdVar2Index, IdVar3Index, IdVar4Index, IdVar5Index, IdPar, IdPar1Index, IdPar2Index, IdPar3Index, IdPar4Index, IdPar5Index, IdNum, IdOp, IdComp, IdAnd, IdOr, IdSet, IdSetOp, IdSum, IdSumIn, IdSumTo };

class Expr
{
public:

	virtual Id id() const
	{
		return IdExpr;
	}

	virtual string toString() const
	{
		return "IdExpr ";
	}

	virtual void print() const
	{
		std::cout << toString() << std::endl;
	}
};

class Num : public Expr
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

	string toString() const
	{
		stringstream ss;
		ss << "EMIPNum(" << d << ")";
		return ss.str();
	}
};


class Var : public Expr
{
protected:
	VarType type;
	string name;
public:

	Var(string _name, VarType _type = Real) :
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

	string toString() const
	{
		stringstream ss;
		ss << "EMIPVar(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";

		return ss.str();
	}
};

class Var1Index : public Var
{
protected:
	Expr i1;
public:

	Var1Index(string _name, Expr _i1, VarType _type = Real) :
		Var(_name, _type), i1(_i1)
	{
	}

	virtual ~Var1Index()
	{
	}

	virtual Id id() const
	{
		return IdVar1Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPVar1Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "] ";

		return ss.str();
	}
};

class Var2Index : public Var
{
protected:
	Expr i1;
	Expr i2;
public:

	Var2Index(string _name, Expr _i1, Expr _i2, VarType _type = Real) :
		Var(_name, _type), i1(_i1), i2(_i2)
	{
	}

	virtual ~Var2Index()
	{
	}

	virtual Id id() const
	{
		return IdVar2Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPVar2Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "] ";
		return ss.str();
	}
};

class Var3Index : public Var
{
protected:
	Expr i1;
	Expr i2;
	Expr i3;
public:

	Var3Index(string _name, Expr _i1, Expr _i2, Expr _i3, VarType _type = Real) :
		Var(_name, _type), i1(_i1), i2(_i2), i3(_i3)
	{
	}

	virtual ~Var3Index()
	{
	}

	virtual Id id() const
	{
		return IdVar3Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPVar3Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "] ";
		return ss.str();
	}
};


class Var4Index : public Var
{
protected:
	Expr i1;
	Expr i2;
	Expr i3;
	Expr i4;
public:

	Var4Index(string _name, Expr _i1, Expr _i2, Expr _i3, Expr _i4, VarType _type = Real) :
		Var(_name, _type), i1(_i1), i2(_i2), i3(_i3), i4(_i4)
	{
	}

	virtual ~Var4Index()
	{
	}

	virtual Id id() const
	{
		return IdVar4Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPVar4Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "]";
		ss << "[" << i4.toString() << "] ";
		return ss.str();
	}
};


class Var5Index : public Var
{
protected:
	Expr i1;
	Expr i2;
	Expr i3;
	Expr i4;
	Expr i5;
public:

	Var5Index(string _name, Expr _i1, Expr _i2, Expr _i3, Expr _i4,  Expr _i5, VarType _type = Real) :
		Var(_name, _type), i1(_i1), i2(_i2), i3(_i3), i4(_i4), i5(_i5)
	{
	}

	virtual ~Var5Index()
	{
	}

	virtual Id id() const
	{
		return IdVar5Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPVar5Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "]";
		ss << "[" << i4.toString() << "]";
		ss << "[" << i5.toString() << "] ";
		return ss.str();
	}
};


class Par : public Expr
{
protected:
	VarType type;
	string name;
public:

	Par(string _name, VarType _type = Real) :
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

	string toString() const
	{
		stringstream ss;
		ss << "EMIPPar(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";

		return ss.str();
	}
};

class Par1Index : public Par
{
protected:
	Expr i1;
public:

	Par1Index(string _name, Expr _i1, VarType _type = Real) :
		Par(_name, _type), i1(_i1)
	{
	}

	virtual ~Par1Index()
	{
	}

	virtual Id id() const
	{
		return IdPar1Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPPar1Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "] ";

		return ss.str();
	}
};

class Par2Index : public Par
{
protected:
	Expr i1;
	Expr i2;
public:

	Par2Index(string _name, Expr _i1, Expr _i2, VarType _type = Real) :
		Par(_name, _type), i1(_i1), i2(_i2)
	{
	}

	virtual ~Par2Index()
	{
	}

	virtual Id id() const
	{
		return IdPar2Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPPar2Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "] ";
		return ss.str();
	}
};

class Par3Index : public Par
{
protected:
	Expr i1;
	Expr i2;
	Expr i3;
public:

	Par3Index(string _name, Expr _i1, Expr _i2, Expr _i3, VarType _type = Real) :
		Par(_name, _type), i1(_i1), i2(_i2), i3(_i3)
	{
	}

	virtual ~Par3Index()
	{
	}

	virtual Id id() const
	{
		return IdPar3Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPPar3Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "] ";
		return ss.str();
	}
};


class Par4Index : public Par
{
protected:
	Expr i1;
	Expr i2;
	Expr i3;
	Expr i4;
public:

	Par4Index(string _name, Expr _i1, Expr _i2, Expr _i3, Expr _i4, VarType _type = Real) :
		Par(_name, _type), i1(_i1), i2(_i2), i3(_i3), i4(_i4)
	{
	}

	virtual ~Par4Index()
	{
	}

	virtual Id id() const
	{
		return IdPar4Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPPar4Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "]";
		ss << "[" << i4.toString() << "] ";
		return ss.str();
	}
};


class Par5Index : public Par
{
protected:
	Expr i1;
	Expr i2;
	Expr i3;
	Expr i4;
	Expr i5;
public:

	Par5Index(string _name, Expr _i1, Expr _i2, Expr _i3, Expr _i4,  Expr _i5, VarType _type = Real) :
		Par(_name, _type), i1(_i1), i2(_i2), i3(_i3), i4(_i4), i5(_i5)
	{
	}

	virtual ~Par5Index()
	{
	}

	virtual Id id() const
	{
		return IdPar5Index;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPPar5Index(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << ",'" << name << "')";
		ss << "[" << i1.toString() << "]";
		ss << "[" << i2.toString() << "]";
		ss << "[" << i3.toString() << "]";
		ss << "[" << i4.toString() << "]";
		ss << "[" << i5.toString() << "] ";
		return ss.str();
	}
};

class Op : public Expr
{
protected:
	char op;
	Expr e1;
	Expr e2;
public:
	Op(Expr _e1, char _op, Expr _e2) :
		e1(_e1), op(_op), e2(_e2)
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

	string toString() const
	{
		stringstream ss;
		ss << "EMIPOp(" << e1.toString() << " " << op << " " << e2.toString() << ") ";
		return ss.str();
	}
};


class Comp : public Expr
{
protected:
	string op;
	Expr e1;
	Expr e2;
public:

	// to allow later instantiation of derived classes (strange C++...)
	Comp()
	{
	}

	Comp(Expr _e1, string _op, Expr _e2) :
		e1(_e1), op(_op), e2(_e2)
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

	string toString() const
	{
		stringstream ss;
		ss << "EMIPComp(" << e1.toString() << " " << op << " " << e2.toString() << ") ";
		return ss.str();
	}
};


class And : public Comp
{
protected:
	Comp e1;
	Comp e2;
public:
	And(Comp _e1, Comp _e2) :
		e1(_e1), e2(_e2)
	{
	}

	virtual ~And()
	{
	}

	virtual Id id() const
	{
		return IdAnd;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPAnd(" << e1.toString() << " AND " << e2.toString() << ") ";
		return ss.str();
	}
};


class Or : public Comp
{
protected:
	Comp e1;
	Comp e2;
public:
	Or(Comp _e1, Comp _e2) :
		e1(_e1), e2(_e2)
	{
	}

	virtual ~Or()
	{
	}

	virtual Id id() const
	{
		return IdOr;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPOr(" << e1.toString() << " OR " << e2.toString() << ") ";
		return ss.str();
	}
};


class Set
{
protected:
	string name;
	Expr unitary;

public:

	// C++ crazy programming reasons...
	Set()
	{
		name = "";
	}

	Set(string _name) :
		name(_name)
	{
	}

	Set(Expr _un) :
		name(""), unitary(_un)
	{
	}

	virtual ~Set()
	{
	}

	virtual Id id() const
	{
		return IdSet;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPSet('" << name << "' || unitary:{" << unitary.toString() << "}) ";
		return ss.str();
	}
};


class SetOp : public Set
{
protected:
	Set s1;
	string op;
	Set s2;

public:
	SetOp(Set _s1, string _op, Set _s2) :
		s1(_s1), op(_op), s2(_s2)
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

	string toString() const
	{
		stringstream ss;
		ss << "EMIPSetOp(" << s1.toString() << " " << op << " " << s2.toString() << ") ";
		return ss.str();
	}
};



class Sum : public Expr
{
protected:
	Expr body;
public:
	Sum(Expr _body) :
		body(_body)
	{
	}

	virtual ~Sum()
	{
	}

	virtual Id id() const
	{
		return IdSum;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPSum{" << body.toString() << "} ";
		return ss.str();
	}
};


class SumIn : public Sum
{
protected:
	Var v;
	Set s;
	Comp st; // such that
public:
	SumIn(Var _v, Set _s, Expr body) :
		Sum(body), v(_v), s(_s)
	{
	}

	SumIn(Var _v, Set _s, Expr body, Comp _st) :
		Sum(body), v(_v), s(_s), st(_st)
	{
	}

	virtual ~SumIn()
	{
	}

	virtual Id id() const
	{
		return IdSumIn;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPSumIn(" << v.toString() << " in " << s.toString() << "{" << Sum::body.toString() << "} ";
		return ss.str();
	}
};


class SumTo : public Sum
{
protected:
	Var v;
	Expr begin;
	Expr end;
	Comp st; // such that
public:
	SumTo(Var _v, Expr _begin, Expr _end, Expr body) :
		Sum(body), v(_v), begin(_begin), end(_end)
	{
	}

	SumTo(Var _v, Expr _begin, Expr _end, Expr body, Comp _st) :
		Sum(body), v(_v), begin(_begin), end(_end), st(_st)
	{
	}

	virtual ~SumTo()
	{
	}

	virtual Id id() const
	{
		return IdSumTo;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPSumTo(" << v.toString() << " <- " << begin.toString() << " to " << end.toString() << " { " << Sum::body.toString() << "} ";
		return ss.str();
	}
};



}





#endif

