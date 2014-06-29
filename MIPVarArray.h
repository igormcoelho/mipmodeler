#ifndef MIPVARARRAY
#define MIPVARARRAY

#include<iostream>
#include<sstream>
#include<vector>

#include<stdio.h>
#include<stdlib.h>

#include "MIPModel.h"

using namespace std;

class MIPVarArray
{
protected:
	vector<MIPVar*> v;
	string name;

public:
	MIPVarArray(string _name="") :
		name(_name)
	{
	}

	MIPVarArray(unsigned size, string _name="") :
		name(_name)
	{
		v = vector<MIPVar*>(size, NULL);
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVar;
	}

	MIPVarArray(const MIPVarArray& mva) :
		name(mva.name), v(mva.v)
	{
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVar(*mva.v[i]);
	}

	virtual ~MIPVarArray()
	{
		for(unsigned i=0; i<v.size(); i++)
			delete v[i];
		v.clear();
	}

	inline string getName()
	{
		return name;
	}

	inline MIPVarArray& setName(string _name)
	{
		name = _name;
	}

	void renameVars()
	{
		if(name == "")
			return;

		for(unsigned i=0; i<v.size(); i++)
			if(v[i])
			{
				stringstream ss;
				ss << name << "_" << i;
				v[i]->setName(ss.str());
			}
	}

	inline MIPVar& operator[](unsigned index)
	{
		return *v[index];
	}

	inline const MIPVar& operator[](unsigned index) const
	{
		return *v[index];
	}

	inline MIPVar& at(unsigned index)
	{
		return *v.at(index);
	}

	inline const MIPVar& at(unsigned index) const
	{
		return *v.at(index);
	}

	inline unsigned size() const
	{
		return v.size();
	}

	inline void push_back(MIPVar* var)
	{
		if(var)
			v.push_back(var);
	}

	inline void push_back(const MIPVar& var)
	{
		v.push_back(new MIPVar(var));
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPVarArray(" << size() << "): ";
		for(unsigned i=0; i<v.size(); i++)
			ss << (v[i]==NULL?"NULL":v[i]->toString()) << "\t";
		ss << endl;
		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}
};


class MIPVarArray2
{
protected:
	vector<MIPVarArray*> v;
	string name;

public:
	MIPVarArray2(string _name="") :
		name(_name)
	{
	}


	MIPVarArray2(unsigned size, string _name="") :
		name(_name)
	{
		v = vector<MIPVarArray*>(size, NULL);
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray;
	}

	MIPVarArray2(const MIPVarArray2& mva) :
		name(mva.name), v(mva.v)
	{
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray(*mva.v[i]);
	}

	virtual ~MIPVarArray2()
	{
		for(unsigned i=0; i<v.size(); i++)
			delete v[i];
		v.clear();
	}

	inline string getName()
	{
		return name;
	}

	inline MIPVarArray2& setName(string _name)
	{
		name = _name;
	}

	void renameVars()
	{
		if(name == "")
			return;

		for(unsigned i=0; i<v.size(); i++)
			for(unsigned j=0; j<v[i]->size(); j++)
			{
				stringstream ss;
				ss << name << "_" << i << "_" << j;
				(*v[i])[j].setName(ss.str());
			}
	}

	inline MIPVarArray& operator[](unsigned index)
	{
		return *v[index];
	}

	inline const MIPVarArray& operator[](unsigned index) const
	{
		return *v[index];
	}

	inline MIPVarArray& at(unsigned index)
	{
		return *v.at(index);
	}

	inline const MIPVarArray& at(unsigned index) const
	{
		return *v.at(index);
	}

	inline unsigned size() const
	{
		return v.size();
	}

	inline void push_back(const MIPVarArray& array)
	{
		v.push_back(new MIPVarArray(array));
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPVarArray2(" << size() << "): " << endl;
		for(unsigned i=0; i<v.size(); i++)
			ss << v[i]->toString() << endl;
		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}
};


class MIPVarArray3
{
protected:
	vector<MIPVarArray2*> v;
	string name;

public:
	MIPVarArray3(string _name="") :
		name(_name)
	{
	}


	MIPVarArray3(unsigned size, string _name="") :
		name(_name)
	{
		v = vector<MIPVarArray2*>(size, NULL);
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray2;
	}

	MIPVarArray3(const MIPVarArray3& mva) :
		name(mva.name), v(mva.v)
	{
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray2(*mva.v[i]);
	}

	virtual ~MIPVarArray3()
	{
		for(unsigned i=0; i<v.size(); i++)
			delete v[i];
		v.clear();
	}

	inline string getName()
	{
		return name;
	}

	inline MIPVarArray3& setName(string _name)
	{
		name = _name;
	}

	void renameVars()
	{
		if(name == "")
			return;

		for(unsigned i=0; i<v.size(); i++)
			for(unsigned j=0; j<v[i]->size(); j++)
				for(unsigned k=0; k<v[i]->at(j).size(); k++)
				{
					stringstream ss;
					ss << name << "_" << i << "_" << j << "_" << k;
					(*v[i])[j][k].setName(ss.str());
				}
	}

	inline MIPVarArray2& operator[](unsigned index)
	{
		return *v[index];
	}

	inline const MIPVarArray2& operator[](unsigned index) const
	{
		return *v[index];
	}

	inline MIPVarArray2& at(unsigned index)
	{
		return *v.at(index);
	}

	inline const MIPVarArray2& at(unsigned index) const
	{
		return *v.at(index);
	}

	inline unsigned size() const
	{
		return v.size();
	}

	inline void push_back(const MIPVarArray2& array)
	{
		v.push_back(new MIPVarArray2(array));
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPVarArray3(" << size() << "): " << endl;
		for(unsigned i=0; i<v.size(); i++)
			ss << "\t" << v[i]->toString() << endl;
		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}
};


#endif

