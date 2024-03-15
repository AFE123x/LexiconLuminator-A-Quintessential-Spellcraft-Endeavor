#include "tries.h"
#include<string.h>
#include<stdlib.h>
struct Node{
  char* data;
  struct Node* left;
  struct Node* right;
  unsigned int height;  
};

struct Node* head = NULL;
unsigned int max(unsigned int A, unsigned int B){
    (A > B) ? A : B;
}
unsigned int height(struct Node* curr){
    if(curr == NULL){
        return 0;
    }
    return curr->height;
}
unsigned int getbalance(struct Node* curr){
    return height(curr->left) - height(curr->right);
}
static struct Node* nodeconstructor(char* word){
    struct Node* toreturn = malloc(sizeof(struct Node));
    toreturn->data = word;
    toreturn->height = 1;
}
static void LRotate(struct Node* curr){
    struct Node* newhead = curr->right;
    struct Node* saveboi = curr->right->left;
    newhead->left = curr;
    curr->right = saveboi;
    curr = newhead;
}
static void RRotate(struct Node* curr){
    struct Node* newhead = curr->left;
    struct Node* saveboi = newhead->right;
    newhead->right = curr;
    curr->left = saveboi;
    curr = newhead;
}
static struct Node* put_helper(struct Node* curr, char* word){
    if(curr == NULL){
        return nodeconstructor(word);
    }
    int decision = strcmp(word,curr->data);

    if(decision < 0){ //A < B
        curr->left = put_helper(curr->left,word);
    }
    else if(decision > 0){ //A > B
        curr->right = put_helper(curr->right,word);
    }
    else{
        free(curr->data);
        curr->data = word;
    }
    curr->height = max(height(curr->left),height(curr->right)) + 1;
    unsigned int balance = getbalance(curr);
    if(balance < -1 && getbalance(curr->right) < 0){ //RR case
        LRotate(curr);
    }
    else if(balance < -1 && getbalance(curr->right) > 0){ //RL case
        RRotate(curr->right);
        LRotate(curr);
    }
    else if(balance > 1 && getbalance(curr->left) > 0){ //LL
        RRotate(curr);
    }
    else if(balance > 1 && getbalance(curr->left) < 0){ //LR
        LRotate(curr->left);
        RRotate(curr);
    }
    //balancing tree
    //L 
    //R

}
static char* get_helper(struct Node* curr, char* word){
    if(curr == NULL){
        return NULL;
    }
    int decision = strcmp(word,curr->data);

    if(decision < 0){ //A < B
        curr->left = put_helper(curr->left,word);
    }
    else if(decision > 0){ //A > B
        curr->right = put_helper(curr->right,word);
    }
    else{
        return curr->data;
    }
}
char* get(char* word){
    return get_helper(head,word);
}
char exists(char* word){
    return get(word) != NULL;
}
static void destroy_helper(struct Node* curr){
    if(curr == NULL){
        return;
    }
    destroy_helper(curr->left);
    destroy_helper(curr->right);
    free(curr->data);
    free(curr);
}
void destroy(){
    destroy_helper(head);
}
void put(char* word){
    head = put_helper(head,word);
}