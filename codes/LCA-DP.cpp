// Este codigo foi testado no problema LCA - Lowest Common Ancestor do SPOJ
// URL do problema: https://www.spoj.com/problems/LCA/

#include <bits/stdc++.h>
using namespace std;

int profundidade[1005], baldeAnterior[1005], pai[1005], raizQuadrada, pd[1005][15], alturaMaxima = 1;
vector <int> filhos[1005];

void CalculaProfundidade(int vertice, int nivel) {
	profundidade[vertice] = nivel;
	alturaMaxima = max(alturaMaxima, nivel);
	for (int filho : filhos[vertice]) {
		CalculaProfundidade(filho, nivel+1);
	}
}

void CalculaPD(int qntdVertices) {
	alturaMaxima = floor(log(qntdVertices));
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
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int qntdTestes, qntdVertices, qntdFilhos, filho, raiz, qntdPerguntas, a, b;
	cin >> qntdTestes;
	memset(pai, -1, sizeof(pai));
	for (int test = 1; test <= qntdTestes; test++) {
		cin >> qntdVertices;
		raizQuadrada = ceil(sqrt(qntdVertices));
		for (int parentNode = 1; parentNode <= qntdVertices; parentNode++) {
			filhos[parentNode].clear();
			cin >> qntdFilhos;
			while (qntdFilhos--) {
				cin >> filho;
				pai[filho] = parentNode;
				filhos[parentNode].push_back(filho);
			}
		}
		for (int node = 1; node <= qntdVertices; node++) {
			if (pai[node] == -1) {
				raiz = node;
				pai[raiz] = raiz;
				break;
			}
		}

		CalculaProfundidade(raiz, 1);
		CalculaPD(qntdVertices);
		cin >> qntdPerguntas;
		cout << "Case " << test << ":\n";
		while (qntdPerguntas--) {
			cin >> a >> b;
			cout << LCA(a,b) << '\n';
		}
	}
	return 0;
}