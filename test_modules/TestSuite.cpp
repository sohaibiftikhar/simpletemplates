//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../test_includes/TestSuite.hpp"
#include "../includes/common.hpp"
#include "../test_includes/tests_common.hpp"

using namespace std;

TestSuite::TestSuite(vector<std::unique_ptr<Specification>> specifications)
        : specifications(move(specifications)) {}

void TestSuite::run() {
    unsigned successful = 0;
    unsigned failed = 0;
    vector<string> failedSpecs;
    printToConsole("", "");
    for (auto &specification: specifications) {
        auto result = specification->run();
        successful += result.first;
        failed += result.second;
        if (result.second > 0) failedSpecs.push_back(specification->specName);
    }
    printToConsole(
            {"Total tests: ", to_string(successful + failed), " Passed: ", to_string(successful),
             " Failed: ", to_string(failed)
            },
            {4, 5},
            {2, 3},
            0,
            ""
    );
    if (!failedSpecs.empty()) {
        printToConsole("Failed specifications are: ", "");
        for (string &specName: failedSpecs) printToConsole(specName, 1);
    }
    printToConsole("", "");
}