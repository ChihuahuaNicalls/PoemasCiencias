#ifndef GESTOR_H
#define GESTOR_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Lista.h"
#include "Autor.h"
#include "Editorial.h"
#include "Edicion.h"
#include "Obra.h"
#include "Fecha.h"

using namespace std;

string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c)
              { return tolower(c); });
    return s;
}

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
    void obrasPorAutor();
    void nombresObrasPorTipo();
    void autoresPorEditorial();
    void editorialesPorPoetas(int umbral);
    void generoPorEditorial();
    void autoresPorEdadYFormacion(int edadMin, int edadMax, string formacion);
    void autoresPorPoesiaYEditorial(string tipo, int idEditorial);

    // Busqueda binaria
    Autor *busquedaBinariaAutor(const string &apellido);
    Editorial *busquedaBinariaEditorial(const string &nombre);

    // Gestion
    void agregarAutor(const Autor &autor);
    void agregarEditorial(const Editorial &editorial);
    void agregarObra(const Obra &obra);
    void agregarEdicion(const Edicion &edicion);
    bool eliminarAutor(const string &apellido);
    bool eliminarEditorial(const string &nombre);
    bool eliminarObra(const string &titulo);
    bool eliminarEdicion(const string &titulo, int numero);
    bool modificarAutor(const string &apellido, const Autor &nuevo);
    bool modificarEditorial(int id, const Editorial &nueva);
    bool modificarObra(const string &titulo, const Obra &nueva);
    bool modificarEdicion(const string &titulo, int numero, const Edicion &nueva);

    // Listas
    void listaAutores();
    void listaEditoriales();
    void listaObras();
    void listaEdiciones();
};

void Gestor::cargarDatos()
{
    // Cargar autores verificando id
    ifstream fa("autores.txt");
    if (fa.is_open())
    {
        string linea;
        while (getline(fa, linea))
        {
            stringstream ss(linea);
            int id, fechaInicio, fechaPrimeraObra;
            string nombre, apellido, sexo, fechaNacStr, ciudadNac, pais, ciudadRes, formacion;
            getline(ss, nombre, ';');
            getline(ss, apellido, ';');
            getline(ss, sexo, ';');
            getline(ss, fechaNacStr, ';');
            getline(ss, ciudadNac, ';');
            getline(ss, pais, ';');
            getline(ss, ciudadRes, ';');
            getline(ss, formacion, ';');
            ss >> id;
            ss.ignore();
            ss >> fechaInicio;
            ss.ignore();
            ss >> fechaPrimeraObra;
            Fecha fechaNac(fechaNacStr);
            agregarAutor(Autor(id, nombre, apellido, sexo, fechaNac, ciudadNac, pais, ciudadRes, formacion, fechaInicio, fechaPrimeraObra));
        }
        fa.close();
    }

    // Cargar editoriales verificando id
    ifstream fe("editoriales.txt");
    if (fe.is_open())
    {
        string linea;
        while (getline(fe, linea))
        {
            stringstream ss(linea);
            string idStr, nombre, ciudadNac, pais;
            getline(ss, idStr, ';');
            getline(ss, nombre, ';');
            getline(ss, ciudadNac, ';');
            getline(ss, pais);

            int id = stoi(idStr);

            // Verificar si el ID ya existe
            bool idDuplicado = false;
            for (int i = 0; i < editoriales.getNumElem(); ++i)
            {
                if (editoriales.obtener(i).getId() == id)
                {
                    cout << "Id duplicado: " << id << endl;
                    idDuplicado = true;
                    break;
                }
            }

            if (!idDuplicado)
            {
                editoriales.insertarFinal(Editorial(id, nombre, ciudadNac, pais));
            }
        }
        fe.close();
    }

    // Cargar obras verificando titulo
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

            bool tituloDuplicado = false;
            for (int i = 0; i < obras.getNumElem(); ++i)
            {
                if (obras.obtener(i).getTitulo() == nombre)
                {
                    cout << "Titulo duplicado: " << nombre << endl;
                    tituloDuplicado = true;
                    break;
                }
            }

            if (!tituloDuplicado)
            {
                obras.insertarFinal(Obra(idAutor, nombre, tipo));
            }
        }
        fo.close();
    }

    // Cargar ediciones verificando numero
    ifstream fed("ediciones.txt");
    if (fed.is_open())
    {
        string linea;
        while (getline(fed, linea))
        {
            stringstream ss(linea);
            string nombreObra, fechaStr, ciudadNac, idEditorialStr;
            int numero, idEditorial;
            getline(ss, nombreObra, ';');
            ss >> numero;
            ss.ignore();
            getline(ss, fechaStr, ';');
            getline(ss, idEditorialStr, ';');
            getline(ss, ciudadNac);
            Fecha fecha(fechaStr);
            idEditorial = stoi(idEditorialStr);

            // Buscar obra
            bool obraEncontrada = false;
            for (int i = 0; i < obras.getNumElem(); ++i)
            {
                if (obras.obtener(i).getTitulo() == nombreObra)
                {
                    // Verificar edicion existente
                    bool numeroDuplicado = false;
                    Lista<Edicion> &ediciones = obras.obtener(i).getEdiciones();
                    for (int j = 0; j < ediciones.getNumElem(); ++j)
                    {
                        if (ediciones.obtener(j).getNumero() == numero)
                        {
                            cout << "Edicion duplicada: " << numero
                                 << "; para obra: " << nombreObra << endl;
                            numeroDuplicado = true;
                            break;
                        }
                    }

                    if (!numeroDuplicado)
                    {
                        Edicion editorial(numero, fecha, idEditorial,
                                          obras.obtener(i).getIdAutor(),
                                          ciudadNac, nombreObra);
                        ediciones.insertarFinal(editorial);
                    }

                    obraEncontrada = true;
                    break;
                }
            }

            if (!obraEncontrada)
            {
                cout << "Obra no encontrada para edicion: " << nombreObra << endl;
            }
        }
        fed.close();
    }
}

