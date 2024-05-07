#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Color {WHITE, GRAY, BLACK};

typedef struct Position {
    int x;
    int y;
    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool isExist(int rows, int columns) {
        return (0 <= x && x <= (columns - 1) && 0 <= y && y <= (rows - 1));
    }
} pos_t;

class GraphAdjancencyList {
public:
    vector<vector<int>> list;
    GraphAdjancencyList(int rows, int cols) {
        list.resize(rows * cols);
    }
    void addEdge(size_t u, size_t v) {
        int vertex = v;
        list[u].push_back(vertex);
    }
    vector<int> BFS(int s, string maze) {
        queue<int> que;
        vector<Color> color(list.size(), WHITE);
        vector<int> distance(list.size(), -1);
        color[s] = GRAY;
        distance[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            if (maze[u] == 'F') {
                return distance;
            }
            for (int i = 0; i < list[u].size(); i++) {
                int v = list[u][i];
                if (color[v] == WHITE) {
                    color[v] = GRAY;
                    distance[v] = distance[u] + 1;
                    que.push(v);
                }
            }
            color[u] = BLACK;
        }
        return distance;
    }
};
pos_t getPos(int number, int columns) {
    pos_t position(number % columns, number / columns);
    return position;
}
int getNumber(pos_t pos, int columns) {
    return columns * pos.y + pos.x;
}
void printMaze(string maze, int columns) {
    cout << "Initial labyrinth:";
    for (int i = 0; i < maze.size(); i++) {
        if (i % columns == 0) cout << endl;
        cout << maze[i];
    }
    cout << endl;
}
void printGraph(GraphAdjancencyList graph, int rows, int cols) {
    cout << "Graph:" << endl;
    for (int u = 0; u < rows * cols; u++) {
        cout << u << " - ";
        if (graph.list[u].size() == 0) {
            cout << "None";
        }
        for (int i = 0; i < graph.list[u].size(); i++) {
            cout << graph.list[u][i] << " ";
        }
        cout << endl;
    }
}
int main() {
    int rows, cols;
    cin >> rows >> cols;
    string maze = "";
    for (int i = 0; i < rows; i++) {
        string line;
        cin >> line;
        maze += line;
    }
    GraphAdjancencyList graph(rows, cols);
    printMaze(maze, cols);

    int s;
    for (int i = 0; i < maze.size(); i++) {
        if (maze[i] == 'S') {
            s = i;
        }
        if (maze[i] != '#') {
            pos_t pos = getPos(i, cols);
            pos_t move(pos.x, pos.y);
            move.x = pos.x;
            move.y = pos.y - 1;
            if (move.isExist(rows, cols)) {
                int number = getNumber(move, cols);
                if (maze[number] != '#') {
                    graph.addEdge(i, number);
                }
            }
            move.x = pos.x - 1;
            move.y = pos.y;
            if (move.isExist(rows, cols)) {
                int number = getNumber(move, cols);
                if (maze[number] != '#') {
                    graph.addEdge(i, number);
                }
            }
            move.x = pos.x + 1;
            move.y = pos.y;
            if (move.isExist(rows, cols)) {
                int number = getNumber(move, cols);
                if (maze[number] != '#') {
                    graph.addEdge(i, number);
                }
            }
            move.x = pos.x;
            move.y = pos.y + 1;
            if (move.isExist(rows, cols)) {
                int number = getNumber(move, cols);
                if (maze[number] != '#') {
                    graph.addEdge(i, number);
                }
            }
        }
    }
    printGraph(graph, rows, cols);
    vector<int> d = graph.BFS(s, maze);
    cout << "BFS result is:" << endl;
    for (int i = 0; i < d.size(); i++) {
        if (i % cols == 0 && i != 0) cout << endl;
        cout << d[i] << " ";
    }
}