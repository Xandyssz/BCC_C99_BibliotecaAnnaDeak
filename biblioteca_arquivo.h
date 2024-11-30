#ifndef BIBLIOTECA_ARQUIVO_H
#define BIBLIOTECA_ARQUIVO_H

#include "estrutura.h"
#include <string.h>  // Para strcmp

// 1.0 - FUNÇÃO PARA GRAVAR O LIVRO NO ARQUIVO BINÁRIO.
void adicionar_livro(tp_livro livro) {
    FILE *arq;
    arq = fopen("biblioteca.dat", "ab");
    if (arq == NULL)
        arq = fopen("biblioteca.dat", "wb");
    if (arq == NULL) {
        printf("Não foi possível abrir o arquivo para gravação.\n");
    } else {
        livro.flag = true;
        fwrite(&livro, sizeof(tp_livro), 1, arq);
        fclose(arq);
    }
}


// 1.1 - FUNÇÃO PARA VERIFICAR SE O "NR_TOMBO" JÁ EXISTE NO ARQUIVO BINÁRIO.
bool verificarTombo(tp_int Nr_tombo_livro) {
    FILE *arq;
    tp_livro livro;
    bool existe = false;
    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        return false;
    }
    fread(&livro, sizeof(tp_livro), 1, arq);
    while (!feof(arq)) {
        if (livro.flag && livro.Nr_tombo_livro == Nr_tombo_livro) {
            existe = true;
        }
        fread(&livro, sizeof(tp_livro), 1, arq);
    }
    fclose(arq);
    return existe;
}


tp_livro buscar_livro_por_posicao(int posicao) {
    FILE *arq;
    tp_livro livro;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("\nO Arquivo binario nao existe.\n");
    } else {
        fseek(arq, posicao * sizeof(tp_livro),SEEK_SET);
        fread(&livro, sizeof(tp_livro), 1, arq);
        fclose(arq);
    }
    return livro;
}

void sobreescrever_livro(tp_livro livro, int posicao) {
    FILE *arq;

    arq = fopen("biblioteca.dat", "rb+");
    if (arq == NULL) {
        printf("\nO Arquivo binario nao existe.\n");
    } else {
        fseek(arq, posicao * sizeof(tp_livro),SEEK_SET);
        fwrite(&livro, sizeof(tp_livro), 1, arq);
        fclose(arq);
    }
}


int encontrar_livro_por_titulo(char titulo_livro[]) {
    FILE *arq;
    tp_livro livro;
    int i = 0, posicao = -1;
    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("\nO Arquivo binario nao existe.\n");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        while (!feof(arq) && posicao == -1) {
            if (strcmp(livro.titulo_livro, titulo_livro) == 0)
                posicao = i;
            fread(&livro, sizeof(tp_livro), 1, arq);
            i++;
        }
        fclose(arq);
    }
    return posicao;
}


int encontrar_livro_por_tombo(int Nr_tombo_Livro) {
    FILE *arq;
    tp_livro livro;
    int i = 0, posicao = -1;
    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("\nO Arquivo binario nao existe.\n");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        while (!feof(arq) && posicao == -1) {
            if (livro.Nr_tombo_livro == Nr_tombo_Livro)
                posicao = i;
            fread(&livro, sizeof(tp_livro), 1, arq);
            i++;
        }
        fclose(arq);
    }
    return posicao;
}

#endif // BIBLIOTECA_ARQUIVO_H
