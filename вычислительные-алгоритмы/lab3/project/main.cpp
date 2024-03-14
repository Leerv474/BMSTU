#include <iostream>
#include <chrono>
#include <fstream>
#include <stack>
#include "stack.h"
#include "linkedlists.h"
#include "queue.h"
 
LinkedList mergeLists(const LinkedList& list1, const LinkedList& list2) {
    LinkedList mergedList;
    
    // Copy elements from list1 to mergedList
    for (int i = 0; i < list1.getSize(); ++i) {
        mergedList.insert(list1.get(i));
    }

    // Copy elements from list2 to mergedList
    for (int i = 0; i < list2.getSize(); ++i) {
        mergedList.insert(list2.get(i));
    }

    return mergedList;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    std::string postfix = "";
    Stack stack;
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop();
        } else {
            while (!stack.getSize() == 0 && precedence(c) <= precedence(stack.peek())) {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }
    while (stack.getSize() != 0) {
        postfix += stack.pop();
    }
    return postfix;
}

std::string standart_infixToPostfix(const std::string& infix) {
    std::string postfix = "";
    std::stack<char> stack;
    for (char c : infix) {
        if (std::isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop(); // Discard '('
        } else {
            while (!stack.empty() && precedence(c) <= precedence(stack.top())) {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }
    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }
    return postfix;
}


void encryptMessage(const std::string& inputFile, const std::string& outputFile, Queue& queue) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        if (ch != '\n') {
            outFile.put(queue.peek());
            queue.enqueue(ch);
        }
    }

    inFile.close();
    outFile.close();
}

int main() {
    // Create LinkedList objects L1 and L2
    LinkedList L1, L2;

    // Insert elements into L1
    L1.insert(1);
    L1.insert(2);
    L1.insert(3);

    // Insert elements into L2
    L2.insert(4);
    L2.insert(5);
    L2.insert(6);

    // Merge L2 into L1 and store the result in L
    LinkedList L = mergeLists(L1, L2);

    // Display the merged list L
    std::cout << "Merged List: ";
    for (int i = 0; i < L.getSize(); ++i) {
        std::cout << L.get(i) << " ";
    }
    std::cout << std::endl;

 // Test infixToPostfix function
    std::string infixExpression = "(a+b)*c-d/e";
    
    // Time measurement for custom infixToPostfix
    auto start_custom = std::chrono::high_resolution_clock::now();
    std::string postfix = infixToPostfix(infixExpression);
    auto end_custom = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_custom = end_custom - start_custom;
    std::cout << "Time taken for custom infixToPostfix: " << elapsed_custom.count() << " seconds" << std::endl;

    // Time measurement for standard infixToPostfix
    auto start_standard = std::chrono::high_resolution_clock::now();
    std::string standardPostfix = standart_infixToPostfix(infixExpression);
    auto end_standard = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_standard = end_standard - start_standard;
    std::cout << "Time taken for standard infixToPostfix: " << elapsed_standard.count() << " seconds" << std::endl;

    // Encrypt a message using Queue
    Queue queue;
    encryptMessage("input.txt", "output.txt", queue);

    return 0;
}

