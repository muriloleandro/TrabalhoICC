#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//structs:
typedef struct datas {
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int ano;
} Data;

typedef struct reserva {
    char *nome;
    char *sobrenome;
    char cpf[15];
    char *numero_assento;
    int classe; // 0 ou 1 ; 0 = economica ; 1 = executiva ;
    Data data_da_viagem;

} Reserva;

typedef struct dados {
    int aberto;
    int assentos;
    float valores[2]; // convenção: 0 = economica ; 1 = executiva ;
    Reserva *reservas;
    int num_reservas;
    Reserva *reservasnovas;
    int num_reservasnovas;
} Dados;


//funções:

void cancelar_reserva(Dados *dados) {
    char cancelado[15];
    scanf("%s", cancelado);
    for(int i = 0; i < dados->num_reservas; i++){
        if(strcmp(dados->reservas[i].cpf, cancelado) == 0){
            for(int j = i; j < dados->num_reservas - 1; j++){
                dados->reservas[j] = dados->reservas[j + 1];
            }
            dados->num_reservas = dados->num_reservas - 1;
            dados->reservas = (Reserva *) realloc(dados->num_reservas * sizeof(Reserva));
            break;
        }
    }
    for(int i = 0; i < 10; i++){
        printf("-----");
    }
    printf("\n");
}

void fechar_dia(Dados dados) {
    float posicao = 0;
    printf("Fechamento do dia: \n");
    printf("Quantidade de reservas: %d\n", dados.num_reservas);
    for(int i = 0; i < dados.num_reservas; i++) {
        if (dados.reservas[i].classe == 0) {
            posicao += dados.valores[0];
        }
        else {
            posição += dados.valores[1];
        }
    }
    printf("Posição: %.2f\n", posicao);
    for(int i = 0; i < 10; i++){
        printf("-----");
    }
    printf("\n");
    exit(0);
}


//main:
int main(void) {
    Dados dados;
    
    ler_arquivo(&dados);



    salvar_arquivo(&dados);
    return 0;
}