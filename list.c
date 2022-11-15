#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init(int n, List *L) {
   L->length=n;
   L->head=NULL;
}
int length(List L) {
return L.length;
}

void add(List *L, int c) {
  NodeType *new;
  new=(NodeType *) malloc(sizeof(NodeType));
  new->ch=c;
  new->next=NULL;

  if(L->head == NULL){
     L->head=new;
     L->length++;
  }else{
     NodeType *lastNode = L->head;

     while (lastNode->next != NULL)
     {
            lastNode = lastNode->next;
     }
     lastNode->next = new;
   }
}

int found(List L, int num){
 NodeType *temp;
 temp = L.head;
 while(temp != NULL){
    if((temp->ch) == num){
       return 0;
    }
    temp = temp->next;
 }
 return 1;
}

void print(List L) {
 NodeType *temp;
 temp = L.head;
 printf("CallList:");
 while(temp != NULL){
   switch (temp->ch)
   {
       case 1 ... 9:
          printf(" L0%d", temp->ch);
          break;
       case 10 ... 15:
          printf(" L%d", temp->ch);
          break;
       case 16 ... 30:
          printf(" I%d", temp->ch);
          break;
       case 31 ... 45:
          printf(" N%d", temp->ch);
          break;
       case 46 ... 60:
          printf(" U%d", temp->ch);
          break;
       case 61 ... 75:
          printf(" X%d", temp->ch);
          break;
       default:
          break;
   }
   temp = temp->next;
 }
 printf("\n");
}