//
// Created by Sohaib Iftikhar on 2019-10-10.
//

#include "../includes/Template.hpp"

Template::Template(const string& templateName) : ComplexBinding(templateName) {}

const std::string& Template::name() {
    return varName;
}

void Template::bind(ostream& os, map<std::string, unique_ptr<Renderable>>& context) {
    for (auto &binding: bindings) {
        binding->bind(os, context);
    }
}

void Template::build(Parser &parser) {
    parser.parseUntil(bindings, TokenType::End);
}

