#ifndef UI_H
#define UI_H

#include "Retea.h"

class UserInterface {
public:
    UserInterface(Retea& retea);
    ~UserInterface();

    void run();

    void adaugaUtilizator();
    void adaugaEveniment();
    void creeazaChat();

    void trimiteMesaj();

    void modificaUtilizator();
    void modificaEveniment();

    void stergeUtilizator();
    void stergeEveniment();

    void afiseazaUtilizator();
    void afiseazaEveniment();
    void afiseazaChat();

    void afiseazaUtilizatori();
    void afiseazaEvenimente();
    void afiseazaChats();
    void afiseazaChatsBetween();

    void adaugarePrietenie();
    void stergerePrietenie();
    void afisarePrieteni();

    void adaugareUrmaritor();
    void stergereUrmaritor();
    void afisareUrmaritori();

    void participareEveniment();
    void stergereParticipare();
    void afisareParticipanti();
    void afisareEvenimenteParticipate();

private:
    Retea &retea;    
};

#endif // UI_H
