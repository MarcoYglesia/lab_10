// Name: Marco Yglesia
// Date: April 19th, 2024
// Assignment: Lab 10 - Tries
// Programming Language: C

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie Structure
struct Trie
{
    int isWord;
    struct trie* next[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    // Create the struct, not a word.
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->isWord = 0;

    // Set each pointer to NULLL.
    int i;
    for (i=0; i<26; i++)
        myTree->next[i] = NULL;

    // Return a pointer to the new root.
    return myTree;
}

void insertRec(struct Trie* tree, char word[], int k, int wordlen) {

    // Down to the end, insert the word.
    if (k == wordlen) {
        tree->isWord = 1;
        return;
    }

    // See if the next place to go exists, if not, create it.
    int nextIndex = word[k] - 'a';
    if (tree->next[nextIndex] == NULL)
        tree->next[nextIndex] = createTrie();

    // Insert recursively down the path of this word, advancing one letter.
    insertRec(tree->next[nextIndex], word, k+1, wordlen);

}

// Inserts the word to the trie structure
// Takes in the Trie and the word to be inserted.
void insert(struct Trie *pTrie, char *word)
{
    insertRec(pTrie, word, 0, strlen(word));
}

int numberOfOccurances(char *array[], int size, char *word)
{
    int count = 0;

    for (int i = 0; i < size; i++) {
        // If the current element matches the target, increment count
        if (strcmp(array[i], word) == 0) {
            count++;
        }
    }
    return count;
}

void printWords(char **array, int size) {
    printf("Words in the array:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", array[i]);
    }
}
// Deallocate the trie structure
// Deallocates memory for a given trie
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    int i;
    for (i=0; i<26; i++){
        if (pTrie->next[i] != NULL) {
            deallocateTrie(pTrie->next[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// This function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    // File failed to reead
    if (file == NULL)
    {
        printf("Error opening file \n");
        return 0;
    }

    int num;
    char word[30];

    fscanf(file,"%d \n",&num);

    for (int i = 0 ; i < num ; i++){
        fscanf(file,"%s", word);
        pInWords[i] = strdup(word);
    }

    fclose(file); // Close the file after reading
    return num;
}

int main(void)
{
    // Initialize the trie
    struct Trie* myDictionary = createTrie();


    char *inWords[256];

    // Read the number of the words in the dictionary
    int numWords = readDictionary("/Users/marcoyglesia/Desktop/C Code/COP 3502 CS1/Lab_10/dictionary-1.txt", inWords);

    // Print out words in inWords array
    for (int i=0;i<numWords;++i)
    {
        printf("%s\n", inWords[i]);
    }
    printf("\n\n\n");

    struct Trie *pTrie = createTrie();
    for (int i=0;i<numWords;i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(inWords, numWords, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
