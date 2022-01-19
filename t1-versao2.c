// INPUT
// T Dado na primeira linha
// N Dado na segunda linha
// Para cada linha Ni, segue uma linha contendo P e W
// G Dado após as N linhas
// Para cada linha Gi, segue uma linha contendo MW

#include <stdio.h>
#include <stdlib.h>

// Valores máximos das variáveis
#define TESTES_MAX 1000 
#define COMPRAS_MAX 1000 
#define PRECO_MAX 100  
#define PESO_MAX 30   
#define GRUPO_MAX 100   
#define PESO_SUPORTADO_MAX 30 

// Valores mínimos das variáveis
#define TESTES_MIN 1   
#define COMPRAS_MIN 1 
#define PRECO_MIN 1   
#define PESO_MIN 1 
#define GRUPO_MIN 1   
#define PESO_SUPORTADO_MIN 1 

// Declaracao de variaveis globais
FILE *fp = NULL;
int num_testes,
	VPreco[COMPRAS_MAX], // Máximo de N linhas
	VPeso[COMPRAS_MAX], // Máximo de N linhas
	VGrupo[GRUPO_MAX]; // Máximo de G pessoas no grupo
	
int MAIOR_VALOR_DO_SOMATORIO(int TEMP_VPreco[], int TEMP_VPeso[], int peso_suportado, int num_compras, int indiceCandidato) {
	int 
		i,
		pesoAcumulado, precoAcumulado, maiorPreco=0;
	
	if(TEMP_VPeso[indiceCandidato] == peso_suportado) {
		maiorPreco = TEMP_VPreco[indiceCandidato];
		return maiorPreco;
	}
	else {
		pesoAcumulado=TEMP_VPeso[indiceCandidato];
		for(i=indiceCandidato; i<num_compras; i++) {
			if( ((TEMP_VPeso[i]+pesoAcumulado) <= peso_suportado) && (TEMP_VPreco[i]+precoAcumulado) > maiorPreco) {
				pesoAcumulado+=TEMP_VPeso[i];
				precoAcumulado+=TEMP_VPreco[i];
				maiorPreco=precoAcumulado;
			}
		}
		return maiorPreco;
	}
}

int SELECIONA_MAIOR_VALOR_DOS_SOMATORIOS(int TEMP_VPreco[], int TEMP_VPeso[], int peso_suportado, int num_compras) {
	int 
		i, candidato, maiorValor=0;
	
	for(i=0; i<num_compras; i++) {
		candidato=MAIOR_VALOR_DO_SOMATORIO(TEMP_VPreco, TEMP_VPeso, peso_suportado, num_compras, i);
		if(candidato>maiorValor) {
			maiorValor=candidato;
		}
	}
	return maiorValor;
}

void EXECUTA_TESTE(FILE *fp) {
	int 
		i, j, k, l,
		num_compras, num_grupo,
		maiorValor, // Resposta
		TEMP_VPreco[COMPRAS_MAX], // Vetores temporários apenas com os pesos suportáveis para a pessoa i
		TEMP_VPeso[COMPRAS_MAX];
	// INICIO DA LEITURA DO ARQUIVO DE TESTES
	fp = fopen("teste.txt","rb");
	if(fp) {
		fscanf(fp, "%d", &num_testes); 	// Lê T
		printf("TESTES %d\n-----------------------------------\n", num_testes);	
		for(k=1; k<=num_testes; k++) { 	// INICIO DA ITERAÇÂO DOS TESTES 
			fscanf(fp, "%d", &num_compras); // Lê N	
			printf("\n-----------------------------------\nCOMPRAS %d\n", num_compras);	
			for(i=0; i<num_compras; i++) {		// Lê P e W de N linhas
				fscanf(fp, "%d %d", &VPreco[i], &VPeso[i]);
				printf("PREÇO %d PESO %d\n", VPreco[i], VPeso[i]);
			}
			fscanf(fp, "%d", &num_grupo); 	// Lê G	
			printf("GRUPO %d\n", num_grupo);
			for(i=0; i<num_grupo; i++) {		// Lê MW de cada pessoa no grupo
				fscanf(fp, "%d", &VGrupo[i]);
				printf("MAXIMO PESO PESSOA %d = %d\n", i, VGrupo[i]);
			}
			printf("\n-----------------------------------\n");
			
			// INICIO DA OTIMIZACAO EM VETORES TEMPORÁRIOS
			for(i=0; i<num_grupo; i++) {
				printf("\n\nPRECOS E PESOS QUE A PESSOA COM MW %d PODE CARREGAR:\n-----------------------------------\n", VGrupo[i]);
				for(j=0, l=0; j<num_compras; j++) {
					if(VPeso[j] <= VGrupo[i]) {   // Se o peso da compra é suportável para a pessoa
						TEMP_VPeso[l]=VPeso[j];   // Adicione nos vetores temporários.
						TEMP_VPreco[l]=VPreco[j];						
						printf("%d %d\n", TEMP_VPreco[l], TEMP_VPeso[l]);
						l++;
					}
				}
				maiorValor=SELECIONA_MAIOR_VALOR_DOS_SOMATORIOS(TEMP_VPreco, TEMP_VPeso, VGrupo[i], num_compras);
				printf("\n%d\n", maiorValor);
			}
			// FIM DA OTIMIZACAO EM VETORES TEMPORÁRIOS
		}	
		// FIM DA ITERAÇÂO DOS TESTES
		fclose(fp);		
	}
	// FIM DA LEITURA DO ARQUIVO DE TESTES	
}

int main() {	
	EXECUTA_TESTE(fp);
	return 0;
}
