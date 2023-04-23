#include <iostream>
#include <fstream>
#include <set>
#include "Trie.h"
using namespace std;

int main(int argc, char* argv[]) {
    int line_num = 0;

    string dict_path = argv[1];
    wifstream dictionary;
    dictionary.open(dict_path);

    if (!dictionary.is_open()) {
        cerr << "Cannot open " << dict_path << endl;
        exit(-1);
    }
    
    Trie trie;

    wstring word;
    while (dictionary >> word) {
        trie.insert(word);
    }

    dictionary.close();

    // trie.print();

    string file_path;
    if (argc != 3) {
        cout << "Enter a file name: ";
        cin >> file_path;
    }
    else file_path = argv[2];

    wifstream text_file;
    text_file.open(file_path);

    if (!text_file.is_open()) {
        cerr << "Cannot open " << file_path << endl;
        exit(-1);
    }

    int index = 0;
    char dict_string[80];
    wstring file_line;

    set<string> all_words;
    string miss_words = "\nMisspelled word(s):\n";
    int miss_len = miss_words.length();

    while (getline(text_file, file_line)) {
        ++line_num;
        for (char letter : file_line + L'\n') {
            if (isspace(letter)) {
                if (index > 0) {
                    dict_string[index] = '\0';
                    all_words.insert(dict_string);

                    if (!trie.check_word(dict_string)) {
                        miss_words += string(dict_string) + " on line " + to_string(line_num) + '\n';
                    }
                }

                index = 0;
            }
            else if (!iswalpha(letter)) {
                continue;
            }
            else {
                dict_string[index] = towlower(letter);
                ++index;
            }
        }
    }

    cout << "All words in your document: ";

    for (auto word : all_words) {
        cout << word << " ";
    }

    cout << endl;
    
    if (miss_words.length() > miss_len) {
        cout << miss_words;
    }
    
    return 0;
}
