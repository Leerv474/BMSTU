#include <iostream>


class HashMap {
    struct Node {
        int hash = 0;
        std::string data = "";
        Node *next = nullptr;

        Node(std::string data, int hash) {
            this->data = data;
            this->hash = hash;
        }
    };
    
    Node *list = nullptr;

    bool hashExists(int hash) {
        Node *temp = list;
        while (temp) {
            if (hash == temp->hash) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
public: 
    void enhash(std::string data) {
        if (data.size() < 2) {
            std::cerr << "string is too short\n";
            return;
        }
        int newHash = data[0] + data[1];
        while (hashExists(newHash)) {
            newHash++;
        }
        Node *newNode = new Node(data, newHash);

        if (!list) {
            list = newNode;
            return;
        }

        newNode->next = list;
        list = newNode;
    }

    std::string getByHash(int hash) {
        Node *temp = list;
        while (temp) {
            if (temp->hash == hash) {
                return temp->data;
            }
            temp = temp->next;
        }
        return "";
    }
};


int main() {
    // Create an instance of HashMap
    HashMap hashMap;

    // Test adding data to the hash map
    hashMap.enhash("apple");
    hashMap.enhash("banana");
    hashMap.enhash("cat");
    hashMap.enhash("dog");

    // Test retrieving data by hash
    std::cout << "Data for hash 215: " << hashMap.getByHash(215) << std::endl;
    std::cout << "Data for hash 211: " << hashMap.getByHash(211) << std::endl;
    std::cout << "Data for hash 218: " << hashMap.getByHash(218) << std::endl;

    // Test adding data with short string
    hashMap.enhash("x"); // This should print an error message

    return 0;
}
