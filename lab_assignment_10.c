#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie{
    int flag;
    struct Trie *children[25];
} Trie;


void insert(struct Trie **ppTrie, char *word)
{
    if (*ppTrie == NULL) return;
    int length = strlen(word);
    Trie *temp = *ppTrie;
    for(int i = 0; i < length; i++)
    {
        //Index of char relative to ASCII value of a
        int index = word[i] - 'a';
        //If child node doesn't exist allocate new Trie for node
        if (temp->children[index] == NULL){
            temp->children[index] = (Trie *)calloc(1, sizeof(Trie));        
        }
        //tmp now points to that child node
        temp = temp->children[index];
    }
    //increment flag to indicate word added
    temp->flag++;
}

int numberOfOccurances(struct Trie *pTrie, char *word){
    int len = strlen(word);
    Trie *tmp = pTrie;
    for(int i = 0; i < len; i++)
    {
        //Calculate current character's child's index
        int nextIndex = word[i] - 'a';
        //Word does not exist in structure
        if (tmp->children[nextIndex] == NULL)
            return 0;
        //update tmp to point to child node w char
        tmp = tmp->children[nextIndex];
    }
    //value of num occurrences as per flag
    return tmp->flag;
}

struct Trie *deallocateTrie(struct Trie *pTrie){

    for (int i = 0; i < 26; i++) {
        if(pTrie->children[i] != NULL)
           // Recursive method to free memory of each child note
            deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
    Trie *trie = (Trie *)calloc(1, sizeof(Trie));

    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for(int i = 0; i < 5; i++) insert(&trie, pWords[i]);
    for(int i = 0; i < 5; i++) printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));

    trie = deallocateTrie(trie);

    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}