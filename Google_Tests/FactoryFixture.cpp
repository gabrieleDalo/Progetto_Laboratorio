//
// Created by Gabriele on 18/07/2020.
//
#include "gtest/gtest.h"
#include "../FormulaFactory.h"
#include "../FormulaFactory.cpp"

class FactorySuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        values.push_back(12);
        values.push_back(0);
    }

    virtual void TearDown() {
        values.clear();
    }

    FormulaFactory formula;
    vector<float> values;
};

TEST_F(FactorySuite,TestCalculateSum){
    ASSERT_EQ(stof(formula.calculateOperation("SOMMA",values)),12);
}

TEST_F(FactorySuite,TestCalculateMax){
    ASSERT_EQ(stof(formula.calculateOperation("MAX",values)),12);
}

TEST_F(FactorySuite,TestCalculateMin){
    ASSERT_EQ(stof(formula.calculateOperation("MIN",values)),0);
}

TEST_F(FactorySuite,TestCalculateMean){
    ASSERT_EQ(stof(formula.calculateOperation("MEAN",values)),6);
}

TEST_F(FactorySuite,Error){
    ASSERT_EQ(formula.calculateOperation("SOMETHING",values),"Error");
}