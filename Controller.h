//
// Created by Gabriele on 06/07/2020.
//

#ifndef PROGETTO_LABORATORIO_CONTROLLER_H
#define PROGETTO_LABORATORIO_CONTROLLER_H

#include "Model.h"

class Controller {
public:
    explicit Controller(Model* m,bool error = false) : model(m),error(error) {}

    void checkOperation(int x,int y,string row,string column,string data);

    float checkString(string data);

    float checkFormula(string data);

    int convertLabelValue(string value);

    float calculateSum(vector<float> values);

    float calculateMax(vector<float> values);

    float calculateMin(vector<float> values);

    float calculateMean(vector<float> values);

    vector<float> getRange(string data);

    bool isError() const;

    void setError(bool error);

private:
    Model* model;
    bool error;
};


#endif //PROGETTO_LABORATORIO_CONTROLLER_H
