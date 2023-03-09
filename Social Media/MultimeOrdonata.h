#ifndef MULTIMEORDONATA_H
#define MULTIMEORDONATA_H

#include "Lista.h"
#include <iostream>
using namespace std;

template<class T>
class MultimeOrdonata {
private:
    struct Node {
        T val;
        Node* stanga;
        Node* dreapta;
    };

    Node* radacina;

    void adauga(Node*& radacina, T val) {
        if (radacina == nullptr) {
            radacina = new Node;
            radacina->val = val;
            radacina->stanga = nullptr;
            radacina->dreapta = nullptr;
        }
        else if (val < radacina->val) {
            adauga(radacina->stanga, val);
        }
        else if (val > radacina->val) {
            adauga(radacina->dreapta, val);
        }
    }

    void distruge(Node* radacina) {
        if (radacina != nullptr) {
            distruge(radacina->stanga);
            distruge(radacina->dreapta);
            delete radacina;
        }
    }

    void sterge(Node*& radacina, T val) {
        if (radacina != nullptr) {
            if (val < radacina->val) {
                sterge(radacina->stanga, val);
            }
            else if (val > radacina->val) {
                sterge(radacina->dreapta, val);
            }
            else {
                if (radacina->stanga == nullptr && radacina->dreapta == nullptr) {
                    delete radacina;
                    radacina = nullptr;
                }
                else if (radacina->stanga == nullptr) {
                    Node* temp = radacina;
                    radacina = radacina->dreapta;
                    delete temp;
                }
                else if (radacina->dreapta == nullptr) {
                    Node* temp = radacina;
                    radacina = radacina->stanga;
                    delete temp;
                }
                else {
                    Node* temp = radacina->dreapta;
                    while (temp->stanga != nullptr) {
                        temp = temp->stanga;
                    }
                    radacina->val = temp->val;
                    sterge(radacina->dreapta, temp->val);
                }
            }
        }
    }

    bool exista(Node* radacina, T val) {
        if (radacina != nullptr) {
            if (val < radacina->val) {
                exista(radacina->stanga, val);
            } else if (val > radacina->val) {
                exista(radacina->dreapta, val);
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    void get_ordered_lista(Node* radacina, Lista<T> &l) const {
        if (radacina != nullptr) {
            get_ordered_lista(radacina->stanga, l);
            l.adauga(radacina->val);
            get_ordered_lista(radacina->dreapta, l);
        }
    }

public:
    MultimeOrdonata() {
        radacina = nullptr;
    }

    ~MultimeOrdonata() {
        distruge(radacina);
    }

    void adauga(T val) {
        adauga(radacina, val);
    }

    void sterge(T val) {
        sterge(radacina, val);
    }

    bool exista(T val) {
        return exista(radacina, val);
    }

    Lista<T> get_lista_ordonata() {
        Lista<T> l;
        get_ordered_lista(radacina, l);
        return l;
    }
};

#endif // MULTIMEORDONATA_H
