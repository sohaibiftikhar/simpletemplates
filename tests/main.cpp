//
// Created by Sohaib Iftikhar on 2019-10-08.
//

#include "../test_includes/TestSuite.hpp"
#include "../test_includes/TemplateConfigSpec.hpp"

using namespace std;

int main(int argc, char **arv) {
    // Create specification list
    vector<unique_ptr<Specification>> specifications;
    specifications.push_back(make_unique<TemplateConfigSpec>());
    TestSuite testSuite(move(specifications));
    testSuite.run();
}