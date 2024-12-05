#include <bits/stdc++.h>

using namespace std;

int main() {
    Graph wordSearch = Graph();
    vector<vector<Node*>> rows;
    
    string s;
    while (cin >> s) {
        vector<Node*> row;
        for (char x: s) {
            // cout << x;
            Node* n = new Node(x);
            row.emplace_back(n);
            wordSearch.addNode(n);
        }
        // cout << endl;
        rows.emplace_back(row);
    }
}
