#include "tries.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
struct Node{
  char* data;
  struct Node* left;
  struct Node* right;
  unsigned int height;  
};

struct Node* head; //our head instance

//========================helper functions================================


/**
 * A helper function to actually put our new word in the trie.
 * @param curr: the reference to a Node.
 * @param word: a string buffer
 * @param index: indicates what character to point at. 
 * @return a Node with new data.
*/
struct Node* puthelp(struct Node* curr, char* word, int index) {
    char c = word[index];
   if(curr == NULL){
    curr = (struct Node*)malloc(sizeof(struct Node));
    if(isupper(c)){
        curr->isUppercase = 1;
        c += 32;
        curr->c = c;
    }
    else{
        curr->isUppercase = 0;
        curr->c = c;
    }
    
    curr->center = curr->left = curr->right = NULL;
    if(word[index + 1] == '\0'){
        curr->isEnd = 1;
        return curr;
    }
    else{
        curr->isEnd = 0;
    }
   }
   //if(DEBUGMODE) printf("char c = %c\t curr->c = %c\n",c,curr->c);
    
    
   if(c < curr->c){
    curr->left = puthelp(curr->left,word,index);
   }
   else if(c > curr->c){
    curr->right = puthelp(curr->right,word,index);
   }
   else if(word[index + 1] != '\0'){
    curr->center = puthelp(curr->center,word,index+1);
   }
   else{
    curr->isEnd = 1;
   }
   return curr;
}
/**
 * Helper method for freeing up our memory.
 * @param curr node, which holds reference 
 * to heap allocated node.

*/
void destroy_helper(struct Node* curr){
    if(curr == NULL) return;
    destroy_helper(curr->left);
    destroy_helper(curr->center);
    destroy_helper(curr->right);
    free(curr);
}



/**
 * a helper function to determine if string exists.
 * @param curr: a node reference
 * @param word: a word we're looking for
 * @param index: indicates which character to look at.
*/
#include <ctype.h>

struct Node* get_helper(struct Node* curr, char* word, int index) {
    // Check if current node is NULL
    if (curr == NULL) {
        return NULL;
    }
    
    char c = word[index];

    // Convert c to lowercase for comparison
    if(islower(c) == islower(curr->c)){
    if (isupper(c) && !curr->isUppercase) {
        c = tolower(c);
    }
    else if(!isupper(c) && curr->isUppercase){
        c = toupper(c);
struct Node* head = NULL;
unsigned int max(unsigned int A, unsigned int B){
    return (A > B) ? A : B;
}
unsigned int height(struct Node* curr){
    if(curr == NULL){
        return 0;
    }
    return curr->height;
}
unsigned int getbalance(struct Node* curr){
    if(curr == NULL){
        return 0;
    }
    return height(curr->left) - height(curr->right);
}
static struct Node* nodeconstructor(char* word){
    struct Node* toreturn = malloc(sizeof(struct Node));
    toreturn->data = malloc(strlen(word) + 1); // Allocate memory for the string data
    strcpy(toreturn->data, word); // Copy the string data
    toreturn->height = 1;
    toreturn->left = toreturn->right = NULL;
    printf("Node created: %s\n",toreturn->data);
    return toreturn; // Don't forget to return the constructed node
}
static void tolowercase(char* a){
    for(int i = 0; a[i] != '\0'; i++){
        if(a[i] >= 65 && a[i] < 90){
            a[i] += 32;
        }
    }
}
int slaycmp(char* a, char* b){
    int length = (strlen(a) + 1);
    char* atemp = malloc(sizeof(char) * length);
    strcpy(atemp,a);
    length = strlen(b) + 1;
    char* btemp = malloc(sizeof(char) * length);
    strcpy(btemp,b);
    tolowercase(atemp);
    tolowercase(btemp);
    int decision = strcmp(atemp,btemp);
    free(atemp);
    free(btemp);
    return decision;
}
static struct Node* LRotate(struct Node* curr){
    struct Node* newhead = curr->right;
    struct Node* saveboi = newhead->left;
    newhead->left = curr;
    curr->right = saveboi;
    return newhead; // Return the new root of the subtree
}

static struct Node* RRotate(struct Node* curr){
    struct Node* newhead = curr->left;
    struct Node* saveboi = newhead->right;
    newhead->right = curr;
    curr->left = saveboi;
    return newhead; // Return the new root of the subtree
}

static struct Node* put_helper(struct Node* curr, char* word){
    if(curr == NULL){
        return nodeconstructor(word);
    }
    int decision = slaycmp(word,curr->data);

    if(decision < 0){ //A < B
        curr->left = put_helper(curr->left,word);
    }
    else if(decision > 0){ //A > B
        curr->right = put_helper(curr->right,word);
    }
    else{
        islower(c);
    }

    //printf("char c = %c\t curr->c = %c\n", c, curr->c);

    if (c < curr->c) {
        return get_helper(curr->left, word, index);
    } else if (c > curr->c) {
        return get_helper(curr->right, word, index);
    } else {
        if (word[index + 1] == '\0') {
            // Reached the end of the word
            if (curr->isEnd) {
                return curr; // Found the word
            } else {
                return NULL; // Word not found
            }
        } else {
            // Continue searching in the center subtree
            return get_helper(curr->center, word, index + 1);
        }
    }
}


//========================client functions================================

void put(char* word){
    char buffer[strlen(word) + 1];
    strcpy(buffer,word);
    head = puthelp(head,buffer,0);
}
char* get(char* word){
    char buffer[strlen(word) + 1];
    strcpy(buffer,word);
    struct Node* temp = get_helper(head,buffer,0);
    if(temp != NULL){
        return word;
        free(curr->data);
        curr->data = word;
    }
    curr->height = max(height(curr->left),height(curr->right)) + 1;
    unsigned int balance = getbalance(curr);
    if(balance < -1 && getbalance(curr->right) < 0){ // RR case
        return LRotate(curr);
    }
    else if(balance < -1 && getbalance(curr->right) > 0){ // RL case
        curr->right = RRotate(curr->right);
        return LRotate(curr);
    }
    else if(balance > 1 && getbalance(curr->left) > 0){ // LL case
        return RRotate(curr);
    }
    else if(balance > 1 && getbalance(curr->left) < 0){ // LR case
        curr->left = LRotate(curr->left);
        return RRotate(curr);
    }

    //balancing tree
    //L 
    //R
    return curr;
}
static char* get_helper(struct Node* curr, char* word){
    if(curr == NULL){
        return NULL;
    }
    int decision = slaycmp(word,curr->data);

    if(decision < 0){ //A < B
        return get_helper(curr->left, word); // Call recursively on the left child
    }
    else if(decision > 0){ //A > B
        return get_helper(curr->right, word); // Call recursively on the right child
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
    printf("Destroying at %p\n",head);
    destroy_helper(head);
}
void put(char* word){
    head = put_helper(head,word);
}