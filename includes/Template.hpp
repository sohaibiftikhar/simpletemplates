//
// Created by Sohaib Iftikhar on 2019-10-08.
//

#ifndef SIMPLE_TEMPLATES_TEMPLATE_HPP
#define SIMPLE_TEMPLATES_TEMPLATE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "Binding.hpp"

class Template: public ComplexBinding {
private:
    void parse(std::istream &inputTemplate);

public:
    /**
     * Compiles the inputSource to a renderable Template
     * @param inputTemplate An input stream of characters for the template
     */
    Template(std::istream &inputTemplate);

    /**
     * Renders the compiled template against the context and writes it to the output stream specified.
     * The context map might be modified during the rendering process.
     * @param os the output stream for writing the rendered content
     * @param context The renderContext
     */
    void bind(std::ostream& os, std::map<std::string, std::unique_ptr<Renderable>>& context) override;

    void build(Parser& parser) override;
};

#endif //SIMPLE_TEMPLATES_TEMPLATE_HPP
