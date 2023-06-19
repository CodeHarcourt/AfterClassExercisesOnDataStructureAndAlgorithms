#include<stdio.h>
#include<malloc.h>
#define True 0
#define False -1

typedef int KeyType;
typedef struct node{
    KeyType key;
    struct node* LChild;
    struct node* RChild;
    int bf;
}AVLTNode,*AVLTree;

void InsAVLtree(AVLTree* avlt,KeyType key){
    AVLTNode *S,*A,*B,*C,*p,*FA,*fp;
    S=(AVLTNode*)malloc(sizeof(AVLTNode));
    S->key=key;
    S->LChild=S->RChild=NULL;
    S->bf=0;
    if(*avlt==NULL) *avlt=S;
    else{
        FA=NULL;
        A=*avlt;
        p=*avlt;
        fp=NULL;
        while(p!=NULL){

        }
    }
}