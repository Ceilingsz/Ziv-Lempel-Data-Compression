#include "naive_suffixtrees.hpp"
#include <iostream>
using namespace std;

pair<int,int> findPrior(string& s, int pos, Node* node, int length, int i) {
    for(auto edge : node->edges) {
        if(edge->label[0] != s[pos])continue;

        Node* child = edge->child;
        int cv = child->mnSuf;
        int curr = 0;
        while(pos < s.size() && curr < edge->label.size() && cv + length < i) {
            if(s[pos] != edge->label[curr]) {
                if(cv >= i)
                    return {-1, -1};

                return {cv, length};
            }
            
            curr++; pos++; length++;
        }
        
        cout << cv << " " << length << " " << i << endl;
        if(cv >= i) {
            return {-1, -1};
        }

        if(!(curr == edge->label.size())) {
            return {cv, length};
        } else {
            pair<int, int> maybe = findPrior(s, pos, child, length, i);
            if(maybe.first != -1 && maybe.second > length)  
                return maybe;
            else 
                return {cv, length};
        } 
    }

    return {-1, -1};
}

string compress(string& data) {
    SuffixTree sTree(data);

    sTree.printTree();

    string compressedData = "";
    for(int i = 0; i < data.size();) {
        
                
        cout << i << " " << data[i] << endl;
        pair<int,int> p = findPrior(data, i, sTree.root, 0, i + 1);
        // cout << p.first << " " << p.second << endl;
        if(p.first == -1) {
            compressedData += data[i];
            i++;
        } else {
            string add = "(" + to_string(p.first) + "," + to_string(p.second) + ")";
            compressedData += add;
            i += p.second;
        }
    }

    return compressedData;
}


int main(){
    string data;
    cin >> data;

    cout << compress(data) << endl;
}