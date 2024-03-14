class Queue {
private:
    struct Node { 
        char data = 0;
        Node *next = nullptr;
        Node *prev = nullptr;
        Node(char data) {
            this->data = data;
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;

public:
    void enqueue(char data) {
        Node *newNode = new Node(data);
        if (!head) {
            head = newNode;
            tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    char dequeue() {
        if (!head) {
            return -1;
        }
        if (head == tail) {
            char data = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
            return data;
        }
        Node *temp = tail;
        char data = tail->data;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        return data;   
    }

    char peek() {
        if (!head) {
            return -1;
        }
        return tail->data;
    }
};
