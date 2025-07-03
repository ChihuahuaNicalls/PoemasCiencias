#ifndef AUTOR_H
#define AUTOR_H
#include <iostream>
#include <string>

using namespace std;

class Autor
{
private:
    int id;
    string nombre;
    string apellido;
    string sexo;
    string fechaNacimiento;
    string ciudadNacimiento;
    string paisNacimiento;
    string ciudadResidencia;
    string formacionAcademica;
    string yearInicioLiteratura;
    string yearPublicacionPrimeraObra;

public:
    Autor(int id, string nombre, string apellido, string sexo, string fechaNacimiento, string ciudadNacimiento, string paisNacimiento, string ciudadResidencia, string formacionAcademica, string yearInicioLiteratura, string yearPublicacionPrimeraObra)
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

    int getId() { return id; }
    string getNombre() { return nombre; }
    string getApellido() { return apellido; }
    string getSexo() { return sexo; }
    string getFechaNacimiento() { return fechaNacimiento; }
    string getCiudadNacimiento() { return ciudadNacimiento; }
    string getPaisNacimiento() { return paisNacimiento; }
    string getCiudadResidencia() { return ciudadResidencia; }
    string getFormacionAcademica() { return formacionAcademica; }
    string getYearInicioLiteratura() { return yearInicioLiteratura; }
    string getYearPublicacionPrimeraObra() { return yearPublicacionPrimeraObra; }

    void setId(int id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setApellido(string apellido) { this->apellido = apellido; }
    void setSexo(string sexo) { this->sexo = sexo; }
    void setFechaNacimiento(string fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
    void setCiudadNacimiento(string ciudadNacimiento) { this->ciudadNacimiento = ciudadNacimiento; }
    void setPaisNacimiento(string paisNacimiento) { this->paisNacimiento = paisNacimiento; }
    void setCiudadResidencia(string ciudadResidencia) { this->ciudadResidencia = ciudadResidencia; }
    void setFormacionAcademica(string formacionAcademica) { this->formacionAcademica = formacionAcademica; }
    void setYearInicioLiteratura(string yearInicioLiteratura) { this->yearInicioLiteratura = yearInicioLiteratura; }
    void setYearPublicacionPrimeraObra(string yearPublicacionPrimeraObra) { this->yearPublicacionPrimeraObra = yearPublicacionPrimeraObra; }
};

#endif