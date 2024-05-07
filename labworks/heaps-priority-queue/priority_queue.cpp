#include <iostream>
#include <vector>

#define MAX_SIZE 10000000
using namespace std;

void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }
typedef struct BinaryHeap {
    vector<int> heap;

    BinaryHeap() {
        this->heap.reserve(MAX_SIZE);
    }

    void extractMax() {
        cout << heap[0] << endl;

        // Heap with 1 element
        if (heap.size() <= 1) {
            heap.pop_back();
            return;
        }

        swap(heap[heap.size() - 1], heap[0]);
        heap.pop_back();

        int i = 0;
        int leftChildIndex = i * 2 + 1;
        int rightChildIndex = i * 2 + 2;
        int maxChildIndex;

        // Check if right child is out of range
        if (rightChildIndex < heap.size()) {
            maxChildIndex = heap[leftChildIndex] > heap[rightChildIndex] ? leftChildIndex : rightChildIndex;
        }
        else {
            maxChildIndex = leftChildIndex;
        }

        // Shift Down while left child is not out of range
        while (heap[maxChildIndex] > heap[i] && leftChildIndex < heap.size()) {
            // Swap parent and child
            swap(heap[i], heap[maxChildIndex]);

            // update values
            i = maxChildIndex;
            leftChildIndex = i * 2 + 1;
            rightChildIndex = i * 2 + 2;
            if (rightChildIndex < heap.size()) {
                maxChildIndex = heap[leftChildIndex] > heap[rightChildIndex] ? leftChildIndex : rightChildIndex;
            } else {
                maxChildIndex = leftChildIndex;
            }
        }
    }
    void insert(int value) {
        heap.push_back(value);
        // Shift up
        for (int i = heap.size() - 1; i > 0; i = (i - 1) / 2) {
            if (heap[i] < heap[(i - 1) / 2]) break;
            else {
                    swap(heap[i], heap[(i - 1) / 2]);
            }
        }
    }


} binary_heap_t;

int main() {

    int n;
    cin >> n;

    binary_heap_t priorityQueue;

    for (int i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "Insert") {
            int value;
            cin >> value;
            priorityQueue.insert(value);
        }
        if (command == "ExtractMax") {
            priorityQueue.extractMax();
        }
    }

    return 0;
}