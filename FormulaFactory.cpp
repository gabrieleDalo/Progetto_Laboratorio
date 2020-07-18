//
// Created by Gabriele on 18/07/2020.
//

#include <vector>
#include <string>
#include <iostream>
#include "FormulaFactory.h"
#include "Somma.h"
#include "Max.h"
#include "Min.h"
#include "Mean.h"

string FormulaFactory::calculateOperation(string operation,vector<float> values){
    string somma = "SOMMA",max="MAX",min="MIN",mean="MEAN";
    string value;
    Formula* formula = 0;

    if(operation.compare(0,somma.length(),somma)==0) {
        cout << "Somma" << endl;
        formula = new Somma();
    }else if(operation.compare(0,max.length(),max)==0) {
        cout << "Max" << endl;
        formula = new Max();
    }else if(operation.compare(0,min.length(),min)==0) {
        cout << "Min" << endl;
        formula = new Min();
    }else if(operation.compare(0,mean.length(),mean)==0) {
        cout << "Mean" << endl;
        formula = new Mean();
    }else{
        cout << "Altro" << endl;
        value = "Error";
    }
    if(value != "Error")
        value = to_string(formula->calculate(values));

    return value;
}
