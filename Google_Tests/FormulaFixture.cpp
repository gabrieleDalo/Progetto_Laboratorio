//
// Created by Gabriele on 23/07/2020.
//
#include "gtest/gtest.h"
#include "../Formula.h"
#include "../Somma.h"
#include "../Max.h"
#include "../Min.h"
#include "../Mean.h"

class FormulaSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        values.push_back(12);
        values.push_back(6);
        values.push_back(0);
        values.push_back(10);
    }

    virtual void TearDown() {
        values.clear();
    }

    vector<float> values;
};

TEST_F(FormulaSuite,TestFormulaSum){
    Somma sum;
    ASSERT_EQ(sum.calculate(values),28);
}

TEST_F(FormulaSuite,TestFormulaMax){
    Max max;
    ASSERT_EQ(max.calculate(values),12);
}

TEST_F(FormulaSuite,TestFormulaMin){
    Min min;
    ASSERT_EQ(min.calculate(values),0);
}

TEST_F(FormulaSuite,TestFormulaMean){
    Mean mean;
    ASSERT_EQ(mean.calculate(values),7);
}