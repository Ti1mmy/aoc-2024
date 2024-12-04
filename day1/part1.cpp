#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    bool isLeft = true;
    priority_queue<int> left, right = priority_queue<int>();
    while (cin >> n) {
        if (isLeft) left.emplace(n);
        else right.emplace(n);

        isLeft = !isLeft;
    }

    // pop off and add
    int total_distance = 0;
    while(left.empty() == false) {
        total_distance += abs(left.top() - right.top());
        left.pop();
        right.pop();
    }
    cout << "Total Distance: " << total_distance << endl;
    return 0;
}
