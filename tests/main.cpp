//
// Created by Sohaib Iftikhar on 2019-10-08.
//

#include "../test_includes/TestSuite.hpp"
#include "../test_includes/TemplateConfigSpec.hpp"
#include "../test_includes/ParserSpec.hpp"
#include "../test_includes/TemplateEngineSpec.hpp"

using namespace std;

int main(int argc, char **arv) {
    // Create specification list
    vector<unique_ptr<Specification>> specifications;
    specifications.push_back(make_unique<TemplateConfigSpec>());
    specifications.push_back(make_unique<ParserSpec>());
    specifications.push_back(make_unique<TemplateEngineSpec>());
    TestSuite testSuite(move(specifications));
    testSuite.run();
}