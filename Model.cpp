//
// Created by Gabriele on 06/07/2020.
//

#include "Model.h"

void Model::addObserver(Observer* o) {
    observers.push_back(o);
}

void Model::removeObserver(Observer* o) {
    observers.remove(o);
}

void Model::notify() {
    for (Observer* observer : observers)
        observer->update();
}