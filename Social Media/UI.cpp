#include "UI.h"

#include <iostream>
#include <tuple>

using std::cout;
using std::endl;

UserInterface::UserInterface(Retea &retea) : retea(retea) {}

UserInterface::~UserInterface()
= default;

void UserInterface::run() {
    int optiune;
    while (true) {
        cout << "1. Adauga utilizator." << endl;
        cout << "2. Adauga eveniment." << endl;
        cout << "3. Creeaza chat." << endl;
        cout << "4. Trimite mesaj." << endl;
        cout << "------------------" << endl;
        cout << "5. Modifica utilizator." << endl;
        cout << "6. Modifica eveniment." << endl;
        cout << "------------------" << endl;
        cout << "7. Sterge utilizator." << endl;
        cout << "8. Sterge eveniment." << endl;
        cout << "------------------" << endl;
        cout << "9. Afiseaza utilizator." << endl;
        cout << "10. Afiseaza eveniment." << endl;
        cout << "11. Afiseaza conversatie." << endl;
        cout << "------------------" << endl;
        cout << "12. Afiseaza utilizatori." << endl;
        cout << "13. Afiseaza evenimente." << endl;
        cout << "14. Afiseaza toate conversatiile." << endl;
        cout << "15. Afiseaza conversatia dintre 2 utilizatori." << endl;
        cout << "------------------" << endl;
        cout << "16. Adauga prietenie." << endl;
        cout << "17. Sterge prietenie." << endl;
        cout << "18. Afiseaza prieteni." << endl;
        cout << "------------------" << endl;
        cout << "19. Adauga urmaritor." << endl;
        cout << "20. Sterge urmaritor." << endl;
        cout << "21. Afiseaza urmaritori." << endl;
        cout << "------------------" << endl;
        cout << "22. Participare eveniment." << endl;
        cout << "23. Sterge participare." << endl;
        cout << "24. Afiseaza participanti eveniment." << endl;
        cout << "25. Afiseaza evenimente participate." << endl;
        cout << "------------------" << endl;
        cout << "0. Iesire." << endl;
        cout << "Optiune: ";
        cin >> optiune;
        cout << endl;
        switch (optiune) {
            case 1:
                adaugaUtilizator();
                break;
            case 2:
                adaugaEveniment();
                break;
            case 3:
                creeazaChat();
                break;
            case 4:
                trimiteMesaj();
                break;
            case 5:
                modificaUtilizator();
                break;
            case 6:
                modificaEveniment();
                break;
            case 7:
                stergeUtilizator();
                break;
            case 8:
                stergeEveniment();
                break;
            case 9:
                afiseazaUtilizator();
                break;
            case 10:
                afiseazaEveniment();
                break;
            case 11:
                afiseazaChat();
                break;
            case 12:
                afiseazaUtilizatori();
                break;
            case 13:
                afiseazaEvenimente();
                break;
            case 14:
                afiseazaChats();
                break;
            case 15:
                afiseazaChatsBetween();
                break;
            case 16:
                adaugarePrietenie();
                break;
            case 17:
                stergerePrietenie();
                break;
            case 18:
                afisarePrieteni();
                break;
            case 19:
                adaugareUrmaritor();
                break;
            case 20:
                stergereUrmaritor();
                break;
            case 21:
                afisareUrmaritori();
                break;
            case 22:
                participareEveniment();
                break;
            case 23:
                stergereParticipare();
                break;
            case 24:
                afisareParticipanti();
                break;
            case 25:
                afisareEvenimenteParticipate();
                break;
            case 0:
                return;
        }
    }
}

