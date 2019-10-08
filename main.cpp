#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Token.h"

int main(int argc, char* argv[]) {
    std::string fileName = argv[1];
    std::vector<Token*> *myTokens;
    Scanner myScanner(fileName);

    myTokens = myScanner.tokenize();

    std::vector<int> deleteThese;
    for (int i = 0; i < myTokens->size(); i++)
    {
        if ((*myTokens).at(i) == NULL || myTokens->at(i)->getTokenType() == COMMENT)
        {
            deleteThese.push_back(i);
        }
    }

    for (int i = deleteThese.size() - 1; i >= 0; i--)
    {
        delete myTokens->at(deleteThese[i]);
        myTokens->erase(myTokens->begin() + deleteThese[i]);
    }

    Parser myParser(myTokens);
    DatalogProgram* myProgram = myParser.getProg();

    if (myParser.getValidProg())
    {
        std::cout << "Success!" << std::endl;
        myProgram->toStringScheme();
    }

    else
    {
        std::cout << "Failure!" << std::endl << "  " << myParser.getBadToken()->toString();
    }

    delete myProgram;

    for (int i = 0; i < myTokens->size(); i++)
    {
        delete myTokens->at(i);
    }

    delete myTokens;

    return 0;
}
