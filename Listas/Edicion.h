#ifndef EDICION_H
#define EDICION_H
#include <iostream>
#include <string>

using namespace std;

class Edicion
{
private:
    int numero;
    int idEditorial;
    string fechaPublicacion;
    string ciudad;

public:
    Edicion(int numero, string fechaPublicacion, int idEditorial, string ciudad)
    {
        this->numero = numero;
        this->fechaPublicacion = fechaPublicacion;
        this->idEditorial = idEditorial;
        this->ciudad = ciudad;
    }

    int getNumero() { return numero; }
    string getFechaPublicacion() { return fechaPublicacion; }
    int getIdEditorial() { return idEditorial; }
    string getCiudad() { return ciudad; }

    void setNumero(int numero) { this->numero = numero; }
    void setFechaPublicacion(string fechaPublicacion) { this->fechaPublicacion = fechaPublicacion; }
    void setIdEditorial(int idEditorial) { this->idEditorial = idEditorial; }
    void setCiudad(string ciudad) { this->ciudad = ciudad; }
};

#endif