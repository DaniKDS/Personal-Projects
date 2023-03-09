#include "Eveniment.h"
#include <fstream>

Eveniment::Eveniment()
= default;

Eveniment::Eveniment(int id, string nume, string data, string locatie)
{
    this->id = id;
    this->nume = nume;
    this->data = data;
    this->locatie = locatie;
}

Eveniment::~Eveniment()
= default;

int Eveniment::getId() const {
    return id;
}


string Eveniment::getNume() const {
    return nume;
}

string Eveniment::getData() const {
    return data;
}

string Eveniment::getLocatie() const {
    return locatie;
}

Lista<int> Eveniment::getParticipanti() const {
    return participanti;
}

void Eveniment::setId(int id) {
    this->id = id;
}

void Eveniment::setNume(string nume) {
    this->nume = nume;
}

void Eveniment::setData(string data) {
    this->data = data;
}

void Eveniment::setLocatie(string locatie) {
    this->locatie = locatie;
}

void Eveniment::addParticipant(int id) {
    participanti.adauga(id);
}

void Eveniment::removeParticipant(int id) {
    for (int i = 0; i < participanti.getDim(); i++) {
        if (participanti[i] == id) {
            participanti.sterge(i);
            break;
        }
    }
}

bool Eveniment::operator<(const Eveniment& e) {
    return this->nume < e.nume;
}

bool Eveniment::operator>(const Eveniment& e) {
    return this->nume > e.nume;
}

ostream& operator<<(ostream& out, Eveniment& e) {
    out << e.id << " " << e.nume << " " << e.data << " " << e.locatie << " " << e.participanti.getDim() << " ";
    for (int i = 0; i < e.participanti.getDim(); i++) {
        out << e.participanti[i] << " ";
    }

    return out;
}

istream& operator>>(istream& in, Eveniment& e) {
    int nr_participanti;

    in >> e.id >> e.nume >> e.data >> e.locatie >> nr_participanti;
    for (int i = 0; i < nr_participanti; i++) {
        int id;
        in >> id;
        e.participanti.adauga(id);
    }

    return in;
}
