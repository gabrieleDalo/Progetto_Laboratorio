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
        model->setValue(0,0,0,1,12,"",false);
        model->setValue(0,0,1,1,"Dodici","",false);
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
    ASSERT_EQ(controller.getRange(2,1,"1,A:2,A)"),values);
    ASSERT_EQ(controller.getRange(2,1,"1,A;2,A)"),values);
    ASSERT_EQ(controller.getRange(2,1,"A,1;2,A)"),values);

    vector<float> error;
    error.push_back(0);
    ASSERT_EQ(controller.getRange(2,1,"1,A,2,A)"),error);
    ASSERT_EQ(controller.getRange(2,1,"1,A:2,A"),error);
    ASSERT_EQ(controller.getRange(2,1,"1,1;2,A"),error);
    ASSERT_EQ(controller.getRange(2,1,"(1,1;2,A)"),error);
    ASSERT_EQ(controller.getRange(2,1,"()"),error);
    error.clear();
}

TEST_F(ControllerSuite,TestCheckFormula){
    ASSERT_EQ(controller.checkFormula(2,1,"SOMMA(1,A:2,A)"),12);
    ASSERT_EQ(controller.checkFormula(2,1,"MAX(1,A:2,A)"),12);
    ASSERT_EQ(controller.checkFormula(2,1,"MIN(1,A:2,A)"),0);
    ASSERT_EQ(controller.checkFormula(2,1,"MEAN(1,A:2,A)"),6);
    ASSERT_EQ(controller.checkFormula(2,1,"MUL(1,A:2,A)"),0);
    ASSERT_EQ(controller.checkFormula(2,1,"(1,A:2,A)"),0);
}

TEST_F(ControllerSuite,TestCheckOperation){
    controller.checkOperation(0,0,"1","A","12");
    controller.checkOperation(1,0,"2","A","Dodici");
    controller.checkOperation(2,0,"3","A","=MEAN(1,A:2,A)");
    ASSERT_EQ(model->getValue(0,1),12);
    ASSERT_EQ(model->getValue(1,1),0);
    ASSERT_EQ(model->getValue(2,1),6);
}
