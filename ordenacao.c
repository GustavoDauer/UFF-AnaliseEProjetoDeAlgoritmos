/*
 * busca.c
 * 
 * Copyright 2016 Gustavo <gustavo@gustavo-notebook>
 * Ubuntu 16.04 LTS 
 * 
 * UFF - Ciência da Computação - Análise e Projeto de Algoritmos
 * Trabalho 2 - Ordenação por Insertion Sort e Merge Sort
 * Aluno: Gustavo Henrique Mello Dauer
 * Professora: Karina Mochetti
 * 
 * Compilação: gcc -Wall -o "ordenacao" "ordenacao.c"
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_MAX_VETOR 500000
#define TRUE 1
#define FALSE 0

// PROTOTIPOS //////////////////////////////////////////////////////////
void InsertionSort(int*, int);
void MergeSort(int*, int, int);
void printVetor(int*, int);
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	// VARIAVEIS ///////////////////////////////////////////////////////
	int tamanhoVetor = 0,
		vetorIS[TAMANHO_MAX_VETOR],
		vetorMS[TAMANHO_MAX_VETOR];
	
	clock_t start_t, end_t;
	
	double total_t;
	////////////////////////////////////////////////////////////////////
	
	
	// ENTRADA /////////////////////////////////////////////////////////
	printf("\n------------------------------------------------------------------------\n");
	printf("\tAluno: Gustavo Henrique Mello Dauer\n\tTrabalho 2 - Ordenacao Insertion Sort / Ordenacao Merge Sort");
	printf("\n------------------------------------------------------------------------\n");			
	
	//printf("\n\tEntre com o tamanho do vetor: ");
	scanf("%d", &tamanhoVetor);
	printf("\n\tTamanho entrada: %d", tamanhoVetor);
	
	int i = 0;
	for(;i<tamanhoVetor;i++)
	{
		//printf("\tvetor[%d] = ", i);
		scanf("%d", &vetorIS[i]);
		vetorMS[i] = vetorIS[i];
	}
	
	printf("\n");
	////////////////////////////////////////////////////////////////////
	
	// ORDENACAO ///////////////////////////////////////////////////////
	printf("\n\tOrdenacao Insertion Sort\n");
	start_t = clock();
	InsertionSort(vetorIS, tamanhoVetor);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("\n\tTempo total levado pela CPU: %f\n", total_t  );
	//printVetor(vetorIS, tamanhoVetor);
	
	printf("\n\tOrdenacao Merge Sort\n");
	start_t = clock();
	MergeSort(vetorMS, 0, tamanhoVetor - 1);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("\n\tTempo total levado pela CPU: %f\n", total_t  );
	//printVetor(vetorMS, tamanhoVetor);
	
	printf("\n");
	////////////////////////////////////////////////////////////////////
	return 0;
}

// Fonte: https://pt.wikipedia.org/wiki/Insertion_sort#C
void InsertionSort(int *vetor, int tamanho)
{
	int i = 1, 
		j, atual;

	for(; i<tamanho; i++)
	{
		atual = vetor[i];
		j = i - 1;

		while ((j >= 0) && (atual < vetor[j]))
		{
			vetor[j+1] = vetor[j];
            j = j - 1;
		}
    
		vetor[j+1] = atual;
	}
}

// Fonte: https://pt.wikipedia.org/wiki/Merge_sort#C.C3.B3digo_em_C
void MergeSort(int *vetor, int posicaoInicio, int posicaoFim)
{
    int i, j, k, 
		metadeTamanho, 
		*vetorTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    MergeSort(vetor, posicaoInicio, metadeTamanho);
    MergeSort(vetor, metadeTamanho + 1, posicaoFim);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1)
    {
        if (i == metadeTamanho + 1 ) // i passou do final da primeira metade, pegar v[j]
        { 
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        } 
        else
        {
            if (j == posicaoFim + 1) // j passou do final da segunda metade, pegar v[i]
            { 
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            } 
            else
            {
                if (vetor[i] < vetor[j])
                { 
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                } 
                else 
                { 
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }
    }
    
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++)
    {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }
    
    free(vetorTemp);
}

void printVetor(int *vetor, int tamanho)
{
	int i = 0;
	
	for(; i<tamanho; i++)
	{
		printf("\n\tvetor[%d] = %d", i, vetor[i]);
	}
	
	printf("\n");
}
