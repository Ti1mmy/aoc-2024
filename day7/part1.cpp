#include <bits/stdc++.h>

using namespace std;

int main() {
    string line;
    uint64_t ans = 0;
    while(getline(cin, line)) {
        stringstream ss{line};
        uint64_t target; ss >> target;

        uint64_t n;
        vector<uint64_t> nums;
        while (ss >> n) {
            nums.emplace_back(n);
        }

        // there's always k = nums.size() - 1 operators. 
        // use k-digit binary number to represent all + or * iterating over every bit
        // if 1: multiply
        // if 0: add
        // loop from 0 to 2^k - 1
        
        int combination = (1 << (nums.size() - 1)) - 1;
        uint64_t eval = nums[0];

        while (combination >= 0) {
            int c = combination;

            for (int i = 1; i < nums.size(); ++i) {
                if (eval > target) break; // optimize

                bool op = c % 2; c = c >> 1; // probably same as doing c = c / 2 to compiler anyway
                if (op) eval *= nums[i];
                else eval += nums[i];
            }
            if (eval == target) {
                ans += eval;
                break;
            }

            --combination; // next combination
            eval = nums[0];
        }
    }
    cout << "Answer: " << ans << endl;
    return 0;
}
