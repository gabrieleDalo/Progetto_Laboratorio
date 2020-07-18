//
// Created by Gabriele on 18/07/2020.
//

#ifndef PROGETTO_LABORATORIO_FORMULA_H
#define PROGETTO_LABORATORIO_FORMULA_H

#include <vector>
using namespace std;

class Formula{
public:
    virtual float calculate(vector<float> values) = 0;
};

#endif //PROGETTO_LABORATORIO_FORMULA_H
