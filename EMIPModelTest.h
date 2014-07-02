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

enum Id { IdExpr, IdVar, IdVar1Index, IdNum, IdOp, IdComp, IdAnd, IdOr };

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

}





#endif

