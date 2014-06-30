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
#include<algorithm>

#include<stdio.h>
#include<stdlib.h>

using namespace std;


#define MIPInf numeric_limits<double>::infinity()

enum MIPType { MIPReal, MIPBinary, MIPInteger };

class MIPVar
{
protected:
	unsigned index;
	MIPType type;
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

	MIPVar(MIPType _type = MIPReal, double _lb = 0, double _ub = MIPInf) :
		index(++count),  type(_type), name(""), lb(_lb), ub(_ub)
	{
		if(count > count_max)
			count_max = count;
	}

	MIPVar(string _name, MIPType _type = MIPReal, double _lb = 0, double _ub = MIPInf) :
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

	inline double getUpperBound() const
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

	inline bool isBinary() const
	{
		return type == MIPBinary;
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
		ss << "MIPVar#" << index << "(";
		if(isInteger())
			ss << "Integer";
		else if(isBinary())
			ss << "Binary";
		else
			ss << "Real";
		ss << "):'" << name << "'{" << lb << ";" << ub << "}";

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
		fprintf(f, "\\ENCODING=ISO-8859-1\n\\Problem name: \nMinimize\n obj: "); 

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

