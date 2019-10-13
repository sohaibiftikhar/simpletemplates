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
    /**
     * Compiles the characters from the given input string into a Template that can be rendered
     * @param istream
     * @param config
     * @return
     */
    Template compile(const std::string& templateName, std::istream& istream, TemplateConfig& config);
};

#endif //SIMPLE_TEMPLATES_TEMPLATEENGINE_HPP
