// Copyright 2014 Julia Buchina

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/fraction_calculator_application.h"

using ::testing::internal::RE;
using std::vector;
using std::string;

class AppTest : public ::testing::Test {
 protected:
    virtual void SetUp() {
        args.clear();
    }

    void Act(vector<string> args_) {
        vector<const char*> starts;
        starts.push_back("appname");

        for (size_t i = 0; i < args_.size(); ++i) {
            starts.push_back(args_[i].c_str());
        }
        const char** argv = &starts.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    CalculatorApplication app_;
    string output_;
    vector<string> args;
};

TEST_F(AppTest, Do_Print_Help_Without_Arguments) {
    Act(args);

    Assert("This is a fraction calculator application\\..*");
}

TEST_F(AppTest, Is_Checking_Number_Of_Arguments) {
    args = {"1", "2"};

    Act(args);

    Assert("ERROR: Should be 5 arguments\\..*");
}

TEST_F(AppTest, Can_Detect_Wrong_Number_Format) {
    args = {"1", "pi", "1", "1", "+"};

    Act(args);

    Assert("Wrong number format!.*");
}

TEST_F(AppTest, Can_Detect_Wrong_Operation_Format) {
    args = {"1", "1", "1", "1", "garbage"};

    Act(args);

    Assert("Wrong operation!");
}

TEST_F(AppTest, Can_Add) {
    args = {"1", "3", "1", "3", "+"};

    Act(args);

    Assert("Result = 2 3");
}

TEST_F(AppTest, Can_Sub) {
    args = {"2", "3", "1", "3", "-"};

    Act(args);

    Assert("Result = 1 3");
}

TEST_F(AppTest, Can_Multiply) {
    args = {"1", "3", "1", "3", "*"};

    Act(args);

    Assert("Result = 1 9");
}

TEST_F(AppTest, Can_Divide) {
    args = {"1", "3", "2", "3", "/"};

    Act(args);

    Assert("Result = 1 2");
}
