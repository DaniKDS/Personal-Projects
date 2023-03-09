#ifndef CHAT_H
#define CHAT_H

#include <string>
#include "Lista.h"
using namespace std;

class Chat {
public:
    Chat();
    Chat(int id, int id_user1, int id_user2);
    ~Chat();

    int getId() const;
    int getIdUser1() const;
    int getIdUser2() const;
    Lista<pair<int, string>> getMesaje() const;

    void setId(int id);
    void setIdUser1(int id_user1);
    void setIdUser2(int id_user2);
    void addMesaj(int id_user_trimitor, string mesaj);

    friend ostream& operator<<(ostream& out, Chat& c);
    friend istream& operator>>(istream& in, Chat& c);

private:
    int id{};
    int id_user1{};
    int id_user2{};
    Lista<pair<int, string>> mesaje;
};

#endif // CHAT_H
