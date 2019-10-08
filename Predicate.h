//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#ifndef LAB2_PREDICATE_H
#define LAB2_PREDICATE_H

#include <vector>
#include "Token.h"

class Predicate {
public:
    Predicate();
    Predicate(std::vector<std::string*> *newPred)
    {
        predName = *newPred->at(0);

        for (int i = 1; i < newPred->size(); ++i)
        {
            parmList.push_back(*newPred->at(i));
        }
    }

    std::string getName() { return predName; }
    std::vector<std::string> getParams() { return parmList; }
private:
    std::string predName;
    std::vector<std::string> parmList;
};


#endif //LAB2_PREDICATE_H
