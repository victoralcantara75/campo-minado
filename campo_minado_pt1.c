#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAM 11


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

void imprimir_matriz(char matriz[TAM][TAM]){

	printf("  ");
	for (int i=1; i< TAM-1; i++)
		printf("%d ", i);

	printf("\n\n");
	for (int i=1; i< TAM-1; i++)
	{
		printf("%d ", i);
		for (int j=1; j< TAM-1; j++)
		{
			printf("%c ", matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void imprimir_inicial(){
	printf("  ");
	for (int i=1; i< TAM-1; i++)
		printf("%d ", i);
	printf("\n\n");
	for (int i=1; i< TAM-1; i++)
	{
		printf("%d ", i);
		for (int j=1; j< TAM-1; j++)
		{
			printf("- ");
		}
		printf("\n");
	}
	printf("\n");
}

void imprimir_jogo(char matriz[TAM][TAM], char matriz_hide[TAM][TAM], int i, int j,int escolha, int *bandeiras){
	
	if (escolha == 1 && matriz_hide[i][j] != '@')
	{
		matriz_hide[i][j] = matriz[i][j];

	}

	else if(escolha == 2){
		if (*bandeiras == 0)
		{
			printf("Não ha mais bandeiras !\n");
		}
		else 
		{
			matriz_hide[i][j] = '@';
			(*bandeiras)--;
		}
	}

	else if (escolha == 3 && matriz_hide[i][j] == '@'){
		matriz_hide[i][j] = '-';
		(*bandeiras)++;
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

int menu(){

	int opcao;

	printf("\n");
	printf("1 - JOGAR \n");
	printf("2 - RECORDES \n");
	printf("0 - SAIR\n");
	printf("\n");

	printf("Escolha sua opcao: ");
	scanf("%d", &opcao);

	return opcao;
}

int main(){
	
	char matriz[TAM][TAM];
	char matriz_hide[TAM][TAM];

	int perdeu =0, ganhou =0, escolha, primeira = 1, opcao, bandeiras = 10;
	int x, y;

	system("cls||clear");
	
	do{
		
		opcao = menu();
		switch(opcao){

			case 0:
				break;

			case 1:

				system("cls||clear");
				imprimir_inicial();
				while(ganhou == 0 && perdeu == 0)
				{
					printf(" |>\n");
					printf(" | Bandeiras: %d\n", bandeiras);
					printf("\n");
					printf("1 - COORDENADAS\n");
					printf("2 - MARCAR BOMBA\n");
					printf("3 - DESMARCAR BOMBA\n");
					printf("escolha: ");

					scanf("%d", &escolha);

					if (escolha == 1)
						printf("COORDENADAS: ");
					if (escolha == 2)
						printf("MARCAR BOMBA: ");
					if (escolha == 3)
						printf("DESMARCAR BOMBA: ");

					scanf("%d %d", &x, &y);

					if(primeira == 1){
						carregar_tabuleiro(matriz, matriz_hide, x, y);
						primeira = 0;
					}

					if (escolha == 1 && matriz[x][y] == '0')
					{
						perdeu = 1;
					}
					
					system("cls||clear");
					imprimir_jogo(matriz, matriz_hide, x, y, escolha, &bandeiras);

					ganhou = ganhar(matriz_hide);

				}
				primeira = 1;
				break;

			case 2:
				system("cls||clear");
				printf("Estamos trabalhando nessa parte ;) \n");
				printf("\n");
				break;

			default:
				system("cls||clear");
				printf("Opcao invalida\n");
				break;
		}
		
		if (perdeu == 1)
		{
			perdeu = 0;
			printf("SINTO MUITO, VOCE PERDEU :(\n\n");
		}
		if (ganhou == 1)
		{
			ganhou = 0;
			printf("PARABENS, VOCE GANHOU :)\n\n");
		}


	}while(opcao != 0);

	return 0;
}