//
// Created by Gabriele on 12/07/2020.
//

#include "gtest/gtest.h"
#include "../Model.h"
#include "../Model.cpp"

class ModelSuite : public ::testing::Test {

protected:
protected:
    virtual void SetUp() {
        m.setWidth(700);
        m.setHeight(500);
        m.setValue(2,2,2,1,12);
        m.setValue(2,1,2,0,"Test");
    }

    Model m;
};

TEST_F(ModelSuite, TestGetValue) {
    ASSERT_EQ(12, m.getValue(2,1));
}
