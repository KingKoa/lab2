//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#include "DatalogProgram.h"
DatalogProgram::~DatalogProgram()
{
    for (int i = 0; i < mySchemes.size(); ++i)
    {
        delete mySchemes.at(i);
    }

    for (int i = 0; i < myFacts.size(); ++i)
    {
        delete myFacts.at(i);
    }

    for (int i = 0; i < myQueries.size(); ++i)
    {
        delete myQueries.at(i);
    }

    for (int i = 0; i < myRules.size(); ++i)
    {
        delete myRules.at(i);
    }
}

std::string DatalogProgram::toStringScheme()
{
    std::string returnString = "";
    returnString += "Scheme(";
    returnString += std::to_string(mySchemes.size());
    returnString += "):\n";
    for(int i = 0; i < mySchemes.size(); ++i)
    {
        returnString += mySchemes.at(i)->getName();
        returnString += "(";
        std::vector<std::string> theParams = mySchemes.at(i)->getParams();
        for(int j = 0; j < theParams.size(); ++i)
        {
            returnString += theParams.at(i);
            if(j != theParams.size() - 1)
            {
                returnString += ",";
            }
        }
        returnString += ").\n";
    }

    return returnString;
}
