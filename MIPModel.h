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
#define MIPInteger true
#define MIPReal false

class MIPVar
{
protected:
	unsigned index;
	bool type;
	string name;

	double lb;
	double ub;

	static unsigned count;
	static unsigned count_max;

public:

	inline static unsigned getCountMax()
	{
		return count_max;
	}

	MIPVar(double _lb = 0, double _ub = MIPInf, bool _type = MIPReal) :
		index(++count),  type(_type), name(""), lb(_lb), ub(_ub)
	{
		if(count > count_max)
			count_max = count;
	}

	MIPVar(string _name, double _lb = 0, double _ub = MIPInf, bool _type = MIPReal) :
		index(++count), type(_type), name(_name), lb(_lb), ub(_ub)
	{
		if(count > count_max)
			count_max = count;
	}

	MIPVar(const MIPVar& var) :
		index(++count), name(var.name), type(var.type), lb(var.lb), ub(var.ub)
	{
		if(count > count_max)
			count_max = count;
	}

	virtual ~MIPVar()
	{
		count--;
		if(count==0)
			count_max=0;
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
		return type == MIPInteger;
	}

	inline bool isReal() const
	{
		return type == MIPReal;
	}

	void print() const
	{
		cout << toString() << endl;
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPVar#" << index << "(" << (type==MIPInteger?"Integer":"Real") << "):'" << name;
		ss << "'{" << lb << ";";
		ss << ub << "}";
		return ss.str();
	}

	MIPVar& operator=(const MIPVar& var)
	{
		if(&var == this)
			return *this;

		type = var.type;
		name = var.name;
		lb   = var.lb;
		ub   = var.ub;

		return *this;
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

	static unsigned count;
	static unsigned count_max;

public:

	inline static unsigned getCountMax()
	{
		return count_max;
	}

	MIPCons(char _signal, double _rhs = 0) :
		index(++count), name(""), signal(_signal), rhs(_rhs)
	{
		if(count > count_max)
			count_max = count;

		if((signal != '<') && (signal != '=') && (signal != '>'))
		{
			cout << "MIPCons::error! unknown signal '" << signal << "'" << endl;
			exit(1);
		}
	}

	MIPCons(string _name, char _signal, double _rhs = 0) :
		index(++count), name(_name), signal(_signal), rhs(_rhs)
	{
		if(count > count_max)
			count_max = count;

		if((signal != '<') && (signal != '=') && (signal != '>'))
		{
			cout << "MIPConstraint::error! unknown signal '" << signal << "'" << endl;
			exit(1);
		}
	}

	MIPCons(const MIPCons& cons) :
		index(++count), name(cons.name), signal(cons.signal), rhs(cons.rhs), coefs(cons.coefs), vars(cons.vars)
	{
		if(count > count_max)
			count_max = count;
	}

	virtual ~MIPCons()
	{
		count--;
		if(count==0)
			count_max=0;

		vars.clear();
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
		constraints.clear();
		coefs.clear();
		vars.clear();
	}

	MIPMinimize& add(double coef, MIPVar& var)
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

	MIPMinimize& add(MIPCons& cons)
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
		ss << "Minimize: ";
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

	}
};






#endif

