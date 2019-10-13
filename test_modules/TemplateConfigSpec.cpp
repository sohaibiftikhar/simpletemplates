//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../test_includes/TemplateConfigSpec.hpp"
#include "../includes/TemplateConfig.hpp"

using namespace std;

void TemplateConfigSpec::runSpecification() {
    printToConsole("A TemplateConfig should");

    {
        // TEST
        printToConsole("work correctly for correct arguments", 1);
        std::function<void()> func = []() { TemplateConfig("{{", "}}"); };
        mustSucceed(func);
    }

    {
        // TEST
        printToConsole("throw invalid_argument exception for invalid expression start", 1);
        std::function<void()> func = []() { TemplateConfig config("||a", "$$"); };
        mustFail(func);
    }

    {
        // TEST
        printToConsole("throw invalid_argument exception for invalid expression end", 1);
        std::function<void()> func = []() { TemplateConfig config("{{", "}1"); };
        mustFail(func);
    }

    {
        printToConsole("not work for zero length expression start", 1);
        std::function<void()> func = []() { TemplateConfig config("", "}}"); };
        mustFail(func);
    }

    {
        printToConsole("not work for zero length expression end", 1);
        std::function<void()> func = []() { TemplateConfig config("{{", ""); };
        mustFail(func);
    }
}
