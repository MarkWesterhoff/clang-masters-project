#pragma once


class Graph<V,E> {
public:
  //constructors
  Graph() = default;
  //Graph() from file
  ~Graph();

  //constructing the graph
  bool addVertex(V& v);
  bool addEdge(const V& v1, V& v2);
  bool addEdge(const V& v1, const V& v2);

  std::string printAdjacencyMatrix();


private:


};