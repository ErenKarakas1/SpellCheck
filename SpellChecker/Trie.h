using namespace std;

class Trie;

class TrieParentNode {

public:
    TrieParentNode() {}
    TrieParentNode( char );

private:
    bool leaf, lastLetter;
    string letters;
    TrieParentNode** ptrs;
    friend class Trie;
};

class TrieLeafNode {

public:
    TrieLeafNode() {}
    TrieLeafNode( string );

private:
    bool leaf;
    string word;
    friend class Trie;
};

class Trie {

public:
    Trie() : notFound( -1 ) {}
    Trie( string );

    void printTrie() {
        *prefix = '\0';
        printTrie( 0, root, prefix );
    }

    void insert( string );
    bool wordFound( string );

private:
    TrieParentNode* root;
    const int notFound;
    char prefix[80];

    int position( TrieParentNode*, char );
    void addCell( char, TrieParentNode*, int );
    void createLeaf( char, string, TrieParentNode* );
    void printTrie( int, TrieParentNode*, string );
};
