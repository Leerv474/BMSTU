#include <iostream>
#include <map>

int findNum()
{
    bool keepAlive = true;
    int currentNum = 1;
    int nextNum = 2;
    int sum;
    int occurences;
    std::map<int, int> sums;
    while (keepAlive) {
        for (int i = 1; i < nextNum; i++) {
            sum = (i * i * i) + (currentNum * currentNum * currentNum);
            occurences = sums[sum];
            if (occurences == 1) {
                return sum;
            }
            sums[sum] = occurences + 1;
        }
        currentNum++;
        nextNum++;
    }
    return 0;
}

int main()
{
    std::cout << findNum() << '\n';
    return 0;
}
