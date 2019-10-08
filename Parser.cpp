//
// Created by Kekoapo'aono Montalbo on 10/6/19.
//

#include "Parser.h"

bool Parser::checkProgram()
{
    try {
        checkDataLogProg();
    } catch (Token* thrownToken)
    {
        badToken = thrownToken;
        return false;
    }

    return true;
}

void Parser::checkDataLogProg()
{
    //SCHEMES
    if (myTokens->at(curPos)->getTokenType() == SCHEMES) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //scheme
    scheme();

    //schemeList
    schemeList();

    //FACTS
    if (myTokens->at(curPos)->getTokenType() == FACTS) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //factList
    factList();

    //RULES
    if (myTokens->at(curPos)->getTokenType() == RULES) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //ruleList
    ruleList();

    //QUERIES
    if (myTokens->at(curPos)->getTokenType() == QUERIES) { curPos++; }
    else { throw myTokens->at(curPos); }

    //COLON
    if (myTokens->at(curPos)->getTokenType() == COLON) { curPos++; }
    else { throw myTokens->at(curPos); }

    //queryList
    queryList();

    //EOF
    if (myTokens->at(curPos)->getTokenType() == EndOfFile) {}
    else { throw myTokens->at(curPos); }
}

void Parser::schemeList()
{
    if (myTokens->at(curPos)->getTokenType() != FACTS)
    {
        scheme();
        if (myTokens->at(curPos)->getTokenType() != FACTS) { schemeList(); }
    }
}

void Parser::factList()
{
    if (myTokens->at(curPos)->getTokenType() != RULES)
    {
        fact();
        if (myTokens->at(curPos)->getTokenType() != RULES) { factList(); }
    }
}

void Parser::ruleList()
{
    if (myTokens->at(curPos)->getTokenType() != QUERIES)
    {
        rule();
        if (myTokens->at(curPos)->getTokenType() != QUERIES) { ruleList(); }
    }
}

void Parser::queryList()
{
    if (myTokens->at(curPos)->getTokenType() != EndOfFile)
    {
        query();
        if (myTokens->at(curPos)->getTokenType() != EndOfFile) { queryList(); }
    }
}

void Parser::scheme()
{
    auto *thisScheme = new std::vector<std::string*>();
    //ID
    if (myTokens->at(curPos)->getTokenType() == ID)
    {
        thisScheme->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
        curPos++;
    }
    else { throw myTokens->at(curPos); }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else
        {
            for (int i = 0; i < thisScheme->size(); ++i)
            {
                delete thisScheme->at(i);
            }

            delete thisScheme;

            throw myTokens->at(curPos);
        }

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) { curPos++; }
    else
        {
            for (int i = 0; i < thisScheme->size(); ++i)
            {
                delete thisScheme->at(i);
            }

            delete thisScheme;

            throw myTokens->at(curPos);
        }

    //idList
    idList(thisScheme);

    //Create & Add scheme to DataLogProgram
    auto *myScheme = new Predicate(thisScheme);
    myProgram->addScheme(myScheme);

    //Delete my scheme pointers
    for (int i = 0; i < thisScheme->size(); ++i)
    {
        delete thisScheme->at(i);
    }

    delete thisScheme;

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::fact()
{
    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) { curPos++; }
    else { throw myTokens->at(curPos); }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }

    //STRING
    if (myTokens->at(curPos)->getTokenType() == STRING) { curPos++; }
    else { throw myTokens->at(curPos); }
    //stringList
    stringList();

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }

    //PERIOD
    if (myTokens->at(curPos)->getTokenType() == PERIOD) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::rule()
{
    //headPredicate
    headPredicate();

    //COLON_DASH
    if (myTokens->at(curPos)->getTokenType() == COLON_DASH) { curPos++; }
    else { throw myTokens->at(curPos); }

    //predicate
    predicate();

    //predicateList
    predicateList();

    //PERIOD
    if (myTokens->at(curPos)->getTokenType() == PERIOD) { curPos++; }
    else if (myTokens->at(curPos)->getTokenType() != PERIOD) { throw myTokens->at(curPos); }
}

void Parser::query()
{
    //predicate
    predicate();
    // Q_MARK
    if (myTokens->at(curPos)->getTokenType() == Q_MARK) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::headPredicate()
{
    auto *thisRule = new std::vector<std::string*>();

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) { curPos++; }
    else { throw myTokens->at(curPos); }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }

    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) { curPos++; }
    else { throw myTokens->at(curPos); }

    //idList
    idList(thisRule);

    //Delete my Rule pointers
    for (int i = 0; i < thisRule->size(); ++i)
    {
        delete thisRule->at(i);
    }

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::predicate()
{
    //ID
    if (myTokens->at(curPos)->getTokenType() == ID) { curPos++; }
    else { throw *myTokens->at(curPos); }

    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }

    //parameter
    parameter();

    //parameterList
    parameterList();

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::predicateList() {
    if (myTokens->at(curPos)->getTokenType() != PERIOD)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else { throw myTokens->at(curPos); }

        // predicate
        predicate();

        // predicateList
        if (myTokens->at(curPos)->getTokenType() != PERIOD) { predicateList(); }
    }
}

void Parser::parameterList()
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else { throw myTokens->at(curPos); }

        //parameter
        parameter();

        //parameterList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { parameterList(); }
    }
}

void Parser::stringList()
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else { throw myTokens->at(curPos); }

        //STRING
        if (myTokens->at(curPos)->getTokenType() == STRING) { curPos++; }
        else { throw myTokens->at(curPos); }

        //stringList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { stringList(); }
    }
}

void Parser::idList(std::vector<std::string*> *schemeList)
{
    if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN)
    {
        //COMMA
        if (myTokens->at(curPos)->getTokenType() == COMMA) { curPos++; }
        else
            {
                for (int i = 0; i < schemeList->size(); ++i)
                {
                    delete schemeList->at(i);
                }

                delete schemeList;

                throw myTokens->at(curPos);
            }

        //ID
        if (myTokens->at(curPos)->getTokenType() == ID)
        {
            schemeList->push_back(new std::string(myTokens->at(curPos)->getTokenString()));
            curPos++;
        }

        else
            {

                for (int i = 0; i < schemeList->size(); ++i)
                {
                    delete schemeList->at(i);
                }

                delete schemeList;

                throw myTokens->at(curPos);
            }

        //idList
        if (myTokens->at(curPos)->getTokenType() != RIGHT_PAREN) { idList(schemeList); }
    }
}

void Parser::parameter()
{
    //STRING ,ID, expression
    if (myTokens->at(curPos)->getTokenType() == ID || myTokens->at(curPos)->getTokenType() == STRING) { curPos++; }
    else { expression(); }
}

void Parser::expression()
{
    //LEFT_PAREN
    if (myTokens->at(curPos)->getTokenType() == LEFT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }

    //parameter
    parameter();

    //operator
    op();

    //parameter
    parameter();

    //RIGHT_PAREN
    if (myTokens->at(curPos)->getTokenType() == RIGHT_PAREN) { curPos++; }
    else { throw myTokens->at(curPos); }
}

void Parser::op()
{
    //ADD | MULTIPLY
    if (myTokens->at(curPos)->getTokenType() == ADD || myTokens->at(curPos)->getTokenType() == MULTIPLY) { curPos++; }
    else { throw myTokens->at(curPos); }
}
