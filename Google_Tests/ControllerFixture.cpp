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

TEST_F(ControllerSuite,TestCalculateSum){
    ASSERT_EQ(controller.calculateSum(values),12);
}

TEST_F(ControllerSuite,TestCalculateMax){
    ASSERT_EQ(controller.calculateMax(values),12);
}

TEST_F(ControllerSuite,TestCalculateMin){
    ASSERT_EQ(controller.calculateMin(values),0);
}

TEST_F(ControllerSuite,TestCalculateMean){
    ASSERT_EQ(controller.calculateMean(values),6);
}

TEST_F(ControllerSuite,TestGetRange){
    ASSERT_EQ(controller.getRange("1,A:2,A)"),values);
    ASSERT_EQ(controller.getRange("1,A;2,A)"),values);
}

TEST_F(ControllerSuite,TestCheckFormula){
    ASSERT_EQ(controller.checkFormula("SOMMA(1,A:2,A)"),12);
    ASSERT_EQ(controller.checkFormula("MAX(1,A:2,A)"),12);
    ASSERT_EQ(controller.checkFormula("MIN(1,A:2,A)"),0);
    ASSERT_EQ(controller.checkFormula("MEAN(1,A:2,A)"),6);
}

TEST_F(ControllerSuite,TestCheckOperation){
    controller.checkOperation(0,0,"1","A","12");
    controller.checkOperation(1,0,"2","A","Dodici");
    ASSERT_EQ(model->getValue(0,1),12);
    ASSERT_EQ(model->getValue(1,1),0);
}