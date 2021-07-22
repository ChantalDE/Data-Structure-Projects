#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include "Vertices.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <iterator>
#include <deque>
#include <functional>

class Graph:public GraphBase{
public:
struct Edge{
    unsigned long distance;
    std::string nextState;
};
    Graph(){};

    virtual void addVertex(std::string label);
    virtual void removeVertex(std::string label);
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight);
    virtual void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    void print();

private:
    std::vector<std::string> vertices;
    std::unordered_map<std::string, std::vector<Edge>> edges;
};
    


#endif

