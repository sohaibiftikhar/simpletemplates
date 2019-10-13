//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#ifndef SIMPLE_TEMPLATES_TESTS_COMMON_HPP
#define SIMPLE_TEMPLATES_TESTS_COMMON_HPP
#define COLORRED "\033[1;31m"
#define COLORGREEN "\033[1;32m"
#define COLORBLUE "\033[1;34m"
#define COLOREND "\033[0m"

#include <vector>
#include <set>
#include <string>

// Bunch of pretty print functions
void printToConsole(const std::vector<std::string>& strings, const std::set<unsigned>& red,
                    const std::set<unsigned>& green, unsigned offset, const std::string& prefix);
void printToConsole(const std::vector<std::string>& strings, const std::set<unsigned>& red,
                    const std::set<unsigned>& green, unsigned offset);
void printToConsole(const std::vector<std::string> &strings, unsigned offset);
void printToConsole(const std::vector<std::string> &strings);
void printToConsole(const std::string& str);
void printToConsole(const std::string& str, int offset, const std::string& prefix);
void printToConsole(const std::string& str, const std::string& prefix);
void printToConsole(const std::string& str, int offset);
void printRedToConsole(const std::vector<std::string> &strings, const std::set<unsigned>& red,
                       int offset);
void printRedToConsole(const std::string& str, int offset);
void printGreenToConsole(const std::vector<std::string> &strings, const std::set<unsigned>& green,
                         int offset);
void printGreenToConsole(const std::string& str, int offset);
void printSuccess();
void printFailure();

#endif //SIMPLE_TEMPLATES_TESTS_COMMON_HPP
