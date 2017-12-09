#include "graph.h"

Graph::Graph(int numNodes) throw (const char*)
{
	try
	{
		numV = numNodes;
		matrix = new bool[numNodes * numNodes];
		for (int i = 0; i < numNodes * numNodes; ++i)
			matrix[i] = false;
	}
	catch (const std::bad_alloc)
	{
		throw "ERROR: Unable to allocate memory for the graph.";
	}
}

Graph::Graph(const Graph & rhs)
{
	*this = rhs;
}

Graph::~Graph()
{
	clear();
	if (matrix)
	{
		delete[] matrix;
		matrix = NULL;
	}
}

Graph& Graph::operator=(const Graph & rhs) throw (const char*)
{
	try
	{
		delete[] matrix;
		matrix = new bool[rhs.numV * rhs.numV];
		numV = rhs.numV;
		lines = rhs.lines;
		for (int i = 0; i < size(); ++i)
			matrix[i] = rhs.matrix[i];
		return *this;
	}
	catch (const std::bad_alloc)
	{
		throw "ERROR: Unable to allocate memory for the graph.";
	}
}

void Graph::clear()
{
	for (int i = 0; i < numV * numV; ++i)
	{
		matrix[i] = false;
	}
}

bool Graph::isEdge(const Vertex& v1, const Vertex& v2) const
{
	return matrix[v1.index() * numV + v2.index()];
}

set<Vertex> Graph::findEdges(const Vertex& v)
{
	set<Vertex> s;
	for (int i = 0; i < numV; ++i)
	{
		if (matrix[v.index() * numV + i])
			s.insert(Vertex(i));
	}
	return s;
}

void Graph::add(Vertex v1, Vertex v2)
{
	matrix[v1.index() * numV + v2.index()] = true;
}

void Graph::add(Vertex v1, set<Vertex> s)
{
	for (set<Vertex>::iterator it = s.begin(); it != s.end(); ++it)
	{
		matrix[v1.index() * numV + (*it).index()] = true;
	}
}


Vector<Vertex> Graph::findPath(const Vertex& v1, const Vertex& v2)
{
	int distance = 0;
	Vector<Vertex> predecessor = Vector<Vertex>(size());
	custom::queue<Vertex> toVisit;
	toVisit.push(v1);
	Vector<int> distances;
	for (int i = 0; i < size(); ++i)
		distances.push_back(-1);

	while ((!toVisit.empty()) && (distances[v2.index()] = -1)) //something is creating an infinite loop in this while
	{
		Vertex v = toVisit.front();
		toVisit.pop();

		if (distances[v.index()] > distance)
		{
			distance++;
		}
		
		set<Vertex> s = findEdges(v);
		for (set<Vertex>::iterator it = s.begin(); it != s.end(); ++it)
		{
			if (distances[(*it).index()] = -1)
			{
				distances[(*it).index()] = distance + 1;
				predecessor[(*it).index()] = v;
				toVisit.push(*it);
			}
		}
	}
	distance++;

	Vector<Vertex> path;
	if (distances[v1.index()] = -1)
		return path;
	path.push_back(v1);
	for (int i = 1; i < distance; ++i)
		path.push_back(predecessor[path[i - 1].index()]);
	return path;
}