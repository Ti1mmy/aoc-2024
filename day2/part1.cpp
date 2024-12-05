#include <bits/stdc++.h>

using namespace std;

// less efficient best-case runtime because no chance of ending early (whole report needs to be read)
// but I dont want to implement input seeking.
bool isSafe(vector<int>& report) {
    // for (auto x: report) {
    //     cout << x << " ";
    // }
    // cout << endl;
    bool increasing = (report[1] - report[0]) > 0;

    for (int i = 0; i < report.size() - 1; ++i) {
        // check if strictly increasing or decreasing
        if (increasing && report[i+1] - report[i] < 0) return false;
        else if (!increasing && report[i+1] - report[i] > 0) return false;
    }

    for (int i = 0; i < report.size() - 1; ++i) {
        // check if differences are strictly within 3
        int difference = abs(report[i] - report[i+1]);
        if ((difference > 3) || (difference == 0)) return false;
    }
    // cout << "Safe!" << endl;
    return true;
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
