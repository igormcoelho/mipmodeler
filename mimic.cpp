// Author: Igor Machado Coelho
// Date: 10-09-2014
// Introduction to the MoveSwap C++ Pattern

// The MoveSwap Pattern makes a class imitate the behavior
// of another class (usually an inherited one).

#include<assert.h>
#include<stdio.h>
#include<iostream>

using namespace std;

class Mimic
{
private:
    Mimic* mimic;

protected:
    Mimic()
    {
        //cout << __PRETTY_FUNCTION__ << endl;
        mimic = NULL;
    }

public:

    virtual ~Mimic()
    {
        if (mimic)
            delete mimic;
    }

    Mimic(const Mimic& b)
    {
        if (b.mimic)
            b.mimic->clone(mimic);
        else
            b.clone(mimic);
    }

    virtual void clone(Mimic*& m) const
    {
        m = new Mimic(*this);
    }

    virtual void work() const
    {
        assert(mimic);
        mimic->work();
    }

    Mimic& operator=(const Mimic& m)
    {
        if (&m == this)
            return *this;
        if (mimic)
        {
            delete mimic;
            mimic = NULL;
        }
        if (m.mimic)
            m.mimic->clone(mimic);
        else
            m.clone(mimic);
        return *this;
    }
};

// Base class should include mimic variable
// designed for originally pure abstract classes
class MimicBase
{
private:
    MimicBase* mimic;

protected:
    MimicBase()
    {
        mimic = NULL;
    }

public:

    virtual ~MimicBase()
    {
        if (mimic)
            delete mimic;
    }

    MimicBase(const MimicBase& b)
    {
        if (b.mimic)
            mimic = &b.mimic->clone();
        else
            mimic = &b.clone();
    }

    virtual MimicBase& clone() const
    {
        return *new MimicBase(*this);
    }

    inline virtual void work() const
    {
        assert(mimic);
        mimic->work();
    }

    MimicBase& operator=(const MimicBase& m)
    {
        if (&m == this)
            return *this;
        if (mimic)
        {
            delete mimic;
            mimic = NULL;
        }
        if (m.mimic)
            mimic = &m.mimic->clone();
        else
            mimic = &m.clone();
        return *this;
    }
};

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

/*
 class Include
 {
 private:


 public:
 Include(Move& m)
 : base(m), mimic(MoveSwap(9,8))
 {
 }

 Include()
 : mimic(MoveSwap(3,4)), base(NULL)
 {
 }

 void callWork()
 {
 cout << "call work" << endl;
 mimic.work();
 }

 private:
 MoveSwap mimic;
 Move base;
 };
 */

class NS
{
public:

    NS()
    {
    }

    virtual ~NS()
    {
    }

    virtual Move generate() = 0;
};

class NSSwap: public NS
{
public:

    Move generate()
    {
        MoveSwap mv(0, 99);

        cout << "will return (" << &mv << ")" << endl;
        return mv;
    }

    MoveSwap generate2()
    {
        MoveSwap mv(2, 99);

        cout << "will return (" << &mv << ")" << endl;
        return mv;
    }

    Move generate3()
    {
        return MoveSwap(3, 99);
    }

    MoveSwap generate4()
    {
        return MoveSwap(4, 99);
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

    cout << "NSSWAP" << endl;
    NSSwap nsswap;
    cout << "generate()" << endl;
    Move mov = nsswap.generate();
    cout << "got " << &mov << endl;
    mov.work();

    cout << endl;

    cout << "generate2() no storage" << endl;
    nsswap.generate2();

    cout << endl;

    cout << "generate2() storage" << endl;
    MoveSwap mov2 = nsswap.generate2();
    cout << "got " << &mov2 << endl;
    mov2.work();

    cout << endl;

    cout << "generate3() storage" << endl;
    Move mov3 = nsswap.generate3();
    cout << "got " << &mov3 << endl;
    mov3.work();

    cout << endl;

    cout << "generate4() storage" << endl;
    MoveSwap mov4 = nsswap.generate4();
    cout << "got " << &mov4 << endl;
    mov4.work();

    cout << endl;

    cout << "MULTIPLE COPY" << endl;
    Move m5 = Move(Move(Move(MoveSwap(MoveSwap(MoveSwap(5, 88))))));
    m5.work();

    cout << endl;

    //cout << "EMPTY" << endl;
    //Move empty; // ERROR! protected constructor!
    //empty.work();
}

class A: public Mimic
{
private:
    A* mimic2;

public:

    A()
    {
        mimic2 = NULL;
    }

    A(const A& a)
    {
        if (a.mimic2)
            a.mimic2->clone(mimic2);
        else
            a.clone(mimic2);
    }

    virtual void work() const
    {
        if (mimic2)
        {
            mimic2->work();
            return;
        }

        cout << "A()" << endl;
    }

    virtual void clone(Mimic*& m) const
    {
        m = new A();
    }

    virtual void clone(A*& a) const
    {
        a = new A();
    }

    virtual A& operator=(const A& m)
    {
        if (&m == this)
            return *this;
        if (mimic2)
        {
            delete mimic2;
            mimic2 = NULL;
        }
        if (m.mimic2)
            m.mimic2->clone(mimic2);
        else
            m.clone(mimic2);

        return *this;
    }

};

class B: public A
{

public:

    B()
    {
    }

    B(const B& b) :
        A()
    {
    }

    virtual void work() const
    {
        cout << "B()" << endl;
    }

    virtual void clone(Mimic*& m) const
    {
        m = new B();
    }

    virtual void clone(A*& a) const
    {
        a = new B();
    }

    virtual B& operator=(const B& m)
    {
        if (&m == this)
            return *this;
        return *this;
    }

};

class C: public B
{

private:
    // USE THIS TO DISABLE FUTURE SLICINGS WITHOUT THE MIMIC
    // To force a compile error for non-friends (thanks bk1e)
    // Not implemented, so will cause a link error for friends
    template<typename T> C(T const& d);
    template<typename T> C const& operator=(T const& rhs);

public:

    C()
    {
    }

    C(const C& c) :
        B()
    {
    }

    virtual void work()
    {
        cout << "C()" << endl;
    }

    virtual void clone(Mimic* m)
    {
        m = new C();
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

    virtual void work()
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

    A* ap = new A();
    B* bp = new B();
    A* abp = new B();
    print(*ap);
    print(*bp);
    print(*abp);

    cout << endl << endl;


    B b;
    b.work();
    print(b);

    A a = b;
    a.work();
    print(a);

    C c;
    c.work();
    print(c);

    b = c;
    b.work();
    print(b);

    cout << "FINISHED OK!" << endl;
    return 0;
}

