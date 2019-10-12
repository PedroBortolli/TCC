// Este codigo foi testado no problema LCA - Lowest Common Ancestor do SPOJ
// URL do problema: https://www.spoj.com/problems/LCA/

#include <bits/stdc++.h>
using namespace std;

int pai[1005], profundidade[1005];
vector <int> filhos[1005];

void CalculaProfundidade(int vertice, int nivel) {
	profundidade[vertice] = nivel;
	for (int filho : filhos[vertice]) {
		CalculaProfundidade(filho, nivel+1);
	}
}

int LCA(int a, int b) {
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

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int qntdTestes, qntdVertices, qntdFilhos, filho, raiz, qntdPerguntas, a, b;
	cin >> qntdTestes;
	memset(pai, -1, sizeof(pai));
	for (int test = 1; test <= qntdTestes; test++) {
		cin >> qntdVertices;
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
		CalculaProfundidade(raiz, 1);
		cin >> qntdPerguntas;
		cout << "Case " << test << ":\n";
		while (qntdPerguntas--) {
			cin >> a >> b;
			cout << LCA(a,b) << '\n';
		}
	}
	return 0;
}