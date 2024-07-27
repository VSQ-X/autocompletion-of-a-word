#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;
//string _str;
const int ALPHABET_SIZE = 26;

// Структура узела дерева 
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, string);
bool search(TrieNode*, string);
bool isEmpty(TrieNode*);
void fullfillvec(vector<string>& vec);
TrieNode* remove(TrieNode*, string, int depth = 0);
void autocomplete(TrieNode*, TrieNode*, string&, string, int&, vector<string>&, int jk=-1);
string autocorrect(vector<string>&,string);
TrieNode* moveStartPrefix(TrieNode*, string&);
#endif