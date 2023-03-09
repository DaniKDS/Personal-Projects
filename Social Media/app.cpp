#include "UI.h"
#include "Utilizator.h"

int main() {
    
    Retea retea("utilizatori.txt", "evenimente.txt");
    UserInterface ui(retea);
    ui.run();
    return 0;
}