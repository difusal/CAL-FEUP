#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <limits.h>

template<class T> class Edge;
template<class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/*
 * Class Vertex
 */
template<class T>
class Vertex {
	T info;
	std::vector<Edge<T> > adj;

	bool visited;
	bool processing;
	int indegree;
	int dist;

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);

public:
	Vertex(T in);
	T getInfo() const;
	int getIndegree() const;

	Vertex* path;

	friend class Graph<T> ;
};

/*
 * Class Edge
 */
template<class T>
class Edge {
	Vertex<T> *dest;
	double weight;

public:
	Edge(Vertex<T> *d, double w);

	friend class Graph<T> ;
	friend class Vertex<T> ;
};

/*
 * Class Graph
 */
template<class T>
class Graph {
	std::vector<Vertex<T> *> vertexSet;
	int numCycles;

	void dfs(Vertex<T> *v, std::vector<T> &res) const;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, std::list<T> &res);

public:
	/**
	 * Returns the number of vertexes on the graph.
	 */
	int getNumVertex() const;
	std::vector<Vertex<T> *> getVertexSet() const;
	Vertex<T>* getVertex(const T &v) const;

	bool addVertex(const T &in);
	bool removeVertex(const T &in);

	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);

	std::vector<T> dfs() const;
	std::vector<T> bfs(Vertex<T> *v) const;

	/**
	 * Retorna o número máximo de filhos de um nó do grafo (a partir de v);
	 * O parâmetro inf é o conteúdo desse nó do grafo.
	 */
	int maxNewChildren(Vertex<T> *v, T &inf) const;

	/**
	 * Retorna um vetor contendo apontadores para os vértices-fonte do grafo.
	 *
	 * Um vértice-fonte é um vértice que não tem arestas incidentes, ou seja,
	 * arestas a chegarem ao vértice; portanto, o seu indegree é igual a zero.
	 * Caso não existam tais vértices, o vetor a retornar estará vazio.
	 */
	std::vector<Vertex<T>*> getSources() const;

	/**
	 * retorna um vetor com a sequência dos elementos do grafo representando
	 * os vértices do caminho de origin até dest, inclusivé.
	 * origin e dest são os membros-dado info dos vértices de origem e destino
	 * do caminho, respetivamente.
	 */
	std::vector<T> getPath(const T &origin, const T &dest);

	/**
	 * Atualiza o valor do membro-dado indegree de todos os vértices do grafo.
	 */
	void resetIndegrees();

	int getNumCycles();
	bool isDAG();
	std::vector<T> topologicalOrder();

	/**
	 * Algoritmo para encontrar os caminhos mais curtos a partir
	 * do elemento v do grafo (vértice cujo conteúdo é v) a todos
	 * os outros vértices do grafo, no caso de grafos não pesados.
	 */
	void unweightedShortestPath(const T &v);
};
