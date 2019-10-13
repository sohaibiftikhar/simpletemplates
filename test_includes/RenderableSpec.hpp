//
// Created by Sohaib Iftikhar on 2019-10-13.
//

#ifndef SIMPLE_TEMPLATES_RENDERABLESPEC_HPP
#define SIMPLE_TEMPLATES_RENDERABLESPEC_HPP

#include "Specification.hpp"

class RenderableSpec: public Specification {
public:
    RenderableSpec(): Specification("RenderableSpec") {}
    void runSpecification() override;
};


#endif //SIMPLE_TEMPLATES_RENDERABLESPEC_HPP
