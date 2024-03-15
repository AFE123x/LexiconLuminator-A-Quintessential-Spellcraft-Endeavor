/**
 * implementation of tries data structure. This will
 * allow us to find correct spelling for words.
*/
#include "tries.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/**
 * enable debugging mode, which will enable print statements
 * To use, at -DDEBUG to compilation
*/
#ifndef DEBUG

    #define DEBUGMODE 0

#else

    #define DEBUGMODE 1

#endif
/**Our node class, 3 nodes for a three way
 * tries.
*/
struct Node{
    char c;
    char isEnd;
    char isUppercase;
    struct Node* left;
    struct Node* center;
    struct Node* right;
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
   if(DEBUGMODE) printf("char c = %c\t curr->c = %c\n",c,curr->c);
    
    
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
struct Node* get_helper(struct Node* curr, char* word, int index) {
    //65-90 uppercase 97-122 lowercase
    if (curr == NULL) {
        return NULL;
    }
    
    char c = word[index];

    if(DEBUGMODE) printf("char c = %c\t curr->c = %c\n",c,curr->c);
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
    }
    else{
        return NULL;
    }
}
void destroy(){
    destroy_helper(head);
}
char exists(char* word){
    return get(word) != NULL;
}
//====================================troubleshooting===============================================

void printTree(struct Node* root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 5;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%c\n", root->c);

    // Print isEnd flag
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%c\n", root->isEnd);

    // Print left and center children
    printTree(root->center, space);
    printTree(root->left, space);
}

void print(){
    printTree(head,0);
}


