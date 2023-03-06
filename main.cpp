#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASIZE 256 // Tamanho do alfabeto
#define XSIZE 100 // Tamanho máximo do padrão
#define MAX(a,b) ((a) > (b) ? (a) : (b))

void SAIDA(int j) {
    printf("Ocorrência na posição %d\n", j);
}

// Pré-processamento da tabela ztBc
//A tabela ztBc armazena o tamanho máximo do salto que pode ser feito a partir de um determinado caractere do alfabeto para um caractere do padrão.
void preZtBc(char *x, int m, int ztBc[ASIZE][ASIZE]) {
    int i, j;
    for (i = 0; i < ASIZE; ++i)//Todas as posições da tabela são carregadas com o valor do tamanho da palavra.
        for (j = 0; j < ASIZE; ++j)
            ztBc[i][j] = m;
    for (i = 0; i < ASIZE; ++i)//Faz uma varredura na palavra, alternando o valor correspondente a cada caracter na tabela alfabeto.
        ztBc[i][x[0]] = m - 1;
    for (i = 1; i < m; ++i)//Os caracteres alterados recebem o valor m - 1 - i.
        ztBc[x[i - 1]][x[i]] = m - 1 - i;
}
// Calcula os sufixos do padrão
void calculateSuffixes(char *x, int m, int *suff) {
    int f = 0, g, i;

    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}
//Pré-processamento da tabela BmGs
void preBmGs(char *x, int m, int bmGs[XSIZE]) {
    int i, j, suff[XSIZE];

    // Calculando o array de sufixos
    calculateSuffixes(x, m, suff);

    // Caso 1
    for (i = 0; i < m; ++i)
        bmGs[i] = m;
    // Caso 2
    j = 0;
    for (i = m - 1; i >= 0; --i)
        if (suff[i] == i + 1)
            for (; j < m - 1 - i; ++j)
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
    // Caso 3
    for (i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;
}
// Algoritmo de busca ZT
//A função utiliza as tabelas ztBc e bmGs para determinar o tamanho do salto a ser feito a cada iteração.
void ZT(char *x, int m, char *y, int n) {
    int i, j, ztBc[ASIZE][ASIZE], bmGs[XSIZE];

    /* Pré-processando */
    preZtBc(x, m, ztBc);
    preBmGs(x, m, bmGs);

    /* Procurando */
    j = 0;
    while (j <= n - m) {
        i = m - 1;
        while (i >= 0 && x[i] == y[i + j])
            --i;
        if (i < 0) {
            SAIDA(j);
            j += bmGs[0];
        } else {
            j += MAX(bmGs[i], ztBc[y[i + j]][x[i]]);
        }
    }
}
// Exemplo de uso
int main() {
char texto[] = "abacate";
char padrao[] = "ca";
int n = strlen(texto);
int m = strlen(padrao);
ZT(padrao, m, texto, n);
return 0;
}
