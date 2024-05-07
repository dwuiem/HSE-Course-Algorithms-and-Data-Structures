#include <iostream>
#include <vector>
#include <cmath>

#define DIVIDER '|'

using namespace std;

// Calculating array prefixes for line
vector<size_t> prefixFunction(string line) {
    vector<size_t> result(line.size());
    result[0] = 0;
    size_t k = 0;
    for (int i = 1; i < line.size(); i++) {
        while (k > 0 && line[k] != line[i]) {
            k = result[k - 1];
        }
        if (line[k] == line[i]) {
            k++;
        }
        result[i] = k;
    }
    return result;
}

void log(const vector<size_t>& prefixes, const vector<size_t>& matches, size_t size) {
    cout << "Prefix template: ";
    for (size_t i = 0; i < size; i++) {
        cout << prefixes[i] << " ";
    }
    cout << endl;
    cout << "Prefix function: ";
    for (size_t v : prefixes) {
        cout << v << " ";
    }
    cout << endl;
    cout << "Matches: ";
    for (size_t v : matches) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    string t;
    string s;
    cin >> t >> s;
    vector<size_t> prefixes = prefixFunction(t + DIVIDER + s);
    vector<size_t> matches;
    // Knut-Morris-Pratt algorithm
    for (size_t i = t.size(); i < prefixes.size(); i++) {
        if (prefixes[i] == t.size()) {
            matches.push_back(i - 2 * t.size());
        }
    }
    log(prefixes, matches, t.size());
}

// contest: https://contest.yandex.ru/contest/61772/problems/B/