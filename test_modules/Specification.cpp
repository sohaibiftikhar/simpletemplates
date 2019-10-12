//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../test_includes/Specification.hpp"
#include "../includes/common.hpp"
#include <iostream>

using namespace std;

Specification::Specification(std::string specName) : specName(move(specName)) {}

void Specification::printToConsole(const vector<std::string>& strings, const set<unsigned>& red,
                                   const set<unsigned>& green, unsigned offset) {
    for (unsigned i=0; i<offset; i++) cout<<"    ";
    cout<<COLORBLUE<<"- "<<COLOREND;
    for (unsigned long i=0; i < strings.size(); i++) {
        bool hasColor = false;
        if (red.count(i)) {
            cout<<COLORRED; hasColor = true;
        } else if (green.count(i)) {
            cout<<COLORGREEN; hasColor = true;
        }
        cout<<strings[i];
        if (hasColor) cout<<COLOREND;
    }
    cout<<endl;
}

void Specification::printToConsole(const std::vector<std::string> &strings, unsigned offset) {
    printToConsole(strings, {}, {}, offset);
}

void Specification::printToConsole(const std::vector<std::string> &strings) {
    printToConsole(strings, {}, {}, 0);
}

void Specification::printToConsole(const std::string &str) {
    printToConsole({str}, {}, {}, 0);
}

void Specification::printToConsole(const std::string &str, int offset) {
    printToConsole({str}, {}, {}, offset);
}

void
Specification::printRedToConsole(const std::vector<std::string> &strings, const std::set<unsigned> &red, int offset) {
    printToConsole(strings, red, {}, offset);
}

void
Specification::printGreenToConsole(const std::vector<std::string> &strings, const std::set<unsigned> &green, int offset) {
    printToConsole(strings, {}, green, offset);
}

void Specification::printRedToConsole(const std::string &str, int offset) {
    printRedToConsole({str}, {0}, offset);
}

void Specification::printGreenToConsole(const std::string &str, int offset) {
    printGreenToConsole({str}, {0}, offset);
}

void Specification::printSuccess() {
    printGreenToConsole("test successful", 2);
}

void Specification::printFailure() {
    printRedToConsole("test failed", 2);
}



