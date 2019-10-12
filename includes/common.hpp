//
// Created by Sohaib Iftikhar on 2019-10-08.
//

#ifndef SIMPLE_TEMPLATES_COMMON_HPP
#define SIMPLE_TEMPLATES_COMMON_HPP
#define COLORRED "\033[1;31m"
#define COLORGREEN "\033[1;32m"
#define COLORBLUE "\033[1;34m"
#define COLOREND "\033[0m"

#include <set>
#include <string>

// Helpful functions
template<typename CheckType, typename InstanceType>
bool isInstanceOf(InstanceType &instance) {
    return (dynamic_cast<CheckType*>(&instance) != nullptr);
}

template<typename OutType, typename InstanceType>
OutType* asInstanceOf(InstanceType &instance) {
    return dynamic_cast<OutType*>(&instance);
}

bool conforms(std::set<char> &valid, const std::string &str);

#endif //SIMPLE_TEMPLATES_COMMON_HPP