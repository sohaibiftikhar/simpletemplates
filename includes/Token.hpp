//
// Created by Sohaib Iftikhar on 2019-10-10.
//

#ifndef SIMPLE_TEMPLATES_TOKEN_HPP
#define SIMPLE_TEMPLATES_TOKEN_HPP

#include <string>
#include <vector>


using namespace std;

enum TokenType {
    Static, LoopStart, LoopEnd, ConditionStart, ConditionEnd, SimpleVar, End
};
class Token {
public:
    const TokenType type;
    const vector<string> tokens;
private:
    Token(TokenType type, vector<string> tokens);
    static void verifyVarName(string& varName);
public:
    // Move constructor would be generated automatically
    // Token(Token&& token);
    static Token createStaticToken(const string& content);

    static Token createExpressionToken(const string& content);

    static Token createEndToken();

    static string typeToString(TokenType type);
    string typeToString();
};

#endif //SIMPLE_TEMPLATES_TOKEN_HPP
