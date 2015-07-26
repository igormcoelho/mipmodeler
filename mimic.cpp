// Author: Igor Machado Coelho
// Date: 10-09-2014
// Introduction to the MoveSwap C++ Pattern

// The MoveSwap Pattern makes a class imitate the behavior
// of another class (usually an inherited one).

#include<assert.h>
#include<iostream>

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

    inline virtual void work() const
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

int main()
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

    cout << "FINISHED OK!" << endl;
    return 0;
}
;

