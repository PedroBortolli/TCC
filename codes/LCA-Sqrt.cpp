// Este codigo foi testado no problema LCA - Lowest Common Ancestor do SPOJ
// URL do problema: https://www.spoj.com/problems/LCA/

#include <bits/stdc++.h>
using namespace std;

int profundidade[1005], baldeAnterior[1005], pai[1005], raizQuadrada;
vector <int> filhos[1005];

void CalculaProfundidade(int vertice, int nivel, int ancestralAnterior) {
	profundidade[vertice] = nivel;
	baldeAnterior[vertice] = ancestralAnterior;
	int anterior = ancestralAnterior;
	if (nivel % raizQuadrada == 0) anterior = vertice;
	for (int filho : filhos[vertice])
		CalculaProfundidade(filho, nivel+1, anterior);
}

int LCA_Simples(int a, int b) {
	if (profundidade[a] < profundidade[b])
		swap(a,b);
	while (profundidade[a] > profundidade[b])
		a = pai[a];
	while (a != b) {
		a = pai[a];
		b = pai[b];
	}
	return a;
}

int LCA(int a, int b) {
	while (baldeAnterior[a] != baldeAnterior[b]) {
		if (profundidade[a] < profundidade[b]) swap(a, b);	
		a = baldeAnterior[a];
	}
	return LCA_Simples(a, b);
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
				break;
			}
		}

		CalculaProfundidade(raiz, 1, raiz);
		cin >> qntdPerguntas;
		cout << "Case " << test << ":\n";
		while (qntdPerguntas--) {
			cin >> a >> b;
			cout << LCA(a,b) << '\n';
		}
	}
	return 0;
}