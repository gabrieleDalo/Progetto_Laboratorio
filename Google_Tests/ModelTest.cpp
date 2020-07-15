//
// Created by Gabriele on 12/07/2020.
//
#include "gtest/gtest.h"
#include "../Model.h"
#include "../Model.cpp"

TEST(Model, DefaultConstructor) {
    Model model;
    ASSERT_EQ(0, model.getWidth());
    ASSERT_EQ(0, model.getHeight());
}

TEST(Model, TestGetValue) {
    Model model;
    model.setWidth(100);
    model.setHeight(52);
    model.setValue(2,2,2,1,12);
    model.setValue(2,1,2,0,"Test");
    ASSERT_EQ(12, model.getValue(2,1));
    ASSERT_EQ(0,model.getValue(2,0));
    ASSERT_EQ(100, model.getWidth());
    ASSERT_EQ(52,model.getHeight());
}