void Gestor::guardarDatos()
{
    // Guardar autores
    ofstream fa("autores.txt");
    if (fa.is_open())
    {
        for (int i = 0; i < autores.getNumElem(); i++)
        {
            Autor a = autores.obtener(i);
            fa << a.getNombre() << ';' << a.getApellido() << ';' << a.getSexo() << ';'
               << a.getFechaNacimiento().toString() << ';' << a.getCiudadNacimiento() << ';'
               << a.getPaisNacimiento() << ';' << a.getCiudadResidencia() << ';'
               << a.getFormacionAcademica() << ';' << a.getId() << ';'
               << a.getYearInicioLiteratura() << ';' << a.getYearPublicacionPrimeraObra() << '\n';
        }
        fa.close();
    }

    // Guardar editoriales
    ofstream fe("editoriales.txt");
    if (fe.is_open())
    {
        for (int i = 0; i < editoriales.getNumElem(); i++)
        {
            Editorial e = editoriales.obtener(i);
            fe << e.getId() << ';' << e.getNombre() << ';'
               << e.getCiudad() << ';' << e.getPais() << '\n';
        }
        fe.close();
    }

    // Guardar obras
    ofstream fo("obras.txt");
    if (fo.is_open())
    {
        for (int i = 0; i < obras.getNumElem(); i++)
        {
            Obra &o = obras.obtener(i); // Referencia
            fo << o.getTitulo() << ';' << o.getTipoPoesia() << ';'
               << o.getIdAutor() << '\n';
        }
        fo.close();
    }

    // Guardar ediciones
    ofstream fed("ediciones.txt");
    if (fed.is_open())
    {
        for (int i = 0; i < obras.getNumElem(); i++)
        {
            Obra &o = obras.obtener(i);
            Lista<Edicion> &ediciones = o.getEdiciones();
            for (int j = 0; j < ediciones.getNumElem(); j++)
            {
                Edicion &e = ediciones.obtener(j);
                fed << o.getTitulo() << ';' << e.getNumero() << ';'
                    << e.getFechaPublicacion().toString() << ';'
                    << e.getIdEditorial() << ';' << e.getCiudad() << '\n';
            }
        }
        fed.close();
    }

    cout << "Datos guardados...\n";
}

Autor *Gestor::busquedaBinariaAutor(const string &apellido)
{
    int ini = 0, fin = autores.getNumElem() - 1;
    std::string apellidoBuscadoLower = toLower(apellido);

    while (ini <= fin)
    {
        int mid = (ini + fin) / 2;
        std::string apellidoActualLower = toLower(autores.obtener(mid).getApellido());

        if (apellidoActualLower == apellidoBuscadoLower)
            return &autores.obtener(mid);
        else if (apellidoActualLower < apellidoBuscadoLower)
            ini = mid + 1;
        else
            fin = mid - 1;
    }
    return nullptr;
}

Editorial *Gestor::busquedaBinariaEditorial(const string &nombre)
{
    int ini = 0, fin = editoriales.getNumElem() - 1;
    std::string nombreBuscadoLower = toLower(nombre);

    while (ini <= fin)
    {
        int mid = (ini + fin) / 2;
        std::string actualLower = toLower(editoriales.obtener(mid).getNombre());
        if (actualLower == nombreBuscadoLower)
            return &editoriales.obtener(mid);
        else if (actualLower < nombreBuscadoLower)
            ini = mid + 1;
        else
            fin = mid - 1;
    }
    return nullptr;
}

void Gestor::agregarAutor(const Autor &autor)
{
    // Verificar id
    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        if (autores.obtener(i).getId() == autor.getId())
        {
            cout << "Id duplicado: " << autor.getId() << endl;
            return;
        }
    }

    int pos = 0;
    while (pos < autores.getNumElem() && autores.obtener(pos).getApellido() < autor.getApellido())
    {
        pos++;
    }
    autores.insertarPos(autor, pos);
}

void Gestor::agregarEdicion(const Edicion &ed)
{
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getTitulo() == ed.getNombreObra())
        {
            // Verificar si la edicion ya existe
            Lista<Edicion> &ediciones = obras.obtener(i).getEdiciones();
            for (int j = 0; j < ediciones.getNumElem(); ++j)
            {
                if (ediciones.obtener(j).getNumero() == ed.getNumero())
                {
                    cout << "Numero de edicion duplicada: " << ed.getNumero()
                         << "; para obra: " << ed.getNombreObra() << endl;
                    return;
                }
            }

            ediciones.insertarFinal(ed);
            break;
        }
    }
}

void Gestor::agregarObra(const Obra &obra)
{
    // Verificar si el titulo ya existe
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getTitulo() == obra.getTitulo())
        {
            cout << "Titulo duplicado - " << obra.getTitulo() << endl;
            return;
        }
    }
    obras.insertarFinal(obra);
}

void Gestor::agregarEditorial(const Editorial &editorial)
{
    // Verificar si el id ya existe
    for (int i = 0; i < editoriales.getNumElem(); ++i)
    {
        if (editoriales.obtener(i).getId() == editorial.getId())
        {
            cout << "Error: ID de editorial duplicado - " << editorial.getId() << endl;
            return;
        }
    }

    int pos = 0;
    while (pos < editoriales.getNumElem() && editoriales.obtener(pos).getNombre() < editorial.getNombre())
    {
        pos++;
    }
    editoriales.insertarPos(editorial, pos);
}

bool Gestor::eliminarAutor(const string &apellido)
{
    Autor *autor = busquedaBinariaAutor(apellido);
    if (!autor)
        return false;

    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        if (autores.obtener(i).getId() == autor->getId())
        {
            autores.borrarPos(i);
            return true;
        }
    }
    return false;
}

