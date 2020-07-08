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

void Controller::checkOperation(int x,int y,string data) {
    float value;

    if(data.at(0)=='='){
        //Chiamata operazione a seconda di ciò che c'è dopo =
        data = data.substr(1);
        transform(data.begin(),data.end(),data.begin(),::tolower);

        value = checkFormula(data);
    }else{
        value = checkString(data);
    }

    model->setValue(x,y,value);
    cout << "X:" << x << " Y:" << y << " Value:" << value << endl;
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

    v.push_back(5);
    v.push_back(7.777);

    if(data.compare(0,somma.length(),somma)==0) {
        cout << "Somma" << endl;
        value = calculateSum(v);
    }else if(data.compare(0,max.length(),max)==0) {
        cout << "Max" << endl;
        value = calculateMax(v);
    }else if(data.compare(0,min.length(),min)==0) {
        cout << "Min" << endl;
        value = calculateMin(v);
    }else if(data.compare(0,mean.length(),mean)==0) {
        cout << "Mean" << endl;
        value = calculateMean(v);
    }else{
        cout << "Altro" << endl;
        value = 0;
    }
    return value;
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


