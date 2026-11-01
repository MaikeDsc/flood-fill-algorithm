// Nome completo: Maquiavel dos Santos Campos 
// Matricula: 22653828
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
//verifica se o elemento pertence a região de pintura e aos limites da matriz
int verifica_validade(int i, int j, int cor_atual, Matriz matriz){
    if(i> matriz.linhas-1 || j>matriz.colunas-1 || i<0 || j<0){ //se o indice não está dentro do limite da matriz
        return 0;
    }
    else if (cor_atual != matriz.I[i][j]){ //caso encontre uma barreira, celula de outra cor
        return 0;
    }
    
    return 1;
}


// Prohibido alterar a assinatura da função colorir.
void colorir(int i, int j, int nova_cor, int cor_atual, Matriz matriz) {
    // completar com a mesma lógica do TP1, prohibido usar uma lógica diferente da do TP1, apenas pode ser alterado a forma de percorrer a matriz, mas a lógica de colorir deve ser a mesma.
    printf("colorindo... \n");
    if(nova_cor != cor_atual && verifica_validade(i,j,cor_atual,matriz)){
                              //pintamos o ponto indicado para -1(cor que não existe na tabela)
        matriz.I[i][j] = -1;          //assim vamos fiferenciando a celula que queremos pintar de
                                // outras celulas da mesma cor. Assim evitamos pintar qualquer celula que tenha a "cor_atual"
        int continua_verif = 1;
        while(continua_verif){  //enquanto houver indices sendos pintados de -1 buscamos por novos para pintar 
            continua_verif = 0;

            for(int x = 0; x< matriz.linhas; x++){
                for(int y = 0; y < matriz.colunas; y++){

                    if(matriz.I[x][y] == -1){ // verifica se os vizinhos são validos para pintar. Se sim, os pintas.
                        
                        if(verifica_validade(x, y+1, cor_atual, matriz)){
                            matriz.I[x][y+1] = -1;
                            continua_verif = 1;  // pintou um pixel, logo a busca deve continuar. 
                        }
                        if(verifica_validade(x+1, y, cor_atual, matriz)){
                            matriz.I[x+1][y] = -1;
                            continua_verif = 1;
                        }
                        if(verifica_validade(x-1, y, cor_atual, matriz)){
                            matriz.I[x-1][y] = -1;
                            continua_verif = 1;
                        }
                        if(verifica_validade(x, y-1, cor_atual, matriz)){
                            matriz.I[x][y-1] = -1;
                            continua_verif = 1;
                        }
                    }
                }
            }
        }
        // troca os pixel com valores -1 para a nova cor solicitada. 
        for(int x = 0; x< matriz.linhas; x++){
            for(int y = 0; y < matriz.colunas; y++){
                if(matriz.I[x][y] == -1){
                    matriz.I[x][y] = nova_cor;
                }
            }
        }
        
    }
    else{
        return;
    }

}

