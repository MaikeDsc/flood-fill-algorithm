// Nome completo:
// Matricula:
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

//prohibido utilizar variáveis globais, exceto algum #define que seja necessário para o funcionamento do programa. 

// não alterar esta struct
typedef struct {
    int linhas;
    int colunas;
    int ** I;
} Matriz;

// Não alterar este vetor
const char cores[][8] = {
    "\033[30m", // 0 - preto
    "\033[31m", // 1 - vermelho
    "\033[32m", // 2 - verde
    "\033[33m", // 3 - amarelo
    "\033[34m", // 4 - azul
    "\033[35m", // 5 - magenta
    "\033[36m", // 6 - ciano
    "\033[37m", // 7 - branco
    "\033[90m", // 8 - cinza
};

// Não alterar esta função
void print_matrix(Matriz matriz) {
    printf("\n");
    for (int i = 0; i < matriz.linhas; i++) {
        printf("%d ", i);
        for (int j = 0; j < matriz.colunas; j++) {
            printf("%s%c", cores[matriz.I[i][j]], 35);
        }
        printf("\033[0m\n");
    }
    printf("\n");
}

// Prohibido alterar a assinatura da função colorir.
void colorir(int i, int j, int nova_cor, int cor_atual, Matriz matriz) {
    // completar com a mesma lógica do TP1, prohibido usar uma lógica diferente da do TP1, apenas pode ser alterado a forma de percorrer a matriz, mas a lógica de colorir deve ser a mesma.
}

// Prohibido alterar a assinatura da função ler_arquivo.
int** ler_arquivo(char *nome_arquivo, Matriz *matriz) {

    // Abre o arquivo para leitura com fopen e verifica se foi aberto com sucesso, caso contrário imprime uma mensagem de erro e encerra o programa com exit(1)

    // Lê as dimensões da matriz (linhas e colunas) do arquivo usando fscanf, verificando se a leitura foi bem-sucedida e se os valores são válidos (maiores que zero). Caso contrário, fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).

    // Aloca dinamicamente a matriz de inteiros com malloc usando int** (vetor de ponteiros), verificando se a alocação foi bem-sucedida. Caso contrário, fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).

    // Aloca dinamicamente cada linha da matriz com malloc usando I[], verificando se a alocação foi bem-sucedida. Caso contrário, libera a memória já alocada (todas as linhas que foram alocadas e o vetor de ponteiros), fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1). 

    // Lê os valores da matriz do arquivo usando fscanf, verificando se a leitura foi bem-sucedida e se os valores são válidos (entre 0 e 8). Caso contrário, libera a memória alocada (todas as linhas e o vetor de ponteiros), fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).

    // Fecha o arquivo e retorna o ponteiro para a matriz alocada.
    fclose(arquivo);
    return I;
}

// Prohibido alterar esta função utilizada para limpar_buffer_do_teclado.
void limpar_buffer_do_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Prohibido alterar a assinatura da função main.
int main(int argc, char *argv[]) {
    
    int i, j, nova_cor, cor_atual;

    // Verifica se o número de argumentos passados para o programa é igual a 2 (o nome do programa e o nome do arquivo da matriz). Caso contrário, imprime uma mensagem de uso e retorna 1.

    Matriz matriz = {0, 0, NULL};
    matriz.I = ler_arquivo(argv[1], &matriz);    

    // Cria o arquivo de log "color_fill_log.txt" usando a função criar_arquivo_log do TAD log.h. Caso não seja possível criar o arquivo, imprime uma mensagem de erro, libera a memória da matriz e retorna 1.
    
    while (1)
    {
        print_matrix(matriz);

        // Lógica de interação com o usuário para solicitar a nova cor, a posição (i, j) e chamar a função colorir. A cada iteração, imprime a matriz atualizada e solicita a entrada do usuário.

        // Verifica se a cor de entrada do usuário é válida (cor entre 0 e 8 ou -1 para sair). Caso a entrada seja inválida, imprime uma mensagem de erro "Entrada inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.
        
        // Solicita a coordenada i. Verifica se a coordenada é válida (posição dentro dos limites da matriz). Caso a entrada seja inválida, imprime uma mensagem de erro "Coordenada i inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.

        // Solicita a coordenada j. Verifica se a coordenada é válida (posição dentro dos limites da matriz). Caso a entrada seja inválida, imprime uma mensagem de erro "Coordenada j inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.

        // Após colorir a matriz, chama a função log_append para registrar a operação no arquivo de log. Caso não seja possível escrever no arquivo, imprime uma mensagem de aviso.

        // Verifica se a nova cor é diferente da cor atual na posição (i, j). Caso sejam iguais, imprime uma mensagem de erro "A nova cor deve ser diferente da cor na posição atual\n" e solicita novamente a entrada do usuário.

        colorir(i, j, nova_cor, cor_atual, matriz);

        if (!log_append("color_fill_log.txt", nova_cor, i, j)) {
            fprintf(stderr, "Aviso: nao foi possivel escrever o color_fill_log.txt\n");
        }
    }
    
    // Liberar memória da matriz antes de encerrar o programa

    return 0;
}