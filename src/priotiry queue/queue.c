#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

int isEmpty(queue *q){
    return q->head == NULL;
}

queue *initQue(){
    queue *newQue = malloc(sizeof *newQue);
    if (newQue != NULL){
        newQue->head = NULL;
        newQue->tail = NULL;
    }
    return newQue;
}

void addToQue(queue *q, int prior, treeNode *tree){
    printf("x");
    queNode *newNode = malloc(sizeof *newNode);
    queNode *originalHead = q->head;
    queNode *prevNode = q->head;
    int i = 0;
    if(newNode == NULL)
        return;
    
    newNode->prior = prior;
    newNode->value = tree;
    newNode->next = NULL;
    if(isEmpty(q)){
        q->head = newNode;
        q->tail = newNode;
        return;
    }
    
    // Znajdź element o niższym numerze (prior) w kolejce
    // Nie działa: jeżeli q->head->next == NULL a q->head->prior < prior, to program dopisze nowNode w złe miejsce
    while(q->head->prior < prior){
        printf("%d", i);
        // jeżeli doszliśmy do końca
        if(q->head == q->tail){
            if(q->head->prior < prior){ // wstaw na koniec
                q->head->next = newNode;
                q->tail = newNode;
                if(i == 1)
                    q->head = originalHead;
                return;
            }
            else{   // wstaw jako przedostatnie
                newNode->next = q->head;
                prevNode->next = newNode;
                if(i == 1)
                    q->head = originalHead;
                return;
            }
        }
        prevNode = q->head;
        q->head = q->head->next;    // Przejdź dalej
        i = 1;
        
    }
    
    // Przypisz kolejny element do newNode, wstaw newNode do kolejki
    newNode->next = q->head;  // tu wyskakuje seg fault (pewnie bo q->head->next nie istnieje bo q->head == NULL)
    if(q->head != originalHead)
    prevNode->next = newNode;
    else
    q->head = newNode;


    if(i == 1)
        q->head = originalHead;
    // if(q->head == originalHead){
    //     return;
    // }



    // Jeżeli newNode jest ostatnim elementem, zapisz to w tail

}