bool Gestor::eliminarEditorial(const string &nombre)
{
    for (int i = 0; i < editoriales.getNumElem(); ++i)
    {
        if (editoriales.obtener(i).getNombre() == nombre)
        {
            editoriales.borrarPos(i);
            return true;
        }
    }
    return false;
}

bool Gestor::eliminarObra(const string &titulo)
{
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getTitulo() == titulo)
        {
            obras.borrarPos(i);
            return true;
        }
    }
    return false;
}

bool Gestor::eliminarEdicion(const string &titulo, int numero)
{
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getTitulo() == titulo)
        {
            Lista<Edicion> &ediciones = obras.obtener(i).getEdiciones();
            for (int j = 0; j < ediciones.getNumElem(); ++j)
            {
                if (ediciones.obtener(j).getNumero() == numero)
                {
                    ediciones.borrarPos(j);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Gestor::modificarAutor(const string &apellido, const Autor &nuevo)
{
    Autor *autorExistente = busquedaBinariaAutor(apellido);
    if (!autorExistente)
        return false;

    int id = autorExistente->getId();
    bool apellidoCambiado = (autorExistente->getApellido() != nuevo.getApellido());

    int pos = -1;
    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        if (autores.obtener(i).getId() == id)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
        return false;

    if (apellidoCambiado)
    {
        autores.borrarPos(pos);
        agregarAutor(nuevo);
    }
    else
    {
        autores.modificarPos(nuevo, pos);
    }

    return true;
}

bool Gestor::modificarEditorial(int id, const Editorial &nueva)
{
    for (int i = 0; i < editoriales.getNumElem(); ++i)
    {
        if (editoriales.obtener(i).getId() == id)
        {
            editoriales.modificarPos(nueva, i);
            return true;
        }
    }
    return false;
}

bool Gestor::modificarObra(const string &titulo, const Obra &nueva)
{
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getTitulo() == titulo)
        {
            obras.modificarPos(nueva, i);
            return true;
        }
    }
    return false;
}

bool Gestor::modificarEdicion(const string &titulo, int numero, const Edicion &nueva)
{
    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        if (obras.obtener(i).getTitulo() == titulo)
        {
            Lista<Edicion> &ediciones = obras.obtener(i).getEdiciones();
            for (int j = 0; j < ediciones.getNumElem(); ++j)
            {
                if (ediciones.obtener(j).getNumero() == numero)
                {
                    ediciones.modificarPos(nueva, j);
                    return true;
                }
            }
        }
    }
    return false;
}

void Gestor::listaAutores()
{
    int n = autores.getNumElem();
    if (n <= 0)
        return;
    int *indices = new int[n];
    for (int i = 0; i < n; ++i)
    {
        indices[i] = i;
    }

    // Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = indices[i];
            int j;
            for (j = i; j >= gap; j -= gap)
            {
                int indiceAnt = indices[j - gap];
                if (autores.obtener(indiceAnt).getId() <= autores.obtener(temp).getId())
                {
                    break;
                }
                indices[j] = indiceAnt;
            }
            indices[j] = temp;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        int idx = indices[i];
        Autor &a = autores.obtener(idx);
        cout << a.getId() << " - " << a.getNombre() << " " << a.getApellido() << endl;
    }

    delete[] indices;
}

void Gestor::listaEditoriales()
{
    int n = editoriales.getNumElem();
    if (n <= 0)
        return;

    int *indices = new int[n];
    for (int i = 0; i < n; ++i)
    {
        indices[i] = i;
    }

    // Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = indices[i];
            int j;
            for (j = i; j >= gap; j -= gap)
            {
                int indiceAnt = indices[j - gap];
                if (editoriales.obtener(indiceAnt).getId() <= editoriales.obtener(temp).getId())
                {
                    break;
                }
                indices[j] = indiceAnt;
            }
            indices[j] = temp;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        int idx = indices[i];
        Editorial &e = editoriales.obtener(idx);
        cout << e.getId() << " - " << e.getNombre() << endl;
    }

    delete[] indices;
}

void Gestor::listaObras()
{
    int n = obras.getNumElem();
    if (n <= 0)
        return;

    int *indices = new int[n];
    for (int i = 0; i < n; ++i)
    {
        indices[i] = i;
    }

    // Shell Sort
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = indices[i];
            int j;
            for (j = i; j >= gap; j -= gap)
            {
                int prev_idx = indices[j - gap];
                string titulo1 = obras.obtener(prev_idx).getTitulo();
                string titulo2 = obras.obtener(temp).getTitulo();
                if (titulo1 <= titulo2)
                    break;
                indices[j] = prev_idx;
            }
            indices[j] = temp;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        int idx = indices[i];
        Obra &o = obras.obtener(idx);
        cout << o.getTitulo() << " - " << o.getTipoPoesia() << " - Autor ID: " << o.getIdAutor() << endl;
    }

    delete[] indices;
}

