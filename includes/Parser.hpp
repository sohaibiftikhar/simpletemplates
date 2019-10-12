//
// Created by Sohaib Iftikhar on 2019-10-10.
//

#ifndef SIMPLE_TEMPLATES_PARSER_HPP
#define SIMPLE_TEMPLATES_PARSER_HPP

#include <iostream>
#include <string>
#include "Token.hpp"
#include "TemplateConfig.hpp"
#include <vector>
#include <set>
#include <memory>

class Binding;

using namespace std;

class Parser {
private:
    enum ParserTokenType { Constant, Expression, StreamEnd };
    ParserTokenType nextTokenType;
    istream& is;
    const TemplateConfig config;
    vector<char> buffer;

    bool searchExpressionStart();
    bool searchExpressionEnd();
    bool search(const string& expr, ParserTokenType token);
    bool read(char &c);
    bool read(unsigned &bufferOffset, char &c);
    Token nextToken();
public:
    Parser(istream& is, TemplateConfig config);

    void parseUntil(std::vector<std::unique_ptr<Binding>>& bindings, TokenType until);
};

#endif //SIMPLE_TEMPLATES_PARSER_HPP
