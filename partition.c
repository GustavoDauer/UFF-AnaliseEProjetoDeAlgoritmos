/*
 * sum.c
 * 
 * Copyright 2016 Gustavo <gustavo@gustavo-workstation>
 * Ubuntu 14.04 LTS 
 * 
 * UFF - Ciência da Computação - Análise e Projeto de Algoritmos
 * Trabalho 4 - Problema da Partição
 * Aluno: Gustavo Henrique Mello Dauer
 * Professora: Karina Mochetti
 * 
 * Compilação: gcc -Wall -o "partition" "partition.c"
 */


#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX_VETOR 10000
#define TRUE 1
#define FALSE 0
#define BOOL int
#define ALGORITMO int
#define GULOSO 1
#define DINAMICA 2

// PROTOTIPOS //////////////////////////////////////////////////////////
void AlgoritmoGuloso(int array[], int array_len);
void ProgramacaoDinamica(int array[], int array_len);
void MergeSort(int *vetor, int posicaoInicio, int posicaoFim);
void addVetor(int array[], int array_len, int elem);
void imprimeVetor(int array[], int array_len);
int somaVetor(int array[], int array_len, ALGORITMO contar);
////////////////////////////////////////////////////////////////////////

// VARIAVEIS GLOBAIS (CONTAGEM DE ATRIBUICOES) /////////////////////////
	unsigned long long 
		num_atrib_guloso = 0, 
		num_atrib_dinamica = 0;
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	// VARIAVEIS ///////////////////////////////////////////////////////
	int tamanhoVetor = 0,
		vetorGuloso[TAMANHO_MAX_VETOR],
		vetorDinamica[TAMANHO_MAX_VETOR];
	////////////////////////////////////////////////////////////////////
	
	
	// ENTRADA /////////////////////////////////////////////////////////
	printf("\n------------------------------------------------------------------------\n");
	printf("\tAluno: Gustavo Henrique Mello Dauer\n\tTrabalho 4 - Problema da Partição");
	printf("\n------------------------------------------------------------------------\n");			
	
	scanf("%d", &tamanhoVetor);
	printf("\n\tTamanho entrada: %d", tamanhoVetor);
	
	int i;
	
	for(i=0;i<tamanhoVetor;i++) // Inicializar vetores com número negativo para que possamos identificar posições não usadas
	{
		vetorGuloso[i] = -1;
		vetorDinamica[i] = -1;
	}
	
	for(i=0;i<tamanhoVetor;i++)
	{
		scanf("%d", &vetorGuloso[i]);		
		vetorDinamica[i] = vetorGuloso[i];
	}
	
	printf("\n");
	////////////////////////////////////////////////////////////////////
	
	// SOLUCAO ///////////////////////////////////////////////////////
	printf("\n\tAlgoritmo Guloso - ");	
	AlgoritmoGuloso(vetorGuloso, tamanhoVetor);
	
	printf("\n\tProgramacao Dinamica - ");
	ProgramacaoDinamica(vetorDinamica, tamanhoVetor);
	
	printf("\n");
	////////////////////////////////////////////////////////////////////
	return 0;
}

void ProgramacaoDinamica(int array[], int array_len)
{
	/* Seja k o valor da soma total do vetor de n elementos, faça uma matriz M de tamanho k/2 
	 * por n de valores boolenanos onde M[i,j] é verdadeiro que o vetor de valores v[1] a v[j] 
	 * possui um subvetor de soma total i e falso, caso contrário. Assim, o valor de M[i, j] 
	 * será verdadeiro somente se ou o valor de M[i, j-1] for verdadeiro ou o valor de 
	 * M[i-v[j], j-1] for verdadeiro. */
	 
	int i, j, k = somaVetor(array, array_len, DINAMICA); // 3
	int total = (k/2) + 1; 								 // 1
	BOOL M[total][array_len+1];							 // total * (N + 1)
	 
	for(i=0; i<=array_len; i++)
	{
		num_atrib_dinamica++;	
		 	 
		M[0][i] = TRUE;
		num_atrib_dinamica++;
	}
	 
	for(i=1; i<total; i++)
	{
		num_atrib_dinamica++;	
		 	 
		M[i][0] = FALSE;
		num_atrib_dinamica++;
	}
	 
	for(i=1; i<total; i++)
	{
		num_atrib_dinamica++;
		 
		for(j=1; j<array_len; j++)
		{
			num_atrib_dinamica++;
			 			 
			M[i][j] = M[i][j-1] || M[i-array[j]][j-1];
			num_atrib_dinamica++;					
		}
	}	 
	
    printf("Numero de atribuicoes: %lld\n", num_atrib_dinamica);	
	printf("\n\tPossui soma? %s\n", M[k/2][array_len - 1] == TRUE ? "Sim" : "Nao");
	//printf("Valor total da soma inicial do vetor: %d\n", total); // Usado no cálculo da complexidade de espaço
}

