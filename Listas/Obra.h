#ifndef OBRAS_H
#define OBRAS_H
#include <iostream>
#include <string>
#include "Edicion.h"
#include "Lista.h"

using namespace std;

class Obra
{
private:
    int idAutor;
    string titulo;
    string tipo;
    Lista<Edicion> ediciones;

public:
    Obra(int idAutor, string titulo, string tipo)
    {
        this->idAutor = idAutor;
        this->titulo = titulo;
        this->tipo = tipo;
    }

    int getIdAutor() { return idAutor; }
    string getTitulo() { return titulo; }
    string getTipo() { return tipo; }
    Lista<Edicion>& getEdiciones() { return ediciones; }

    void setIdAutor(int idAutor) { this->idAutor = idAutor; }
    void setTitulo(string titulo) { this->titulo = titulo; }
    void setTipo(string tipo) { this->tipo = tipo; }
    void agregarEdicion(Edicion edicion)
    {
        ediciones.insertarFinal(edicion);
    }
    void eliminarEdicion(int pos)
    {
        ediciones.borrarPos(pos);
    }
};

#endif