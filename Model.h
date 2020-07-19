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

    void onAddFormula(int row,int column,int currentRow,int currentColumn){
        if(values.find(make_pair(currentRow,currentColumn)) != values.end() && values.find(make_pair(row,column)) != values.end()) {
            values.find(make_pair(currentRow, currentColumn))->second.addSubject(values.find(make_pair(row, column))->second.getCell());
            values.find(make_pair(row, column))->second.addObserver(values.find(make_pair(currentRow, currentColumn))->second.getCell());
        }
    }

    pair<bool,list<pair<int,int>>> onChangeCellFormula(int row,int column){
        return values.find(make_pair(row,column))->second.notifyCell(row,column);
    }

    bool findValue(int x,int y){
        if(x < 0 || x > width || y < 0 || y > height){
            throw out_of_range("Out of range values");
        }else{
            if(values.find(make_pair(x,y)) != values.end())
                return true;
            else
                return false;
        }
    }

    float getValue(int x,int y) const {
        if(x < 0 || x > width || y < 0 || y > height){
            throw out_of_range("Out of range values");
        }else{
            if(values.find(make_pair(x,y)) != values.end())
                return values.find(make_pair(x,y))->second.getValue();
            else
                return 0;
        }
    }

    string getFormula(int x,int y) const {
        if(x < 0 || x > width || y < 0 || y > height){
            throw out_of_range("Out of range values");
        }else{
            if(values.find(make_pair(x,y)) != values.end())
                return values.find(make_pair(x,y))->second.getFormula();
            else
                return "";
        }
    }

    void setValue(int x,int y,int row,int column,float value,string formula,bool modified) {
        if(x < 0 || x > width || y < 0 || y > height || row < 0 || row > width || column < 0 || column > width-1){
            throw out_of_range("Out of range values");
        }else{

            if(modified){
                values.find(make_pair(row,column))->second.removeObservers();
                values.find(make_pair(row,column))->second.removeSubjects();
            }

            values[make_pair(row,column)].setRow(row);
            values[make_pair(row,column)].setColumn(column);
            values[make_pair(row,column)].setValue(value);
            values[make_pair(row,column)].setFormula(formula);
            notify(x,y,value);
        }
    }

    void setValue(int x,int y,int row,int column,string value,string formula,bool modified) {
        if(x < 0 || x > width || y < 0 || y > height || row < 0 || row > width || column < 0 || column > width-1){
            throw out_of_range("Out of range values");
        }else{
            if(modified){
                values.find(make_pair(row,column))->second.removeObservers();
                values.find(make_pair(row,column))->second.removeSubjects();
            }

            values[make_pair(row,column)].setRow(row);
            values[make_pair(row,column)].setColumn(column);
            values[make_pair(row,column)].setValue(0);
            values[make_pair(row,column)].setFormula(formula);
            notify(x,y,value);
        }
    }

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
