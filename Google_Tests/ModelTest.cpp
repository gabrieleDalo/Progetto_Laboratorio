//
// Created by Gabriele on 12/07/2020.
//
#include "gtest/gtest.h"
#include "../Model.h"

TEST(Model, DefaultConstructor) {
    Model m;
    ASSERT_EQ(0, m.getWidth());
    ASSERT_EQ(0, m.getHeight());
}



