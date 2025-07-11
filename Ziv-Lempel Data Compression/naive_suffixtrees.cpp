#include "naive_suffixtrees.hpp"

// Constructor implementation
SuffixTree::SuffixTree(string& word) {
    t1 = 0;
    t2 = word.size() + 1;
    root = createSuffixTree(word);
}

// printTree method
void SuffixTree::printTree() {
    _printTree(root);
}

// initializeSuffixTree
Node* SuffixTree::initializeSuffixTree(const string& s){
    Node* nd = new Node();
    Edge* newEdge = new Edge();
    Node* newLeaf = new Node();
    newEdge->child = newLeaf;
    newEdge->parent = nd;
    newEdge->label = s;
    nd->edges.push_back(newEdge);

    nd->num = t1++;
    newLeaf->num = t1++;

    return nd;
}

// iterationCreateSuffixTree
void SuffixTree::iterationCreateSuffixTree(int pos, Node * nd, const string& s){
    if(pos >= s.size()){
        cout << "Not enough length." << endl;
    }

    Node* curr = nd;
    bool need = true;
    for(auto &edge : curr->edges){
        if(edge->label[0] != s[pos]) continue;

        need = false;
        bool flag = true;
        for(int i = 0; pos < s.size() && i < edge->label.size(); i++, pos++){
            if(s[pos] != edge->label[i]){
                // must create a new node and put it in between

                Node* newLeaf = new Node();
                Edge* newEdge1 = new Edge();
                Edge* newEdge2 = new Edge();
                Node* newNode = new Node();
                newEdge1->label = edge->label.substr(i, edge->label.size() - i);
                newEdge1->parent = newNode; newEdge1->child = edge->child;
                edge->child = newNode;
                newEdge2->child = newLeaf; newEdge2->parent = newNode;

                newEdge2->label = s.substr(pos, s.size() - pos);
                newNode->edges.push_back(newEdge1); newNode->edges.push_back(newEdge2);
                edge->label = edge->label.substr(0, i);
                flag = false;

                newLeaf->num = t1++;
                newNode->num = t2++;
            }
        }

        if(flag){
            // prefix matches
            iterationCreateSuffixTree(pos, edge->child, s);
        }
        break;
    }

    if(need){
        Node* newLeaf = new Node();
        Edge* newEdge = new Edge();
        newEdge->child = newLeaf;
        newEdge->parent = nd;
        newEdge->label = s.substr(pos, s.size() - pos);
        nd->edges.push_back(newEdge);
        newLeaf->num = t1++;
    }
}

// _printTree helper
void SuffixTree::_printTree(Node* node) {
    if(node == NULL) return;
    for (auto edge : node->edges) {
        cout << edge->parent->num << " " << edge->label << " " << edge->child->num << endl;
    }
    for(auto edge : node->edges){
        _printTree(edge->child);
    }
}

// createSuffixTree
Node* SuffixTree::createSuffixTree(string& s){
    s += '$';
    Node* root = initializeSuffixTree(s);
    for(int i = 1; i < s.size() - 1; i++){
       iterationCreateSuffixTree(i, root, s);
    }

    findMin(root);

    return root;
}

// findMin
void SuffixTree::findMin(Node* nd) {
    int res = nd->num;
    for(auto edge : nd->edges) {
        auto child = edge->child;

        findMin(child);
        res = min(res, child->mnSuf);
    }

    nd->mnSuf = res;

    if(nd->num == 0)
        nd->mnSuf = 1;
}