// Prohibido alterar a assinatura da função ler_arquivo.
int** ler_arquivo(char *nome_arquivo, Matriz *matriz) {

    // Abre o arquivo para leitura com fopen e verifica se foi aberto com sucesso, caso contrário imprime uma mensagem de erro e encerra o programa com exit(1)
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo '%s'\n", nome_arquivo);
        exit(1);
    }
    
    // Lê as dimensões da matriz (linhas e colunas) do arquivo usando fscanf, verificando se a leitura foi bem-sucedida e se os valores são válidos (maiores que zero). Caso contrário, fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).
    
    fscanf(arquivo, "%d %d", &matriz->linhas, &matriz->colunas);
    //printf("linhas: %d colunas: %d\n", matriz->linhas, matriz->colunas);
    if(matriz->linhas<0 && matriz->colunas<0){
        printf("As dimensões informadas, não forman uma matriz. m ou n <= 0\n");
        exit(1);
    }
    // Aloca dinamicamente a matriz de inteiros com malloc usando int** (vetor de ponteiros), verificando se a alocação foi bem-sucedida. Caso contrário, fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).
    matriz->I = (int**)malloc(matriz->linhas * sizeof(int*));
    // Aloca dinamicamente cada linha da matriz com malloc usando I[], verificando se a alocação foi bem-sucedida. Caso contrário, libera a memória já alocada (todas as linhas que foram alocadas e o vetor de ponteiros), fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1). 
    for(int i = 0; i< matriz->linhas; i++){
        matriz->I[i] = (int*)malloc(matriz->colunas * sizeof(int));
    }
    // Lê os valores da matriz do arquivo usando fscanf, verificando se a leitura foi bem-sucedida e se os valores são válidos (entre 0 e 8). Caso contrário, libera a memória alocada (todas as linhas e o vetor de ponteiros), fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).
    int matrizValida = 1;
    for(int i =0; i< matriz->linhas && matrizValida; i++){
        for(int j =0; j< matriz->colunas && matrizValida; j++){
            fscanf(arquivo, "%d", &matriz->I[i][j]);
            if(matriz->I[i][j] <0 || matriz->I[i][j] > 8){
                matrizValida =  0;
            }
        }
    }
    if(matrizValida == 0){
        for(int i = 0; i< matriz->linhas; i++){
            free(matriz->I[i]);
        }
        free(matriz->I);
        fclose(arquivo);
        printf("Matriz com cores invalidas.\nEncerrando programa.\n");
        exit(1); 
    }

    // Fecha o arquivo e retorna o ponteiro para a matriz alocada.
    fclose(arquivo);
    return matriz->I;
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
    if(argc !=2){
        printf("Argumentos passados incorretamentes\n");
        return 1;
    }
    Matriz matriz = {0, 0, NULL};
    matriz.I = ler_arquivo(argv[1], &matriz);    

    // Cria o arquivo de log "color_fill_log.txt" usando a função criar_arquivo_log do TAD log.h. Caso não seja possível criar o arquivo, imprime uma mensagem de erro, libera a memória da matriz e retorna 1.
    if(criar_arquivo_log("color_fill_log.txt")==0){
        printf("Erro ao criar arquivo de log.\n");
        free(matriz.I);
    }

    while (1)
    {
        print_matrix(matriz);

        // Lógica de interação com o usuário para solicitar a nova cor, a posição (i, j) e chamar a função colorir. A cada iteração, imprime a matriz atualizada e solicita a entrada do usuário.
        printf("Informe a cor (0 a 8) ou (-1 para sair):\n");
        scanf("%d",&nova_cor);
        
        // Verifica se a cor de entrada do usuário é válida (cor entre 0 e 8 ou -1 para sair). Caso a entrada seja inválida, imprime uma mensagem de erro "Entrada inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.
        while(nova_cor<-1 || nova_cor>8){  //cor invalida
            printf("a cor informada eh invalida\n");
            limpar_buffer_do_teclado();
            printf("Informe a cor (0 a 8) ou (-1 para sair):\n");
            scanf("%d",&nova_cor);
        }
        if(nova_cor==-1){break;}
        // Solicita a coordenada i. Verifica se a coordenada é válida (posição dentro dos limites da matriz). Caso a entrada seja inválida, imprime uma mensagem de erro "Coordenada i inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.
        printf("Informe a coordenada i (0 - %d):\n", matriz.linhas-1);
        scanf("%d",&i);
        while(i<0 || i>(matriz.linhas-1)){  //linha invalida
            printf("i eh invalida\n");
            limpar_buffer_do_teclado();
            printf("Informe a cooredenada i(0 - %d):\n", matriz.linhas-1);
            scanf("%d",&i);
        }
        // Solicita a coordenada j. Verifica se a coordenada é válida (posição dentro dos limites da matriz). Caso a entrada seja inválida, imprime uma mensagem de erro "Coordenada j inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.
        printf("Informe a coordenada j (0 - %d):\n", matriz.colunas-1);
        scanf("%d",&j);
        while(j<0 || j>(matriz.colunas-1)){  //coluna invalida
            printf("j eh invalida!\n");
            limpar_buffer_do_teclado();
            printf("Informe a cooedenada j (0 - %d):\n", matriz.colunas-1);
            scanf("%d",&j);
        }
        // Após colorir a matriz, chama a função log_append para registrar a operação no arquivo de log. Caso não seja possível escrever no arquivo, imprime uma mensagem de aviso.
        cor_atual= matriz.I[i][j];
        // Verifica se a nova cor é diferente da cor atual na posição (i, j). Caso sejam iguais, imprime uma mensagem de erro "A nova cor deve ser diferente da cor na posição atual\n" e solicita novamente a entrada do usuário.
        while(nova_cor == cor_atual || nova_cor<-1 || nova_cor>8){  //coluna invalida
            printf("A nova cor deve ser diferente da cor na posição atual e valida\n");
            limpar_buffer_do_teclado();
            printf("Informe a cor (0 a 8) ou (-1 para sair):\n");
            scanf("%d",&nova_cor);
        }
        if(nova_cor==-1){break;}
        colorir(i, j, nova_cor, cor_atual, matriz);
        //print_matrix(matriz);
        if (!log_append("color_fill_log.txt", nova_cor, i, j)) {
            fprintf(stderr, "Aviso: nao foi possivel escrever o color_fill_log.txt\n");
        }
    }
    
    // Liberar memória da matriz antes de encerrar o programa
    free(matriz.I);
    return 0;
}