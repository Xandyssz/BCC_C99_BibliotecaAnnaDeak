#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef int tp_int;

typedef struct {
    char titulo_livro[100], autores_livro[100];
    char situacao;
    tp_int Nr_tombo_livro, ano_livro, qntEmprestimo_livro;
    bool flag;
} tp_livro;


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

// 1.2 - REMOVE O CARACTERE DE QUEBRA DE LINHA (\N) DE UMA STRING
void removerQuebra(char atributo[]) {
    if (atributo[strlen(atributo) - 1] == '\n') {
        atributo[strlen(atributo) - 1] = '\0';
    }
}

// 1.3 - LÊ UMA STRING DO USUÁRIO E REMOVE O CARACTERE DE QUEBRA DE LINHA USANDO A FUNÇÃO REMOVERQUEBRA
void lerString(char atributo[], int tamanho) {
    fgets(atributo, tamanho, stdin);
    removerQuebra(atributo);
}

// 1.4 - Lê um número inteiro do usuário, verificando se o valor é maior que 0.
void lerInt(int *atributo) {
    do {
        scanf("%d", atributo);
        if (*atributo <= 0) {
            printf("Numero invalido, insira um valor maior que 0.\n");
        }
    } while (*atributo <= 0);
}

tp_livro criar_livro() {
    tp_livro livro;

    do {
        printf("Tombo do livro...:");
        lerInt(&livro.Nr_tombo_livro);
        if (verificarTombo(livro.Nr_tombo_livro)) {
            printf("Tombo ja Cadastrado, insira outro tombo\n");
        }
    } while (verificarTombo(livro.Nr_tombo_livro));

    fflush(stdin);
    printf("Titulo do livro...: ");
    lerString(livro.titulo_livro, 100);

    printf("Autores do livro...: ");
    lerString(livro.autores_livro, 100);

    printf("Ano do livro...:");
    lerInt(&livro.ano_livro);

    livro.situacao = 'D';
    livro.qntEmprestimo_livro = 0;

    return livro;
}

void cadastrar_livros() {
    tp_livro livro;
    char continua;

    printf("Iniciando Inclusao de livros...\n");
    do {
        livro = criar_livro();
        adicionar_livro(livro);
        printf("\nCadastrar outro livro? <S/N>: ");
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
        printf("\nO Arquivo binario nao existe.\n");
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
        printf("\nO Arquivo binario nao existe.\n");
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

void alterar_livro() {
    FILE *arq;
    char situacao;
    tp_livro livro;
    int pos, qntEmprestimo = 0;


    arq = fopen("biblioteca.dat", "rb+");
    if (arq == NULL) {
        printf("O Arquivo binario nao existe.\n");
    } else {
        fflush(stdin);
        printf("Informe o titulo do livro que deseja alterar: ");
        lerString(livro.titulo_livro, 100);
        pos = encontrar_livro_por_titulo(livro.titulo_livro);
        if (pos == -1) {
            printf("\nO Livro nao foi encontrado. Verifique o titulo e tente novamente.\n");
        } else {
            livro = buscar_livro_por_posicao(pos);
            printf("\nLivro localizado com sucesso!\n");
            printf("\n");
            apresentar_cabecalho();
            mostrar_livro(livro);
            qntEmprestimo = qntEmprestimo + livro.qntEmprestimo_livro;
            situacao = livro.situacao;
            if (livro.flag) {
                printf("\nDigite os novos dados para o livro selecionado...\n");
                livro = criar_livro();
                livro.qntEmprestimo_livro = qntEmprestimo;
                livro.situacao = situacao;
                sobreescrever_livro(livro, pos);
            } else {
                printf("\nEste livro foi excluido e nao pode ser alterado no momento.\n");
            }
        }
        printf("Quantidade de Emprestimos do Livro...: %d:", qntEmprestimo);
        printf("\nSituacao do Livro..: %c", situacao);
        fclose(arq);
    }
}

void pesquisar_por_titulo() {
    FILE *arq;
    tp_livro livro;
    int pos;

    arq = fopen("biblioteca.dat", "rb+");
    if (arq == NULL) {
        printf("O Arquivo binario nao existe.\n");
    } else {
        fflush(stdin);
        printf("Titulo do livro...: ");
        lerString(livro.titulo_livro, 100);
        pos = encontrar_livro_por_titulo(livro.titulo_livro);
        if (pos == -1) {
            printf("\nO Livro nao foi localizado.\n");
        } else {
            livro = buscar_livro_por_posicao(pos);
            if (livro.flag) {
                printf("\nLivro localizado com sucesso!\n");
                printf("\n");
                apresentar_cabecalho();
                mostrar_livro(livro);
            } else {
                printf("\nO Livro pesquisado esta excluido (OCULTO).\n");
            }
        }
        fclose(arq);
    }
}

void excluir_titulo() {
    char titulo_livro[100], excluir;
    tp_livro livro;
    int pos, op;

    do {
        printf("1 - Exclusao Logica\n");
        printf("2 - Exclusao Fisica\n");
        printf("0 - Sair\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 2) {
            printf("\nOpcao invalida. Selecione uma opcao valida...\n\n");
        }
    } while (op < 0 || op > 2);
    switch (op) {
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        case 1:
            printf("Exclusao Logica\n");
            fflush(stdin);
            printf("Informe o titulo do livro que deseja excluir...:");
            gets(titulo_livro);
            pos = encontrar_livro_por_titulo(titulo_livro);
            if (pos == -1) {
                printf("\nLivro nao encontrado. Certifique-se de que o titulo esta correto e tente novamente.\n");
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
                    printf("\nO livro ja foi excluido anteriormente e nao pode ser excluido novamente.\n");
                }
                break;
            case 2:
                printf("Exclusao Fisica\n");
                FILE *atual, *novo;

                atual = fopen("biblioteca.dat", "rb");
                novo = fopen("novo.dat", "wb");
                if (atual != NULL && novo != NULL) {
                    printf("\nLivros Selecionado para serem mantidos:\n");
                    apresentar_cabecalho();
                    while (fread(&livro, sizeof(tp_livro), 1, atual)) {
                        if (livro.flag == true) {
                            fwrite(&livro, sizeof(tp_livro), 1, novo);
                            mostrar_livro(livro);
                        }
                    }
                    fclose(atual);
                    fclose(novo);
                    remove("biblioteca.dat");
                    rename("novo.dat", "biblioteca.dat");
                } else
                    printf("Houve um erro!!!!");
            }
            break;
    }
}


void recuperar_titulo() {
    FILE *arq;
    char recuperar;
    tp_livro livro;
    int pos;


    arq = fopen("biblioteca.dat", "rb+");
    if (arq == NULL) {
        printf("O Arquivo binario nao existe.\n");
    } else {
        fflush(stdin);
        printf("Informe o titulo do livro que deseja recuperar..: ");
        lerString(livro.titulo_livro, 100);
        pos = encontrar_livro_por_titulo(livro.titulo_livro);
        if (pos == -1) {
            printf("\nLivro nao encontrado. Certifique-se de que o titulo esta correto e tente novamente.\n");
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
                    printf("\nRecuperacao cancelada.\n");
                }
            } else {
                printf("\nO livro ja esta ativo e nao precisa ser recuperado.\n");
            }
        }
        fclose(arq);
    }
}