void Gestor::listaEdiciones()
{
    int nObras = obras.getNumElem();
    if (nObras <= 0)
        return;

    int *indicesObras = new int[nObras];
    for (int i = 0; i < nObras; ++i)
    {
        indicesObras[i] = i;
    }

    // Shell Sort para ordenar obras relacionadas a ediciones
    for (int gap = nObras / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < nObras; i++)
        {
            int temp = indicesObras[i];
            int j;
            for (j = i; j >= gap; j -= gap)
            {
                int prev_idx = indicesObras[j - gap];
                string titulo1 = obras.obtener(prev_idx).getTitulo();
                string titulo2 = obras.obtener(temp).getTitulo();
                if (titulo1 <= titulo2)
                    break;
                indicesObras[j] = prev_idx;
            }
            indicesObras[j] = temp;
        }
    }

    // Recorrer obras ordenadas para mostrar ediciones
    for (int i = 0; i < nObras; ++i)
    {
        int idxObra = indicesObras[i];
        Obra &o = obras.obtener(idxObra);
        Lista<Edicion> &ediciones = o.getEdiciones();
        int nEdiciones = ediciones.getNumElem();

        if (nEdiciones > 0)
        {
            cout << "Obra: " << o.getTitulo() << endl;

            int *indicesEdiciones = new int[nEdiciones];
            for (int j = 0; j < nEdiciones; ++j)
            {
                indicesEdiciones[j] = j;
            }

            // Shell sort
            for (int gap_ed = nEdiciones / 2; gap_ed > 0; gap_ed /= 2)
            {
                for (int iEd = gap_ed; iEd < nEdiciones; iEd++)
                {
                    int temp = indicesEdiciones[iEd];
                    int jEd;
                    for (jEd = iEd; jEd >= gap_ed; jEd -= gap_ed)
                    {
                        int prev_idx = indicesEdiciones[jEd - gap_ed];
                        int num1 = ediciones.obtener(prev_idx).getNumero();
                        int num2 = ediciones.obtener(temp).getNumero();
                        if (num1 <= num2)
                            break;
                        indicesEdiciones[jEd] = prev_idx;
                    }
                    indicesEdiciones[jEd] = temp;
                }
            }

            for (int j = 0; j < nEdiciones; ++j)
            {
                int idxEd = indicesEdiciones[j];
                Edicion &e = ediciones.obtener(idxEd);
                cout << "Edicion " << e.getNumero()
                     << "; Editorial ID: " << e.getIdEditorial()
                     << "; Fecha: " << e.getFechaPublicacion().toString()
                     << "; Ciudad: " << e.getCiudad() << endl;
            }

            delete[] indicesEdiciones;
        }
    }

    delete[] indicesObras;
}

void Gestor::obrasPorAutor()
{
    cin.ignore();
    string nombreCompleto;
    cout << "Nombre completo del autor (\"Nombre Apellido\"): ";
    getline(cin, nombreCompleto);

    size_t pos = nombreCompleto.find_last_of(' ');
    if (pos == string::npos)
    {
        cout << "Formato invalido\n";
        return;
    }
    string nombre = nombreCompleto.substr(0, pos);
    string apellido = nombreCompleto.substr(pos + 1);
    string apellidoLower = toLower(apellido);

    // Binaria para autores
    Lista<Autor *> autoresConApellido;

    int low = 0;
    int high = autores.getNumElem() - 1;
    int midPoint = -1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        string currentApellido = toLower(autores.obtener(mid).getApellido());

        if (currentApellido == apellidoLower)
        {
            midPoint = mid;
            break;
        }
        else if (currentApellido < apellidoLower)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    // Expandir busqueda para encontrar todos los autores con el mismo apellido
    if (midPoint != -1)
    {
        int first = midPoint;
        while (first > 0 && toLower(autores.obtener(first - 1).getApellido()) == apellidoLower)
        {
            first--;
        }

        int last = midPoint;
        while (last < autores.getNumElem() - 1 && toLower(autores.obtener(last + 1).getApellido()) == apellidoLower)
        {
            last++;
        }

        for (int i = first; i <= last; ++i)
        {
            autoresConApellido.insertarFinal(&autores.obtener(i));
        }
    }

    if (autoresConApellido.getNumElem() == 0)
    {
        cout << "Autor no encontrado.\n";
        return;
    }

    int idAutor;
    string nombreAutorS;
    if (autoresConApellido.getNumElem() == 1)
    {
        idAutor = autoresConApellido.obtener(0)->getId();
        nombreAutorS = autoresConApellido.obtener(0)->getNombre() + " " + autoresConApellido.obtener(0)->getApellido();
    }
    else
    {
        cout << "Se encontraron " << autoresConApellido.getNumElem()
             << " autores con el apellido '" << apellido << "'. Seleccione uno:\n";

        for (int i = 0; i < autoresConApellido.getNumElem(); ++i)
        {
            Autor *a = autoresConApellido.obtener(i);
            cout << "id: " << a->getId() << " ; "
                 << a->getNombre() << " " << a->getApellido() << endl;
        }

        cout << "Ingrese el id del autor: ";
        cin >> idAutor;
        cin.ignore();

        bool idValido = false;
        for (int i = 0; i < autoresConApellido.getNumElem(); ++i)
        {
            if (autoresConApellido.obtener(i)->getId() == idAutor)
            {
                idValido = true;
                nombreAutorS = autoresConApellido.obtener(i)->getNombre() + " " +
                              autoresConApellido.obtener(i)->getApellido();
                break;
            }
        }

        if (!idValido)
        {
            cout << "id invalido\n";
            return;
        }
    }

    cout << "Obras por editorial y fecha de publicacion:\n";
    bool encontradas = false;
    string nombreAutor = "";

    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        if (autores.obtener(i).getId() == idAutor)
        {
            nombreAutor = autores.obtener(i).getNombre() + " " + autores.obtener(i).getApellido();
            break;
        }
    }
    int totalObras = 0;

    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        Obra &obra = obras.obtener(i);
        if (obra.getIdAutor() == idAutor)
        {
            totalObras++;
            encontradas = true;

            if (obra.getEdiciones().getNumElem() == 0)
            {
                cout << obra.getTitulo()
                     << " ; (Sin ediciones registradas)" << endl;
            }
            else
            {
                for (int j = 0; j < obra.getEdiciones().getNumElem(); ++j)
                {
                    Edicion &ed = obra.getEdiciones().obtener(j);
                    bool editorialEncontrada = false;
                    string nombreEditorial = "(Editorial desconocida)";

                    for (int k = 0; k < editoriales.getNumElem(); ++k)
                    {
                        if (editoriales.obtener(k).getId() == ed.getIdEditorial())
                        {
                            nombreEditorial = editoriales.obtener(k).getNombre();
                            editorialEncontrada = true;
                            break;
                        }
                    }

                    cout << obra.getTitulo() << " ; "
                         << nombreEditorial << " ; "
                         << ed.getFechaPublicacion().getYear();

                    if (!editorialEncontrada)
                    {
                        cout << " [Editorial con id " << ed.getIdEditorial() << " no registrada]";
                    }

                    cout << endl;
                }
            }
        }
    }

    if (!encontradas)
    {
        cout << nombreAutor << " no tiene obras registradas en el sistema.\n";
    }
    else
    {
        cout << "No hay mas obras de " << nombreAutor << ", el total de sus obras fue " << totalObras << "\n";
    }
}

