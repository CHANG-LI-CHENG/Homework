#include <iostream>
#include <vector>

int main_powerset() {
    int n;
    std::cout << "請輸入集合的元素個數：";
    std::cin >> n;

    std::vector<char> S(n);
    std::cout << "請依序輸入這 " << n << " 個字元元素（例如 a b c）：\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> S[i];
    }

    int total_subsets = 1 << n; // 總共有 2^n 個子集
    std::cout << "\n計算出的冪集合為：\n";

    // 使用巢狀 for 迴圈與 if 判斷來產生所有子集
    for (int i = 0; i < total_subsets; ++i) {
        std::cout << "{ ";
        bool first = true;
        for (int j = 0; j < n; ++j) {
            // 用 if 檢查第 j 個位元是否為 1
            if ((i >> j) & 1) {
                if (!first) {
                    std::cout << ", ";
                }
                std::cout << S[j];
                first = false;
            }
        }
        std::cout << " }\n";
    }

    return 0;
}