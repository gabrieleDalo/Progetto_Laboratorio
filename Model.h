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
#include "Cell.h"

using namespace std;

class Model : public Subject {   // Concrete Subject
public:
    Model(int width=0,int height=0) : width(width),height(height) {}

    virtual ~Model(){
        if(!values.empty())
            values.clear();
    }

    void addObserver(Observer* o) override;

    void removeObserver(Observer* o) override;

    void notify(int x,int y,float value) override;

    void notify(int x,int y,string value) override;

    void onAddFormula(int row,int column,int currentRow,int currentColumn);

    pair<bool,list<pair<int,int>>> onChangeCellFormula(int row,int column);

    bool findValue(int x,int y);

    float getValue(int x,int y) const;

    string getFormula(int x,int y) const;

    void setValue(int x,int y,int row,int column,float value,string formula,bool modified);

    void setValue(int x,int y,int row,int column,string value,string formula,bool modified);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);


private:
    int width,height;
    map<pair<int,int>,Cell> values;
    list<Observer*> observers;
};


#endif //PROGETTO_LABORATORIO_MODEL_H
