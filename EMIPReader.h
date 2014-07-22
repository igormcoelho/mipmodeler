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
};

struct epar
{
    string name;
    int nindex;
};

struct eset
{
    string name;
    int nindex;
};

class Reader
{
public:

    vector<evar*> vvar;
    vector<epar*> vpar;
    vector<eset*> vset;

    evar* getVar(string name)
    {
        for(unsigned i=0; i<vvar.size(); i++)
            if(vvar[i]->name == name)
                return vvar[i];
        return NULL;
    }

    epar* getParam(string name)
    {
        for(unsigned i=0; i<vpar.size(); i++)
            if(vpar[i]->name == name)
                return vpar[i];
        return NULL;
    }

    eset* getSet(string name)
    {
        for(unsigned i=0; i<vset.size(); i++)
            if(vset[i]->name == name)
                return vset[i];
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


        return mk.clone();
    }


};

}


#endif

