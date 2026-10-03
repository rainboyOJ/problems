// 数独解计数器（DLX）：输出解的个数（最多数到 2）
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
static const int N = 16;
static const int NC = N * N * 4;
static const int MAXR = N * N * N + 5;
static const int MAXNODE = MAXR * 4 + NC + 5;
int L[MAXNODE], R[MAXNODE], U[MAXNODE], D[MAXNODE], rowOf[MAXNODE], colHead[MAXNODE];
int colSize[NC + 5], headNode, nodeCnt;
void initDLX(int nCol) {
    headNode = 0; L[0] = nCol; R[0] = 1;
    for (int i = 1; i <= nCol; i++) { L[i] = i-1; R[i] = i+1; U[i] = i; D[i] = i; colSize[i] = 0; }
    R[nCol] = 0; nodeCnt = nCol;
}
void addRow(int cols[], int k, int rIdx) {
    if (!k) return;
    int first = nodeCnt + 1;
    for (int i = 0; i < k; i++) {
        int c = cols[i], nd = ++nodeCnt;
        rowOf[nd] = rIdx; colHead[nd] = c;
        U[nd] = U[c]; D[nd] = c; D[U[c]] = nd; U[c] = nd; colSize[c]++;
        if (i == 0) { L[nd] = nd; R[nd] = nd; }
        else { L[nd] = nodeCnt-1; R[nd] = first; R[nodeCnt-1] = nd; L[first] = nd; }
    }
}
void cover(int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) for (int j = R[i]; j != i; j = R[j]) {
        U[D[j]] = U[j]; D[U[j]] = D[j]; colSize[colHead[j]]--;
    }
}
void uncover(int c) {
    for (int i = U[c]; i != c; i = U[i]) for (int j = L[i]; j != i; j = L[j]) {
        colSize[colHead[j]]++; U[D[j]] = j; D[U[j]] = j;
    }
    L[R[c]] = c; R[L[c]] = c;
}
int solCount = 0;
void searchK(int limit) {
    if (solCount >= limit) return;
    if (R[headNode] == headNode) { solCount++; return; }
    int c = R[headNode], best = colSize[c];
    for (int j = R[c]; j != headNode; j = R[j]) if (colSize[j] < best) { best = colSize[j]; c = j; }
    cover(c);
    for (int i = D[c]; i != c && solCount < limit; i = D[i]) {
        for (int j = R[i]; j != i; j = R[j]) cover(colHead[j]);
        searchK(limit);
        for (int j = L[i]; j != i; j = L[j]) uncover(colHead[j]);
    }
    uncover(c);
}
int main() {
    vector<string> lines; string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        lines.push_back(line);
        if ((int)lines.size() < N) continue;
        initDLX(NC);
        int given[N][N];
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
            char ch = lines[i][j];
            given[i][j] = (ch == '-') ? -1 : ch - 'A';
        }
        int rIdx = 1;
        for (int r = 0; r < N; r++) for (int c = 0; c < N; c++) for (int v = 0; v < N; v++) {
            if (given[r][c] != -1 && given[r][c] != v) continue;
            int cols[4] = {1 + r*16 + c, 1 + 256 + r*16 + v, 1 + 512 + c*16 + v,
                           1 + 768 + ((r >> 2) * 4 + (c >> 2)) * 16 + v};
            addRow(cols, 4, rIdx++);
        }
        solCount = 0;
        searchK(2);
        printf("%d\n", solCount);
        lines.clear();
    }
    return 0;
}
