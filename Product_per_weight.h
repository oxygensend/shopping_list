//
// Created by szymon on 06.12.2020.
//

#ifndef BERDZIKSZYMON_ETAP1_PRODUCT_PER_WEIGHT_H
#define BERDZIKSZYMON_ETAP1_PRODUCT_PER_WEIGHT_H

#include "Product.h"

class Product_per_weight : public Product {
protected:
    char *_name;
    double weight;


    void print(std::ostream &window) const override;

public:

    explicit Product_per_weight(char * = nullptr, double = 0);

    ~Product_per_weight();


    Product_per_weight(const std::string &, double);

    Product_per_weight(const Product_per_weight &);

    void operator+=(const Product &) override;

    Product_per_weight &operator=(const Product &) override;

    Product_per_weight *allocate() override { return new Product_per_weight; }

    void changeCount(double new_liters) override;

    std::string getName() const override { return _name; }

};

#endif //BERDZIKSZYMON_ETAP1_PRODUCT_PER_WEIGHT_H
