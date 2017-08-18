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
#include<assert.h>

#include "EMIPBase.hpp"
#include "EMIPExpr.hpp"
#include "EMIPOp.hpp"
#include "EMIPBool.hpp"
#include "EMIPVar.hpp"
#include "EMIPPar.hpp"
#include "EMIPSet.hpp"
#include "EMIPSum.hpp"
#include "EMIPForAll.hpp"
#include "EMIPCons.hpp"

using namespace std;

namespace EMIP
{

class GeneralInfo
{
public:
	vector<Index*> vindex;
	vector<Set*> vset;
	vector<Var*> vvar;
	vector<Par*> vpar;

public:
	void declare(const Index& i)
	{
		vindex.push_back(&i.cloneIndex());
	}
	void declare(const Set& s)
	{
		vset.push_back(&s.clone());
	}
	void declare(const Var& v)
	{
		vvar.push_back(&v.cloneVar());
	}
	void declare(const Par& p)
	{
		vpar.push_back(&p.clonePar());
	}

	string toLatex() const
	{
		stringstream ss;
		if (vindex.size() > 0)
		{
			ss << "Index: ";
			for (unsigned i = 0; i < vindex.size(); i++)
				ss << vindex[i]->name << " ";
			ss << endl << endl;
		}

		if (vset.size() > 0)
		{
			ss << "Sets: ";
			for (unsigned i = 0; i < vset.size(); i++)
				ss << vset[i]->getName() << " ";
			ss << endl << endl;
		}

		if (vvar.size() > 0)
		{
			ss << "Vars: ";
			for (unsigned i = 0; i < vvar.size(); i++)
				ss << vvar[i]->getExprName() << " ";
			ss << endl << endl;
		}

		if (vpar.size() > 0)
		{
			ss << "Params: ";
			for (unsigned i = 0; i < vpar.size(); i++)
				ss << vpar[i]->getExprName() << " ";
			ss << endl << endl;
		}

		return ss.str();
	}

};

class Modeler
{
public:
	GeneralInfo gi;

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
		if (model.obj)
			obj = &model.obj->clone();
		for (unsigned i = 0; i < model.constraints.size(); ++i)
			constraints.push_back(&model.constraints[i]->clone());
		for (unsigned i = 0; i < model.condCons.size(); ++i)
			condCons.push_back(&model.condCons[i]->clone());
		for (unsigned i = 0; i < model.dependPar.size(); ++i)
			dependPar.push_back(&model.dependPar[i]->clonePar());
		for (unsigned i = 0; i < model.dependVar.size(); ++i)
			dependVar.push_back(&model.dependVar[i]->cloneVar());
		for (unsigned i = 0; i < model.dependSet.size(); ++i)
			dependSet.push_back(&model.dependSet[i]->clone());
		gi = model.gi;
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
		if (obj)
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
		if (type == Minimize)
			ss << "Minimize";
		else
			ss << "Maximize";

		if (!obj)
		{
			ss << " !NO-OBJECTIVE)";
			return ss.str();
		}

		ss << " { " << obj->toString() << "} " << endl;
		ss << " subject to: {" << endl;
		for (unsigned i = 0; i < constraints.size(); ++i)
			ss << constraints[i]->toString() << endl;
		ss << "})";

		return ss.str();
	}

	virtual string toLatex() const
	{
		if (!obj)
			return "";

		stringstream ss;

		ss << gi.toLatex() << endl;

		ss << "\\begin{equation}\n";

		if (type == Minimize)
			ss << "min: ";
		else
			ss << "max: ";
		ss << obj->toLatex() << " ";
		if (obj->getExprName() != "")
			ss << "\\label{eq:" << obj->getExprName() << "}";
		ss << "\n\\end{equation}\n\n";

		ss << "\\begin{align}\n";
		for (int i = 0; i < ((int) constraints.size()); ++i)
			ss << constraints[i]->toLatex(i != ((int) constraints.size()) - 1) << endl;
		ss << "\\end{align}\n";

		for (unsigned j = 0; j < condCons.size(); ++j)
			ss << condCons[j]->toLatex() << endl;

		return ss.str();
	}

	virtual string toConcertOld() const
	{

		stringstream ss;
		ss << "MIPModel model(";
		if (type == Minimize)
			ss << "MIPMinimize";
		else
			ss << "MIPMaximize";
		ss << ");\n\n";

		for (unsigned i = 0; i < dependPar.size(); i++)
			ss << "// depend on parameter '" << dependPar[i]->toString() << "'" << endl;
		for (unsigned i = 0; i < dependVar.size(); i++)
			ss << "// depend on variable '" << dependVar[i]->toString() << "'" << endl;
		for (unsigned i = 0; i < dependSet.size(); i++)
			ss << "// depend on set '" << dependSet[i]->toString() << "'" << endl;
		ss << endl;

		return ss.str();
	}

	virtual string toMIP() const
	{
		if (obj->getExprName() == "")
		{
			cout << "ERROR! EMPTY NAME FOR OBJ" << endl;
			exit(1);
			return "";
		}

		stringstream ss;
		ss << "IloEnv env;\n";
		ss << "IloModel model(env);\n\n";
		ss << "IloExpr " << obj->getExprName() << "(env);\n";

		ss << "// " << obj->toLatex() << endl;
		GenMIP exprobj = obj->toMIP(obj->getExprName());
		ss << exprobj.before;
		ss << exprobj.now;
		ss << exprobj.after;

		ss << "\n";
		ss << "model.add(";
		if (type == Minimize)
			ss << "IloMinimize";
		else
			ss << "IloMaximize";

		ss << "(env, " << obj->getExprName() << "));\n\n";

		for (unsigned i = 0; i < constraints.size(); i++)
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
typedef const SetSet& SETSET;
typedef const ForAll& FORALL;
typedef const Cons& CONS;
typedef const IfElse& IFELSE;
typedef const Modeler& MODELER;

}

#endif

