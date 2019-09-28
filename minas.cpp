#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <string.h>
#define TAM 11
using namespace std;

// ========================= CARREGAR TABULEIRO ============================
void carregar_tabuleiro(char matriz[TAM][TAM],char matriz_hide[TAM][TAM], int x, int y){
	int bombaX, bombaY;
	
	for (int i=0; i<TAM; i++)
	{
		for (int j=0; j<TAM; j++)
		{
			matriz[i][j] = ' ';
		}
	}

	for (int i=0; i<TAM; i++)
	{
		for (int j=0; j<TAM; j++)
		{
			matriz_hide[i][j] = '-';
		}
	}
	
	srand (time(NULL));
	//srand(42);

	for (int i=0; i<10; i++){
		
		do{
		
			bombaX = rand()% 9 + 1;
			bombaY = rand()% 9 + 1;
		
		}while((matriz[bombaX][bombaY] == '0' || (bombaX == x && bombaY == y)));
		
		matriz[bombaX][bombaY] = '0';
	}

	for (int i=1; i< TAM-1; i++)
	{
		for (int j=1; j< TAM-1; j++)
		{
			int cont = 0;
			if (matriz[i][j] != '0')
			{	

				if (matriz[i][j-1] == '0')
					cont++;
				if (matriz[i-1][j-1] == '0')
					cont++;	
				if (matriz[i][j+1] == '0')
					cont++;
				if (matriz[i+1][j+1] == '0')
					cont++;
				if (matriz[i+1][j] == '0')
					cont++;
				if (matriz[i+1][j-1] == '0')
					cont++;
				if (matriz[i-1][j+1] == '0')
					cont++;
				if (matriz[i-1][j] == '0')
					cont++;
					
				if(cont != 0) matriz[i][j] = cont+'0';
			}
		}
	}
}
// ========================= CARREGAR TABULEIRO ============================

void inicializar_matriz(int matriz[TAM][TAM]){
	for (int i=0; i<TAM; i++)
	{
		for (int j=0; j<TAM; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

void imprimir_matriz(char matriz[TAM][TAM]){
	cout << "   ";
	for (int i=1; i< TAM-1; i++)
		cout << i << " ";
	cout << endl << endl;
	for (int i=1; i< TAM-1; i++)
	{
		cout << i << "  ";
		for (int j=1; j< TAM-1; j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void imprimir_inicial(){
	cout << "   ";
	for (int i=1; i< TAM-1; i++)
		cout << i << " ";
	cout << endl << endl;
	for (int i=1; i< TAM-1; i++)
	{
		cout << i << "  ";
		for (int j=1; j< TAM-1; j++)
		{
			cout << '-' << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void liberar_casas1(char matriz[TAM][TAM], char matriz_hide[TAM][TAM], int visitados[TAM][TAM], int i, int j){

	matriz_hide[i][j] = matriz[i][j];

	visitados[i][j] = 1;

	if (matriz[i][j] != ' ')
	{	
		return;
	}

	if (i != 1)
	{
		if (visitados[i-1][j] == 0)
			liberar_casas1(matriz, matriz_hide,visitados, i-1, j);
		if (j != 1)
			if (visitados[i-1][j-1] == 0)
				liberar_casas1(matriz, matriz_hide,visitados, i-1, j-1);
		if (j != TAM-2)
			if (visitados[i-1][j+1] == 0)
				liberar_casas1(matriz, matriz_hide,visitados, i-1, j+1);
	}

	if (i != TAM-2)
	{
		if (visitados[i+1][j] == 0)
			liberar_casas1(matriz, matriz_hide,visitados, i+1, j);
		
		if (j != 1)
			if (visitados[i+1][j-1] == 0)
				liberar_casas1(matriz, matriz_hide,visitados, i+1, j-1);
		if ( j != TAM-2)
			if (visitados[i+1][j+1] == 0)
				liberar_casas1(matriz, matriz_hide,visitados, i+1, j+1);
	}

	
	if (j != 1)
	{
		if (visitados[i][j-1] == 0)
			liberar_casas1(matriz, matriz_hide,visitados, i, j-1);
	}
	
	if (j != TAM-2)
	{
		if (visitados[i][j+1] == 0)
			liberar_casas1(matriz, matriz_hide,visitados, i, j+1);
	}

	return;
}

void imprimir_jogo(char matriz[TAM][TAM], char matriz_hide[TAM][TAM],int visitados[TAM][TAM], int i, int j,int escolha){
	
	if(escolha == 2)
		matriz_hide[i][j] = '@';

	else
	{
		matriz_hide[i][j] = matriz[i][j];

		if(matriz[i][j] == ' ')
			liberar_casas1(matriz, matriz_hide, visitados, i, j);
	}
	

	imprimir_matriz(matriz_hide);
}

int ganhar(char matriz_hide[TAM][TAM]){
	for (int i = 1; i < TAM-1; ++i)
	{
		for (int j = 1; j < TAM-1; ++j)
		{
			if (matriz_hide[i][j] == '-')
			{
				return 0;
			}
		}
	}
	return 1;
}

int main(){
	
	char matriz[TAM][TAM];
	char matriz_hide[TAM][TAM];
	int visitados[TAM][TAM];

	int perdeu =0, ganhou =0, escolha, primeira = 1;
	int x, y, bomba;

	printf("\e[H\e[2J");
	imprimir_inicial();

	inicializar_matriz(visitados);
	

	while(ganhou == 0 && perdeu == 0)
	{
		cout << "1 - COORDENADAS" << endl;
		cout << "2 - MARCAR BOMBA" << endl;
		cout << "3 - DESMARCAR BOMBA" << endl;
		cout << "escolha: ";
		cin >> escolha;

		if (escolha == 1)
			cout << "COORDENADAS: ";
		if (escolha == 2)
			cout << "MARCAR BOMBA: ";
		if (escolha == 3)
			cout << "DESMARCAR BOMBA: ";

		cin >> x >> y ;

		if(primeira == 1){
			carregar_tabuleiro(matriz, matriz_hide, x, y);
		}

		if (escolha == 1 && matriz[x][y] == '0')
		{
			perdeu = 1;
		}
		
		printf("\e[H\e[2J");
		imprimir_jogo(matriz, matriz_hide,visitados, x, y, escolha);

		ganhou = ganhar(matriz_hide);
		primeira = 0;

	}
	
	if (perdeu == 1)
		cout << "SINTO MUITO, VOCE PERDEU :(" << endl;
	if (ganhou == 1)
		cout << "PARABENS, VOCE GANHOU :)" << endl;

	return 0;
}