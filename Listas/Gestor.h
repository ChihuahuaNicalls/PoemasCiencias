#ifndef GESTOR_H
#define GESTOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Lista.h"
#include "Autor.h"
#include "Editorial.h"
#include "Edicion.h"
#include "Obra.h"
#include "Obra.h"

using namespace std;

class Gestor
{
private:
    Lista<Autor> autores;
    Lista<Editorial> editoriales;
    Lista<Obra> obras;

public:
    void cargarDatos();
    void guardarDatos();

    void menu();

    // Consultas
    void consulta1_obrasPorAutor();
    void consulta2_nombresObrasPorTipo();
    void consulta3_autoresPorEditorial();
    void consulta4_editorialesPorPoetas(int umbral);
    void consulta5_generoPorEditorial();
    void consulta6_autoresPorEdadYFormacion(int edadMin, int edadMax, string formacion);
    void consulta7_autoresPorPoesiaYEditorial(string tipo, int idEditorial);

    // Helpers
    Autor *buscarAutorPorId(int id);
    Editorial *buscarEditorialPorId(int id);
    void ordenarObrasPorEditorialYFecha(vector<Edicion> &ediciones);

    // Binaria sobre autores (ordenado por ID)
    Autor *busquedaBinariaAutor(int id);
    Editorial *busquedaBinariaEditorial(int id);

    // CRUD Básico
    void agregarAutor(const Autor &autor);
    void agregarEditorial(const Editorial &editorial);
    void agregarObra(const Obra &obra);
    void agregarEdicion(const Edicion &edicion);
    void ordenarAutoresPorId();
    void ordenarEditorialesPorId();

    void listarAutores();
    void listarEditoriales();
    void listarObras();
};

void Gestor::cargarDatos()
{
    ifstream fa("autores.txt");
    if (fa.is_open())
    {
        string linea;
        while (getline(fa, linea))
        {
            stringstream ss(linea);
            int id, inicio, primera;
            string nombre, apellido, sexo, fNacStr, cNac, pNac, cRes, formacion;
            getline(ss, nombre, ';');
            getline(ss, apellido, ';');
            getline(ss, sexo, ';');
            getline(ss, fNacStr, ';');
            getline(ss, cNac, ';');
            getline(ss, pNac, ';');
            getline(ss, cRes, ';');
            getline(ss, formacion, ';');
            ss >> id;
            ss.ignore();
            ss >> inicio;
            ss.ignore();
            ss >> primera;
            Fecha fNac(fNacStr);
            autores.insertarFinal(Autor(id, nombre, apellido, sexo, fNac, cNac, pNac, cRes, formacion, inicio, primera));
        }
        fa.close();
    }

    ifstream fe("editoriales.txt");
    if (fe.is_open())
    {
        string linea;
        while (getline(fe, linea))
        {
            stringstream ss(linea);
            string id, nombre, ciudad, pais;
            getline(ss, id, ';');
            getline(ss, nombre, ';');
            getline(ss, ciudad, ';');
            getline(ss, pais);
            editoriales.insertarFinal(Editorial(stoi(id), nombre, ciudad, pais));
        }
        fe.close();
    }

    ifstream fo("obras.txt");
    if (fo.is_open())
    {
        string linea;
        while (getline(fo, linea))
        {
            stringstream ss(linea);
            string nombre, tipo;
            int idAutor;
            getline(ss, nombre, ';');
            getline(ss, tipo, ';');
            ss >> idAutor;
            obras.insertarFinal(Obra(idAutor, nombre, tipo));
        }
        fo.close();
    }

    ifstream fed("ediciones.txt");
    if (fed.is_open())
    {
        string linea;
        while (getline(fed, linea))
        {
            stringstream ss(linea);
            string nombreObra, fechaStr, ciudad, idEditorialStr;
            int numero, idEditorial;
            getline(ss, nombreObra, ';');
            ss >> numero;
            ss.ignore();
            getline(ss, fechaStr, ';');
            getline(ss, idEditorialStr, ';');
            getline(ss, ciudad);
            Fecha fecha(fechaStr);
            idEditorial = stoi(idEditorialStr);
            for (int i = 0; i < obras.getNumElem(); ++i)
            {
                if (obras.obtener(i).getTitulo() == nombreObra)
                {
                    Edicion e(numero, fecha, idEditorial, obras.obtener(i).getIdAutor(), ciudad, nombreObra);
                    obras.obtener(i).getEdiciones().insertarFinal(e);
                    break;
                }
            }
        }
        fed.close();
    }

    ordenarAutoresPorId();
    ordenarEditorialesPorId();
}

