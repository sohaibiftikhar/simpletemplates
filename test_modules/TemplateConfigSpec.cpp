//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../test_includes/TemplateConfigSpec.hpp"
#include "../includes/TemplateConfig.hpp"
#include <stdexcept>

using namespace std;

std::pair<unsigned, unsigned> TemplateConfigSpec::runSpecification() {
    unsigned successful = 0; unsigned failed = 0;
    printToConsole("TemplateConfig should");

    // TEST 1
    printToConsole("work correctly for correct arguments", 1);
    try {
        TemplateConfig config("{{", "}}");
        printSuccess();
        successful++;
    } catch (std::invalid_argument& ex) {
        failed++;
        printFailure();
    }

    // TEST 2
    printToConsole("throw invalid_argument exception for invalid expression start", 1);
    try {
        TemplateConfig config("||a", "$$");
        printFailure();
        failed++;
    } catch (std::invalid_argument& ex) {
        printSuccess();
        successful++;
    }

    // TEST 3
    printToConsole("throw invalid_argument exception for invalid expression end", 1);
    try {
        TemplateConfig config("{{", "}1");
        printFailure();
        failed++;
    } catch (std::invalid_argument& ex) {
        printSuccess();
        successful++;
    }

    // TEST 4
    printToConsole("not work for zero length expression start", 1);
    try {
        TemplateConfig config("", "}}");
        printFailure();
        failed++;
    } catch (std::invalid_argument& ex) {
        printSuccess();
        successful++;
    }

    // TEST 5
    printToConsole("not work for zero length expression end", 1);
    try {
        TemplateConfig config("{{", "");
        printFailure();
        failed++;
    } catch (std::invalid_argument& ex) {
        printSuccess();
        successful++;
    }

    return {successful, failed};
}
