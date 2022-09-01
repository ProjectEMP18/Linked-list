#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

//FUNCIONES PRIVADAS DE TDA LISTA ABAJO DE ESTA LINEA
nodo_t* crear_nodo(void* elemento){
   nodo_t* nodo = malloc(sizeof(nodo_t));
   if (!nodo){
       free(nodo);
       return NULL;
    }
   else{
       nodo->elemento = elemento;
       nodo->siguiente = NULL;
       return nodo;       
   }
}

//FUNCIONES PRIVADAS DE TDA LISTA ARRIBA DE ESTA LINEA

lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if (!lista){
        free(lista);
        return NULL;
    }
    lista->cantidad = 0;
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    return lista;
}

lista_t* lista_insertar(lista_t* lista, void* elemento){
    if (!lista)
        return NULL;
    if (lista_vacia(lista) == true){
        nodo_t* nodo = crear_nodo(elemento);
        lista->nodo_inicio = nodo;
        lista->nodo_fin = nodo;
        lista->cantidad++;
        return lista;
    }
    else{
        nodo_t* nodo = crear_nodo(elemento);
        nodo_t* ultimo_nodo_anterior = lista->nodo_fin; 
        ultimo_nodo_anterior->siguiente = nodo;
        lista->nodo_fin = nodo;
        lista->cantidad++;
        return lista;
    }
}

lista_t* lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if (!lista)
        return NULL;
    if (posicion >= lista->cantidad || lista_vacia(lista)==true){
        return lista_insertar(lista, elemento);
    }
    else if (posicion==0){
        nodo_t* nodo_a_insertar = crear_nodo(elemento);
        nodo_t* nodo_actual = lista->nodo_inicio;
        nodo_a_insertar->siguiente = nodo_actual;
        lista->nodo_inicio = nodo_a_insertar;
        lista->cantidad++;
        return lista;
    }
    else{
        nodo_t* nodo_a_insertar = crear_nodo(elemento);
        size_t iterador = 0;
        nodo_t* nodo_actual = lista->nodo_inicio;
        while(iterador < posicion-1){
            iterador++;
            nodo_actual = nodo_actual->siguiente;
            
        }
        nodo_a_insertar->siguiente = nodo_actual->siguiente;
        nodo_actual->siguiente = nodo_a_insertar;
        lista->cantidad++;
        return lista;
    }
}

void* lista_quitar(lista_t* lista){
    if (!lista)
        return NULL;
    if(lista_vacia(lista)==true){
        return NULL;
    }
    else if (lista->cantidad == 1){
        nodo_t* aux = lista->nodo_fin;
        void* elemento = aux->elemento;
        lista->cantidad--;
        free(aux);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
        return elemento;
    }
    else{
        nodo_t* aux = lista->nodo_fin;
        size_t pos_act = 0;
        nodo_t* nodo_actual = lista->nodo_inicio;
        while(pos_act < (lista->cantidad - 2)){
            pos_act++;
            nodo_actual = nodo_actual->siguiente;
            
        }
        nodo_actual->siguiente = aux->siguiente;
        void* elemento = aux->elemento;
        lista->nodo_fin = nodo_actual;
        lista->cantidad--;
        free(aux);
        return elemento;
    }
}

