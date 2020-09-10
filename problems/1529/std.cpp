#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MaxN = 100000;
const int MaxM = 200000;

inline int getint()
{
	char c;
	while (c = getchar(), '0' > c || c > '9');

	int res = c - '0';
	while (c = getchar(), '0' <= c && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

struct halfEdge
{
	int u;
	bool used;
	halfEdge *next;
};
halfEdge adj_pool[MaxM * 2], *adj_tail = adj_pool;

int tour_n = 0;
int tour[MaxM];

int n, m;
halfEdge *adj[MaxN + 1];

inline void addEdge(int v, int u)
{
	adj_tail->u = u, adj_tail->used = false, adj_tail->next = adj[v], adj[v] = adj_tail++;
}

namespace UndirectedCase
{
	inline halfEdge *oppo(halfEdge *e)
	{
		return adj_pool + ((e - adj_pool) ^ 1);
	}
	inline int eid(halfEdge *e)
	{
		int id = (e - adj_pool) / 2 + 1;
		return (e - adj_pool) % 2 == 0 ? id : -id;
	}
	void dfs(int v)
	{
		while (adj[v])
		{
			if (!adj[v]->used)
			{
				halfEdge *e = adj[v];
				e->used = true, oppo(e)->used = true;
				dfs(e->u);
				tour[tour_n++] = eid(e);
			}
			else
				adj[v] = adj[v]->next;
		}
	}

	bool solve()
	{
		static int deg[MaxN + 1];

		n = getint(), m = getint();
		for (int i = 1; i <= m; i++)
		{
			int v = getint(), u = getint();
			addEdge(v, u), addEdge(u, v);
			deg[v]++, deg[u]++;
		}

		for (int v = 1; v <= n; v++)
			if (deg[v] % 2 != 0)
				return false;
		for (int v = 1; v <= n; v++)
			if (adj[v])
			{
				dfs(v);
				break;
			}
		for (int v = 1; v <= n; v++)
			if (adj[v])
				return false;
		reverse(tour, tour + tour_n);
		return true;
	}
}
namespace DirectedCase
{
	inline int eid(halfEdge *e)
	{
		return e - adj_pool + 1;
	}
	void dfs(int v)
	{
		while (adj[v])
		{
			if (!adj[v]->used)
			{
				halfEdge *e = adj[v];
				e->used = true;
				dfs(e->u);
				tour[tour_n++] = eid(e);
			}
			else
				adj[v] = adj[v]->next;
		}
	}

	bool solve()
	{
		static int deg[MaxN + 1];

		n = getint(), m = getint();
		for (int i = 1; i <= m; i++)
		{
			int v = getint(), u = getint();
			addEdge(v, u);
			deg[v]--, deg[u]++;
		}

		for (int v = 1; v <= n; v++)
			if (deg[v] != 0)
				return false;
		for (int v = 1; v <= n; v++)
			if (adj[v])
			{
				dfs(v);
				break;
			}
		for (int v = 1; v <= n; v++)
			if (adj[v])
				return false;
		reverse(tour, tour + tour_n);
		return true;
	}
}

int main()
{
	int type = getint();

	if (type == 1 ? UndirectedCase::solve() : DirectedCase::solve())
	{
		cout << "YES" << endl;
		for (int i = 0; i < tour_n; i++)
			printf("%d ", tour[i]);
		printf("\n");
	}
	else
		cout << "NO" << endl;

	return 0;
}
