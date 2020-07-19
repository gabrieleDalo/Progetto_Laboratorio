/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#include "Model.h"

void Model::addObserver(Observer* o) {
    observers.push_back(o);
}

void Model::removeObserver(Observer* o) {
    observers.remove(o);
}

void Model::notify(int x,int y,float value) {
    for (Observer* observer : observers) {
        observer->update(x, y, value);
    }
}

void Model::notify(int x,int y,string value) {
    for (Observer* observer : observers)
        observer->update(x,y,value);
}

void Model::onAddFormula(int row,int column,int currentRow,int currentColumn){
    if(values.find(make_pair(currentRow,currentColumn)) != values.end() && values.find(make_pair(row,column)) != values.end()) {
        values.find(make_pair(currentRow, currentColumn))->second.addSubject(values.find(make_pair(row, column))->second.getCell());
        values.find(make_pair(row, column))->second.addObserver(values.find(make_pair(currentRow, currentColumn))->second.getCell());
    }
}

pair<bool,list<pair<int,int>>> Model::onChangeCellFormula(int row,int column){
    return values.find(make_pair(row,column))->second.notifyCell(row,column);
}

bool Model::findValue(int x,int y){
    if(x < 0 || x > width || y < 0 || y > height){
        throw out_of_range("Out of range values");
    }else{
        if(values.find(make_pair(x,y)) != values.end())
            return true;
        else
            return false;
    }
}

float Model::getValue(int x,int y) const {
    if(x < 0 || x > width || y < 0 || y > height){
        throw out_of_range("Out of range values");
    }else{
        if(values.find(make_pair(x,y)) != values.end())
            return values.find(make_pair(x,y))->second.getValue();
        else
            return 0;
    }
}

string Model::getFormula(int x,int y) const {
    if(x < 0 || x > width || y < 0 || y > height){
        throw out_of_range("Out of range values");
    }else{
        if(values.find(make_pair(x,y)) != values.end())
            return values.find(make_pair(x,y))->second.getFormula();
        else
            return "";
    }
}

void Model::setValue(int x,int y,int row,int column,float value,string formula,bool modified) {
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

void Model::setValue(int x,int y,int row,int column,string value,string formula,bool modified) {
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


