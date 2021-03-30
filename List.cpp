//
// Created by szymon on 16.11.2020.
//


#include "List.h"

#include <utility>


using namespace std;


List::List(string name) : _name(std::move(name)) {
    p_list.reserve(max_elem);
}

List::List(const List &l) : List(l._name) {

    for (int i = 0; i < l.currentState(); i++) {
        p_list.push_back( l.p_list[i]->allocate());
        *p_list[i] = *l.p_list[i]; // operator przypisywania z klasy Product

    }
}

List &List::operator=(const List &l) {

    if (&l != this) {


        _name = l._name + "(kopia)";

        p_list.reserve(max_elem);

        for (int i = 0; i < l.currentState(); i++) {
            p_list.push_back(l.p_list[i]->allocate());
            *p_list[i] = *l.p_list[i]; // operator przypisywania z klasy Product

        }

    }
    return *this;

}


List::~List() {

    for (int i = 0; i < currentState(); i++)
        delete p_list[i];


}

void List::addProdukt() {

    if (currentState() == max_elem) {
        cerr << "ERROR:Nie możesz wprowadzić więcej elementów do listy." << endl;
        return;
    }
    cout << "Podaj nazwe : ";
    string name = getString();
    /*Sprawdzam czy nie istnieje już przypadkiem produkt o tej nazwie*/
    for (int i = 0; i < currentState(); i++) {
        if (p_list[i]->getName() == name) {
            cout << "Istnieje już element o takiej nazwie!" << endl;
            return addProdukt();
        }
    }


    Product *p ;


    p = createProdukt(name);


    cout << "Do listy dopisuje  " << *p; // operator << z klasy Product
    p_list.push_back(p);


}

void List::delProdukt() {


    if (p_list.empty()) {

        cerr << "ERROR: Na twojej liście nie ma żadnego elementu" << endl;
        return;
    }

    cout << *this;
    cout << "Podaj numer rzeczy: ";
    int index = getIndex(currentState());

    cout << "Usuwam z listy " << *p_list[index];
    delete p_list[index];

    p_list.erase(p_list.begin() + index);


}


void List::changeCount() {

    if (p_list.empty()) {

        cerr << "ERROR: Na twojej liście nie ma żadnego elementu" << endl;
        return;
    }

    cout << *this << endl << "Podaj index produktu, którego ilość chcesz zmienić: ";
    int index = getIndex(currentState());


    cout << "Podaj nową wartość: ";
    int new_count = getInt();


    p_list[index]->changeCount(new_count);
    cout << "Teraz musisz kupić " << new_count << " " << p_list[index]->getName() << "!!";


}

void List::clear() {

    if (p_list.empty()) {

        cerr << "ERROR: Na twojej liście nie ma żadnego elementu" << endl;
        return;
    }
    cout << "Czy na pewno chcesz wyczyścić całą liste? T/N: ";
    string odp = getString();

    if (odp == "T" || odp == "t") {
        for (int i = 0; i < currentState(); i++)
            delete p_list[i];

        p_list.clear();
    } else
        return;

    cout << " Lista została wyczyszczona!";

}


ostream &operator<<(ostream &window, const List &l) {


    if (l.p_list.empty())
        window << "Lista jest pusta" << endl;
    else
        for (int i = 0; i < l.currentState(); i++)
            window << i + 1 << ": " << *l.p_list[i];

    return window;
}

Product *List::createProdukt(std::string &name) {

    cout << "Podaj jednostke, w której chcesz zliczyć swój produkt\n"
            "1: Sztuki\n"
            "2: Kilogramy\n"
            "3: Litry\n"
            "Wybierz akcje:\n";
    int choice = -1;
    while (true) {

        choice = getInt();

        switch (choice) {

            case 1:
                cout << "Podaj ilość sztuk: ";
                return new Product_per_pieces(name, getInt());


            case 2:
                cout << "Podaj ilość w kilogramach: ";
                return new Product_per_weight(name, getDouble());

            case 3:
                cout << "Podaj ilość w litrach: ";
                return new Product_per_litr(name, getDouble());


            default:
                cerr << "ERROR:Niepoprawny wybór, spróbuj jeszcze raz: ";
        }

    }
    return nullptr;
}


void List::moveProdukt(List &l, int index, bool version) {

    int i = l.compare(*p_list[index]);
    if (i != INT16_MIN) {
        *l.p_list[i] += *p_list[index];
        if (version) {
            cout << "Istnieje już element o takiej nazwie, więc uaktualnie jego ilość!" << endl;
            delete p_list[index];
            p_list.erase(p_list.begin() + index);

        }

        return;
    }

    if (l.currentState() == max_elem) {
        if (version) cerr << "ERROR:Ta lista jest już pełna!" << endl;
        return;
    }

    Product *p = p_list[index];
    p_list[index] = nullptr;
    l.p_list.push_back(p);


    if (version) {
        p_list.erase(p_list.begin() + index);
        cout << "Pomyślnie przeniosłeś produkt na liste " << l.getName() << endl;
    }

}

int List::compare(const Product &p) {

    for (int i = 0; i < currentState(); i++)
        if (typeid(*p_list[i]) == typeid(p) && p_list[i]->getName() == p.getName())
            return i;

    return INT16_MIN;
}
