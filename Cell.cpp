//
// Created by Gabriele on 18/07/2020.
//

#include "Cell.h"
#include <iostream>

void Cell::update(int x, int y, float value) {
    this->setValue(value);
}

void Cell::update(int x, int y, string value) {
    this->setValue(0);
}

void Cell::updateCell(int x, int y) {
    cout << "OK: " << x << y << endl;
    this->setValue(10);
}

void Cell::addObserver(Observer *o) {
    if(find(observers.begin(), observers.end(), dynamic_cast<Cell*>(o)) == observers.end())
        observers.push_back(dynamic_cast<Cell*>(o));
}

void Cell::addSubject(Subject *s){
    if(find(subjects.begin(), subjects.end(), dynamic_cast<Cell*>(s)) == subjects.end())
        subjects.push_back(dynamic_cast<Cell*>(s));
}

void Cell::removeObserver(Observer *o) {
    observers.remove(dynamic_cast<Cell*>(o));
}

void Cell::removeSubjects() {
    subjects.clear();
}

void Cell::removeObservers() {
    for(auto itr : subjects){
        itr->removeObserver(this);
    }
}

void Cell::notify(int x, int y, float value) {
    for (Observer* observer : observers) {
        observer->update(x, y, value);
    }
}

void Cell::notify(int x, int y, string value) {
    for (Observer* observer : observers) {
        observer->update(x, y, value);
    }
}

pair<bool,list<pair<int,int>>> Cell::notifyCell(int x,int y) {
    bool changed = false;
    list<pair<int,int>> coordinates;

    if(!observers.empty())
        changed = true;

    for(auto itr : observers) {
        coordinates.emplace_back(itr->getRow(),itr->getColumn());
        itr->updateCell(itr->getRow(),itr->getColumn());
    }
    return make_pair(changed,coordinates);
}
