//
// Created by Gabriele on 18/07/2020.
//

#ifndef PROGETTO_LABORATORIO_CELL_H
#define PROGETTO_LABORATORIO_CELL_H
#include <list>
#include <string>
#include "Subject.h"

class Cell : public Subject, public Observer {
public:
    Cell(){}

    Cell(int row, int column, float value, const string &formula) : row(row), column(column), value(value),formula(formula) {}

    void update(int x, int y, float value) override;

    void update(int x, int y, string value) override;

    void updateCell(int x, int y);

    void addObserver(Observer *o) override;

    void addSubject(Subject *s);

    void removeObserver(Observer *o) override;

    void removeSubjects();

    void removeObservers();

    void notify(int x, int y, float value) override;

    void notify(int x, int y, string value) override;

    pair<bool,list<pair<int,int>>> notifyCell(int x,int y);

    Cell* getCell() {
        return this;
    }

    int getRow() const {
        return row;
    }

    void setRow(int row) {
        Cell::row = row;
    }

    int getColumn() const {
        return column;
    }

    void setColumn(int column) {
        Cell::column = column;
    }

    float getValue() const {
        return value;
    }

    void setValue(float value) {
        Cell::value = value;
    }

    const string &getFormula() const {
        return formula;
    }

    void setFormula(const string &formula) {
        Cell::formula = formula;
    }

private:
    int row, column;
    float value;
    string formula;
    list<Cell*> subjects;
    list<Cell*> observers;
};


#endif //PROGETTO_LABORATORIO_CELL_H
