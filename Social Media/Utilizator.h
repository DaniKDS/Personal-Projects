#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <string>
#include "Lista.h"

using namespace std;

class Utilizator {
public:
    Utilizator();
    Utilizator(int id, string nume, int varsta, string email, string parola);
    ~Utilizator();

    int getId() const;
    string getNume() const;
    int getVarsta() const;
    string getEmail() const;
    string getParola() const;
    Lista<int> getFollowing() const;
    Lista<int> getFollowers() const;
    Lista<int> getPrieteni() const;
    Lista<int> getEvenimente() const;

    void setId(int id);
    void setNume(string nume);
    void setVarsta(int varsta);
    void setEmail(string email);
    void setParola(string parola);

    void addFollowing(int id);
    void addFollower(int id);
    void addPrieten(int id);
    void addEveniment(int id);

    void removeFollowing(int id);
    void removeFollower(int id);
    void removePrieten(int id);
    void removeEveniment(int id);

    friend ostream& operator<<(ostream& out, Utilizator& u);
    friend istream& operator>>(istream& in, Utilizator& u);

    bool operator<(const Utilizator& u);
    bool operator>(const Utilizator& u);

    bool operator==(const Utilizator& u);

private:
    int id;
    string nume;
    int varsta;
    string email;
    string parola;
    Lista<int> following;
    Lista<int> followers;
    Lista<int> prieteni;
    Lista<int> evenimente;
};

#endif // UTILIZATOR_H
