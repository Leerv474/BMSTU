#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdlib> // для функции rand()
#include <ctime> // для функции time()
#include <chrono>
#include <memory>

using namespace std;

template<typename V, typename T>
class Node {
public:
    V value;
    T priority;
    int length;
    unique_ptr<Node<V, T>> left;
    unique_ptr<Node<V, T>> right;

    Node(V _value, T _priority)
        : value(_value), priority(_priority), length(1), left(nullptr), right(nullptr) {}
};

template<typename V, typename T>
class PriorityQueue {
private:
    unique_ptr<Node<V, T>> root;

    int length(Node<V, T>* node) {
        return (node == nullptr) ? 0 : node->length;
    }

    Node<V, T>* newMeld(unique_ptr<Node<V, T>>& root, unique_ptr<Node<V, T>>& add) {
        if (!root) return add.release();
        if (!add) return root.release();

        if (root->priority < add->priority) swap(root, add);

        root->right.reset(newMeld(root->right, add));
        if (length(root->left.get()) < length(root->right.get())) {
            swap(root->left, root->right);
        }
        root->length = length(root->right.get()) + 1;

        return root.release();
    }

public:
    PriorityQueue() : root(nullptr) {}

    void insert(unique_ptr<Node<V, T>> node) {
        root.reset(newMeld(root, node));
    }

    unique_ptr<Node<V, T>> getMax() {
        if (!root) return nullptr;
        return make_unique<Node<V, T>>(root->value, root->priority);
    }

    unique_ptr<Node<V, T>> extractMax() {
        if (!root) return nullptr;

        unique_ptr<Node<V, T>> ret = make_unique<Node<V, T>>(root->value, root->priority);
        root.reset(newMeld(root->right, root->left));

        return ret;
    }

    void clear() {
        while (root) {
            extractMax();
        }
    }
};

void writeCSV(vector<double>& arr, const string& path) {
    ofstream writer(path);
    if (writer.is_open()) {
        writer << "N;Time\n";
        for (int i = 0; i < arr.size(); i++) {
            writer << (i + 1) * 10 << ";" << arr[i] << "\n";
        }
        writer.close();
        cout << "Successfully written to " << path << endl;
    } else {
        cerr << "Error writing to file!" << endl;
    }
}

vector<int> createMas(int n) {
    vector<int> mas;
    int el = -1000 + rand() % 10000;
    mas.push_back(el);
    for (int i = 1; i < n; i++) {
        el += -1000 + rand() % 10000;
        mas.push_back(el);
    }
    return mas;
}

void createFiles(int n) {
    for (int i = 0; i < n; i++) {
        string path = "files/" + to_string(i) + ".txt";
        ofstream writer(path);
        if (writer.is_open()) {
            vector<int> mas = createMas(20);
            for (int j = 0; j < mas.size(); j++) {
                writer << mas[j] << "\n";
            }
            writer.close();
        } else {
            cerr << "Error writing to file!" << endl;
            return;
        }
    }
}

void joinFiles(int n) {
    PriorityQueue<int, int> queue;
    for (int i = 0; i < n; i++) {
        string path = "files/" + to_string(i) + ".txt";
        ifstream reader(path);
        if (reader.is_open()) {
            int buff;
            while (reader >> buff) {
                queue.insert(make_unique<Node<int, int>>(buff, buff));
            }
            reader.close();
        } else {
            cerr << "Error opening file!" << endl;
            return;
        }
    }
    ofstream writer("files/Joined.txt");
    if (writer.is_open()) {
        while (auto maxNode = queue.extractMax()) {
            writer << maxNode->value << "\n";
        }
        writer.close();
    } else {
        cerr << "Error writing to file!" << endl;
    }
}

int main() {
    srand(time(NULL));
    vector<double> arr(51, 0.0);

    createFiles(2);
    joinFiles(2);

    for (int j = 0; j < 1; j++) {
        for (int i = 1; i <= 100; i += 10) {
            createFiles(i);

            auto startTime = chrono::steady_clock::now();
            joinFiles(i);
            auto endTime = chrono::steady_clock::now();
            double duration = chrono::duration<double, milli>(endTime - startTime).count();

            cout << "N=" << i << " Time in ms= " << duration << endl;
            arr[i / 10 - 1] += duration;

            if (j != 0) {
                arr[i / 10 - 1] /= 2.0;
            }
        }
    }

    writeCSV(arr, "res1.csv");

    return 0;
}

