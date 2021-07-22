#include "Graph.hpp"
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>

void Graph::addVertex(std::string label){
    //if vertex already exist, throw error
    for(auto it = vertices.begin(); it!= vertices.end(); it++){
        if(label == *it){
            throw std::runtime_error("Vertice already exist");
        }
    }
    vertices.push_back(label);
}

void Graph::removeVertex(std::string label){    
    //loop through map, find if 1abel is in vector value
    for(auto it = edges.begin(); it != edges.end();){
        bool incr = false;
        if(it->first == label){
            it = edges.erase(it);
        }
        else{
            incr = true; //increment it @ end if incr = true
        }
        //loop through vector
        for(auto iter = it->second.begin(); iter !=it->second.end();){
            if((iter->nextState) == label){ //remove element in vector
                iter = it->second.erase(iter);
            }
            else{
                iter++;
            }
        }
        if(incr){
            it++;
        }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){    
//If vertice don't exist, can't create edge
    bool v1 = true;
    bool v2 = true;
    for(auto it = vertices.begin(); it != vertices.end(); it++){
        if(*it == label1){
            v1 = false;
        }
        if(*it == label2){
            v2 = false;
        }
    }
    if(v1 || v2){
        throw std::runtime_error("Vertice(s) doesn't excist");
    }

//if edge already exist, throw error
    for(auto it = edges[label1].begin(); it != edges[label1].end(); it++){
        if(label2 == it->nextState){
            throw std::runtime_error("Edge already exist");
        }
    }

    for(auto it = edges[label2].begin(); it != edges[label2].end(); it++){
        if(label1 == it->nextState){
            throw std::runtime_error("Edge already exist");
        }
    }

//actual adding to adjacency list (map)
    Edge a;
    a.nextState = label2;
    a.distance = weight;    
    edges[label1].push_back(a);

    //bidirectional graph
    Edge b;
    b.nextState = label1;
    b.distance = weight;
    edges[label2].push_back(b);
}


void Graph::removeEdge(std::string label1, std::string label2){
    for(auto it = edges[label1].begin(); it != edges[label1].end(); it++){
        if(it->nextState == label2){
            edges[label1].erase(it);
        }
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){ 
    std::unordered_map<std::string, unsigned long> dist;
    std::unordered_map<std::string, std::string> prev;
    unsigned long inf = std::numeric_limits<unsigned long>::max(); //INFINITE number

    std::deque<std::string> unvisited;
    for(auto iter = edges.begin(); iter != edges.end(); iter++){
        dist[iter->first] = inf;                // Unknown distance from source to v
        prev[iter->first] = std::string{};     // Predecessor of v
        unvisited.push_back(iter->first);
   }

    dist[startLabel] = 0;                    
    while(!(unvisited.empty())){
       //------------TRAVEL PROPPERLY BASED ON MIN_ELEMENT-----------------        
        auto uIter = std::min_element(unvisited.begin(), unvisited.end(), [&](const auto& l, const auto& r){
            return dist[l] < dist[r];
        });
        auto u = *uIter;

        for(auto iter = edges[u].begin(); iter != edges[u].end(); iter++){
            unsigned long sum = dist[u] + iter->distance;
            //avoid overflow
            if(dist[u] == inf){
                sum = inf;
            }    
           // std::cout << "from vertex " << u << " to " << iter->nextState << ": "<< sum << "\n";       

            if(sum < dist[iter->nextState]){
                dist[iter->nextState] = sum;
                prev[iter->nextState] = u;
            }
        }
        unvisited.erase(uIter);    
    }
    unsigned long sumOfEdges = dist[endLabel];

    //------------------FIND PATH------------------//
    std::vector<std::string> reversePath = {endLabel};
    std::string currentLabel  = prev[endLabel];
    while (currentLabel != "")
    {
        reversePath.push_back(currentLabel);
        currentLabel = prev[currentLabel];
    }
    if (*(reversePath.end() - 1) != startLabel){
        throw std::runtime_error("path doesn't exist");
    }
    else{
        path = std::vector<std::string>(reversePath.rbegin(), reversePath.rend());
    }
    return sumOfEdges;
}


//------------------HELPER--PRINT-STATEMENT------------------//
void Graph::print(){
    for(auto it = edges.begin(); it != edges.end(); it++){
        std::cout << "vertex: " << it->first << ": " << std::endl;
    //loop through vector
        for(auto iter = it->second.begin(); iter !=it->second.end(); iter++){
            std::cout << "nxt state: " << iter->nextState << ", distance: " << iter->distance << std::endl;
        }
    std::cout << "\n";
    }
}