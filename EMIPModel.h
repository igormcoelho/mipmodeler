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

enum Id { IdExpr, IdVar, IdVar1Index, IdVar2Index, IdVar3Index, IdVar4Index, IdVar5Index, IdNum, IdOp, IdComp, IdAnd, IdOr };

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


class MIPCons
{
protected:
	string name;
	char signal;
	double rhs;
	vector<double> coefs;
	vector<MIPVar*> vars;

public:

	MIPCons(char _signal, double _rhs = 0) :
		name(""), signal(_signal), rhs(_rhs)
	{

		if((signal != '<') && (signal != '=') && (signal != '>'))
		{
			cout << "MIPCons::error! unknown signal '" << signal << "'" << endl;
			exit(1);
		}
	}

	MIPCons(string _name, char _signal, double _rhs = 0) :
		name(_name), signal(_signal), rhs(_rhs)
	{
		if((signal != '<') && (signal != '=') && (signal != '>'))
		{
			cout << "MIPConstraint::error! unknown signal '" << signal << "'" << endl;
			exit(1);
		}
	}

	MIPCons(const MIPCons& cons) :
		name(cons.name), signal(cons.signal), rhs(cons.rhs), coefs(cons.coefs), vars(cons.vars)
	{
	}

	virtual ~MIPCons()
	{
		vars.clear();
		coefs.clear();
	}

	MIPCons& add(double value)
	{
		rhs -= value;
		return *this;
	}

	MIPCons& add(double coef, MIPVar& var)
	{
		coefs.push_back(coef);
		vars.push_back(&var);

		return *this;
	}

	inline string getName() const
	{
		return name;
	}

	inline MIPCons& setName(string _name)
	{
		name = _name;
		return *this;
	}

	inline unsigned getNumVars() const
	{
		return vars.size();
	}

	inline MIPVar& getVar(unsigned index)
	{
		return *vars.at(index);
	}

	inline double getCoef(unsigned index)
	{
		return coefs.at(index);
	}

	inline char getSignal()
	{
		return signal;
	}

	inline double getRHS()
	{
		return rhs;
	}

	void print() const
	{
		cout << toString() << endl;
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPCons('" << name << "'): ";
		for(unsigned i=0; i<coefs.size(); i++)
			ss << (coefs[i]>=0?'+':' ') << coefs[i] << " " << vars[i]->toString() << " ";
		ss << signal << " ";
		ss << rhs;
		return ss.str();
	}
};


class MIPModel
{
protected:
	MIPType type;
	vector<double> coefs;
	vector<MIPVar*> vars;
	vector<MIPCons*> constraints;

	int varIdx;
	int consIdx;

public:

	MIPModel(MIPType _type) :
		type(_type)
	{
		varIdx = 0;
		consIdx = 0;
	}

	virtual ~MIPModel()
	{
		constraints.clear();
		coefs.clear();
		vars.clear();
	}

	MIPModel& add(double coef, MIPVar& var)
	{
		coefs.push_back(coef);
		vars.push_back(&var);

		// auto naming
		if(var.getName() == "")
		{
			varIdx++;
			stringstream ss;
			ss << "var_" << varIdx;
			var.setName(ss.str());
		}
		
		return *this;
	}

	MIPModel& add(MIPCons& cons)
	{
		constraints.push_back(&cons);

		// auto naming
		if(cons.getName() == "")
		{
			consIdx++;
			stringstream ss;
			ss << "cons_" << consIdx;
			cons.setName(ss.str());
		}

		// auto naming
		for(unsigned i=0; i<cons.getNumVars(); i++)
			if(cons.getVar(i).getName() == "")
			{
				varIdx++;
				stringstream ss;
				ss << "var_" << varIdx;
				cons.getVar(i).setName(ss.str());
			}

		return *this;
	}


	string toString() const
	{
		stringstream ss;
		ss << (type==MIPMinimize?"Minimize":"Maximize") << ": ";
		for(unsigned i=0; i<coefs.size(); i++)
			ss << (coefs[i]>=0?'+':' ') << coefs[i] << " " << vars[i]->toString() << " ";
		ss << endl;
		ss << "Subject to:" << endl;
		for(unsigned i=0; i<constraints.size(); i++)
			ss << constraints[i]->toString() << endl;
		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}

