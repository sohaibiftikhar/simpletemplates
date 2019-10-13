//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../includes/Binding.hpp"
#include "../includes/Parser.hpp"
#include "../includes/common.hpp"

StaticBinding::StaticBinding(std::string staticStr): value(std::move(staticStr)) {}

void StaticBinding::bind(std::ostream &os, std::map<std::string, std::unique_ptr<Renderable>> &context) {
    // Static bindings don't need to use context
    os<<value;
}

DynamicBinding::DynamicBinding(std::string varName): varName(std::move(varName)) {}

SimpleBinding::SimpleBinding(std::string varName): DynamicBinding(std::move(varName)) {}

void SimpleBinding::bind(std::ostream &os, std::map<std::string, std::unique_ptr<Renderable>> &context) {
    auto it = context.find(varName);
    if (it != context.end()) {
        (*(it->second)).render(os);
    } else {
        throw std::invalid_argument("Variable " + varName + " not found in context.");
    }
}

ComplexBinding::ComplexBinding(std::string varName): DynamicBinding(std::move(varName)) {}

LoopBinding::LoopBinding(std::string varName, std::string loopVarName)
    : ComplexBinding(std::move(varName)), loopVarName(std::move(loopVarName)) {}

void LoopBinding::build(Parser &parser) {
    parser.parseUntil(bindings, TokenType::LoopEnd);
}

void LoopBinding::bind(std::ostream &os, std::map<std::string, std::unique_ptr<Renderable>> &context) {
    // For every item in the loop variable we need to loop over the bindings
    auto result = context.find(varName);
    if (result != context.end()) {
        Renderable *r = result->second.get();
        if (isInstanceOf<ListRenderable>(*r)) {
            auto *list = asInstanceOf<ListRenderable>(*r);
            for (auto &renderable : list->value) {
                context[loopVarName] = std::move(renderable);
                for (auto &binding : bindings) {
                    (*binding).bind(os, context);
                }
            }
        } else {
            throw std::invalid_argument("Array variable " + varName + " is not iterable.");
        }
    } else {
        throw std::invalid_argument("Array variable " + varName + " not found in context.");
    }
}

ConditionalBinding::ConditionalBinding(std::string varName) : ComplexBinding(std::move(varName)) {}

void ConditionalBinding::build(Parser &parser) {
    parser.parseUntil(bindings, TokenType::ConditionEnd);
}

void ConditionalBinding::bind(std::ostream &os, std::map<std::string, std::unique_ptr<Renderable>> &context) {
    // For every item in the loop variable we need to loop over the bindings
    auto result = context.find(varName);
    if (result != context.end()) {
        Renderable *r = result->second.get();
        if (isInstanceOf<BoolRenderable>(*r)) {
            auto *list = asInstanceOf<ListRenderable>(*r);
            auto condition = asInstanceOf<BoolRenderable>(*r);
            if (condition->value) {
                for (auto &binding : bindings) {
                    (*binding).bind(os, context);
                }
            } // Else we don't render this section
        } else {
            throw invalid_argument("Conditional variable " + varName + " is not a Boolean");
        }
    } else {
        throw invalid_argument("Conditional variable " + varName + " not found in context.");
    }
}
