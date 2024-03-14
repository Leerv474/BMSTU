class LinkedList {
private:
    struct Node {
        int data = 0;
        Node *next = nullptr;
        Node(int data) {
            this->data = data;
        }
    };

    Node *head = nullptr;
    unsigned int size = 0;

public:
    int getSize() const {
        return size;
    }
    void insert(int data) {
        Node *newNode = new Node(data);
        if (!head) {
            head = newNode;
            size++;
            return;
        }
        newNode->next = head;
        head = newNode;
        size++;
    }

    void remove() {
        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    int get(int index = 0) const {
        Node *temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

};