	void writeLP(string filename)
	{
		if(vars.size() == 0)
			return;
		if(constraints.size() == 0)
			return;

		vector<MIPVar*> vbin;
		vector<MIPVar*> vreal;
		vector<MIPVar*> vint;

		const int LINE_BASE_OBJ  = 6;
		const int LINE_SIZE_OBJ  = 45;
		const int LINE_BASE_CONS = 29;
		const int LINE_SIZE_CONS = 60;

		FILE* f = fopen(filename.c_str(), "w");
		fprintf(f, "\\ENCODING=ISO-8859-1\n\\Problem name: \n%s\n obj: ", (type==MIPMinimize?"Minimize":"Maximize")); 

		addUniqueByType(vars[0], vbin, vint, vreal);
		string var1 = formatLPVar(coefs[0], vars[0]->getName(), false);
		fprintf(f, "%s", var1.c_str());
		int countCharObj = var1.length();
		for(unsigned v=1; v<vars.size(); v++)
		{
			addUniqueByType(vars[v], vbin, vint, vreal);
			string var_v = formatLPVar(coefs[v], vars[v]->getName(), true);
			fprintf(f, " %s", var_v.c_str());
			countCharObj += var_v.length();
			if(countCharObj >= LINE_SIZE_OBJ)
			{
				fprintf(f, "\n");
				for(int i=0; i<LINE_BASE_OBJ; i++)
					fprintf(f, " ");
				countCharObj = 0;
			}
		}

		if(countCharObj != 0)
			fprintf(f, "\n");

		fprintf(f, "Subject To\n");

		for(unsigned c=0; c<constraints.size(); c++)
		{
			string cname = constraints[c]->getName();
			fprintf(f, " %s:", cname.c_str());

			for(int i=0; i<LINE_BASE_CONS-2-cname.length(); i++)
				fprintf(f, " ");

			addUniqueByType(&constraints[c]->getVar(0), vbin, vint, vreal);
			string var1 = formatLPVar(constraints[c]->getCoef(0), constraints[c]->getVar(0).getName(), false);
			fprintf(f, "%s", var1.c_str());
			int countCharObj = var1.length();
			for(unsigned v=1; v<constraints[c]->getNumVars(); v++)
			{
				addUniqueByType(&constraints[c]->getVar(v), vbin, vint, vreal);
				string var_v = formatLPVar(constraints[c]->getCoef(v), constraints[c]->getVar(v).getName(), true);
				fprintf(f, " %s", var_v.c_str());
				countCharObj += var_v.length();
				if(countCharObj >= LINE_SIZE_CONS)
				{
					fprintf(f, "\n");
					for(int i=0; i<LINE_BASE_CONS; i++)
						fprintf(f, " ");
					countCharObj = 0;
				}
			}

			stringstream ssrhs;
			ssrhs << " " << constraints[c]->getSignal() << (constraints[c]->getSignal()=='='?"":"=") << " " << constraints[c]->getRHS() << endl;
			fprintf(f, "%s", ssrhs.str().c_str());
		}

		fprintf(f, "Bounds\n");

		std::sort(vbin.begin(), vbin.end(), orderName);
		std::sort(vint.begin(), vint.end(), orderName);
		std::sort(vreal.begin(), vreal.end(), orderName);

		for(unsigned i=0; i<vbin.size(); i++)
			fprintf(f, "%s\n", printBound(*vbin[i]).c_str());
		for(unsigned i=0; i<vint.size(); i++)
			fprintf(f, "%s\n", printBound(*vint[i]).c_str());
		for(unsigned i=0; i<vreal.size(); i++)
			fprintf(f, "%s\n", printBound(*vreal[i]).c_str());
		if(vbin.size() > 0)
		{
			fprintf(f, "Binaries\n");
			const int CHAR_LIMIT = 69;
			int countChar = 0;
			for(unsigned i=0; i<vbin.size(); i++)
			{
				string var = vbin[i]->getName();
				fprintf(f, " %s", var.c_str()); 
				countChar += var.length();
				if(countChar >= CHAR_LIMIT)
				{
					countChar = 0;
					fprintf(f, "\n");
				}
			}
			if(countChar != 0)
				fprintf(f, "\n");
		}
		if(vint.size() > 0)
		{
			fprintf(f, "Generals\n");
			const int CHAR_LIMIT = 69;
			int countChar = 0;
			for(unsigned i=0; i<vint.size(); i++)
			{
				string var = vint[i]->getName();
				fprintf(f, " %s", var.c_str()); 
				countChar += var.length();
				if(countChar >= CHAR_LIMIT)
				{
					countChar = 0;
					fprintf(f, "\n");
				}
			}
			if(countChar != 0)
				fprintf(f, "\n");
		}
		fprintf(f, "End\n");

		fclose(f);
	}

private:
	inline string formatLPVar(const double& coef, const string& varName, bool signal)
	{
		if(coef == 0)
			return "";

		stringstream ss;
		if(signal)
			ss << (coef>=0?"+":"-") << " " << myabs(coef) << " " << varName;
		else
			ss << (coef>=0?"":"-")  << " " << myabs(coef) << " " << varName;
		return ss.str();
	}

	double myabs(double x)
	{
		if(x < 0)
			return -1*x;
		return x;
	}

	void addUniqueByType(MIPVar* var, vector<MIPVar*>& vBinary, vector<MIPVar*>& vInteger, vector<MIPVar*>& vReal)
	{
		if(var->isInteger())
			addUnique(var, vInteger);
		else if(var->isBinary())
			addUnique(var, vBinary);
		else
			addUnique(var, vReal);
	}

	void addUnique(MIPVar* var, vector<MIPVar*>& v)
	{
		for(unsigned i=0; i<v.size(); i++)
			if(v[i]->getName() == var->getName())
				return;
		v.push_back(var);
	}

	static bool orderName(const MIPVar* v1, const MIPVar* v2)
	{
		return v1->getName() < v2->getName();
	}

	string printBound(MIPVar& var)
	{
		stringstream ss;
		if(var.getLowerBound() == var.getUpperBound())
			ss << "      " << var.getName() << " = " << var.getLowerBound();
		else if((var.getLowerBound() != -MIPInf) && (var.getUpperBound() != MIPInf))
			ss << " " << var.getLowerBound() << " <= " << var.getName() << " <= " << var.getUpperBound();
		else if(var.getUpperBound() == MIPInf)
			ss << "      " << var.getName() << " >= " << var.getLowerBound();
		else
		{
			cout << "ERROR! DONT KNOW HOW TO PRINT VARIABLE: " << var.toString() << endl;
			exit(1);
		}

		return ss.str();
	}
};






#endif

