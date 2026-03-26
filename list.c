#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// 1. Programe la función List* createList(), la cual retorna el puntero del tipo de dato List con sus valores inicializados en NULL.
// Recuerda reservar memoria al puntero usando malloc o calloc.

List * createList() {
    List * new_list = malloc(sizeof(List));
    assert(new_list != NULL);
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->current = NULL;
    return new_list;
}

// 2. Programe las funciones void * firstList(List * list) y void * nextList(List * list).
//   - La primera retorna el dato del primer nodo de la lista (head) y actualiza el current para que apunte a ese nodo.
//   - La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.

void * firstList(List * list) {
    //assert(list->head != NULL);
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    // Verificar si los punteros son validos
    if ((list->head == NULL) || (list->current == NULL)) return NULL;
    //Verificar si existe next
    if ((list->current->next == NULL)) return NULL;

    list->current = list->current->next;
    
    return list->current->data;
}

// 3. Programe las funciones void * lastList(List * list) y void * prevList(List * list).
//   - La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
//   - La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.

void * lastList(List * list) {
    if ((list->current == NULL) || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

// 4. Programe la función void pushFront(List * list, void * data), la cual agrega un dato al comienzo de la lista.
// Puede utilizar la función Node* createNode(void * data) la cual crea, incializa y retorna un nodo con el dato correspondiente.

void pushFront(List * list, void * data) {
    
    Node * new_node = createNode(data);
    // Verificar la existencia de un head
    if (list->head != NULL){
        //El nuevo nodo y el head se concetan mutuamente
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    } else { //Se inserta el primer elemnto de la lista en caso de esta vacia
        list->head = new_node;
        list->tail = new_node;
    }
    
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}


// 5. Programe la función void pushCurrent(List * list, void* data), la cual agrega un dato a continuación del nodo apuntado por list->current.

void pushCurrent(List * list, void * data) {
    Node * new_node = createNode(data);
    // Verificar si existe current
    if (list->current != NULL){
        //Verificar que exista nodo luego de current
        if (list->current->next != NULL){
            //Se conecta el nodo con el current y el elemente siguiente a este
            new_node->prev = list->current;
            new_node->next = list->current->next;
            new_node->next->prev = new_node;
            new_node->prev->next = new_node;
        } else {
            list->tail = new_node;
            list->current->next = list->tail;
            list->tail->prev = list->current;
        }
        
    } else { // EN CASO DE NO EXISTIR CURRENT
        // Verificar que exista head
        if (list->head != NULL){
            list->current = list->head;

            //Se conecta el nodo con el current y el elemente siguiente a este
            new_node->prev = list->current;
            new_node->next = list->current->next;
            new_node->next->prev = new_node;
            new_node->prev->next = new_node;
        } else {
            // Se asigna el puntero head al nuevo nodo
            list->head = new_node;
            list->current = list->head;
        }
    } //FIN ELSE list->current != NULL
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

// 6. Programe la función void* popCurrent(List * list), la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el dato del nodo eliminado.
// Nota: El current debe quedar apuntando al nodo siguiente del eliminado.

void * popCurrent(List * list) {
    if (list->current == NULL) return NULL;
    
    Node * current_node = list->current;
    
    Node * current_data = list->current->data;

    Node * izq = current_node->prev;
    Node * der = current_node->next;

    // no hay elemento a la izquiera -> current es el head
    if (izq == NULL){
        list->head = der;
    } else {
        izq->next = der;
    } // FIN izq == NULL

    // no hay elemento a la derecha -> current es el tail
    // ¡Recuerda que el next del current sera el nuevo current!
    if (der == NULL){
        list->tail = izq;
        list->current = current_node->next;
    } else {
        der->prev = izq;
        list->current = current_node->next;
    } // FIN izq == NULL

    free(current_node);
    return current_data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}