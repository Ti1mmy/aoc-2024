#include <bits/stdc++.h>

using namespace std;

class Node {
    public:
        char val;
        unordered_set<Node*> neighbours; // avoid duplicates
        Node(char x) : val(x) {}
};

class Graph {
    private:
    vector<Node*> nodes;
    public:
    ~Graph() {
        for (Node* node: nodes) delete node;
    }
    void addNode(Node* node) {
        nodes.emplace_back(node);
    }
    void addEdge(Node* from, Node* to) {
        // undirected graph
        from->neighbours.emplace(to);
        to->neighbours.emplace(from);
    }

    int count_xmas() {
        // use stack implementation to avoid recursion
        int sum = 0;
        stack<Node*> nodeStack = stack<Node*>();

        for (Node* n: nodes) {
            if (n->val == 'X') nodeStack.emplace(n);
        }


        // this approach wont work because it doesnt preserve directionality
        // must keep only searching in one direction.
        while (!nodeStack.empty()) {
            Node* n = nodeStack.top();
            nodeStack.pop();

            for (Node* next: n->neighbours) {
                if (n->val == 'X' && next->val == 'M') nodeStack.emplace(next);
                if (n->val == 'M' && next->val == 'A') nodeStack.emplace(next);
                if (n->val == 'A' && next->val == 'S') ++sum;
            }
        }
        return sum;
    }

    void print() {
        for (auto n: nodes) cout << n->val << endl;
    }
};

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

    // add neighbours
    for (int i = 1; i < rows.size() - 1; ++i) {
        for (int j = 1; j < rows[i].size() - 1; ++j) {
            // we need to add all of these relevant nodes (impl uses unordered_set so dw bout dupes)
            // (i-1,j-1) (i-1,j) (i-1,j+1)
            //  (i,j-1)  [(i,j)]  (i,j+1)
            // (i+1,j-1) (i+1,j) (i+1,j+1)

            Node* center = rows[i][j];

            wordSearch.addEdge(center, rows[i-1][j-1]);
            wordSearch.addEdge(center, rows[i-1][j]);
            wordSearch.addEdge(center, rows[i-1][j+1]);

            wordSearch.addEdge(center, rows[i][j-1]);
            wordSearch.addEdge(center, rows[i][j+1]);

            wordSearch.addEdge(center, rows[i+1][j-1]);
            wordSearch.addEdge(center, rows[i+1][j]);
            wordSearch.addEdge(center, rows[i+1][j+1]);
        }
    }

    // now all that's left is to connect the nodes around the edges since we skipped them
    // top/bottom edge
    for (int i = 0; i < rows[0].size() - 1; ++i) {
        wordSearch.addEdge(rows[0][i], rows[0][i+1]);
        wordSearch.addEdge(rows[rows.size()-1][i], rows[rows.size()-1][i+1]);
    }
    // left/right edge
    for (int i = 0; i < rows.size() - 1; ++i) {
        wordSearch.addEdge(rows[i][0], rows[i+1][0]);
        wordSearch.addEdge(rows[i][rows[i].size()-1], rows[i+1][rows[i].size()-1]);
    }

    // wordSearch.print();
    cout << "XMAS Occurrences: " << wordSearch.count_xmas() << endl;
    return 0;
}
