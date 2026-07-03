#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
class DisjointSet {
private:
    vector<int> parent;

public:
    DisjointSet(int n = 0) {
        parent.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            parent[i] = -1;//makeset(i);
        }
    }

    int FindSet(int x) {
        if (x <= 0 || x >= parent.size()) {
            return -1;
        }
        int r = x;

        while (parent[r] > 0) {
            r = parent[r];
        }

        int s = x;
        while (s != r) {
            int t = s;
            s = parent[s];
            parent[t] = r;
        }

        return r;
    }

    bool Union(int i, int j) {
        int x = FindSet(i);
        int y = FindSet(j);
        if (x == -1 || y == -1) return false;

        if (x == y) {
            return false;
        }

        if (abs(parent[x]) >= abs(parent[y])) {
            parent[x] += parent[y];
            parent[y] = x;
        }
        else {
            parent[y] += parent[x];
            parent[x] = y;
        }

        return true;
    }

    int countComponents() {
        int count = 0;

        for (int i = 1; i < parent.size(); i++) {
            if (parent[i] < 0) {
                count++;
            }
        }

        return count;
    }

    void printParent() const {
        for (int i = 1; i < parent.size(); i++) {
            cout << parent[i];

            if (i != parent.size() - 1) {
                cout << ", ";
            }
        }

        cout << endl;
    }

    void printSets() {
        //but noctice that after we do print
        //if the set was 4->2->1 it will become 4->1 because of FindSet
        for (int i = 1; i < parent.size(); i++) {
            if (parent[i] < 0) { // i is the root
                cout << "{";

                bool first = true;

                for (int j = 1; j < parent.size(); j++) {
                    if (FindSet(j) == i) {
                        if (!first) {
                            cout << ", ";
                        }

                        cout << j;
                        first = false;
                    }
                }

                cout << "} ";
            }
        }

        cout << endl;
    }
};

#endif