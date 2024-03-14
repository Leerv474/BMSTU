#include <iostream>
#include "bintree.h"


int main() {
    BinTree tree;

    // Insert nodes into the tree
    tree.insert('F');
    tree.insert('B');
    tree.insert('G');
    tree.insert('A');
    tree.insert('D');
    tree.insert('C');
    tree.insert('E');
    tree.insert('X');
    tree.insert('Y');
    tree.insert('Z');

    // Print the tree
    tree.printTree();

    // Traverse the tree
    std::cout << "In-order traversal: ";
    tree.traverse();
    std::cout << std::endl;

    // Search for a node
    char searchData = 'C';
    std::cout << "searchData: " << tree.searchNode(searchData) << '\n';

    // Delete a node
    char deleteData = 'D';
    std::cout << "Deleting node with data '" << deleteData << "'..." << std::endl;
    tree.deleteByData(deleteData);
    std::cout << "In-order traversal after deletion: ";
    tree.traverse();
    std::cout << std::endl;

    return 0;
}

