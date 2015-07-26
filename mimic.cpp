// Author: Igor Machado Coelho
// Date: 10-09-2014
// Introduction to the MoveSwap C++ Pattern

// The MoveSwap Pattern makes a class imitate the behavior
// of another class (usually an inherited one).

#include<assert.h>
#include<stdio.h>
#include<iostream>

#include "mimic.h"

using namespace std;


class Move
{
private:
    Move* mimic;

protected:
    // Move() must be protected to avoid creation of empty object ("pure virtual")
    // PATTERN ABC: Abstract Base Class
    Move()
    {
        cout << __PRETTY_FUNCTION__ << endl;
        mimic = NULL;
    }

public:
//	Move(Move* p)
//	{
//		cout << __PRETTY_FUNCTION__ << endl;
//		mimic = p;
//	}

    Move(const Move& b)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << "b.mimic=" << b.mimic << endl;
        if (b.mimic)
        {
            cout << "COPY pointer!!" << endl;
            mimic = &b.mimic->clone();
        }
        else
        {
            cout << "COPY body!!" << endl;
            mimic = &b.clone();
        }
    }

    /*
     Move(const Move&& r)
     {
     cout << __PRETTY_FUNCTION__ << endl;
     if(r.mimic)
     {
     cout << "STEAL pointer!!" << endl;
     Move& m = const_cast<Move&>(r);
     mimic = m.mimic;
     m.mimic = NULL;
     }
     else
     {
     cout << "COPY body!!" << endl;
     mimic = &r.clone();
     }
     }
     */

    virtual ~Move()
    {
        if (mimic)
            delete mimic;
    }

    // classic clone() function (really clones object)
    virtual Move& clone() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        return *new Move(*this);
    }

    // method mimic() that generates an object that
    // IMITATES the behavior of object "this". Copy
    // using move semantics.
    virtual Move doMimic() const
    {
    }

    virtual void work() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        assert(mimic);
        mimic->work();
    }

    Move& operator=(const Move& m)
    {
        cout << "Move::operator=" << endl;
        if (&m == this)
            return *this;
        if (mimic)
            delete mimic;
        mimic = NULL;
        cout << "(m.mimic=" << m.mimic << ") := ";
        mimic = (m.mimic ? &m.mimic->clone() : &m.clone());
        cout << mimic << endl;

        return *this;
    }
};

class MoveSwap: public Move
{
protected:
    int i;
    int j;
public:
    MoveSwap(int _i, int _j) :
        i(_i), j(_j)
    {
        cout << "MoveSwap(" << i << "," << j << ")" << endl;
    }

    MoveSwap(const MoveSwap& b) :
        i(b.i), j(b.j)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    /*
     MoveSwap(MoveSwap&& b)
     : i(b.i), j(b.j)
     {
     cout << __PRETTY_FUNCTION__ << endl;
     }
     */

    virtual ~MoveSwap()
    {
    }

    virtual Move& clone() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        return *new MoveSwap(*this);
    }

    virtual Move doMimic() const
    {
        return Move(*this);
    }

    virtual void work() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << "MOVE_SWAP_WORK! (" << i << "," << j << ")" << endl;
    }

    virtual MoveSwap& operator=(const MoveSwap& m)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        if (&m == this)
            return *this;
        i = m.i;
        j = m.j;
        return *this;
    }
};

class Move2: public MoveSwap
{
protected:
    int k;
public:
    Move2(int _i, int _j, int _k) :
        k(_k), MoveSwap(_i, _j)
    {
        cout << "Move2(" << _i << "," << _j << "," << _k << ")" << endl;
    }

    Move2(const Move2& b) :
        k(b.k), MoveSwap(b)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << "Move2(" << b.i << "," << b.j << "," << b.k << ")" << endl;
    }

    /*
     MoveSwap(MoveSwap&& b)
     : i(b.i), j(b.j)
     {
     cout << __PRETTY_FUNCTION__ << endl;
     }
     */

    virtual ~Move2()
    {
    }

    virtual Move& clone() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        return *new Move2(*this);
    }

    virtual Move doMimic() const
    {
        return Move(*this);
    }

    virtual void work() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << "MOVE2_WORK! (" << i << "," << j << "," << k << ")" << endl;
    }

    virtual MoveSwap& operator=(const Move2& m)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        if (&m == this)
            return *this;

        (MoveSwap&) (*this) = (MoveSwap&) m;
        k = m.k;
        return *this;
    }
};

