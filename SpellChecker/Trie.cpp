#include <iostream>
#include <string.h>
#include <cstdlib>
#include "Trie.h"
using namespace std;

TrieLeafNode::TrieLeafNode( string suffix ) {
    leaf = true;

    if ( word[0] == 0 ) {
        cerr << "Out of memory.\n";
        exit( -1 );
    }

    word = suffix;
}

TrieParentNode::TrieParentNode( char letter ) {
    ptrs = new TrieParentNode*;
    letters = new char[2];

    if ( ptrs == 0 || letters.empty() ) {
        cerr << "Out of memory.\n";
        exit( 1 );
    }

    leaf = false;
    lastLetter = false;

    *ptrs = 0;
    letters[0] = letter;
    letters[1] = '\0';
}

Trie::Trie( string word ) : notFound( -1 ) {
    root = new TrieParentNode( word[0] );
    createLeaf( word[0], word.substr(1), root );
}

void Trie::printTrie( int depth, TrieParentNode* parent, string prefix ) {
    register int index;

    if ( parent->leaf ) {
        TrieLeafNode *leaf = ( TrieLeafNode* ) parent;

        for ( index = 1; index <= depth; index++ ) {
            cout << "   ";
        }

        cout << " >>" << prefix << "|" << leaf->word << endl;
    }
    else {
        for ( index = parent->letters.size() - 1; index >= 0; index-- ) {
            if ( parent->ptrs[index] != 0 ) {
                prefix[depth] = parent->letters[index];
                prefix[depth + 1] = '\0';
                printTrie( depth + 1, parent->ptrs[index], prefix );
            }
        }

        if ( parent->lastLetter ) {
            prefix[depth] = '\0';

            for ( index = 1; index <= depth + 1; index++ ) {
                cout << "   ";
            }

            cout << ">>>" << prefix << "\n";
        }
    }
}

int Trie::position( TrieParentNode* parent, char letter ) {
    int index;

    for ( index = 0; index < parent->letters.size() && parent->letters[index] != letter; index++ );

    if ( index < parent->letters.size() ) {
        return index;
    }
    else return notFound;
}

bool Trie::wordFound( string word ) {
    TrieParentNode* parent = root;
    TrieLeafNode* leaf;
    int pos;
    int index = 0;

    while ( true ) {
        if ( parent->leaf ) {
            leaf = ( TrieLeafNode* ) parent;

            return word, leaf->word.size() == 0;
        }
        else if ( word[0] == '\0' ) {
            return parent->lastLetter;
        }
        else if ( ( pos = position( parent, word[index] ) ) != notFound && parent->ptrs[pos] != 0 ) {
            parent = parent->ptrs[pos];
            index++;
        }
        else return false;
    }
}

void Trie::addCell( char letter, TrieParentNode* parent, int stop ) {
    int index, length = parent->letters.size();
    string letterList = parent->letters;

    TrieParentNode** temp = parent->ptrs;
    parent->letters = new char[length + 2];
    parent->ptrs = new TrieParentNode*[length + 1];

    if ( parent->letters.empty() || parent->ptrs == 0 ) {
        cerr << "Out of memory.\n";
        exit(1);
    }

    for ( index = 0; index < length + 1; index++ ) {
        parent->ptrs[index] = 0;
    }

    if ( stop < length ) {
        for ( index = length; index >= stop + 1; index-- ) {
            parent->ptrs[index] = temp[index - 1];
            parent->letters[index] = letterList[index - 1];
        }
    }

    parent->letters[stop] = letter;

    for ( index = stop - 1; index >= 0; index-- ) {
        parent->ptrs[index] = temp[index];
        parent->letters[index] = letterList[index];
    }

    parent->letters[length + 1] = '\0';
}

void Trie::createLeaf( char letter, string suffix, TrieParentNode* parent ) {
    int pos = position( parent, letter );

    if ( pos == notFound ) {
        for ( pos = 0; pos < parent->letters.size() && parent->letters[pos] < letter; pos++ ) {
            addCell( letter, parent, pos );
        }
    }

    parent->ptrs[pos] = ( TrieParentNode* ) new TrieLeafNode( suffix );
}

void Trie::insert( string word ) {
    TrieParentNode* parent = root;
    TrieLeafNode* leaf;

    int offset, pos;
    int index = 0;
    string hold = word;

    while ( true ) {
        if ( word[0] == '\0' ) {
            if ( parent->lastLetter ) {
                cout << "Duplicate entry " << hold << endl;
            }
            else parent->lastLetter = true;
            return;
        }

        pos = position( parent, word[0] );

        if ( pos == notFound ) {
            createLeaf( word[0], word.substr(1), parent );
            return;
        }
        else if ( pos != notFound && parent->ptrs[pos]->leaf ) {
            leaf = ( TrieLeafNode* ) parent->ptrs[pos];

            if ( leaf->word == word.substr(1) ) {
                cout << "Duplicate entry " << hold << endl;
                return;
            }

            offset = 0;
            
            do {
                pos = position( parent, word[offset] );

                if ( word.size() == offset + 1 ) {
                    parent->ptrs[pos] = new TrieParentNode( word[offset] );
                    parent->ptrs[pos]->lastLetter = true;

                    createLeaf( leaf->word[offset], word.substr(index + offset + 1), parent->ptrs[pos] );
                    return;
                }
                else if ( leaf->word.size() == offset ) {
                    parent->ptrs[pos] = new TrieParentNode( word[offset + 1] );
                    parent->ptrs[pos]->lastLetter = true;

                    createLeaf( word[index + offset + 1], word.substr(index + offset + 2), parent->ptrs[pos] );
                    return;
                }

                parent->ptrs[pos] = new TrieParentNode( word[index + offset + 1] );
                parent = parent->ptrs[pos];
                offset++;
            } 
            while ( word[index + offset] == leaf->word[index + offset - 1] );

            offset--;

            string node = "";

            if ( node.size() > offset + 2 ) {
                node = word[index + offset + 2];
            }

            createLeaf( word[index + offset + 1], node, parent );

            if ( leaf->word.size() > offset + 1 ) {
                node = leaf->word[index + offset + 1];
            }
            else node = "";

            createLeaf( leaf->word[index + offset], node, parent );

            delete leaf;
            return;
        }
        else {
            parent = parent->ptrs[pos];
            index++;
        }
    }
}
