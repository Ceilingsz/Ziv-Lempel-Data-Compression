#include "naive_suffixtrees.hpp"
#include "zl_compress.hpp"
#include <iostream>
using namespace std;


ZivLempelCompression::ZivLempelCompression(string& s) {
    give = s;
    compressedData = compress(give);
}

string ZivLempelCompression::compress(string& data) {
        SuffixTree sTree(data);
        
        string compressedData = "";
        for(int i = 0; i < data.size();) {
            
            pair<int,int> p = findPrior(data, i, sTree.root, 0, i + 1);
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
        
string ZivLempelCompression::decompress(string& data) {
    string s = "";
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == '(') {
            string chck = data.substr(i, data.find(')', i) - i + 1);
            auto [pos, len] = parse(chck);
            for(int j = 0; j < len; j++) {
                s += s[pos + j];
            }
            i = data.find(')', i);
        } else {    
            s += data[i];
        }
    }

    return s;
}
pair<int,int> ZivLempelCompression::findPrior(string& s, int pos, Node* node, int length, int i) {
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


pair<int,int> ZivLempelCompression::parse(string& s) {
    int n = s.size();
    // s[n - 1] == ')' and s[0] = '('
    string ints = s.substr(1, n - 2);
    int p = ints.find(',');
    
    int pos = stoi(ints.substr(0, p));
    int len = stoi(ints.substr(p + 1));

    return {pos - 1, len};
}


