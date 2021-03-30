#include <iostream>
#include <algorithm>
#include <fstream>
#include "Container.h"
#include "List.h"


using namespace std;

void addList(Container<List *> &list);               //dodaje liste do vektora
void delList(Container<List *> &list);              //usuwa liste
void print(Container<List *> &list, bool decision, int valid = INT16_MIN); //wypisuje nazwy list wraz z indexami
int chooseList(Container<List *> &list);           //zwraca index wybranej listy
void update(Container<List *> &list);            //upgraduje nasza liste(umożliwa czynnosci dotyczące edycji)
void copyList(Container<List *> &list);         //kopiuje zawartość listy do nowo utworzonej nowej.
void mergeList(Container<List *> &list);       //scala dwie listy w jedna
void move(List *, Container<List *> &list);

void check(double &);
void check(int &, int border, int valid = INT16_MIN);

struct NegativeNumberError : public std::exception {};

int main(int argc, char *argv[]) {

    /*zmiana strumienia buffora pamieci */
    std::ifstream in;
    if (argc > 1) {
        in.open(argv[1]);
        std::cin.rdbuf(in.rdbuf());
    }


    Container<List *> list;

    cout << "Zostałeś nominowany do bycia tym szczęśliwcem, który wybierze się na zakupy, lepiej zrób liste!" << endl;
    cout << "-----------------------------------------------------------" << endl;

    int choice = -1;

    while (choice) {

        cout << "\n------- MENU -------\n"
                "1: Dodaj liste\n"
                "2: Modyfikuj liste\n"
                "3: Usuń liste\n"
                "4: Kopiuj liste\n"
                "5: Spis list\n"
                "6: Scal liste\n"
                "0: Wyjście\n"


                "Wybierz akcje: " << std::endl;
        choice = getInt();
        switch (choice) {
            case 0:
                return 0;
            case 1:
                addList(list);
                break;
            case 2:
                update(list);
                break;
            case 3:
                delList(list);
                break;
            case 4:
                copyList(list);
                break;
            case 5:
                print(list, true);
                break;
            case 6:
                mergeList(list);
                break;

            default:


                cerr << "ERROR:Niepoprawny wybór, spróbuj jeszcze raz";


        }
    }


}

int chooseList(Container<List *> &list) {
    int choice;


    cout << "Wybierz liste: " << endl;
    print(list, false);
    choice = getIndex(list.size());
    std::cout << "Wybieram liste " << list[choice]->getName() << std::endl;

    return choice;
}

void update(Container<List *> &list) {
    if (list.empty()) {

        cerr << ("ERROR:Nie masz żadnej listy, dodaj ją napierw.") << endl;
        return;
    }

    int index = chooseList(list);
    int choice = -1;

    while (choice) {

        cout << endl << "-------" << list[index]->getName() << "-------" << endl <<
             "1: Dodaj produkt\n"
             "2: Usuń produkt\n"
             "3: Wyczyść liste\n"
             "4: Zmień ilość produktu\n"
             "5: Pokaż liste\n"
             "6: Przenieś produkt\n"
             "0: Wyjście\n:"

             "Wybierz akcje: " << endl;
        choice = getInt();
        switch (choice) {
            case 0:
                return;

            case 1:
                list[index]->addProdukt();
                break;

            case 2:
                list[index]->delProdukt();
                break;
            case 3:
                list[index]->clear();
                break;

            case 4:
                list[index]->changeCount();
                break;

            case 5:
                cout << *list[index];
                break;
            case 6:
                move(list[index], list);
                break;

            case 7:

            default:

                cerr << "ERROR:Niepoprawny wybór, spróbuj jeszcze raz";

        }


    }

}

void addList(Container<List *> &list) {

    cout << "Podaj nazwe listy: ";
    string name = getString();

    /*Sprawdzenie czy nie istnieje już lista o takiej nazwie*/
    for (List *l : list) {
        if (l->getName() == name) {
            cout << "Lista o tej nazwie już istnieje!" << endl;
            return addList(list);
        }
    }


    List *l = new List(name);
    list.push_back(l);
    cout << "Pomyślnie utworzono liste " << l->getName();
}

void delList(Container<List *> &list) {

    if (list.empty()) {
        cerr << ("ERROR:Nie masz żadnej listy, dodaj ją napierw.") << endl;
        return;
    }
    int index = chooseList(list);
    cout << "Lista " << list[index]->getName() << " została na stałe usunięta." << endl;
    delete list[index];
    list.erase(list.begin() + index);


}

