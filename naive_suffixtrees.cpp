#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int t = 0;
typedef struct Node {
    vector<struct Edge *> edges;
    int num;
} Node;

typedef struct Edge {
    struct Node* parent;
    struct Node* child;
    string label;
} Edge;

class SuffixTree {
public:
    Node* root;

    SuffixTree(string& word) {
        root = Create_Suffix_Tree(word);
    }
    // Function to create the initial tree N_0 (consisting of only one edge)
    Node* Initialize_Suffix_Tree(const string& s){
        Node* root = new Node();
        Edge* newEdge = new Edge();
        Node* newLeaf = new Node();
        newEdge->child = newLeaf;
        newEdge->parent = root;
        newEdge->label = s;
        root->edges.push_back(newEdge);

        root->num = t++;
        newLeaf->num = t++;

        return root;
    }

    //Create tree iteratively for each suffix. Function to return tree after each iteration.
    Node* Iteration_Create_Suffix_Tree(int pos, Node * root, const string& s){
        if(pos >= s.size()){
            cout << "Not enough length." << endl;
            return NULL;
        }

        Node* curr = root;
        bool need = true;
        for(auto &edge : curr->edges){
            if(edge->label[0] != s[pos])continue;

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

                    newLeaf->num = t++;
                    newNode->num = t++;
                    return root;
                }
            }


            if(flag){
                // prefix matches
                root = Iteration_Create_Suffix_Tree(pos, root, s);
            }
            break;
        }

        if(need){
            Node* newLeaf = new Node();
            Edge* newEdge = new Edge();
            newEdge->child = newLeaf;
            newEdge->parent = root;
            newEdge->label = s.substr(pos, s.size() - pos);
            root->edges.push_back(newEdge);
            newLeaf->num = t++;
            return root;
        }

        return root;
    }
    void _printTree(Node* node) {
        if(node == NULL) return;   
        for (auto edge : node->edges) {
            cout << edge->parent->num << " " << edge->label << " " << edge->child->num << endl;
        }
        for(auto edge : node->edges){
            _printTree(edge->child);
        }
    }

    void printTree() {
        _printTree(root);
    }

    Node* Create_Suffix_Tree(string& s){
        s += '$';
        Node* root = Initialize_Suffix_Tree(s);
        for(int i = 1; i < s.size() - 1; i++){
            root = Iteration_Create_Suffix_Tree(i, root, s);
        }
        return root;
    }
};

int main() {
    string s = "";
    SuffixTree sTree(s);
    sTree.printTree();

    return 0;
}