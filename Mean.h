/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#ifndef PROGETTO_LABORATORIO_MEAN_H
#define PROGETTO_LABORATORIO_MEAN_H

#include <algorithm>
#include <numeric>
#include "Formula.h"

class Mean : public Formula{
public:
    float calculate(vector<float> values) override {
        return (std::accumulate(values.begin(),values.end(),0.0))/values.size();
    }
};

#endif //PROGETTO_LABORATORIO_MEAN_H
