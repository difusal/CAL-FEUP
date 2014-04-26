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

template<class T>
Vertex<T>::Vertex(T in) :
		info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}

template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest, w);
	adj.push_back(edgeD);
}

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	d->indegree--;

	typename std::vector<Edge<T> >::iterator it = adj.begin();
	typename std::vector<Edge<T> >::iterator ite = adj.end();

	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);

			return true;
		} else
			it++;
	}

	return false;
}

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

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w) {
}

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

	int numInitStates;
	int numFinalStates;

public:
	Graph();
	~Graph();

	/**
	 * Returns the number of vertexes on the graph.
	 */
	int getNumVertex() const;
	std::vector<Vertex<T> *> getVertexSet() const;
	Vertex<T>* getVertex(const T &v) const;

	bool addVertex(const T &in);
	bool removeVertex(const T &in);

	bool addEdge(const T &sourc, const T &dest, double w);
	bool addEdge(const int sourcID, const int destID, double w);
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

	int getNumInitStates();
	int getNumFinalStates();

	void incNumInitStates();
	void incNumFinalStates();
};

template<class T>
Graph<T>::Graph() {
	numCycles = 0;

	numInitStates = 0;
	numFinalStates = 0;
}

template<class T>
Graph<T>::~Graph() {
	// TODO this
}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v)
			return vertexSet[i];

	return NULL;
}

template<class T>
bool Graph<T>::addVertex(const T &in) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();

	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;

	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);

	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();

	for (; it != ite; it++) {
		// if found
		if ((*it)->info == in) {
			// temporarily save
			Vertex<T> * v = *it;

			// delete
			vertexSet.erase(it);

			typename std::vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename std::vector<Vertex<T>*>::iterator it1e = vertexSet.end();

			for (; it1 != it1e; it1++)
				(*it1)->removeEdgeTo(v);

			// decrementa indegree para arestas que se iniciam em "v"
			typename std::vector<Edge<T> >::iterator itAdj = v->adj.begin();
			typename std::vector<Edge<T> >::iterator itAdje = v->adj.end();

			for (; itAdj != itAdje; itAdj++)
				itAdj->dest->indegree--;

			delete v;
			return true;
		}
	}

	return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();

	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}

		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}

		it++;
	}

	if (found != 2)
		return false;

	vD->indegree++;
	vS->addEdge(vD, w);

	return true;
}

template<class T>
bool Graph<T>::addEdge(const int sourc, const int dest, double w) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();

	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info.getID() == sourc) {
			vS = *it;
			found++;
		}

		if ((*it)->info.getID() == dest) {
			vD = *it;
			found++;
		}

		it++;
	}

	if (found != 2)
		return false;

	vD->indegree++;
	vS->addEdge(vD, w);

	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();

	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}

		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}

		it++;
	}

	if (found != 2)
		return false;

	return vS->removeEdgeTo(vD);
}

template<class T>
std::vector<T> Graph<T>::dfs() const {
	typename std::vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::const_iterator ite = vertexSet.end();

	for (; it != ite; it++)
		(*it)->visited = false;

	std::vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);

	return res;
}

template<class T>
std::vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	std::vector<T> res;
	std::queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;

	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);

		typename std::vector<Edge<T> >::iterator it = v1->adj.begin();
		typename std::vector<Edge<T> >::iterator ite = v1->adj.end();

		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;

			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template<class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	std::vector<T> res;
	std::queue<Vertex<T> *> q;
	std::queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;

	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop();
		l++;
		int nChildren = 0;

		typename std::vector<Edge<T> >::iterator it = v1->adj.begin();
		typename std::vector<Edge<T> >::iterator ite = v1->adj.end();

		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}

		if (nChildren > maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}

	return maxChildren;
}

template<class T>
std::vector<Vertex<T>*> Graph<T>::getSources() const {
	std::vector<Vertex<T>*> buffer;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->indegree == 0)
			buffer.push_back(vertexSet[i]);

	return buffer;
}

template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) {
	unweightedShortestPath(origin);

	std::list<T> buffer;
	Vertex<T>* v = getVertex(dest);
	std::cout << "Path to " << v->info << ": ";

	std::cout << (std::string) v->info << " ";
	buffer.push_front(v->info);

	while (v->path->info != origin) {
		v = v->path;
		std::cout << (std::string) v->info << " ";
		buffer.push_front(v->info);
	}

	buffer.push_front(v->path->info);
	std::cout << std::endl;

	std::vector<T> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}

	return res;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		//percorrer o vetor de Edges, e atualizar indegree
		for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++)
			vertexSet[i]->adj[j].dest->indegree++;
}

template<class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();

	return this->numCycles;
}

template<class T>
bool Graph<T>::isDAG() {
	return getNumCycles() == 0;
}

template<class T>
std::vector<T> Graph<T>::topologicalOrder() {
	//vetor com o resultado da ordenacao
	std::vector<T> res;

	//verificar se ee um DAG
	if (getNumCycles() > 0) {
		std::cout << "Ordenacao Impossivel!" << std::endl;

		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	std::queue<Vertex<T>*> q;

	std::vector<Vertex<T>*> sources = getSources();
	while (!sources.empty()) {
		q.push(sources.back());
		sources.pop_back();
	}

	//processar fontes
	while (!q.empty()) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;

			if (v->adj[i].dest->indegree == 0)
				q.push(v->adj[i].dest);
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != vertexSet.size())
		while (!res.empty())
			res.pop_back();

	//garantir que os "indegree" ficam atualizados no final
	this->resetIndegrees();

	return res;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	std::queue<Vertex<T>*> q;
	q.push(v);

	while (!q.empty()) {
		v = q.front();
		q.pop();

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;

			if (w->dist == INT_INFINITY) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}

}

template<class T>
void Graph<T>::dfs(Vertex<T> *v, std::vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);

	typename std::vector<Edge<T> >::iterator it = (v->adj).begin();
	typename std::vector<Edge<T> >::iterator ite = (v->adj).end();

	for (; it != ite; it++)
		if (it->dest->visited == false)
			dfs(it->dest, res);
}

template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;

	typename std::vector<Edge<T> >::iterator it = (v->adj).begin();
	typename std::vector<Edge<T> >::iterator ite = (v->adj).end();

	for (; it != ite; it++) {
		if (it->dest->processing == true)
			numCycles++;

		if (it->dest->visited == false)
			dfsVisit(it->dest);
	}

	v->processing = false;
}

template<class T>
void Graph<T>::dfsVisit() {
	typename std::vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::const_iterator ite = vertexSet.end();

	for (; it != ite; it++)
		(*it)->visited = false;

	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false) {
			std::cout << "Being visited" << std::endl;
			dfsVisit(*it);
		}
}

template<class T>
void Graph<T>::getPathTo(Vertex<T> *dest, std::list<T> &res) {
	res.push_back(dest->info);

	if (dest->path != NULL)
		getPathTo(dest->path, res);
}

template<class T>
int Graph<T>::getNumInitStates() {
	return numInitStates;
}

template<class T>
int Graph<T>::getNumFinalStates() {
	return numFinalStates;
}

template<class T>
void Graph<T>::incNumInitStates() {
	numInitStates++;
}

template<class T>
void Graph<T>::incNumFinalStates() {
	numFinalStates++;
}
