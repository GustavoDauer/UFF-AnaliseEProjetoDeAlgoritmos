/*
 * busca.c
 * 
 * Copyright 2016 Gustavo <gustavo@gustavo-workstation>
 * Ubuntu 14.04 LTS 
 * 
 * UFF - Ciência da Computação - Análise e Projeto de Algoritmos
 * Trabalho 1 - Busca Sequencial e Binária
 * Aluno: Gustavo Henrique Mello Dauer
 * Professora: Karina Mochetti
 * 
 * Compilação: gcc -Wall -o "busca" "busca.c"
 */


#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX_VETOR 100000
#define TAMANHO_MAX_NOME_ARQUIVO 11
#define TRUE 1
#define FALSE 0
#define POSICAO_PROCURADA 0
#define NUMERO_COMPARACOES 1

// PROTOTIPOS
int carregaArquivoDeTeste(char*, int*, int*, int[]);
void buscaSequencial(int*, int*, int[], int[]);
void buscaBinaria(int*, int*, int[], int[]);

int main(int argc, char **argv)
{
	// VARIAVEIS
	int procurado = 0,
		tamanhoVetor = 0,
		vetorInteiros[TAMANHO_MAX_VETOR],
		arquivoCarregado = FALSE;
		
	char *nomeArquivo = argv[1];
	
	printf("\n------------------------------------------------------------------------\n");
	printf("\tAluno: Gustavo Henrique Mello Dauer\n\tTrabalho 1 - Busca Sequencial / Busca Binaria");
	printf("\n------------------------------------------------------------------------\n");		
	
	if(nomeArquivo != NULL) // Se foi passado um parâmetro na chamada principal do programa, tentar abrir o arquivo com o nome passado
	{
		arquivoCarregado = carregaArquivoDeTeste(nomeArquivo, &procurado, &tamanhoVetor, vetorInteiros);	
	}
	
	if(!arquivoCarregado)
	{
		nomeArquivo = malloc( TAMANHO_MAX_NOME_ARQUIVO * sizeof(char) );
		
		printf("\tDigite o nome do arquivo de teste: ");		
		scanf ("%11[^\n]", nomeArquivo); // Le no maximo TAMANHO_MAX_NOME_ARQUIVO caracteres			
		arquivoCarregado = carregaArquivoDeTeste(nomeArquivo, &procurado, &tamanhoVetor, vetorInteiros);	
		printf("\n");
		
		free(nomeArquivo);
		nomeArquivo = NULL;
	}
	
	if(!arquivoCarregado) return 1; // Se nenhum arquivo válido foi escolhido, abortar
	
	int resultadoBuscaSequencial[2] = {-1, 0}; // Posição 0 [POSICAO_PROCURADA]: Guarda a posição do elemento procurado no vetor	
	int resultadoBuscaBinaria[2] = {-1, 0};	   // Posição 1 [NUMERO_COMPARACOES]: Guarda o número de comparações feitas
	
	
	printf("\n\tBusca sequencial\n\n");	
	buscaSequencial(&procurado, &tamanhoVetor, resultadoBuscaSequencial, vetorInteiros);	
	
	if(resultadoBuscaSequencial[POSICAO_PROCURADA] != -1) // Caso a posicao seja -1 apos o fim da busca, o elemento nao foi encontrado
		printf("\tPosicao no vetor: %d\n", resultadoBuscaSequencial[POSICAO_PROCURADA]);
	else
		printf("\tPosicao no vetor: Nao encontrado\n");
		
	printf("\tNumero de comparacoes feitas: %d\n", resultadoBuscaSequencial[NUMERO_COMPARACOES]);
	
	printf("\n\tBusca binaria\n\n");
	buscaBinaria(&procurado, &tamanhoVetor, resultadoBuscaBinaria, vetorInteiros);
	
	if(resultadoBuscaBinaria[POSICAO_PROCURADA] != -1) // Caso a posicao seja -1 apos o fim da busca, o elemento nao foi encontrado
		printf("\tPosicao no vetor: %d\n", resultadoBuscaBinaria[POSICAO_PROCURADA]);
	else
		printf("\tPosicao no vetor: Nao encontrado\n");
		
	printf("\tNumero de comparacoes feitas: %d\n", resultadoBuscaBinaria[NUMERO_COMPARACOES]);
	
	printf("\n");
	
	return 0;
}

