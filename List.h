//
// Created by szymon on 16.11.2020.
//

#ifndef ZAKUPY_LISTA_H
#define ZAKUPY_LISTA_H


#include "Product.h"
#include "Container.h"
#include "Product_per_pieces.h"
#include "Product_per_litr.h"
#include "Product_per_weight.h"

constexpr size_t max_elem = 10;

class List {
private:

    std::string _name;
    Container<Product *> p_list;


public:
    friend void mergeList(Container<List *> &list);

    friend std::ostream &operator<<(std::ostream &window, const List &l);


    explicit List(std::string  = "");


    List(const List &);

    ~List();


    List &operator=(const List &);                         //kopiujący operator przypisania
    std::string getName() const { return _name; }        //Zwraca nazwe listy
    void addProdukt();                                  //Dodaje produkt do listy
    void delProdukt();                                 //Usuwa produkt z listy
    void changeCount();                              //Zmienia ilość elementu na liscie
    void clear();                                   //Czyści całą liste//
    static Product *createProdukt(std::string &name);

    void moveProdukt(List &, int index, bool version = false); //metoda przenosi produkt na inna liste

    size_t currentState() const { return p_list.size(); }


    int compare(const Product &);


};

/*Definicje tych funkcji znajduja sie w pliku main.ccp, poniewaz nie maja nic wspólnego z klasa List,
 * a chciałem żeby moduly były przeznaczone tylko dla funkcji mających cos wspólnego z klasa, a
 * deklaracje znajduja sie tutaj, ponieważ korzystam z tych funkcji w w tej klasie*/
std::string getString(); //za pomocą getline pobieramy stringa

int getIndex(int border, int valid = INT16_MIN); //za pomoca getline, pobieramy index zgodny z granica

int getInt(); //za pomoca getline pobieramy inta>0

double getDouble();


#endif //ZAKUPY_LISTA_H
