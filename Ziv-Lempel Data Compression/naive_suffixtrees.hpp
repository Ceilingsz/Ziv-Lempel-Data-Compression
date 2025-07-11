#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct Node {
    vector<struct Edge *> edges;
    int num;
    int mnSuf;
} Node;

typedef struct Edge {
    struct Node* parent;
    struct Node* child;
    string label;
} Edge;

class SuffixTree {
    public:
        Node* root;
        SuffixTree(string& word);
        void printTree();

    private:
        int t1, t2;
        Node* createSuffixTree(string& s);
        Node* initializeSuffixTree(const string& s);
        void iterationCreateSuffixTree(int pos, Node* root, const string& s);
        void _printTree(Node* node);
        void findMin(Node* nd);
};

#endif