#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 10

typedef struct TrieNode {
    struct TrieNode *children[26];
    int is_end_of_word;
} TrieNode;

TrieNode* create_node() {
    TrieNode *node = (TrieNode*) malloc(sizeof(TrieNode));
    node->is_end_of_word = 0;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert_word(TrieNode *root, const char *word) {
    TrieNode *current = root;
    for (int level = 0; level < strlen(word); level++) {
        int index = tolower(word[level]) - 'a';
        if (!current->children[index]) {
            current->children[index] = create_node();
        }
        current = current->children[index];
    }
    current->is_end_of_word = 1;
}

int search_word(TrieNode *root, const char *word) {
    TrieNode *current = root;
    for (int level = 0; level < strlen(word); level++) {
        int index = tolower(word[level]) - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];
    }
    return current != NULL && current->is_end_of_word;
}

int get_word_length(const char *word) {
    int length = 0;
    while (word[length] != '\0') {
        length++;
    }
    return length;
}

void free_trie(TrieNode *root) {
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            free_trie(root->children[i]);
        }
    }
    free(root);
}

int main() {
    TrieNode *root = create_node();

    // Load dictionary
    FILE *dictionary_file = fopen("dictionary.txt", "r");
    if (!dictionary_file) {
        printf("Error: Unable to open dictionary file.\n");
        return 1;
    }
    char word[MAX_WORD_LENGTH];
    while (fscanf(dictionary_file, "%s", word) != EOF) {
        insert_word(root, word);
    }
    fclose(dictionary_file);


    // Play the game
    char drawn_letters[10];
    printf("Enter 10 letters: ");
    scanf("%s", drawn_letters);

    int max_word_length = 0;
    int max_word_length_count = 0;
    for (int length = 10; length >= 2; length--) {
        for (int i = 0; i <= 10 - length; i++) {
            char substring[MAX_WORD_LENGTH];
            strncpy(substring, drawn_letters + i, length);
            substring[length] = '\0';

            if (search_word(root, substring)) {
                int word_length = get_word_length(substring);
                if (word_length > max_word_length) {
                    max_word_length = word_length;
                    max_word_length_count = 1;
                } else if (word_length == max_word_length) {
                    max_word_length_count++;
                }
            }
        }
    }

    printf("Maximum word length: %d\n", max_word_length);
    printf("Number of %d-letter words: %d\n", max_word_length, max_word_length_count);

    free_trie(root);

    return 0;
}