void testmove()
{
    cout << "DIRECT PRINT" << endl;
    MoveSwap m(100, 9);
    cout << "*** try work()" << endl;
    m.work();

    cout << endl;

    cout << "DIRECT COPY" << endl;
    Move mcopy = m;
    cout << "*** try work()" << endl;
    mcopy.work();
    cout << "*** try work() m" << endl;
    m.work();
    cout << endl;

    cout << "RESET COPY" << endl;
    mcopy = m;
    cout << "*** try work()" << endl;
    mcopy.work();

    cout << endl;

    cout << "COPY THE COPY" << endl;
    Move mcopy2 = mcopy;
    cout << "*** try work()" << endl;
    mcopy2.work();

    //cout << "INCLUDE CALL WORK" << endl;
    //Include inc(m);
    //inc.callWork();

    cout << endl;

    cout << endl << "========================================" << endl << endl;
    // ===========================================

    cout << "(2)DIRECT PRINT" << endl;
    Move2 m2(100, 9, 10);
    cout << "*** try work()" << endl;
    m2.work();
    cout << endl;

    cout << "(2)DIRECT COPY" << endl;
    Move mcopy2X = m2;
    cout << "*** try work()" << endl;
    mcopy2X.work();
    cout << "*** try work() m" << endl;
    m2.work();
    cout << endl;

    cout << "(2)RESET COPY" << endl;
    mcopy2X = m2;
    cout << "*** try work()" << endl;
    mcopy2X.work();
    cout << endl;

    cout << "(2)RESET COPY Swap to Move2" << endl;
    mcopy2X = m;
    cout << "*** try work()" << endl;
    mcopy2X.work();
    cout << endl;

    cout << endl << "========================================" << endl << endl;
    // ====================================================

    cout << "COPY THE COPY" << endl;
    Move mcopyX = mcopy;
    cout << "*** try work()" << endl;
    mcopyX.work();

    //cout << "INCLUDE CALL WORK" << endl;
    //Include inc(m);
    //inc.callWork();

    cout << endl;

    // ==================================

    cout << "MULTIPLE COPY" << endl;
    Move m5 = Move(Move(Move(MoveSwap(MoveSwap(MoveSwap(5, 88))))));
    m5.work();

    cout << endl;

    //cout << "EMPTY" << endl;
    //Move empty; // ERROR! protected constructor!
    //empty.work();
}

class Mimic
{
    MIMIC_BEGIN(Mimic)

// pure abstract class!
protected:
    Mimic()
    {
        MIMIC_INIT(Mimic)
    }

public:

    virtual ~Mimic()
    {
        MIMIC_DESTROY(Mimic)
    }

    virtual void clone(Mimic*& m) const
    {
        m = new Mimic(*this);
    }

    virtual void work() const
    {
        MIMIC_VOIDFUNC(Mimic, work)
        cout << "work!!" << endl;
    }

    virtual int dfunc(int x, int y) const
    {
        MIMIC_RETFUNC(Mimic, dfunc, x, y)
        return x + y;
    }
};

class A: public Mimic
{
    MIMIC_BEGIN(A)

public:

    A()
    {
        MIMIC_INIT(A)
    }

    virtual ~A()
    {
        MIMIC_DESTROY(A)
    }

    virtual void work() const
    {
        MIMIC_VOIDFUNC(A, work)

        cout << "work:A()" << endl;
    }

    virtual int dfunc(int x, int y) const
    {
        MIMIC_RETFUNC(A, dfunc, x, y)

        return x * y;
    }

    MIMIC_CLONE(A, Mimic)

    virtual void clone(A*& a) const
    {
        cout << "CLONE(A)" << endl;
        a = new A();
    }

};

class B: public A
{
    MIMIC_BEGIN(B)

public:

    B()
    {
        MIMIC_INIT(B)
    }

    virtual ~B()
    {
        MIMIC_DESTROY(B)
    }

    virtual void work() const
    {
        MIMIC_VOIDFUNC(B, work)

        cout << "work:B()" << endl;
    }

    MIMIC_CLONE(B, Mimic)

    MIMIC_CLONE(B, A)

    virtual void clone(B*& b) const
    {
        assert(b==NULL);
        b = new B();
    }

    /*
     virtual B& operator=(const B& m)
     {
     if (&m == this)
     return *this;
     return *this;
     }*/

};

class C: public B
{
    DISABLE_SLICING(C)

public:

    C()
    {
    }

    C(const C& c) :
        B()
    {
    }

    virtual void work() const
    {
        cout << "work:C()" << endl;
    }

    MIMIC_CLONE(C, Mimic)

    MIMIC_CLONE(C, A)

    MIMIC_CLONE(C, B)

    virtual void clone(C*& m) const
    {
        m = new C();
    }

    C& operator=(const C& c)
    {
        cout << "CCCC" << endl;
        return *this;
    }

};

class D: public C
{
public:

    D()
    {
    }

    D(const D& d) :
        C()
    {
    }

    virtual void work() const
    {
        cout << "D()" << endl;
    }

    virtual void clone(Mimic* m)
    {
        m = new D();
    }

};

void print(A& a)
{
    cout << "print A: ";
    a.work();
}

void print(B& b)
{
    cout << "print B: ";
    b.work();
}

void print(C& c)
{
    cout << "print C: ";
    c.work();
}

int main()
{
    cout << "BEGIN TESTS" << endl;

    //testmove();

    /*
     A* ap = new A();
     B* bp = new B();
     A* abp = new B();
     print(*ap);
     print(*bp);
     print(*abp);
     */

    cout << endl << endl;

    B b;
    b.work();

    A a = b;
    a.work();

    C c;
    c.work();

    b = c;
    b.work();

    cout << "FINISHED OK!" << endl;
    return 0;
}

