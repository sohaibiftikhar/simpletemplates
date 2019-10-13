//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#ifndef SIMPLE_TEMPLATES_TEMPLATECONFIGSPEC_HPP
#define SIMPLE_TEMPLATES_TEMPLATECONFIGSPEC_HPP

#include "Specification.hpp"

class TemplateConfigSpec: public Specification {
public:
    TemplateConfigSpec(): Specification("TemplateConfigSpec") {}
    void runSpecification() override;
};


#endif //SIMPLE_TEMPLATES_TEMPLATECONFIGSPEC_HPP
