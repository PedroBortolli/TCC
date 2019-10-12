#include <bits/stdc++.h>
using namespace std;

const int N = 1e4+5;

bool visto[N];
int profundidade[N], pai[N], pd[N][15], alturaMaxima = 13, somaAc[N];
vector <int> adj[N];
map<pair <int, int>, int> custo;
char s[10];

void CalculaProfundidade(int vertice, int nivel, int soma) {
	visto[vertice] = true;
	profundidade[vertice] = nivel;
	somaAc[vertice] = soma;
	for (int filho : adj[vertice]) {
		if (!visto[filho]) {
			CalculaProfundidade(filho, nivel+1, soma+custo[{vertice, filho}]);
			pai[filho] = vertice;
		}
	}
}

void CalculaPD(int qntdVertices) {
	for (int vertice = 1; vertice <= qntdVertices; vertice++)
		pd[vertice][0] = pai[vertice];
	for (int exp = 1; exp <= alturaMaxima; exp++) {
		for (int vertice = 1; vertice <= qntdVertices; vertice++)
				pd[vertice][exp] = pd[pd[vertice][exp-1]][exp-1];
	}
}

int LCA(int a, int b) {
	if (profundidade[b] < profundidade[a]) swap(a, b);
	for (int i = alturaMaxima; i >= 0; i--) {
		if (profundidade[b] - (1 << i) >= profundidade[a])
			b = pd[b][i];
	}
	if (a == b) return a;
	for (int i = alturaMaxima; i >= 0; i--) {
		if (pd[a][i] != pd[b][i])
			a = pd[a][i], b = pd[b][i];
	}
	return pai[a];
}

int main() {
	int t, n, a, b, c, k;
	scanf("%d", &t);
	while (t--) {
		// Resetando variaveis globais utilizadas para cada caso de teste
		for (int i = 0; i < N; i++) {
			pai[i] = 0, profundidade[i] = 0, somaAc[i] = 0, visto[i] = false;
			adj[i].clear();
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 15; j++) {
				pd[i][j] = 0;
			}
		}
		custo.clear();


		scanf("%d", &n);
		for (int i = 0; i < n-1; i++) {
			scanf("%d %d %d", &a, &b, &c);
			adj[a].push_back(b);
			adj[b].push_back(a);
			custo[{a, b}] = c;
			custo[{b, a}] = c;
			pai[i+1] = i+1;
		}
		pai[n] = n;

		CalculaProfundidade(1, 1, 0);
		CalculaPD(n);

		while (1) {
			scanf(" %s", s);
			if (s[1] == 'O') break;
			scanf("%d %d", &a, &b);
			int lca = LCA(a, b);
			if (s[1] == 'I') printf("%d\n", somaAc[a] + somaAc[b] - 2*somaAc[lca]);
			else if (s[1] == 'T') {
				scanf("%d", &k);
				int qntA = profundidade[a]-profundidade[lca]+1;
				int qntB = profundidade[b]-profundidade[lca];
				if (k <= qntA) {
					// o k-esimo vertice esta no caminho do vertice a para o LCA
					int alvo = k-1;
					for (int i = alturaMaxima; i >= 0; i--) {
						if ((1 << i) <= alvo) {
							alvo -= (1 << i);
							a = pd[a][i];
						}
					}
					printf("%d\n", a);
				}
				else {
					// o k-esimo vertice esta no caminho do vertice b para o LCA
					int alvo = qntB + qntA - k;
					for (int i = alturaMaxima; i >= 0; i--) {
						if ((1 << i) <= alvo) {
							alvo -= (1 << i);
							b = pd[b][i];
						}
					}
					printf("%d\n", b);
				}
			}
		}
		printf("\n");
	}
	return 0;
}
