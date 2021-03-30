//
// Created by szymon on 06.12.2020.
//

#include "Product_per_pieces.h"

Product_per_pieces::Product_per_pieces(char *name, int number) : _name(nullptr), count(number) {
    if (name) {
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
    } else
        _name = nullptr;

}


Product_per_pieces::~Product_per_pieces() {
    delete[] _name;
}

Product_per_pieces::Product_per_pieces(const std::string &name, int number) {
    if (name.c_str()) {
        _name = new char[strlen(name.c_str()) + 1];
        strcpy(_name, name.c_str());
    } else
        _name = nullptr;

    count = number;
}

Product_per_pieces::Product_per_pieces(const Product_per_pieces &p) : Product_per_pieces(p._name, p.count) {


}

Product_per_pieces &Product_per_pieces::operator=(const Product &p) {
    const Product_per_pieces p_pieces = dynamic_cast<const Product_per_pieces &>(p);
    if (&p_pieces != this) {
        delete[] _name;

        if (p_pieces._name)
            _name = new char[strlen(p_pieces._name) + 1];
        else
            _name = nullptr;

        strcpy(_name, p_pieces._name);
        count = p_pieces.count;


    }
    return *this;

}

void Product_per_pieces::changeCount(double new_count) {
    count = new_count;
}

void Product_per_pieces::print(std::ostream &window) const {
    window << _name << " " << count << "szt" << std::endl;
}

void Product_per_pieces::operator+=(const Product &p) {
    const Product_per_pieces p_liter = dynamic_cast<const Product_per_pieces &>(p);
    count += p_liter.count;
}
