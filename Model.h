//
// Created by Gabriele on 06/07/2020.
//

#ifndef PROGETTO_LABORATORIO_MODEL_H
#define PROGETTO_LABORATORIO_MODEL_H

#include <iostream>
#include <list>
#include "Subject.h"
using namespace std;

class Model : public Subject {
public:
    Model(int width,int height) : width(width),height(height) {
        values = new float[width*height];
    }

    void addObserver(Observer* o) override;

    void removeObserver(Observer* o) override;

    void notify(int x,int y,float value) override;

    float getValue(const int x,const int y) const {
        return values[width*x+y];
    }

    void setValue(const int x,const int y,const float value) {
        values[width*x+y] = value;
        notify(x,y,value);
    }

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

private:
    int width,height;
    float* values;
    list<Observer*> observers;
};


#endif //PROGETTO_LABORATORIO_MODEL_H
