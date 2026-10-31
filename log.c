// Nome completo: Maquiavel dos Santos Campos 
// Matricula: 22653828
#include <stdio.h>
#include "log.h"

int criar_arquivo_log(const char *nome_arquivo) {
    // cria arquivo de log vazio
    FILE *arquivoLog = fopen("log.txt", "w");

    // verifica se o arquivo foi criado com sucesso, caso contrário retorna 0
    if(arquivoLog == NULL){
        return 0;
    }
    // verifica se o arquivo foi fechado com sucesso, caso contrário retorna 0
    if(fclose(arquivoLog) != 0){
        return 0;
    }
    return 1;
}

int log_append(const char *nome_arquivo, int cor, int i, int j) {
    // Abre o arquivo e faz append no final do arquivo de log no formato: "cor=cor i=i j=j\n". Verifica se o arquivo foi aberto com sucesso, caso contrário retorna 0
    
    // Verifica se a escrita no arquivo foi bem-sucedida, caso contrário fecha o arquivo eretorna 0. Utiliza fprintf() para escrever no arquivo.

    // Fecha o arquivo. Verifica se o arquivo foi fechado com sucesso, caso contrário retorna 0

    return 1;
}
