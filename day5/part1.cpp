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
        if (!conflict) ans += update[update.size() / 2] ;
        
    }
    cout << ans << endl;
    return 0;
}
