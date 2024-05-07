#include <iostream>
#include <limits>

using namespace std;

int getMax(int a, int b, int c) {
    int res = a;
    if (b > res) res = b;
    if (c > res) res = c;
    return res;
}
int getMin(int a, int b, int c) {
    int res = a;
    if (b < res) res = b;
    if (c < res) res = c;
    return res;
}

int solution(int* a, int* b, int* c, int n1, int n2, int n3, int* numbers) {
    int ptr1 = 0;
    int ptr2 = 0;
    int ptr3 = 0;
    int minDifference = getMax(a[0], b[0], c[0]) - getMin(a[0], b[0], c[0]);
    numbers[0] = a[0];
    numbers[1] = b[0];
    numbers[2] = c[0];
    bool flag = false;
    while (!flag) {
        int currentMin = getMin(a[ptr1], b[ptr2], c[ptr3]);
        if (a[ptr1] == currentMin) {
            if (ptr1 == n1 - 1) flag = true;
            while (ptr1 < n1 - 1) {
                ptr1++;
                if (a[ptr1] >= b[ptr2] || a[ptr1] >= c[ptr3]) {
                    break;
                }
            }
        }
        else if (b[ptr2] == currentMin) {
            if (ptr2 == n2 - 1) flag = true;
            while (ptr2 < n2 - 1) {
                ptr2++;
                if (b[ptr2] >= a[ptr1] || b[ptr2] >= c[ptr3]) {
                    break;
                }
            }
        }
        else {
            if (ptr3 == n3 - 1) flag = true;
            while (ptr3 < n3 - 1) {
                ptr3++;
                if (c[ptr3] >= b[ptr2] || c[ptr3] >= a[ptr1]) {
                    break;
                }
            }
        }
        int currentDifference = getMax(a[ptr1], b[ptr2], c[ptr3]) - getMin(a[ptr1], b[ptr2], c[ptr3]);
        if (currentDifference < minDifference) {
            minDifference = currentDifference;
            numbers[0] = a[ptr1];
            numbers[1] = b[ptr2];
            numbers[2] = c[ptr3];
        }
    }
    return minDifference;
}

int main() {
    // Input
    int n1, n2, n3;
    cin >> n1;
    int A[n1];
    for (int i = 0; i < n1; i++) {
        cin >> A[i];
    }
    cin >> n2;
    int B[n2];
    for (int i = 0; i < n2; i++) {
        cin >> B[i];
    }
    cin >> n3;
    int C[n3];
    for (int i = 0; i < n3; i++) {
        cin >> C[i];
    }
    int numbers[3];
    int result = solution(A, B, C, n1, n2, n3, numbers);
    cout << "Numbers = " << numbers[0] << " " << numbers[1] << " " << numbers[2] << endl;
    cout << "Result = " << result;
}

// CONTEST: https://contest.yandex.ru/contest/61483/problems/B/