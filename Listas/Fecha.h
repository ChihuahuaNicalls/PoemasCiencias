#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <stdexcept>
using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int year;

public:
    Fecha() : dia(1), mes(1), year(2000) {}
    
    Fecha(int dia, int mes, int year) : dia(dia), mes(mes), year(year) {
        validarFecha();
    }
    
    Fecha(const string& fechaString) {
        // YYYY-MM-DD
        if (fechaString.length() != 10 || fechaString[4] != '-' || fechaString[7] != '-') {
            throw invalid_argument("Formato de fecha invalido");
        }
        
        year = stoi(fechaString.substr(0, 4));
        mes = stoi(fechaString.substr(5, 2));
        dia = stoi(fechaString.substr(8, 2));
        validarFecha();
    }
    
    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getYear() const { return year; }
    
    void setDia(int dia) { this->dia = dia; validarFecha(); }
    void setMes(int mes) { this->mes = mes; validarFecha(); }
    void setYear(int year) { this->year = year; }
    
    string toString() const {
        return to_string(year) + "-" + 
               (mes < 10 ? "0" : "") + to_string(mes) + "-" + 
               (dia < 10 ? "0" : "") + to_string(dia);
    }
    
    int calcularEdad() const {
        int edad = 2025 - year;
        if (mes > 1 || (mes == 1 && dia > 1)) {
            edad--;
        }
        return edad;
    }

private:
    void validarFecha() {
        if (year < 0 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
            throw invalid_argument("Fecha invalida");
        }
    }
};

#endif