void Gestor::nombresObrasPorTipo()
{
    cin.ignore();
    string nombreCompleto;
    cout << "Nombre completo del autor (\"Nombre Apellido\"): ";
    getline(cin, nombreCompleto);

    size_t pos = nombreCompleto.find_last_of(' ');
    if (pos == string::npos)
    {
        cout << "Formato invalido\n";
        return;
    }
    string apellido = nombreCompleto.substr(pos + 1);

    Autor *autor = busquedaBinariaAutor(apellido);
    if (!autor)
    {
        cout << "Autor no encontrado.\n";
        return;
    }

    int idAutor = autor->getId();
    cout << "Obras del autor agrupadas por tipo de poesia:\n";

    for (int i = 0; i < obras.getNumElem(); ++i)
    {
        Obra &obra = obras.obtener(i);
        if (obra.getIdAutor() == idAutor)
        {
            cout << "Tipo: " << obra.getTipoPoesia() << endl;
            for (int j = 0; j < obra.getEdiciones().getNumElem(); ++j)
            {
                Edicion &ed = obra.getEdiciones().obtener(j);
                cout << obra.getTitulo()
                     << " ; Edicion " << ed.getNumero()
                     << " ; Publicada en: " << ed.getFechaPublicacion().toString() << endl;
            }
        }
    }
}

void Gestor::autoresPorEditorial()
{
    string nombreEditorial;
    cin.ignore();
    cout << "Nombre de la editorial: ";
    getline(cin, nombreEditorial);

    Editorial *editorial = busquedaBinariaEditorial(nombreEditorial);
    if (!editorial)
    {
        cout << "Editorial no encontrada.\n";
        return;
    }

    int idEditorial = editorial->getId();
    int totalAutores = 0;
    cout << "Autores publicados por la editorial \"" << editorial->getNombre() << "\":\n";

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
                    if (obras.obtener(j).getEdiciones().obtener(k).getIdEditorial() == idEditorial)
                    {
                        publicado = true;
                        totalAutores++;
                        break;
                    }
                }
            }
            if (publicado)
                break;
        }

        if (publicado)
        {
            Autor &a = autores.obtener(i);
            cout << a.getNombre() << " " << a.getApellido()
                 << "; Nacido en: " << a.getCiudadNacimiento() << ", " << a.getPaisNacimiento()
                 << "; Reside en: " << a.getCiudadResidencia()
                 << "; fecha inicio en la literatura: " << a.getYearInicioLiteratura() << '\n';
        }
    }
    cout << "Total de autores publicados por la editorial: " << totalAutores << endl;
}

void Gestor::editorialesPorPoetas(int umbral)
{
    cout << "Editoriales con al menos " << umbral << " poetas:\n";

    for (int i = 0; i < editoriales.getNumElem(); ++i)
    {
        Editorial &editorial = editoriales.obtener(i);
        Lista<int> autoresPublicados;

        for (int j = 0; j < obras.getNumElem(); ++j)
        {
            Obra &obra = obras.obtener(j);

            for (int k = 0; k < obra.getEdiciones().getNumElem(); ++k)
            {
                Edicion &ed = obra.getEdiciones().obtener(k);

                if (ed.getIdEditorial() == editorial.getId())
                {
                    bool yaContado = false;
                    for (int a = 0; a < autoresPublicados.getNumElem(); ++a)
                    {
                        if (autoresPublicados.obtener(a) == obra.getIdAutor())
                        {
                            yaContado = true;
                            break;
                        }
                    }

                    if (!yaContado)
                    {
                        autoresPublicados.insertarFinal(obra.getIdAutor());
                    }

                    break;
                }
            }
        }

        if (autoresPublicados.getNumElem() >= umbral)
        {
            cout << editorial.getNombre() << " (" << autoresPublicados.getNumElem() << " poetas)\n";
        }
    }
}

void Gestor::generoPorEditorial()
{
    cout << "Distribucion por generos de autores por editorial:\n";

    for (int i = 0; i < editoriales.getNumElem(); ++i)
    {
        Editorial &editorial = editoriales.obtener(i);
        Lista<int> idsAutores;

        for (int j = 0; j < obras.getNumElem(); ++j)
        {
            Obra &obra = obras.obtener(j);

            for (int k = 0; k < obra.getEdiciones().getNumElem(); ++k)
            {
                Edicion &ed = obra.getEdiciones().obtener(k);

                if (ed.getIdEditorial() == editorial.getId())
                {
                    bool yaExiste = false;
                    for (int x = 0; x < idsAutores.getNumElem(); ++x)
                    {
                        if (idsAutores.obtener(x) == obra.getIdAutor())
                        {
                            yaExiste = true;
                            break;
                        }
                    }
                    if (!yaExiste)
                        idsAutores.insertarFinal(obra.getIdAutor());
                }
            }
        }

        int hombres = 0, mujeres = 0;

        for (int i = 0; i < idsAutores.getNumElem(); ++i)
        {
            int idAutor = idsAutores.obtener(i);
            for (int j = 0; j < autores.getNumElem(); ++j)
            {
                if (autores.obtener(j).getId() == idAutor)
                {
                    std::string sexoLower = toLower(autores.obtener(j).getSexo());
                    if (sexoLower == "m")
                        hombres++;
                    else if (sexoLower == "f")
                        mujeres++;
                    break;
                }
            }
        }

        cout << editorial.getNombre()
             << ": Hombres = " << hombres
             << "; Mujeres = " << mujeres << '\n';
    }
}

