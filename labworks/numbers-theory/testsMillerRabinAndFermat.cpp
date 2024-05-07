#include <iostream>

using namespace std;

// calculate (base ^ exponent) % modulus
int modulareExponentiation(long long int base, long long int exponent, long long int modulus) {
    if (exponent == 0) return 1;
    long long int z = modulareExponentiation(base, exponent / 2, modulus);

    // if exponent is even
    if (exponent % 2 == 0) {
        return (z * z) % modulus;
    }
    // if is odd
    else {
        return base * (z * z) % modulus;
    }
}

// test for a
int MillerRabinTest(int n, int a) {
    // n - 1 = t * 2^s
    int t = (n - 1);
    int s = 1;
    // find t - odd
    while (t % 2 == 0) {
        t = t / 2;
        s++;
    }
    int x = modulareExponentiation(a, t, n);

    // firstCondition
    if (x == 1) {
        return 1;
    }
    // secondCondition
    if (x == n - 1) {
        return 2;
    }

    for (int i = 0; i < s-1; i++) {
        x = (x * x) % n;
        if (x == 1) return 0;

        // secondCondition
        if (x == n - 1) return 2;
    }
    return 0;
}
int FermatTest(int n, int a) {
    // Fermat Condition
    return (modulareExponentiation(a, n - 1, n) == 1);
}

int main() {
    int number;
    cin >> number;

    // test completed or not
    int isPrimeMillerRabin = 1;
    int isPrimeFermat = 1;

    // number of candidates (composite)
    int numberOfCandidatesFermat = 0;
    int numberOfCandidatesMiller = 0;

    // Counters of completed tests
    int numberOfCompletedFermat = 0;
    // 2 different conditions for miller
    int numberOfCompletedMiller1 = 0;
    int numberOfCompletedMiller2 = 0;

    for (int i = 1; i <= number - 1; i++) {
        if (FermatTest(number, i) == 0) {
            isPrimeFermat = 0;
            numberOfCandidatesFermat++;
        }
        else {
            numberOfCompletedFermat++;
        }
        if (MillerRabinTest(number, i) == 0) {
            isPrimeMillerRabin = 0;
            numberOfCandidatesMiller++;
        }
        else if (MillerRabinTest(number, i) == 1) {
            numberOfCompletedMiller1++;
        }
        else {
            numberOfCompletedMiller2++;
        }
    }

    if (isPrimeMillerRabin) {
        cout << "Miller-Rabin test: True "
        << numberOfCandidatesMiller << " "
        << numberOfCompletedMiller1 << " "
        << numberOfCompletedMiller2 << endl;
    }
    else {
        cout << "Miller-Rabin test: False "
             << numberOfCandidatesMiller << " "
             << numberOfCompletedMiller1 << " "
             << numberOfCompletedMiller2 << endl;
    }
    if (isPrimeFermat) {
        cout << "Fermat test: True "
             << numberOfCandidatesFermat << " "
             << numberOfCompletedFermat << endl;
    }
    else {
        cout << "Fermat test: False "
             << numberOfCandidatesFermat << " "
             << numberOfCompletedFermat << endl;
    }

    return 0;
}