void* lista_quitar_de_posicion(lista_t* lista, size_t posicion){
    if (!lista)
        return NULL;
    if(posicion > lista->cantidad || (posicion == 0 && lista->cantidad == 1)){
        return lista_quitar(lista);
    }
    else if (posicion == 0){
        nodo_t* aux = lista->nodo_inicio;
        void* elemento_a_devolver = aux->elemento;
        lista->nodo_inicio = aux->siguiente;
        free(aux);
        lista->cantidad--;
        return elemento_a_devolver;
    }
    else{
        nodo_t* nodo_actual = lista->nodo_inicio;
        size_t iterador = 0;
        while (iterador < posicion-1){
            iterador++;
            nodo_actual = nodo_actual->siguiente;
            
        }
        nodo_t* aux = nodo_actual->siguiente;
        nodo_actual->siguiente = aux->siguiente;
        void* elemento_a_devolver = aux->elemento;
        free(aux);
        lista->cantidad--;
        return elemento_a_devolver;
    }
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if (!lista || (posicion > lista->cantidad-1 || lista_vacia(lista)==true)){
        return NULL;
    }
    else if (posicion == 0){
        return lista->nodo_inicio->elemento;
    }
    else if(posicion == lista->cantidad-1){
        return lista->nodo_fin->elemento;
    }
    else{
        size_t pos_act = 0;
        nodo_t* nodo_actual = lista->nodo_inicio;
        while (pos_act <= posicion-1){
            pos_act++;
            nodo_actual = nodo_actual->siguiente;
            
        }
        return nodo_actual->elemento;
    }
}

void* lista_primero(lista_t* lista){
    if (lista_vacia(lista)==true)
        return NULL;
    nodo_t* nodo_a_devolver = lista->nodo_inicio;
    return nodo_a_devolver->elemento;
}

void* lista_ultimo(lista_t* lista){
    if(lista_vacia(lista)==true)
        return NULL;
    nodo_t* nodo_a_devolver = lista->nodo_fin;
    return nodo_a_devolver->elemento;
}

bool lista_vacia(lista_t* lista){
    if (!lista || lista->cantidad == 0)
        return true;
    return false;
}

size_t lista_tamanio(lista_t* lista){
    if (lista_vacia(lista) == true)
        return 0;
    return lista->cantidad;
}

void lista_destruir(lista_t* lista){
    if (lista_vacia(lista)==true){
        free(lista);
    }
    else{
        size_t it = 0;
        nodo_t* nodo_actual = lista->nodo_inicio;
        nodo_t* aux = nodo_actual->siguiente;
        while(it < lista->cantidad - 1){
            free(nodo_actual);
            nodo_actual = aux;
            aux = aux->siguiente;
            it++;
        }
        free(aux);
        free(lista->nodo_fin);
        free(lista);
    }
}


//FUNCIONES CON ITERADOR EXTERNO
lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if (!lista)
        return NULL;
    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if (!iterador){
        free(iterador);
        return NULL;
    }
    else{
        iterador->lista = lista;
        iterador->corriente = lista->nodo_inicio;
        return iterador;
    }
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if (!iterador)
        return false;
    if (iterador->corriente != NULL && iterador->corriente->siguiente == NULL){
        return true;
    }
    else if (iterador->corriente == NULL || iterador->corriente->siguiente == NULL)
        return false;
    return true;
    
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if (!iterador)
        return false;
    else if (iterador->corriente != NULL && lista_iterador_tiene_siguiente(iterador)==false){
        iterador->corriente = NULL;
        return false;
    }
    else if (iterador->corriente == NULL){
        return false;
    }
    else if (lista_iterador_tiene_siguiente(iterador)==false){
        return false;
    }
    else if (iterador->corriente->siguiente != NULL){
        iterador->corriente = iterador->corriente->siguiente;
        return true;
    }
    else{
        iterador->corriente = iterador->corriente->siguiente;
        return false;
    }
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if (!iterador || !iterador->corriente){
        return NULL;
    }
    else{
        return iterador->corriente->elemento;
    }
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    if(!iterador)
        return;
    free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if (lista_vacia(lista)==true)
        return 0;
    else if (*funcion == NULL || !contexto){
        return 0;
    }
    else{
        nodo_t* nodo_actual = lista->nodo_inicio;
        size_t iterador = 0;
        while(nodo_actual != NULL && funcion(nodo_actual->elemento, contexto)!= false){
            iterador++;
            nodo_actual = nodo_actual->siguiente;
        }
        return iterador;
    }
}
