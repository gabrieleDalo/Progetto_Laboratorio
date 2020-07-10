//
// Created by Gabriele on 06/07/2020.
//

#include <string>
#include <iostream>
#include <exception>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Controller.h"

void Controller::checkOperation(int x,int y,string row,string column,string data) {
    float value;

    if(data.at(0)=='='){
        //Chiamata operazione a seconda di ciò che c'è dopo =
        data = data.substr(1);
        transform(data.begin(),data.end(),data.begin(),::tolower);

        value = checkFormula(data);
    }else{
        value = checkString(data);
    }

    model->setValue(x,y,convertLabelValue(row),convertLabelValue(column),value);

    cout << "X: " << x << " Y: " << y << " Row:" << row << " Column:" << column << " Value:" << model->getValue(convertLabelValue(row),convertLabelValue(column)) << endl;
}

float Controller::checkString(string data){
    float value;

    if(data.size()>7)
        data = data.substr(0,7);

    try{
        value = stof(data);
    }catch (invalid_argument &exception){
        value = 0;
    }catch(out_of_range &exception){
        value = 0;
    }

    value = round(value*100)/100;

    return value;
}

float Controller::checkFormula(string data) {
    string somma = "somma(",max="max(",min="min(",mean="mean(";
    float value;
    vector<float> v;

    if(data.compare(0,somma.length(),somma)==0) {
        cout << "Somma" << endl;
        data = data.substr(somma.size());
        v = getRange(data);
        value = calculateSum(v);
    }else if(data.compare(0,max.length(),max)==0) {
        cout << "Max" << endl;
        data = data.substr(max.size());
        v = getRange(data);
        value = calculateMax(v);
    }else if(data.compare(0,min.length(),min)==0) {
        cout << "Min" << endl;
        data = data.substr(min.size());
        v = getRange(data);
        value = calculateMin(v);
    }else if(data.compare(0,mean.length(),mean)==0) {
        cout << "Mean" << endl;
        data = data.substr(mean.size());
        v = getRange(data);
        value = calculateMean(v);
    }else{
        cout << "Altro" << endl;
        value = 0;
    }
    return value;
}

int Controller::convertLabelValue(string value){
    int convertedValue = 0;
    string newValue;

    try{
        convertedValue = stoi(value);
        convertedValue --;
    }catch (invalid_argument &exception){
        transform(value.begin(),value.end(),value.begin(),::toupper);

        for(const auto& itr : value){
            convertedValue *=26;
            convertedValue += itr - 'A' + 1;
        }

    }

    return convertedValue;
}

float Controller::calculateSum(const vector<float> values) {
    return accumulate(values.begin(),values.end(),0.0);
}

float Controller::calculateMax(const vector<float> values) {
    return *max_element(values.begin(),values.end());
}

float Controller::calculateMin(const vector<float> values) {
    return *std::min_element(values.begin(),values.end());
}

float Controller::calculateMean(const vector<float> values) {
    return (std::accumulate(values.begin(),values.end(),0.0))/values.size();
}

vector<float> Controller::getRange(string data) {
    vector<float> values;
    int firstRow,lastRow;
    int firstColumn,lastColumn;
    int row,column;

    if(data.find(')') != string::npos && data.at(0) != ')') {
        data = data.substr(0, data.find(')', 0));

        firstRow = convertLabelValue("3");
        lastRow = convertLabelValue("1");
        firstColumn = convertLabelValue("A");
        lastColumn = convertLabelValue("C");

        if(firstRow > lastRow)
            swap(firstRow,lastRow);
        if(firstColumn > lastColumn)
            swap(firstColumn,lastColumn);

        row = firstRow;
        column = firstColumn;

        while(row <= lastRow){
            cout << "Row: " << row << lastRow << endl;
            column = firstColumn;
            while(column <= lastColumn){
                values.push_back(model->getValue(row,column));
                cout << "Col: " << column << lastColumn << endl;
                column++;
            }
            row++;
        }

    }else{
        values.push_back(0);
    }

    return values;
}


