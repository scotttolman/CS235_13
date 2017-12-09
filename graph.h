#ifndef GRAPH_H
#define GRAPH_H

#include "set.h"
#include "list.h"
#include "vertex.h"
#include "vector.h"
#include "queue.h"


class Graph
{
public:
	Graph(int numNodes) throw (const char*);
	Graph(const Graph& rhs);
	~Graph();
	Graph& operator=(const Graph& rhs) throw (const char*);
	int size() const { return numV; }
	void clear();
	bool isEdge(const Vertex& v1, const Vertex& v2) const;
	set <Vertex> findEdges(const Vertex& v);
	void add(Vertex v1, Vertex v2);
	void add(Vertex v1, set<Vertex> s);
	Vector <Vertex> findPath(const Vertex& v1, const Vertex& v2);
private:
	bool* matrix;
	int numV;
	int lines;
};

#endif // !GRAPH_H
