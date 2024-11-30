#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdbool.h>

typedef int tp_int;

typedef struct {
    char titulo_livro[100], autores_livro[100];
    char situacao;
    tp_int Nr_tombo_livro, ano_livro, qntEmprestimo_livro;
    bool flag;
} tp_livro;

#endif
