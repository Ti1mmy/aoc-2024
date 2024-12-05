#include <bits/stdc++.h>
#define DEBUG true
using namespace std;

// less efficient best-case runtime because no chance of ending early (whole report needs to be read)
// but I dont want to implement input seeking.
bool isSafe(vector<int>& report) {

    for (auto x: report) {
        if (DEBUG) cout << x << " ";
    }

    auto difference_array = vector<int>();
    for (int i = 0; i < report.size() - 1; ++i) {
        difference_array.emplace_back(report[i+1] - report[i]);
    }
    if (DEBUG) cout << "| difference array: ";
    for (auto x: difference_array) {
        if (DEBUG) cout << x << " ";
    }

    // need to check if differences are all same sign, and if diffs are all 1 2 or 3
    bool valid = true;
    bool increasing = difference_array[0] > 0;
    int problem_idx = -1;
    for (int i = 0; i < difference_array.size(); ++i) {
        if (abs(difference_array[i]) > 3) valid = false;
        if (increasing && difference_array[i] <= 0) valid = false;
        if (!increasing && difference_array[i] >= 0) valid = false;

        if (!valid) {
            problem_idx = i;
            break;
        }
    }
    if (valid) {
        if (DEBUG) cout << "valid: true" << endl;
        return true;
    }
    // simulate removing head
    valid = true;
    increasing = difference_array[1] > 0;
    for (int i = 1; i < difference_array.size(); ++i) {
        if (abs(difference_array[i]) > 3) valid = false;
        if (increasing && difference_array[i] <= 0) valid = false;
        if (!increasing && difference_array[i] >= 0) valid = false;

        if (!valid) {
            break;
        }
    }
    if (valid) {
        cout << "Valid by removing first" << endl;
        return true;
    }

    // simulate removing tail
    valid = true;
    increasing = difference_array[0] > 0;
    for (int i = 0; i < difference_array.size() - 1; ++i) {
        if (abs(difference_array[i]) > 3) valid = false;
        if (increasing && difference_array[i] <= 0) valid = false;
        if (!increasing && difference_array[i] >= 0) valid = false;

        if (!valid) {
            break;
        }
    }

    if (valid) {
        cout << "Valid by removing last" << endl;
        return true;
    }



    if (DEBUG) cout << "| problem idx: " << problem_idx << " | ";

    // if not remove problem value then fix difference array
    int problem_value = difference_array[problem_idx]; // store problem value
    difference_array.erase(difference_array.begin() + problem_idx); // remove

    if ((problem_idx != 0) && (problem_idx != difference_array.size())) {
        difference_array[problem_idx] += problem_value; // fix difference array if not removing last
    }
    
    if (DEBUG) cout << "fixed: ";
    for (auto x: difference_array) {
        if (DEBUG) cout << x << " ";
    }

    // then check again
    valid = true;
    increasing = difference_array[0] > 0;
    for (int i = 0; i < difference_array.size(); ++i) {
        if (abs(difference_array[i]) > 3) valid = false;
        if (increasing && difference_array[i] <= 0) valid = false;
        if (!increasing && difference_array[i] >= 0) valid = false;

        if (!valid) {
            break;
        }
    }
    if (DEBUG) cout << "| valid: " << valid ? "true" : "false";
    if (DEBUG) cout << endl;
    return valid;
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
