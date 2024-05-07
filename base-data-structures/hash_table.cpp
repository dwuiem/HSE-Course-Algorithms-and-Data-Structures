#include <iostream>
#include <string>
#include <cmath>

#define MAX_SIZE 10000

using namespace std;

struct HashNode {
    string key;
    int value;
    bool isEmpty;
    bool wasDeleted;
};
typedef HashNode hash_node_t;

struct HashTable {
    hash_node_t nodesArray[MAX_SIZE];

    // Size of hashtable

    int size;
    int parametr;

    // Constructor

    HashTable(int q, int p) : size(q), parametr(p) {
        for (int i = 0; i < size; i++) {
            nodesArray[i].key = "";
            nodesArray[i].value = 0;
            nodesArray[i].isEmpty = true;
            nodesArray[i].wasDeleted = false;
        }
    };

    // Hash Function polynomial

    int hashFunction(string key) {
        long long int hashSum = 0;
        for (int i = 0; i < key.length(); i++) {
            hashSum += (static_cast<long long int>(key[i]) - static_cast<long long int>('a') + 1) * pow(parametr, i);
        }
        return hashSum % size;
    }

    // Linear Probing

    int putLinearProbing(int index) {
        int start = index;
        while(!nodesArray[index].isEmpty) {
            index++;
            index %= size;
            if (index == start) return -1;
        }
        return index;
    }
    int getFirstHole(int index) {
        while (!nodesArray[index].isEmpty || nodesArray[index].wasDeleted) {
            index++;
            index %= size;
        }
        return index;
    }
    int getLinearProbing(int index, string key) {
        int start = index;
        while(nodesArray[index].isEmpty || nodesArray[index].key != key) {
            index++;
            index %= size;
            if (index == start) return -1;
        }
        return index;
    }
    void put(string key, int value) {

        int hash = hashFunction(key);

        // No collision case
        if (nodesArray[hash].isEmpty) {

            // PUT DATA
            nodesArray[hash].key = key;
            nodesArray[hash].value = value;
            nodesArray[hash].isEmpty = false;

            // OUTPUT
            cout << "key=" << key << " ";
            cout << "hash=" << hash << " ";
            cout << "operation=PUT" << " ";
            cout << "result=inserted" << " ";
            cout << "value=" << value;
            cout << endl;

        }
        // Collision case
        else {
            int index = putLinearProbing(hash);
            if (index != -1) {
                // PUT DATA
                nodesArray[index].key = key;
                nodesArray[index].value = value;
                nodesArray[index].isEmpty = false;

                // OUTPUT
                cout << "key=" << key << " ";
                cout << "hash=" << hash << " ";
                cout << "operation=PUT" << " ";
                cout << "result=collision" << " ";
                cout << "linear_probing=" << index << " ";
                cout << "value=" << value;
                cout << endl;
            }
            // Overflow
            else {
                // OUTPUT
                cout << "key=" << key << " ";
                cout << "hash=" << hash << " ";
                cout << "operation=PUT" << " ";
                cout << "result=overflow";
                cout << endl;
            }
        }
    }
    void get(string key) {
        int hash = hashFunction(key);

        // Keys are equal and node is empty (No Collision)
        if (nodesArray[hash].isEmpty && !nodesArray[hash].wasDeleted) {
            // OUTPUT
            cout << "key=" << key << " ";
            cout << "hash=" << hash << " ";
            cout << "operation=GET" << " ";
            cout << "result=no_key";
            cout << endl;
        }

        // Keys are equal and node is not empty (No Collision)
        else if (nodesArray[hash].key == key && !nodesArray[hash].isEmpty) {
            // OUTPUT
            cout << "key=" << key << " ";
            cout << "hash=" << hash << " ";
            cout << "operation=GET" << " ";
            cout << "result=found" << " ";
            cout << "value=" << nodesArray[hash].value;
            cout << endl;
        }
        // Collision case
        else {
            int firstHole = getFirstHole(hash);
            int index = getLinearProbing(hash, key);
            if (index != -1) {
                cout << "key=" << key << " ";
                cout << "hash=" << hash << " ";
                cout << "operation=GET" << " ";
                cout << "result=collision" << " ";
                cout << "linear_probing=" << index << " ";
                cout << "value=" << nodesArray[index].value;
                cout << endl;
            }
            else {
                cout << "key=" << key << " ";
                cout << "hash=" << hash << " ";
                cout << "operation=GET" << " ";
                cout << "result=collision" << " ";
                cout << "linear_probing=" << firstHole << " ";
                cout << "value=no_key";
                cout << endl;
            }
        }
    }
    void del(string key) {
        int hash = hashFunction(key);

        // Keys are equal and node is empty (No Collision)
        if (nodesArray[hash].isEmpty) {
            // OUTPUT
            cout << "key=" << key << " ";
            cout << "hash=" << hash << " ";
            cout << "operation=DEL" << " ";
            cout << "result=no_key";
            cout << endl;
        }

        // Keys are equal and node is not empty (No Collision)
        else if (nodesArray[hash].key == key && !nodesArray[hash].isEmpty) {
            // Delete node
            nodesArray[hash].isEmpty = true;
            nodesArray[hash].wasDeleted = true;
            nodesArray[hash].key.clear();
            // OUTPUT
            cout << "key=" << key << " ";
            cout << "hash=" << hash << " ";
            cout << "operation=DEL" << " ";
            cout << "result=removed" << " ";
            cout << endl;
        }
        // Collision case
        else {
            int firstHole = getFirstHole(hash);
            int index = getLinearProbing(hash, key);
            if (index != -1) {
                // Delete node
                nodesArray[index].isEmpty = true;
                nodesArray[hash].wasDeleted = true;
                nodesArray[index].key.clear();
                // OUTPUT
                cout << "key=" << key << " ";
                cout << "hash=" << hash << " ";
                cout << "operation=DEL" << " ";
                cout << "result=collision" << " ";
                cout << "linear_probing=" << index << " ";
                cout << "value=removed";
                cout << endl;
            }
            else {
                cout << "key=" << key << " ";
                cout << "hash=" << hash << " ";
                cout << "operation=DEL" << " ";
                cout << "result=collision" << " ";
                cout << "linear_probing=" << firstHole << " ";
                cout << "value=no_key";
                cout << endl;
            }
        }
    }
};

int main() {
    int q, p, n;
    cin >> q >> p >> n;
    HashTable hashTable(q, p);
    for (int i = n; i > 0; i--) {
        string request, key;
        int value;
        cin >> request >> key;
        if (request == "PUT") {
            cin >> value;
            hashTable.put(key, value);
        }
        else if (request == "GET") {
            hashTable.get(key);
        }
        else if (request == "DEL") {
            hashTable.del(key);
        }
    }

    return 0;
}