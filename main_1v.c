//Nome: Maquiavel dos Santos Campos
//Matricula: 22653828
//ABI - Computação
#include <stdio.h>

#define linhas 10
#define colunas 16

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

void print_matrix(int I[linhas][colunas]) {
    printf("\n");

    for (int i = 0; i < linhas; i++) {
        printf("%d ", i);
        for (int j = 0; j < colunas; j++) {
            printf("%s%c", cores[I[i][j]], 35);
        }
        printf("\033[0m\n");
    }
    printf("\n");
}

//verifica se o elemento pertence a região de pintura e aos limites da matriz
int verifica_validade(int i, int j, int cor_atual, int I[linhas][colunas]);

void colorir(int i, int j, int nova_cor, int cor_atual, int I[linhas][colunas]) {
    printf("colorindo... \n");
    if(nova_cor != cor_atual && verifica_validade(i,j,cor_atual,I)){
                              //pintamos o ponto indicado para -1(cor que não existe na tabela)
         I[i][j] = -1;          //assim vamos fiferenciando a celula que queremos pintar de
                                // outras celulas da mesma cor. Assim evitamos pintar qualquer celula que tenha a "cor_atual"
        int continua_verif = 1;
        while(continua_verif){  //enquanto houver indices sendos pintados de -1 buscamos por novos para pintar 
            continua_verif = 0;

            for(int x = 0; x< linhas; x++){
                for(int y = 0; y < colunas; y++){

                    if(I[x][y] == -1){ // verifica se os vizinhos são validos para pintar. Se sim, os pintas.
                        
                        if(verifica_validade(x, y+1, cor_atual, I)){
                            I[x][y+1] = -1;
                            continua_verif = 1;  // pintou um pixel, logo a busca deve continuar. 
                        }
                        if(verifica_validade(x+1, y, cor_atual, I)){
                            I[x+1][y] = -1;
                            continua_verif = 1;
                        }
                        if(verifica_validade(x-1, y, cor_atual, I)){
                            I[x-1][y] = -1;
                            continua_verif = 1;
                        }
                        if(verifica_validade(x, y-1, cor_atual, I)){
                            I[x][y-1] = -1;
                            continua_verif = 1;
                        }
                    }
                }
            }
        }
        // troca os pixel com valores -1 para a nova cor solicitada. 
        for(int x = 0; x< linhas; x++){
            for(int y = 0; y < colunas; y++){
                if(I[x][y] == -1){
                    I[x][y] = nova_cor;
                }
            }
        }
        
    }
    else{
        return;
    }

    
}

void main() {
//  Caso de teste 1:   
/*    int I[linhas][colunas] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    }; */
//  Caso de teste 2:   
    int I[linhas][colunas] = {
        {3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {3,3,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
        {3,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    
    int i, j, nova_cor, cor_atual;
    print_matrix(I);
    
    printf("informe o codigo da cor(-1 sair): ");
    scanf("%d", &nova_cor);
    
    while(nova_cor != -1){     
        printf("informe as coordenadas: ");
        scanf("%d %d", &i, &j);
        cor_atual = I[i][j];
        colorir(i, j, nova_cor, cor_atual, I);
        print_matrix(I);
        printf("informe o codigo da cor(-1 sair): ");
        scanf("%d", &nova_cor);
    }
    
    printf("fim\n");
}

int verifica_validade(int i, int j, int cor_atual, int I[linhas][colunas]){

    if(i> linhas-1 || j>colunas-1 || i<0 || j<0){ //se o indice não está dentro do limite da matriz
        return 0;
    }
    else if (cor_atual != I[i][j]){ //caso encontre uma barreira, celula de outra cor
        return 0;
    }
    
    return 1;
}
