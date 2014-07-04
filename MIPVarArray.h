// =========================================
// Simple class for MIP modeling
//
// Author: Igor Machado Coelho
//
// Copyleft 2014 - LGPLv3 (Gnu Lesser GPLv3)
// =========================================

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
	string name;
	vector<MIPVar*> v;

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
		return *this;
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
		ss << "MIPVarArray('" << name << "'," << size() << "): " << endl;
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
	string name;
	vector<MIPVarArray*> v;

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
		return *this;
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
		ss << "MIPVarArray2('" << name << "'," << size() << "): " << endl;
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
	string name;
	vector<MIPVarArray2*> v;

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
		return *this;
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
		ss << "MIPVarArray3('" << name << "'," << size() << "): " << endl;
		for(unsigned i=0; i<v.size(); i++)
			ss << v[i]->toString() << endl;
		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}
};



class MIPVarArray4
{
protected:
	string name;
	vector<MIPVarArray3*> v;

public:
	MIPVarArray4(string _name="") :
		name(_name)
	{
	}


	MIPVarArray4(unsigned size, string _name="") :
		name(_name)
	{
		v = vector<MIPVarArray3*>(size, NULL);
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray3;
	}

	MIPVarArray4(const MIPVarArray4& mva) :
		name(mva.name), v(mva.v)
	{
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray3(*mva.v[i]);
	}

	virtual ~MIPVarArray4()
	{
		for(unsigned i=0; i<v.size(); i++)
			delete v[i];
		v.clear();
	}

	inline string getName()
	{
		return name;
	}

	inline MIPVarArray4& setName(string _name)
	{
		name = _name;
		return *this;
	}

	void renameVars()
	{
		if(name == "")
			return;

		for(unsigned i=0; i<v.size(); i++)
			for(unsigned j=0; j<v[i]->size(); j++)
				for(unsigned k=0; k<(*v[i])[j].size(); k++)
					for(unsigned l=0; l<(*v[i])[j][k].size(); l++)
					{
						stringstream ss;
						ss << name << "_" << i << "_" << j << "_" << k << "_" << l;
						(*v[i])[j][k][l].setName(ss.str());
					}
	}

	inline MIPVarArray3& operator[](unsigned index)
	{
		return *v[index];
	}

	inline const MIPVarArray3& operator[](unsigned index) const
	{
		return *v[index];
	}

	inline MIPVarArray3& at(unsigned index)
	{
		return *v.at(index);
	}

	inline const MIPVarArray3& at(unsigned index) const
	{
		return *v.at(index);
	}

	inline unsigned size() const
	{
		return v.size();
	}

	inline void push_back(const MIPVarArray3& array)
	{
		v.push_back(new MIPVarArray3(array));
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPVarArray4('" << name << "'," << size() << "): " << endl;
		for(unsigned i=0; i<v.size(); i++)
			ss << v[i]->toString() << endl;
		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}
};


class MIPVarArray5
{
protected:
	string name;
	vector<MIPVarArray4*> v;

public:
	MIPVarArray5(string _name="") :
		name(_name)
	{
	}


	MIPVarArray5(unsigned size, string _name="") :
		name(_name)
	{
		v = vector<MIPVarArray4*>(size, NULL);
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray4;
	}

	MIPVarArray5(const MIPVarArray5& mva) :
		name(mva.name), v(mva.v)
	{
		for(unsigned i=0; i<v.size(); i++)
			v[i] = new MIPVarArray4(*mva.v[i]);
	}

	virtual ~MIPVarArray5()
	{
		for(unsigned i=0; i<v.size(); i++)
			delete v[i];
		v.clear();
	}

	inline string getName()
	{
		return name;
	}

	inline MIPVarArray5& setName(string _name)
	{
		name = _name;
		return *this;
	}

	void renameVars()
	{
		if(name == "")
			return;

		for(unsigned i=0; i<v.size(); i++)
			for(unsigned j=0; j<v[i]->size(); j++)
				for(unsigned k=0; k<(*v[i])[j].size(); k++)
					for(unsigned l=0; l<(*v[i])[j][k].size(); l++)
						for(unsigned m=0; m<(*v[i])[j][k][m].size(); m++)
						{
							stringstream ss;
							ss << name << "_" << i << "_" << j << "_" << k << "_" << l << "_" << m;
							(*v[i])[j][k][l][m].setName(ss.str());
						}
	}

	inline MIPVarArray4& operator[](unsigned index)
	{
		return *v[index];
	}

	inline const MIPVarArray4& operator[](unsigned index) const
	{
		return *v[index];
	}

	inline MIPVarArray4& at(unsigned index)
	{
		return *v.at(index);
	}

	inline const MIPVarArray4& at(unsigned index) const
	{
		return *v.at(index);
	}

	inline unsigned size() const
	{
		return v.size();
	}

	inline void push_back(const MIPVarArray4& array)
	{
		v.push_back(new MIPVarArray4(array));
	}

	string toString() const
	{
		stringstream ss;
		ss << "MIPVarArray5('" << name << "'," << size() << "): " << endl;
		for(unsigned i=0; i<v.size(); i++)
			ss << v[i]->toString() << endl;
		return ss.str();
	}

	void print() const
	{
		cout << toString() << endl;
	}
};


// TODO: generic N-dimensional array
template<class N>
class MIPVarArrayN
{

};

#endif

