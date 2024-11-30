# 📚 Sistema de Biblioteca Anna Déak

## 📝 Sobre o Projeto

Este projeto foi desenvolvido para gerenciar os empréstimos realizados na biblioteca do **IFSP-PEP**, permitindo um controle eficiente sobre os livros cadastrados, emprestados e devolvidos. A aplicação oferece funcionalidades como inclusão, alteração, pesquisa, exclusão lógica, recuperação de registros e geração de relatórios.

Este trabalho foi desenvolvido como parte da disciplina **Algoritmos e Programação II** do curso de **Bacharelado em Ciência da Computação**.

---

## 🛠️ Funcionalidades Principais

### 1. Cadastro de Livros
- **Inclua novos livros no sistema com os seguintes dados:**
  - **Número do tombo** (identificação única do livro);
  - **Título**
  - **Autores do livro**;
  - **Ano de publicação**;
  - Situação inicial definida como `D - Disponível`;
  - Quantidade inicial de empréstimos definida como `0`.

### 2. Gerenciamento de Livros
- **Alterar Livro:** Atualize informações como título, autores e ano de publicação. `A quantidade de empréstimos permanece inalterada.`
- **Pesquisar Livro:** Busque livros pelo título e visualize suas informações.
- **Excluir Livro:** Marque um livro como inativo (exclusão lógica).
- **Excluir Livro:** Remove permanentemente um livro do sistema. (Exclusão Física) Este processo é irreversível.

- **Recuperar Livro:** Reative um livro previamente excluído logicamente.

### 3. Relatórios
- **Lista de Livros:**
  - Mostra todos os livros cadastrados com suas situações (`Disponível` ou `Emprestado`).
  - Exibe a quantidade total de empréstimos realizados pela biblioteca.

- **Livros Emprestados:**
  - Lista todos os livros com situação `E - Emprestado`.
  - Exibe a quantidade total de livros emprestados.
 
- **Livros Indisponíveis:**
  - Lista todos os livros que estão indisponiveis ou seja `flag - false`

### 4. Empréstimos e Devoluções
- **Realizar Empréstimo:**
  - Solicite o número do tombo do livro.
  - Confirme se o livro está disponível para empréstimo.
  - Atualize a situação para `E - Emprestado`.
  - Incrementa a quantidade de empréstimos realizados.

- **Devolução:**
  - Solicite o número do tombo.
  - Confirme se o livro está emprestado.
  - Atualize a situação para `D - Disponível`.

---

## 🗂️ Estrutura do Código

### Arquivos
- **`biblioteca.c`**: Contém toda a lógica do sistema, incluindo as funções de gerenciamento de livros e interação com o usuário. | Executa s/ Bibilioteca.
- **`gerenciar_biblioteca.c`**: Arquivo com funções específicas para manipular os dados da biblioteca. | Executa c/ bibliotecas
- **`biblioteca.dat`**: Arquivo binário usado para armazenar os dados dos livros.

### Biblioteca
- **`biblioteca_arquivo.h`**: Contém funções para manipulação do arquivo binário `biblioteca.dat`.
- **`biblioteca_interface.h`**: Implementa a interface do programa, incluindo os menus.
- **`estrutura.h`**: Define as estruturas de dados, como a `tp_livro`.



### Estrutura de Dados
A estrutura `tp_livro` define os campos necessários para representar um livro:
```c
typedef struct {
    char titulo_livro[100], autores_livro[100];
    char situacao; // 'D' para Disponível, 'E' para Emprestado
    int Nr_tombo_livro, ano_livro, qntEmprestimo_livro;
    bool flag; // true para ativo, false para excluído logicamente
} tp_livro;
```

## 🔧 Funcionalidades Detalhadas

### Inclusão de Livros
- Solicite as informações básicas do livro **(número do tombo, título, autores, ano de publicação)**.
- Grave o livro no arquivo binário ``biblioteca.dat``.
- Defina a situação inicial como D - ``Disponível`` e o número de empréstimos como ``0``.

### Alteração de Livros
- Pesquise o livro pelo ``título``.
- Altere as informações desejadas, exceto a ``quantidade de empréstimos``.

### Controle de Exclusão e Recuperação
- Exclusão lógica: O livro permanece no arquivo, mas é marcado como ``inativo``.
- Recuperação: Permite ``reativar`` livros previamente excluídos.
  
### Relatórios
- **Exibe relatórios filtrados:**
  - Número do tombo **(identificação única do livro)**;
  - Todos os livros disponíveis.
  - Todos os livros emprestados.
  - Quantidade total de empréstimos realizados.
 
## 🚀 Como Executar
**Pré-requisitos**

```Um compilador C, como GCC```

### - Passo a Passo
- Clone o Repositório:
```
git clone https://github.com/Xandyssz/BCC_C99_BibliotecaAnnaDeak.git
cd BCC_C99_BibliotecaAnnaDeak
```

## 🗒️ Exemplo de Execução
- Menu Principal
```
==========================================
=        Bem-vindo ao Sistema            =
=      da Biblioteca Anna Dek!           =
==========================================

1 - Inclusão de Novos Livros
2 - Alterar, Pesquisar e Excluir/Recuperar Livros
3 - Relatório de Livros [EMPRESTADOS] e [DISPONÍVEIS]
4 - Realizar Empréstimo
5 - Realizar Devolução
6 - Relatório de Livros [EMPRESTADOS]
7 - Relatório de Livros [INDISPONIVEIS]
0 - Sair
```
- 1 - Inclusão de Novos Livros
  **Informe os dados do livro:**
```
Tombo do livro: 12345
Título do livro: Ensino de algoritmos com uso de fluxograma, pseudolinguagem e linguagem C
Autores do livro: Melissa Marchiani Palone Zanatta e César Alberto da Silva
Ano do livro: 2021
```
- 2 - O livro será salvo com a situação inicial D - Disponível.

## 🖋️ Autor(es)
Este projeto foi desenvolvido por estudantes do curso de Bacharelado em Ciência da Computação.<br>
**Professores Orientadores: André e Melissa**.<br>
**Alunos: Alexandre Ferreira e Pedro Lopes**
