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
                if(word == "maximize:")
                    minimize = false;
            }
            ss << endl;
        }

        return ss.str();
    }

    Modeler& readFile(string filename)
    {
        bool minimize = true;


        Modeler mk = (minimize?Modeler(Minimize):Modeler(Maximize));



        return mk.clone();
    }


};

}


#endif

