//
// Created by Gabriele on 06/07/2020.
//

#include <string>
#include <iostream>
#include <exception>
#include <cmath>
#include "Controller.h"

bool Controller::checkOperation(int x,int y,string data) {
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
    string somma = "somma",max="max",min="min",mean="mean";
    float value = 0;

    if(data.compare(0,somma.length(),somma)==0) {
        cout << "Somma" << endl;
    }else if(data.compare(0,max.length(),max)==0) {
        cout << "Max" << endl;
    }else if(data.compare(0,min.length(),min)==0) {
        cout << "Min" << endl;
    }else if(data.compare(0,mean.length(),mean)==0) {
        cout << "Mean" << endl;
    }else{
        cout << "Altro" << endl;
    }
    return value;
}
