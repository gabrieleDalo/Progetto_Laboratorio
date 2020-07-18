/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#ifndef PROGETTO_LABORATORIO_MIN_H
#define PROGETTO_LABORATORIO_MIN_H

#include <algorithm>
#include <numeric>
#include "Formula.h"

class Min : public Formula{
public:
    float calculate(vector<float> values) override {
        return *min_element(values.begin(),values.end());
    }
};

#endif //PROGETTO_LABORATORIO_MIN_H
