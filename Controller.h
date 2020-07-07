//
// Created by Gabriele on 06/07/2020.
//

#ifndef PROGETTO_LABORATORIO_CONTROLLER_H
#define PROGETTO_LABORATORIO_CONTROLLER_H

#include "Model.h"

class Controller {
public:
    explicit Controller(Model* m) : model(m) {}

    bool checkOperation(int x,int y,string data);

    float checkString(string data);

    float checkFormula(string data);
private:
    Model* model;
};


#endif //PROGETTO_LABORATORIO_CONTROLLER_H
