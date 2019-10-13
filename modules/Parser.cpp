//
// Created by Sohaib Iftikhar on 2019-10-10.
//

#include "../includes/Parser.hpp"
#include "../includes/Binding.hpp"
#include <memory>
#include <utility>
#include <cassert>

Parser::Parser(istream &is, TemplateConfig config):
        is(is), config(move(config)), nextTokenType(Constant) {}

bool Parser::search(const string& expr, ParserTokenType nextToken) {
    char c;
    // This offset marks how many characters need to be read from the buffer in case
    // we need to backtrack
    unsigned bufferOffset = 0;
    while (true) {
        size_t i = 0;
        while (read(bufferOffset, c) && c == expr[i] && ++i < expr.length());
        if (i == expr.length()) {
            this->nextTokenType = nextToken;
            return true;
        } else if (this->nextTokenType == StreamEnd) {
            return false;
        }
        // else we continue to look but only from the next char of the buffer and not from
        // the input stream
        bufferOffset = i;
    }
}

bool Parser::searchExpressionStart() {
    return search(config.exprStart, Expression);
}

bool Parser::searchExpressionEnd() {
    return search(config.exprEnd, Constant);
}

bool Parser::read(char &c) {
    if (is) {
        if (is.get(c)) {
            buffer.push_back(c);
            return true;
        } else {
            nextTokenType = StreamEnd;
            return false;
        }
    } else {
        nextTokenType = StreamEnd;
        return false;
    }
}

bool Parser::read(unsigned &bufferOffset, char &c) {
    if (bufferOffset > 0) {
        assert(buffer.size() > bufferOffset && "Algorithm error. Buffer size shouldn't exceed offset size");
        c = *(buffer.end() - bufferOffset);
        // Now that we used that char time to decrease the offset
        bufferOffset--;
        return true;
    } else {
        return read(c);
    }
}


Token Parser::nextToken() {
    // before beginning clear the buffer
    do {
        buffer.clear();
        ParserTokenType currentToken = nextTokenType;
        switch (currentToken) {
            case StreamEnd: {
                return Token::createEndToken();
            }
            case Constant: {
                auto endIt = searchExpressionStart() ? buffer.end() - config.exprStart.length() : buffer.end();
                if (buffer.begin() != endIt) {
                    return Token::createStaticToken(string(buffer.begin(), endIt));
                }
                // Else this was a zero length token so we continue to search for the next one.
                break;
            }
            case Expression: {
                if (searchExpressionEnd()) {
                    return Token::createExpressionToken(
                            string(buffer.begin(), buffer.end() - config.exprEnd.length())
                    );
                } else {
                    throw invalid_argument("Reached end of input searching for  " + config.exprEnd);
                }
            }
        }
    } while (true);
}

void Parser::parseUntil(std::vector<std::unique_ptr<Binding>> &bindings, TokenType until) {
    do {
        Token token = nextToken();
        switch(token.type) {
            case Static: {
                bindings.push_back(std::make_unique<StaticBinding>(token.tokens[0]));
                break;
            }
            case SimpleVar: {
                bindings.push_back(make_unique<SimpleBinding>(token.tokens[0]));
                break;
            }
            case LoopStart: {
                std::unique_ptr<LoopBinding> loopBinding(new LoopBinding(token.tokens[1], token.tokens[2]));
                loopBinding->build(*this);
                bindings.push_back(std::move(loopBinding));
                break;
            }
            case ConditionStart: {
                std::unique_ptr<ConditionalBinding> conditionalBinding(new ConditionalBinding(token.tokens[1]));
                conditionalBinding->build(*this);
                bindings.push_back(std::move(conditionalBinding));
                break;
            }
            case LoopEnd:
            case ConditionEnd:
            case End: {
                // No bindings do these tokens
                break;
            }
        }
        // Since do/while does not allow us to check loop variable declared inside the loop
        // we have our own break check
        if (token.type == until || token.type == End) {
            if (token.type != until) {
                throw invalid_argument("Reached end of stream while looking for " + Token::typeToString(until));
            }
            return;
        }
    } while (true);
}

void Parser::reset() {
    nextTokenType = Constant;
}
