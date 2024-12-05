#include <bits/stdc++.h>
using namespace std;

// just do unga bunga solution - remove each element and test
bool isSafe(vector<int>& report) {
    int diff, num_pos, num_neg = 0;
    for (int skipped = 0; skipped < report.size(); ++skipped) {
        auto difference_array = vector<int>();
        auto dampened_report = vector<int>();

        // make copy without skipped element
        for (int i = 0; i < report.size(); ++i) {
            if (i == skipped) continue;
            dampened_report.emplace_back(report[i]);
        }
        
        // create difference array
        for (int i = 0; i < dampened_report.size() - 1; ++i) {
            diff = dampened_report[i+1] - dampened_report[i];
            difference_array.emplace_back(diff);
        }

        // test
        bool valid = true;
        bool increasing = difference_array[0] > 0;
        for (int i = 0; i < difference_array.size(); ++i) {
            if (abs(difference_array[i]) > 3) valid = false;
            else if (increasing && difference_array[i] <= 0) valid = false;
            else if (!increasing && difference_array[i] >= 0) valid = false;

            if (!valid) {
                break;
            }
        }
        if (valid) return true;
    }
    return false; // tried all combinations, none worked
}

int main() { 
    string line;

    int counter = 0;
    int n, safe_reports = 0;
    
    auto report = vector<int>();
    while (getline(cin, line)) {
        istringstream iss(line);
        while (iss >> n) report.emplace_back(n);

        // report full
        if (isSafe(report)) ++safe_reports;
        report.clear();
    }

    cout << "Number of safe reports: " << safe_reports << endl;
    return 0;
}
