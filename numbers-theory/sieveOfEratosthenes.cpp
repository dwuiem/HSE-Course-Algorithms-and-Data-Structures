#include <iostream>

using namespace std;

int main() {
    int a;
    int b;

    cin >> a;
    cin >> b;

    // Contest output
    cout << "Start and finish: " << a << " " << b << endl;

    size_t size = b + 1;
    int numbers[size];

    // By default, all numbers are prime
    for (int i = 0; i < size; i++) {
        numbers[i] = 1;
    }
    // 0 and 1 are extra
    numbers[0] = 0;
    numbers[1] = 0;

    // Counter of iterations in contest
    int k = 1;

    // The sieve of Eratosthenes algorithm
    for (int i = 2; i * i < size; i++) {
        // If "i" is prime
        if (numbers[i] == 1) {
            int iteration = 0;
            for (int j = i * i; j < size; j += i) {
                if (j >= a && numbers[j] != 0) {
                    iteration = 1;
                    break;
                }
            }
            if (iteration) {
                cout << "Iteration : " << k << endl;
                // Remove multiplies of this number from the sieve
                for (int j = i * i; j < size; j += i) {
                    // If number between borders
                    if (j >= a && numbers[j] != 0) {
                        cout << j << " ";
                    }
                    numbers[j] = 0;  // Not prime if it is multiplie for i
                }
                cout << endl;
            }
            k++;
        }
    }
    int outPrimes = 0;
    for (int i = a; i < size; i++) {
        if (numbers[i] == 1) {
            outPrimes = 1;
            break;
        }
    }
    cout << "Primes : " << endl;
    if (outPrimes) {
        for (int i = a; i < size; i++) {
            if (numbers[i] == 1) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << "No primes" << endl;
    }
    return 0;
}
