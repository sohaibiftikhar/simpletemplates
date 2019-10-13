//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../test_includes/Specification.hpp"
#include "../includes/common.hpp"
#include <iostream>

using namespace std;

Specification::Specification(std::string specName) : specName(move(specName)), successful(0), failed(0) {}


void Specification::mustFail(std::function<void()> &func) {
    try {
        func();
        printFailure();
        failed++;
    } catch (std::invalid_argument &exc) {
        printSuccess();
        successful++;
    }
}

void Specification::mustSucceed(std::function<void()> &func) {
    try {
        func();
        printSuccess();
        successful++;
    } catch (std::invalid_argument &exc) {
        printFailure();
        failed++;
    }
}

std::pair<unsigned, unsigned> Specification::results() {
    return {successful, failed};
}

std::pair<unsigned, unsigned> Specification::run() {
    printToConsole("Running tests for specification " + specName, "+ ");
    runSpecification();
    printToConsole(
            {
                    specName, " ran ", to_string(successful + failed),
                    " tests of which ", to_string(successful), " were successful ", " and ",
                    to_string(failed),
                    " were unsuccessful\n"
            },
            {7, 8},
            {4, 5},
            0,
            "  "
    );
    return results();
}
