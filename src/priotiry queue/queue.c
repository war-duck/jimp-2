// Ten plik zawiera implementację kolejki priorytetowej

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

// Zwraca true, jeżeli kolejka nie ma elementów
int isEmpty(queue *q){
    return q->head == NULL;
}

// Zainicjowanie kolejki
queue *initQue(){
    queue *newQue = malloc(sizeof *newQue);
    if (newQue != NULL){
        newQue->head = NULL;    
        newQue->tail = NULL;
    }
    return newQue;
}

// Dodaje nowy element do kolejki w odpowiednie miejsce
void addToQue(queue *q, treeNode *tree){
    int prior = tree->count;
    queNode *newNode = malloc(sizeof *newNode); // Nowy element do dodania
    queNode *originalHead = q->head;            // Zapamiętuje początkowy adres początku kolejki
    queNode *prevNode = q->head;                // Zapamiętuje poprzedni element w kolejce (służy w iteracji)
    int hasMoved = 0;                           // Flaga mówiąca, czy przesunęliśmy head
                        // Taki sam efekt można podając równanie prevNode == q->head, ale tak jest przejrzyściej

    if(newNode == NULL)                         // Brak miejsca
        return;
    
    // Inicjowanie nowego elementu
    newNode->prior = prior;
    newNode->value = tree;
    newNode->next = NULL;

    // Jeżeli kolejka jej pusta, to pierwszy element będzie jej głową i końcem
    if(isEmpty(q)){
        q->head = newNode;
        q->tail = newNode;
        return;
    }
    
    // Znajdź element o priority wyższym, niż nowego elementu
    while(q->head->prior < prior){
        
        if(q->head == q->tail){             // Jeżeli doszliśmy do końca kolejki
                q->head->next = newNode;    // Wstaw go na koniec
                q->tail = newNode;
                if(hasMoved == 1)           // Jeżeli zmieniliśmy q->head
                    q->head = originalHead; // Przywróć go do początku
                return;
        }
        prevNode = q->head;                 // Zapisz poprzedni element
        q->head = q->head->next;            // Przejdź dalej
        hasMoved = 1;
    }
    
    // Przypisz kolejny element do newNode, wstaw newNode do kolejki
    newNode->next = q->head;                // Dopisz każdy kolejny element kolejki jako następujące po nowym elemencie
    if(q->head != originalHead)
        prevNode->next = newNode;           // Wstaw nowy element
    else
        q->head = newNode;                  // Wstaw nowy element na początku, jeżeli jego priorytet jest najwyższy (najmniejsza liczba)


    if(hasMoved == 1)
        q->head = originalHead;             // Zwróć q->head na początkowy adres
}