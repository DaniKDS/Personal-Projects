#include "Retea.h"
#include <fstream>
#include <iostream>
#include <string>

Retea::Retea()
= default;

Retea::Retea(string fisierUtilizatori, string fisierEvenimente)
{
    this->fisierUtilizatori = fisierUtilizatori;
    this->fisierEvenimente = fisierEvenimente;

    try { 
        citireEvenimenteDinFisier();
        citireUtilizatoriDinFisier();
    } catch (string& e) {
        cout << e << endl;
    }
}

Retea::~Retea()
{
    if (!fisierEvenimente.empty())
        salvareEvenimenteInFisier();

    if (!fisierUtilizatori.empty())
        salvareUtilizatoriInFisier();
}

void Retea::adaugaUtilizator(const Utilizator& u) {
    Lista<Utilizator> lista = getUtilizatori();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == u.getId()) {
            throw string("Utilizatorul exista deja!");
        }
    }

    utilizatori.adauga(u);
}

void Retea::adaugaEveniment(const Eveniment& e) {
    Lista<Eveniment> lista = getEvenimente();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == e.getId()) {
            throw string("Evenimentul exista deja!");
        }
    }
    evenimente.adauga(e);
}

void Retea::creeazaChat(const Chat& c) {
    Lista<Chat> lista_chats = getChats();
    Lista<Utilizator> lista_utilizatori = getUtilizatori();

    bool user1gasit = false;
    bool user2gasit = false;

    for (int i = 0; i < lista_chats.getDim(); i++) {
        if (lista_chats[i].getIdUser1() == c.getIdUser1() && lista_chats[i].getIdUser2() == c.getIdUser2()) {
            throw string("Chatul exista deja!");
        }
    }

    for (int i = 0; i < lista_utilizatori.getDim(); i++) {
        if (lista_utilizatori[i].getId() == c.getIdUser1()) {
            user1gasit = true;
        }
        if (lista_utilizatori[i].getId() == c.getIdUser2()) {
            user2gasit = true;
        }
    }

    if (!user1gasit) {
        throw string("Utilizatorul cu id-ul " + to_string(c.getIdUser1()) + " nu exista!");
    }

    if (!user2gasit) {
        throw string("Utilizatorul cu id-ul " + to_string(c.getIdUser2()) + " nu exista!");
    }

    for (int i = 0; i < lista_chats.getDim(); i++) {
        if (lista_chats[i].getId() == c.getId()) {
            throw string("Chatul exista deja!");
        }
    }

    chats.adauga(c);
}

void Retea::trimiteMesaj(int id_user_expeditor, int id_user_destinatar, string mesaj) {
    for (int i = 0; i < chats.getDim(); i++) {
        if ((chats[i].getIdUser1() == id_user_expeditor && chats[i].getIdUser2() == id_user_destinatar) || (chats[i].getIdUser1() == id_user_destinatar && chats[i].getIdUser2() == id_user_expeditor)) {
            cout << "before dump" << endl;
            chats[i].addMesaj(id_user_expeditor, mesaj);
            cout << "after dump" << endl;
            return;
        }
    }
    
    throw string("Nu exista un chat intre acesti doi utilizatori!");
}

void Retea::modificaUtilizator(int id, const Utilizator& u) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id) {
            this->utilizatori.sterge(lista[i]);
            this->utilizatori.adauga(u);
            return;
        }
    }

    throw string("Utilizatorul cu id-ul " + to_string(id) + " nu exista!");
}

void Retea::modificaEveniment(int id, const Eveniment& e) {
    Lista<Eveniment> lista = this->evenimente.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id) {
            this->evenimente.sterge(lista[i]);
            this->evenimente.adauga(e);
            return;
        }
    }

    throw string("Evenimentul cu id-ul " + to_string(id) + " nu exista!");
}

void Retea::stergeUtilizator(int id) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id) {
            this->stergereUtilizatorDinListe(id);
            this->utilizatori.sterge(lista[i]);
            return;
        }
    }

    throw string("Utilizatorul cu id-ul " + to_string(id) + " nu exista!");
}

void Retea::stergeEveniment(int id) {
    Lista<Eveniment> lista = this->evenimente.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id) {
            this->stergeEvenimentDinListe(id);
            this->evenimente.sterge(lista[i]);
            return;
        }
    }
    throw string("Evenimentul cu id-ul " + to_string(id) + " nu exista!");
}

Utilizator Retea::getUtilizator(int id) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id) {
            return lista[i];
        }
    }

    throw string("Utilizatorul cu id-ul " + to_string(id) + " nu exista!");
}

