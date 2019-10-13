//
// Created by Sohaib Iftikhar on 2019-10-09.
//

#include "../includes/Renderable.hpp"
#include <iterator>
#include <iomanip>

StringRenderable::StringRenderable(std::string str): value(std::move(str)) {}

IntRenderable::IntRenderable(int i): value(i) {}

FloatRenderable::FloatRenderable(float i, int precision): value(i), precision(precision) {}

BoolRenderable::BoolRenderable(bool i): value(i) {}

ListRenderable::ListRenderable(std::vector<std::unique_ptr<Renderable>> v): value(std::move(v)) {}

void StringRenderable::render(std::ostream &os) {
    os<<value;
}

void IntRenderable::render(std::ostream &os) {
    os<<value;
}

void FloatRenderable::render(std::ostream &os) {
    os<<std::fixed<<std::setprecision(precision)<<value;
}

void BoolRenderable::render(std::ostream &os) {
    value? os<<"True" : os <<"False";
}

void ListRenderable::render(std::ostream &os) {
    os<<"[";
    for (auto it = value.begin(); it != value.end(); it++) {
        (**it).render(os);
        if (std::distance(it, value.end()) > 1) {
            os<<", ";
        }
    }
    os<<"]";
}