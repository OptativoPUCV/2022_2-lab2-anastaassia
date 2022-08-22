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

List * createList() {
  List* list = (List* )malloc(sizeof(List));//se reserva memoria 
  list->head = NULL;//se inicializa la cabezera con NULL
  list->tail = NULL;//se inicialoza la cola con NULL
  list->current = NULL;//se inicializa el dato actual con NULL
     return list;
}

void * firstList(List * list) {
  if(list->current == NULL)
    return NULL;
  if(list->current->next == NULL)
    return NULL;
  list->current = list->head;//se le asigna el valor a la cabezera 
    return list->head->data;//retorna el dato del primer nodo cabezera
}

void * nextList(List * list) {
  if(list->current == NULL)
    return NULL;
  if(list->current->next == NULL)
    return NULL;
  list->current = list->current->next;//se le asigna un valor al dato siguiente del current
  return list->current->data;//retorna el dato siguiente del current
}

void * lastList(List * list) {
  if(list->tail == NULL)
    return NULL;
  list->current = list->tail;//asigna al current al final de lista 
  return list->tail->data;//retorna el dato del final de la lista
}

void * prevList(List * list) {
  if(list->current == NULL)
    return NULL;
  if(list->current->prev == NULL)
    return NULL;
  list->current = list->current->prev;//asigna el current al nodo anterior del mismo 
  return list->current->data;//retorna el dato el current
}

void pushFront(List * list, void * data) {
  Node *newNode = createNode(data);
  if(list->head != NULL){
    list->head->prev = newNode;//el anterior al head se convierte en el nuevo nodo 
    newNode->next = list->head;// el next del nuevo nodo pasa ser el head 
    list->head = newNode;//actualiza el head al nuevo nodo
  }else{
    list->head = newNode;//asigan el head al nuevo nodo
    list->tail = newNode;//asigna el tail al nuevo nodo 
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;//asigna el current al tail
    pushCurrent(list,data);//llama a funcion 
}

void pushCurrent(List * list, void * data) {
  Node *newNode = createNode(data);
  if(list->current == list->tail){
    newNode->prev = list->current;//el anterior del nuevo nodo es igual al current
    list->current->next = newNode;//el siguiente del current es igual al nuevo nodo
    list->tail = newNode;//el tail es igual al nuevo nodo
  }else{
    newNode->prev = list->current;//el anterior del nuevo nodo es igual al current
    newNode->next = list->current->next;//el siguente del nuevo nodo es igual al siguiente del currente
    list->current->next = newNode;//el siguente del current es igual al nuevo nodo
  }
}

void * popFront(List * list) {
    list->current = list->head;//actualiza el currrent al head
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;//actualiza el current al tail
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node *current  = list->current;
  void *dato = current-> data;
  if(current == NULL)
    return NULL;
  
  if(list->head == current){
    current->next->prev = NULL;//el previo del siguente del current se trasforma a null
    list->head = current->next;//el head se trasforma al siguiente del current
    
  }else if(list->tail == current){
    current->prev->next = NULL;//el siguente del previo del current se trasforma a null
    list->tail = current->prev;//el tail se trasforma al previo del current
    
  }else{
    current->prev->next = list->current->next;//actualiza el siguiente del previo del current al siguente del current
    current->next->prev = list->current->prev;//actualiza el previo del siguiente del current al previo del current
  }
  free(current);//se libera la memoria del current
  return dato;//retorna el dato
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}