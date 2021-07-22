#ifndef VERTICES_HPP
#define VERTICES_HPP

#include "Graph.hpp"
#include <string>
#include <unordered_map>

class Vertices{
public:

    Vertices(const std::string& label){
        this->label = label;
    };
    friend class Graph;

private:
    std::string label; // State Name
};

#endif