void Gestor::autoresPorEdadYFormacion(int edadMin, int edadMax, string formacion)
{
    cout << "Autores con formacion '" << formacion << "' y edad entre " << edadMin << " y " << edadMax << ":\n";
    std::string formacionLower = toLower(formacion);

    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        Autor &autor = autores.obtener(i);
        int edad = autor.calcularEdad();

        if (edad >= edadMin && edad <= edadMax && toLower(autor.getFormacionAcademica()) == formacionLower)
        {
            cout << autor.getNombre() << " " << autor.getApellido()
                 << " ; Edad: " << edad
                 << " ; Formacion: " << autor.getFormacionAcademica() << '\n';
        }
    }
}

void Gestor::autoresPorPoesiaYEditorial(string tipo, int idEditorial)
{
    cout << "Autores que escriben poesia tipo '" << tipo
         << "' y han publicado con la editorial id " << idEditorial << ":\n";

    std::string tipoLower = toLower(tipo);

    for (int i = 0; i < autores.getNumElem(); ++i)
    {
        int idAutor = autores.obtener(i).getId();
        bool coincide = false;

        for (int j = 0; j < obras.getNumElem(); ++j)
        {
            Obra &o = obras.obtener(j);
            if (o.getIdAutor() == idAutor && toLower(o.getTipoPoesia()) == tipoLower)
            {
                for (int k = 0; k < o.getEdiciones().getNumElem(); ++k)
                {
                    if (o.getEdiciones().obtener(k).getIdEditorial() == idEditorial)
                    {
                        coincide = true;
                        break;
                    }
                }
            }
            if (coincide)
                break;
        }

        if (coincide)
        {
            Autor &a = autores.obtener(i);
            cout << "- " << a.getNombre() << " " << a.getApellido() << '\n';
        }
    }
}

