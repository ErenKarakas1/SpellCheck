using namespace std;

#define CHAR_LIMIT 200

class TrieNode {

public:
    TrieNode();
    TrieNode(char);
    TrieNode& operator=(TrieNode& right);

private:
    char data;
    bool is_leaf;
    TrieNode* children[CHAR_LIMIT];
    friend class Trie;
};

class Trie {

public:
    Trie();
    ~Trie();
    void insert(wstring);
    bool check_word(char[]);
    void print();

private:
    TrieNode* root;
    void print_trie(TrieNode* node);
    void destroy_trie(TrieNode* node);
};
