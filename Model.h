//
// Created by Gabriele on 06/07/2020.
//

#ifndef PROGETTO_LABORATORIO_MODEL_H
#define PROGETTO_LABORATORIO_MODEL_H

#include <list>
#include "Subject.h"
using namespace std;

class Model : public Subject {
public:
    void addObserver(Observer* o) override;

    void removeObserver(Observer* o) override;

    void notify() override;

    int getData() const {
        return data;
    }

    void setData(const int data) {
        this->data = data;
        notify();
    }
private:
    int data = 0;
    list<Observer*> observers;
};


#endif //PROGETTO_LABORATORIO_MODEL_H
