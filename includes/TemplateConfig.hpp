//
// Created by Sohaib Iftikhar on 2019-10-11.
//

#ifndef SIMPLE_TEMPLATES_TEMPLATECONFIG_HPP
#define SIMPLE_TEMPLATES_TEMPLATECONFIG_HPP

#include<string>
#include <utility>
#include <set>
#include <stdexcept>

using namespace std;

class TemplateConfig {
private:
public:
    const string exprStart;
    const string exprEnd;

    TemplateConfig(string  expressionStart, string  expressionEnd);
    TemplateConfig();
};

#endif //SIMPLE_TEMPLATES_TEMPLATECONFIG_HPP
