#include <iostream>
using namespace std;
#include "Graph.h"

int main() {

    Graph A, B;
    int n, m, v1, v2, w;

    cout << "Enter nodes in Graph A: ";
    cin >> n;
    A.setNodes(n);

    cout << "Enter edges in Graph A: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        cout << "Enter edge (u v w): ";
        cin >> v1 >> v2 >> w;
        //i added this yestarday (just to note the user that 0 is not valid and not just skip it).
        if (v1 == 0 || v2 == 0) {
            cout << "Vertex 0 is not valid, edge ignored.\n";
            i--; 
            continue;
        }
        A.addEdge(v1, v2, w);
    }

    cout << "\nEnter nodes in Graph B: ";
    cin >> n;
    B.setNodes(n);

    cout << "Enter edges in Graph B: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        cout << "Enter edge (v1 v2 w): ";
        cin >> v1 >> v2 >> w;
        //i added this yestarday (just to note the user that 0 is not valid and not just skip it).
        if (v1 == 0 || v2 == 0) {
            cout << "Vertex 0 is not valid, edge ignored.\n";
            i--;
            continue;
        }
        B.addEdge(v1, v2, w);
    }

    int choice;

    do {

        cout << "\n1- Output graph A from the array of lists\n";
        cout << "2- Output graph A from the matrix\n";
        cout << "3- Output graph A from the array of structures\n";
        cout << "4- Output graph B from the array of lists\n";
        cout << "5- Output graph B from the matrix\n";
        cout << "6- Output graph B from the array of structures\n";
        cout << "7- The intersection between both graphs\n";
        cout << "8- The union of the two graphs\n";
        cout << "9- Is graph (A) a subgraph of graph (B)?\n";
        cout << "10- Is graph (B) a subgraph of graph (A)?\n";
        cout << "11- Display highest degree from graph A\n";
        cout << "12- Display highest degree from graph B\n";
        cout << "13- Are the graphs equal?\n";
        cout << "14- Exit\n";

        cin >> choice;

        switch (choice) {

        case 1: A.printFromAdjList(); break;
        case 2: A.printFromMatrix(); break;
        case 3: A.printFromEdgeList(); break;

        case 4: B.printFromAdjList(); break;
        case 5: B.printFromMatrix(); break;
        case 6: B.printFromEdgeList(); break;

        case 7: A.intersection(B); break;
        case 8: A.Union(B); break;

        case 9:
            cout << ( A.isSubgraph(B) ? "Yes\n" : "No\n");
            break;

        case 10:
            cout << (B.isSubgraph(A) ? "Yes\n" : "No\n");
            break;

        case 11: A.highestDegree(); break;
        case 12: B.highestDegree(); break;

        case 13:
            cout << (A.areEqual(B) ? "Equal\n" : "Not Equal\n");
            break;

        }

    } while (choice != 14);

    return 0;
}
