#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; bool isLeft = true;
    auto left = unordered_set<int>();
    auto counts = unordered_map<int, int>();
    
    while (cin >> n) {
        if (isLeft) left.emplace(n);
        else counts[n] += 1;
        isLeft = !isLeft;
    }
    int sim_score = 0;
    for (auto x: left) {
        sim_score += x * counts[x];
    }
    
    cout << "Similarity Score: " << sim_score << endl;
    return 0;
}