Eveniment Retea::getEveniment(int id) {
    Lista<Eveniment> lista = this->evenimente.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id) {
            return lista[i];
        }
    }

    throw string("Evenimentul cu id-ul " + to_string(id) + " nu exista!");
}

Chat Retea::getChat(int id) {
    for (int i = 0; i < chats.getDim(); i++) {
        if (chats[i].getId() == id) {
            return chats[i];
        }
    }

    throw string("Chatul cu id-ul " + to_string(id) + " nu exista!");
}

Lista<Utilizator> Retea::getUtilizatori() {
    return this->utilizatori.get_lista_ordonata();
}

Lista<Eveniment> Retea::getEvenimente() {
    return this->evenimente.get_lista_ordonata();
}

Lista<Chat> Retea::getChats() {
    return this->chats;
}

Chat Retea::getChatBetween(int id_user1, int id_user2) {

    for (int i = 0; i < chats.getDim(); i++) {
        if (chats[i].getIdUser1() == id_user1 && chats[i].getIdUser2() == id_user2) {
            return chats[i];
        }
        else if (chats[i].getIdUser1() == id_user2 && chats[i].getIdUser2() == id_user1) {
            return chats[i];
        }
    }
    throw string("Nu exista niciun chat intre acesti utilizatori!");
}

void Retea::adaugarePrietenie(int id_user1, int id_user2) {
    //se stabileste intre 2 useri
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    Utilizator *u1 = nullptr;
    Utilizator *u2 = nullptr;

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id_user1) {
            u1 = &lista[i];
        }
        if (lista[i].getId() == id_user2) {
            u2 = &lista[i];
        }
    }

    if (u1 == nullptr || u2 == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user1) + " sau cu id-ul " + to_string(id_user2) + " nu exista!");
    }

    if (u1->getId() == u2->getId()) {
        throw string("Nu se poate adauga prietenie cu sine insusi!");
    }

    Lista<int> prieteniU1 = u1->getPrieteni();
    Lista<int> prieteniU2 = u2->getPrieteni();

    for (int i = 0; i < prieteniU1.getDim(); i++) {
        if (prieteniU1[i] == u2->getId()) {
            throw string("Utilizatorul cu id-ul " + to_string(id_user2) + " este deja prieten cu utilizatorul cu id-ul " + to_string(id_user1) + "!");
        }
    }

    u1->addPrieten(u2->getId());
    u2->addPrieten(u1->getId());

    this->utilizatori.sterge(*u1);
    this->utilizatori.sterge(*u2);

    this->utilizatori.adauga(*u1);
    this->utilizatori.adauga(*u2);
}

void Retea::stergerePrietenie(int id_user1, int id_user2) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    Utilizator *u1 = nullptr;
    Utilizator *u2 = nullptr;

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id_user1) {
            u1 = &lista[i];
        }
        if (lista[i].getId() == id_user2) {
            u2 = &lista[i];
        }
    }

    if (u1 == nullptr || u2 == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user1) + " sau cu id-ul " + to_string(id_user2) + " nu exista!");
    }

    if (u1->getId() == u2->getId()) {
        throw string("Nu se poate sterge prietenia cu sine insusi!");
    }

    Lista<int> prieteniU1 = u1->getPrieteni();
    Lista<int> prieteniU2 = u2->getPrieteni();

    for (int i = 0; i < prieteniU1.getDim(); i++) {
        if (prieteniU1[i] == u2->getId()) {
            u1->removePrieten(u2->getId());
            u2->removePrieten(u1->getId());

            this->utilizatori.sterge(*u1);
            this->utilizatori.sterge(*u2);

            this->utilizatori.adauga(*u1);
            this->utilizatori.adauga(*u2);
            return;
        }
    }

    throw string("Utilizatorul cu id-ul " + to_string(id_user2) + " nu este prieten cu utilizatorul cu id-ul " + to_string(id_user1) + "!");
}

Lista<int> Retea::getPrieteni(int id_user) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    Utilizator *u = nullptr;

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id_user) {
            u = &lista[i];
        }
    }

    if (u == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user) + " nu exista!");
    }

    return u->getPrieteni();
}

