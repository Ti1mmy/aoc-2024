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
    stack<pair<Node*, string>> taskList;
    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].size(); ++j) {
            if (rows[i][j]->val == 'X') taskList.emplace(rows[i][j], "");
        }
    }

    while (!taskList.empty()) {
        auto top = taskList.top();
        Node* top_node = top.first;
        string direction = top.second;
        taskList.pop();

        if (!top_node) continue;

        // this is quite probably the worse code i've ever written
        if (direction.empty() && top_node->val == 'X') {

            if (top_node->botleft && top_node->botleft->val == 'M') taskList.emplace(make_pair(top_node->botleft, "botleft"));
            if (top_node->botmid && top_node->botmid->val == 'M') taskList.emplace(make_pair(top_node->botmid, "botmid"));
            if (top_node->botright && top_node->botright->val == 'M') taskList.emplace(make_pair(top_node->botright, "botright"));
            if (top_node->midleft && top_node->midleft->val == 'M') taskList.emplace(make_pair(top_node->midleft, "midleft"));
            if (top_node->midright && top_node->midright->val == 'M') taskList.emplace(make_pair(top_node->midright, "midright"));
            if (top_node->topleft && top_node->topleft->val == 'M') taskList.emplace(make_pair(top_node->topleft, "topleft"));
            if (top_node->topmid && top_node->topmid->val == 'M') taskList.emplace(make_pair(top_node->topmid, "topmid"));
            if (top_node->topright && top_node->topright->val == 'M') taskList.emplace(make_pair(top_node->topright, "topright"));
        } else if (top_node->val == 'M') {
            if (direction == "botleft" && top_node->botleft && top_node->botleft->val == 'A') taskList.emplace(make_pair(top_node->botleft, "botleft"));
            else if (direction == "botmid" && top_node->botmid && top_node->botmid->val == 'A') taskList.emplace(make_pair(top_node->botmid, "botmid"));
            else if (direction == "botright" && top_node->botright && top_node->botright->val == 'A') taskList.emplace(make_pair(top_node->botright, "botright"));
            else if (direction == "midleft" && top_node->midleft && top_node->midleft->val == 'A') taskList.emplace(make_pair(top_node->midleft, "midleft"));
            else if (direction == "midright" && top_node->midright && top_node->midright->val == 'A') taskList.emplace(make_pair(top_node->midright, "midright"));
            else if (direction == "topleft" && top_node->topleft && top_node->topleft->val == 'A') taskList.emplace(make_pair(top_node->topleft, "topleft"));
            else if (direction == "topmid" && top_node->topmid && top_node->topmid->val == 'A') taskList.emplace(make_pair(top_node->topmid, "topmid"));
            else if (direction == "topright" && top_node->topright && top_node->topright->val == 'A') taskList.emplace(make_pair(top_node->topright, "topright"));
        } else if (top_node->val == 'A') {
            if (direction == "botleft" && top_node->botleft && top_node->botleft->val == 'S') ++sum;
            else if (direction == "botmid" && top_node->botmid && top_node->botmid->val == 'S') ++sum;
            else if (direction == "botright" && top_node->botright && top_node->botright->val == 'S') ++sum;
            else if (direction == "midleft" && top_node->midleft && top_node->midleft->val == 'S') ++sum;
            else if (direction == "midright" && top_node->midright && top_node->midright->val == 'S') ++sum;
            else if (direction == "topleft" && top_node->topleft && top_node->topleft->val == 'S') ++sum;
            else if (direction == "topmid" && top_node->topmid && top_node->topmid->val == 'S') ++sum;
            else if (direction == "topright" && top_node->topright && top_node->topright->val == 'S') ++sum;
        }
    }
    cout << "Answer: " << sum << endl;

    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].size(); ++j) {
            delete rows[i][j];
        }
    }
}
