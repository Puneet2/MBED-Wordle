//Put your DLL from P2-1 in here
//=================================================================
// Implementation for DLL module.
//
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

//===========================
/* Creating nodes and lists */
//===========================

LLNode* create_llnode(void* data) {
    LLNode* node = (LLNode*)malloc(sizeof(LLNode));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

DLinkedList* create_dlinkedlist(CompareFunction compare) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    newList->compare = compare;
    return newList;
}

//============================
/* Accessing nodes and lists */
//============================

int getSize(DLinkedList* dLinkedList){
    return dLinkedList->size;
}

LLNode* getHead(DLinkedList* dLinkedList){
    return dLinkedList->head;
}

LLNode* getTail(DLinkedList* dLinkedList){
    return dLinkedList->tail;
}

LLNode* getNext(LLNode* node){
    return node->next;
}

LLNode* getPrev(LLNode* node){
    return node->prev;
}

void* getData(LLNode* node){
    return node->data;
}

//============================
/* Inserting nodes into lists */
//============================

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
    if(prev_node != NULL && dLinkedList != NULL && data != NULL){
        LLNode* node = create_llnode(data);
        if(dLinkedList->tail == prev_node){
            node->prev = prev_node;
            prev_node->next = node;
            dLinkedList->tail = prev_node->next;
        }
        else{
            node->next = prev_node->next;
            node->prev = prev_node;
            prev_node->next->prev = node; // this may run into nullpointer
            prev_node->next = node;
        }
        dLinkedList->size++;
    }
    else{
        printf("ERROR: The prev_node was NULL");
    }
}


void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){ 
    if(next_node != NULL && dLinkedList != NULL && data != NULL){
        LLNode* node = create_llnode(data);
        if(dLinkedList->head == next_node){
            node->next = next_node;
            next_node->prev = node;
            dLinkedList->head = next_node->prev;
        }
        else{
            node->prev = next_node->prev;
            node->next = next_node;
            next_node->prev->next = node;
            next_node->prev = node; 
        }
        dLinkedList->size++;
    }
    else{
        printf("ERROR: The prev_node was NULL");
    }
}


void insertHead(DLinkedList* dLinkedList, void* data){
     if(dLinkedList == NULL || data == NULL){
        return;
    }
    if(getSize(dLinkedList) == 0){
        LLNode* node = create_llnode(data);
        dLinkedList->head = node;
        dLinkedList->tail = node;
        dLinkedList->size++;
    }
    else{
        insertBefore(dLinkedList, dLinkedList->head, data);
    }
}

void insertTail(DLinkedList* dLinkedList, void* data){
    if(dLinkedList == NULL || data == NULL){
        return;
    }
    if(getSize(dLinkedList) == 0){
        LLNode* node = create_llnode(data);
        dLinkedList->head = node;
        dLinkedList->tail = node;
        dLinkedList->size++;
    }
    else{
        insertAfter(dLinkedList, dLinkedList->tail, data);
    }
}

//============================
/* Looking up nodes in lists */
//============================

LLNode* findNode(DLinkedList* dLinkedList, void* data){
    if(getSize(dLinkedList) > 0 && data != NULL){
        LLNode* node = dLinkedList->head;
        while(node){
            if(dLinkedList->compare(node->data, data)){
                return node;
            }
            node = node->next;
        }
    }
    return NULL;
}

//===========================
/* Deleting nodes and lists */
//===========================

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
    if(dLinkedList == NULL || getSize(dLinkedList) == 0){
        return; 
    }
    if(Node->next == NULL && Node->prev == NULL && getSize(dLinkedList) == 1){
        dLinkedList->tail = NULL;
        dLinkedList->head = NULL;
        free(Node->data);
        free(Node);
        dLinkedList->size--;
    }
    else if(Node->next == NULL){
        dLinkedList->tail = Node->prev;
        Node->prev->next = NULL;
        Node->prev = NULL;
        dLinkedList->size--;
        free(Node->data);
        free(Node);
    }
    else if(Node->prev == NULL){
        dLinkedList->head = Node->next;
        Node->next->prev = NULL;
        Node->next = NULL;
        dLinkedList->size--;
        free(Node->data);
        free(Node);
    }
    else{
        Node->next->prev = Node->prev;
        Node->prev->next = Node->next;
        Node->prev = NULL;
        Node->next = NULL;
        dLinkedList->size--;
        free(Node->data);
        free(Node);
    }
}


void destroyList(DLinkedList* dLinkedList){
    if(dLinkedList == NULL){
        return;
    }
    if(getSize(dLinkedList) > 0){
        LLNode* node = dLinkedList->head;
        LLNode* temp = node->next;
        while(temp){
            deleteNode(dLinkedList, node);
            node = temp;
            temp = temp->next;
        }
        free(temp);
        free(node->data);
        free(node);
    }
    free(dLinkedList);
}

//==================
/* Reversing lists */
//==================

void reverse(DLinkedList* dLinkedList){
    if(dLinkedList == NULL || getSize(dLinkedList) < 1 ){
        return;
    }
    LLNode* current = dLinkedList->head;
    LLNode* temp = NULL;
    while(current){
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
        temp = dLinkedList->tail;
        dLinkedList->tail = dLinkedList->head;
        dLinkedList->head = temp;
        temp = NULL;
        free(temp);
        current = NULL;
        free(current);
}     