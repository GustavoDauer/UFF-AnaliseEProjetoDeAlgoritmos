/*
 * sum.c
 * 
 * Copyright 2016 Gustavo <gustavo@gustavo-workstation>
 * Ubuntu 14.04 LTS 
 * 
 * UFF - Ciência da Computação - Análise e Projeto de Algoritmos
 * Trabalho 3 - Sub-Vetor de soma máxima
 * Aluno: Gustavo Henrique Mello Dauer
 * Professora: Karina Mochetti
 * 
 * Compilação: gcc -Wall -o "sum" "sum.c"
 */


#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX_VETOR 10000
#define TRUE 1
#define FALSE 0

// PROTOTIPOS //////////////////////////////////////////////////////////
void ForcaBruta(int array[], int array_len);
void ProgramacaoDinamica(int array[], int array_len);
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	// VARIAVEIS ///////////////////////////////////////////////////////
	int tamanhoVetor = 0,
		vetor[TAMANHO_MAX_VETOR];
	////////////////////////////////////////////////////////////////////
	
	
	// ENTRADA /////////////////////////////////////////////////////////
	printf("\n------------------------------------------------------------------------\n");
	printf("\tAluno: Gustavo Henrique Mello Dauer\n\tTrabalho 3 - Sub-Vetor de soma máxima");
	printf("\n------------------------------------------------------------------------\n");			
	
	//printf("\n\tEntre com o tamanho do vetor: ");
	scanf("%d", &tamanhoVetor);
	printf("\n\tTamanho entrada: %d", tamanhoVetor);
	
	int i = 0;
	for(;i<tamanhoVetor;i++)
	{
		//printf("\tvetor[%d] = ", i);
		scanf("%d", &vetor[i]);
	}
	
	printf("\n");
	////////////////////////////////////////////////////////////////////
	
	// SOLUCAO ///////////////////////////////////////////////////////
	printf("\n\tForca Bruta\n");
	ForcaBruta(vetor, tamanhoVetor);
	
	printf("\n\tProgramacao Dinamica\n");
	ProgramacaoDinamica(vetor, tamanhoVetor);
	
	printf("\n");
	////////////////////////////////////////////////////////////////////
	return 0;
}

// Baseado em: http://stackoverflow.com/a/7943955/7507
void ProgramacaoDinamica(int array[], int array_len)
{
	unsigned long long num_atrib = 0; 	// Contagem do total de atribuicoes feitas
    int bestSoFar = 0,				// Melhor soma
		bestNow = 0,				// Auxiliar
		bestStartIndexSoFar = -1, 	// Inicio do sub-vetor maximo
		bestStopIndexSoFar = -1, 	// Fim do sub-vetor maximo
		bestStartIndexNow = -1, 	// Auxiliar
		i;
		
		num_atrib += 5;
	
	for(i = 0; i < array_len; i++)
	{
		num_atrib++; // Para a variavel i!
		int value = bestNow + array[i];
		num_atrib++;
		
		if(value > 0)
		{
			if (bestNow == 0)
			{
				bestStartIndexNow = i;
				num_atrib++;
			}
			
			bestNow = value;
			num_atrib++;
		} 
		else
		{
			bestNow = 0;
			num_atrib++;
		}
		
		if(bestNow > bestSoFar)
		{
			bestSoFar = bestNow;
			num_atrib++;
			bestStopIndexSoFar = i;
			num_atrib++;
			bestStartIndexSoFar = bestStartIndexNow;
			num_atrib++;
		}
	}
	
	printf("\tTotal atribuicoes = %llu\n", num_atrib);
	printf("\tMelhor Soma = %d\n", bestSoFar);
	printf("\tSub-Vetor Maximo de %d a %d\n", bestStartIndexSoFar, bestStopIndexSoFar);
	// Descomentar o trecho abaixo para ver o sub-vetor
	/*printf("\tSub-Vetor Maximo = [");
	
	for(i = bestStartIndexSoFar; i < bestStopIndexSoFar + 1; i++)
	{
		printf(" %d", array[i]);
	}
	
	printf(" ]\n");*/
}

void ForcaBruta(int array[], int array_len)
{
	unsigned long long num_atrib = 0; 	// Contagem do total de atribuicoes feitas
    int maximum = 0, 				// Melhor soma
		bestStartIndexSoFar = -1, 	// Inicio do sub-vetor maximo
		bestStopIndexSoFar = -1, 	// Fim do sub-vetor maximo
		bestStartIndexNow = -1, 	// Auxiliar
		i, j;
		
	num_atrib += 4;
	
	for(i = 0; i < array_len; i++)
	{
		num_atrib++; // Para a variavel i!
		int current = 0;
		num_atrib++;
		bestStartIndexNow = i;
		num_atrib++;
		
		for(j = i; j < array_len; j++)
		{
			num_atrib++; // Para a variavel j!
			current += array[j];
			num_atrib++;
		
			if(current > maximum)
			{
				maximum = current;
				num_atrib++;
				bestStartIndexSoFar = bestStartIndexNow;
				num_atrib++;
				bestStopIndexSoFar = j;
				num_atrib++;
			}
		}
	}
	
	printf("\tTotal atribuicoes = %llu\n", num_atrib);
	printf("\tMelhor Soma = %d\n", maximum);
	printf("\tSub-Vetor Maximo de %d a %d\n", bestStartIndexSoFar, bestStopIndexSoFar);
	// Descomentar o trecho abaixo para ver o sub-vetor
	/*printf("\tSub-Vetor Maximo = [");
	
	for(i = bestStartIndexSoFar; i < bestStopIndexSoFar + 1; i++) {
		printf(" %d", array[i]);
	}
	
	printf(" ]\n");*/
}
