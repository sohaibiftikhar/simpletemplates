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
