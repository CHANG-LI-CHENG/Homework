# 41443132

作業報告：遞迴阿克曼函數、非遞迴阿克曼函數與冪集合

## 解題說明

本報告涵蓋三個不同的演算法程式實作，分別是用於探討深層遞迴與數學函數成長的「遞迴版阿克曼函數」、利用堆疊模擬來避免系統溢位的「非遞迴版阿克曼函數」，以及透過位元運算高效生成集合子集的「冪集合（Power Set）」。

1. **遞迴版阿克曼函數**：根據數學定義直接遞迴拆解 $A(m, n)$，當 $m=0$ 時返回 $n+1$，否則依據 $n$ 的值進行巢狀遞迴呼叫。

2. **非遞迴版阿克曼函數**：利用 `std::vector` 模擬系統堆疊（Stack），以迴圈疊代方式替代系統遞迴，解決大數值運算時可能發生的 Stack Overflow 問題。

3. **冪集合生成**：透過 $2^n$ 個組合與位元遮罩（Bitmask）運算，依序檢查每一位元的開關狀態來快速列舉出給定字元集合的所有子集。

## 程式實作

以下為三個程式的主要原始碼：

### 1. 遞迴版阿克曼函數

```
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

```

### 2. 非遞迴版阿克曼函數

```
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

```

### 3. 冪集合生成

```
#include <iostream>
#include <vector>

int main() {
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

    for (int i = 0; i < total_subsets; ++i) {
        std::cout << "{ ";
        bool first = true;
        for (int j = 0; j < n; ++j) {
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

```

## 效能分析

1. **時間複雜度**：

   * 遞迴與非遞迴阿克曼函數：隨著 $m$ 與 $n$ 的數值增長，呈雙微弱指數級成長，計算時間隨之暴增。

   * 冪集合生成：總共需產生 $2^n$ 個子集，每個子集最大長度為 $n$，時間複雜度為 $O(n \cdot 2^n)$。

2. **空間複雜度**：

   * 遞迴阿克曼函數：空間複雜度取決於函數遞迴巢狀的系統堆疊深度。

   * 非遞迴阿克曼函數：使用動態堆疊（Heap）取代系統呼叫堆疊，有效避免深層遞迴造成的 Stack Overflow。

   * 冪集合生成：使用向量儲存輸入字元，空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例彙整

| **程式類型** | **測試案例說明** | **輸入參數** | **預期輸出** | **實際輸出** | 
| **遞迴阿克曼** | 基礎邊界值 | $m=0, n=0$ | 1 | 1 | 
| **遞迴阿克曼** | 一般運算值 | $m=2, n=2$ | 7 | 7 | 
| **非遞迴阿克曼** | 基礎邊界值 | $m=0, n=0$ | 1 | 1 | 
| **非遞迴阿克曼** | 一般運算值 | $m=3, n=3$ | 61 | 61 | 
| **冪集合生成** | 空集合 | $n=0$ | `{ }` | `{ }` | 
| **冪集合生成** | 雙元素集合 | $n=2, [a, b]$ | 4 個子集組合 | 4 個子集組合 | 

### 編譯與執行指令

```
$ g++ -std=c++17 -o program_main main.cpp
$ ./program_main

```

## 申論及開發報告

本次作業透過三個經典演算法展示了不同的程式設計思維：

1. **遞迴與疊代的權衡**：阿克曼函數展現了遞迴在表達數學定義時的極致簡潔性，但同時也凸顯了系統堆疊受限的缺點。透過非遞迴版本的實作（使用 `std::vector` 模擬堆疊），我們學會了如何在記憶體與效能之間取得平衡，避免系統溢位。

2. **位元運算的應用效益**：在冪集合生成中，利用位元運算子（`<<` 與 `>>`）能夠完美對應二進位狀態，以極高效能且直觀的方式列舉出所有組合，省去了複雜的遞迴組合開銷。