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
    explicit Template(const std::string& templateName);
    friend class TemplateEngine;
protected:
    void build(Parser& parser) override;
public:
    /**
     * Returns the name this template was created with.
     * @return
     */
    const std::string& name();

    /**
     * Renders the compiled template against the context and writes it to the output stream specified.
     * The context map might be modified during the rendering process.
     * @param os the output stream for writing the rendered content
     * @param context The renderContext
     */
    void bind(std::ostream& os, std::map<std::string, std::unique_ptr<Renderable>>& context) override;

};

#endif //SIMPLE_TEMPLATES_TEMPLATE_HPP
