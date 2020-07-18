/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#ifndef PROGETTO_LABORATORIO_MODEL_H
#define PROGETTO_LABORATORIO_MODEL_H

#include <iostream>
#include <map>
#include <list>
#include "Subject.h"

using namespace std;

class Model : public Subject {   // Concrete Subject
public:
    Model(int width=0,int height=0) : width(width),height(height) {}

    virtual ~Model(){
        values.clear();
    }

    void addObserver(Observer* o) override;

    void removeObserver(Observer* o) override;

    void notify(int x,int y,float value) override;

    void notify(int x,int y,string value) override;

    float getValue(int x,int y) const {
        if(x < 0 || x > width || y < 0 || y > height){
            throw out_of_range("Out of range values");
        }else{
            return values.find(make_pair(x,y))->second;
        }
    }

    void setValue(int x,int y,int row,int column,float value) {
        if(x < 0 || x > width || y < 0 || y > height || row < 0 || row > width || column < 0 || column > width-1){
            throw out_of_range("Out of range values");
        }else{
            values[make_pair(row,column)] = value;
            notify(x,y,value);
        }
    }

    void setValue(int x,int y,int row,int column,string value) {
        if(x < 0 || x > width || y < 0 || y > height || row < 0 || row > width || column < 0 || column > width-1){
            throw out_of_range("Out of range values");
        }else{
            values[make_pair(row,column)] = 0;
            notify(x,y,value);
        }
    }

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);


private:
    int width,height;
    map<pair<int,int>,float> values;
    list<Observer*> observers;
};


#endif //PROGETTO_LABORATORIO_MODEL_H
