#ifndef RETEA_H
#define RETEA_H

#include "Lista.h"
#include "MultimeOrdonata.h"
#include "Chat.h"
#include "Utilizator.h"
#include "Eveniment.h"

class Retea {
public:
    Retea();
    Retea(string fisierUtilizatori, string fisierEvenimente);
    ~Retea();

    void adaugaUtilizator(const Utilizator& u);
    void adaugaEveniment(const Eveniment& e);
    void creeazaChat(const Chat& c);

    void trimiteMesaj(int id_user_expeditor, int id_user_destinatar, string mesaj);

    void modificaUtilizator(int id, const Utilizator& u);
    void modificaEveniment(int id, const Eveniment& e);

    void stergeUtilizator(int id);
    void stergeEveniment(int id);

    Utilizator getUtilizator(int id);
    Eveniment getEveniment(int id);
    Chat getChat(int id);

    Lista<Utilizator> getUtilizatori();
    Lista<Eveniment> getEvenimente();
    Lista<Chat> getChats();
    Chat getChatBetween(int id_user1, int id_user2);

    void adaugarePrietenie(int id_user1, int id_user2);
    void stergerePrietenie(int id_user1, int id_user2);
    Lista<int> getPrieteni(int id_user);

    // user2 urmareste user1
    void adaugareUrmaritor(int id_user1, int id_user2);
    // user2 nu mai urmareste user1
    void stergereUrmaritor(int id_user1, int id_user2);
    Lista<int> getUrmaritori(int id_user);

    void participareEveniment(int id_user, int id_eveniment);
    void stergereParticipare(int id_user, int id_eveniment);
    Lista<int> getParticipanti(int id_eveniment);
    Lista<int> getEvenimenteParticipate(int id_user);

    void setFisierUtilizatori(const std::string &fisierUtilizatori_);

    void setFisierEvenimente(const std::string &fisierEvenimente_);

private:
    void salvareUtilizatoriInFisier();
    void citireUtilizatoriDinFisier();
    
    void salvareEvenimenteInFisier();
    void citireEvenimenteDinFisier();

    // sterge utilziatorul cu id-ul id din toate listele de prieteni, followeri si following a tuturor ceilalti utilizatori si din listele cu participanti ale evenimentelor
    void stergereUtilizatorDinListe(int id);
    void stergeEvenimentDinListe(int id);

    MultimeOrdonata<Utilizator> utilizatori;
    MultimeOrdonata<Eveniment> evenimente;
    Lista<Chat> chats;

    std::string fisierUtilizatori;
    std::string fisierEvenimente;
};

#endif // RETEA_H
