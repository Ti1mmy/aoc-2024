#include <bits/stdc++.h>

using namespace std;

uint64_t concat(const uint64_t& a, const uint64_t& b) {
    if (b == 0) return a * 10;
    uint64_t temp = b;
    uint64_t multiplier = 1;
    while (temp > 0) {
        multiplier *= 10;
        temp /= 10;
    }
    return a * multiplier + b;
}

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
        // modulo 3 then divide by 3
        // if 2: concat
        // if 1: multiply
        // if 0: add
        // loop from 0 to 2^k - 1
        
        int combination = pow(3, nums.size() - 1) - 1;
        uint64_t eval = nums[0];

        while (combination >= 0) {
            int c = combination;

            for (int i = 1; i < nums.size(); ++i) {
                if (eval > target) break; // optimize

                char op = c % 3; c = c / 3;
                if (op == 1) eval = concat(eval, nums[i]);
                else if (op == 2) eval *= nums[i];
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
