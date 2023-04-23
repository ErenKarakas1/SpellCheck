#include <iostream>
#include <string.h>
#include "Trie.h"
using namespace std;

TrieNode::TrieNode(char letter) {
    data = letter;
    is_leaf = false;

    for (int i = 0; i < CHAR_LIMIT; ++i) {
        children[i] = nullptr;
    }
}

Trie::Trie() {
    root = nullptr;
}

Trie::~Trie() {
    destroy_trie(root);
}

void Trie::insert(wstring word) {
    if (root == nullptr) {
        root = new TrieNode('\0');
    }

    TrieNode* curr = root;

    char letter;

    for (int i = 0; i < word.length(); ++i) {
        if (!iswalpha(word[i])) {
            continue;
        }

        letter = towlower(word[i]);
        int pos = (int) (letter - 'a');
        if (curr->children[pos] == nullptr) {
            TrieNode* node = new TrieNode(letter);
            curr->children[pos] = node;
        }

        curr = curr->children[pos];
    }

    curr->is_leaf = true;
}

bool Trie::check_word(char word[]) {
    if (root == nullptr) {
        return false;
    }

    TrieNode* curr = root;

    for (int i = 0; i < strlen(word); ++i) {
        int pos = (int) (word[i] - 'a');
        if (curr->children[pos] == nullptr) {
            return false;
        }

        curr = curr->children[pos];
    }

    return (curr != nullptr && curr->is_leaf);
}

void Trie::print() {
    print_trie(root);
    cout << "DONE" << endl;
}

void Trie::print_trie(TrieNode* node) {
    if (node == nullptr) {
        return;
    }

    if (node->data != '\0') {
        printf("%c -> ", node->data);
    }

    for (int i = 0; i < CHAR_LIMIT; ++i) {
        print_trie(node->children[i]);
    }
}

void Trie::destroy_trie(TrieNode* node) {
    if ( node != nullptr ) {
        for (int i = 0; i < CHAR_LIMIT; ++i) {
            destroy_trie(node->children[i]);
        }

        delete node;
        node = nullptr;
    }
}
