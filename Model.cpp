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

void Model::notify(int x,int y,float value) {
    for (Observer* observer : observers)
        observer->update(x,y,value);
}

int Model::getWidth() const {
    return width;
}

void Model::setWidth(int width) {
    Model::width = width;
}

int Model::getHeight() const {
    return height;
}

void Model::setHeight(int height) {
    Model::height = height;
}
