//
// Created by szymon on 06.12.2020.
//

#ifndef BERDZIKSZYMON_ETAP1_PRODUCT_PER_LITR_H
#define BERDZIKSZYMON_ETAP1_PRODUCT_PER_LITR_H

#include "Product.h"

class Product_per_litr : public Product {
protected:
    char *_name;
    double liters;

    void print(std::ostream &window) const override;

public:

    explicit Product_per_litr(char * = nullptr, double = 0);

    ~Product_per_litr();

    Product_per_litr(const std::string &, double);

    Product_per_litr(const Product_per_litr &);

    Product_per_litr &operator=(const Product &) override;

    void operator+=(const Product &) override;

    Product_per_litr *allocate() override { return new Product_per_litr; }

    void changeCount(double new_liters) override;

    std::string getName() const override { return _name; }
};

#endif //BERDZIKSZYMON_ETAP1_PRODUCT_PER_LITR_H
