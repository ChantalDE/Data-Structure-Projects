#include "HuffmanTree.hpp"
#include <iostream>

int main(){
HuffmanTree test;
std::string testS = "helloo";

std::cout << test.compress(testS) << std::endl;
std::cout << test.serializeTree() << std::endl;
std::cout << test.decompress(test.output, test.serializeTree());

return 0;
}

