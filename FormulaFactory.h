//
// Created by Gabriele on 18/07/2020.
//

#ifndef PROGETTO_LABORATORIO_FORMULAFACTORY_H
#define PROGETTO_LABORATORIO_FORMULAFACTORY_H
#include <vector>
#include <string>
#include "Formula.h"
using namespace std;

class FormulaFactory{
public:
    string calculateOperation(string operation,vector<float> values);
};

#endif //PROGETTO_LABORATORIO_FORMULAFACTORY_H
