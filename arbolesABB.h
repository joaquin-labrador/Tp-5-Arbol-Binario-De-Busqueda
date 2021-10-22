#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define FILE_ARBOL "arbolesabb.bin"
typedef struct {
     int legajo;
     char nombre[20]; 
     int edad; 
} persona;
typedef struct nodoArbol { 
     persona dato;
     struct nodoArbol * izq; 
     struct nodoArbol * der;
} nodoArbol;
typedef struct nodo{
     persona dato;
     struct nodo * sig;
}nodo;

persona crearStruct();
int verficador(int legajo);
void cargarArchivo();
void verArchivo();
void cargarArbol(nodoArbol **a);
nodoArbol *crearNodo(persona a);
void insertarOrdenado(nodoArbol **a,persona dato);
void inorder(nodoArbol *a);
void mostrador(persona a);
nodo *crearNodoLista (persona dato);
void insertarAlPrincipio(nodo **lista, persona dato);
void copiaArbolALista(nodoArbol *a, nodo **lista);
void verLista(nodo *lista);
void nodoPorlegajo (nodoArbol *a,int legajo);
nodoArbol *busquedaPorLegajo(nodoArbol *a, int legajo);
nodoArbol *busquedaPorNombre(nodoArbol *a, char nombre[]);
int cantidadDeNodo(nodoArbol *a);
int cantidadHojas(nodoArbol *a);
int alturaArbol(nodoArbol *a);
void eliminarNodo(nodoArbol **a , int legajo);
void borrarDatoExtIzq (nodoArbol **a, nodoArbol *act);
void borrarDatoExtDer(nodoArbol **a, nodoArbol *act);
