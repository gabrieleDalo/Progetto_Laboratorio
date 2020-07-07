//
// Created by Gabriele on 06/07/2020.
//

#ifndef PROGETTO_LABORATORIO_OBSERVER_H
#define PROGETTO_LABORATORIO_OBSERVER_H

class Observer {  // Abstract Observer
public:
    virtual	void update(int x,int y,float value) = 0;
    virtual ~Observer() {}
};


#endif //PROGETTO_LABORATORIO_OBSERVER_H