// ???????7^. .......:~^^^^^^^~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^!~^^^^^^^^^^~!!!^^^^^^^!~^!!!!!7777777777
// ?????????!^..     .~^^^^^^~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^~!~!!!!!!!!!!77!~~~~~~~^~~!!7~77!!7777777
// ?????????~..:.    :~^^^^^~!^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^~~:~~~~~~~~7!~!!~~~~~~~^~!7!!~!77!?777777
// ???????7!  .~~^:^^~~~~~~~!~^~~~~~~~^~~~~~~:^~~^~~~~~~~^^^~~~~..:^~~^~7!~^^!~^~~~~~!!!777!~777?777777
// ~~~~!!!!~:^~~~~~!~~~~~~~!~:^~~~~~~~~~~~~!^:^^~~~~~~~~~~~~~~~~:...:~!7!~~~~~!~~~~~~!!!!777!!77??7!!!?
// ::....:!~~~~~~~~!~~~~~~~!^:^~~~~~~!~~~~~!^:~^^~~~~~~~~!~~~~~~:.....~!~~~~~~~!~~~~~77~~~!77!?77777?!?
// ^:::::!~~~~~~~~!!~~~~~~!!^^~~~~~~~!~~~~!~^^~~~~~~~~~~~!~~~~~~:..... :~~~~~~~!~~~~~77~~~~7!??77!?7?!?
// ~~~~^~^~~~~~~~~!~~~~~~~!~~~~~~~~~~!~~~~7~~~~~~~~~~~~~~!~~~~~~^........^~~~~~~!~~~~77!~~~!!?777!?7?!?
// 7????!:^~~~~~~~!~~~~~~~!~~~~~~~~~~!~~~!!~~~~~~~~~~~~~~!~~~~~~: ........:~~~~~!!~~~!77~!!77??7?77777?
// ?????^^~~~~!~~~!~~~~~~!!~~~~~!!~~7!~~~!~~~~!~~~~~~~~~~!~~~~~!~::::.......:~~~~!~~~~!777777?7??7??7?7
// ????7:~~~~!!~~!!~~~~~~!~~~~~~!~~~7!~~!7!~~~!~~~~~~~~~~!~~~~^~:::::::.......:~~7~~~~~~!77!777??!77??7
// 77777~~~~~!!~~!!~~~~~~!~~~~~~!~~!!!~~!~~^~~!^^^^^^^^^^!^^^^~~................:!~~~~~~7!7~7777?7~?7?7
// ???J!~~~~~!!~~!!~~~~~~!~~~~~~!~~~~~^~~^~^^~~^^^^^^^^^^!^^^^!~................ ~~~~~~~!777!777??!777?
// ???J!~~~~~!!~~!7~~~~~~!~~~~~!~^~^^~^~^^~^^~~^^^^^^^^^^~^^^^~^.................~~~~~~~~~!77777?777777
// ???J!7~~~~!!~~~7~~~~~~!~~~~^!~^~::^^^^^^^^~^^^^^^^^^^^~^^^~~:.................~~~~~~~~~~??777?77?777
// ???J!7~~~~!!~~~7~~~~~~!~^^^^!^^~.:^^~:^^^^~^:^::^::^:^~:::~~..::... ..    ....~~~~~~~~~~J777777??777
// ???J7?~~~~~7~~~7~~~~~~~!^^^~!^^^.:~^~^~~^^~^:::::::::~^::^~^....:^~!7J7!!~:..:~^^^^^~!~~~!77!77?7777
// ????7?~~~~~7!~~!!~~~!~^!^^^~~^^^..~^~::^::~^:::::::::~^::^~^...~JYJ7!!!!!7!^::^~^^^^!^~~.!77!77?7777
// ????7?~~~~~!!~~!!~~~!~^~^^^~^^^^.^7!?JJ7!^~^:::::::::~:::~~....::. ..........^~!^^^~~^!^.~7?!77?7777
// ??7??J!~~~~!7!~~!~~^~~^^~:^~^~!JJ7?!!!!!~~~^::::::::^~::^!^.................^^!^^^^~:!~~.^??!77?!!!!
// ??????7~~~~~!7~~!!~^^!^^~^:^^~~~..:^^:.^::^~::::::::~^::~~.................^~!^:::~^~~~~.~??!777!!~!
// ??????J!~~~~~77~!!~^^~~:~~:^:^^^...~^:.^^:^^:::::...:.....................^~~~:::~^~!~^.:7?7~?7?!!!!
// ?????JJ?!!!!~~77~!~~^^~^^~^~:~~^...::....................................^~~~^::^!~~:.:^!7?77J7?7!!!
// 77????JJ7~!!~~~77!!~^:^~:^~~:^^:::......................................:~^^:...:^. .!7!77??7?7?77!!
// ~~!77?JJ?7!!!!!!!77!~^:~^:~^:...................................................^.:!JJ!J77?7!?7?????
// !!7777!7?77!!!!!!!7?7~^^~^:....................................................!JJYYY7J77??7?J?YYYYY
// 77??77~^~777!!!!!!!!?7~~~~~:..................................................~YYYYYJJ?7J?YYYY?YJJJJ
// 77??7!~~^~!!!!!!!!!!!!!JYJ?7:.................... ...::::^^:.................!YYYYYYYJJYJ?YJYY?YYJJJ
// 7??7~^:.:.:^~~!!!!!!!7!!JYYYJ^..................^777!!!!!7??:..............:7YY5555YJ??J?JYYYJ?YYYYY
// 7!!~^::...:::~~~!!!!!!7!!JYY5Y7:................:!~^^^^^^:...............^7YY5555YJ????J?J??JJ?YYYYJ
// ~~:...::^^::::^~!777!!77!7YY5YYJ7^............... ....................:!J5YYYYJJJJJJJ?J??J??J?JJYYYJ
// ~.........:^^^...:!!!77?!!JYYYYY5Y?!^..............................:^?Y555YYY???JJJJ??J?JJJJJ?JJYYJJ
// ............:::....:^^^!7!J5JJY5YY55YJ?!~:......................:^~!?5J?JJJ?????JJ???J??????J?J?!^:^
// ...............::....^^~?J55555555Y5555Y77!!!^::............::^~!!~!?!^~7JJ??JYYYYYJ?J??77????!:....
// .................::...!Y5555P555555555?:....!!!!~~~^^^^^:^^~!!!~~~!!~....~?JJY55YYYYJJJ??77J7:.....:
// ..................:^...?555Y555555YYYY~ .::::^!~!!~~!!!!!~!!~^~!!~^:..::..JY55YYJJJJYYYYYY?^........
// .......................:?JYJYYYYYYYYYY7.::.....!~:..:^!~~!^....:~......^.~YYJJJJJYYYYY?777..........
// ......................::..^7J??7????7!!^::.....^......:~!^......::....:^^^~~~!?JYYY?~:...^..........
// ......................^.....^?77!~^:....:^.....:........!.......:^...:^:.......:^!~^.....^:.........
// .....................:^......^:^.........:.....~:..............:~:................^^.....^:.........
// ......................^......^:^...............:^:...... .. ..:^..................^^:....::^........
// :.....................::.....^:^............... ..:^~!7!7?!77!^:..................^^:......^........
// 7......................:^:...:^^.............:~?JY5YJ?7PBB?~7?JYY?!:..............^~.......^........
// PJ!^::.................:^.....^^^.........:75P5J7~:.  ^5GG5^ ..:~7Y557^..........^^^......^:........
// PGGGP5YJ?^.............:^.....:~^:.......^PBJ^......^JGG~JBG?:.....:!YPY~.......:^^.....:^:.........
// GGGBBGGGG5^.............^^.....^^^:......^PB7.....~JGPB5.!BYPP!.......JB5......:^^:....:~:..........
// PPGPYJJ??7^..............:^:....^^^:......!PGJ^.^JGP77B?.~GJ:YGY~..:!5GY^.....^^^:......^^..........