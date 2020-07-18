/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#ifndef PROGETTO_LABORATORIO_MAX_H
#define PROGETTO_LABORATORIO_MAX_H

#include <algorithm>
#include <numeric>
#include "Formula.h"

class Max : public Formula{
public:
    float calculate(vector<float> values) override {
        return *max_element(values.begin(),values.end());
    }
};

#endif //PROGETTO_LABORATORIO_MAX_H
