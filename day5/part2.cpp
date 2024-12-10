#include <bits/stdc++.h>

using namespace std;

int main() {
    int N; cin >> N;
    int X, Y;
    unordered_map<int, unordered_set<int>> rules;
    for (int i = 0; i < N; ++i) {
        cin >> X >> Y;
        rules[X].emplace(Y);
    }
    // cout << X << " " << Y << endl;

    string line;
    getline(cin, line); // clear next line

    long long n, ans=0;
    vector<vector<int>> problematic;
    while (getline(cin, line)) {
        // cout << line << endl;
        vector<int> update;
        istringstream iss(line);
        while (iss >> n) {
            // cout << n << endl;
            update.emplace_back(n);
        }

        // check from left to right
        // check if left update[i] does not conflict with any 
        bool conflict = false;
        for (int i = 0; i < update.size() - 1; ++i) {
            if (conflict) break;
            for (int j = i+1; j < update.size(); ++j) {
                if (conflict) break;

                if (rules[update[j]].find(update[i]) != rules[update[j]].end()) conflict = true;
            }
        }
        if (!conflict) continue;

        unordered_set<int> update_set;
        for (int x: update) update_set.emplace(x);

        // fix [update]

        vector<int> fixed;
        unordered_set<int> added; // O(1) expected lookup
        unordered_map<int, vector<int>> filtered_rules;

        for (int x: update) {
            vector<int> rule;
            for (int y: rules[x]) {
                if (update_set.find(y) != update_set.end()) rule.emplace_back(y);
            }
            filtered_rules[x] = rule;
        }

        while (fixed.size() < update.size()) {
            for (int x: update) {
                if (added.find(x) != added.end()) continue; // already added
                
                bool can_add = true;
                for (int y: filtered_rules[x]) {
                    if (added.find(y) == added.end()) {
                        can_add = false;
                        break;
                    }
                }
                if (can_add) {
                    added.emplace(x);
                    fixed.emplace_back(x);
                }
            }
        }

        cout << "Fixed: " << endl;
        for (int x: fixed) cout << x << " ";
        cout << endl;

        ans += fixed[fixed.size() / 2];
    }
    cout << ans << endl;
    return 0;
}
