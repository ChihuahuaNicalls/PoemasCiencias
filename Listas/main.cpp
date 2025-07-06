#include <iostream>
#include "Gestor.h"

int main() {
    Gestor gestor;
    try {
        gestor.cargarDatos();
        gestor.menu();
    } catch (const exception& e) {
        cerr << "Error al iniciar el programa: " << e.what() << endl;
    }
    system("PAUSE");
    return 0;
}
