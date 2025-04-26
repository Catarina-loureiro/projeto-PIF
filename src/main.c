#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
   int eBomba;
   int estaAberta;
   int vizinhos;
}Celula;

Celula jogo [10][10];
int tam = 10;

void inicio(){
    int l, c;
    for(l = 0; l < tam; l++){
        for(c= 0; c < tam; c++){
            jogo[l][c].eBomba = 0;
            jogo[l][c].estaAberta = 0;
            jogo[l][c].vizinhos = 0;
        }
    }
}
void sorteio(int n){
    int i, l, c;
    srand(time(NULL));
    for(i = 1; i <= n; i++){
        l = rand() % tam;
        c = rand() % tam;
        if(jogo[l][c].eBomba == 0){
            jogo[l][c].eBomba = 1;
        }
        else{
            i--;
        }
    }

}
int coordenadaValida(int l, int c){
    if(l >= 0 && l < tam && c>= 0 && c < tam){
        return 1;
    }
    else{
        return 0;
    }
}

int bombasVizinhas(int l, int c){
    int quantidade = 0;

    if(coordenadaValida(l - 1, c) && jogo[l-1][c].eBomba){
        quantidade++;
    }
    if(coordenadaValida(l + 1, c) && jogo[l+1][c].eBomba){
        quantidade++;
    }
    if(coordenadaValida(l, c + 1) && jogo[l][c+1].eBomba){
        quantidade++;
    }
    if(coordenadaValida(l, c - 1) && jogo[l][c-1].eBomba){
        quantidade++;
    }
    return quantidade;
}

void contagem(){
    int l, c;
    for(l = 0; l < tam; l++){
        for(c= 0; c < tam; c++){
            jogo[l][c].vizinhos = bombasVizinhas(l,c);
        }
    }
}

void imprimir(){
    int l, c;
    printf("\n\n\t    ");

    for(l=0; l< tam; l++){
        printf(" %i  ", l);
    }

    printf("\n\t   -----------------------------------------\n");

    for(l = 0; l < tam; l++){
        printf("\t%i  |", l);
        for(c= 0; c < tam; c++){
            if(jogo[l][c].estaAberta){
                if(jogo[l][c].eBomba){
                    printf(" * ");
                }
                else{
                   printf(" %i ", jogo[l][c].vizinhos);
                }
            }
            else{
                printf("   ");
            }
            printf("|");
        }
        printf("\n\t   -----------------------------------------\n");
    }

}
void abrircelula(int l , int c){
    if (coordenadaValida(l, c)==1 && jogo[l][c].estarAberta==0){
        jogo[l][c].estaAberta= 1;
        if (jogo[l][c].vizinhos==0){
            abrircelula(l-1, c);
            abrircelula(l+1, c);
            abrircelula(l, c +1);
            abrircelula(l, c-1);
        }
    }
}

int ganhou(){
    int quantidade=0;
    int l, c;
    for(l = 0; l < tam; l++){
        for(c= 0; c < tam; c++){
           if (jogo[l][c].estaAberta==0 && jogo[l][c].eBomba==0){
                quantidade++;
           }
        }
    }
    return quantidade
}

void jogar(){
    int linha, coluna;
    do{
        imprimir();
        do{
            printf("\nDigite as coordenadas de linha e coluna: ");
            scanf("%d %d", &linha, &coluna);
            if (coordenadaValida(linha, coluna)==0){
                printf("\nCoordenada inválida!");
            }
        }while (coordenadaValida(linha, coluna)==0 || jogo[linha][coluna].estarAberta == 1);
        abrircelula(linha,coluna);
    }while(ganhou()!=0 && jogo[linha][coluna].eBomba==0);

    if(jogo[linha][coluna].eBomba==1){
        printf("\n\t GAME OVER\n")
    }else{
        printf("\n\t CONGRATS! YOU WON!\n")
    }
}

int main(){

    int op;

    do{

        inicio();
        sorteio(10);
        contagem();
        printf("\n\t\t\tCAMPO MINADO\n");
        jogar();

        printf("Digite 1 para jogar novamente: ");
        scanf("%d", &op);

    }while(op==1);

    return 0;
}
