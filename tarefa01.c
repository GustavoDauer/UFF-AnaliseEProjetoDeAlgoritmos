#include <stdio.h>

int main () {
	int a[1000000];
	int y, p;
	int i, j;
	int count, max;
	int first, last;

	/* loop principal */
	while (scanf("%d", &y) != EOF) {

		/* leitura do numero de papas */
		scanf("%d", &p);
		/* leitura de cada ano */
		for (i=0; i<p; i++) scanf("%d", &a[i]);

		/* verifica inciando em cada ano, quantos papas assumiram em y anos */
		max = 0;
		for (i=0; i<p; i++) {
			count = 0;
			j = i;
			/* iniciando em i, quantos foram eleitos em y anos */
			while (j < p && a[j]-a[i] < y) {
				j++;
				count++;
			}

			/* se for maior que a solucao atual, eh a melhor solucao */
			if (count > max) {
				max = count;
				first = a[i];
				last = a[j-1];
			}
		}

		printf("%d %d %d\n", max, first, last);
	}

	return 0;
}