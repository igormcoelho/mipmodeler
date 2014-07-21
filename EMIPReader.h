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

    string removeComments(string filename, bool& minimize)
    {
        minimize = false;

        stringstream ss;
        Scanner s(new File(filename));

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
                if(word == "minimize")
                    minimize = true;
            }
            ss << endl;
        }

        return ss.str();
    }

    Modeler& readFile(string filename)
    {
        bool minimize = true;
        string text = removeComments(filename, minimize);


        Modeler mk = (minimize?Modeler(Minimize):Modeler(Maximize));

        cout << "text:\n" << text << endl;


        return mk.clone();
    }


};

}


#endif

