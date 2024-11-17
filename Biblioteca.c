#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

typedef int tp_int;

typedef struct {
    char titulo_livro[50], autores_livro[50];
    char situacao;
    tp_int Nr_tombo_livro, ano_livro, qntEmprestimo_livro;
    bool flag;
} tp_livro;


void incluir(tp_livro livro) {
    FILE *arq;

    arq = fopen("biblioteca.dat", "ab");
    if (arq == NULL)
        arq = fopen("biblioteca.dat", "wb");
    if (arq == NULL) {
        printf("Nao foi possivel abrir o arquivo para gravacao");
    } else {
        livro.flag = true;
        fwrite(&livro, sizeof(tp_livro), 1, arq);
        fclose(arq);
    }
}

tp_livro ler_livro() {
    tp_livro livro;

    printf("Tombo do livro...:");
    scanf("%d", &livro.Nr_tombo_livro);

    fflush(stdin);
    printf("Titulo do livro...: ");
    gets(livro.titulo_livro);

    printf("Autores do livro...: ");
    gets(livro.autores_livro);

    printf("Ano do livro...:");
    scanf("%d", &livro.ano_livro);

    livro.situacao = 'D';
    livro.qntEmprestimo_livro = 10;

    return livro;
}

void cadastrar_livros() {
    tp_livro livro;
    char continua;

    printf("Iniciando Inclusao de livros...\n");
    printf("----------------------\n");
    do {
        livro = ler_livro();
        incluir(livro);
        printf("\nCadastrar outro Livro ?");
        scanf(" %c", &continua);
        continua = toupper(continua);
    } while (continua == 'S');
}

void apresentar_linha(tp_livro livro) {
    printf("%-12d %-35s %-25s %-13d %-18c %-10d\n",
           livro.Nr_tombo_livro, livro.titulo_livro, livro.autores_livro, livro.ano_livro, livro.situacao,
           livro.qntEmprestimo_livro);
}

void apresentar_cabecalho() {
    printf("%-12s %-35s %-25s %-10s %-15s %-12s\n",
           "Nr Tombo", "Titulo", "Autores", "Ano", "Situacao", "Qnt Emprestimo.");
}

void apresentar_todos() {
    FILE *arq;
    tp_livro livro;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("Nao existe o arquivo.");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        apresentar_cabecalho();
        while (!feof(arq)) {
            if (livro.flag)
                apresentar_linha(livro);
            fread(&livro, sizeof(tp_livro), 1, arq);
        }
        fclose(arq);
    }
}



int contar_emprestimo() {
    FILE *arq;
    tp_livro livro;
    int contEmprestimo = 0;

    arq = fopen("biblioteca.dat", "rb");
    if(arq == NULL) {
        printf("Nao existe o arquivo.\n");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        while(!feof(arq)) {
            if(livro.flag) {
                contEmprestimo = contEmprestimo + livro.qntEmprestimo_livro;
            }
                    fread(&livro, sizeof(tp_livro), 1, arq);
        }
        fclose(arq);
    }
    return contEmprestimo;
}

void apresentar_filtrado() {
    FILE *arq;
    tp_livro livro;
    int op;

    do {
        printf("1 - Relatorio de livros Emprestados\n");
        printf("2 - Relatorio de livros Disponiveis\n");
        printf("3 - Qnt de Emprestimos ja realizados pela biblioteca\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Selecione a opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 3)
            printf("\nOpcao invalida. Selecione uma opcao valida...\n\n");
    } while (op < 0 || op > 3);

    switch (op) {
        case 0:
            printf("Voltando ao menu principal...\n");
        break;
        case 1:
        case 2:
            arq = fopen("biblioteca.dat", "rb");
        if (arq == NULL) {
            printf("Nao existe o arquivo.\n");
        } else {
            printf("\n");
            apresentar_cabecalho();

            fread(&livro, sizeof(tp_livro), 1, arq);

            while (!feof(arq)) {
                if (livro.flag) {
                    if ((op == 1 && livro.situacao == 'E') || (op == 2 && livro.situacao == 'D')) {
                        apresentar_linha(livro);
                    }
                }
                fread(&livro, sizeof(tp_livro), 1, arq);
            }
            fclose(arq);
        }
        break;
        case 3:
            printf("\nTotal de Emprestimos Realizados: %d\n", contar_emprestimo());
        break;
    }
}

int apresentar_menu() {
    int op;
    do {
        printf("1 - Inclusao de Novos Livros\n");
        printf("2 - Alterar, Pesquisar e Excluir/Recuperar Livros\n");
        printf("3 - Relatorio de Livros [EMPRESTADOS] e [DISPONIVEIS]\n");
        printf("4 - Realizar Emprestimo\n");
        printf("5 - Realizar Devolucao\n");
        printf("6 - Relatorio de Livros [EMPRESTADOS]\n");
        printf("0 - Sair\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 6)
            printf("Opcao invalida. Selecione outra.\n\n");
    } while (op < 0 || op > 6);
    return op;
}

int apresentarSubMenu() {
    int op_submenu;
    do {
        printf("\n1 - Alterar Livro\n");
        printf("2 - Pesquisar Livro\n");
        printf("3 - Excluir Livro\n");
        printf("4 - Recuperar Livro\n");
        printf("0 - Voltar ao Menu Principal\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &op_submenu);
        if (op_submenu < 0 || op_submenu > 4)
            printf("Opcao invalida. Selecione outra.\n\n");
    } while (op_submenu < 0 || op_submenu > 4);
    return op_submenu;
}


void main() {
    int op, op_submenu;

    printf("\n==========================================\n");
    printf("=        Bem-vindo ao Sistema            =\n");
    printf("=      da Biblioteca Anna Dek!           =\n");
    printf("==========================================\n");
    printf("\n");

    op = apresentar_menu();
    while (op != 0) {
        switch (op) {
            case 1:
                printf("\nInclusao de Novos Livros selecionada.\n");
                cadastrar_livros();
                printf("\n");
                break;

            case 2:
                op_submenu = apresentarSubMenu();
                while (op_submenu != 0) {
                    switch (op_submenu) {
                        case 1:
                            printf("Alterar Livro selecionado.\n");
                            break;
                        case 2:
                            printf("Pesquisar Livro selecionado.\n");
                            break;
                        case 3:
                            printf("Excluir Livro selecionado.\n");
                            break;
                        case 4:
                            printf("Recuperar Livro selecionado.\n");
                            break;
                    }
                    op_submenu = apresentarSubMenu();
                }
                break;

            case 3:
                printf("\nRelatorio de Livros [EMPRESTADOS] e [DISPONIVEIS] selecionado.\n");
                apresentar_filtrado();
                printf("\n");
                break;

            case 4:
                printf("\nRealizar Emprestimo selecionado.\n");
                break;

            case 5:
                printf("\nRealizar Devolucao selecionada.\n");
                break;

            case 6:
                printf("\nRelatorio de Livros [EMPRESTADOS] selecionado.\n");
                break;
        }
        op = apresentar_menu();
    }

    printf("\nFinalizando o Sistema.\n");
}
