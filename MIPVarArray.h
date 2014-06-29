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

public:
	MIPVarArray()
	{
	}


	MIPVarArray(unsigned size)
	{
		v = vector<MIPVar*>(size, NULL);
	}

	MIPVarArray(const MIPVarArray& mva) :
		v(mva.v)
	{
	}

	~MIPVarArray()
	{
	}

	inline MIPVar* operator[](unsigned index)
	{
		return v[index];
	}

	inline const MIPVar* operator[](unsigned index) const
	{
		return v[index];
	}

	inline MIPVar* at(unsigned index)
	{
		return v.at(index);
	}

	inline const MIPVar* at(unsigned index) const
	{
		return v.at(index);
	}

	inline unsigned size() const
	{
		return v.size();
	}

	inline void push_back(MIPVar* var)
	{
		v.push_back(var);
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
}


#endif
