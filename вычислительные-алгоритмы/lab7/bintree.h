#pragma once
#include <iostream>

#include <string>
class BinTree {
private:
    struct Node {
        char data;
        Node *right = nullptr;
        Node *left = nullptr;
        Node *parent = nullptr;
        int side = -1;

        Node(char data) {
            this->data = data;
        }
    };

    Node *root = nullptr;

    Node *searchNode(char data, Node *currentNode) {
        if (!currentNode) {
            std::cout << "not found\n";
            return nullptr;
        }
        if (data > currentNode->data) {
            return searchNode(data, currentNode->right);
        }
        if (data < currentNode->data) {
            return searchNode(data, currentNode->left);
        }
        return currentNode;
    }

    void printTree(Node **level, int depth, int indent) {
        int nullCNT = 0;
        std::string spacing = "";
        std::string smallSpacing = "";
        for (int i = 0; i < indent; i++) {
            spacing += ' ';
            if (i == indent - 1) {
                continue;
            }
            smallSpacing += ' ';
        }
        std::cout << smallSpacing;
        int twos = 0;
        for (int i = 0; i < depth; i++) {
            twos++;
            if (level[i] == nullptr) {
                nullCNT++;
                std::cout << ' ';
            } else {
                std::cout << level[i]->data;
            }

            std::cout << smallSpacing;
            std::cout << spacing;
        }
        std::cout << "\n\n";
    

        if (nullCNT == depth) {
            return;
        }

        
        Node **newLevel = new Node*[depth * 2];
        int cnt = 0;
        for (int i = 0; i < depth; i++){
            if (level[i] == nullptr) {
                newLevel[cnt] = nullptr;
                cnt++;
                newLevel[cnt] = nullptr;
                cnt++;
                continue;
            }
            newLevel[cnt] = (level[i])->left;
            cnt++;
            newLevel[cnt] = (level[i])->right;
            cnt++;
        }

        printTree(newLevel, depth * 2, indent / 2);
    }

    int getHeight(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        int rightHeight = getHeight(root->right);
        int leftHeight = getHeight(root->left);

        if (rightHeight > leftHeight) {
            return 1 + rightHeight;
        }
        return 1 + leftHeight;
    }

    void traverse(Node* root) {
        if (root == nullptr) return;

        traverse(root->left); // Traverse left subtree
        std::cout << root->data<< " "; // Process current node
        traverse(root->right); // Traverse right subtree
    }


    
public:
    void traverse() {
        if (!root) {
            std::cerr << "tree is empty\n";
            return;
        }
        traverse(root);
    }

    Node *searchNode(const char data) {
        if (root == nullptr) {
            std::cout << "Tree is empty\n";
            return nullptr;
        }

        return searchNode(data, root);
    }
    void printTree() {
        if (root == nullptr) {
            std::cout << "Tree is empty\n";
            return;
        }

        Node **level = new Node*[1];
        level[0] = root;

        int indent = 1;
        int height = getHeight(root);
        std::cout << height << " tree: \n";
        for (int i = 0; i < height; i++) {
            indent *= 2;
        }
        printTree(level, 1, indent + 1);
    }

    
    void deleteByData(char data) {
        Node *nodeToDelete = searchNode(data);

        if (nodeToDelete == root && root->side == -1) {
            root = nullptr;
            delete nodeToDelete->right;
            delete nodeToDelete->left;
            delete nodeToDelete->parent;
            delete nodeToDelete;
            return;
        }

        if (nodeToDelete == nullptr) {
            std::cout << "node not found\n";
            return;
        }

        if (!nodeToDelete->right && !nodeToDelete->left) {
            if (nodeToDelete->side == 0) {
                nodeToDelete->parent->left = nullptr;
            } 
            if (nodeToDelete->side == 1) {
                nodeToDelete->parent->right = nullptr;
            }
            delete nodeToDelete->left;
            delete nodeToDelete->right;
            delete nodeToDelete;
            return;
        }


        if (nodeToDelete->right && !nodeToDelete->left) {
            if (nodeToDelete->side == 0) {
                nodeToDelete->parent->left = nodeToDelete->right;
            } 
            if (nodeToDelete->side == 1) {
                nodeToDelete->parent->right = nodeToDelete->right;
            }
            delete nodeToDelete->left;
            delete nodeToDelete;
            return;
        }

        if (!nodeToDelete->right && nodeToDelete->left) {
            if (nodeToDelete->side == 0) {
                nodeToDelete->parent->left = nodeToDelete->left;
            } 
            if (nodeToDelete->side == 1) {
                nodeToDelete->parent->right = nodeToDelete->left;
            }
            delete nodeToDelete->right;
            delete nodeToDelete;
            return;
        }

        Node *successor = nodeToDelete;
        while (successor->left) {
            successor = successor->left;
        }

        nodeToDelete->data = successor->data;
        if (!successor->right) {
            successor->parent->left = nullptr;
            delete successor->left;
            delete successor->right;
            delete successor;
            return;
        }
        
        nodeToDelete->data = successor->data;
        successor->data = successor->right->data;
        delete successor->right->right;
        delete successor->right->left;
        delete successor->right;
        successor->right = nullptr;
    }



    char getValue(Node *node) {
        if (!node) {
            std::cout << "node is empty\n";
            return 0;
        }
        return node->data;
    }

    Node *getLeft(Node *node) {
        if (!node) {
            std::cout << "node is empty\n";
            return nullptr;
        }
        if (!node->left) {
            std::cout << "left is empty\n";
        }
        return node->left;
    }

    Node *getRight(Node *node) {
        if (!node) {
            std::cout << "node is empty\n";
            return nullptr;
        }
        if (!node->right) {
            std::cout << "right is empty\n";
        }
        return node->right;
    }

    Node *getFather(Node *node) {
        if (!node) {
            std::cout << "node is empty\n";
            return nullptr;
        }
        if (!node->parent) {
            std::cout << "parent doesn't exist\n";
        }
        return node->parent;
    }

    Node *getSibling(Node *node) {
        if (!node) {
            std::cout << "node is empty\n";
            return nullptr;
        }
        if (!node->parent) {
            std::cout << "parent doesn't exist\n";
            return nullptr;
        }

        if (!node->parent->right || !node->parent->left) {
            std::cout << "sibling doesn't exist\n";
            return nullptr;
        }

        if (node->side == 0) {
            return node->parent->right;
        }
        return node->parent->left;
    }

    bool isEmpty() {
        if (root == nullptr) {
            return true;
        }
        return false;
    }


    void insert(const char data) {
        Node *newNode = new Node(data);
        if (isEmpty()) {
            root = newNode;
            return;
        }

        Node *temp = root;
        while (true){
            if (temp->data < data) {
                if (temp->right == nullptr) {
                    temp->right = newNode;
                    newNode->parent = temp;
                    newNode->side = 1;
                    break;
                }
                temp = temp->right;
                continue;
            }

            if (temp->left == nullptr) {
                temp->left = newNode;
                newNode->parent = temp;
                newNode->side = 0;
                break;
            }
            temp = temp->left;
        }
    }

};

