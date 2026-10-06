#include <iostream>
#include <vector>

long long ackermann_non_recursive(long long m, long long n) {
    std::vector<long long> stack;
    stack.push_back(m);
    stack.push_back(n);

    while (!stack.empty()) {
        n = stack.back(); stack.pop_back();
        m = stack.back(); stack.pop_back();

        if (m == 0) {
            n = n + 1;
            if (stack.empty()) {
                return n;
            }
            stack.back() = n; 
        } else if (n == 0) {
            stack.push_back(m - 1);
            stack.push_back(1);
        } else {
            stack.push_back(m - 1);
            stack.push_back(m);
            stack.push_back(n - 1);
        }
    }
    return n;
}

int main() {
    long long m, n;
    std::cout << "請輸入阿克曼函數的 m 和 n (非遞迴版)：\n";
    std::cout << "m = ";
    std::cin >> m;
    std::cout << "n = ";
    std::cin >> n;

    if (m < 0 || n < 0) {
        std::cout << "錯誤：m 和 n 不能為負數！\n";
        return 1;
    }

    std::cout << "計算中...\n";
    long long result = ackermann_non_recursive(m, n);
    std::cout << "A(" << m << ", " << n << ") = " << result << std::endl;

    return 0;
}