void Retea::adaugareUrmaritor(int id_user1, int id_user2) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    Utilizator *u1 = nullptr;
    Utilizator *u2 = nullptr;

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id_user1) {
            u1 = &lista[i];
        }
        if (lista[i].getId() == id_user2) {
            u2 = &lista[i];
        }
    }

    if (u1 == nullptr || u2 == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user1) + " sau cu id-ul " + to_string(id_user2) + " nu exista!");
    }

    if (u1->getId() == u2->getId()) {
        throw string("Nu se poate urmari pe el insusi.");
    }

    Lista<int> urmaritoriU1 = u1->getFollowers();

    for (int i = 0; i < urmaritoriU1.getDim(); i++) {
        if (urmaritoriU1[i] == u2->getId()) {
            throw string("Utilizatorul cu id-ul " + to_string(id_user2) + " urmareste deja utilizatorul cu id-ul " + to_string(id_user1) + "!");
        }
    }

    u1->addFollower(u2->getId());
    u2->addFollowing(u1->getId());

    this->utilizatori.sterge(*u1);
    this->utilizatori.sterge(*u2);

    this->utilizatori.adauga(*u1);
    this->utilizatori.adauga(*u2);
}

void Retea::stergereUrmaritor(int id_user1, int id_user2) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    Utilizator *u1 = nullptr;
    Utilizator *u2 = nullptr;

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id_user1) {
            u1 = &lista[i];
        }
        if (lista[i].getId() == id_user2) {
            u2 = &lista[i];
        }
    }

    if (u1 == nullptr || u2 == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user1) + " sau cu id-ul " + to_string(id_user2) + " nu exista!");
    }

    if (u1->getId() == u2->getId()) {
        throw string("Nu se poate face asa ceva.");
    }

    Lista<int> urmaritoriU1 = u1->getFollowers();

    for (int i = 0; i < urmaritoriU1.getDim(); i++) {
        if (urmaritoriU1[i] == u2->getId()) {
            u1->removeFollower(u2->getId());
            u2->removeFollowing(u1->getId());

            this->utilizatori.sterge(*u1);
            this->utilizatori.sterge(*u2);
            return;
        }
    }

    throw string("Utilizatorul cu id-ul " + to_string(id_user2) + " nu urmareste utilizatorul cu id-ul " + to_string(id_user1) + "!");
}

Lista<int> Retea::getUrmaritori(int id_user) {
    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    Utilizator *u = nullptr;

    for (int i = 0; i < lista.getDim(); i++) {
        if (lista[i].getId() == id_user) {
            u = &lista[i];
        }
    }

    if (u == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user) + " nu exista!");
    }

    return u->getFollowers();
}

void Retea::participareEveniment(int id_user, int id_eveniment) {
    Lista<Utilizator> listaU = this->utilizatori.get_lista_ordonata();

    Utilizator *u = nullptr;

    for (int i = 0; i < listaU.getDim(); i++) {
        if (listaU[i].getId() == id_user) {
            u = &listaU[i];
        }
    }

    if (u == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user) + " nu exista!");
    }

    Lista<Eveniment> listaE = this->evenimente.get_lista_ordonata();

    Eveniment *e = nullptr;

    for (int i = 0; i < listaE.getDim(); i++) {
        if (listaE[i].getId() == id_eveniment) {
            e = &listaE[i];
        }
    }

    if (e == nullptr) {
        throw string("Evenimentul cu id-ul " + to_string(id_eveniment) + " nu exista!");
    }

    Lista<int> participanti = e->getParticipanti();

    for (int i = 0; i < participanti.getDim(); i++) {
        if (participanti[i] == u->getId()) {
            throw string("Utilizatorul cu id-ul " + to_string(id_user) + " participa deja la evenimentul cu id-ul " + to_string(id_eveniment) + "!");
        }
    }

    e->addParticipant(u->getId());
    u->addEveniment(e->getId());

    this->evenimente.sterge(*e);
    this->evenimente.adauga(*e);

    this->utilizatori.sterge(*u);
    this->utilizatori.adauga(*u);
}

void Retea::stergereParticipare(int id_user, int id_eveniment) {
    Lista<Utilizator> listaU = this->utilizatori.get_lista_ordonata();

    Utilizator *u = nullptr;

    for (int i = 0; i < listaU.getDim(); i++) {
        if (listaU[i].getId() == id_user) {
            u = &listaU[i];
        }
    }

    if (u == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user) + " nu exista!");
    }

    Lista<Eveniment> listaE = this->evenimente.get_lista_ordonata();

    Eveniment *e = nullptr;

    for (int i = 0; i < listaE.getDim(); i++) {
        if (listaE[i].getId() == id_eveniment) {
            e = &listaE[i];
        }
    }

    if (e == nullptr) {
        throw string("Evenimentul cu id-ul " + to_string(id_eveniment) + " nu exista!");
    }

    Lista<int> participanti = e->getParticipanti();

    for (int i = 0; i < participanti.getDim(); i++) {
        if (participanti[i] == u->getId()) {
            e->removeParticipant(u->getId());
            u->removeEveniment(e->getId());

            this->evenimente.sterge(*e);
            this->evenimente.adauga(*e);

            this->utilizatori.sterge(*u);
            this->utilizatori.adauga(*u);
            return;
        }
    }

    throw string("Utilizatorul cu id-ul " + to_string(id_user) + " nu participa la evenimentul cu id-ul " + to_string(id_eveniment) + "!");
}

