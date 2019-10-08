//
// Created by Kekoapo'aono Montalbo on 10/6/19.
//

#ifndef CS_236_PARSER_H
#define CS_236_PARSER_H

#include "Token.h"
#include <vector>
#include <iostream>
#include "DatalogProgram.h"

class Parser {
public:
    Parser();
    Parser(std::vector<Token*> *newTokens) : myTokens(newTokens) { validProg = checkProgram(); }
    bool getValidProg() { return validProg; }
    Token* getBadToken() { return badToken; }
    DatalogProgram* getProg() { return myProgram; }
private:
    DatalogProgram *myProgram;
    std::vector<Token*> *myTokens;
    int curPos = 0;
    Token* badToken;
    bool validProg;

    bool checkProgram();
    void checkDataLogProg();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate();
    void predicate();
    void predicateList();
    void parameterList();
    void stringList();
    void idList(std::vector<std::string*> *schemeList);
    void parameter();
    void expression();
    void op();
};


#endif //CS_236_PARSER_H
