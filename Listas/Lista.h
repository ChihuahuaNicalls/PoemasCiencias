#ifndef LISTA_H
#define LISTA_H
#include <iostream>

using namespace std;

template <class T>
struct nodo {
  T dato1;
  nodo<T>* sig;

  nodo(const T& d, nodo<T>* s = nullptr) : dato1(d), sig(s) {}
};

template <class T>
class Lista {
  int numElem;
  nodo<T>* cab;

 public:
  Lista() {
    numElem = 0;
    cab = NULL;
  }

  ~Lista() {
    vaciarLista();
  }

  bool listaVacia() { return (cab == NULL); }

  void insertarInicio(T info1);
  void insertarFinal(T info1);
  void insertarPos(T info1, int pos);
  nodo<T>* buscarPos(int pos);
  T& obtener(int pos);
  bool borrarPos(int pos);
  bool modificarPos(T info1, int pos);
  void vaciarLista();
  int getNumElem() { return numElem; }
};

template <class T>
void Lista<T>::insertarInicio(T info1) {
  cab = new nodo<T>(info1, cab); 
  numElem++;
}

template <class T>
void Lista<T>::insertarFinal(T info1) {
  if (listaVacia()) {
    cab = new nodo<T>(info1);
  } else {
    nodo<T>* fin = cab;
    while (fin->sig != NULL) fin = fin->sig;
    fin->sig = new nodo<T>(info1);
  }
  numElem++;
}

template <class T>
void Lista<T>::insertarPos(T info1, int pos) {
  if (pos < 0 || pos > numElem) {
    cout << "No se pudo insertar en esa posicion" << endl;
    return;
  }

  if (pos == 0) {
    insertarInicio(info1);
  } else if (pos == numElem) {
    insertarFinal(info1);
  } else {
    nodo<T>* ins = cab;
    for (int i = 0; i < pos - 1; i++) {
      ins = ins->sig;
    }
    ins->sig = new nodo<T>(info1, ins->sig);
    numElem++;
  }
}

template <class T>
nodo<T>* Lista<T>::buscarPos(int pos) {
  if (pos < 0 || pos > numElem) {
    cout << "No se pudo insertar en esa posicion" << endl;
    return NULL;
  } else {
    nodo<T>* aux = cab;
    for (int i = 1; i < pos; i++) {
      aux = aux->sig;
    }
    return aux;
  }
}

template <class T>
T& Lista<T>::obtener(int pos) {
    if (pos < 0 || pos >= numElem) {
        throw out_of_range("Posicion invalida");
    }
    nodo<T>* aux = cab;
    for (int i = 0; i < pos; i++) {
        aux = aux->sig;
    }
    return aux->dato1;
}

template <class T>
bool Lista<T>::borrarPos(int pos) {
  if (pos < 0 || pos >= numElem || listaVacia()) return false;
  if (pos == 0) {
    nodo<T>* aux = cab;
    cab = cab->sig;
    delete aux;
    numElem--;
    return true;
  } else {
    nodo<T>* aux = cab;
    for (int i = 0; i < pos - 1; i++) aux = aux->sig;
    nodo<T>* borrar = aux->sig;
    aux->sig = borrar->sig;
    delete borrar;
    numElem--;
    return true;
  }
}

template <class T>
bool Lista<T>::modificarPos(T info1, int pos) {
  nodo<T>* aux = buscarPos(pos);
  if (aux != NULL) {
    aux->dato1 = info1;
    return true;
  } else {
    return false;
  }
}

template <class T>
void Lista<T>::vaciarLista() {
  nodo<T>* aux1 = cab;
  nodo<T>* aux2;
  while (aux1 != NULL) {
    aux2 = aux1->sig;
    delete aux1;
    aux1 = aux2;
  }
  cab = NULL;
  numElem = 0;
}

#endif