void AlgoritmoGuloso(int array[], int array_len)
{
	/* Ordene o vetor de forma decrescente. Do primeiro ao útimo elemento, coloque-o sempre no subvetor que possui a menor soma total.  */
		
    int array_guloso[array_len], // N
		set1[array_len], 		 // N
		set2[array_len],		 // N
		i, j;					 // 2
		
	for(i=0;i<array_len;i++) // Inicializar vetores com número negativo para que possamos identificar posições não usadas
	{
		array_guloso[i] = -1;
		set1[i] = -1;
		set2[i] = -1;
		num_atrib_guloso += 3;
	}
	
	
	MergeSort(array, 0, array_len - 1); // Ordena em ordem crescente
	
	int endVetor = array_len - 1; // 1
	num_atrib_guloso++;
	
	for(i=0; i<array_len; i++) // Acha o fim do vetor para colocar em ordem decrescente
	{
		num_atrib_guloso++;
		
		if(array[i] == -1)
		{
			endVetor = i;
			num_atrib_guloso++;
			break;
		}
	}
	
	for(i=0, j=endVetor; i<array_len && j>=0; i++, j--) // Coloca em ordem decrescente
	{
		num_atrib_guloso++;
		
		array_guloso[i] = array[j];
		num_atrib_guloso++;
	}
	
	set1[0] = array_guloso[0];
	num_atrib_guloso++;
	set2[0] = array_guloso[1];
	num_atrib_guloso++;
	
	unsigned long long somaS1 = 0, somaS2 = 0; // 4 (cada long conta como 2 ints)
	
	for(i=2; i<array_len; i++)
	{
		somaS1 = somaVetor(set1, array_len, GULOSO);
		num_atrib_guloso++;
		somaS2 = somaVetor(set2, array_len, GULOSO);
		num_atrib_guloso++;
		
		if(somaS2 < somaS1)
			addVetor(set2, array_len, array_guloso[i]);		
		else
			addVetor(set1, array_len, array_guloso[i]);
	}
	
	somaS1 = somaVetor(set1, array_len, FALSE); // Descartar essas contagens de atribuições
	somaS2 = somaVetor(set2, array_len, FALSE);
	
	printf("Numero de atribuicoes: %llu\n", num_atrib_guloso);
	
	printf("\n\tParticao 1: Soma %llu\n", somaS1);
	//imprimeVetor(set1, array_len);
	
	printf("\n\tParticao 2: Soma %llu\n", somaS2);
	//imprimeVetor(set2, array_len);
}

// Fonte: https://pt.wikipedia.org/wiki/Merge_sort#C.C3.B3digo_em_C
void MergeSort(int *vetor, int posicaoInicio, int posicaoFim)
{
    int i, j, k, 
		metadeTamanho, 
		*vetorTemp;	

    if(posicaoInicio == posicaoFim) return ;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    num_atrib_guloso++;    
    
    MergeSort(vetor, posicaoInicio, metadeTamanho);
    MergeSort(vetor, metadeTamanho + 1, posicaoFim);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    num_atrib_guloso++;
    j = metadeTamanho + 1;
    num_atrib_guloso++;
    k = 0;
    num_atrib_guloso++;
    vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));    
    num_atrib_guloso++;

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1)
    {
        if (i == metadeTamanho + 1 ) // i passou do final da primeira metade, pegar v[j]
        { 
            vetorTemp[k] = vetor[j];     
            num_atrib_guloso++;       
            j++;        
            num_atrib_guloso++;    
            k++;       
            num_atrib_guloso++;     
        } 
        else
        {
            if (j == posicaoFim + 1) // j passou do final da segunda metade, pegar v[i]
            { 
                vetorTemp[k] = vetor[i];      
                num_atrib_guloso++;          
                i++;       
                num_atrib_guloso++;         
                k++;    
                num_atrib_guloso++;            
            } 
            else
            {
                if (vetor[i] < vetor[j])
                { 
                    vetorTemp[k] = vetor[i];  
                    num_atrib_guloso++;                  
                    i++;       
                    num_atrib_guloso++;             
                    k++;     
                    num_atrib_guloso++;               
                } 
                else 
                { 
                    vetorTemp[k] = vetor[j];     
                    num_atrib_guloso++;               
                    j++;         
                    num_atrib_guloso++;           
                    k++;     
                    num_atrib_guloso++;               
                }
            }
        }
    }
    
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++)
    {
		num_atrib_guloso++;
        vetor[i] = vetorTemp[i - posicaoInicio];
        num_atrib_guloso++;
    }
    
    free(vetorTemp);
}

int somaVetor(int array[], int array_len, ALGORITMO contar)
{
	int soma = 0,
		i;
		
	if(contar == GULOSO) num_atrib_guloso++;			// Contagem de atribuições
	else if (contar == DINAMICA) num_atrib_dinamica++;  // Contagem de atribuições
	
	for(i=0; i<array_len; i++)
	{
		if(contar == GULOSO) num_atrib_guloso++;			// Contagem de atribuições
		else if (contar == DINAMICA) num_atrib_dinamica++;	// Contagem de atribuições
		
		if(array[i] > 0)
		{
			soma += array[i];
			
			if(contar == GULOSO) num_atrib_guloso++;			// Contagem de atribuições
			else if (contar == DINAMICA) num_atrib_dinamica++;	// Contagem de atribuições
		}
	}	
	
	return soma;
}

void addVetor(int array[], int array_len, int elem)
{
	int i;
	
	for(i=0; i<array_len; i++)
	{
		num_atrib_guloso++;
		
		if(array[i] < 0)
		{
			array[i] = elem;
			num_atrib_guloso++;
			
			break;
		}
	}
}

void imprimeVetor(int array[], int array_len)
{
	int i;
	
	printf("\n\t{ ");
	
	for(i=0; i<array_len; i++)
	{
		if(array[i] != -1)
			printf("%d ", array[i]);
	}
		
	printf("}\n");
}
