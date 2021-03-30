//
// Created by szymon on 06.12.2020.
//

#ifndef BERDZIKSZYMON_ETAP1_PRODUCT_PER_PIECES_H
#define BERDZIKSZYMON_ETAP1_PRODUCT_PER_PIECES_H

#include "Product.h"

class Product_per_pieces : public Product {
protected:
    char *_name;
    int count;

    void print(std::ostream &window) const override;

public:

     explicit Product_per_pieces(char * = nullptr, int = 0);

    ~Product_per_pieces();

    Product_per_pieces(const std::string &, int);

    Product_per_pieces(const Product_per_pieces &);

    void operator+=(const Product &) override;

    Product_per_pieces &operator=(const Product &) override;

    Product_per_pieces *allocate() override { return new Product_per_pieces; }

    void changeCount(double new_liters) override;

    std::string getName() const override { return _name; }
};

#endif //BERDZIKSZYMON_ETAP1_PRODUCT_PER_PIECES_H
