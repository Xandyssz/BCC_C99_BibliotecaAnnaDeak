#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef int tp_int;

typedef struct {
    char titulo_livro[50], autores_livro[50];
    char situacao;
    tp_int Nr_tombo_livro, ano_livro, qntEmprestimo_livro;
    bool flag;
} tp_livro;


void adicionar_livro(tp_livro livro) {
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

tp_livro criar_livro() {
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
    livro.qntEmprestimo_livro = 0;

    return livro;
}

void cadastrar_livros() {
    tp_livro livro;
    char continua;

    printf("Iniciando Inclusao de livros...\n");
    printf("----------------------\n");
    do {
        livro = criar_livro();
        adicionar_livro(livro);
        printf("\nCadastrar outro Livro ?");
        scanf(" %c", &continua);
        continua = toupper(continua);
    } while (continua == 'S');
}

void mostrar_livro(tp_livro livro) {
    printf("%-12d %-35s %-25s %-13d %-18c %-10d\n",
           livro.Nr_tombo_livro, livro.titulo_livro, livro.autores_livro, livro.ano_livro, livro.situacao,
           livro.qntEmprestimo_livro);
}

void apresentar_cabecalho() {
    printf("%-12s %-35s %-25s %-10s %-15s %-12s\n",
           "Nr Tombo", "Titulo", "Autores", "Ano", "Situacao", "Qnt Emprestimo.");
}

void listar_livros() {
    FILE *arq;
    tp_livro livro;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("\nNao existe o arquivo.");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        apresentar_cabecalho();
        while (!feof(arq)) {
            if (livro.flag)
                mostrar_livro(livro);
            fread(&livro, sizeof(tp_livro), 1, arq);
        }
        fclose(arq);
    }
}

tp_livro buscar_livro_por_posicao(int posicao) {
    FILE *arq;
    tp_livro livro;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("\nNao existe o arquivo.");
    } else {
        fseek(arq, posicao * sizeof(tp_livro),SEEK_SET);
        fread(&livro, sizeof(tp_livro), 1, arq);
        fclose(arq);
    }
    return livro;
}

