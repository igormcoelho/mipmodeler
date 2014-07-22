#ifndef EMIP_READER_H
#define EMIP_READER_H

#include "Scanner++/Scanner.h"

#include "EMIPModeler.h"

using namespace scannerpp;

namespace EMIP
{

class Reader
{
public:

    string removeComments(string text)
    {
        stringstream ss;
        Scanner s(text);

        while(s.hasNext())
        {
            string line = s.nextLine();
            Scanner sLine(line);
            while(sLine.hasNext())
            {
                string word = sLine.next();
                if(word[0] == '#')
                    break;
                else
                    ss << word << " ";
            }
            ss << endl;
        }

        return ss.str();
    }

    string cleanEmptyLines(string text)
    {
        stringstream ss;
        Scanner s(text);
        while(s.hasNext())
        {
            string line = Scanner::trim(s.nextLine());
            if(line != "")
                ss << line << endl;
        }
        return ss.str();
    }

    pair<string, string> separateModelData(string content, bool& minimize)
    {
        minimize = false;
        Scanner scan(content);
        stringstream ss1;
        while(scan.hasNext())
        {
            string line = Scanner::trim(scan.nextLine());
            Scanner s(line);
            string word = s.next();
            if(word == "minimize")
                minimize = true;
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
        string text = addSpaces(cleanEmptyLines(text1));
        bool minimize = true;
        pair<string, string> pmd = separateModelData(text, minimize);

        Modeler mk = (minimize?Modeler(Minimize):Modeler(Maximize));

        cout << "MODEL" << endl << pmd.first;
        cout << "DATA"  << endl << pmd.second;


        return mk.clone();
    }


};

}


#endif

