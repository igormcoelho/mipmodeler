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

enum VarType { Real, Binary, Integer, Unknown }; // (?)

enum Id { IdExpr, IdVar, IdVar1Index, IdVar2Index, IdVar3Index, IdVar4Index, IdVar5Index, IdPar, IdPar1Index, IdPar2Index, IdPar3Index, IdPar4Index, IdPar5Index, IdNum, IdOp, IdMultiOp, IdComp, IdBoolOp, IdBool, IdNot, IdSet, IdSetElem, IdSetCard, IdSetOp, IdSum, IdSumIn, IdSumTo, IdForAll, IdForAllIn, IdForAllTo, IdCons, IdIfElse };

class Expr
{
public:

	virtual ~Expr()
	{
	}

	virtual Id id() const = 0;

	virtual string toString() const = 0;

	virtual void print() const
	{
		std::cout << toString() << std::endl;
	}

	virtual Expr& clone() const = 0;
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

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPNum(" << d << ")";
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return * new Num(d);
	}
};


class Var : public Expr
{
protected:
	VarType type;
	string name;
public:

	Var(string _name, VarType _type = Unknown) :
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

	virtual Expr& clone() const
	{
		return cloneVar();
	}

	virtual Var& cloneVar() const
	{
		return * new Var(name, type);
	}
};

class Var1Index : public Var
{
protected:
	Expr& i1;
public:

	Var1Index(string _name, const Expr&  _i1, VarType _type = Unknown) :
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

	virtual Var& cloneVar() const
	{
		return * new Var1Index(name, i1, type);
	}
};

class Var2Index : public Var
{
protected:
	Expr& i1;
	Expr& i2;
public:

	Var2Index(string _name, const Expr&  _i1, const Expr&  _i2, VarType _type = Unknown) :
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

	virtual Var& cloneVar() const
	{
		return * new Var2Index(name, i1, i2, type);
	}
};

class Var3Index : public Var
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
public:

	Var3Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, VarType _type = Unknown) :
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

	virtual Var& cloneVar() const
	{
		return * new Var3Index(name, i1, i2, i3, type);
	}
};


class Var4Index : public Var
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
public:

	Var4Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4, VarType _type = Unknown) :
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

	virtual Var& cloneVar() const
	{
		return * new Var4Index(name, i1, i2, i3, i4, type);
	}
};


class Var5Index : public Var
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
	Expr& i5;
public:

	Var5Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4,  const Expr& _i5, VarType _type = Unknown) :
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

	virtual Var& cloneVar() const
	{
		return * new Var5Index(name, i1, i2, i3, i4, i5, type);
	}
};


class Par : public Expr
{
protected:
	VarType type;
	string name;
public:

	Par(string _name, VarType _type = Unknown) :
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

	virtual Expr& clone() const
	{
		return * new Par(name, type);
	}
};

class Par1Index : public Par
{
protected:
	Expr& i1;
public:

	Par1Index(string _name, const Expr& _i1, VarType _type = Unknown) :
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

	virtual Expr& clone() const
	{
		return *new Par1Index(name, i1, type);
	}
};

class Par2Index : public Par
{
protected:
	Expr& i1;
	Expr& i2;
public:

	Par2Index(string _name, const Expr& _i1, const Expr& _i2, VarType _type = Unknown) :
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

	virtual Expr& clone() const
	{
		return *new Par2Index(name, i1, i2, type);
	}
};

class Par3Index : public Par
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
public:

	Par3Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, VarType _type = Unknown) :
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

	virtual Expr& clone() const
	{
		return *new Par3Index(name, i1, i2, i3, type);
	}
};


class Par4Index : public Par
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
public:

	Par4Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4, VarType _type = Unknown) :
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

	virtual Expr& clone() const
	{
		return *new Par4Index(name, i1, i2, i3, i4, type);
	}
};


class Par5Index : public Par
{
protected:
	Expr& i1;
	Expr& i2;
	Expr& i3;
	Expr& i4;
	Expr& i5;
public:

	Par5Index(string _name, const Expr& _i1, const Expr& _i2, const Expr& _i3, const Expr& _i4,  const Expr& _i5, VarType _type = Unknown) :
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

	virtual Expr& clone() const
	{
		return *new Par5Index(name, i1, i2, i3, i4, i5, type);
	}
};

class Op : public Expr
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

	virtual Expr& clone() const
	{
		return *new Op(e1, op, e2);
	}
};


class MultiOp : public Expr
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
		for(unsigned i=0; i<mop.list.size(); ++i)
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
		for(unsigned i=0; i<list.size(); i++)
			ss << " " << list[i].first << " " << list[i].second->toString();
		ss << " ) ";
		
		return ss.str();
	}

	virtual Expr& clone() const
	{
		return *new MultiOp(*this);
	}
};


class Bool
{
public:

	Bool()
	{
	}

	virtual ~Bool()
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

	virtual Bool& clone() const
	{
		return * new Bool;
	}
};



class Comp : public Bool
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

	virtual Bool& clone() const
	{
		return cloneComp();
	}

	virtual Comp& cloneComp() const
	{
		return *new Comp(e1, op, e2);
	}
};




class Not : public Bool
{
protected:
	Bool& e1;
	string op;
public:

	Not(const Bool& _e1) :
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
};


class BoolOp : public Bool
{
protected:
	Comp& e1;
	Comp& e2;
	string op;
public:

	BoolOp(Comp& _e1, string _op, Comp& _e2) :
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

