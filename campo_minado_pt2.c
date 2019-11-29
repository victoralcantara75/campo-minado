#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct sRec{
	char nome[20];
	float tempo;
	int lin, col, bombas;
}recordes;

void carregar_tabuleiro(char **matriz,char **matriz_viz, int x, int y, int tamlin, int tamcol, int numbomb){
	// Coordenadas para as bombas
	int bombaX, bombaY;
	int i, j;
	
	// Inicializa as matrizes do jogo
	for (i=0; i<tamlin; i++)
	{
		for (j=0; j<tamcol; j++)
		{
			matriz[i][j] = ' ';
		}
	}
	for (i=0; i<tamlin; i++)
	{
		for (j=0; j<tamcol; j++)
		{
			matriz_viz[i][j] = '-';
		}
	}
	
	srand (time(NULL));

	// Coloca o numero de bombas desejadas
	for (i=0; i<numbomb; i++){
		
		do{
			// Numeros aleatorios para x e y da bomba
			bombaX = rand()% (tamlin-2) + 1;
			bombaY = rand()% (tamcol-2) + 1;
			

		}while((matriz[bombaX][bombaY] == '0' || (bombaX == x && bombaY == y))); // Repete caso ja tiver bomba na posicao ou for a primeira coordenada digitada pelo jogador
		
		matriz[bombaX][bombaY] = '0';
	}

	// Coloca os numeros em volta da bomba
	// Percorre toda a matriz, conta as bombas nas 8 posicoes em volta
	// O numero encontrado é colocado na matriz
	for (i=1; i< tamlin-1; i++)
	{
		for (j=1; j< tamcol-1; j++)
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
				
				// +'0' para o cont se tornar char 
				if(cont != 0) matriz[i][j] = cont+'0';
			}
		}
	}
}