int somar_emprestimos() {
    FILE *arq;
    tp_livro livro;
    int contEmprestimo = 0;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("O Arquivo binario nao existe..\n");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        while (!feof(arq)) {
            if (livro.flag) {
                contEmprestimo = contEmprestimo + livro.qntEmprestimo_livro;
            }
            fread(&livro, sizeof(tp_livro), 1, arq);
        }
        fclose(arq);
        printf("\nTotal de Emprestimos Realizados: %d\n", contEmprestimo); // MEXI AQ
    }
    return contEmprestimo;
}

void realizar_emprestimo() {
    FILE *arq;
    char emprestar;
    int Nr_tombo_livro, pos;
    tp_livro livro;

    arq = fopen("biblioteca.dat", "rb+");
    if (arq == NULL) {
        printf("O Arquivo binario nao existe.\n");
    } else {
        fflush(stdin);
        printf("Informe o numero do tombo do livro que deseja emprestar...: ");
        scanf("%d", &Nr_tombo_livro);
        pos = encontrar_livro_por_tombo(Nr_tombo_livro);
        if (pos == -1) {
            printf("\nLivro nao encontrado. Certifique-se de que o numero do tombo esta correto e tente novamente.\n");
        } else {
            livro = buscar_livro_por_posicao(pos);
            printf("\nLivro localizado com sucesso!\n");
            printf("\n");
            apresentar_cabecalho();
            mostrar_livro(livro);

            if (livro.situacao == 'D') {
                printf("Deseja realmente emprestar o livro? <S/N>: ");
                scanf(" %c", &emprestar);
                emprestar = toupper(emprestar);
                if (emprestar == 'S') {
                    livro.situacao = 'E';
                    livro.qntEmprestimo_livro++;
                    sobreescrever_livro(livro, pos);
                    printf("\nLivro emprestado com sucesso!\n");
                } else {
                    printf("\nOperacao de emprestimo cancelada.\n");
                }
            } else {
                printf("\nO livro ja esta emprestado e indisponivel no momento.\n");
            }
        }
        fclose(arq);
    }
}

