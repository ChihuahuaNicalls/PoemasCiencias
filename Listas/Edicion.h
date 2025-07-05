#ifndef EDICION_H
#define EDICION_H
#include <iostream>
#include <string>
#include "Fecha.h"

using namespace std;

class Edicion
{
private:
    int numero;
    int idEditorial;
    int idAutor;
    Fecha fechaPublicacion;
    string ciudad;
    string nombreObra;

public:
    Edicion(int numero, Fecha fechaPublicacion, int idEditorial, int idAutor, string ciudad, string nombreObra)
        : numero(numero),
          fechaPublicacion(fechaPublicacion),
          idEditorial(idEditorial),
          idAutor(idAutor),
          ciudad(ciudad),
          nombreObra(nombreObra)
    {
    }

    int getNumero() const { return numero; }
    Fecha getFechaPublicacion() const { return fechaPublicacion; }
    int getIdEditorial() const { return idEditorial; }
    int getIdAutor() const { return idAutor; }
    string getCiudad() const { return ciudad; }
    string getNombreObra() const { return nombreObra; }

    void setNumero(int numero) { this->numero = numero; }
    void setFechaPublicacion(Fecha fechaPublicacion) { this->fechaPublicacion = fechaPublicacion; }
    void setIdEditorial(int idEditorial) { this->idEditorial = idEditorial; }
    void setIdAutor(int idAutor) { this->idAutor = idAutor; }
    void setCiudad(string ciudad) { this->ciudad = ciudad; }
    void setNombreObra(string nombreObra) { this->nombreObra = nombreObra; }
};

#endif