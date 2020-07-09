//
// Created by Gabriele on 09/07/2020.
//

#ifndef PROGETTO_LABORATORIO_CELL_H
#define PROGETTO_LABORATORIO_CELL_H
#include <string>
using namespace std;

class Cell {
public:
    Cell(float value, const string &row, const string &column) : value(value), row(row), column(column) {}

    Cell() {}

    float getValue() const;

    void setValue(float value);

    const string &getRow() const;

    void setRow(const string &row);

    const string &getColumn() const;

    void setColumn(const string &column);

private:
    float value;
    string row,column;
};


#endif //PROGETTO_LABORATORIO_CELL_H
