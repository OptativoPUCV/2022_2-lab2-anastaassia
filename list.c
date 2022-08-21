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
  List* list = (List* )malloc(sizeof(List));//
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
     return list;
}

void * firstList(List * list) {
  if(list->current == NULL)
    return NULL;
  if(list->current->next == NULL)
    return NULL;
  list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
  if(list->current == NULL)
    return NULL;
  if(list->current->next == NULL)
    return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list->tail == NULL)
    return NULL;
  list->current = list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if(list->current == NULL)
    return NULL;
  if(list->current->prev == NULL)
    return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *newNode = createNode(data);
  if(list->head != NULL){
    list->head->prev = newNode;
    newNode->next = list->head; 
    list->head = newNode;
  }else{
    list->head = newNode;
    list->tail = newNode;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node *newNode = createNode(data);
  if(list->current == list->tail){
    newNode->prev = list->current;
    list->current->next = list->current->next;
    list->tail = newNode;
  }else{
    newNode->prev = list->current;
    newNode->next = list->current->next;
    list->current->next = newNode;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node *current  = list->current;
  void *dato = current-> data;
  if(current == NULL)
    return NULL;
  
  if(list->head == current){
    current->next->prev = NULL;
    list->head = current->next;
    
  }else if(list->tail == current){
    current->prev->next = NULL;
    list->tail = current->prev;
    
  }else{
    current->prev->next = list->current->prev;
    current->next->prev = list->current->next;
  }
  free(current);
  return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}