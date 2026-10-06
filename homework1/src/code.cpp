#include <iostream>

long long ackermann_recursive(long long m, long long n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return ackermann_recursive(m - 1, 1);
    } else {
        return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
    }
}

int main() {
    long long m, n;
    std::cout << "請輸入阿克曼函數的 m 和 n (建議 m <= 3, n <= 4);\n";
    std::cout << "m = ";
    std::cin >> m;
    std::cout << "n = ";
    std::cin >> n;

    if (m < 0 || n < 0) {
        std::cout << "錯誤m 和 n 不能為負數！\n";
        return 1;
    }

    std::cout << "計算中...\n";
    long long result = ackermann_recursive(m, n);
    std::cout << "A(" << m << ", " << n << ") = " << result << std::endl;
    
    return 0;
}