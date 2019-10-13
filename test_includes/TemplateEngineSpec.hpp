//
// Created by Sohaib Iftikhar on 2019-10-13.
//

#ifndef SIMPLE_TEMPLATES_TEMPLATEENGINESPEC_HPP
#define SIMPLE_TEMPLATES_TEMPLATEENGINESPEC_HPP


#include "Specification.hpp"

class TemplateEngineSpec: public Specification {
public:
    TemplateEngineSpec(): Specification("TemplateEngineSpec") {}
    void runSpecification() override;
};


#endif //SIMPLE_TEMPLATES_TEMPLATEENGINESPEC_HPP
