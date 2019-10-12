//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../test_includes/TestSuite.hpp"
#include "../includes/common.hpp"
#include <iostream>

using namespace std;

TestSuite::TestSuite(vector<std::unique_ptr<Specification>> specifications)
    : specifications(move(specifications)) {}

void TestSuite::run() {
    for (auto &specification: specifications) {
        cout<<"\nRunning tests for specification "<<specification->specName<<endl;
        auto result = specification->runSpecification();
        cout<<specification->specName<<" ran "<<result.first + result.second
            <<" tests of which "<<COLORGREEN<<result.first<<" were successful"<<COLOREND<<
            " and "<<COLORRED<<result.second<<" were unsuccessful"<<COLOREND<<endl;
    }
}