int carregaArquivoDeTeste(char *nomeArquivo, int *procurado, int *tamanhoVetor, int vetorInteiros[])
{
	FILE *arquivo = fopen(nomeArquivo, "r");
		
	if(arquivo)
	{
		printf("\tArquivo %s aberto! Lendo valores...\n", nomeArquivo);
		
		fscanf(arquivo, "%d", procurado); // Leitura do numero procurado
		fscanf(arquivo, "%d", tamanhoVetor); // Leitura do tamanho do vetor
		
		printf("\tProcurado = %d\n\tTamanho do vetor = %d\n\n", *procurado, *tamanhoVetor);
		
		int i = 0;
		int aux = 0;
			
		while( !feof(arquivo) )
		{
			fscanf(arquivo, "%d", &aux);
			vetorInteiros[i] = aux; // Leitura de cada elemento do vetor
			
			//printf("\tvetorInteiros[%d] = %d\n", i, vetorInteiros[i]); // Debug
			
			i++;
		}
		
		fclose(arquivo);
		
		return TRUE;
	}

	printf("\tArquivo %s nao existe!\n", nomeArquivo);
	
	return FALSE;
}

void buscaSequencial(int *proc, int *tamanho, int result[], int vetorInteiros[])
{
	const int procurado = *proc,
			  tamanhoVetor = *tamanho;
			  		
	int i = 0, 
		comparacoes = 0;
		
	
	for(; i<=tamanhoVetor; i++)		
	{
		comparacoes++;
		
		//printf("\t%d (%d) == %d ? %d\n", vetorInteiros[i], i, procurado, vetorInteiros[i] == procurado); // Debug
		
		if(vetorInteiros[i] == procurado)
		{
			result[POSICAO_PROCURADA] = i;
			break;
		}
	}
	
	result[NUMERO_COMPARACOES] = comparacoes;
}

// Primeira versão iterada!
void buscaBinaria(int *proc, int *tamanho, int result[], int vetorInteiros[])
{
	const int procurado = *proc,
			  tamanhoVetor = *tamanho;
			  
	int	esquerda = 0, 
		direita = tamanhoVetor, 
		meio = 0, 
		comparacoes = 0;
	
	while(esquerda < direita - 1)		
	{
		comparacoes++;
		
		meio = (esquerda + direita) / 2;
		
		if(vetorInteiros[meio] < procurado) 
			esquerda = meio;
		else 
			direita = meio;
	}
	
	comparacoes++;
	
	if(vetorInteiros[direita] == procurado)
	{
		result[POSICAO_PROCURADA] = direita;		
	}
	else  // Ao invés de usar um else if, separei para contar as comparações corretamente!
	{
		comparacoes++;
		
		if(vetorInteiros[esquerda] == procurado)
		{		
			result[POSICAO_PROCURADA] = esquerda;		
		}
	}
		
	result[NUMERO_COMPARACOES] = comparacoes;
}

// Segunda versão iterada!
// Baseado na versão obtida na página da USP: http://www.ime.usp.br/~pf/algoritmos/aulas/bubi2.html
/*void buscaBinaria(int *proc, int *tamanho, int result[], int vetorInteiros[])
{
	const int procurado = *proc,
			  tamanhoVetor = *tamanho;
			  
	int	esquerda = 0, 
		direita = tamanhoVetor - 1, 
		meio = 0, 
		comparacoes = 0;
	
	while(esquerda <= direita)		
	{
		comparacoes++;
		
		meio = (esquerda + direita) / 2;
		
		if(vetorInteiros[meio] == procurado)
		{
			result[POSICAO_PROCURADA] = meio;
			break; // Caso encontre o elemento, sair do loop imediatamente, para nao contar a próxima comparação
		}
		
		comparacoes++;
		
		if(vetorInteiros[meio] < procurado) 
			esquerda = meio + 1;
		else
			direita = meio - 1;
	}
		
	result[NUMERO_COMPARACOES] = comparacoes;
}*/