void Gestor::guardarDatos()
{
    ofstream fa("autores.txt");
    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        Autor &a = autores.obtener(i);
        fa << a.getNombre() << ';' << a.getApellido() << ';' << a.getSexo() << ';'
           << a.getFechaNacimiento().toString() << ';' << a.getCiudadNacimiento() << ';'
           << a.getPaisNacimiento() << ';' << a.getCiudadResidencia() << ';'
           << a.getFormacionAcademica() << ';' << a.getId() << ';'
           << a.getYearInicioLiteratura() << ';' << a.getYearPublicacionPrimeraObra() << '\n';
    }
    fa.close();

    ofstream fe("editoriales.txt");
    for (int i = 0; i < editoriales.getNumElem(); ++i)
    {
        Editorial &e = editoriales.obtener(i);
        fe << e.getId() << ';' << e.getNombre() << ';' << e.getCiudad() << ';' << e.getPais() << '\n';
    }
    fe.close();

    ofstream fo("obras.txt");
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        Obra &o = obras.obtener(i);
        fo << o.getTitulo() << ';' << o.getTipoPoesia() << ';' << o.getIdAutor() << '\n';
    }
    fo.close();

    ofstream fed("ediciones.txt");
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        Obra &o = obras.obtener(i);
        for (int j = 0; j < o.getEdiciones().getNumElem(); ++j)
        {
            Edicion &e = o.getEdiciones().obtener(j);
            fed << o.getTitulo() << ';' << e.getNumero() << ';'
                << e.getFechaPublicacion().toString() << ';'
                << e.getIdEditorial() << ';' << e.getCiudad() << '\n';
        }
    }
    fed.close();
}

void Gestor::ordenarAutoresPorId()
{
    for (int i = 0; i < autores.getNumElem() - 1; ++i)
    {
        for (int j = i + 1; j < autores.getNumElem(); ++j)
        {
            if (autores.obtener(i).getId() > autores.obtener(j).getId())
            {
                Autor temp = autores.obtener(i);
                autores.modificarPos(autores.obtener(j), i);
                autores.modificarPos(temp, j);
            }
        }
    }
}

Editorial* Gestor::buscarEditorialPorId(int id) {
    return busquedaBinariaEditorial(id);
}

void Gestor::ordenarEditorialesPorId()
{
    for (int i = 0; i < editoriales.getNumElem() - 1; ++i)
    {
        for (int j = i + 1; j < editoriales.getNumElem(); ++j)
        {
            if (editoriales.obtener(i).getId() > editoriales.obtener(j).getId())
            {
                Editorial temp = editoriales.obtener(i);
                editoriales.modificarPos(editoriales.obtener(j), i);
                editoriales.modificarPos(temp, j);
            }
        }
    }
}

Autor *Gestor::busquedaBinariaAutor(int id)
{
    int inicio = 0, fin = autores.getNumElem() - 1;
    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;
        int actual = autores.obtener(medio).getId();
        if (actual == id)
            return &autores.obtener(medio);
        else if (actual < id)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }
    return nullptr;
}

Editorial *Gestor::busquedaBinariaEditorial(int id)
{
    int inicio = 0, fin = editoriales.getNumElem() - 1;
    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;
        int actual = editoriales.obtener(medio).getId();
        if (actual == id)
            return &editoriales.obtener(medio);
        else if (actual < id)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }
    return nullptr;
}

Autor *Gestor::buscarAutorPorId(int id)
{
    return busquedaBinariaAutor(id);
}


// ----------------------------- CRUD -----------------------------

void Gestor::agregarAutor(const Autor &autor)
{
    autores.insertarFinal(autor);
    ordenarAutoresPorId();
}

void Gestor::agregarEditorial(const Editorial &editorial)
{
    editoriales.insertarFinal(editorial);
    ordenarEditorialesPorId();
}

void Gestor::agregarObra(const Obra &obra)
{
    obras.insertarFinal(obra);
}

void Gestor::agregarEdicion(const Edicion &ed)
{
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getTitulo() == ed.getNombreObra())
        {
            obras.obtener(i).getEdiciones().insertarFinal(ed);
            break;
        }
    }
}

void Gestor::listarAutores()
{
    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        Autor &a = autores.obtener(i);
        cout << a.getId() << " - " << a.getNombre() << " " << a.getApellido() << endl;
    }
}

void Gestor::listarEditoriales()
{
    for (int i = 0; i < editoriales.getNumElem(); ++i)
    {
        Editorial &e = editoriales.obtener(i);
        cout << e.getId() << " - " << e.getNombre() << endl;
    }
}

void Gestor::listarObras()
{
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        Obra &o = obras.obtener(i);
        cout << o.getTitulo() << " - " << o.getTipoPoesia() << endl;
    }
}


// ----------------------------- CONSULTAS -----------------------------

