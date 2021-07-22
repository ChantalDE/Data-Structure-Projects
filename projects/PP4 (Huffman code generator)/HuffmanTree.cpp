#include "HuffmanTree.hpp"
#include "HeapQueue.hpp"

    //LLLbBLdLiBBLsLnLoBBL LaBBB
    //BBBaL LBBoLnLsLBBiLdLBbLLL
    // bool HuffmanTree::isChar(char a, char b, std::string& inputCode, int i, bool isBL){
    //     bool isCharv = false;
    //     if(inputCode[i] == 'L' || inputCode[i] == 'L' && inputCode[i+1] != 'L' && inputCode[i+1] != 'B'){
    //         return isCharv;
    //     }
    //     if(inputCode[i] == 'B' && inputCode[i+1] == 'L'){
    //         return isCharv;
    //     }
    //     if(inputCode[i] == 'B' && inputCode[i+1] == 'B'){
    //         i++;
    //         isChar(inputCode[i], inputCode[i+1], inputCode, i);
    //         if(isCharv == false){

    //         }
    //     }
    //     if(inputCode[i] == 'L' && inputCode[i+1] == 'L'){
    //         i++;
    //         isChar(inputCode[i], inputCode[i+1], inputCode, i);
    //     }
    //     if(inputCode[i] == 'L' && inputCode[i+1] == 'B'){
    //         i++;
    //         isChar(inputCode[i], inputCode[i+1], inputCode, i);
    //     }       
    // }

    void HuffmanTree::insertMap(HuffmanNode* v, std::string code){
        if (v == nullptr){
            return;
        }
        if(v->isLeaf()){
            preCodeMap.insert({v->getCharacter(), code});
            return;
        }            
        if(v->isBranch()){
            insertMap(v->left, code + "0");
            insertMap(v->right, code + "1");
        }
    }

    void HuffmanTree::printTree(HuffmanNode* v, std::string code = ""){
        if (v == nullptr){
            return;
        }           
        
            //std::cout <<"pos v: " << v->getCharacter() << v->isBranch() << std::endl;
            printTree(v->left, code+'0');
            printTree(v->right, code+'1');
        

        std::cout <<"pos v: " << v->getCharacter() << " " << code << std::endl;

    }

    std::string HuffmanTree::compress(const std::string inputStr){
        //insert input in map based on frequency
        for(unsigned int i = 0; i < inputStr.length(); i++){
            if(list.find(inputStr[i]) == list.end()){
                list.insert({inputStr[i], 1});
            }
            else{
                list.find(inputStr[i])->second +=1;
            }
        }

        //insert in priority queue
        HeapQueue<HuffmanNode*, HuffmanNode::Compare> queue; //object
        for(auto &p : list){
            queue.insert(new HuffmanNode(p.first, p.second));
        }

        while(queue.size() > 1){
            //create child 1
            HuffmanNode* child1 = queue.min();
            queue.removeMin();
            //create child 2
            HuffmanNode* child2 = queue.min();
            queue.removeMin();
            //create parent
            HuffmanNode* parent = new HuffmanNode('\0', child1->getFrequency() + child2->getFrequency(), nullptr, child1, child2);
            child1->parent = parent;
            child2->parent = parent;
            queue.insert(parent);
        }
        root = queue.min();

        HuffmanTree::insertMap(root, "");

        //load output
        for(unsigned int i = 0; i < inputStr.size(); i++){
            output += preCodeMap.find(inputStr[i])->second;
        }  
     return output;
    }
   

// Serialize the tree using the above method.
// We do not need the frequency values to rebuild the tree,
// just the characters on the leaves and where the branches are in the post order.

   // Recursive function to perform post-order traversal of the tree
void HuffmanTree::postRec(HuffmanNode* node, std::string& sOutput) const
{
	// if the current node is empty
	if (node == nullptr){
		return;
    }

	    // Traverse the left subtree
	    postRec(node->left, sOutput);
	    // Traverse the right subtree
	    postRec(node->right, sOutput);

     if(node->isLeaf()){
        sOutput+=(std::string("L") + node->getCharacter());
    }
     else{
        sOutput += "B";
    }
}
    std::string HuffmanTree::serializeTree() const{ 
        std::string sOutput;
        HuffmanTree::postRec(root, sOutput);
        return sOutput;
    }

//  Given a string created with the compress method and a serialized version of the tree,
// return the decompressed original string
    std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
    std::stack<std::string> st;

    //load in stack
    for(int i = 0; i < serializedTree.size();){
        if(serializedTree[i] == 'L'){
            st.push(std::string(1,serializedTree[i]) + std::string(1,serializedTree[i + 1]));
            i++;
            i++;
        }
        if(serializedTree[i] == 'B'){
            st.push(std::string(1,serializedTree[i]));
            i++;
        }
    }

        //build tree back

         HuffmanNode* parent = new HuffmanNode('\0', 0);
         //pop root
         st.pop();
         HuffmanNode* root = parent;
        while(!(st.empty())){
            if(st.top() == "B"){
                HuffmanNode* node = new HuffmanNode('\0', 0);
                node->parent = parent;
                if(parent->right == nullptr){
                    parent->right = node;
                }
                else{
                    parent->left = node;
                }
                parent = node;
                st.pop();
            }
            else{                
                HuffmanNode* node = new HuffmanNode(st.top()[1], 0);
                node->parent = parent;
                if(parent->right == nullptr){
                    parent->right = node;
                }
                else{
                    parent->left = node;
                    while(parent->left != nullptr && parent->right != nullptr && parent->parent != nullptr){
                        parent = parent->parent;
                    }
                }
                st.pop();
            }
        }




        HuffmanNode* pos = root;
        for(auto i = 0; i <= inputCode.size(); i++){
           
            if(pos->isLeaf()){
                tOutput += pos->getCharacter();
                pos = root;              
            }
            if(pos->isBranch()){
                if(inputCode[i] == '0'){
                    pos = pos->left;
                }
                if(inputCode[i] == '1'){
                    pos = pos->right;               
                }
            }
        }
        return tOutput;
    }

