//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#ifndef SIMPLE_TEMPLATES_TESTSUITE_HPP
#define SIMPLE_TEMPLATES_TESTSUITE_HPP

#include <vector>
#include <memory>
#include "Specification.hpp"


class TestSuite {
private:
    std::vector<std::unique_ptr<Specification>> specifications;

public:
    TestSuite(std::vector<std::unique_ptr<Specification>> specifications);

    void run();
};


#endif //SIMPLE_TEMPLATES_TESTSUITE_HPP
