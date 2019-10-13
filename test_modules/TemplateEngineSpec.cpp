//
// Created by Sohaib Iftikhar on 2019-10-13.
//

#include "../test_includes/TemplateEngineSpec.hpp"
#include "../includes/TemplateEngine.hpp"
#include "../includes/TemplateConfig.hpp"

using namespace std;

void TemplateEngineSpec::runSpecification() {
    printToConsole("A Template should");
    TemplateEngine engine;
    stringstream iss;
    stringstream oss;
    TemplateConfig config;
    std::map<string, unique_ptr<Renderable>> context;

    {
        // TEST
        printToConsole("render a static template", 1);
        iss.clear();
        iss.str("this is a static template\nand this is the second line");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        context.clear();
        t.bind(oss, context);
        string actual = oss.str();
        string expected = "this is a static template\nand this is the second line";
        mustEqual(actual, expected);
    }

    {
        // TEST
        printToConsole("render a simple string variable template", 1);
        iss.clear();
        iss.str("Hello {{user}}, welcome!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"user", make_unique<StringRenderable>("Suhaib")});
        t.bind(oss, context);
        string actual = oss.str();
        string expected = "Hello Suhaib, welcome!";
        mustEqual(actual, expected);
    }

    {
        // TEST
        printToConsole("render a simple integer variable template", 1);
        iss.clear();
        iss.str("Hello {{user}}, welcome!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"user", make_unique<IntRenderable>(1234)});
        t.bind(oss, context);
        string actual = oss.str();
        string expected = "Hello 1234, welcome!";
        mustEqual(actual, expected);
    }

    {
        // TEST
        printToConsole("render a simple floating point variable template", 1);
        iss.clear();
        iss.str("Hello {{user}}, welcome!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"user", make_unique<FloatRenderable>(1234.567, 3)});
        t.bind(oss, context);
        string actual = oss.str();
        string expected = "Hello 1234.567, welcome!";
        mustEqual(actual, expected);
    }

    {
        // TEST
        printToConsole("render a simple boolean variable template", 1);
        iss.clear();
        iss.str("Hello {{user}}, welcome!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"user", make_unique<BoolRenderable>(true)});
        t.bind(oss, context);
        string actual = oss.str();
        string expected = "Hello True, welcome!";
        mustEqual(actual, expected);
    }

    {
        // TEST
        printToConsole("render a loop variable template", 1);
        iss.clear();
        iss.str("Hello, You got {{count}} fruits!\n{{#loop fruits fruit}}*{{fruit}}\n{{/loop}}Enjoy!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"count", make_unique<IntRenderable>(3)});
        vector<unique_ptr<Renderable>> fruits;
        fruits.push_back(make_unique<StringRenderable>("Apple")),
                fruits.push_back(make_unique<StringRenderable>("Orange")),
                fruits.push_back(make_unique<StringRenderable>("Banana"));
        context.insert({"fruits", make_unique<ListRenderable>(move(fruits))});
        t.bind(oss, context);
        string actual = oss.str();
        string expected = "Hello, You got 3 fruits!\n"
                          "*Apple\n"
                          "*Orange\n"
                          "*Banana\n"
                          "Enjoy!";
        mustEqual(actual, expected);
    }

    {
        // TEST
        printToConsole("render a conditional template", 1);
        iss.clear();
        iss.str("Hello, You are now {{#if loggedIn}}loggedIn{{/if}}{{#if loggedOut}}loggedOut{{/if}}!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"loggedIn", make_unique<BoolRenderable>(true)});
        context.insert({"loggedOut", make_unique<BoolRenderable>(false)});
        t.bind(oss, context);
        string actual = oss.str();
        string expected = "Hello, You are now loggedIn!";
        mustEqual(actual, expected);
    }

    {
        // TEST
        printToConsole("fail if a template variable is not found in context", 1);
        iss.clear();
        iss.str("Hello, You are now {{#if loggedIn}}loggedIn{{/if}}{{#if loggedOut}}loggedOut{{/if}}!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        using namespace std::placeholders;
        context.insert({"loggedIn", make_unique<BoolRenderable>(true)});
        std::function<void()> func = std::bind(&Template::bind, &t, std::ref(oss), std::ref(context));
        mustFail(func);
    }

    {
        // TEST
        printToConsole("fail if loop variable is not iterable", 1);
        iss.clear();
        iss.str("Hello, You got {{count}} fruits!\n{{#loop fruits fruit}}*{{fruit}}\n{{/loop}}Enjoy!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"fruits", make_unique<StringRenderable>("[Apple, Orange, Banana]")});
        std::function<void()> func = std::bind(&Template::bind, &t, std::ref(oss), std::ref(context));
        mustFail(func);
    }

    {
        // TEST
        printToConsole("fail if conditional variable is not a boolean", 1);
        iss.clear();
        iss.str("Hello, You are now {{#if loggedIn}}loggedIn{{/if}}{{#if loggedOut}}loggedOut{{/if}}!");
        Template t = engine.compile("t", iss, config);
        oss.clear();
        oss.str(""), context.clear();
        context.insert({"loggedIn", make_unique<FloatRenderable>(0.05, 2)});
        context.insert({"loggedOut", make_unique<BoolRenderable>(true)});
        std::function<void()> func = std::bind(&Template::bind, &t, std::ref(oss), std::ref(context));
        mustFail(func);
    }

    {
        printToConsole("code in README should succeed", 1);
        //////
        std::stringstream istream("Hello {{user}}! Welcome to Simple Templates!");
        std::stringstream outstream;
        TemplateConfig myConfig("{{", "}}");
        TemplateEngine myEngine;
        Template myTemplate = engine.compile("WelcomeTemplate", istream, config);
        std::map<std::string, std::unique_ptr<Renderable>> myContext;
        context.insert({"user", std::make_unique<StringRenderable>("Suhaib")});
        myTemplate.bind(outstream, context);
        // std::cout<<outstream.str()<<std::endl;
        //////
        string actual = outstream.str();
        string expected = "Hello Suhaib! Welcome to Simple Templates!";
        mustEqual(actual, expected);
    }
}