void Gestor::menu()
{
    int opcion;
    while (true)
    {
        cout << "\nMenu Principal:\n";
        cout << "1. Gestion de datos\n";
        cout << "2. Consultas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 0)
        {
            cout << "Saliendo del programa\n";
            guardarDatos();
            break;
        }

        switch (opcion)
        {
        case 1:
        {
            int opcion2;
            cout << "\nGestion de datos\n";
            cout << "1. Autores\n";
            cout << "2. Editoriales\n";
            cout << "3. Obras\n";
            cout << "4. Ediciones\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion2;

            switch (opcion2)
            {
            case 1:
            {
                int opcionAutor;
                cout << "\nGestion de Autores\n";
                cout << "1. Listar\n";
                cout << "2. Agregar\n";
                cout << "3. Eliminar\n";
                cout << "4. Modificar\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionAutor;

                switch (opcionAutor)
                {
                case 1:
                    listaAutores();
                    break;
                case 2:
                {
                    int id, fechaInicio, fechaPrimeraObra;
                    string nombre, apellido, sexo, fechaNacStr, ciudadNac, pais, ciudadRes, formacion;
                    cout << "ID: ";
                    cin >> id;
                    cin.ignore();
                    cout << "Nombre: ";
                    getline(cin, nombre);
                    cout << "Apellido: ";
                    getline(cin, apellido);
                    cout << "Sexo (M/F): ";
                    getline(cin, sexo);
                    cout << "Fecha nacimiento (YYYY-MM-DD): ";
                    getline(cin, fechaNacStr);
                    cout << "Ciudad nacimiento: ";
                    getline(cin, ciudadNac);
                    cout << "Pais nacimiento: ";
                    getline(cin, pais);
                    cout << "Ciudad residencia: ";
                    getline(cin, ciudadRes);
                    cout << "Formacion academica: ";
                    getline(cin, formacion);
                    cout << "fecha inicio literatura: ";
                    cin >> fechaInicio;
                    cout << "fecha primera obra: ";
                    cin >> fechaPrimeraObra;
                    Fecha fNac(fechaNacStr);
                    agregarAutor(Autor(id, nombre, apellido, sexo, fNac, ciudadNac, pais, ciudadRes, formacion, fechaInicio, fechaPrimeraObra));
                    break;
                }
                case 3:
                {
                    string nombreCompleto;
                    cin.ignore();
                    cout << "Nombre completo del autor a eliminar (\"Nombre Apellido\"): ";
                    getline(cin, nombreCompleto);

                    size_t pos = nombreCompleto.find_last_of(' ');
                    if (pos == string::npos)
                    {
                        cout << "Formato invalido.\n";
                        break;
                    }
                    string apellido = nombreCompleto.substr(pos + 1);

                    if (eliminarAutor(apellido))
                        cout << "Autor eliminado.\n";
                    else
                        cout << "Autor no encontrado.\n";
                    break;
                }
                case 4:
                {
                    string nombreCompleto;
                    cin.ignore();
                    cout << "Nombre completo del autor a modificar (\"Nombre Apellido\"): ";
                    getline(cin, nombreCompleto);

                    size_t pos = nombreCompleto.find_last_of(' ');
                    if (pos == string::npos)
                    {
                        cout << "Formato invalido.\n";
                        break;
                    }
                    string apellido = nombreCompleto.substr(pos + 1);

                    Autor *autor = busquedaBinariaAutor(apellido);
                    if (!autor)
                    {
                        cout << "Autor no encontrado.\n";
                        break;
                    }

                    string nuevoNombre, nuevoApellido, sexo, fechaNacStr, ciudadNac, pais, ciudadRes, formacion;
                    int fechaInicio, fechaPrimeraObra;

                    cout << "Nuevo nombre: ";
                    getline(cin, nuevoNombre);
                    cout << "Nuevo apellido: ";
                    getline(cin, nuevoApellido);
                    cout << "Nuevo sexo (M/F): ";
                    getline(cin, sexo);
                    cout << "Nueva fecha nacimiento (YYYY-MM-DD): ";
                    getline(cin, fechaNacStr);
                    cout << "Ciudad nacimiento: ";
                    getline(cin, ciudadNac);
                    cout << "Pais nacimiento: ";
                    getline(cin, pais);
                    cout << "Ciudad residencia: ";
                    getline(cin, ciudadRes);
                    cout << "Formacion academica: ";
                    getline(cin, formacion);
                    cout << "fecha inicio literatura: ";
                    cin >> fechaInicio;
                    cout << "fecha primera obra: ";
                    cin >> fechaPrimeraObra;

                    Fecha fNac(fechaNacStr);
                    Autor nuevo(autor->getId(), nuevoNombre, nuevoApellido, sexo, fNac,
                                ciudadNac, pais, ciudadRes, formacion, fechaInicio, fechaPrimeraObra);

                    if (modificarAutor(apellido, nuevo))
                        cout << "Autor modificado.\n";
                    else
                        cout << "Error al modificar autor.\n";
                    break;
                }
                default:
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 2:
            {
                int opcionEd;
                cout << "\nGestion de Editoriales\n";
                cout << "1. Listar\n";
                cout << "2. Agregar\n";
                cout << "3. Eliminar\n";
                cout << "4. Modificar\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionEd;

                switch (opcionEd)
                {
                case 1:
                    listaEditoriales();
                    break;
                case 2:
                {
                    int id;
                    string nombre, ciudad, pais;
                    cout << "ID: ";
                    cin >> id;
                    cin.ignore();
                    cout << "Nombre: ";
                    getline(cin, nombre);
                    cout << "Ciudad: ";
                    getline(cin, ciudad);
                    cout << "Pais: ";
                    getline(cin, pais);
                    agregarEditorial(Editorial(id, nombre, ciudad, pais));
                    break;
                }
                case 3:
                {
                    string nombre;
                    cin.ignore();
                    cout << "Nombre de la editorial a eliminar: ";
                    getline(cin, nombre);
                    if (eliminarEditorial(nombre))
                        cout << "Editorial eliminada.\n";
                    else
                        cout << "Editorial no encontrada.\n";
                    break;
                }
                case 4:
                {
                    string nombre;
                    cin.ignore();
                    cout << "Nombre de la editorial a modificar: ";
                    getline(cin, nombre);
                    Editorial *editorial = busquedaBinariaEditorial(nombre);
                    if (!editorial)
                    {
                        cout << "Editorial no encontrada.\n";
                        break;
                    }
                    string ciudad, pais;
                    cout << "Nuevo nombre: ";
                    getline(cin, nombre);
                    cout << "Nueva ciudad: ";
                    getline(cin, ciudad);
                    cout << "Nuevo pais: ";
                    getline(cin, pais);
                    modificarEditorial(editorial->getId(), Editorial(editorial->getId(), nombre, ciudad, pais));
                    break;
                }
                default:
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 3:
            {
                int opcionObra;
                cout << "\nGestion de Obras\n";
                cout << "1. Listar\n";
                cout << "2. Agregar\n";
                cout << "3. Eliminar\n";
                cout << "4. Modificar\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionObra;

                switch (opcionObra)
                {
                case 1:
                    listaObras();
                    break;
                case 2:
                {
                    string titulo, tipo, nombreCompleto;
                    cin.ignore();
                    cout << "Titulo: ";
                    getline(cin, titulo);
                    cout << "Tipo de poesia: ";
                    getline(cin, tipo);
                    cout << "Nombre completo del autor (\"Nombre Apellido\"): ";
                    getline(cin, nombreCompleto);

                    size_t pos = nombreCompleto.find_last_of(' ');
                    if (pos == string::npos)
                    {
                        cout << "Formato invalido.\n";
                        break;
                    }
                    string apellido = nombreCompleto.substr(pos + 1);

                    Autor *autor = busquedaBinariaAutor(apellido);
                    if (!autor)
                    {
                        cout << "Autor no encontrado.\n";
                        break;
                    }
                    agregarObra(Obra(autor->getId(), titulo, tipo));
                    break;
                }
                case 3:
                {
                    string titulo;
                    cin.ignore();
                    cout << "Titulo de la obra a eliminar: ";
                    getline(cin, titulo);
                    if (eliminarObra(titulo))
                        cout << "Obra eliminada.\n";
                    else
                        cout << "Obra no encontrada.\n";
                    break;
                }
                case 4:
                {
                    string titulo;
                    cin.ignore();
                    cout << "Titulo de la obra a modificar: ";
                    getline(cin, titulo);
                    for (int i = 0; i < obras.getNumElem(); ++i)
                    {
                        if (obras.obtener(i).getTitulo() == titulo)
                        {
                            string nuevoTipo, nuevoAutorCompleto;
                            cout << "Nuevo tipo de poesia: ";
                            getline(cin, nuevoTipo);
                            cout << "Nombre completo del nuevo autor (\"Nombre Apellido\"): ";
                            getline(cin, nuevoAutorCompleto);

                            size_t pos = nuevoAutorCompleto.find_last_of(' ');
                            if (pos == string::npos)
                            {
                                cout << "Formato invalido.\n";
                                break;
                            }
                            string apellido = nuevoAutorCompleto.substr(pos + 1);

                            Autor *autor = busquedaBinariaAutor(apellido);
                            if (!autor)
                            {
                                cout << "Autor no encontrado.\n";
                                break;
                            }
                            Obra nueva(autor->getId(), titulo, nuevoTipo);
                            modificarObra(titulo, nueva);
                            break;
                        }
                    }
                    break;
                }
                default:
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 4:
            {
                int opcionEdicion;
                cout << "\nGestion de Ediciones\n";
                cout << "1. Listar\n";
                cout << "2. Agregar\n";
                cout << "3. Eliminar\n";
                cout << "4. Modificar\n";
                cout << "Seleccione una opcion: ";
                cin >> opcionEdicion;

                switch (opcionEdicion)
                {
                case 1:
                    listaEdiciones();
                    break;
                case 2:
                {
                    string tituloObra, fechaStr, ciudad, idEditorialStr;
                    int numero, idEditorial;
                    cin.ignore();
                    cout << "Titulo de la obra: ";
                    getline(cin, tituloObra);
                    cout << "Numero de edicion: ";
                    cin >> numero;
                    cin.ignore();
                    cout << "Fecha publicacion (YYYY-MM-DD): ";
                    getline(cin, fechaStr);
                    cout << "ID Editorial: ";
                    getline(cin, idEditorialStr);
                    idEditorial = stoi(idEditorialStr);
                    cout << "Ciudad de publicacion: ";
                    getline(cin, ciudad);

                    int idAutor = -1;
                    for (int i = 0; i < obras.getNumElem(); ++i)
                    {
                        if (obras.obtener(i).getTitulo() == tituloObra)
                        {
                            idAutor = obras.obtener(i).getIdAutor();
                            break;
                        }
                    }

                    if (idAutor == -1)
                    {
                        cout << "Obra no encontrada.\n";
                        break;
                    }

                    Fecha fecha(fechaStr);
                    Edicion nuevaEdicion(numero, fecha, idEditorial, idAutor, ciudad, tituloObra);
                    agregarEdicion(nuevaEdicion);
                    cout << "Edicion agregada.\n";
                    break;
                }
                case 3:
                {
                    string titulo;
                    int numero;
                    cin.ignore();
                    cout << "Titulo de la obra: ";
                    getline(cin, titulo);
                    cout << "Numero de edicion a eliminar: ";
                    cin >> numero;

                    if (eliminarEdicion(titulo, numero))
                        cout << "Edicion eliminada.\n";
                    else
                        cout << "Edicion no encontrada.\n";
                    break;
                }
                case 4:
                {
                    string titulo;
                    int numero;
                    cin.ignore();
                    cout << "Titulo de la obra: ";
                    getline(cin, titulo);
                    cout << "Numero de edicion a modificar: ";
                    cin >> numero;

                    Edicion *edicionExistente = nullptr;
                    for (int i = 0; i < obras.getNumElem(); ++i)
                    {
                        if (obras.obtener(i).getTitulo() == titulo)
                        {
                            Lista<Edicion> &ediciones = obras.obtener(i).getEdiciones();
                            for (int j = 0; j < ediciones.getNumElem(); ++j)
                            {
                                if (ediciones.obtener(j).getNumero() == numero)
                                {
                                    edicionExistente = &ediciones.obtener(j);
                                    break;
                                }
                            }
                        }
                    }

                    if (!edicionExistente)
                    {
                        cout << "Edicion no encontrada.\n";
                        break;
                    }

                    string nuevaFechaStr, nuevaCiudad, nuevoIdEditorialStr;
                    int nuevoIdEditorial;
                    cout << "Nuevo numero de edicion: ";
                    cin >> numero;
                    cin.ignore();
                    cout << "Nueva fecha publicacion (YYYY-MM-DD): ";
                    getline(cin, nuevaFechaStr);
                    cout << "Nuevo ID Editorial: ";
                    getline(cin, nuevoIdEditorialStr);
                    nuevoIdEditorial = stoi(nuevoIdEditorialStr);
                    cout << "Nueva ciudad de publicacion: ";
                    getline(cin, nuevaCiudad);

                    Fecha nuevaFecha(nuevaFechaStr);
                    Edicion nuevaEdicion(
                        numero,
                        nuevaFecha,
                        nuevoIdEditorial,
                        edicionExistente->getIdAutor(),
                        nuevaCiudad,
                        titulo);

                    if (modificarEdicion(titulo, edicionExistente->getNumero(), nuevaEdicion))
                        cout << "Edicion modificada.\n";
                    else
                        cout << "Error al modificar edicion.\n";
                    break;
                }
                default:
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            default:
                cout << "Opcion invalida.\n";
            }
            break;
        }

        case 2:
        {
            int opcionConsulta;
            cout << "\nConsultas:\n";
            cout << "1. Obras por autor\n";
            cout << "2. Nombres de obras por tipo de poesia\n";
            cout << "3. Autores por editorial\n";
            cout << "4. Editoriales con al menos X poetas\n";
            cout << "5. Genero por editorial\n";
            cout << "6. Autores por edad y formacion\n";
            cout << "7. Autores por tipo de poesia y editorial\n";
            cout << "Seleccione una opcion: ";
            cin >> opcionConsulta;
            switch (opcionConsulta)
            {
            case 1:
                obrasPorAutor();
                break;
            case 2:
                nombresObrasPorTipo();
                break;
            case 3:
                autoresPorEditorial();
                break;
            case 4:
            {
                int umbral;
                cout << "Ingrese el numero minimo de poetas: ";
                cin >> umbral;
                editorialesPorPoetas(umbral);
                break;
            }
            case 5:
                generoPorEditorial();
                break;
            case 6:
            {
                int min, max;
                string formacion;
                cout << "Edad minima: ";
                cin >> min;
                cout << "Edad maxima: ";
                cin >> max;
                cin.ignore();
                cout << "Formacion academica: ";
                getline(cin, formacion);
                autoresPorEdadYFormacion(min, max, formacion);
                break;
            }
            case 7:
            {
                string tipo;
                string nombreEditorial;
                cout << "Tipo de poesia: ";
                cin.ignore();
                getline(cin, tipo);
                cout << "Nombre de la editorial: ";
                getline(cin, nombreEditorial);
                Editorial *editorial = busquedaBinariaEditorial(nombreEditorial);
                if (editorial)
                    autoresPorPoesiaYEditorial(tipo, editorial->getId());
                else
                    cout << "Editorial no encontrada.\n";
                break;
            }
            default:
                cout << "Opcion invalida.\n";
            }
            break;
        }
        default:
            cout << "Opcion invalida.\n";
        }
    }
}

#endif