void copyList(Container<List *> &list) {
    if (list.empty()) {
        cerr << ("ERROR:Nie masz żadnej listy, dodaj ją napierw.") << endl;
        return;
    }

    int index = chooseList(list);
    /*Sprawdzenie czy przypadkiem nie ma już takiej kopii*/
    for (List *l : list) {
        if (list[index]->getName() + "(kopia)" == l->getName()) {
            cerr << ("ERROR:Istnieje już taka kopia!") << endl;
            return;
        }
    }
    List *temp = new List;
    *temp = *list[index];//korzystamy z operatora przypisywania=
    list.push_back(temp);


}

void print(Container<List *> &list, bool decision, int valid) {

    if (list.empty()) {
        cerr << ("ERROR:Nie masz żadnej listy, dodaj ją napierw.") << endl;
        return;
    }
    for (int i = 0; i < list.size(); i++) {
        if (i != valid)
            cout << "Lista nr: " << i + 1 << ": " << list[i]->getName() << endl;
        if (decision)
            cout << "\t---Stan---\n" << *list[i] << endl; //operator<<

    }
}

void mergeList(Container<List *> &list) {

    if (list.size() <= 1) {
        cerr << "ERROR: Nie wystarczająca ilość list" << endl;
        return;
    }

    int index1 = chooseList(list);

    if (!list[index1]->currentState()) {
        cerr << "ERROR: Nie możesz przenieść elementów z pustej listy";
        return;
    }

    auto itr = find(list.begin(), list.end(), list[index1]);
    int valid = distance(list.begin(), itr);

    cout << "Wybierz liste, którą chcesz dołączyć:\n ";
    print(list, false, valid);
    int index2 = getIndex(list.size(), valid);

    int count = 0;
    for (int i = 0; i < list[index1]->currentState(); i++)
        if (list[index2]->compare(*list[index1]->p_list[i]) != INT16_MIN)
            count++;

    if (list[index1]->currentState() + list[index2]->currentState() - count > 10) {
        cerr << "ERROR: Scalona lista nie zmieści się w zakresie 10 elementów.";
        return;
    }

    for (int i = 0; i < list[index2]->currentState(); i++)
        list[index2]->moveProdukt(*list[index1], i);

    delete list[index2];
    list.erase(list.begin() + index2);

}

void move(List *l, Container<List *> &list) {

    /*Sprawdzenie poprawności potrzebnych do przeprowadzenia tej operacji*/
    if (!l->currentState() || list.size() <= 1) {
        cerr << "ERROR: Coś poszło nie tak " << endl;
        return;
    }

    auto itr = find(list.begin(), list.end(), l);
    int valid = distance(list.begin(), itr);
    print(list, false, valid);
    int l_index = getIndex(list.size(), valid);

    cout << "Podaj index produktu, który chcesz przenieść:\n" << *l << endl;
    int p_index = getIndex(l->currentState());
    l->moveProdukt(*list[l_index], p_index, true);

}

string getString() {

    string str;
    getline(cin, str);
    bool error = false;
    while (!error) {
        if (str.empty()) {
            cerr << "\nNie wprowadziłeś nazwy!! Spróbuj jeszcze raz:\t";
            getline(cin, str);
            error = false;

        } else error = true;
    }
    return str;
}


int getIndex(int border, int valid) {

    string num;
    int num_i;
    getline(std::cin, num);

    while (true) {
        try {
            num_i = stoi(num) - 1; //wyrzuca wyjatek invalid_argument
            check(num_i, border, valid);
            return num_i;

        }
        catch (invalid_argument &) {
            cerr << "\n[INDEX]Zła wartość! Spróbuj jeszcze raz: \t";

        }
        catch (out_of_range &) {
           cerr << "\n[INDEX]Nie ma takiego indexu! Spróbuj jeszcze raz: \t";

        }
        getline(std::cin, num);
    }

}

int getInt() {
    return static_cast<int>(getDouble());
}

double getDouble() {
    string num;
    double num_d;
    getline(std::cin, num);

    while (true) {
        try {
            num_d = stod(num); //wyrzuca wyjatek invalid_argument
            check(num_d);
            return num_d;
        }


        catch (invalid_argument &) {
            cerr << "\nZła wartość! Spróbuj jeszcze raz: \t";

        }
        catch (NegativeNumberError &) {
            cerr << "\nUjemna wartość! Spróbuj jeszcze raz: \t";

        }
        getline(std::cin, num);
    }
}

void check(double &num) {

    if (num < 0)
        throw NegativeNumberError();


}

void check(int &num, int border, int valid) {

    if (num < 0 || num >= border || num == valid)
        throw out_of_range("Nie ma takiego indexu");
}