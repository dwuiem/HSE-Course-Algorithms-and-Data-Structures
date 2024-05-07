#include <iostream>
#include <string>
#include <bitset>

#define SIZE 7

using namespace std;

// calculate (base ^ exponent) % modulus

__int128 modulareExponentiation(__int128 base, __int128 exponent, __int128 modulus) {
    __int128 res = 1;
    while (exponent > 0) {
        // if exp is odd
        if (exponent % 2 == 1) {
            res = (res * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return res;
}


// EUCLID ALGORITHM
long long int gcdEuclid(long long int a, long long int b) {
    if (b == 0) return a;
    else return gcdEuclid(b, a % b);
}

// EXTENDED EUCLID ALGORITHM
long long int gcdExtendedEuclid(long long int a, long long int b, long long int *x, long long int*y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    else {
        long long int x1, y1;
        long long int gcd = gcdExtendedEuclid(b, a % b, &x1, &y1);
        *x = y1;
        *y = x1 - (a/b)*y1;
        return gcd;
    }
}

// MODULAR LINEAR SOLVER
// ax = b (mod n), b = 1 and solve exists
long long int modularReverseEquation(long long int a, long long int n) {
    long long int x, y;
    long long int gcd = gcdExtendedEuclid(a, n, &x, &y);
    long long int res = x * (1 / gcd) % n;
    long long int i = 1;
    while (res < 0) {
        res = (res + i*(n/gcd)) % n;
        i++;
    }
    return res;
}

int main() {

    long long int p, q, e_start;

    // Input
    cin >> p;
    cin >> q;
    cin >> e_start;

    long long int n = p * q;

    // euler function
    long long int euler = (p - 1) * (q - 1);

    long long int e, d;

    // e_start must be odd
    if (e_start % 2 == 0) {
        e = e_start += 1;
    } else {
        e = e_start;
    }

    // find e while it become mutually prime with euler function
    while (gcdEuclid(e, euler) != 1) {
        e += 2;
    }

    // d - is reverse for e (mod euler func)
    d = modularReverseEquation(e, euler);

    char line[SIZE];
    cin >> line;

    cout << "Private: "
         << d << " "
         << n << endl;
    cout << "Public: "
         << e << " "
         << n << endl;

    cout << "Initial bytes: ";

    // Concatenate strings to one with binaryRepresentation
    string binaryConcatendated;
    for (int i = 0; line[i] != '\0'; i++) {
        cout << (int)line[i] << " ";
        bitset<8> binary = (int)line[i];
        binaryConcatendated = binaryConcatendated + binary.to_string();
    }
    cout << endl;
    // string bin -> decimal
    long long int M = stoll(binaryConcatendated, 0, 2);

    // encryption = P(M) = M^e (mod n)
    __int128 encryption = modulareExponentiation(M, e, n);
    cout << "Encrypted bytes: ";

    // Bytes array (in reverse order)
    int* encryptionBytes = (int*) malloc(sizeof(int)*SIZE);
    int i = 0;
    while (encryption > 0) {
        encryptionBytes[i] = encryption % 256;
        encryption /= 256;
        i++;
    }
    i--;
    while (i >= 0) {
        cout << encryptionBytes[i] << " ";
        i--;
    }
    cout << endl;

    return 0;
}