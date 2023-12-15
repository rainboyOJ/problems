#include <fstream>
#include <algorithm>

using namespace std;

int main() {
    int F, N, M, W;
    ifstream in("wormhole.in");
    ofstream out("wormhole.out");

    in >> F;
    for (int f = 0; f < F; f++) {
        int A[6000], B[6000], T[6000], P = 0;
        bool cycle = false;
        int dist[500];

        in >> N >> M >> W;
        memset(dist, 0, sizeof(dist));
        for (int i = 0; i < M; i++) {
            in >> A[P] >> B[P] >> T[P];
            A[P]--;
            B[P]--;
            A[P + 1] = B[P];
            B[P + 1] = A[P];
            T[P + 1] = T[P];
            P += 2;
        }
        for (int i = 0; i < W; i++) {
            in >> A[P] >> B[P] >> T[P];
            A[P]--;
            B[P]--;
            T[P] = -T[P];
            P++;
        }

        for (int r = 0; r <= N; r++)
            for (int i = 0; i < P; i++)
                dist[B[i]] <?= dist[A[i]] + T[i];
        for (int i = 0; i < P; i++)
            if (dist[B[i]] > dist[A[i]] + T[i])
                cycle = true;
        out << (cycle ? "YES\n" : "NO\n");
    }
    return 0;
}
