#include <stdio.h>
#include "estrutura.h"
#include "biblioteca_arquivo.h"
#include "biblioteca_interface.h"

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
                printf("\nRelatorio de Livros [EMPRESTADOS] selecionado.\n");
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