Lista<int> Retea::getParticipanti(int id_eveniment) {
    Lista<Eveniment> listaE = this->evenimente.get_lista_ordonata();

    Eveniment *e = nullptr;

    for (int i = 0; i < listaE.getDim(); i++) {
        if (listaE[i].getId() == id_eveniment) {
            e = &listaE[i];
        }
    }

    if (e == nullptr) {
        throw string("Evenimentul cu id-ul " + to_string(id_eveniment) + " nu exista!");
    }

    return e->getParticipanti();
}

Lista<int> Retea::getEvenimenteParticipate(int id_user) {
    Lista<Utilizator> listaU = this->utilizatori.get_lista_ordonata();

    Utilizator *u = nullptr;

    for (int i = 0; i < listaU.getDim(); i++) {
        if (listaU[i].getId() == id_user) {
            u = &listaU[i];
        }
    }

    if (u == nullptr) {
        throw string("Utilizatorul cu id-ul " + to_string(id_user) + " nu exista!");
    }

    return u->getEvenimente();
}


void Retea::setFisierUtilizatori(const string &fisierUtilizatori_) { 
    fisierUtilizatori = fisierUtilizatori_; 
}

void Retea::setFisierEvenimente(const string &fisierEvenimente_) { 
    fisierEvenimente = fisierEvenimente_; 
}

void Retea::salvareUtilizatoriInFisier() {
    ofstream fout(fisierUtilizatori);

    if (!fout.is_open()) {
        throw string("Fisierul " + fisierUtilizatori + " nu a putut fi deschis!");
    }

    Lista<Utilizator> lista = this->utilizatori.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        fout << lista[i] << endl;
    }    
}

void Retea::citireUtilizatoriDinFisier() {
    ifstream fin(fisierUtilizatori);

    if (!fin.is_open()) {
        throw string("Fisierul " + fisierUtilizatori + " nu a putut fi deschis!");
    }

    Utilizator u;
    while (fin >> u) {
        this->utilizatori.adauga(u);
    }
}

void Retea::salvareEvenimenteInFisier() {
    ofstream fout(fisierEvenimente);

    if (!fout.is_open()) {
        throw string("Fisierul " + fisierEvenimente + " nu a putut fi deschis!");
    }

    Lista<Eveniment> lista = this->evenimente.get_lista_ordonata();

    for (int i = 0; i < lista.getDim(); i++) {
        fout << lista[i] << endl;
    }
}

void Retea::citireEvenimenteDinFisier() {
    ifstream fin(fisierEvenimente);

    if (!fin.is_open()) {
        throw string("Fisierul " + fisierEvenimente + " nu a putut fi deschis!");
    }

    while (!fin.eof()) {
        Eveniment e;
        fin >> e;

        if (fin.eof()) {
            break;
        }

        this->evenimente.adauga(e);
    }
}

void Retea::stergereUtilizatorDinListe(int id) {
    Lista<Utilizator> listaUtilizatori = this->utilizatori.get_lista_ordonata();

    for (int i = 0; i < listaUtilizatori.getDim(); i++) {
        if (listaUtilizatori[i].getId() != id) {
            listaUtilizatori[i].removePrieten(id);
            listaUtilizatori[i].removeFollower(id);
            listaUtilizatori[i].removeFollowing(id);
        }
    }

    Lista<Eveniment> listaEvenimente = this->evenimente.get_lista_ordonata();

    for (int i = 0; i < listaEvenimente.getDim(); i++) {
        listaEvenimente[i].removeParticipant(id);
    }

}

void Retea::stergeEvenimentDinListe(int id) {
    Lista<Utilizator> listaUtilizatori = this->utilizatori.get_lista_ordonata();

    for (int i = 0; i < listaUtilizatori.getDim(); i++) {
        listaUtilizatori[i].removeEveniment(id);
    }
}

