//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#ifndef LAB2_DATALOGPROGRAM_H
#define LAB2_DATALOGPROGRAM_H

#include "Predicate.h"
#include <string>

class DatalogProgram {
public:
    DatalogProgram();
    ~DatalogProgram();
    void addScheme(Predicate *newScheme) { mySchemes.push_back(newScheme); }
    std::string toStringScheme();
private:
    std::vector<Predicate*> mySchemes;
    std::vector<Predicate*> myFacts;
    std::vector<Predicate*> myRules;
    std::vector<Predicate*> myQueries;
};


#endif //LAB2_DATALOGPROGRAM_H
