#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "SinglyList.h"
#include "DisjointSet.h"
using namespace std;
struct Edge {
    int v1;
    int v2;
    int weight;
};
struct LinkedListEdge {
	int vertex;
	int weight;

	LinkedListEdge(int v = 0, int w = 0) {
		vertex = v;
		weight = w;
	}

	bool operator==(const LinkedListEdge& other) const {
		return vertex == other.vertex && weight == other.weight;
	}
}; 
class Graph {
private:
	//Nodes number
	int nodes;
	//edgeList
	vector<Edge> edgeList;
	//matrix
	vector<vector<int>> matrix;
	//adjList
	vector<SinglyList<LinkedListEdge>> adj;
	//for Kruskal Project
	bool dfsPath(int current, int target, vector<bool>& visited, vector<int>& path) {
		visited[current] = true;
		path.push_back(current);

		if (current == target) {
			return true;
		}

		SNode<LinkedListEdge>* temp = adj[current].getHead();

		while (temp != nullptr) {
			int next = temp->getData().vertex;

			if (!visited[next]) {
				if (dfsPath(next, target, visited, path)) {
					return true;
				}
			}

			temp = temp->getNext();
		}

		path.pop_back();
		return false;
	}
	bool selfLoopFound = false;
public:
	//constr and destr
	Graph(int n = 0) {
		nodes = n;
		selfLoopFound = false;
		matrix.resize(n + 1, vector<int>(n + 1, -1));
		adj.resize(n + 1);
	}
	~Graph() {
		//vector can handle memory by it self
	}
	//setters and getters
	void setNodes(int n) {
		selfLoopFound = false;
		adj.clear();
		edgeList.clear();
		nodes = n;
		matrix.assign(n + 1, vector<int>(n + 1, -1));
		adj.resize(n + 1);
	}
	int getNodesNumber() const { return nodes; }
	int getWeight(int v1, int v2) const {
		if (v1 < 1 || v2 < 1 || v1 > nodes || v2 > nodes)
			return -1;

		return matrix[v1][v2];
	}
	const vector<Edge>& getEdgeList() const {
		return edgeList;
	}	
	//methods
	bool addEdge(int v1, int v2, int w) {
		if (v1 < 1 || v2 < 1 || v1 > nodes || v2 > nodes) {
			cout << "Invalid edge: node out of range.\n";
			return false;
		}
		if (w == -1) {
			cout << "Invalid weight: -1 is reserved for no edge.\n";
			return false;
		}
		if (matrix[v1][v2] != -1) {
			cout << "Invalid edge: duplicate edge.\n";
			return false;
		}
		if (v1 == v2) {
			cout << "Self-loop detected: (" << v1 << ", " << v2 << "). It creates a cycle.\n";

			edgeList.push_back({ v1, v2, w });

			matrix[v1][v2] = w;

			// Add it only once, because v1 and v2 are the same node.
			// If we add it twice like a normal undirected edge,
			// adj[v1] would contain the same self-loop two times.
			adj[v1].addBack(LinkedListEdge(v1, w));

			selfLoopFound = true;

			return true;
		}

		edgeList.push_back({ v1, v2, w });

		matrix[v1][v2] = w;
		matrix[v2][v1] = w;

		adj[v1].addBack(LinkedListEdge(v2, w));
		adj[v2].addBack(LinkedListEdge(v1, w));

		return true;
	}	
	int degree(int v) const { return adj[v].size(); }
	void highestDegree() {
		int maxDeg = 0;
		for (int i = 1; i <= nodes; i++)
			if (degree(i) > maxDeg)
				maxDeg = degree(i);

		for (int i = 1; i <= nodes; i++)
			if (degree(i) == maxDeg)
				cout << "Vertex " << i 
				<< " degree = "
				<< maxDeg << endl;
	}
	bool isSubgraph(const Graph& B)const {
		if (this->getNodesNumber() > B.getNodesNumber()) return false;
		for (int i = 0; i < edgeList.size(); i++) {

			Edge e = edgeList[i];

			if (B.getWeight(e.v1, e.v2) != e.weight)
				return false;
		}

		return true;
	}	
	bool areEqual(const Graph& B)const {

		if (this->getNodesNumber() != B.getNodesNumber())
			return false;

		for (int i = 1; i <= this->getNodesNumber(); i++)
			for (int j = 1; j <= this->getNodesNumber(); j++)
				if (this->getWeight(i, j) != B.getWeight(i, j))
					return false;

		return true;
	}
	void intersection(const Graph& B) {
		cout << "Intersection edges:\n";
		for (int i = 0; i < edgeList.size(); i++) {

			Edge e = edgeList[i];
			//notice that we sent e.v1 so the vertix are equil
			if (B.getWeight(e.v1, e.v2) == e.weight)
				cout << "(" << e.v1 << "," << e.v2
				<< ") weight = " << e.weight << endl;
		}
	}
	void Union(const Graph& B)const {

		cout << "Union edges:\n";
		//print all A
		for (int i = 0; i < edgeList.size(); i++) {
			Edge e = edgeList[i];

			cout << "(" << e.v1<< "," << e.v2
				<< ") weight = " << e.weight << endl;
		}
		//if the edge not in A, print it from B
		for (int i = 0; i < B.edgeList.size(); i++) {
			Edge e = B.edgeList[i];
			if (getWeight(e.v1, e.v2) == -1)
				cout << "(" << e.v1 << "," << e.v2
				<< ") weight = " << e.weight << endl;
		}
	}	
	//print
	void printFromEdgeList()const {
		cout << "The edges are:\n";

		for (int i = 0; i < edgeList.size(); i++) {
			cout << "Edge (" << edgeList[i].v1 << ","
				<< edgeList[i].v2
				<< ") weight = "
				<< edgeList[i].weight << endl;

			cout << "Edge (" << edgeList[i].v2 << ","
				<< edgeList[i].v1
				<< ") weight = "
				<< edgeList[i].weight << endl;
		}
	}
	void printFromMatrix()const {
		cout << "The edges are:\n";

		for (int i = 1; i <= nodes; i++)
			for (int j = 1; j <= nodes; j++)
				if (matrix[i][j] != -1)
					cout << "Edge (" << i << ","
					<< j << ") weight = "
					<< matrix[i][j] << endl;
	}
	void printFromAdjList() const {

		cout << "The edges are:\n";

		for (int i = 1; i <= nodes; i++) {

			SNode<LinkedListEdge>* temp = adj[i].getHead();

			while (temp != nullptr) {

				cout << "Edge (" << i  << ","
					<< temp->getData().vertex
					<< ") weight = "
					<< temp->getData().weight << endl;

				temp = temp->getNext();
			}
		}
	}
	//for Kruskal Project
	void kruskalMST() {
		vector<Edge> sortedEdges = edgeList;

		sort(sortedEdges.begin(), sortedEdges.end(), [](Edge a, Edge b) {
			return a.weight < b.weight;
			});

		DisjointSet ds(nodes); // in the beginning {1} {2} {3} {4} {5}

		vector<Edge> mstEdges;//to store the minmum and acyclic edges
		int totalWeight = 0;
		int step = 1;

		cout << "The sets:\n";
		cout << "Step" << step << ": ";//Step1: 
		ds.printSets();// {1} {2} {3} {4} and so on ...

		for (int i = 0; i < sortedEdges.size(); i++) {
			Edge e = sortedEdges[i];

			//(1,2) true (2, 3) true (1, 3) false
			if (ds.Union(e.v1, e.v2)) {
				mstEdges.push_back(e);
				totalWeight += e.weight;

				step++;
				cout << "Step" << step << ": ";//step2:
				ds.printSets();//{1, 2} {3} {4} {5}

				if (mstEdges.size() == nodes - 1) { //edges<=v-1
					break;
				}
			}
		}

		cout << "The final parent array: ";
		ds.printParent();//print the value of the indexs

		cout << "The MST edges: ";//the edges that kurskal choose
		for (int i = 0; i < mstEdges.size(); i++) {
			cout << "(" << mstEdges[i].v1 << "," << mstEdges[i].v2 << ")";

			if (i != mstEdges.size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;

		cout << "The weight of the MST is: " << totalWeight << endl;
	}
	int connectedComponents() {
		DisjointSet ds(nodes);//{1} {2} {3} {4} {5}

		for (int i = 0; i < edgeList.size(); i++) {
			ds.Union(edgeList[i].v1, edgeList[i].v2);
		}// merge nodes into the same set if they are connected by an edge

		return ds.countComponents();//after we collected them, we call this for our class
	}
	bool isConnected() {
		return connectedComponents() == 1;
	}
	bool hasCycle() {
		if (selfLoopFound) {
			return true;
		}

		DisjointSet ds(nodes);

		for (int i = 0; i < edgeList.size(); i++) {
			Edge e = edgeList[i];

			if (!ds.Union(e.v1, e.v2)) {
				return true;
			}
		}

		return false;
	}	
	void findPath(int start, int end) {
		if (start < 1 || end < 1 || start > nodes || end > nodes) {
			cout << "Invalid nodes\n";
			return;
		}
		//move in a road if you reach target stop 
		//if not do backtrak and find another road
		vector<bool> visited(nodes + 1, false);
		vector<int> path;

		if (dfsPath(start, end, visited, path)) {
			for (int i = 0; i < path.size(); i++) {
				cout << path[i];

				if (i != path.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else {
			cout << "No path exists\n";
		}
	}
};