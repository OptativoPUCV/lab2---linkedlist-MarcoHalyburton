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
    List * nuevaLista = (List *)malloc(sizeof(List));
    if (nuevaLista == NULL) {
        perror("Error: No se pudo asignar memoria para la lista.");
        exit(EXIT_FAILURE);
    }
    
    nuevaLista->head = NULL;
    nuevaLista->tail = NULL;
    nuevaLista->current = NULL;
    
    return nuevaLista;
}

void * firstList(List * list) {
    if (list->head != NULL) {
        list->current = list->head;
        return list->head->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL && list->current->next != NULL) {
        list->current = list->current->next;
        return list->current->data;
    }
    return NULL;
}

void * lastList(List * list) {
    if (list->tail != NULL) {
        list->current = list->tail;
        return list->tail->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list->current != NULL && list->current->prev != NULL) {
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node * newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->current == NULL) {
        pushFront(list, data);
        return;
    }
    Node * newNode = createNode(data);
    if (list->current->next != NULL) {
        newNode->next = list->current->next;
        list->current->next->prev = newNode;
    } else {
        list->tail = newNode;
    }
    newNode->prev = list->current;
    list->current->next = newNode;
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
    if (list->current == NULL) {
        return NULL;
    }
    void * data = list->current->data;
    Node * temp = list->current;
    
    if (list->current->prev != NULL) {
        list->current->prev->next = list->current->next;
    } else {
        list->head = list->current->next;
    }
    if (list->current->next != NULL) {
        list->current->next->prev = list->current->prev;
        list->current = list->current->next;
    } else {
        list->tail = list->current->prev;
        list->current = NULL;
    }
    free(temp);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}