//
// Created by Kekoapo'aono Montalbo on 10/7/19.
//

#ifndef LAB2_RULES_H
#define LAB2_RULES_H

#include <vector>
#include "Predicate.h"

class Rules {
public:
    Rules();
private:
    Predicate rulesName;
    std::vector<Predicate> predList;
};

#endif //LAB2_RULES_H
