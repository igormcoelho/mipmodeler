// ==============================
// Simple class for MIP modeling
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - LGPLv3
// ==============================

#ifndef MIPMODEL_HPP
#define MIPMODEL_HPP

#include<iostream>
#include<sstream>
#include<limits>
#include<vector>

#include<stdio.h>
#include<stdlib.h>

using namespace std;


#define MIPInf numeric_limits<double>::infinity()

class MIPVar
{
protected:
	unsigned index;
	bool integer;
	string name;

	double lb;
	double ub;

	static unsigned count;

public:
	MIPVar(double _lb = 0, double _ub = MIPInf, bool _integer = false) :
		index(++count), name(""), integer(_integer)
	{
	}

	MIPVar(string _name, double _lb = 0, double _ub = MIPInf, bool _integer = false) :
		index(++count), name(_name), integer(_integer)
	{
	}

	MIPVar(const MIPVar& var) :
		index(++count), name(var.name), integer(var.integer)
	{
	}

	virtual ~MIPVar()
	{
	}

	unsigned getIdx()
	{
		return index;
	}

	inline string getName() const
	{
		return name;
	}

	inline MIPVar& setName(string _name)
	{
		name = _name;
		return *this;
	}

	inline double getLowerBound() const
	{
		return lb;
	}

	inline MIPVar& setLowerBound(double _lb)
	{
		lb = _lb;
		return *this;
	}

	inline double getUpperBound(double _ub) const
	{
		return ub;
	}

	inline MIPVar& setUpperBound(double _ub)
	{
		ub = _ub;
		return *this;
	}

	inline bool isInteger() const
	{
		return integer;
	}

	inline bool isReal() const
	{
		return !integer;
	}

	void print() const
	{
		cout << toString() << endl;
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPVar#" << index << "(" << (integer?"Integer":"Real") << "):'" << name << "'";
		return ss.str();
	}
};


class MIPCons
{
protected:
	unsigned index;
	string name;
	char signal;
	double rhs;
	vector<double> coefs;
	vector<MIPVar*> vars;
	vector<bool> varsDelete;

	static unsigned count;

public:

	MIPCons(char _signal, double _rhs = 0) :
		index(++count), name(""), signal(_signal), rhs(_rhs)
	{
		if((signal != '<') && (signal != '=') && (signal != '>'))
		{
			cout << "MIPCons::error! unknown signal '" << signal << "'" << endl;
			exit(1);
		}
	}

	MIPCons(string _name, char _signal, double _rhs = 0) :
		index(++count), name(_name), signal(_signal), rhs(_rhs)
	{
		if((signal != '<') && (signal != '=') && (signal != '>'))
		{
			cout << "MIPConstraint::error! unknown signal '" << signal << "'" << endl;
			exit(1);
		}
	}

	MIPCons(const MIPCons& cons) :
		index(++count), name(cons.name), signal(cons.signal), rhs(cons.rhs), coefs(cons.coefs), vars(cons.vars), varsDelete(cons.varsDelete)
	{
	}

	virtual ~MIPCons()
	{
		cout << "~MIPCons(" << name << ")" << endl;
		cout << "|vars|=" << vars.size() << endl;
		cout << "|varsDelete|=" << varsDelete.size() << endl;
		for(unsigned i=0; i<vars.size(); i++)
			if(varsDelete[i])
				delete vars[i];
		vars.clear();
		varsDelete.clear();
		coefs.clear();
	}

	unsigned getIdx()
	{
		return index;
	}

	MIPCons& add(double value)
	{
		rhs -= value;
		return *this;
	}

	MIPCons& add(double coef, MIPVar* var)
	{
		if(var)
		{
			coefs.push_back(coef);
			vars.push_back(var);
			varsDelete.push_back(false);
		}

		return *this;
	}

	MIPCons& add(double coef, MIPVar& var)
	{
		MIPVar* pVar = new MIPVar(var);
		MIPCons& _this = add(coef, pVar);
		varsDelete[varsDelete.size()-1] = true;
		return _this;
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

	inline MIPVar* getVar(unsigned index)
	{
		return vars.at(index);
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
		ss << "MIPCons#" << index << "('" << name << "'): ";
		for(unsigned i=0; i<coefs.size(); i++)
			ss << (coefs[i]>=0?'+':' ') << coefs[i] << " " << vars[i]->toString() << " ";
		ss << signal << " ";
		ss << rhs;
		return ss.str();
	}
};


class MIPMinimize
{
protected:
	vector<double> coefs;
	vector<MIPVar*> vars;
	vector<MIPCons*> constraints;
	vector<bool> consDelete;

	int varIdx;
	int consIdx;

public:

	MIPMinimize()
	{
		varIdx = 0;
		consIdx = 0;
	}

	virtual ~MIPMinimize()
	{
		for(unsigned i=0; i<vars.size(); i++)
			delete vars[i];
		cout << "|consDelete|=" << consDelete.size() << endl;
		cout << "|constraints|=" << constraints.size() << endl;
		for(unsigned i=0; i<consDelete.size(); i++)
			if(consDelete[i])
				delete constraints[i];
		constraints.clear();
		consDelete.clear();
		coefs.clear();
		vars.clear();
	}

	MIPMinimize& add(double coef, const MIPVar& _var)
	{
		coefs.push_back(coef);
		MIPVar* var = new MIPVar(_var);
		vars.push_back(var);

		// auto naming
		if(var->getName() == "")
		{
			varIdx++;
			stringstream ss;
			ss << "var_" << varIdx;
			var->setName(ss.str());
		}
		
		return *this;
	}

	MIPMinimize& add(MIPCons* cons)
	{
		if(cons)
		{
			constraints.push_back(cons);
			consDelete.push_back(false);

			// auto naming
			if(cons->getName() == "")
			{
				consIdx++;
				stringstream ss;
				ss << "cons_" << consIdx;
				cons->setName(ss.str());
			}

			// auto naming
			for(unsigned i=0; i<cons->getNumVars(); i++)
				if(cons->getVar(i)->getName() == "")
				{
					varIdx++;
					stringstream ss;
					ss << "var_" << varIdx;
					cons->getVar(i)->setName(ss.str());
				}

		}

		return *this;
	}

	MIPMinimize& add(const MIPCons& _cons)
	{
		MIPCons* cons = new MIPCons(_cons);
		MIPMinimize& _this = add(cons);
		consDelete[consDelete.size()-1] = true;
		return _this;
	}

	string toStringLP() const
	{
		stringstream ss;
		ss << "Minimize: ";
		for(unsigned i=0; i<coefs.size(); i++)
			ss << (coefs[i]>=0?'+':' ') << coefs[i] << " " << vars[i]->toString() << " ";
		ss << endl;
		ss << "Subject to:" << endl;
		for(unsigned i=0; i<constraints.size(); i++)
			ss << constraints[i]->toString() << endl;
		return ss.str();
	}

	void printLP() const
	{
		cout << toStringLP() << endl;
	}

	void writeLP(string filename)
	{

	}
};






#endif

