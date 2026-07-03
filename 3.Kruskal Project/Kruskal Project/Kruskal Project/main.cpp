#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    int n, m;
    cout << "Enter number of nodes: ";
    cin >> n;
    if (n <= 0 ) {
        cout << "Invalid number of nodes.\n";
        return 0;
    } 
    cout << "Enter number of edges: ";
    cin >> m;
    if (m < 0) {
        cout << "Invalid number of edges.\n";
        return 0;
    }
    int maxEdges = n * (n + 1) / 2;

    if (m > maxEdges) {
        cout << "Invalid: number of edges exceeds maximum possible edges ("
            << maxEdges << ").\n";
        return 0;
    }

    Graph g(n);

    int addedEdges = 0;

    while (addedEdges < m) {
        int u, v, w;

        cout << "Enter edge " << addedEdges + 1 << " (u v w): ";
        cin >> u >> v >> w;

        if (g.addEdge(u, v, w)) {
            addedEdges++;
        }
        else {
            cout << "Please enter this edge again.\n";
        }
    }

    int components = g.connectedComponents();

    if (components == 1) {
        cout << "The graph is connected, it has one connected component.\n";
        g.kruskalMST();
    }
    else {
        cout << "The graph is not connected, it has "
            << components << " connected components.\n";

        cout << "The graph does not have a spanning tree because it is not connected.\n";
    }

    if (g.hasCycle()) {
        cout << "The graph has cycles.\n";
    }
    else {
        cout << "The graph is acyclic.\n";
    }

    int start, end;

    while (true) {
        cout << "Enter two nodes to find a path between them or enter -1 to exit.\n";
        cout << "Input: ";

        cin >> start;

        if (start == -1) {
            cout << "Goodbye!\n";
            break;
        }

        cin >> end;

        if (end == -1) {
            cout << "Goodbye!\n";
            break;
        }

        cout << "Output: ";
        g.findPath(start, end);
    }

    return 0;
}