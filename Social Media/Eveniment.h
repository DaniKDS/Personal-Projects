#ifndef EVENIMENT_H
#define EVENIMENT_H

#include <string>
#include "Lista.h"
using namespace std;

class Eveniment {
public:
    Eveniment();
    Eveniment(int id, string nume, string data, string locatie);
    ~Eveniment();

    int getId() const;
    string getNume() const;
    string getData() const;
    string getLocatie() const;
    Lista<int> getParticipanti() const;

    void setId(int id);
    void setNume(string nume);
    void setData(string data);
    void setLocatie(string locatie);

    void addParticipant(int id);
    void removeParticipant(int id);

    friend ostream& operator<<(ostream& out, Eveniment& e);
    friend istream& operator>>(istream& in, Eveniment& e);

    bool operator<(const Eveniment& e);
    bool operator>(const Eveniment& e);

private:
    int id{};
    string nume;
    string data;
    string locatie;
    Lista<int> participanti;
};

#endif // EVENIMENT_H
