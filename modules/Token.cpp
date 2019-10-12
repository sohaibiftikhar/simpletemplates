//
// Created by Sohaib Iftikhar on 2019-10-11.
//

#include "../includes/Token.hpp"
#include <sstream>
#include <exception>

Token::Token(TokenType type, vector<string> tokens): type(type), tokens(move(tokens)) {}

void Token::verifyVarName(string& varName) {
    if (varName.length() <= 0 || !isalpha(varName[0])) {
        throw invalid_argument("Invalid expression. Variable names must be non zero length, "
                               "without spaces and begin with an alphabet");
    }
}

Token Token::createStaticToken(const string& content) {
    return Token(Static, vector<string>(1, content));
}

Token Token::createExpressionToken(const string& content) {
    // sanitize and split into tokens
    stringstream ss(content);
    string buffer;
    vector<string> tokens;
    while (ss>>buffer) {
        tokens.push_back(buffer);
    }
    if (tokens.empty()) {
        throw invalid_argument("Expression cannot be empty");
    }
    if (tokens.size() == 1) {
        if (tokens[0] == "/loop") {
            return Token(LoopEnd, vector<string>());
        } else if (tokens[0] == "/if") {
            return Token(ConditionEnd, vector<string>());
        } else {
            verifyVarName(tokens[0]);
            return Token(SimpleVar, move(tokens));
        }
    } else if (tokens.size() == 2 && tokens[0] == "#if") {
        verifyVarName(tokens[1]);
        return Token(ConditionStart, move(tokens));
    } else if (tokens.size() == 3 && tokens.at(0) == "#loop") {
        verifyVarName(tokens[1]); verifyVarName(tokens[2]);
        return Token(LoopStart, move(tokens));
    } else {
        throw invalid_argument("Could not parse expression at " + content);
    }
}

Token Token::createEndToken() {
    return Token(End, vector<string>());
}

string Token::typeToString(TokenType type) {
    switch(type) {
        case Static: return "Static";
        case LoopStart: return "#loop";
        case LoopEnd: return "/loop";
        case ConditionStart: return "#if";
        case ConditionEnd: return "/if";
        case SimpleVar: return "SimpleVar";
        case End: return "End";
        default: return "Should not happen";
    }
}

string Token::typeToString() {
    return typeToString(type);
}
