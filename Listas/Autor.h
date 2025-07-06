#ifndef AUTOR_H
#define AUTOR_H
#include <iostream>
#include <string>
#include "Fecha.h"

using namespace std;

class Autor
{
private:
    int id;
    string nombre;
    string apellido;
    string sexo;
    Fecha fechaNacimiento;
    string ciudadNacimiento;
    string paisNacimiento;
    string ciudadResidencia;
    string formacionAcademica;
    int yearInicioLiteratura;
    int yearPublicacionPrimeraObra;

public:
    Autor(int id, string nombre, string apellido, string sexo, Fecha fechaNacimiento, string ciudadNacimiento, string paisNacimiento, string ciudadResidencia, string formacionAcademica, int yearInicioLiteratura, int yearPublicacionPrimeraObra)
    {
        this->id = id;
        this->nombre = nombre;
        this->apellido = apellido;
        this->sexo = sexo;
        this->fechaNacimiento = fechaNacimiento;
        this->ciudadNacimiento = ciudadNacimiento;
        this->paisNacimiento = paisNacimiento;
        this->ciudadResidencia = ciudadResidencia;
        this->formacionAcademica = formacionAcademica;
        this->yearInicioLiteratura = yearInicioLiteratura;
        this->yearPublicacionPrimeraObra = yearPublicacionPrimeraObra;
    }

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getSexo() const { return sexo; }
    Fecha getFechaNacimiento() const { return fechaNacimiento; }
    string getCiudadNacimiento() const { return ciudadNacimiento; }
    string getPaisNacimiento() const { return paisNacimiento; }
    string getCiudadResidencia() const { return ciudadResidencia; }
    string getFormacionAcademica() const { return formacionAcademica; }
    int getYearInicioLiteratura() const { return yearInicioLiteratura; }
    int getYearPublicacionPrimeraObra() const { return yearPublicacionPrimeraObra; }
    int calcularEdad() const{ return fechaNacimiento.calcularEdad(); }

    void setId(int id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setApellido(string apellido) { this->apellido = apellido; }
    void setSexo(string sexo) { this->sexo = sexo; }
    void setFechaNacimiento(Fecha fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
    void setCiudadNacimiento(string ciudadNacimiento) { this->ciudadNacimiento = ciudadNacimiento; }
    void setPaisNacimiento(string paisNacimiento) { this->paisNacimiento = paisNacimiento; }
    void setCiudadResidencia(string ciudadResidencia) { this->ciudadResidencia = ciudadResidencia; }
    void setFormacionAcademica(string formacionAcademica) { this->formacionAcademica = formacionAcademica; }
    void setYearInicioLiteratura(int yearInicioLiteratura) { this->yearInicioLiteratura = yearInicioLiteratura; }
    void setYearPublicacionPrimeraObra(int yearPublicacionPrimeraObra) { this->yearPublicacionPrimeraObra = yearPublicacionPrimeraObra; }
};

#endif