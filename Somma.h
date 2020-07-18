//
// Created by Gabriele on 18/07/2020.
//

#ifndef PROGETTO_LABORATORIO_SOMMA_H
#define PROGETTO_LABORATORIO_SOMMA_H

#include <algorithm>
#include <numeric>
#include "Formula.h"

class Somma : public Formula{
public:
    float calculate(vector<float> values) override {
        return accumulate(values.begin(),values.end(),0.0);
    }
};

#endif //PROGETTO_LABORATORIO_SOMMA_H
