#include "Graph.hpp"
#include <iostream>

int main(){

struct EdgeStruct { 
    std::string a; std::string b; unsigned long w;    
};

    Graph g;

    std::vector<std::string> vertices1 { "1", "2", "3", "4", "5", "6", "9"};
    std::vector<EdgeStruct> edges1{
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}, {"1", "5", 100},
    };

    for (const auto label : vertices1) g.addVertex(label);
    for (const auto &e : edges1) g.addEdge(e.a, e.b, e.w);


    //test to see if adjecency list works
    g.print();
    
    // std::cout << "\n-------REMOVE EDGE(1, 2)--------";
    // g.removeEdge("1", "2");
    // g.print();
    
    // std::cout << "\n----------Remove Vertex (1)---------";  
    // g.removeVertex("1");  
    // g.print();


    std::vector<std::string> path;

    std::cout<< "LOOK:" << g.shortestPath("1", "9", path) << "\nPath: ";
    for (const auto& p : path)
    {
        std::cout << p << ' ';
    }
    std::cout << '\n';
    }