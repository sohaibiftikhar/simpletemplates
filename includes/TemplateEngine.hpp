//
// Created by Sohaib Iftikhar on 2019-10-11.
//

#ifndef SIMPLE_TEMPLATES_TEMPLATEENGINE_HPP
#define SIMPLE_TEMPLATES_TEMPLATEENGINE_HPP


#include "Template.hpp"
#include "TemplateConfig.hpp"
#include <iostream>

class TemplateEngine {
public:
    Template compile(std::istream& istream, TemplateConfig& config);
};


#endif //SIMPLE_TEMPLATES_TEMPLATEENGINE_HPP
