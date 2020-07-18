//
// Created by Gabriele on 15/07/2020.
//
#include "gtest/gtest.h"
#include "../Controller.h"
#include "../Controller.cpp"

class ControllerSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        model = new Model(100,52);
        model->setValue(0,0,0,1,12);
        model->setValue(0,0,1,1,"Dodici");
        controller.setError(false);
        controller.setModel(model);
        values.push_back(12);
        values.push_back(0);
    }

    virtual void TearDown() {
        values.clear();
    }

    Model* model{};
    Controller controller;
    vector<float> values;
};

TEST_F(ControllerSuite,TestCheckString){
    ASSERT_EQ(controller.checkString("12"),12);
    ASSERT_EQ(controller.checkString("Dodici"),0);
}

TEST_F(ControllerSuite,TestConvertLabelValue){
    ASSERT_EQ(controller.convertLabelValue("1"),0);
    ASSERT_EQ(controller.convertLabelValue("A"),1);
}

TEST_F(ControllerSuite,TestGetRange){
    ASSERT_EQ(controller.getRange("1,A:2,A)"),values);
    ASSERT_EQ(controller.getRange("1,A;2,A)"),values);
    ASSERT_EQ(controller.getRange("A,1;2,A)"),values);

    vector<float> error;
    error.push_back(0);
    ASSERT_EQ(controller.getRange("1,A,2,A)"),error);
    ASSERT_EQ(controller.getRange("1,A:2,A"),error);
    ASSERT_EQ(controller.getRange("1,1;2,A"),error);
    ASSERT_EQ(controller.getRange("(1,1;2,A)"),error);
    ASSERT_EQ(controller.getRange("()"),error);
    error.clear();
}

TEST_F(ControllerSuite,TestCheckFormula){
    ASSERT_EQ(controller.checkFormula("SOMMA(1,A:2,A)"),12);
    ASSERT_EQ(controller.checkFormula("MAX(1,A:2,A)"),12);
    ASSERT_EQ(controller.checkFormula("MIN(1,A:2,A)"),0);
    ASSERT_EQ(controller.checkFormula("MEAN(1,A:2,A)"),6);
    ASSERT_EQ(controller.checkFormula("MUL(1,A:2,A)"),0);
    ASSERT_EQ(controller.checkFormula("(1,A:2,A)"),0);
}

TEST_F(ControllerSuite,TestCheckOperation){
    controller.checkOperation(0,0,"1","A","12");
    controller.checkOperation(1,0,"2","A","Dodici");
    controller.checkOperation(2,0,"3","A","=MEAN(1,A:2,A)");
    ASSERT_EQ(model->getValue(0,1),12);
    ASSERT_EQ(model->getValue(1,1),0);
    ASSERT_EQ(model->getValue(2,1),6);
}