void Gestor::consulta1_obrasPorAutor()
{
    int id;
    cout << "ID del autor: ";
    cin >> id;
    Autor *autor = buscarAutorPorId(id);
    if (!autor)
    {
        cout << "Autor no encontrado.\n";
        return;
    }
    cout << "Obras por editorial y año de publicacion:\n";
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getIdAutor() == id)
        {
            for (int j = 0; j < obras.obtener(i).getEdiciones().getNumElem(); ++j)
            {
                Edicion &ed = obras.obtener(i).getEdiciones().obtener(j);
                Editorial *e = buscarEditorialPorId(ed.getIdEditorial());
                cout << obras.obtener(i).getTitulo() << " - "
                     << e->getNombre() << " - "
                     << ed.getFechaPublicacion().getYear() << endl;
            }
        }
    }
}

void Gestor::consulta2_nombresObrasPorTipo()
{
    int id;
    cout << "ID del autor: ";
    cin >> id;
    Autor *autor = buscarAutorPorId(id);
    if (!autor)
    {
        cout << "Autor no encontrado.\n";
        return;
    }
    cout << "Obras del autor por tipo de poesía:\n";
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getIdAutor() == id)
        {
            cout << "Tipo: " << obras.obtener(i).getTipoPoesia() << endl;
            for (int j = 0; j < obras.obtener(i).getEdiciones().getNumElem(); ++j)
            {
                Edicion &ed = obras.obtener(i).getEdiciones().obtener(j);
                cout << "\t" << obras.obtener(i).getTitulo() << " - Edición " << ed.getNumero()
                     << " - Publicada en: " << ed.getFechaPublicacion().toString() << endl;
            }
        }
    }
}

void Gestor::consulta3_autoresPorEditorial()
{
    string idEd;
    cout << "ID de la editorial: ";
    cin >> idEd;
    int id = stoi(idEd);

    Editorial *editorial = buscarEditorialPorId(id);
    if (!editorial)
    {
        cout << "Editorial no encontrada.\n";
        return;
    }

    cout << "Autores publicados por la editorial " << editorial->getNombre() << "\n";

    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        int idAutor = autores.obtener(i).getId();
        bool publicado = false;
        for (int j = 0; j < obras.getNumElem(); ++j)
        {
            if (obras.obtener(j).getIdAutor() == idAutor)
            {
                for (int k = 0; k < obras.obtener(j).getEdiciones().getNumElem(); ++k)
                {
                    if (obras.obtener(j).getEdiciones().obtener(k).getIdEditorial() == id)
                    {
                        publicado = true;
                        break;
                    }
                }
            }
        }
        if (publicado)
        {
            Autor &a = autores.obtener(i);
            cout << a.getNombre() << " " << a.getApellido() << " - Nacido en: "
                 << a.getCiudadNacimiento() << ", " << a.getPaisNacimiento()
                 << " - Reside en: " << a.getCiudadResidencia()
                 << " - Año inicio: " << a.getYearInicioLiteratura() << endl;
        }
    }
}

void Gestor::consulta4_editorialesPorPoetas(int umbral) {
    cout << "Editoriales con al menos " << umbral << " poetas:\n";
    for (int i = 0; i < editoriales.getNumElem(); ++i) {
        Editorial &e = editoriales.obtener(i);
        vector<int> autoresPublicados;

        for (int j = 0; j < obras.getNumElem(); ++j) {
            Obra &o = obras.obtener(j);
            for (int k = 0; k < o.getEdiciones().getNumElem(); ++k) {
                if (o.getEdiciones().obtener(k).getIdEditorial() == e.getId()) {
                    if (find(autoresPublicados.begin(), autoresPublicados.end(), o.getIdAutor()) == autoresPublicados.end()) {
                        autoresPublicados.push_back(o.getIdAutor());
                    }
                }
            }
        }

        if ((int)autoresPublicados.size() >= umbral) {
            cout << "- " << e.getNombre() << " (" << autoresPublicados.size() << " poetas)\n";
        }
    }
}

void Gestor::consulta5_generoPorEditorial() {
    cout << "Distribución por género de autores por editorial:\n";
    for (int i = 0; i < editoriales.getNumElem(); ++i) {
        Editorial &e = editoriales.obtener(i);
        vector<int> idsAutores;
        for (int j = 0; j < obras.getNumElem(); ++j) {
            Obra &o = obras.obtener(j);
            for (int k = 0; k < o.getEdiciones().getNumElem(); ++k) {
                if (o.getEdiciones().obtener(k).getIdEditorial() == e.getId()) {
                    if (find(idsAutores.begin(), idsAutores.end(), o.getIdAutor()) == idsAutores.end()) {
                        idsAutores.push_back(o.getIdAutor());
                    }
                }
            }
        }

        int hombres = 0, mujeres = 0;
        for (int idAutor : idsAutores) {
            Autor *a = buscarAutorPorId(idAutor);
            if (a) {
                if (a->getSexo() == "M") hombres++;
                else if (a->getSexo() == "F") mujeres++;
            }
        }

        cout << "- " << e.getNombre() << ": Hombres = " << hombres << ", Mujeres = " << mujeres << '\n';
    }
}

