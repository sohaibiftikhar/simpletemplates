//
// Created by Sohaib Iftikhar on 2019-10-08.
//

#ifndef SIMPLE_TEMPLATES_BINDING_HPP
#define SIMPLE_TEMPLATES_BINDING_HPP

#include <vector>
#include <iostream>
#include <map>
#include <utility>
#include "Renderable.hpp"
#include "Parser.hpp"

class Binding {
public:
    virtual void bind(std::ostream& os, std::map<std::string, std::unique_ptr<Renderable>>& context) = 0;
};

class StaticBinding: public Binding {
private:
    const std::string value;
public:
    explicit StaticBinding(std::string staticStr);
    void bind(std::ostream& os, std::map<std::string, std::unique_ptr<Renderable>>& context) override;
};

/**
 * Stores dynamic bindings that would be searched for during rendering phase for a template.
 */
class DynamicBinding: public Binding {
protected:
    const std::string varName;
    DynamicBinding(std::string varName);
};

/**
 * Represents a simple binding without any loops or conditions
 */
class SimpleBinding: public DynamicBinding {
public:
    explicit SimpleBinding(std::string varName);
    void bind(std::ostream& os, std::map<std::string, std::unique_ptr<Renderable>>& context) override;
};

/**
 * A complex binding could contain multiple bindings within itself
 */
class ComplexBinding: public DynamicBinding {
protected:
    std::vector<std::unique_ptr<Binding>> bindings;
    ComplexBinding(std::string varName);
public:
    /**
     * Used to populate the bindings for this complex binding
     * @param parser
     */
    virtual void build(Parser& parser) = 0;
};

class LoopBinding: public ComplexBinding {
    const std::string loopVarName;
public:
    explicit LoopBinding(std::string varName, std::string loopVarName);
    void bind(std::ostream& os, std::map<std::string, std::unique_ptr<Renderable>>& context) override;
    void build(Parser& parser) override;
};

class ConditionalBinding: public ComplexBinding {
public:
    explicit ConditionalBinding(std::string varName);
    void bind(std::ostream& os, std::map<std::string, std::unique_ptr<Renderable>>& context) override;
    void build(Parser& parser) override;
};

#endif //SIMPLE_TEMPLATES_BINDING_HPP
