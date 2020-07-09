//
// Created by Gabriele on 09/07/2020.
//

#include "Cell.h"

float Cell::getValue() const {
    return value;
}

void Cell::setValue(float value) {
    Cell::value = value;
}

const string &Cell::getRow() const {
    return row;
}

void Cell::setRow(const string &row) {
    Cell::row = row;
}

const string &Cell::getColumn() const {
    return column;
}

void Cell::setColumn(const string &column) {
    Cell::column = column;
}
