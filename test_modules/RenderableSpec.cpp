//
// Created by Sohaib Iftikhar on 2019-10-13.
//

#include "../test_includes/RenderableSpec.hpp"
#include "../includes/Renderable.hpp"
#include <sstream>

using namespace std;

void RenderableSpec::runSpecification() {
    printToConsole("A Renderable should");
    stringstream os;

    {
        // TEST
        os.clear(); os.str("");
        printToConsole("render a string renderable", 1);
        StringRenderable renderable("this is a string");
        renderable.render(os);
        string actual = os.str();
        string expected = "this is a string";
        mustEqual(actual, expected);
    }

    {
        // TEST
        os.clear(); os.str("");
        printToConsole("render an integer renderable", 1);
        IntRenderable renderable(1234);
        renderable.render(os);
        string actual = os.str();
        string expected = "1234";
        mustEqual(actual, expected);
    }

    {
        // TEST
        os.clear(); os.str("");
        printToConsole("render a float renderable with precision", 1);
        FloatRenderable renderable(1234.456, 2);
        renderable.render(os);
        string actual = os.str();
        string expected = "1234.46";
        mustEqual(actual, expected);
    }

    {
        // TEST
        os.clear(); os.str("");
        printToConsole("render a bool renderable", 1);
        BoolRenderable renderable(false);
        renderable.render(os);
        string actual = os.str();
        string expected = "False";
        mustEqual(actual, expected);
    }

    {
        // TEST
        os.clear(); os.str("");
        printToConsole("render a list renderable", 1);
        vector<std::unique_ptr<Renderable>> renderables;
        renderables.push_back(make_unique<StringRenderable>("hello"));
        vector<std::unique_ptr<Renderable>> renderablesInner;
        renderablesInner.push_back(make_unique<BoolRenderable>(true));
        renderables.push_back(make_unique<ListRenderable>(move(renderablesInner)));
        renderables.push_back(make_unique<IntRenderable>(1234));
        ListRenderable renderable(move(renderables));
        renderable.render(os);
        string actual = os.str();
        string expected = "[hello, [True], 1234]";
        mustEqual(actual, expected);
    }
}
