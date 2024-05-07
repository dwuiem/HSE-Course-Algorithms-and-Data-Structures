#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int d = 26;

int modularExponentiation(int a, int b, int q) {
    if (b == 0) return 1;
    else if (b % 2 == 0) {
        int c = modularExponentiation(a, b / 2, q);
        return (c * c) % q;
    } else {
        int c = modularExponentiation(a, b - 1, q);
        return (a * c) % q;
    }
}

// Polynomial hash function
int getHash(const string &line, int q) {
    int result = 0;
    for (char c : line) {
        result = (result * d + c) % q;
    }
    return result;
}

// Log output
void log(const vector<size_t> &matches, const vector<size_t> &spuriousHits) {
    cout << "Matches: ";
    for (size_t value : matches) {
        cout << value << " ";
    }
    cout << endl;
    cout << "Spurious hits: ";
    for (size_t value : spuriousHits) {
        cout << value << " ";
    }
    cout << endl;
}

int main() {
    // Module
    int q;
    // Template and source string
    string P, T;
    cin >> q >> P >> T;
    // h = d ^ (m - 1)
    int h = modularExponentiation(d, P.size() - 1, q);
    // Calculate template hash
    int p = getHash(P, q);
    // Calculate hash of first substr
    string substring = T.substr(0, P.size());
    int t = getHash(substring, q);
    // Results
    vector<size_t> matches;
    vector<size_t> spuriousHits;
    // The Rabin-Karp algorithm
    for (int i = 0; i < T.size() - P.size() + 1; i++) {
        if (t == p) {
            if (substring == P) {
                matches.push_back(i);
            }
            else {
                spuriousHits.push_back(i);
            }
        }
        // Update substring
        substring = T.substr(i + 1, P.size());
        // Recalculation of hash
        t = (d * (t - T[i] * h) + T[i + P.size()]) % q;
        while (t < 0) {
            t += q;
        }
    }
    log(matches, spuriousHits);
    return 0;
}

// contest: https://contest.yandex.ru/contest/61772/problems/A/