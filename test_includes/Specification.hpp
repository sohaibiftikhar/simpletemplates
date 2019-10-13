//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#ifndef SIMPLE_TEMPLATES_SPECIFICATION_HPP
#define SIMPLE_TEMPLATES_SPECIFICATION_HPP
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <functional>
#include "../test_includes/tests_common.hpp"

class Specification {
protected:
    unsigned successful, failed;
public:
    const std::string specName;
    Specification(std::string specName);

    /**
     * Must be implemented by inheriting classes.
     * Runs the specific test.
     */
    virtual void runSpecification() = 0;

    template<typename T>
    void mustEqual(T &actual, T &expected) {
        if (actual == expected) {
            printSuccess();
            successful++;
        } else {
            printFailure();
            std::stringstream ss;
            ss<<"expected: '"<<expected<<"' but found: '"<<actual<<"'";
            printRedToConsole(ss.str(), 2);
            failed++;
        }
    }

    std::pair<unsigned, unsigned> run();

    void mustFail(std::function<void()> &func);
    void mustSucceed(std::function<void()> &func);
    std::pair<unsigned, unsigned> results();
};


#endif //SIMPLE_TEMPLATES_SPECIFICATION_HPP