void Gestor::consulta6_autoresPorEdadYFormacion(int edadMin, int edadMax, string formacion) {
    cout << "Autores con formación '" << formacion << "' y edad entre " << edadMin << " y " << edadMax << ":\n";

    for (int i = 0; i < autores.getNumElem(); ++i) {
        Autor &a = autores.obtener(i);
        int edad = a.calcularEdad();
        if (edad >= edadMin && edad <= edadMax && a.getFormacionAcademica() == formacion) {
            cout << a.getNombre() << " " << a.getApellido()
                 << " - Edad: " << edad
                 << " - Formación: " << a.getFormacionAcademica() << '\n';
        }
    }
}

void Gestor::consulta7_autoresPorPoesiaYEditorial(string tipo, int idEditorial) {
    cout << "Autores que escriben poesía tipo '" << tipo << "' y han publicado con la editorial ID " << idEditorial << ":\n";

    vector<int> autoresFiltrados;

    for (int i = 0; i < obras.getNumElem(); ++i) {
        Obra &o = obras.obtener(i);
        if (o.getTipoPoesia() == tipo) {
            for (int j = 0; j < o.getEdiciones().getNumElem(); ++j) {
                if (o.getEdiciones().obtener(j).getIdEditorial() == idEditorial) {
                    if (find(autoresFiltrados.begin(), autoresFiltrados.end(), o.getIdAutor()) == autoresFiltrados.end()) {
                        autoresFiltrados.push_back(o.getIdAutor());
                    }
                }
            }
        }
    }

    for (int idAutor : autoresFiltrados) {
        Autor *a = buscarAutorPorId(idAutor);
        if (a) {
            cout << "- " << a->getNombre() << " " << a->getApellido() << '\n';
        }
    }
}


// ----------------------------- MENÚ -----------------------------

void Gestor::menu()
{
    int opcion;
    do
    {
        cout << "\n--- MENÚ PRINCIPAL ---\n";
        cout << "1. Gestión de datos\n";
        cout << "2. Consultas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
            int subop;
            cout << "\n--- Gestión de datos ---\n";
            cout << "1. Listar autores\n";
            cout << "2. Listar editoriales\n";
            cout << "3. Listar obras\n";
            cout << "Seleccione una opción: ";
            cin >> subop;
            switch (subop)
            {
            case 1:
                listarAutores();
                break;
            case 2:
                listarEditoriales();
                break;
            case 3:
                listarObras();
                break;
            default:
                cout << "Opción inválida.\n";
                break;
            }
            break;
        }
        case 2:
        {
            int subop;
            cout << "\n--- Consultas ---\n";
            cout << "1. Consulta 1: Obras por autor\n";
            cout << "2. Consulta 2: Nombres de obras por tipo de poesía\n";
            cout << "3. Consulta 3: Autores por editorial\n";
            cout << "4. Consulta 4: Editoriales con más de N poetas\n";
            cout << "5. Consulta 5: Género por editorial\n";
            cout << "6. Consulta 6: Autores por edad y formación\n";
            cout << "7. Consulta 7: Autores por tipo de poesía y editorial\n";
            cout << "Seleccione una opción: ";
            cin >> subop;
            switch (subop)
            {
            case 1:
                consulta1_obrasPorAutor();
                break;
            case 2:
                consulta2_nombresObrasPorTipo();
                break;
            case 3:
                consulta3_autoresPorEditorial();
                break;
            case 4:
            {
                int umbral;
                cout << "Ingrese el número mínimo de poetas: ";
                cin >> umbral;
                consulta4_editorialesPorPoetas(umbral);
                break;
            }
            case 5:
                consulta5_generoPorEditorial();
                break;
            case 6:
            {
                int min, max;
                string form;
                cout << "Edad mínima: ";
                cin >> min;
                cout << "Edad máxima: ";
                cin >> max;
                cout << "Formación: ";
                cin.ignore();
                getline(cin, form);
                consulta6_autoresPorEdadYFormacion(min, max, form);
                break;
            }
            case 7:
            {
                string tipo;
                int idEd;
                cout << "Tipo de poesía: ";
                cin.ignore();
                getline(cin, tipo);
                cout << "ID de editorial: ";
                cin >> idEd;
                consulta7_autoresPorPoesiaYEditorial(tipo, idEd);
                break;
            }
            default:
                cout << "Opción inválida.\n";
                break;
            }
            break;
        }
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 0);
}

#endif