/*
 * papas.c
 * 
 * Copyright 2016 Gustavo <gustavo@gustavo-ThinkPad-Edge-E431>
 * Ubuntu 14.04 LTS 
 * 
 * UFF - Ciência da Computação - Análise e Projeto de Algoritmos
 * Tarefa 1 - Papas
 * Aluno: Gustavo Henrique Mello Dauer
 * Professora: Karina Mochetti
 * 
 * Compilação: gcc -Wall -o "papas" "papas.c"
 */


#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char **argv)
{
    while (TRUE)
    {
        int periodo,
			numeroDePapas,
			i;
			
        scanf("%d", &periodo);
        scanf("%d", &numeroDePapas);
        
        int vetorAnos[numeroDePapas];                
        
        for (i = 0; i < numeroDePapas; i++)
        {
            int ano;   
                     
            scanf("%d", &ano);            
            vetorAnos[i] = ano;
        }

        int maiorDe = -1;
        int maiorAte = -1;
        int maiorTamanho = -1;

        for (i = 0; i < numeroDePapas; i++)
        {
            int menorAno = vetorAnos[i];
            int maiorAno = menorAno + periodo - 1;
            //vector<int>::iterator upper_bound_pointer = upper_bound(vetorAnos.begin(), vetorAnos.end(), maiorAno);
            //int exclusive_upper_index = upper_bound_pointer - vetorAnos.begin();

            //int size = exclusive_upper_index - i;
            //if (size > maiorTamanho)
            //{
            //    maiorDe = menorAno;
            //    maiorAte = *(upper_bound_pointer - 1);
            //    maiorTamanho = size;
            //}
        }
                
        printf("%d %d %d\n", maiorTamanho, maiorDe, maiorAte);
    }

    return 0;
}
