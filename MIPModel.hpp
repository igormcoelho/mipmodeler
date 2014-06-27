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
	bool integer;
	string name;

	double lb;
	double ub;

public:
	MIPVar(double _lb = 0, double _ub = numeric_limits<double>::infinity(), bool _integer = false) :
		name(""), integer(_integer)
	{
	}

	MIPVar(string _name, double _lb = 0, double _ub = numeric_limits<double>::infinity(), bool _integer = false) :
		name(_name), integer(_integer)
	{
	}

	virtual ~MIPVar()
	{
	}

	string getName()
	{
		return name;
	}

	MIPVar& setName(string _name)
	{
		name = _name;
		return *this;
	}

	double getLowerBound()
	{
		return lb;
	}

	MIPVar& setLowerBound(double _lb)
	{
		lb = _lb;
		return *this;
	}

	double getUpperBound(double _ub)
	{
		return ub;
	}

	MIPVar& setUpperBound(double _ub)
	{
		ub = _ub;
		return *this;
	}

	bool isInteger()
	{
		return integer;
	}

	bool isReal()
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
		ss << "MIPVar(" << (integer?"Integer":"Real") << "):'" << name << "'";
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
		}

		return *this;
	}

	string getName()
	{
		return name;
	}

	MIPCons& setName(string _name)
	{
		name = _name;
		return *this;
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


class MIPMinimize
{
protected:
	vector<double> coefs;
	vector<MIPVar*> vars;
	vector<MIPCons*> constraints;

public:

	MIPMinimize& add(double coef, MIPVar* var)
	{
		if(var)
		{
			coefs.push_back(coef);
			vars.push_back(var);
		}

		return *this;
	}

	MIPMinimize& add(MIPCons* cons)
	{
		if(cons)
			constraints.push_back(cons);

		return *this;
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