void realizar_devolucao() {
    FILE *arq;
    char devolver;
    int Nr_tombo_livro, pos;
    tp_livro livro;

    arq = fopen("biblioteca.dat", "rb+");
    if (arq == NULL) {
        printf("\nO Arquivo binario nao existe..\n");
    } else {
        fflush(stdin);
        printf("\nInforme o numero do tombo do livro que deseja devolver...: ");
        scanf("%d", &Nr_tombo_livro);
        pos = encontrar_livro_por_tombo(Nr_tombo_livro);
        if (pos == -1) {
            printf("\nLivro nao encontrado. Certifique-se de que o numero do tombo esta correto e tente novamente.\n");
        } else {
            livro = buscar_livro_por_posicao(pos);
            printf("\nLivro localizado com sucesso!\n");
            printf("\n");
            apresentar_cabecalho();
            mostrar_livro(livro);

            if (livro.situacao == 'E') {
                printf("\nDeseja confirmar a devolucao do livro? (S/N): ");
                scanf(" %c", &devolver);
                devolver = toupper(devolver);
                if (devolver == 'S') {
                    livro.situacao = 'D';
                    sobreescrever_livro(livro, pos);
                    printf("\nDevolucao realizada com sucesso!\n");
                } else {
                    printf("\nDevolucao cancelada pelo usuário.\n");
                }
            } else {
                printf("\nEste livro nao esta registrado como emprestado. Devolucao nao eh necessaria.\n");
            }
        }
        fclose(arq);
    }
}

void mostrar_livros_por_filtro() {
    FILE *arq;
    tp_livro livro;
    int op, contLivro = 0;

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
                printf("O Arquivo binario nao existe..\n");
            } else {
                printf("\n");

                fread(&livro, sizeof(tp_livro), 1, arq);
                while (!feof(arq)) {
                    if (livro.flag) {
                        if ((op == 1 && livro.situacao == 'E') || (op == 2 && livro.situacao == 'D')) {
                            if (!contLivro) {
                                apresentar_cabecalho();
                            }
                            mostrar_livro(livro);
                            contLivro++;
                        }
                    }
                    fread(&livro, sizeof(tp_livro), 1, arq);
                }
                if (!contLivro) {
                    if (op == 1) {
                        printf("Nao ha livros emprestados no sistema.\n");
                    } else {
                        printf("Nao ha livros emprestados no sistema.\n");
                    }
                }

                fclose(arq);
            }
            break;
        case 3:
            somar_emprestimos();
            break;
    }
}

void listar_emprestados() {
    FILE *arq;
    tp_livro livro;
    int qtd_emprestados = 0;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("O Arquivo binario nao existe..\n");
    } else {
        printf("\n");
        fread(&livro, sizeof(tp_livro), 1, arq);
        while (!feof(arq)) {
            if (livro.flag) {
                if (livro.situacao == 'E') {
                    if (!qtd_emprestados) {
                        apresentar_cabecalho();
                    }
                    mostrar_livro(livro);
                    qtd_emprestados++;
                }
            }
            fread(&livro, sizeof(tp_livro), 1, arq);
        }
        // Se nenhum livro foi encontrado
        if (!qtd_emprestados) {
            printf("Nao ha livros emprestados no sistema.\n");
        } else {
            printf("\nQuantidade de Livros Emprestados: %d\n", qtd_emprestados);
        }
        fclose(arq);
    }
}

// LISTAR LIVROS INDISPONIVEIS NO SISTEMA
void listar_indisponiveis() {
    FILE *arq;
    tp_livro livro;
    int contIndisponiveis = 0;

    arq = fopen("biblioteca.dat", "rb");
    if (arq == NULL) {
        printf("O Arquivo binario nao existe..\n");
    } else {
        fread(&livro, sizeof(tp_livro), 1, arq);
        while (!feof(arq)) {
            if (!livro.flag) {
                if (!contIndisponiveis) {
                    printf("\n");
                    apresentar_cabecalho();
                }
                mostrar_livro(livro);
                contIndisponiveis++;
            }
            fread(&livro, sizeof(tp_livro), 1, arq);
        }
        if (!contIndisponiveis) {
            printf("Nao ha livros indisponiveis no sistema.\n");
        }
        fclose(arq);
    }
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
        printf("7 - Relatorio de Livros [INDISPONIVEIS]\n");

        printf("0 - Sair\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 7)
            printf("Opcao invalida. Selecione outra.\n\n");
    } while (op < 0 || op > 7);
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
                printf("Realizar Emprestimo selecionado.\n");
                realizar_emprestimo();
                printf("\n");
                break;

            case 5:
                printf("Realizar Devolucao selecionada.");
                realizar_devolucao();
                printf("\n");
                break;

            case 6:
                printf("\nRelatorio de Livros [EMPRESTADOS] selecionado.");
                listar_emprestados();
                printf("\n");
                break;
            case 7:
                printf("\nRelatorio de Livros [INDISPONIVEIS] selecionado.\n");
                listar_indisponiveis();
                printf("\n");
                break;
        }
        op = menu_principal();
    }
    printf("\nFinalizando o Sistema.\n");
}
