#include <bits/stdc++.h>

using namespace std;

int compute(const string& mul_string) {
    stringstream a_sstream, b_sstream;
    int a, b;
    int idx = 4; // go past "mul("

    // store a
    while (mul_string[idx] != ',') a_sstream << mul_string[idx++];

    ++idx; // skip comma
    
    // store b
    while (mul_string[idx] != ')') b_sstream << mul_string[idx++];
    // cout << "a: " << a_sstream.str() << " b: " << b_sstream.str() << endl;
    a = stoi(a_sstream.str());
    b = stoi(b_sstream.str());

    return a * b;
}

int main() {
    string input, instr;
    regex const pattern("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");
    int sum = 0;
    bool do_instr = true;
    while (cin >> input) {
        for (sregex_iterator it{input.begin(), input.end(), pattern}, end{}; it != end; ++it) {
            instr = it->str();

            // cout << "Instruction: [" << instr << "]" << endl;

            if (instr == "do()") do_instr = true;
            else if (instr == "don't()") do_instr = false;
            else if (do_instr) sum += compute(instr);
        }
    }
    cout << "Answer: " << sum << endl;
    return 0;
}
