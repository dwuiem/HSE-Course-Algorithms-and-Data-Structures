#include <iostream>

using namespace std;

// Get summary from start index to finish index
int sumInRange(const int *array, int start, int finish) {
    int summary = 0;
    for (int i = start; i <= finish; i++) {
        summary += array[i];
    }
    return summary;
}

// output function
void printInfo(int length, int sum, int start, int finish) {
    cout << "Length = " << length << endl;
    cout << "Sum = " << sum << endl;
    cout << "Start = " << start << endl;
    cout << "Finish = " << finish << endl;
}

int getMax(int a, int b) {
    return a > b ? a : b;
}

void solution(const int *array, int n, int k) {
    //  Use two pointers
    int left = 0;
    int right = 0;

    // Current sum and length
    int sum = 0;
    int length = 0;

    // Results
    int maxSum = 0;
    int minLength = n + 1;
    int start = -1;
    int finish = -1;

    while (right < n) {
        while (sum + array[right] < k) {
            sum += array[right];
            right++;
        }
        sum += array[right];
        while (sum - array[left] >= k) {
            sum -= array[left];
            left++;
        }
        length = right - left + 1;
        if (length < minLength) {
            minLength = length;
            start = left;
            finish = right;
            maxSum = sum;
        }
        else if (length == minLength && sum > maxSum) {
            start = left;
            finish = right;
            maxSum = sum;
        }
        right++;
    }

    printInfo(minLength, maxSum, start, finish);
}

int main() {
    // Input
    int n, k;
    cin >> n >> k;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // My solution
    solution(a, n, k);
    return 0;
}

// https://contest.yandex.ru/contest/61483/problems/B/