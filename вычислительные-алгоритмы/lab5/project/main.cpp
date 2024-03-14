#include <iostream>


void printNums(int number, int k = 1) {
    for (int i = 0; i < k; i++) {
        std::cout << k << ' ';
    }

    if (number == k) {
        std::cout << std::endl;
        return;
    }
    printNums(number, k + 1);
}

bool searchSubstring(const std::string& text, const std::string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();

    // Iterate through each character in the text
    for (int i = 0; i <= textLength - patternLength; ++i) {
        // Check for a match starting at position i
        bool match = true;
        for (int j = 0; j < patternLength; ++j) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        
        // If match is found, return the starting index
        if (match) {
            return true;
        }
    }
    
    // If no match is found, return -1
    return false;
}

int main() {
    printNums(10);

    std::cout << searchSubstring("hello world", "world") << '\n';

    return 0;
}
