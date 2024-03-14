class Stack {
private:
    struct Node {
        char data = 0;
        Node *next = nullptr;
        Node (char data) {
            this->data = data;
        }
    };

    Node *head = nullptr;

    unsigned int size = 0;

public:
    void push(char data) {
        Node *newNode = new Node(data);
        if (!head) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    char peek() {
        if (!head) {
            return -1;
        }
        return head->data;
    }

    char pop() {
        if (!head) {
            return -1;
        }
        char data = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        return data;
    }

    int getSize() {
        return size;
    }
};
