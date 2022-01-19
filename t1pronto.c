#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaracao de variaveis globais
FILE *fp = NULL;
FILE *fp2 = NULL;
int num_testes;

void EXECUTA_TESTE();
	 
int main() {	
	// INICIO DA LEITURA DO ARQUIVO DE TESTES
	fp = fopen("INPUT.txt","rb");
	fp2 = fopen("OUTPUT.txt","w");
	if(fp)
		EXECUTA_TESTE();
	else {
		// CRIACAO DO ARQUIVO DE TESTE PADRAO
		fp = fopen("INPUT.txt","w");
		if(fp)
			fprintf(fp, "2\n3\n72 17\n44 23\n31 24\n1\n26\n6\n64 26\n85 22\n52 4\n99 18\n39 13\n54 9\n4\n23\n20\n20\n26\n");
	}
	fclose(fp);
	fclose(fp2);
    return 0;
}

void EXECUTA_TESTE() {
	int i, j;
	
	fscanf(fp, "%d", &num_testes); 
	printf("TESTES %d\n-----------------------------------\n", num_testes);	 
	while(num_testes--) {
		int 
		num_compras, num_grupo, pesoSuportado, maiorPreco = 0,
		VPreco[1005], VPeso[1005], VTodosValores[35];
						
		fscanf(fp, "%d", &num_compras);			
		for(i=0; i<num_compras; i++) // Leitura dos preços e pesos de cada compra
			fscanf (fp, "%d %d", &VPreco[i], &VPeso[i]);			
		memset (VTodosValores, 0, sizeof (VTodosValores)); // Importante! Para otimizar o desempenho! 
		for(j=0; j<num_compras; j++)
			for(i=32; i>=0; i--) // Calcula todos os valores para o vetor VTodosValores
				if(VPeso[j]<=i && VTodosValores[i] < VTodosValores[i-VPeso[j]]+VPreco[j])
					VTodosValores[i]=VTodosValores[i-VPeso[j]]+VPreco[j]; 		
		fscanf (fp, "%d", &num_grupo); 
		while(num_grupo--) {				
			fscanf (fp, "%d", &pesoSuportado);
			maiorPreco+=VTodosValores[pesoSuportado]; // Extrai do vetor VTodosValores o maior preço para o peso suportado
		}
		printf ("%d\n", maiorPreco);
		if(fp2)
			fprintf (fp2, "%d\n", maiorPreco);
	}
}
