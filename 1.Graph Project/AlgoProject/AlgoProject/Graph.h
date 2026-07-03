#pragma once
#include <vector>
#include <stack>
#include <algorithm>
#include "SinglyList.h"
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
public:
	//constr and destr
	Graph(int n=0) {
		nodes = n;
		matrix.resize(n + 1, vector<int>(n + 1, 0));
		adj.resize(n + 1);
	}
	~Graph() {
		//vector can handle memory by it self
	}
	//setters and getters
	void setNodes(int n) {
		adj.clear();
		edgeList.clear();
		nodes = n;
		matrix.assign(n + 1, vector<int>(n + 1, 0));
		adj.resize(n + 1);
	}
	int getNodesNumber() const { return nodes; }
	int getWeight(int v1, int v2)const {
		//sure we gonna use matrix
		return matrix[v1][v2];
	}
	const vector<Edge>& getEdgeList() const {
		return edgeList;
	}	
	//methods
	void addEdge(int v1, int v2, int w) {
		//n=5 and v1=100 adjList[100] ? erorr
		if (v1 < 1 || v2 < 1 || v1 > nodes || v2 > nodes) return;
		//its addEdge not replace edge
		if (matrix[v1][v2] != 0)
			return;
		//edgeList
		edgeList.push_back({ v1,v2,w });
		//matrix
		matrix[v1][v2] = w;
		matrix[v2][v1] = w;
		//adjList
		adj[v1].addBack(LinkedListEdge(v2, w));
		adj[v2].addBack(LinkedListEdge(v1, w));
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
			if (getWeight(e.v1, e.v2) == 0)
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
				if (matrix[i][j] != 0)
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
	}};