//
// Created by Sohaib Iftikhar on 2019-10-12.
//

#ifndef SIMPLE_TEMPLATES_SPECIFICATION_HPP
#define SIMPLE_TEMPLATES_SPECIFICATION_HPP
#include <vector>
#include <string>
#include <set>

class Specification {
protected:
    // Bunch of pretty print functions
    void printToConsole(const std::vector<std::string>& strings, const std::set<unsigned>& red,
                        const std::set<unsigned>& green, unsigned offset);
    void printToConsole(const std::vector<std::string> &strings, unsigned offset);
    void printToConsole(const std::vector<std::string> &strings);
    void printToConsole(const std::string& str);
    void printToConsole(const std::string& str, int offset);
    void printRedToConsole(const std::vector<std::string> &strings, const std::set<unsigned>& red,
                           int offset);
    void printRedToConsole(const std::string& str, int offset);
    void printGreenToConsole(const std::vector<std::string> &strings, const std::set<unsigned>& green,
                             int offset);
    void printGreenToConsole(const std::string& str, int offset);
    void printSuccess();
    void printFailure();
public:
    const std::string specName;
    Specification(std::string specName);

    /**
     * Print one line to console with color formatting if needed
     * @return the number of successful and unsuccessful tests respectively.
     */
    virtual std::pair<unsigned , unsigned> runSpecification() = 0;
};


#endif //SIMPLE_TEMPLATES_SPECIFICATION_HPP
