//
// Created by Sohaib Iftikhar on 2019-10-10.
//

#include "../test_includes/ParserSpec.hpp"
#include "../includes/Parser.hpp"
#include "../includes/common.hpp"
#include "../includes/Binding.hpp"
#include "../test_includes/tests_common.hpp"
#include <sstream>

using namespace std;

void ParserSpec::runSpecification() {
    printToConsole("A Parser should");

    TemplateConfig templateConfig("{{", "}}");
    string simpleTemplate("stat1 {{var1}} stat2");
    string loopTemplate("stat1 {{#loop arr item }} {{item}} {{/loop}}");
    string conditionalTemplate("stat1 {{#if cond}} {{var1}} {{/if}}");
    vector<unique_ptr<Binding>> bindings;
    stringstream ss(simpleTemplate);
    Parser parser(ss, templateConfig);

    {
        // TEST
        parser.parseUntil(bindings, TokenType::End);
        printToConsole("parse simple bindings correctly", 1);
        bool actual = (bindings.size() == 3 &&
                       isInstanceOf<StaticBinding>(*(bindings[0].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[0].get()))->value == "stat1 " &&
                       isInstanceOf<SimpleBinding>(*(bindings[1].get())) &&
                       asInstanceOf<SimpleBinding>(*(bindings[1].get()))->varName == "var1" &&
                       isInstanceOf<StaticBinding>(*(bindings[2].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[2].get()))->value == " stat2");
        bool expected = true;
        mustEqual(actual, expected);
    }

    {
        // TEST
        ss.clear();
        ss.str(loopTemplate);
        parser.reset();
        bindings.clear();
        parser.parseUntil(bindings, TokenType::End);
        printToConsole("parse loop bindings correctly", 1);
        bool actual = (bindings.size() == 2 &&
                       isInstanceOf<StaticBinding>(*(bindings[0].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[0].get()))->value == "stat1 " &&
                       isInstanceOf<LoopBinding>(*(bindings[1].get())) &&
                       asInstanceOf<LoopBinding>(*(bindings[1].get()))->varName == "arr" &&
                       asInstanceOf<LoopBinding>(*(bindings[1].get()))->loopVarName == "item");
        bool expected = true;
        mustEqual(actual, expected);
    }

    {
        // TEST
        ss.clear();
        ss.str(conditionalTemplate);
        parser.reset();
        bindings.clear();
        parser.parseUntil(bindings, TokenType::End);
        printToConsole("parse conditional bindings correctly", 1);
        bool actual = (bindings.size() == 2 &&
                       isInstanceOf<StaticBinding>(*(bindings[0].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[0].get()))->value == "stat1 " &&
                       isInstanceOf<ConditionalBinding>(*(bindings[1].get())) &&
                       asInstanceOf<ConditionalBinding>(*(bindings[1].get()))->varName == "cond");
        bool expected = true;
        mustEqual(actual, expected);
    }

    {
        // TEST
        ss.clear();
        ss.str(" {{item}} {{/loop}}");
        parser.reset();
        bindings.clear();
        parser.parseUntil(bindings, TokenType::LoopEnd);
        printToConsole("parse bindings until loop end correctly", 1);
        bool actual = (bindings.size() == 3 &&
                       isInstanceOf<StaticBinding>(*(bindings[0].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[0].get()))->value == " " &&
                       isInstanceOf<SimpleBinding>(*(bindings[1].get())) &&
                       asInstanceOf<SimpleBinding>(*(bindings[1].get()))->varName == "item" &&
                       isInstanceOf<StaticBinding>(*(bindings[2].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[2].get()))->value == " ");
        bool expected = true;
        mustEqual(actual, expected);
    }

    {
        // TEST
        ss.clear();
        ss.str(" {{var1}} {{/if}}");
        parser.reset();
        bindings.clear();
        parser.parseUntil(bindings, TokenType::ConditionEnd);
        printToConsole("parse bindings until condition end correctly", 1);
        bool actual = (bindings.size() == 3 &&
                       isInstanceOf<StaticBinding>(*(bindings[0].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[0].get()))->value == " " &&
                       isInstanceOf<SimpleBinding>(*(bindings[1].get())) &&
                       asInstanceOf<SimpleBinding>(*(bindings[1].get()))->varName == "var1" &&
                       isInstanceOf<StaticBinding>(*(bindings[2].get())) &&
                       asInstanceOf<StaticBinding>(*(bindings[2].get()))->value == " ");
        bool expected = true;
        mustEqual(actual, expected);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{#loop arr item}} {{item}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if loop end is missing", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{#if condn}} {{item}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if condition end is missing", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{item ds}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if simple expression is malformed", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        ss.clear();
        ss.str("stat1 {{1item}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if simple variable name is invalid", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{#loop end}} {{item}} {{/loop}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if loop start is malformed", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{#loop end}} {{item}} {{/loop}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if loop start is malformed", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{#loop arr item}} {{item}} {{/ldoop}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if loop end is malformed", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{#if arr item}} {{item}} {{/if}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if condition start is malformed", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{#if condn}} {{item}} {{/iff}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if condition end is malformed", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }

    {
        // TEST
        ss.clear();
        ss.str("stat1 {{item}} {{#loop arr item}} {{item}} {{/loop}}");
        parser.reset();
        bindings.clear();
        printToConsole("fail if loop variable is an already assigned variable in the context", 1);
        std::function<void()> func = std::bind(&Parser::parseUntil, &parser, std::ref(bindings), TokenType::End);
        mustFail(func);
    }
}