void UserInterface::adaugaUtilizator() {
    int id, varsta;
    string nume, email, parola;

    cout << "Id: ";
    cin >> id;

    cout << "Nume: ";
    cin >> nume;

    cout << "Varsta: ";
    cin >> varsta;

    cout << "Email: ";
    cin >> email;

    cout << "Parola: ";
    cin >> parola;

    try {
        retea.adaugaUtilizator(Utilizator(id, nume, varsta, email, parola));
        cout << "Utilizatorul a fost adaugat cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::adaugaEveniment() {
    int id;;
    string nume, data, locatie;

    cout << "Id: ";
    cin >> id;

    cout << "Nume: ";
    cin >> nume;

    cout << "Data: ";
    cin >> data;

    cout << "Locatie: ";
    cin >> locatie;

    try {
        retea.adaugaEveniment(Eveniment(id, nume, data, locatie));
        cout << "Evenimentul a fost adaugat cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::creeazaChat() {
    int id, id_utilizator_1, id_utilizator_2;

    cout << "Id chat: ";
    cin >> id;

    cout << "Id utilizator 1: ";
    cin >> id_utilizator_1;

    cout << "Id utilizator 2: ";
    cin >> id_utilizator_2;

    try {
        retea.creeazaChat(Chat(id, id_utilizator_1, id_utilizator_2));
        cout << "Chat creat cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::trimiteMesaj() {
    int id_utilizator1, id_utilizator2;
    string mesaj;

    cout << "Id utilizator 1: ";
    cin >> id_utilizator1;

    cout << "Id utilizator 2: ";
    cin >> id_utilizator2;

    cout << "Mesaj: ";
    cin.ignore();
    getline(cin, mesaj);

    try {
        retea.trimiteMesaj(id_utilizator1, id_utilizator2, mesaj);
        cout << "Mesaj trimis cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::modificaUtilizator() {
    int id, varsta;
    string nume, email, parola;

    cout << "Id: ";
    cin >> id;

    cout << "Nume nou: ";
    cin >> nume;

    cout << "Varsta noua: ";
    cin >> varsta;

    cout << "Email nou: ";
    cin >> email;

    cout << "Parola noua: ";
    cin >> parola;

    try {
        retea.modificaUtilizator(id, Utilizator(id, nume, varsta, email, parola));
        cout << "Utilizatorul a fost modificat cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::modificaEveniment() {
    int id;
    string nume, data, locatie;

    cout << "Id: ";
    cin >> id;

    cout << "Nume nou: ";
    cin >> nume;

    cout << "Data noua: ";
    cin >> data;

    cout << "Locatie noua: ";
    cin >> locatie;

    try {
        retea.modificaEveniment(id, Eveniment(id, nume, data, locatie));
        cout << "Evenimentul a fost modificat cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::stergeUtilizator() {
    int id;

    cout << "Id: ";
    cin >> id;

    try {
        retea.stergeUtilizator(id);
        cout << "Utilizatorul a fost sters cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::stergeEveniment() {
    int id;

    cout << "Id: ";
    cin >> id;

    try {
        retea.stergeEveniment(id);
        cout << "Evenimentul a fost sters cu succes!" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afiseazaUtilizator() {
    int id;

    cout << "Id: ";
    cin >> id;

    try {
        Utilizator utilizator = retea.getUtilizator(id);

        cout << "Nume: " << utilizator.getNume() << ", "  << "Varsta: " << utilizator.getVarsta() << ", " << "Email: " << utilizator.getEmail() << ", " << "Parola: " << utilizator.getParola() << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afiseazaEveniment() {
    int id;

    cout << "Id: ";
    cin >> id;

    try {
        Eveniment eveniment = retea.getEveniment(id);

        cout << "Nume: " << eveniment.getNume() << ", "  << "Data: " << eveniment.getData() << ", " << "Locatie: " << eveniment.getLocatie() << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afiseazaChat() {
    int id;

    cout << "Id: ";
    cin >> id;

    try {
        Chat chat = retea.getChat(id);

        string numeUtilizator1 = retea.getUtilizator(chat.getIdUser1()).getNume();
        string numeUtilizator2 = retea.getUtilizator(chat.getIdUser2()).getNume();

        auto list = chat.getMesaje();
        cout << "Id: " << chat.getId() << "Mesaje: \n";
        for (int i = 0; i < list.getDim(); i++) {
            string numeExpeditor = retea.getUtilizator(list[i].first).getNume();
            string numeDestinatar = (numeExpeditor == numeUtilizator1 ? numeUtilizator2 : numeUtilizator1);
            cout << numeExpeditor << " - " << numeDestinatar << ": " << list[i].second << endl;
        }

    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afiseazaUtilizatori() {
    auto list = retea.getUtilizatori();

    if (list.getDim() == 0) {
        cout << "Nu exista utilizatori" << endl;
        return;
    }

    cout << "Utilizatori: \n";
    for (int i = 0; i < list.getDim(); i++) {
        cout << "Id: " << list[i].getId() << ", " << "Nume: " << list[i].getNume() << ", " << "Varsta: " << list[i].getVarsta() << ", " << "Email: " << list[i].getEmail() << ", " << "Parola: " << list[i].getParola() << endl;
    }
}

void UserInterface::afiseazaEvenimente() {
    auto list = retea.getEvenimente();

    if (list.getDim() == 0) {
        cout << "Nu exista evenimente" << endl;
        return;
    }

    cout << "Evenimente: \n";
    for (int i = 0; i < list.getDim(); i++) {
        cout << "Id: " << list[i].getId() << ", " << "Nume: " << list[i].getNume() << ", " << "Data: " << list[i].getData() << ", " << "Locatie: " << list[i].getLocatie() << endl;
    }
}

void UserInterface::afiseazaChats() {
    auto list = retea.getChats();

    if (list.getDim() == 0) {
        cout << "Nu exista chats" << endl;
        return;
    }

    cout << "Chats: \n";
    for (int i = 0; i < list.getDim(); i++) {
        string numeUtilizator1 = retea.getUtilizator(list[i].getIdUser1()).getNume();
        string numeUtilizator2 = retea.getUtilizator(list[i].getIdUser2()).getNume();

        for (int j = 0; j < list[i].getMesaje().getDim(); j++) {
            string numeExpeditor = retea.getUtilizator(list[i].getMesaje()[j].first).getNume();
            string numeDestinatar = (numeExpeditor == numeUtilizator1 ? numeUtilizator2 : numeUtilizator1);
            cout << numeExpeditor << " - " << numeDestinatar << ": " << list[i].getMesaje()[j].second << endl;
        }
    }
}

void UserInterface::afiseazaChatsBetween() {
    int id1, id2;

    cout << "Id utilizator 1: ";
    cin >> id1;

    cout << "Id utilizator 2: ";
    cin >> id2;

    try {
        Chat chat = retea.getChatBetween(id1, id2);

        cout << "Chats: \n";
        for (int i = 0; i < chat.getMesaje().getDim(); i++) {
            string numeExpeditor = retea.getUtilizator(chat.getMesaje()[i].first).getNume();
            string numeDestinatar = id1 == chat.getIdUser1() ? retea.getUtilizator(id2).getNume() : retea.getUtilizator(id1).getNume();
            cout << numeExpeditor << " - " << numeDestinatar << ": " << chat.getMesaje()[i].second << endl;
        }
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::adaugarePrietenie() {
    int id1, id2;

    cout << "Id utilizator 1: ";
    cin >> id1;

    cout << "Id utilizator 2: ";
    cin >> id2;

    try {
        retea.adaugarePrietenie(id1, id2);
        cout << "Prietenie adaugata cu succes" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::stergerePrietenie() {
    int id1, id2;

    cout << "Id utilizator 1: ";
    cin >> id1;

    cout << "Id utilizator 2: ";
    cin >> id2;

    try {
        retea.stergerePrietenie(id1, id2);
        cout << "Prietenie stearsa cu succes" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afisarePrieteni() {
    int id;

    cout << "Id utilizator: ";
    cin >> id;

    try {
        Lista<int> list = retea.getPrieteni(id);

        if (list.getDim() == 0) {
            cout << "Nu exista prieteni" << endl;
            return;
        }

        cout << "Prieteni: \n";
        for (int i = 0; i < list.getDim(); i++) {
            Utilizator u = retea.getUtilizator(list[i]);
            cout << "Id: " << u.getId() << ", " << "Nume: " << u.getNume() << ", " << "Varsta: " << u.getVarsta() << ", " << "Email: " << u.getEmail() << ", " << "Parola: " << u.getParola() << endl;
        }
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::adaugareUrmaritor() {
    int id1, id2;

    cout << "Id utilizatorului urmarit: ";
    cin >> id1;

    cout << "Id utilizator urmaritor: ";
    cin >> id2;

    try {
        retea.adaugareUrmaritor(id1, id2);
        cout << "Urmaritor adaugat cu succes" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::stergereUrmaritor() {
    int id1, id2;

    cout << "Id utilizatorului urmarit: ";
    cin >> id1;

    cout << "Id utilizator urmaritor: ";
    cin >> id2;

    try {
        retea.stergereUrmaritor(id1, id2);
        cout << "Urmaritor sters cu succes" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afisareUrmaritori() {
    int id;

    cout << "Id utilizator: ";
    cin >> id;

    try {
        Lista<int> list = retea.getUrmaritori(id);

        if (list.getDim() == 0) {
            cout << "Nu exista urmaritori" << endl;
            return;
        }

        cout << "Urmaritori: \n";
        for (int i = 0; i < list.getDim(); i++) {
            Utilizator u = retea.getUtilizator(list[i]);
            cout << "Id: " << u.getId() << ", " << "Nume: " << u.getNume() << ", " << "Varsta: " << u.getVarsta() << ", " << "Email: " << u.getEmail() << ", " << "Parola: " << u.getParola() << endl;
        }
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::participareEveniment() {
    int id1, id2;

    cout << "Id utilizator: ";
    cin >> id1;

    cout << "Id eveniment: ";
    cin >> id2;

    try {
        retea.participareEveniment(id1, id2);
        cout << "Participare inregistrata cu succes" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::stergereParticipare() {
    int id1, id2;

    cout << "Id utilizator: ";
    cin >> id1;

    cout << "Id eveniment: ";
    cin >> id2;

    try {
        retea.stergereParticipare(id1, id2);
        cout << "Participare stearsa cu succes" << endl;
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afisareParticipanti() {
    int id;

    cout << "Id eveniment: ";
    cin >> id;

    try {
        Lista<int> list = retea.getParticipanti(id);

        if (list.getDim() == 0) {
            cout << "Nu exista participanti" << endl;
            return;
        }

        cout << "Participanti: \n";
        for (int i = 0; i < list.getDim(); i++) {
            Utilizator u = retea.getUtilizator(list[i]);
            cout << "Id: " << u.getId() << ", " << "Nume: " << u.getNume() << ", " << "Varsta: " << u.getVarsta() << ", " << "Email: " << u.getEmail() << ", " << "Parola: " << u.getParola() << endl;
        }
    } catch (string msg) {
        cout << msg << endl;
    }
}

void UserInterface::afisareEvenimenteParticipate() {
    int id;

    cout << "Id utilizator: ";
    cin >> id;

    try {
        Lista<int> list = retea.getEvenimenteParticipate(id);

        if (list.getDim() == 0) {
            cout << "Nu exista evenimente participate" << endl;
            return;
        }

        cout << "Evenimente participate: \n";
        for (int i = 0; i < list.getDim(); i++) {
            Eveniment e = retea.getEveniment(list[i]);
            cout << "Id: " << e.getId() << ", " << "Nume: " << e.getNume() << ", " << "Data: " << e.getData() << ", " << "Locatie: " << e.getLocatie() << endl;
        }
    } catch (string msg) {
        cout << msg << endl;
    }
}

