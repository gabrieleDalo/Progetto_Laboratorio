//
// Created by Gabriele on 12/07/2020.
//
#include "gtest/gtest.h"
#include "../Model.h"
#include "../Model.cpp"
#include "../Cell.h"
#include "../Cell.cpp"

TEST(Model, DefaultConstructor) {
    Model model;
    ASSERT_EQ(0, model.getWidth());
    ASSERT_EQ(0, model.getHeight());
}

TEST(Model, TestGetValue) {
    Model model;
    model.setWidth(100);
    model.setHeight(52);
    model.setValue(2,2,2,1,12,"",false);
    model.setValue(2,1,2,0,"Test","",false);
    ASSERT_EQ(12, model.getValue(2,1));
    ASSERT_EQ(0,model.getValue(2,0));
    ASSERT_EQ(100, model.getWidth());
    ASSERT_EQ(52,model.getHeight());
}

TEST(Model, TestGetFormula) {
    Model model;
    model.setWidth(100);
    model.setHeight(52);
    model.setValue(2,2,2,1,12,"",false);
    model.setValue(2,1,2,0,"Test","",false);
    model.setValue(2,3,2,2,6,"=MEAN(2,A;2,B)",false);
    ASSERT_EQ(12, model.getValue(2,1));
    ASSERT_EQ(0,model.getValue(2,0));
    ASSERT_EQ(6,model.getValue(2,2));
    ASSERT_EQ("=MEAN(2,A;2,B)",model.getFormula(2,2));
}

TEST(Model, TestFindValue) {
    Model model;
    model.setWidth(100);
    model.setHeight(52);
    model.setValue(2,2,2,1,12,"",false);
    ASSERT_EQ(true, model.findValue(2,1));
    ASSERT_EQ(false,model.findValue(2,0));
}

TEST(Model, TestOnChangeCellFormula) {
    Model model;
    list<pair<int,int>> l;
    model.setWidth(100);
    model.setHeight(52);
    model.setValue(2,2,2,1,12,"",false);
    model.setValue(2,1,2,0,0,"",false);
    model.setValue(2,3,2,2,6,"=MEAN(2,A;2,B)",false);
    model.onAddFormula(2,0,2,2);
    model.onAddFormula(2,1,2,2);
    ASSERT_EQ(6,model.getValue(2,2));
    model.setValue(2,2,2,1,6,"",false);
    l.emplace_back(make_pair(2,2));
    ASSERT_EQ(make_pair(true,l), model.onChangeCellFormula(2,1));
    l.clear();
}