#include "Chat.h"
#include <fstream>
#include <iostream>
#include <tuple>
#include <iomanip>

Chat::Chat()
= default;

Chat::Chat(int id, int id_user1, int id_user2)
{
    this->id = id;
    this->id_user1 = id_user1;
    this->id_user2 = id_user2;
}

Chat::~Chat()
= default;

int Chat::getId() const {
    return id;
}

int Chat::getIdUser1() const {
    return id_user1;
}

int Chat::getIdUser2() const {
    return id_user2;
}

Lista<pair<int,string>> Chat::getMesaje() const {
    return mesaje;
}

void Chat::setId(int id) {
    this->id = id;
}

void Chat::setIdUser1(int id_user1) {
    this->id_user1 = id_user1;
}

void Chat::setIdUser2(int id_user2) {
    this->id_user2 = id_user2;
}

void Chat::addMesaj(int id_user_trimitor, string mesaj) {
    mesaje.adauga(pair<int, string>(id_user_trimitor, mesaj));
}

ostream& operator<<(ostream& out, Chat& c) {
    out << c.id << " " << c.id_user1 << " " << c.id_user2 << " ";
    out << c.mesaje.getDim() << " ";
    for (int i = 0; i < c.mesaje.getDim(); i++) {
        out << c.mesaje[i].first << " " << std::quoted(c.mesaje[i].second) << " ";
    }
    return out; 
}

istream& operator>>(istream& in, Chat& c) {
    in >> c.id >> c.id_user1 >> c.id_user2;
    int nr_mesaje;
    in >> nr_mesaje;
    for (int i = 0; i < nr_mesaje; i++) {
        int id_user1;
        string mesaj;
        in >> id_user1 >> std::quoted(mesaj);
        c.mesaje.adauga(pair<int, string>(id_user1, mesaj));
    }

    return in;
}