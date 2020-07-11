//
// Created by Gabriele on 06/07/2020.
//

#ifndef PROGETTO_LABORATORIO_SUBJECT_H
#define PROGETTO_LABORATORIO_SUBJECT_H

#include "Observer.h"

class Subject {  // Abstract Subject
public:
    virtual void addObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notify(int x,int y,float value) = 0;
    virtual void notify(int x,int y,string value) = 0;
    virtual ~Subject() {}
};



#endif //PROGETTO_LABORATORIO_SUBJECT_H
