/*
 * EMIPBase.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: imcoelho
 */

#ifndef EMIP_SET_HPP_
#define EMIP_SET_HPP_

#include<iostream>
#include<sstream>
#include<limits>
#include<vector>
#include<algorithm>

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "EMIPBase.hpp"

using namespace std;

namespace EMIP
{

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

	string getName() const
	{
		return name;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSet('" << name << "') ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << " ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		r.now = name;
		return r;
	}

	virtual Set& clone() const
	{
		return *new Set(name);
	}
};

class SetSet
{
public:
	//protected:
	string name;

public:

	SetSet(string _name) :
			name(_name)
	{
	}

	virtual ~SetSet()
	{
	}

	virtual Id id() const
	{
		return IdSetSet;
	}

	string getName() const
	{
		return name;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSetSet('" << name << "') ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << name << " ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		r.now = name;
		return r;
	}

	virtual SetSet& clone() const
	{
		return *new SetSet(name);
	}
};

// TODO: create MIPRange{n1..n2} : Set

// THIS IS THE ELEMENT OF A SET OF SETS
class SetSetElem: public Set
{
protected:
	Expr& elem;
	SetSet& sset;

public:

	SetSetElem(const SetSet& _sset, const Expr& _elem) :
			Set("anonSetSet"), elem(_elem.clone()), sset(_sset.clone())
	{
	}

	virtual ~SetSetElem()
	{
	}

	virtual Id id() const
	{
		return IdSetSetElem;
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "EMIPSetSetElem(" << sset.name << "(" << elem.toString() << ")) ";
		return ss.str();
	}

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << sset.name << "(" << elem.toLatex() << ") ";
		return ss.str();
	}

	virtual Set& clone() const
	{
		return *new SetSetElem(sset, elem);
	}
};

class SetElem: public Set
{
protected:
	Expr& elem;

public:

	SetElem(const Expr& _elem) :
			Set("anonSet"), elem(_elem.clone())
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

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "\\{" << elem.toLatex() << " \\} ";
		return ss.str();
	}

	virtual Set& clone() const
	{
		return *new SetElem(elem);
	}
};

class SetCard: public Expr
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

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		ss << "|" << s1.toLatex() << "|";
		return ss.str();
	}

	virtual GenMIP toMIP(string var) const
	{
		GenMIP r;
		stringstream ss;
		if (var != "")
			ss << var << " += ";
		ss << s1.getName() << ".size() ";
		if (var != "")
			ss << "; /* ';' added by Card */\n";
		r.now = ss.str();
		return r;
	}

	virtual Expr& clone() const
	{
		return *new SetCard(s1);
	}
};

class SetOp: public Set
{
protected:
	Set& s1;
	string op;
	Set& s2;

public:

	SetOp(const Set& _s1, string _op, const Set& _s2) :
			Set(""), s1(_s1.clone()), op(_op), s2(_s2.clone())
	{
		if ((op != "U") && (op != "-") && (op != "\\") && (op != "C") && (op != "C="))
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

	virtual string toLatex(bool br = true) const
	{
		stringstream ss;
		if (br)
			ss << "\\left(";

		ss << s1.toLatex() << " ";

		if (op == "U")
			ss << "\\cup ";
		else if (op == "-")
			ss << "- ";
		else if (op == "\\")
			ss << "\\setminus ";
		else if (op == "C")
			ss << "\\subset ";
		else if (op == "C=")
			ss << "\\subseteq ";

		ss << s2.toLatex();

		if (br)
			ss << " \\right) ";
		return ss.str();
	}

	virtual GenMIP toMIP() const
	{
		GenMIP r;
		stringstream ss;
		cout << "TODO: IMPLEMENT setOp toMIP()!" << endl;
		exit(1);
		r.now = ss.str();
		return r;
	}

	virtual Set& clone() const
	{
		return *new SetOp(s1, op, s2);
	}
};

}


#endif /* EMIP_SET_HPP_ */
