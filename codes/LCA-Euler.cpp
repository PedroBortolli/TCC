#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5, INF = 1e9+7;

bool visitado[N];
int m, profundidade[N], tempo[N], contador = 0, arvoreSeg[4*N][2];
long long pd[N];
vector <int> adj[N];
map<pair <int, int>, int> custo;


// Constroi uma arvore de segmentos de duas dimensoes
// -----------------------------------------------------------------
// a primeira possui as profundidades dos vertices
// -----------------------------------------------------------------
// na segunda e feito o mapeamento para saber qual vertice da arvore
// original este no da arvore de segmentos representa
void Constroi() {
	for (int i = m; i > 0; i--) {
		if (arvoreSeg[2*i][0] < arvoreSeg[2*i+1][0]) {
			arvoreSeg[i][0] = arvoreSeg[2*i][0];
			arvoreSeg[i][1] = arvoreSeg[2*i][1];
		}
		else {
			arvoreSeg[i][0] = arvoreSeg[2*i+1][0];
			arvoreSeg[i][1] = arvoreSeg[2*i+1][1];	
		}
	}
}

// Consulta o menor elemento no intervalo [esquerda, direita)
// -----------------------------------------------------------------
// aqui, o "menor" elemento significa o que tem a menor profundidade
// - ou seja - menor valor em sua primeira dimensao
// -----------------------------------------------------------------
// retorna o identificador de tal vertice - ou seja - o valor em sua
// segunda dimensao
int Consulta(int esquerda, int direita) {
	int resposta = arvoreSeg[esquerda][1], profMinima = INF;   // profMinima = infinito
	esquerda += m, direita += m+1;
	while (esquerda < direita) {
		if (esquerda % 2 != 0) {
			if (arvoreSeg[esquerda][0] < profMinima) {
				profMinima = arvoreSeg[esquerda][0];
				resposta = arvoreSeg[esquerda][1];
			}
			esquerda++;
		}
		if (direita % 2 != 0) {
			direita--;			
			if (arvoreSeg[direita][0] < profMinima) {
				profMinima = arvoreSeg[direita][0];
				resposta = arvoreSeg[direita][1];
			}
		}
		esquerda /= 2;
		direita /= 2;
	}
	return profMinima == INF ? arvoreSeg[esquerda][1] : resposta;
}

// Calcula a programacao dinamica da soma dos pesos das arestas
// do caminho entre a raiz e todo vertice da arvore
void CalculaPD(int vertice, int prof, long long soma) {
	visitado[vertice] = true;
	profundidade[vertice] = prof;
	pd[vertice] = soma;
	for (int filho : adj[vertice]) {
		if (!visitado[filho])  {
			CalculaPD(filho, prof + 1, soma + custo[{vertice, filho}]);
		}
	}

}

// Faz o passeio de euler na arvore, montando a arvore de segmentos
// utilizada para determinar o LCA
void Euler(int vertice) {
	visitado[vertice] = true;
	for (int filho : adj[vertice]) {
		if (!visitado[filho]) {
			arvoreSeg[contador+m][0] = profundidade[vertice];
			arvoreSeg[contador+m][1] = vertice;
			contador++;
			Euler(filho);
		}
	}
	tempo[vertice] = contador;
	arvoreSeg[contador+m][0] = profundidade[vertice];
	arvoreSeg[contador+m][1] = vertice;
	contador++;
}

// Retorna o LCA entre os vertices a e b utilizando a funcao Consulta
int LCA(int a, int b) {
	int esquerda = tempo[a];
	int direita = tempo[b];
	if (esquerda > direita) swap(esquerda, direita);
	return Consulta(esquerda, direita);
}



int main() {
	int n, v2, comprimento, q, s, t;

	while(1) {
		scanf("%d", &n);
		if (!n) break;
		
		m = 2*n - 1;   // m = quantidade de vertices na arvore (seguindo Euler): #vertices + #arestas

		// Abaixo sao resetadas as variaveis globais que sao utilizadas em cada caso de teste do problema
		contador = 0;
		for (int i = 0; i < m; i++) adj[i].clear(), pd[i] = 0, tempo[i] = 0, profundidade[i] = 0, visitado[i] = false;
		for (int i = 0; i < 2*m; i++) arvoreSeg[i][0] = INF, arvoreSeg[i][1] = 0;
		custo.clear();

		for (int v1 = 1; v1 < n; v1++) {
			scanf("%d %d", &v2, &comprimento);
			adj[v1].push_back(v2);
			adj[v2].push_back(v1);
			custo[{v1, v2}] = comprimento;
			custo[{v2, v1}] = comprimento;
		}

		CalculaPD(0, 1, 0);
		memset(visitado, false, sizeof(visitado));
		Euler(0);
		Constroi();

		scanf("%d", &q);
		while (q--) {
			scanf("%d %d", &s, &t);
			int lca = LCA(s, t);
			printf("%lld%c", pd[s] + pd[t] - 2*pd[lca], q ? ' ' : '\n');
		}
	}

	return 0;
}
