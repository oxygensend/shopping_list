//
// Created by szymon on 06.01.2021.
//

#ifndef BERDZIKSZYMON_ETAP1_CONTAINER_H
#define BERDZIKSZYMON_ETAP1_CONTAINER_H

#include <iostream>
#include <iterator>


template<typename T>
class Container {
private:
    T *tab = nullptr;
    size_t t_size = 0;
    size_t capacity = 0;
    using iterator = T *;


public:
    explicit Container(size_t cap = 2) { reserve(cap); }

    Container(const Container<T> &con);

    ~Container() { delete[] tab; }

    void push_back(const T &element);

    void pop_back();

    void clear();

    bool empty() const { return !t_size; }

    size_t size() const { return t_size; }

    T &operator[](int i) const;

    Container<T> &operator=(const Container<T> &);

    void resize(size_t new_size);

    void reserve(size_t new_capacity);

    iterator begin() { return tab; }

    iterator end() { return tab + size(); }

    T &front() { return tab[0]; }

    T &back() { return tab[size() - 1]; }

    iterator erase(iterator pos);

};

template<typename T>
Container<T>::Container(const Container<T> &con) {
    t_size = con.size();
    capacity = con.capacity;
    tab = new T[capacity];
    for (int i = 0; i < t_size; i++)
        tab[i] = con.tab[i];

}

template<typename T>
void Container<T>::push_back(const T &element) {

    if (t_size >= capacity) {
        reserve(capacity + capacity);
    }
    tab[t_size] = element;
    t_size++;
}

template<typename T>
void Container<T>::pop_back() {
    if (t_size > 0)
        t_size--;
}

template<typename T>
void Container<T>::clear() {
    resize(0);

}

template<typename T>
T &Container<T>::operator[](int i) const {
    if (i <= t_size)
        return tab[i];

    else if (i == -1)
        return tab[t_size - 1];

    else
        throw std::out_of_range("[] - index out of range]");
}


template<typename T>
typename Container<T>::iterator Container<T>::erase(Container::iterator pos) {

    int valid = std::distance(begin(), pos);

    T *new_tab = new T[capacity];
    for (int i = 0; i < valid; i++)
        new_tab[i] = tab[i];

    for (int i = valid; i < size() - 1; i++)
        new_tab[i] = tab[i + 1];

    delete[] tab;
    tab = new_tab;
    t_size--;
    return pos;
}

template<typename T>
void Container<T>::resize(size_t n) {
    t_size = n;
}

template<typename T>
Container<T> &Container<T>::operator=(const Container<T> &con) {
    if (&con != this) {

        delete[] tab;

        t_size = con.t_size;
        capacity = con.capacity;

        tab = new T[capacity];

        for (int i = 0; i < t_size; i++)
            tab[i] = con.tab[i];


    }
    return *this;

}

template<typename T>
void Container<T>::reserve(size_t new_capacity) {
    T *new_tab;
    try {
        new_tab = new T[new_capacity];

    }
    catch (std::bad_alloc &) {
        std::cout << "Nie udało się zaalokowac pamieci\n"
                     "spróbuje jeszcze raz, jeśli znowu się nie uda, wyjdę z bledem";
        new_tab = new T[new_capacity];
    }

    for (int i = 0; i < t_size; i++)
        new_tab[i] = tab[i];

    delete[] tab;
    tab = new_tab;
    capacity = new_capacity;

}


#endif //BERDZIKSZYMON_ETAP1_CONTAINER_H


