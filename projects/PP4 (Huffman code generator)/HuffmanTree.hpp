#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <vector>
#include <stack>
#include <string>


class HuffmanTree : public HuffmanTreeBase{
public:
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);

    void insertMap(HuffmanNode*, std::string code);
    void postRec(HuffmanNode*, std::string& ) const;
    void printTree(HuffmanNode*, std::string);
    std::string tOutput;
    std::string output;
private:

    std::map<char, int> list;
    std::map<char,int>::iterator it;

    std::map<char, std::string> preCodeMap;
    std::map<char,std::string>::iterator iter;

    
    

    HuffmanNode* root;
    HuffmanNode* startPost;
};

#endif






// ------------HINTS----------------------------------------------------------------

//  For the encoding step where you translate characters using your Huffman Tree, 
//  this is essentially a preordering of the tree and can be done recursively.

//  Remember,  when you are deserializing, you are going from post ordering back to the full tree.
//  This is very similar to the postfix to infix conversion you did in PP2,
//   but now building a tree instead of an expression.

// For decoding the characters, you just follow the tree down the branches until you hit the leaf with the character,
// adding a zero for a left move and adding a 1 for a right move.

// I suggest implementing a recursive method to destroy nodes for your destructor.

// For the branching nodes, I suggest using the null character just to hold a spot 
// since this should not be popping up in text you are compressing.

//  The test cases are based on using the standard library header <map>, not the unordered map.
