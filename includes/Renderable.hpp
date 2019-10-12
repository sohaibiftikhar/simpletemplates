#include <utility>

//
// Created by Sohaib Iftikhar on 2019-10-08.
//

#include <iostream>
#include <utility>
#include <vector>
#include <bits/unique_ptr.h>

#ifndef SIMPLE_TEMPLATES_RENDERABLE_HPP
#define SIMPLE_TEMPLATES_RENDERABLE_HPP

#endif //SIMPLE_TEMPLATES_RENDERABLE_HPP

class Renderable {
public:
    virtual void render(std::ostream& os) = 0;
};

class StringRenderable: public Renderable {
public:
    const std::string value;
    StringRenderable(std::string str);
    void render(std::ostream&) override;
};

class IntRenderable: public Renderable {
public:
    const int value;
    IntRenderable(int i);
    void render(std::ostream&) override;
};

class FloatRenderable: public Renderable {
public:
    const float value;
    FloatRenderable(float f);
    void render(std::ostream&) override;
};

class BoolRenderable: public Renderable {
public:
    bool value;
    BoolRenderable(bool b);
    void render(std::ostream&) override;
};

class ListRenderable: public Renderable {
public:
    std::vector<std::unique_ptr<Renderable>> value;
    ListRenderable(std::vector<std::unique_ptr<Renderable>> b);
    void render(std::ostream&) override;
};