/*
 * busca.c
 * 
 * Copyright 2016 Gustavo <gustavo@gustavo-workstation>
 * Ubuntu 16.04 LTS 
 * 
 * UFF - Ciência da Computação - Análise e Projeto de Algoritmos
 * Tarefa 2 - Intercambio
 * Aluno: Gustavo Henrique Mello Dauer
 * Professora: Karina Mochetti
 * 
 * Compilação: gcc -Wall -o "intercambio" "intercambio.c"
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_MAX_VETOR 500000
#define YES 1
#define NO 0

// PROTOTIPOS //////////////////////////////////////////////////////////
void MergeSort(int *vetor, int posicaoInicio, int posicaoFim);
void printVetor(int *vetor, int tamanho);
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	// VARIAVEIS ///////////////////////////////////////////////////////
	int i, 
		result = YES,
		nCandidatos = 0,
		vetor1[TAMANHO_MAX_VETOR],
		vetor2[TAMANHO_MAX_VETOR];
	////////////////////////////////////////////////////////////////////
	
	
	// ENTRADA /////////////////////////////////////////////////////////
	scanf("%d", &nCandidatos);
	
	for(i=0; i<nCandidatos; i++)
	{
		scanf("%d", &vetor1[i]);	
		scanf("%d", &vetor2[i]);
	}
	////////////////////////////////////////////////////////////////////
	
	MergeSort(vetor1, 0, nCandidatos - 1);
	MergeSort(vetor2, 0, nCandidatos - 1);
	
	printVetor(vetor1, nCandidatos);
	printVetor(vetor2, nCandidatos);
	
	for(i=0; i<nCandidatos; i++)
	{
		if(vetor1[i] != vetor2[i])
		{
			result = NO;
			break;
		}
	}
	
	if(result) 
		printf("YES\n");
	else 
		printf("NO\n");
	
	return 0;
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
