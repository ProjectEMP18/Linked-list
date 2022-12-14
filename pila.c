#include "pila.h"
#include "lista.h"


pila_t* pila_crear(){
    lista_t* lista = lista_crear();
    return (pila_t*) lista;
}

pila_t* pila_apilar(pila_t* pila, void* elemento){
    lista_t* lista = (lista_t*) pila;
    lista = lista_insertar(lista, elemento);
    return (pila_t*)lista;
}

void* pila_desapilar(pila_t* pila){
    lista_t* lista = (lista_t*) pila;
    return lista_quitar(lista);
}

void* pila_tope(pila_t* pila){
    lista_t* lista = (lista_t*) pila;
    return lista_ultimo(lista);
}

size_t pila_tamanio(pila_t* pila){
    lista_t* lista = (lista_t*) pila;
    return lista_tamanio(lista);
}

bool pila_vacia(pila_t* pila){
    lista_t* lista = (lista_t*) pila;
    return lista_vacia(lista);
}

void pila_destruir(pila_t* pila){
    lista_t* lista = (lista_t*) pila;
    lista_destruir(lista);
}
