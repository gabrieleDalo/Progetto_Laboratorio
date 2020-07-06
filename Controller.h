//
// Created by Gabriele on 06/07/2020.
//

#ifndef PROGETTO_LABORATORIO_CONTROLLER_H
#define PROGETTO_LABORATORIO_CONTROLLER_H

#include "Model.h"

class Controller {
public:
    Controller(Model* m) : model(m) {}
private:
    Model* model;
};


#endif //PROGETTO_LABORATORIO_CONTROLLER_H
