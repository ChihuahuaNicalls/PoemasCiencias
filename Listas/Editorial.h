#ifndef EDITORIAL_H
#define EDITORIAL_H
#include <iostream>
#include <string>

using namespace std;

class Editorial
{
private:
    int id;
    string nombre;
    string ciudad;
    string pais;

public:
    Editorial(int id, string nombre, string ciudad, string pais)
    {
        this->id = id;
        this->nombre = nombre;
        this->ciudad = ciudad;
        this->pais = pais;
    }

    int getId() { return id; }
    string getNombre() { return nombre; }
    string getCiudad() { return ciudad; }
    string getPais() { return pais; }

    void setId(int id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setCiudad(string ciudad) { this->ciudad = ciudad; }
    void setPais(string pais) { this->pais = pais; }
};

#endif