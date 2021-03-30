//
// Created by szymon on 06.12.2020.
//

#include "Product_per_litr.h"

using namespace std;

Product_per_litr::Product_per_litr(char *name, double number) : _name(nullptr), liters(number) {
    if (name) {
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
    } else
        _name = nullptr;



}

Product_per_litr &Product_per_litr::operator=(const Product &p) {
    const Product_per_litr  p_liter = dynamic_cast<const Product_per_litr &>(p);
    if (&p_liter != this) {
        delete[] _name;

        if (p_liter._name)
            _name = new char[strlen(p_liter._name) + 1];
        else
            _name = nullptr;

        strcpy(_name, p_liter._name);
        liters = p_liter.liters;


    }
    return *this;
}

void Product_per_litr::changeCount(double new_liters) {
    liters = new_liters;
}

void Product_per_litr::print(std::ostream &window) const {


    window << _name << " " << liters << "l" << endl;
}

Product_per_litr::~Product_per_litr() {
    delete[] _name;
}

Product_per_litr::Product_per_litr(const string &name, double number) {
    if (name.c_str()) {
        _name = new char[strlen(name.c_str()) + 1];
        strcpy(_name, name.c_str());
    } else
        _name = nullptr;

    liters = number;
}

Product_per_litr::Product_per_litr(const Product_per_litr &p) : Product_per_litr(p._name, p.liters) {

}

void Product_per_litr::operator+=(const Product &p) {
    const Product_per_litr p_liter = dynamic_cast<const Product_per_litr &>(p);
    liters += p_liter.liters;

}

