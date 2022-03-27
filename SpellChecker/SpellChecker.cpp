#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include "Trie.h"
using namespace std;

char* turnUppercase( char* node ) {
    char* nodeCounter;

    for ( nodeCounter = node; *node = toupper( *node ); node++ );

    return nodeCounter;
}

int main( int argc, char* argv[] ) {
    char fileName[25], dictString[80], letter;
    int index, lineNum = 1;

    ifstream dictionary( "dictionary" );

    if ( dictionary.fail() ) {
        cerr << "Cannot open 'dictionary'\n";
        exit( -1 );
    }

    dictionary >> dictString;

    Trie trie( turnUppercase( dictString ) );

    while ( dictionary >> dictString ) {
        trie.insert( turnUppercase( dictString ) );
    }

    trie.printTrie();

    if ( argc != 2 ) {
        cout << "Enter a file name: ";
        cin >> fileName;
    }
    else strcpy( fileName, argv[1] );

    ifstream textFile( fileName );

    if ( textFile.fail() ) {
        cout << "Cannot open " << fileName << endl;
        exit( -1 );
    }

    cout << "Misspelled word:\n";

    textFile.get( letter );

    while ( !textFile.eof() ) {
        while ( true ) {
            if ( !textFile.eof() && !isalpha( letter ) ) {
                if ( letter == '\n' ) {
                    lineNum++;
                }

                textFile.get( letter );
            }
            else break;
        }

        if ( textFile.eof() ) {
            break;
        }

        for ( index = 0; !textFile.eof() && isalpha( letter ); index++ ) {
            dictString[index] = toupper( letter );
            textFile.get( letter );
        }

        dictString[index] = '\0';

        if ( !trie.wordFound( dictString ) ) {
            cout << dictString << " on line " << lineNum << endl;
        }
    }

    dictionary.close();
    textFile.close();

    return 0;
}
