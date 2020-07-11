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
    error = false;

    try{
        stof(data);
        if(data != "0.00"){
            model->setValue(x,y,convertLabelValue(row),convertLabelValue(column),0);
        }
    }catch (invalid_argument &exception){
        model->setValue(x,y,convertLabelValue(row),convertLabelValue(column),data);
        error = true;
    }catch(out_of_range &exception){
        model->setValue(x,y,convertLabelValue(row),convertLabelValue(column),data);
        error = true;
    }

    if(!error || data.at(0) == '=') {
        if (data.at(0) == '=') {
            error = false;
            //Chiamata operazione a seconda di ciò che c'è dopo =
            data = data.substr(1);
            transform(data.begin(), data.end(), data.begin(), ::toupper);
            value = checkFormula(data);
        } else {
            value = checkString(data);
        }
        model->setValue(x, y, convertLabelValue(row), convertLabelValue(column), value);
    }
    cout << "X: " << x << " Y: " << y << " Row:" << row << " Column:" << column << " Value:" << model->getValue(convertLabelValue(row), convertLabelValue(column)) << endl;
}

float Controller::checkString(string data){
    float value;

    if(data.size()>7)
        data = data.substr(0,7);

    try{
        value = stof(data);
    }catch (invalid_argument &exception){
        value = 0;
        error = true;
    }catch(out_of_range &exception){
        value = 0;
        error = true;
    }

    value = round(value*100)/100;

    return value;
}

float Controller::checkFormula(string data) {
    string somma = "SOMMA(",max="MAX(",min="MIN(",mean="MEAN(";
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
        error = true;
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
    string help,copyHelp;
    int firstRow,lastRow;
    int firstColumn,lastColumn;
    int row,column;
    int counter;

    if(data.find(')') != string::npos && data.at(0) != ')') {
        data = data.substr(0, data.find(')', 0));
        if(data.find(';') != string::npos){
            counter = count(data.begin(),data.end(),';');
            for(int i = 0;i <= counter;i++){
                help = data.substr(0, data.find(';'));
                if (count(help.begin(), help.end(), ',') == 1) {
                    copyHelp = help;
                    try {
                        stoi(help.substr(0, help.find(',')));
                        try {
                            stoi(copyHelp.erase(0, copyHelp.find_first_of(',')+1));
                            values.push_back(0);
                            error = true;
                        } catch (invalid_argument &exception) {
                            firstRow = convertLabelValue(help.substr(0, help.find(',')));
                            firstColumn = convertLabelValue(help.erase(0, help.find(',') + 1));
                        }
                    } catch (invalid_argument &exception) {
                        try {
                            stoi(copyHelp.erase(0, copyHelp.find_first_of(',')+1));
                            firstColumn = convertLabelValue(help.substr(0, help.find(',')));
                            firstRow = convertLabelValue(help.erase(0, help.find(',') + 1));
                        } catch (invalid_argument &exception) {
                            values.push_back(0);
                            error = true;
                        }
                    }

                    values.push_back(model->getValue(firstRow, firstColumn));
                    data.erase(0, data.find_first_of(';'));

                    if (data.find(';') != string::npos)
                        data = data.substr(1);
                }else{
                    values.push_back(0);
                    error = true;
                    i = counter;
                }
            }
        }else{
            if (data.find(':') != string::npos) {
                help = data;
                if (count(data.begin(), data.end(), ':') == 1) {
                    help = data.substr(0, data.find(':'));
                    data.erase(0, data.find_first_of(':'));
                    data = data.substr(1);

                    if (count(help.begin(), help.end(), ',') == 1 && count(data.begin(), data.end(),',') == 1) {

                        copyHelp = help;
                        try {
                            stoi(help.substr(0, help.find(',')));
                            try {
                                stoi(copyHelp.erase(0, copyHelp.find_first_of(',')+1));
                                values.push_back(0);
                                error = true;
                            } catch (invalid_argument &exception) {
                                firstRow = convertLabelValue(help.substr(0, help.find(',')));
                                firstColumn = convertLabelValue(help.erase(0, help.find(',') + 1));
                            }
                        } catch (invalid_argument &exception) {
                            try {
                                stoi(copyHelp.erase(0, copyHelp.find_first_of(',')+1));
                                firstColumn = convertLabelValue(help.substr(0, help.find(',')));
                                firstRow = convertLabelValue(help.erase(0, help.find(',') + 1));
                            } catch (invalid_argument &exception) {
                                values.push_back(0);
                                error = true;
                            }
                        }
                        copyHelp = data;
                        try {
                            stoi(data.substr(0, data.find(',')));
                            try {
                                stoi(copyHelp.erase(0, copyHelp.find_first_of(',')+1));
                                values.push_back(0);
                                error = true;
                            } catch (invalid_argument &exception) {
                                lastRow = convertLabelValue(data.substr(0, data.find(',')));
                                lastColumn = convertLabelValue(data.erase(0, data.find(',') + 1));
                            }
                        } catch (invalid_argument &exception) {
                            try {
                                stoi(copyHelp.erase(0, copyHelp.find_first_of(',')+1));
                                lastColumn = convertLabelValue(data.substr(0, data.find(',')));
                                lastRow = convertLabelValue(data.erase(0, data.find(',') + 1));
                            } catch (invalid_argument &exception) {
                                values.push_back(0);
                                error = true;
                            }
                        }
                    } else {
                        values.push_back(0);
                        error = true;
                    }
                } else {
                    values.push_back(0);
                    error = true;
                }
            } else if (data.find(',') != string::npos) {
                help = data;
                if (count(data.begin(), data.end(), ',') == 1) {
                    try {
                        stoi(data.substr(0, data.find(',')));
                        try {
                            stoi(help.erase(0, help.find_first_of(',')+1));
                            values.push_back(0);
                            error = true;
                        } catch (invalid_argument &exception) {
                            firstRow = convertLabelValue(data.substr(0, data.find(',')));
                            lastRow = firstRow;
                            firstColumn = convertLabelValue(data.erase(0, data.find(',') + 1));
                            lastColumn = firstColumn;
                        }
                    } catch (invalid_argument &exception) {
                        try {
                            stoi(help.erase(0, help.find_first_of(',')+1));
                            firstColumn = convertLabelValue(data.substr(0, data.find(',')));
                            lastColumn = firstColumn;
                            firstRow = convertLabelValue(data.erase(0, data.find(',') + 1));
                            lastRow = firstRow;
                        } catch (invalid_argument &exception) {
                            values.push_back(0);
                            error = true;
                        }
                    }
                } else {
                    values.push_back(0);
                    error = true;
                }
            } else {
                try {
                    stoi(data);
                    firstRow = convertLabelValue(data);
                    lastRow = firstRow;
                    firstColumn = 1;
                    lastColumn = model->getWidth();
                } catch (invalid_argument &exception) {
                    firstColumn = convertLabelValue(data);
                    lastColumn = firstColumn;
                    firstRow = 0;
                    lastRow = model->getHeight();
                }
            }

            if (!error) {

                if (firstRow > lastRow)
                    swap(firstRow, lastRow);
                if (firstColumn > lastColumn)
                    swap(firstColumn, lastColumn);

                row = firstRow;
                column = firstColumn;

                while (row <= lastRow) {
                    column = firstColumn;
                    while (column <= lastColumn) {
                        values.push_back(model->getValue(row, column));
                        column++;
                    }
                    row++;
                }
            }
        }
    }else{
        values.push_back(0);
        error = true;
    }

    return values;
}

bool Controller::isError() const {
    return error;
}

void Controller::setError(bool error) {
    Controller::error = error;
}


