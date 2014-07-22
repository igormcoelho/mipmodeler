#ifndef EMIP_READER_H
#define EMIP_READER_H

#include "Scanner++/Scanner.h"

#include "EMIPModeler.h"

using namespace scannerpp;

namespace EMIP
{

struct evar
{
    string name;
    int nindex;
    double lb;
    double ub;
    Type type;

    evar(string _name, int _nindex, double _lb, double _ub, Type _type) :
        name(_name), nindex(_nindex), lb(_lb), ub(_ub), type(_type)
    {
        print();
    }

    void print()
    {
        cout << "evar('" << name << "', dim=" << nindex << ")" << endl;
    }
};

struct epar
{
    string name;
    int nindex;

    epar(string _name, int _nindex) :
        name(_name), nindex(_nindex)
    {
        print();
    }

    void print()
    {
        cout << "epar('" << name << "', dim=" << nindex << ")" << endl;
    }
};

struct eset
{
    string name;
    int nindex;

    eset(string _name, int _nindex) :
        name(_name), nindex(_nindex)
    {
        print();
    }

    void print()
    {
        cout << "eset('" << name << "', dim=" << nindex << ")" << endl;
    }
};

class Reader
{
public:

    vector<evar*> vvar;
    vector<epar*> vpar;
    vector<eset*> vset;

    // function get works for vvar, vpar and vset
    template<class T>
    T* get(string name, vector<T*>& vt)
    {
        for(unsigned i=0; i<vt.size(); i++)
            if(vt[i]->name == name)
                return vt[i];
        return NULL;
    }

    string removeComments(string text)
    {
        string out;
        bool inComment = false;
        Scanner s(text);
        while(s.hasNext())
        {
            char c = s.nextChar();
            if(!inComment && c=='#')
            {
                s.nextLine();
                continue;
            }

            if(!inComment && (c=='/') && s.nextCharIs('*'))
            {
                s.nextChar();
                inComment = true;
                continue;
            }

            if(inComment && (c=='*') && s.nextCharIs('/'))
            {
                s.nextChar();
                inComment = false;
                continue;
            }

            if(!inComment)
                out += c;
        }

        return out;
    }

    string joinSemicolon(string text)
    {
        stringstream ss;
        Scanner s(text);
        while(s.hasNext())
        {
            string word = s.next();
            ss << word << " ";
            if(word == ";")
                ss << endl;
        }
        return ss.str();
    }

    pair<string, string> separateModelData(string content, bool& minimize)
    {
        minimize = false;
        bool found = false;
        Scanner scan(content);
        stringstream ss1;
        while(scan.hasNext())
        {
            string line = Scanner::trim(scan.nextLine());
            Scanner s(line);
            string word = s.next();
            if(word == "minimize")
            {
                minimize = true;
                found = true;
            }

            if(word == "maximize")
            {
                minimize = false;
                found = true;
            }

            if(word != "data")
                ss1 << line << endl;
            else
                break;
        }

        stringstream ss2;
        while(scan.hasNext())
        {
            string line = Scanner::trim(scan.nextLine());
            ss2 << line << endl;
        }

        if(!found)
        {
            cout << "ERROR: didn't find 'minimize' or 'maximize' in model part" << endl;
            exit(1);
        }

        return make_pair(ss1.str(), ss2.str());
    }

    string addSpaces(string text)
    {
        string output;
        for(unsigned i=0; i<text.length(); i++)
            switch(text[i])
            {
            case ')':
                output += ' ';
            case '(':
            {
                output += text[i];
                output += ' ';
                break;
            }
            case '{':
            case '}':
            case '[':
            case ']':
            case ',':
            case ';':
            case ':':
            case '+':
            case '-':
            case '*':
            case '/':
            {
                output += ' ';
                output += text[i];
                output += ' ';
                break;
            }
            case '=':
            {
                if((text[i-1] != '<') && (text[i-1] != '>'))
                    output += ' ';
                output += text[i];
                output += ' ';
                break;
            }
            case '>':
            case '<':
            {
                output += ' ';
                output += text[i];
                if(text[i+1] != '=')
                    output += ' ';
                break;
            }
            case '.':
            {
                if(text[i+1] == '.')
                {
                    output += ' ';
                    output += text[i];
                }
                if(text[i-1] == '.')
                {
                    output += text[i];
                    output += ' ';
                }
                break;
            }
            default:
                output += text[i];
            }

        return output;
    }

    vector<string> readListNoHead(Scanner& s)
    {
        vector<string> r;
        s.useSeparators(", \t");
        string elem = s.next();
        while(elem != "}")
        {
            r.push_back(elem);
            elem = s.next();
        }
        s.useDefaultSeparators();
        return r;
    }


    string findSetVarParam(string text)
    {
        stringstream ss;
        Scanner s(text);
        while(s.hasNext())
        {
            string token = s.next();
            if(token == "set")
            {
                string name = s.next();
                string block = s.next();
                if(block != ";")
                {
                    cout << "ERROR: NOT SUPPORTING SPECIFICATION OVER SETS (dimen, etc)!" << endl;
                    exit(1);
                }
                vset.push_back(new eset(name, 1));
            }
            else if(token == "var")
            {


            }
            else if(token == "param")
            {
                string name = s.next();
                string block = s.next();
                vector<string> vs;
                if(block != ";")
                {
                    vs = readListNoHead(s);
                    block = s.next();
                }

                vpar.push_back(new epar(name, vs.size()));
            }
            else
                ss << token << " " << s.nextLine() << endl;
        }

        return ss.str();
    }

    Modeler& readFile(string filename)
    {
        Scanner scanAll(new File(filename));
        string text1 = removeComments(scanAll.rest());
        string text = joinSemicolon(addSpaces(text1));
        bool minimize = true;
        pair<string, string> pmd = separateModelData(text, minimize);
        string model = pmd.first;

        Modeler mk = (minimize?Modeler(Minimize):Modeler(Maximize));

        cout << "MODEL" << endl << pmd.first;
        cout << "DATA"  << endl << pmd.second;

        cout << "WILL READ MODEL PART" << endl;

        string ctrs = findSetVarParam(pmd.first);

        cout << "REST" << endl << ctrs;

        return mk.clone();
    }


};

}


#endif

