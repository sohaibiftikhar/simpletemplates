//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#include "../test_includes/tests_common.hpp"
#include <iostream>
using namespace std;

void printToConsole(const std::vector<std::string>& strings, const std::set<unsigned>& red,
                    const std::set<unsigned>& green, unsigned offset, const std::string& prefix) {
    for (unsigned i=0; i<offset; i++) cout<<"    ";
    if (prefix.length() > 0) cout<<COLORBLUE<<prefix<<COLOREND;
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

void printToConsole(const vector<std::string>& strings, const set<unsigned>& red,
                                   const set<unsigned>& green, unsigned offset) {
    printToConsole(strings, red, green, offset, "- ");
}

void printToConsole(const std::vector<std::string> &strings, unsigned offset) {
    printToConsole(strings, {}, {}, offset);
}

void printToConsole(const std::vector<std::string> &strings) {
    printToConsole(strings, {}, {}, 0);
}

void printToConsole(const std::string& str, int offset, const std::string& prefix) {
    printToConsole({str}, {}, {}, offset, prefix);
}
void printToConsole(const std::string& str, const std::string& prefix) {
    printToConsole({str}, {}, {}, 0, prefix);
}

void printToConsole(const std::string &str) {
    printToConsole({str}, {}, {}, 0);
}

void printToConsole(const std::string &str, int offset) {
    printToConsole({str}, {}, {}, offset);
}

void
printRedToConsole(const std::vector<std::string> &strings, const std::set<unsigned> &red, int offset) {
    printToConsole(strings, red, {}, offset);
}

void
printGreenToConsole(const std::vector<std::string> &strings, const std::set<unsigned> &green, int offset) {
    printToConsole(strings, {}, green, offset);
}

void printRedToConsole(const std::string &str, int offset) {
    printRedToConsole({str}, {0}, offset);
}

void printGreenToConsole(const std::string &str, int offset) {
    printGreenToConsole({str}, {0}, offset);
}

void printSuccess() {
    printGreenToConsole("test successful", 2);
}

void printFailure() {
    printRedToConsole("test failed", 2);
}