	virtual string toString() const
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

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSet('" << name << "') ";
		return ss.str();
	}

	virtual Set& clone() const
	{
		return * new Set(name);
	}
};


class SetElem : public Set
{
protected:
	Expr& elem;

public:

	SetElem(const Expr& _elem) :
		Set(""), elem(_elem.clone())
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

	virtual Set& clone() const
	{
		return * new SetElem(elem);
	}
};

class SetCard : public Expr
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

	virtual Expr& clone() const
	{
		return * new SetCard(s1);
	}
};



class SetOp : public Set
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

	virtual Set& clone() const
	{
		return * new SetOp(s1, op, s2);
	}
};



class Sum : public Expr
{
protected:
	Expr& body;

public:
	Sum(const Expr& _body) :
		body(_body.clone())
	{
	}

	virtual ~Sum()
	{
	}

	virtual Id id() const
	{
		return IdSum;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSum({" << body.toString() << "}) ";
		return ss.str();
	}

	virtual Expr& clone() const = 0;
};


class SumIn : public Sum
{
protected:
	Var& v;
	Set& s;
	Bool& st; // such that

public:
	SumIn(const Var& _v, const Set& _s, const Expr& body) :
		Sum(body.clone()), v(_v.cloneVar()), s(_s.clone()), st(* new Bool)
	{
	}

	SumIn(const Var& _v, const Set& _s, const Expr& body, const Bool& _st) :
		Sum(body.clone()), v(_v.cloneVar()), s(_s.clone()), st(_st.clone())
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

	virtual Expr& clone() const
	{
		return * new SumIn(v, s, body, st);
	}
};


class SumTo : public Sum
{
protected:
	Var& v;
	Expr& begin;
	Expr& end;
	Bool& st; // such that
public:
	SumTo(const Var& _v, const Expr& _begin, const Expr& _end, const Expr& body) :
		Sum(body.clone()), v(_v.cloneVar()), begin(_begin.clone()), end(_end.clone()), st(* new Bool)
	{
	}

	SumTo(const Var& _v, const Expr& _begin, const Expr& _end, const Expr& body, const Bool& _st) :
		Sum(body.clone()), v(_v.cloneVar()), begin(_begin.clone()), end(_end.clone()), st(_st.clone())
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

	virtual Expr& clone() const
	{
		return *new SumTo(v, begin, end, body, st);
	}
};


class ForAll
{
public:

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

	virtual ForAll& clone() const = 0;
};


class ForAllIn : public ForAll
{
protected:
	Var& v;
	Set& s;
	Bool& st; // such that
public:
	ForAllIn(const Var& _v, const Set& _s) :
		v(_v.cloneVar()), s(_s.clone()), st(* new Bool)
	{
	}

	ForAllIn(const Var& _v, const Set& _s, const Bool& _st) :
		v(_v.cloneVar()), s(_s.clone()), st(_st.clone())
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

	virtual ForAll& clone() const
	{
		return * new ForAllIn(v, s, st);
	}
};


class ForAllTo : public ForAll
{
protected:
	Var& v;
	Expr& begin;
	Expr& end;
	Bool& st; // such that
public:
	ForAllTo(const Var& _v, const Expr& _begin, const Expr& _end) :
		v(_v.cloneVar()), begin(_begin.clone()), end(_end.clone()), st(* new Bool)
	{
	}

	ForAllTo(const Var& _v, const Expr& _begin, const Expr& _end, const Bool& _st) :
		v(_v.cloneVar()), begin(_begin.clone()), end(_end.clone()), st(_st.clone())
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

	virtual ForAll& clone() const
	{
		return * new ForAllTo(v, begin, end, st);
	}
};


class Cons
{
protected:
	ForAll& fa;
	Expr& lhs;
	char signal;
	Expr& rhs;
public:

	Cons(const ForAll& _fa, const Expr& _lhs, char _signal, const Expr& _rhs) :
		fa(_fa.clone()), lhs(_lhs.clone()), signal(_signal), rhs(_rhs.clone())
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
		ss << "EMIPCons(" << fa.toString() << ": " << lhs.toString() << " '" << signal << "' " << rhs.toString() << ") ";
		return ss.str();
	}

	virtual Cons& clone() const
	{
		return * new Cons(fa, lhs, signal, rhs);
	}
};



class IfElse
{
protected:
	Bool& condition;
	vector<Cons*> vif;
	vector<Cons*> velse;
public:
	IfElse(const Bool& _condition) :
		condition(_condition.clone())
	{
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
		for(unsigned i=0; i<vif.size(); i++)
			ss << vif[i]->toString() << " ";
		ss << " } else { " << endl;
		for(unsigned i=0; i<velse.size(); i++)
			ss << vif[i]->toString() << " ";
		ss << " } ";

		return ss.str();
	}
};



class Model
{
protected:
	ProblemType type;
	Expr* obj;
	vector<Cons*> constraints;

public:

	Model(ProblemType _type) :
			type(_type), obj(NULL)
	{
	}

	Model(ProblemType _type, const Expr& _obj) :
		type(_type), obj(&_obj.clone())
	{
	}

	virtual ~Model()
	{
	}

	Model& setObj(const Expr& _obj)
	{
		if(obj)
			delete obj;

		obj = &_obj.clone();

		return *this;
	}

	Model& addCons(const Cons& cons)
	{
		constraints.push_back(&cons.clone());
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
		ss << " { " << obj->toString() << "} subject to: {" << endl;
		for(unsigned i=0; i<constraints.size(); ++i)
			ss << constraints[i]->toString() << endl;
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

