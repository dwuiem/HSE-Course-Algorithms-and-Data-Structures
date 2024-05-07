#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

#include <limits>

using namespace std;

long double w(unordered_map<string, pair<long long int, long long int>> cities, string s1, string s2) {
    return sqrt(pow((cities[s2].first - cities[s1].first), 2) + pow((cities[s2].second - cities[s1].second), 2));
}

class Graph {
private:
    unordered_map<string, string> prev;
public:
    unordered_map<string, vector<string>> list;
    Graph(int v) {
        list.reserve(v);
        prev.reserve(v);
    }
    void addEdge(string u, string v) {
        list[u].push_back(v);
    }
    unordered_map<string, long double> dijkstra(string start, unordered_map<string, pair<long long int, long long int>> cities) {
        unordered_map<string, long double> distances;
        distances.reserve(cities.size());
        for (auto city = cities.begin(); city != cities.end(); ++city) {
            distances[city->first] = numeric_limits<long double>::infinity();
            prev[city->first] = "";
        }

        distances[start] = 0;
        priority_queue<pair<long double, string>, vector<pair<long double, string>>, greater<pair<long double, string>>> queue;
        queue.push({0, start});
        while (!queue.empty()) {
            string u = queue.top().second;
            queue.pop();
            for (int i = 0; i < list[u].size(); i++) {
                string v = list[u][i];
                if (distances[v] > distances[u] + w(cities, u, v)) {
                    distances[v] = distances[u] + w(cities, u, v);
                    // previous[v].push_back(u);
                    prev[v] = u;
                    queue.push({distances[v], v});
                }
            }
        }
        return distances;
    }
    void printPaths(string start, string end) {
        vector<string> ans;
        string curr = end;
        while(curr != start) {
            ans.push_back(curr);
            curr = prev[curr];
        }
        ans.push_back(curr);
        for (int i = ans.size() - 1; i >= 0; i--) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    string line;
    int v;
    cin >> v;
    getline(cin, line);
    Graph graph(v);
    unordered_map<string, pair<long long int, long long int>> cities;
    cities.reserve(v);
    for (int i = 0; i < v; i++) {
        getline(cin, line);
        stringstream ss(line);
        string name, neib;
        int x, y;
        ss >> name >> x >> y;
        cities[name] = {x, y};
        while (ss >> neib) {
            graph.addEdge(name, neib);
        }
    }
    getline(cin, line);
    stringstream a(line);
    string start, end;
    a >> start >> end;
    unordered_map<string, long double> distances = graph.dijkstra(start, cities);
    if (distances[end] != numeric_limits<long double>::infinity()) {
        cout << "Path is not greater than " << (long long int)distances[end] + 1 << endl;
        cout << "Path:" << endl;
        graph.printPaths(start, end);
    }
    else {
        cout << "Path:" << endl;
        cout << "No way";
    }
    return 0;
}
