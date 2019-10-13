//
// Created by Sohaib Iftikhar on 2019-10-10.
//

#ifndef SIMPLE_TEMPLATES_PARSERSPEC_HPP
#define SIMPLE_TEMPLATES_PARSERSPEC_HPP


#include "Specification.hpp"

class ParserSpec: public Specification {
public:
    ParserSpec(): Specification("ParserSpec") {}
    std::pair<unsigned , unsigned> runSpecification() override;
};


#endif //SIMPLE_TEMPLATES_PARSERSPEC_HPP
