//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../includes/common.hpp"

using namespace std;

bool conforms(set<char> &valid, const string &str) {
    int i = 0;
    while (valid.count(str[i]) && ++i < str.length());
    return i == str.length();
}