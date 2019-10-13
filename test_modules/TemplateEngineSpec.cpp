//
// Created by Sohaib Iftikhar on 2019-10-13.
//

#include "../test_includes/TemplateEngineSpec.hpp"
#include "../test_includes/tests_common.hpp"
#include "../includes/TemplateEngine.hpp"
#include "../includes/TemplateConfig.hpp"
#include <sstream>

using namespace std;

std::pair<unsigned, unsigned> TemplateEngineSpec::runSpecification() {
    unsigned successful = 0;
    unsigned failed = 0;
    printToConsole("A Template should");
    TemplateEngine engine;
    stringstream iss;
    stringstream oss;
    TemplateConfig config;
    std::map<string, unique_ptr<Renderable>> context;

    // TEST
    printToConsole("render a static template", 1);
    string tmpl1 = "this is a static template\nand this is the second line";
    iss.clear();
    iss.str(tmpl1);
    Template t1 = engine.compile("t1", iss, config);
    oss.clear();
    context.clear();
    t1.bind(oss, context);
    if (oss.str() == tmpl1) {
        printSuccess();
        successful++;
    } else {
        printFailure();
        failed++;
    }

    // TEST
    printToConsole("render a simple variable template", 1);
    iss.clear();
    iss.str("Hello {{user}}, welcome!");
    Template t2 = engine.compile("t1", iss, config);
    oss.clear();
    oss.str(""), context.clear();
    context.insert({"user", make_unique<StringRenderable>("Suhaib")});
    t2.bind(oss, context);
    if (oss.str() == "Hello Suhaib, welcome!") {
        printSuccess(); successful++;
    } else {
        printFailure(); failed++;
    }

    // TEST
    printToConsole("render a loop variable template", 1);
    iss.clear();
    iss.str("Hello, You got {{count}} fruits!\n{{#loop fruits fruit}}*{{fruit}}\n{{/loop}}Enjoy!");
    Template t3 = engine.compile("t3", iss, config);
    oss.clear();
    oss.str(""), context.clear();
    context.insert({"count", make_unique<IntRenderable>(3)});
    vector<unique_ptr<Renderable>> fruits;
    fruits.push_back(make_unique<StringRenderable>("Apple")),
    fruits.push_back(make_unique<StringRenderable>("Orange")),
    fruits.push_back(make_unique<StringRenderable>("Banana"));
    context.insert({"fruits", make_unique<ListRenderable>(move(fruits))});
    t3.bind(oss, context);
    string resultStr = "Hello, You got 3 fruits!\n"
                       "*Apple\n"
                       "*Orange\n"
                       "*Banana\n"
                       "Enjoy!";
    if (oss.str() == resultStr) {
        printSuccess(); successful++;
    } else {
        printFailure(); failed++;
    }

    // TEST
    printToConsole("render a conditional template", 1);
    iss.clear();
    iss.str("Hello, You are now {{#if loggedIn}}loggedIn{{/if}}{{#if loggedOut}}loggedOut{{/if}}!");
    Template t4 = engine.compile("t4", iss, config);
    oss.clear();
    oss.str(""), context.clear();
    context.insert({"loggedIn", make_unique<BoolRenderable>(true)});
    context.insert({"loggedOut", make_unique<BoolRenderable>(false)});
    t4.bind(oss, context);
    if (oss.str() == "Hello, You are now loggedIn!") {
        printSuccess(); successful++;
    } else {
        cout<<oss.str()<<endl;
        printFailure(); failed++;
    }

    return {successful, failed};
}