int encontrar_livro_por_titulo(char titulo_livro[]) {
    FILE *arq;
    tp_livro livro;
    int i = 0, posicao = -1;
    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("\nNao existe o arquivo.");
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


void sobreescrever_livro(tp_livro livro, int posicao) {
    FILE *arq;

    arq = fopen("biblioteca.dat", "rb+");
    if (arq == NULL) {
        printf("\nNao existe o arquivo.");
    } else {
        fseek(arq, posicao * sizeof(tp_livro),SEEK_SET);
        fwrite(&livro, sizeof(tp_livro), 1, arq);
        fclose(arq);
    }
}

void alterar_livro() {
    char titulo_livro[50];
    tp_livro livro;
    int pos;

    fflush(stdin);
    printf("Titulo do livro...: ");
    gets(titulo_livro);
    pos = encontrar_livro_por_titulo(titulo_livro);
    if (pos == -1) {
        printf("\nO Livro nao foi localizado.");
    } else {
        livro = buscar_livro_por_posicao(pos);
        printf("\nO Livro foi Localizado...\n");
        printf("\n");
        apresentar_cabecalho();
        mostrar_livro(livro);
        if (livro.flag) {
            printf("\n\nDigite os novos dados do aluno\n");
            livro = criar_livro();
            sobreescrever_livro(livro, pos);
        } else {
            printf("\nO Livro pesquisado esta excluido (OCULTO). nao eh possivel alterar\n");
        }
    }
}

void pesquisar_por_titulo() {
    char titulo_livro[50];
    tp_livro livro;
    int pos;

    fflush(stdin);
    printf("Titulo do livro...: ");
    gets(titulo_livro);
    pos = encontrar_livro_por_titulo(titulo_livro);
    if (pos == -1) {
        printf("\nO Livro nao foi localizado.");
    } else {
        livro = buscar_livro_por_posicao(pos);
        if (!livro.flag)
            printf("\nO Livro foi Localizado...\n");
        printf("\n");
        apresentar_cabecalho();
        mostrar_livro(livro);
        printf("\nO Livro pesquisado esta excluido (OCULTO).\n");
    }
}

void excluir_titulo() {
    char titulo_livro[50], excluir;
    tp_livro livro;
    int pos;

    fflush(stdin);
    printf("Titulo do livro...: ");
    gets(titulo_livro);
    pos = encontrar_livro_por_titulo(titulo_livro);
    if (pos == -1) {
        printf("\nO Livro nao foi localizado...\n");
    } else {
        livro = buscar_livro_por_posicao(pos);
        printf("\nLivro Selecionado para exlucsao:\n");
        apresentar_cabecalho();
        mostrar_livro(livro);
        if (livro.flag) {
            printf("Deseja excluir o livro? <S/N>: ");
            scanf(" %c", &excluir);
            excluir = toupper(excluir);
            if (excluir == 'S') {
                livro.flag = false;
                sobreescrever_livro(livro, pos);
            }
        } else {
            printf("\nO Livro ja esta excluido, nao eh possivel exclui-lo novamente\n");
        }
    }
}


void recuperar_titulo() {
    char titulo_livro[50], recuperar;
    tp_livro livro;
    int pos;

    fflush(stdin);
    printf("Titulo do livro...: ");
    gets(titulo_livro);
    pos = encontrar_livro_por_titulo(titulo_livro);
    if (pos == -1) {
        printf("\nO Livro não foi localizado...\n");
    } else {
        livro = buscar_livro_por_posicao(pos);
        printf("\nLivro Selecionado para recuperacao:\n");
        apresentar_cabecalho();
        mostrar_livro(livro);
        if (!livro.flag) {
            printf("Deseja recuperar o livro? <S/N>: ");
            scanf(" %c", &recuperar);
            recuperar = toupper(recuperar);
            if (recuperar == 'S') {
                livro.flag = true;
                sobreescrever_livro(livro, pos);
                printf("\nLivro recuperado com sucesso!\n");
            } else {
                printf("\nRecuperação cancelada.\n");
            }
        } else {
            printf("\nO livro ja esta ativo. Nao ha necessidade de recuperara-lo...\n");
        }
    }
}


int somar_emprestimos() {
    FILE *arq;
    tp_livro livro;
    int contEmprestimo = 0;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("\nNao existe o arquivo.\n");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        while (!feof(arq)) {
            if (livro.flag) {
                contEmprestimo = contEmprestimo + livro.qntEmprestimo_livro;
            }
            fread(&livro, sizeof(tp_livro), 1, arq);
        }
        fclose(arq);
    }
    return contEmprestimo;
}


void mostrar_livros_por_filtro() {
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
                            mostrar_livro(livro);
                        }
                    }
                    fread(&livro, sizeof(tp_livro), 1, arq);
                }
                fclose(arq);
            }
            break;
        case 3:
            printf("\nTotal de Emprestimos Realizados: %d\n", somar_emprestimos());
            break;
    }
}


void listar_emprestados() {
    FILE *arq;
    tp_livro livro;
    int qtd_emprestados = 0;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("Nao existe o arquivo.\n");
    } else {
        printf("\n");
        apresentar_cabecalho();

        fread(&livro, sizeof(tp_livro), 1, arq);

        while (!feof(arq)) {
            if (livro.flag) {
                if (livro.situacao == 'E') {
                    mostrar_livro(livro);
                    qtd_emprestados++;
                }
            }
            fread(&livro, sizeof(tp_livro), 1, arq);
        }
        fclose(arq);
    }
    printf("\nQuantidade de Livros Emprestados: %d\n", qtd_emprestados);
}


int menu_principal() {
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

    op = menu_principal();
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
                            alterar_livro();
                            break;
                        case 2:
                            printf("Pesquisar Livro selecionado.\n");
                            pesquisar_por_titulo();
                            break;
                        case 3:
                            printf("Excluir Livro selecionado.\n");
                            excluir_titulo();
                            break;
                        case 4:
                            printf("Recuperar Livro selecionado.\n");
                            recuperar_titulo();
                            break;
                    }
                    op_submenu = apresentarSubMenu();
                }
                break;

            case 3:
                printf("\nRelatorio de Livros [EMPRESTADOS] e [DISPONIVEIS] selecionado.\n");
                mostrar_livros_por_filtro();
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
                listar_emprestados();
                printf("\n");
                break;
        }
        op = menu_principal();
    }

    printf("\nFinalizando o Sistema.\n");
}