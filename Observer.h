/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#ifndef PROGETTO_LABORATORIO_OBSERVER_H
#define PROGETTO_LABORATORIO_OBSERVER_H
using namespace std;

class Observer {  // Abstract Observer
public:
    virtual	void update(int x,int y,float value) = 0;
    virtual	void update(int x,int y,string value) = 0;
    virtual ~Observer() {}
};


#endif //PROGETTO_LABORATORIO_OBSERVER_H
