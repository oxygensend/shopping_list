//
// Created by szymon on 16.11.2020.
//

#ifndef ZAKUPY_PRODUKT_H
#define ZAKUPY_PRODUKT_H

#include<iostream>
#include <string>
#include <cstring>

class Product {
protected:
    virtual void print(std::ostream &window) const = 0;

public:
    friend std::ostream &operator<<(std::ostream &window, const Product &p) {

        p.print(window);
        return window;

    }

    virtual ~Product() {};

    virtual void operator+=(const Product &) = 0;

    virtual Product &operator=(const Product &) = 0;

    virtual std::string getName() const = 0;

    virtual void changeCount(double new_count) = 0;

    virtual Product* allocate() = 0;


};

#endif //ZAKUPY_PRODUKT_H
