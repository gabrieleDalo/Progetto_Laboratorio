/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Controller.h"
#include "FormulaFactory.h"

// TODO Aggiungere gestione valori in caso cambino le celle alle quali delle formule fanno riferimento
// Funzione che controlla l'operazione da eseguire su una cella
void Controller::checkOperation(int x,int y,string row,string column,string data) {
    float value;
    error = false;

    try{
        stof(data);
        if(data != "0.00"){
            try {
                model->setValue(x, y, convertLabelValue(row), convertLabelValue(column), 0);
            } catch (out_of_range& e) {
                error = true;
            }
        }
    }catch (invalid_argument &exception){
        try {
            model->setValue(x, y, convertLabelValue(row), convertLabelValue(column), data);
            error = true;
        } catch (out_of_range& e) {
            error = true;
        }
    }catch(out_of_range &exception){
        try {
            model->setValue(x, y, convertLabelValue(row), convertLabelValue(column), data);
            error = true;
        } catch (out_of_range& e) {
            error = true;
        }
    }

    if(!error || data.at(0) == '=') {
        // Se è presente un = all'inizio della stringa,
        // esso specifica che ciò che lo segue deve essere il nome di una formula
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

// Funzione che controlla la stringa presente nella cella
float Controller::checkString(string data){
    float value;

    // Se la stringa supera la dimensione massima viene tagliata
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

    // Se la stringa è un numero esso viene approssimato a 2 cifre decimali
    value = round(value*100)/100;

    return value;
}

// Funzione che converte la label di una riga/colonna nel suo rispettivo valore x/y
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

// Funzione che controlla la formula inserita dall'utente
float Controller::checkFormula(string data) {
    float value;
    vector<float> v;
    string operation;
    FormulaFactory formula;

    if(data.find('(') != string::npos)
        operation = data.substr(0, data.find('(', 0));
    else
        error = true;

    if(!error) {
        data = data.substr(operation.size() + 1);
        v = getRange(data);
        operation = formula.calculateOperation(operation, v);

        if (operation != "Error") {
            try {
                value = stof(operation);
            } catch (invalid_argument &exception) {
                value = 0;
                error = true;
            } catch (out_of_range &exception) {
                value = 0;
                error = true;
            }
        } else {
            value = 0;
            error = true;
        }
    }else{
        value = 0;
    }

    return value;
}

// Funzione che restituisce un vettore contenente tutti i valori su cui devono essere eseguite le formule
vector<float> Controller::getRange(string data) {
    vector<float> values;
    string help,copyHelp;
    int firstRow,lastRow;
    int firstColumn,lastColumn;
    int row,column;
    int counter;

    // Vengono eseguiti i vari controlli sulla correttezza sintattica della stringa
    // inserita dall'utente, e vengono salvati i valori di conseguenza
    if(data.find(')') != string::npos && data.at(0) != ')' && !error) {
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

                    if(!error) {
                        try{
                            values.push_back(model->getValue(firstRow, firstColumn));
                        } catch (out_of_range& e) {
                            error = true;
                            values.push_back(0);
                        }
                    }

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
                                error = true;
                            }
                        }
                        copyHelp = data;
                        try {
                            stoi(data.substr(0, data.find(',')));
                            try {
                                stoi(copyHelp.erase(0, copyHelp.find_first_of(',')+1));
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
                                error = true;
                            }
                        }
                    } else {
                        error = true;
                    }
                } else {
                    error = true;
                }
            } else if (data.find(',') != string::npos) {
                help = data;
                if (count(data.begin(), data.end(), ',') == 1) {
                    try {
                        stoi(data.substr(0, data.find(',')));
                        try {
                            stoi(help.erase(0, help.find_first_of(',')+1));
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
                            error = true;
                        }
                    }
                } else {
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

                while(row <= lastRow){
                    column = firstColumn;
                    while (column <= lastColumn) {
                        try {
                            values.push_back(model->getValue(row, column));
                        } catch (out_of_range& e) {
                            values.push_back(0);
                        }
                        column++;
                    }
                    row++;
                }
            }else{
                values.push_back(0);
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

Model *Controller::getModel() const {
    return model;
}

void Controller::setModel(Model *model) {
    Controller::model = model;
}




