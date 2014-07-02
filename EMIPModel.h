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

enum Id { IdExpr, IdVar, IdVar1Index, IdVar2Index, IdVar3Index, IdVar4Index, IdVar5Index, IdPar, IdPar1Index, IdPar2Index, IdPar3Index, IdPar4Index, IdPar5Index, IdNum, IdOp, IdMultiOp, IdComp, IdBoolOp, IdSet, IdSetOp, IdSum, IdSumIn, IdSumTo, IdForAll, IdForAllIn, IdForAllTo, IdCons, IdIfElse };

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


class MultiOp : public Expr
{
protected:
	Expr first;
	vector<pair<char, Expr> > list;
public:
	MultiOp(Expr _first) :
		first(_first)
	{

	}

	virtual ~MultiOp()
	{
	}

	MultiOp& add(char op, Expr e)
	{
		if((op != '+') && (op != '-') && (op != '*') && (op != '/'))
		{
			cout << "ERROR: UNKNOWN OPERATION '" << op << "'" << endl;
			exit(1);
		}
		list.push_back(make_pair(op, e));
		return *this;
	}

	virtual Id id() const
	{
		return IdMultiOp;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPMultiOp(SIZE=" << list.size() << "; " << first.toString();
		for(unsigned i=0; i<list.size(); i++)
			ss << " " << list[i].first << " " << list[i].second.toString();
		ss << " ) ";
		
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


class BoolOp : public Comp
{
protected:
	Comp e1;
	Comp e2;
	string op;
public:

	BoolOp(string _op, Comp _e1) :
		e1(_e1), op(_op)
	{
		if((op != "!"))
		{
			cout << "ERROR! UNKNOWN BoolOp '" << op << "'" << endl;
			exit(1);
		}
	}

	BoolOp(Comp _e1, string _op, Comp _e2) :
		e1(_e1), op(_op), e2(_e2)
	{
		if((op != "&&") && (op != "||"))
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

	string toString() const
	{
		stringstream ss;
		ss << "EMIPBoolOp(" << e1.toString() << " " << op << " " << e2.toString() << ") ";
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
	// cardinality
	SetOp(string _op, Set _s1) :
		s1(_s1), op(_op)
	{
		if((op != "|"))
		{
			cout << "UNKNOWN SET OPERATION '" << op << "'" << endl;
			exit(1);
		}
	}


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
		ss << "EMIPSum({" << body.toString() << "}) ";
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
		ss << "EMIPSumIn(" << v.toString() << " in " << s.toString() << "{" << Sum::body.toString() << "}) ";
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
		ss << "EMIPSumTo(" << v.toString() << " <- " << begin.toString() << " to " << end.toString() << "{ " << Sum::body.toString() << "}) ";
		return ss.str();
	}
};


class ForAll
{
protected:
	vector<ForAll> list;
public:
	ForAll()
	{
	}

	ForAll& add(ForAll fa)
	{
		list.push_back(fa);
		return *this;
	}

	virtual ~ForAll()
	{
	}

	virtual Id id() const
	{
		return IdForAll;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPForAll(" << list.size() << "){";
		for(unsigned i=0; i<list.size(); i++)
			ss << list[i].toString() << " ";
		ss << "} ";
		return ss.str();
	}
};


class ForAllIn : public ForAll
{
protected:
	Var v;
	Set s;
	Comp st; // such that
public:
	ForAllIn(Var _v, Set _s) :
		v(_v), s(_s)
	{
	}

	ForAllIn(Var _v, Set _s, Comp _st) :
		v(_v), s(_s), st(_st)
	{
	}

	virtual ~ForAllIn()
	{
	}

	virtual Id id() const
	{
		return IdForAllIn;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPForAllIn(" << v.toString() << " in " << s.toString() << ") ";
		return ss.str();
	}
};


class ForAllTo : public ForAll
{
protected:
	Var v;
	Expr begin;
	Expr end;
	Comp st; // such that
public:
	ForAllTo(Var _v, Expr _begin, Expr _end) :
		v(_v), begin(_begin), end(_end)
	{
	}

	ForAllTo(Var _v, Expr _begin, Expr _end, Comp _st) :
		v(_v), begin(_begin), end(_end), st(_st)
	{
	}

	virtual ~ForAllTo()
	{
	}

	virtual Id id() const
	{
		return IdForAllTo;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPForAllTo(" << v.toString() << " <- " << begin.toString() << " to " << end.toString() << ") ";
		return ss.str();
	}
};


class Cons
{
protected:
	ForAll fa;
	Expr lhs;
	char signal;
	Expr rhs;
public:

	Cons()
	{
	}

	Cons(ForAll _fa, Expr _lhs, char _signal, Expr _rhs) :
		fa(_fa), lhs(_lhs), signal(_signal), rhs(_rhs)
	{
	}

	virtual ~Cons()
	{
	}

	virtual Id id() const
	{
		return IdCons;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPCons(" << fa.toString() << ": " << lhs.toString() << " '" << signal << "' " << rhs.toString() << ") ";
		return ss.str();
	}
};



class IfElse : public Cons
{
protected:
	Comp condition;
	vector<Cons> vif;
	vector<Cons> velse;
public:
	IfElse(Comp _condition) :
		condition(_condition)
	{
	}

	virtual ~IfElse()
	{
	}

	IfElse& addIf(Cons cons)
	{
		vif.push_back(cons);
		return *this;
	}

	IfElse& addElse(Cons cons)
	{
		velse.push_back(cons);
		return *this;
	}

	virtual Id id() const
	{
		return IdIfElse;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPIfElse(if(" << condition.toString() << ") { ";
		for(unsigned i=0; i<vif.size(); i++)
			ss << vif[i].toString() << " ";
		ss << " } else { " << endl;
		for(unsigned i=0; i<velse.size(); i++)
			ss << vif[i].toString() << " ";
		ss << " } ";

		return ss.str();
	}
};



class Model
{
protected:
	ProblemType type;
	Expr obj;
	vector<Cons> constraints;

public:

	Model(ProblemType _type, Expr _obj) :
		type(_type), obj(_obj)
	{
	}

	Model(ProblemType _type) :
		type(_type)
	{
	}

	virtual ~Model()
	{
	}

	Model& setObj(Expr _obj)
	{
		obj = _obj;
		return *this;
	}

	Model& addCons(Cons cons)
	{
		constraints.push_back(cons);
		return *this;
	}

	string toString() const
	{
		stringstream ss;
		ss << "EMIPModel(";
		if(type == Minimize)
			ss << "Minimize";
		else
			ss << "Maximize";
		ss << " { " << obj.toString() << "} subject to: {" << endl;
		for(unsigned i=0; i<constraints.size(); ++i)
			ss << constraints[i].toString() << endl;
		ss << "})";

		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}
};


}



#endif

