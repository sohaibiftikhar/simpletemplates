//
// Created by Sohaib Iftikhar on 2019-10-11.
//

#include "../includes/TemplateEngine.hpp"
#include "../test_includes/tests_common.hpp"

Template TemplateEngine::compile(const string& name, istream &is, TemplateConfig &config) {
    Parser parser(is, config);
    Template t(name);
    t.build(parser);
    return move(t);
}

