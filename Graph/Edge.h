#pragma once

class Vertex;
class Direction;

template <Label> 
class Edge {
  Edge(Vertex* v1, Vertex* v2);
  ~Edge() = default;
  Edge(const Edge& e2) = delete;
  Edge(Edge&& e2) = delete;
  
  Label getLabel();
};

