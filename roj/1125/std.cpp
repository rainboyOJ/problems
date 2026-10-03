/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 21:47
 * update_at: 2026-10-02 21:47
 */
// std.cpp：矩阵乘法标准解，三层循环 O(n*m*k)，n、m、k < 100 时最多约 10^6 次运算。
#include <iostream>
using namespace std;

const int MAXN = 105; // 题面保证 n、m、k 均小于 100

int n, m, k;
int a[MAXN][MAXN];      // A 矩阵，n 行 m 列
int b[MAXN][MAXN];      // B 矩阵，m 行 k 列
long long c[MAXN][MAXN]; // 结果矩阵 C，n 行 k 列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < k; j++)
            cin >> b[i][j];

    // C[i][j] = sum_{t=0}^{m-1} A[i][t] * B[t][j]
    // 最坏情形 |C[i][j]| <= 99 * 1000 * 1000 = 9.9e7，int 不会溢出，
    // 但中间结果统一用 long long 累加，避免以后放宽数据范围时出错。
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            long long sum = 0;
            for (int t = 0; t < m; t++)
                sum += (long long)a[i][t] * b[t][j];
            c[i][j] = sum;
        }
    }

    // 输出 n 行，每行 k 个整数，整数之间一个空格（题面要求，不带取模）
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            if (j > 0) cout << ' ';
            cout << c[i][j];
        }
        cout << '\n';
    }

    return 0;
}
