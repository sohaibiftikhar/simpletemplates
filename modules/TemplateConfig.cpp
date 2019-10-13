//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../includes/TemplateConfig.hpp"
#include "../includes/common.hpp"

TemplateConfig::TemplateConfig(string  expressionStart, string  expressionEnd):
exprStart(std::move(expressionStart)), exprEnd(std::move(expressionEnd)) {
    set<char> validExprChars{'{', '[', '(', '<', '|', '$', '>', ')', ']', '}'};
    if (!(exprStart.length() > 0 && conforms(validExprChars, exprStart))) {
        throw invalid_argument("expressionStart must have a length greater than 0 and not have any "
                               "characters other {[(<|$>)]}");
    }
    if (!(exprEnd.length() > 0 && conforms(validExprChars, exprEnd))) {
        throw invalid_argument("expressionEnd must have a length greater than 0 and not have any "
                               "characters other {[(<|$>)]}");
    }
}

TemplateConfig::TemplateConfig(): TemplateConfig("{{", "}}") {};