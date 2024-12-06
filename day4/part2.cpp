#include <bits/stdc++.h>

using namespace std;
class Node {
    public:
        char val;
        Node* topleft, *topmid, *topright, *midleft, *midright, *botleft, *botmid, *botright;
        Node(char x) : val(x), topleft(nullptr), topmid(nullptr), topright(nullptr),
               midleft(nullptr), midright(nullptr), botleft(nullptr),
               botmid(nullptr), botright(nullptr) {}
};

int main() {
    vector<vector<Node*>> rows;
    
    string s;
    while (cin >> s) {
        vector<Node*> row;
        for (char x: s) {
            row.emplace_back(new Node(x));
        }
        // cout << endl;
        rows.emplace_back(row);
    }
    int sum = 0;
    // do search this way
    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].size(); ++j) {
            // (i-1,j-1) (i-1,j) (i-1,j+1)
            //  (i,j-1)  [(i,j)]  (i,j+1)
            // (i+1,j-1) (i+1,j) (i+1,j+1)
            Node* n = rows[i][j];

            if ((i > 0) && (j > 0)) n->topleft = rows[i-1][j-1];
            if (i > 0) n->topmid = rows[i-1][j];
            if ((i > 0) && (j+1 < rows[i-1].size())) n->topright = rows[i-1][j+1];
            if (j > 0) n->midleft = rows[i][j-1];
            if (j+1 < rows[i].size()) n->midright = rows[i][j+1];
            if ((i+1 < rows.size()) && (j > 0)) n->botleft = rows[i+1][j-1];
            if (i+1 < rows.size()) n->botmid = rows[i+1][j];
            if ((i+1 < rows.size()) && (j+1 < rows[i+1].size())) n->botright = rows[i+1][j+1];
        }
    }

    // do search now
    // create stack of [node, dir] pair
    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].size(); ++j) {
            // search all 'A' nodes to check if the corners are
            // W X Y'
            // X A X
            // Y X W'
            // where exactly one of W, W' is M, and exactly one of W, W' is S
            //                      Y, Y' is M, and exactly one of Y, Y' is S
            Node* A = rows[i][j];
            if (A->val != 'A') continue;
            else if (!(A->botleft && A->botright && A->topleft && A->topright)) continue;

            Node* W, *Wp, *Y, *Yp;
            W = A->topleft; Wp = A->botright;
            Y = A->botleft; Yp = A->topright;

            // boolean equivalent is W xor Wp is M, W xor Wp is S, symetrically for Y, Yp
            // use !=
            bool W_MAS = ((W->val == 'M') != (Wp->val == 'M')) && ((W->val == 'S') != (Wp->val == 'S'));
            bool Y_MAS = ((Y->val == 'M') != (Yp->val == 'M')) && ((Y->val == 'S') != (Yp->val == 'S'));
            if (W_MAS && Y_MAS) ++sum;
        }
    }

    cout << "Answer: " << sum << endl;

    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].size(); ++j) {
            delete rows[i][j];
        }
    }
}
