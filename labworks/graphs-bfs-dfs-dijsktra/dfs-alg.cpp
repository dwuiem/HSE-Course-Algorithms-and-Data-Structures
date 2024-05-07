#include <iostream>
#include <vector>

using namespace std;

enum Color { WHITE, BLACK};

typedef struct Vertex {
    Color color;
    int parent;
} vertex_t;

class GraphAdjancencyList {
private:
    vector<vertex_t> vertices;
    int count;
public:
    vector<int> hamiltonian;
    vector<vector<int>> list;
    GraphAdjancencyList(int s) {
        list.resize(s*s);
    }
    void addEdge(size_t u, size_t v) {
        int vertex = v;
        list[u].push_back(vertex);
    }
    bool DFS(int n) {
        vertices.resize(list.size());
        clearVerties();
        bool result = false;
        if (vertices[n].color == WHITE) {
            count = 1;
            DFSVisit(n);
//            cout << "---- TOTAL: " << count << " " << vertices.size() << endl;
            if (count == vertices.size()) {
                result = true;
            }
            clearVerties();
        }
        return result;
    }
    void DFSVisit(int u) {
        vertices[u].color = BLACK;
        for (int v : list[u]) {
            if (vertices[v].color == WHITE) {
                int prevCount = count;
                vector<vertex_t> prevVertices = vertices;

                count++;
                vertices[v].parent = u;
                DFSVisit(v);
                if (count != vertices.size()) {
                    count = prevCount;
                    vertices = prevVertices;
                }
                else {
                    hamiltonian.push_back(v);
                }
            }
        }
    }
    void clearVerties() {
        for (int i = 0; i < vertices.size(); i++) {
            vertices[i].color = WHITE;
            vertices[i].parent = -1;
        }
    }
};

typedef struct Cell {
    int x;
    int y;
    bool isExist(int s) {
        return (0 <= x && x <= s - 1 && 0 <= y && y <= s - 1);
    }
} cell_t;

int convertToNumber(int s, cell_t cell) {
    return s * cell.y + cell.x;
}
cell_t getCell(int s, int n) {
    cell_t cell;
    cell.y = n / s;
    cell.x = n % s;
    return cell;
}
vector<cell_t> horseMoves(cell_t c, int s) {
    vector<cell_t> result;
    cell_t t;
    t.x = c.x - 1;
    t.y = c.y - 2;
    if (t.isExist(s)) result.push_back(t);

    t.x = c.x + 1;
    t.y = c.y - 2;
    if (t.isExist(s)) result.push_back(t);

    t.x = c.x - 2;
    t.y = c.y - 1;
    if (t.isExist(s)) result.push_back(t);

    t.x = c.x + 2;
    t.y = c.y - 1;
    if (t.isExist(s)) result.push_back(t);

    t.x = c.x - 2;
    t.y = c.y + 1;
    if (t.isExist(s)) result.push_back(t);

    t.x = c.x + 2;
    t.y = c.y + 1;
    if (t.isExist(s)) result.push_back(t);

    t.x = c.x - 1;
    t.y = c.y + 2;
    if (t.isExist(s)) result.push_back(t);

    t.x = c.x + 1;
    t.y = c.y + 2;
    if (t.isExist(s)) result.push_back(t);

    return result;
}
void printGraph(GraphAdjancencyList graph, int s) {
    cout << "Graph:" << endl;
    for (int u = 0; u < s * s; u++) {
        cout << u << " - ";
        for (int i = 0; i < graph.list[u].size(); i++) {
            cout << graph.list[u][i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int s, x, y;
    cin >> s >> x >> y;
    GraphAdjancencyList graph(s);
    for (int i= 0; i < s * s; i++) {
        cell_t cell = getCell(s, i);
        vector<cell_t> vertices = horseMoves(cell, s);
        for (int v = 0; v < vertices.size(); v++) {
            graph.addEdge(i, convertToNumber(s, vertices[v]));
        }
    }
    printGraph(graph, s);
    cout << "Hamiltonian path:" << endl;
    cell_t c;
    c.x = x;
    c.y = y;
    cell_t horse;
    horse.x = x;
    horse.y = y;
    int n = convertToNumber(s, horse);
    if (graph.DFS(n)) {
        vector<int> result;
        result.resize(graph.hamiltonian.size());
        for (int i = 0; i < graph.hamiltonian.size(); i++) {
            result[graph.hamiltonian[graph.hamiltonian.size() - i - 1]] = i + 1;
        }
        for (int i = 0; i < result.size() + 1; i++) {
            if (i % s == 0 && i != 0) cout << endl;
            cout << result[i] << " ";
        }
    }
    else {
        cout << "No way" << endl;
    }
    return 0;
}
