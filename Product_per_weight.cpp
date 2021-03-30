//
// Created by szymon on 06.12.2020.
//

#include "Product_per_weight.h"

Product_per_weight::Product_per_weight(char *name, double number) : _name(nullptr), weight(number) {
    if (name) {
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
    } else
        _name = nullptr;

}

Product_per_weight::~Product_per_weight() {
    delete[] _name;
}

Product_per_weight::Product_per_weight(const std::string &name, double number) {
    if (name.c_str()) {
        _name = new char[strlen(name.c_str()) + 1];
        strcpy(_name, name.c_str());
    } else
        _name = nullptr;

    weight = number;
}


Product_per_weight::Product_per_weight(const Product_per_weight &p) : Product_per_weight(p._name, p.weight) {

}

Product_per_weight &Product_per_weight::operator=(const Product &p) {
    const Product_per_weight p_weight = dynamic_cast<const Product_per_weight &>(p);

    if (&p_weight != this) {
        delete[] _name;

        if (p_weight._name)
            _name = new char[strlen(p_weight._name) + 1];
        else
            _name = nullptr;

        strcpy(_name, p_weight._name);
        weight = p_weight.weight;


    }
    return *this;
}


void Product_per_weight::changeCount(double new_weight) {
    weight = new_weight;
}

void Product_per_weight::print(std::ostream &window) const {

    window << _name << " " << weight << "kg" << std::endl;
}


void Product_per_weight::operator+=(const Product &p) {
    const Product_per_weight p_liter = dynamic_cast<const Product_per_weight &>(p);

    weight += p_liter.weight;

}