void inicializar_matriz(int **matriz, int tamlin, int tamcol){
	
	int i, j;
	// Inicializa a matriz de visitados todos com 0 (false)
	for (i=0; i<tamlin; i++)
	{
		for (j=0; j<tamcol; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

void imprimir_matriz(char **matriz, int tamlin, int tamcol){

	int i, j;
	
	// Imprime o numero das colunas
	printf("  ");
	for (i=1; i< tamcol-1; i++)
		printf("%d ", i);

	// Imprime o numero das linhas e a matriz
	printf("\n\n");
	for (i=1; i< tamlin-1; i++)
	{
		printf("%d ", i);
		for (j=1; j< tamcol-1; j++)
		{
			printf("%c ", matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void imprimir_inicial(int tamlin, int tamcol){
	int i,j;
	printf("  ");
	for (i=1; i< tamcol-1; i++)
		printf("%d ", i);
	printf("\n\n");
	for (i=1; i< tamlin-1; i++)
	{
		printf("%d ", i);
		for (j=1; j< tamcol-1; j++)
		{
			printf("- ");
		}
		printf("\n");
	}
	printf("\n");
}

void liberar_casas(char **matriz, char **matriz_viz, int **visitados, int i, int j, int tamlin, int tamcol){

	// Atualiza a matriz que o jogador ve (abrir o quadradinho)
	matriz_viz[i][j] = matriz[i][j];
	// Marca esse quadradinho como visitado
	visitados[i][j] = 1;

	// Caso base, se a posicao for uma fronteira retorna
	if (matriz[i][j] != ' ')
	{	
		return;
	}

	// Verifica se os 8 espaços em volta sao espaços vazios para abrir ate uma fronteira (numero ou fim do tabuleiro)
	// Chama a funcao recursivamente para cada um dos 8 espaços possiveis
	
	
	// Caso nao seja a primeira linha posso chamar a funcao pra linha de cima
	if (i != 1)
	{
		if (visitados[i-1][j] == 0)
			liberar_casas(matriz, matriz_viz,visitados, i-1, j, tamlin, tamcol);
		// Caso nao seja a primeira coluna posso chamar pra coluna anterior
		if (j != 1)
			if (visitados[i-1][j-1] == 0)
				liberar_casas(matriz, matriz_viz,visitados, i-1, j-1, tamlin, tamcol);
 		// Caso nao seja a ultima coluna posso chamar pra proxima
		if (j != tamcol-2)
			if (visitados[i-1][j+1] == 0)
				liberar_casas(matriz, matriz_viz,visitados, i-1, j+1, tamlin, tamcol);
	}

	// Caso nao seja a ultima linha, posso chamar pra proxima
	if (i != tamlin-2)
	{
		if (visitados[i+1][j] == 0)
			liberar_casas(matriz, matriz_viz,visitados, i+1, j, tamlin, tamcol);
		// Caso nao seja a primeira coluna posso chamar pra coluna anterior
		if (j != 1)
			if (visitados[i+1][j-1] == 0)
				liberar_casas(matriz, matriz_viz,visitados, i+1, j-1, tamlin, tamcol);
 		// Caso nao seja a ultima coluna posso chamar pra proxima
		if ( j != tamcol-2)
			if (visitados[i+1][j+1] == 0)
				liberar_casas(matriz, matriz_viz,visitados, i+1, j+1, tamlin, tamcol);
	}

	// Caso nao seja a primeira coluna posso chamar pra coluna anterior
	if (j != 1)
	{
		if (visitados[i][j-1] == 0)
			liberar_casas(matriz, matriz_viz,visitados, i, j-1, tamlin, tamcol);
	}
	
	// Caso nao seja a ultima coluna posso chamar pra proxima
	if (j != tamcol-2)
	{
		if (visitados[i][j+1] == 0)
			liberar_casas(matriz, matriz_viz,visitados, i, j+1, tamlin, tamcol);
	}

	return;
}

void imprimir_jogo(char **matriz, char **matriz_viz,int **visitados, int i, int j,int escolha, int *bandeiras, int tamlin, int tamcol){
	
	// Se o usuario quer abrir a posicao e ela nao esta marcada com uma bandeira
	if (escolha == 1 && matriz_viz[i][j] != '@')
	{
		// Atualiza a matriz que o jogador ve com o valor real
		matriz_viz[i][j] = matriz[i][j];

		// Se for um espaço em branco, abre os espaços ate uma fronteira
		if(matriz[i][j] == ' ')
			liberar_casas(matriz, matriz_viz, visitados, i, j, tamlin, tamcol);
		
	}

	// Se o jogador quiser marcar uma bandeira
	else if(escolha == 2){
		// Se não houver bandeiras para utilizar
		if (*bandeiras == 0)
		{
			printf("Não ha mais bandeiras !\n");
		}
		else 
		{	
			// Se o jogador ainda nao abriu aquela posicao
			if (matriz_viz[i][j] == '-'){
				// Marca o tabuleiro com a bandeira e diminui uma bandeira 
				matriz_viz[i][j] = '@';
				(*bandeiras)--;
			}
			
		}
	}

	// Se o jogador quiser desmarcar uma bandeira verifica se realmente a posicao esta marcada e desfaz
	else if (escolha == 3 && matriz_viz[i][j] == '@'){
		matriz_viz[i][j] = '-';
		(*bandeiras)++;
	}
			
	// Imprime o tabuleiro atualizado com o movimento do jogador
	imprimir_matriz(matriz_viz, tamlin, tamcol);
}

int ganhar(char **matriz, char **matriz_viz, int tamlin, int tamcol){
	
	int i, j;
	// Percorre a matriz verificando se ha numeros na matriz que ainda nao foi revelado na matriz do jogador
	// Se houver o jogador ainda nao ganhou, retorna 0;
	for (i = 1; i < tamlin-1; ++i)
	{
		for (j = 1; j < tamcol-1; ++j)
		{
			if (matriz[i][j] != ' ' && matriz[i][j] != '0' && matriz_viz[i][j] != matriz[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

int menu(){

	int opcao;
	printf("--------------------\n");
	printf("    CAMPO MINADO    \n");
	printf("--------------------\n");
	printf("\n");
	printf("1 - JOGAR \n");
	printf("2 - PERSONALIZAR TABULEIRO\n");
	printf("3 - RECORDES \n");
	printf("0 - SAIR\n");
	printf("\n");

	printf("Escolha sua opcao: ");
	scanf("%d", &opcao);

	return opcao;
}

float jogar(int tamlin, int tamcol, int numbomb){
	
	// Aumenta uma linha e uma coluna para a inicialização nao precisar verificar posicoes invalidas nas bordas, e ficar no formato coneçando do 1
	tamlin+= 2;
	tamcol+= 2;
	
	int perdeu =0, ganhou =0, escolha, primeira = 1, bandeiras = numbomb;
	int x, y, i;
	float tempo;
	clock_t cronometro;
	
	// Alocaçao das matrizes
	char **matriz = (char**)malloc(tamlin*sizeof(char*));
	for (i=0; i<tamlin; i++)
		matriz[i]=(char*)malloc(tamcol*sizeof(char));
	
	char **matriz_viz = (char**)malloc(tamlin*sizeof(char*));
	for (i=0; i<tamlin; i++)
		matriz_viz[i]=(char*)malloc(tamcol*sizeof(char));

	int **visitados = (int**)malloc(tamlin*sizeof(int*));
	for (i=0; i<tamlin; i++)
		visitados[i]=(int*)malloc(tamcol*sizeof(int));
	
	inicializar_matriz(visitados, tamlin, tamcol);

	
	system("cls||clear");
	imprimir_inicial(tamlin, tamcol);
	
	cronometro = clock();
	
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
		
		// Verificando se a posicao é valida
		if (x >= 1 && x<=tamlin-2 && y >=1 && y <= tamcol-2)
		{
			// O tabuleiro so é carregado apos a primeira coordenada do usuario
			// para evitar que ja seja uma bomba
			if(primeira == 1){
				carregar_tabuleiro(matriz, matriz_viz, x, y, tamlin, tamcol, numbomb);
				primeira = 0;
			}
	
			if (escolha == 1 && matriz[x][y] == '0')
			{
				perdeu = 1;
			}
			
			system("cls||clear");
			imprimir_jogo(matriz, matriz_viz, visitados, x, y, escolha, &bandeiras, tamlin, tamcol);
			ganhou = ganhar(matriz, matriz_viz, tamlin, tamcol);
		}
	}
	// Calcula o tempo
	cronometro = clock() - cronometro;
	tempo = cronometro / CLOCKS_PER_SEC;
	
	free(matriz);
	free(matriz_viz);
	free(visitados);
	
	if (perdeu == 1)
	{
		printf("SINTO MUITO, VOCE PERDEU :(\n\n");
		return -1;
	}
	if (ganhou == 1)
	{
		printf("PARABENS, VOCE GANHOU :)\n\n");
		printf("Tempo:%.2f s \n", tempo);
		
		return tempo;
	}
	
}

int verificar_recordes(recordes vet[5], float tempo, int tamlin, int tamcol, int numbomb){
	
	int i, posicao = -1;
	char nome[20];
	
	// Percorre o vetor de recordes verificando se o tempo é menor 
	// o vetor é inicializado com 0, os 5 primeiros tempos serao recordes
	for(i=0; i<5; i++)
	{
	 	if(tempo < vet[i].tempo || vet[i].tempo == 0)
		{
			posicao = i;
			break;
		}
	}
	
	// Se achou a posicao do novo recorde
	if(posicao != -1)
	{
		// Anda pra frente os recordes posteriores
		for (i=4; i>posicao; i--)
		{
			vet[i] = vet[i-1];
		}
		
		vet[posicao].tempo = tempo;
		printf("Voce acabou de bater um recorde, o %d° mais rapido!! \n", posicao+1);
		printf("Digite seu nome: ");
		scanf("%s", nome);
		
		strcpy(vet[posicao].nome, nome);
		vet[posicao].lin = tamlin;
		vet[posicao].col = tamcol;
		vet[posicao].bombas = numbomb;
		
		return 1;
	}
	return 0;
}

void salvar (recordes recordes_padrao[], recordes recordes_personalizado[]){
	
	int i;
	
	// Abre o arquivo para escrita, cria caso nao exista
	FILE *f = fopen("recordes.txt", "w");
	// Verifica se realmente abriu/criou arquivo
	if(f == NULL)
	{
		printf("Erro ao abrir arquivo! \n");
		return ;
	}
	
	// Escreve no arquivo
	fprintf(f, "%s", "#### RECORDES TABULEIRO PADRAO ####\n");
	for(i=0; i<5; i++)
	{
		fprintf(f, "%d", i+1);
		fprintf(f, "%s", " ");
		fprintf(f, "%s", recordes_padrao[i].nome);
		fprintf(f, "%s", " ");
		fprintf(f, "%.2f", recordes_padrao[i].tempo);
		fprintf(f, "%s", " seg\n");
	}

	fprintf(f, "%s", "#### RECORDES TABULEIRO PERSONALIZADO ####\n");
	for(i=0; i<5; i++)
	{
		fprintf(f, "%d ", i+1);
		fprintf(f, "%s ", recordes_personalizado[i].nome);
		fprintf(f, "%.2f ", recordes_personalizado[i].tempo);
		fprintf(f, "%s", "seg ");
		fprintf(f, "%d", recordes_personalizado[i].lin);
		fprintf(f, "%s", " x ");
		fprintf(f, "%d", recordes_personalizado[i].col);
		fprintf(f, "%s", " ");
		fprintf(f, "%d", recordes_personalizado[i].bombas);
		fprintf(f, "%s", "\n");
	}
	
	fclose(f);
}

void inicializar_recordes(recordes padrao[5], recordes personalizado[5]){
	
	char texto[50];
	int pos, i;
	char txt[4], txt2[2];

	// Abre o arquivo para leitura
	FILE *f = fopen("recordes.txt", "r");
	
	// Caso ainda nao exista o arquivo de recordes
	if(f == NULL)
	{
		for(i=0; i<5; i++)
		{
			strcpy(padrao[i].nome, "TBD");
			padrao[i].tempo = 0;
			padrao[i].lin = 9;
			padrao[i].col = 9;
			padrao[i].bombas = 10;
			
			strcpy(personalizado[i].nome, "TBD");
			personalizado[i].tempo = 0;
			personalizado[i].lin = 0;
			personalizado[i].col = 0;
			personalizado[i].bombas = 0;
		}
		
		salvar(padrao, personalizado);
		return;
	}
	
	// Le do arquivo os nomes e tempos e inicializa os vetores de recordes
	for(i=0; i<5; i++){
		fgets(texto, 50, f);
		fscanf(f, "%d %s %f", &pos, padrao[i].nome, &padrao[i].tempo);
	}
	
	fgets(texto, 50, f);
	for(i=0; i<5; i++){
		fgets(texto, 50, f);
		fscanf(f, "%d %s %f", &pos, personalizado[i].nome, &personalizado[i].tempo);
		fscanf(f, "%s %d %s %d %d", txt, &personalizado[i].lin, txt2, &personalizado[i].col, &personalizado[i].bombas);
	}
	
	// Fecha o arquivo
	fclose(f);
}

void mostrar_recordes (){
	
	
	char texto[50];
	// Abre o arquivo para leitura
	FILE *f = fopen("recordes.txt", "r");
	
	if(f == NULL)
	{
		printf("Erro ao procurar recordes ou nenhum recorde existente \n");
		return;
	}
	
	// fgets ira ler 50 caracteres ou ate o \n
	while(fgets(texto, 50, f) != NULL)
	{
		printf("%s", texto);
	}
	
	fclose(f);
}

int main(){
	
	// Variaveis de controle
	int tamlin, tamcol, numbomb;
	int opcao, modificado;
	float tempo;
	
	// Cria e inicia com -1 os vetores de recordes
	recordes recordes_padrao[5];
	recordes recordes_personalizado[5];
	inicializar_recordes(recordes_padrao, recordes_personalizado);

	
	system("cls||clear");
	do{
		opcao = menu();
		switch(opcao){

			case 0:
				break;

			case 1:
				// Caso 1, tabuleiro padrao 9x9, 10 bombas
				tamlin = 9;
				tamcol = 9;
				numbomb = 10;
				// Retorna o tempo caso jogador ganhe, -1 caso perca
				tempo = jogar(tamlin, tamcol, numbomb);
				if(tempo != -1)
					// Verifica se o tempo é menor que algum recorde, se sim o vetor de recordes é modificado com o novo tempo
					modificado = verificar_recordes(recordes_padrao, tempo, tamlin, tamcol, numbomb);
				break;

			case 2:
				// Caso 2, usuario entra com informações do tabuleiro
				printf("Digite o numero de linhas: ");
				scanf("%d", &tamlin);
				printf("Digite o numero de colunas: ");
				scanf("%d", &tamcol);
				printf("Digite o numero de bombas: ");
				scanf("%d", &numbomb);
				// Retorna o tempo caso jogador ganhe, -1 caso perca
				tempo = jogar(tamlin, tamcol, numbomb);
				if(tempo != -1)
					// Verifica se o tempo é menor que algum recorde, se sim o vetor de recordes é modificado com o novo tempo
					modificado = verificar_recordes(recordes_personalizado, tempo, tamlin, tamcol, numbomb);
				break;
			
			case 3:
				system("cls||clear");
				mostrar_recordes();
				break;

			default:
				system("cls||clear");
				printf("Opcao invalida\n");
				break;
		}
		
		// Se o vet de recordes foi modificado, salva no arquivo txt o novo tempo
		if(modificado)
		{
			salvar(recordes_padrao, recordes_personalizado);
		}


	}while(opcao != 0);

	return 0;
}